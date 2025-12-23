/*
flasm, command line assembler & disassembler of flash actionscript bytecode
Copyright (c) 2001 Opaque Industries, (c) 2002-2003 Igor Kogan
All rights reserved. See LICENSE.TXT for terms of use.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "util.h"
#include "action.h"

void disassembleSWF(FILE *f, char *fname);
void skipProtected(FILE *f, unsigned long int length);
void print(char *s, ...);

extern void tellUser(int isError, char *s, ...);
extern char isRA3;

static int indent = 1;
static int targetIndent = 0;
static long int swfabspos = -1;
static long int swfrelpos = -1;

static int swfVersion;

static int nDict = 0;
struct _dict {
	char *value;
	int count;
};
static FILE *outstream;
static struct _dict dictionary[MAX_CONSTANTS];
static char *flasmDict = NULL;

static long int numLabels = 0;
static long int curLabel = 0;
static unsigned long int *labels = NULL;

static unsigned long int conststart = 0, constend = 0;

int printActionRecordCallCount;

/* from flasm.c */
extern int mode;
extern char wasCompressed;

/* from flasm.c <- flasm.ini */
extern int showoffset, hexoffset, literalregisters;

enum {
	eventLoad			= 0x01,
	eventEnterFrame		= 0x02,
	eventUnload			= 0x04,
	eventMouseMove		= 0x08,
	eventMouseDown		= 0x10,
	eventMouseUp		= 0x20,
	eventKeyDown		= 0x40,
	eventKeyUp			= 0x80,
	eventData			= 0x100,
	eventInitialize		= 0x200, /* flash 6/7 only; flash 5 stores smartClip parameters in eventLoad */
	eventPress			= 0x400,
	eventRelease		= 0x800,
	eventReleaseOutside	= 0x1000,
	eventRollOver		= 0x2000,
	eventRollOut		= 0x4000,
	eventDragOver		= 0x8000,
	eventDragOut		= 0x10000,
	eventKeyPress		= 0x20000,
	eventConstruct		= 0x40000 /* flash 7 only */
};

enum {
	IdleToOverUp		= 0x01,
	OverUpToIdle		= 0x02,
	OverUpToOverDown	= 0x04,
	OverDownToOverUp	= 0x08,
	OverDownToOutDown	= 0x10,
	OutDownToOverDown	= 0x20,
	OutDownToIdle		= 0x40,
	IdleToOverDown		= 0x80,
	OverDownToIdle		= 0x100
};

enum {
	keyLeft				= 1,
	keyRight			= 2,
	keyHome				= 3,
	keyEnd				= 4,
	keyInsert			= 5,
	keyDelete			= 6,
	keyBackspace		= 8,
	keyEnter			= 13,
	keyUp				= 14,
	keyDown				= 15,
	keyPgUp				= 16,
	keyPgDn				= 17,
	keyTab				= 18,
	keyEscape			= 19,
	keySpace			= 32
};

/* names of automatic values for function2 */
char *arNames[] = {"this", "arguments", "super", "_root", "_parent", "_global"};
/* flags that are set for particular automatic value */
unsigned int arFlags[] = {0x0001, 0x0004, 0x0010, 0x0040, 0x0080, 0x0100};
/* flags that are set, if the value *is not* used */
unsigned int arNotFlags[] = {0x0002, 0x0008, 0x0020, 0x0000, 0x0000, 0x0000};

static int printNoIndent(char *s, ...)
{
	va_list ap;
	va_start(ap, s);
	return vfprintf(outstream, s, ap);
}

void printChar(int c)
{
	switch ( c )
	{
	case '\b':
		printNoIndent("\\b");
		break;
	case '\t':
		printNoIndent("\\t");
		break;
	case '\n':
		printNoIndent("\\n");
		break;
	case '\f':
		printNoIndent("\\f");
		break;
	case '\r':
		printNoIndent("\\r");
		break;
	case '\\':
		printNoIndent("\\\\");
		break;
	default:
		printNoIndent("%c", (char)c);
		break;
	}
}

static void printIndent(int i)
{
	size_t buflen = INDENT_LEVEL*i;
	static long int lastpos = 0;
	long int swfpos;

	if (showoffset > 0 && mode == MODE_DISASSEMBLE) {
		if (showoffset == 1)
			swfpos = swfrelpos;
		else
			swfpos = swfabspos+swfrelpos;

		/* don't print adress if unchanged */
		if (swfpos >= 0 && (swfpos > lastpos || swfpos == 0)) {
			lastpos = swfpos;
			if (hexoffset == 1)
				/* big endian issues? */
				printNoIndent("%04X%04X", (unsigned int) (0xFFFF & (swfpos>>16)), (unsigned int) (0xFFFF & swfpos));
			else
				printNoIndent("%08li", swfpos);
		}
		else
			buflen += 8;
	}

	if (i>0) {
		char *buf = new char[buflen];
		memset(buf, ' ', buflen);
		fwrite(buf, sizeof(char), buflen, outstream);
		delete [] buf;
	}
}

void skipProtected(FILE *f, unsigned long int length)
{
	if (fseek(f, length, SEEK_CUR) != 0)
		tellUser(1, "Unexpected end of file");
}

static void printstr(char *str)
{
	char *buf = new char[strlen(str)*2+3];
	char *bufp = buf, *bufstr = str;

	*bufp++ = '\'';
	while (*bufstr++ != '\0') {
		switch (*(bufstr-1)) {
			case '\b':
				*bufp++ = '\\';	*bufp++ = 'b';
				break;
			case '\t':
				*bufp++ = '\\';	*bufp++ = 't';
				break;
			case '\n':
				*bufp++ = '\\';	*bufp++ = 'n';
				break;
			case '\f':
				*bufp++ = '\\';	*bufp++ = 'f';
				break;
			case '\r':
				*bufp++ = '\\';	*bufp++ = 'r';
				break;
			case '\'':
				*bufp++ = '\\';	*bufp++ = '\'';
				break;
			case  '\\':
				*bufp++ = '\\';
				*bufp++ = '\\';
				break;
			default:
				*bufp++ = *(bufstr-1);
		}
	}
	*bufp++ = '\'';
    fwrite(buf, sizeof(char), bufp-buf, outstream);
	delete [] buf;
}

static void printFloat(float f, int intCast)
{
	char s[60];
	char *sp, *xpn;

	if (f != f)
		printNoIndent("_NANF");
	else if (f == (1.0f / zero))
		printNoIndent("POSITIVE_INFINITYF");
	else if (f == (-1.0f / zero))
		printNoIndent("NEGATIVE_INFINITYF");
	else {
		sprintf(s, "%#g", (double) f);

		if ((xpn = strchr(s, 'e')) == NULL)
			sp = s + strlen(s) - 1;
		else
			sp = xpn - 2;

		while (*sp == '0')
			--sp;

		if (intCast == 1) {
			if (*sp == '.')
				--sp;
			*(sp + 1) = '\0';
			printNoIndent("%s", s);
		}
		else {
			if (*sp == '.')
				*++sp = '0';
			*++sp = '\0';
			printNoIndent("%s", s);
			if (xpn != NULL)
				printNoIndent("%s", xpn);
			printNoIndent("f");
		}
	}
}

static unsigned int bitPos;
static unsigned int bitBuf;

static void InitBits(FILE *f)
{
	bitPos = 8;
	bitBuf = (unsigned int) fgetc(f);
}

static unsigned int getBits(FILE *f, unsigned int n)
{
	unsigned long int v = 0;

	while (n > bitPos) {
		n -= bitPos;
		v |= bitBuf << n;
		bitBuf = (unsigned int) fgetc(f);
		bitPos = 8;
	}

	bitPos -= n;
	v |= bitBuf >> bitPos;
	bitBuf &= 0xff >> (8 - bitPos);
	/* never need more than 16 bits */
	return (unsigned int) v;
}

static void printFrameNum(unsigned int frameNum)
{
	printNoIndent("\n");
	printIndent(indent);
	printNoIndent("&frame %u\n", frameNum);
}

static void addLabel(unsigned long int offset)
{
	long int i;

	for (i = 0; i < numLabels; ++i) {
		if (labels[i] == offset)
			return;
	}

	SUREALLOC(numLabels, labels, unsigned long int, sizeof (unsigned long int));
	
	if (labels == NULL)
		tellUser(1, "Not enough memory to store all labels");

	labels[numLabels++] = offset;
}

static void processASMLine(char *line);

static void includeFile(const char *ifilename)
{
	FILE *ifile;
	char buf[256];

	while (*ifilename == ' ' || *ifilename == '\t')
		ifilename++;

	if ((ifile = fopen(ifilename, "rt")) == NULL)
		tellUser(1, "Couldn't include file: %s", ifilename);

	printNoIndent("\n// start of %s\n", ifilename);

	while (fgets(buf, 256, ifile))
		processASMLine(buf);

	printNoIndent("\n// end of %s\n", ifilename);

	fclose(ifile);
}

static void processASMLine(char *line)
{
	char *ci = strIstr(line, "constants ");
	char *fi = strIstr(line, "#include ");

	if ((ci == NULL) || (constend == 0)) {
		/* line contains no 'constants' or prev constant declaration absent */
		if (fi != NULL)
			includeFile(fi + 9);
		else
			printNoIndent("%s", line);
	}
	else if (flasmDict == NULL) {
		/* dump flasm statement */
		flasmDict = strdup(ci + 10);
	}
	else {
		/* add user constants */
		flasmDict = (char *)realloc(flasmDict, strlen(flasmDict) + strlen(ci + 10) + 3);
		strcat(flasmDict, ", ");
		strcat(flasmDict, ci + 10);
	}
}

static void checkLabel(unsigned long int addr)
{
	if (curLabel < numLabels) {
		while (addr > labels[curLabel]) {
			printIndent(indent-1);
			printNoIndent(" %s%li: // Wild label in the middle of an action, now placed before next action\n", mode < MODE_UPDATE ? "label" : "lbl", ++curLabel);
			tellUser(0, "Branch into the middle of an action, %s%li (off by %i bytes) is placed before next action", mode < MODE_UPDATE ? "label" : "lbl", curLabel, (int)(addr - labels[curLabel-1]));
		}
		if (addr == labels[curLabel]) {
			printIndent(indent-1);
			/* make sure generated labels don't match user labels */
			printNoIndent(" %s%li:\n", mode < MODE_UPDATE ? "label" : "lbl", ++curLabel);
		}
	}
}

static byte *buffer;

static void printActionRecord(byte *p, Action type, unsigned int *lenptr, char **regtable);

static unsigned long int printActions(byte *p, unsigned long int length, unsigned long int maxActions, char **regtable)
{
	/*
	   processes also nested blocks like 'function', 'with', and 'ifFrameLoaded'
	   stops at given length (in bytes) or after given numActions
	   give ANY_VALUE as parameter, if one of them is unused
	 */
	unsigned long int i = 0;
	unsigned long int curAction = 0;
	unsigned int blocklen;

	while ((i < length) && (curAction < maxActions)) {
		Action type = (Action) p[i];

		checkLabel(p + i - buffer);
		swfrelpos = p + i - buffer;

		++i;

		if ((type & 0x80) != 0) {
			blocklen = S16(p + i);
			i += 2;
		}
		else
			blocklen = 0;

		if (i+blocklen <= length)
			printActionRecord(p + i, type, &blocklen, regtable);
		else {
			tellUser(0, "I'm lost");
			exit(0);
			//return length;
		}

		i += blocklen;
		curAction++;
	}

	checkLabel(p + i - buffer);

	return i;
}

static void printActionRecord(byte *p, Action type, unsigned int *lenptr, char **regtable)
{
	unsigned int len = *lenptr;
	++printActionRecordCallCount;

	switch (type) {
		case SWFACTION_ADD:
			print("&oldAdd\n");
			break;
		case SWFACTION_SUBTRACT:
			print("&subtract\n");
			break;
		case SWFACTION_MULTIPLY:
			print("&multiply\n");
			break;
		case SWFACTION_DIVIDE:
			print("&divide\n");
			break;
		case SWFACTION_EQUALS:
			print("&oldEquals\n");
			break;
		case SWFACTION_LESSTHAN:
			print("&oldLessThan\n");
			break;
		case SWFACTION_LOGICALAND:
			print("&and\n");
			break;
		case SWFACTION_LOGICALOR:
			print("&or\n");
			break;
		case SWFACTION_LOGICALNOT:
			print("&not\n");
			break;
		case SWFACTION_STRINGEQ:
			print("&stringEq\n");
			break;
		case SWFACTION_STRINGLENGTH:
			print("&stringLength\n");
			break;
		case SWFACTION_SUBSTRING:
			print("&substring\n");
			break;
		case SWFACTION_INT:
			print("&int\n");
			break;
		case SWFACTION_POP:
			print("&pop\n");
			break;
		case SWFACTION_SWAP:
			print("&swap\n");
			break;
		case SWFACTION_INITOBJECT:
			print("&initObject\n");
			break;
		case SWFACTION_INITARRAY:
			print("&initArray\n");
			break;
		case SWFACTION_GETVARIABLE:
			print("&getVariable\n");
			break;
		case SWFACTION_SETVARIABLE:
			print("&setVariable\n");
			break;
		case SWFACTION_STRINGCONCAT:
			print("&concat\n");
			break;
		case SWFACTION_GETPROPERTY:
			print("&getProperty\n");
			break;
		case SWFACTION_SETPROPERTY:
			print("&setProperty\n");
			break;
		case SWFACTION_DUPLICATECLIP:
			print("&duplicateClip\n");
			break;
		case SWFACTION_REMOVECLIP:
			print("&removeClip\n");
			break;
		case SWFACTION_TRACE:
			print("&trace\n");
			break;
		case SWFACTION_STARTDRAGMOVIE:
			print("&startDrag\n");
			break;
		case SWFACTION_STOPDRAGMOVIE:
			print("&stopDrag\n");
			break;
		case SWFACTION_STRINGLESSTHAN:
			print("&stringLessThan\n");
			break;
		case SWFACTION_STRINGGREATERTHAN:
			print("&stringGreaterThan\n");
			break;
		case SWFACTION_RANDOM:
			print("&random\n");
			break;
		case SWFACTION_MBLENGTH:
			print("&mbLength\n");
			break;
		case SWFACTION_ORD:
			print("&ord\n");
			break;
		case SWFACTION_CHR:
			print("&chr\n");
			break;
		case SWFACTION_GETTIMER:
			print("&getTimer\n");
			break;
		case SWFACTION_MBSUBSTRING:
			print("&mbSubstring\n");
			break;
		case SWFACTION_MBORD:
			print("&mbOrd\n");
			break;
		case SWFACTION_MBCHR:
			print("&mbChr\n");
			break;
		case SWFACTION_NEXTFRAME:
			print("&nextFrame\n");
			break;
		case SWFACTION_PREVFRAME:
			print("&prevFrame\n");
			break;
		case SWFACTION_PLAY:
			print("&play\n");
			break;
		case SWFACTION_STOP:
			print("&stop\n");
			break;
		case SWFACTION_TOGGLEQUALITY:
			print("&toggleQuality\n");
			break;
		case SWFACTION_STOPSOUNDS:
			print("&stopSounds\n");
			break;

			/* eaf ops */
		case SWFACTION_PUSHNULL:
			print("&pushnull\n");
			break;
		case SWFACTION_PUSHUNDEFINED:
			print("&pushundef\n");
			break;
		case SWFACTION_PUSHTRUE:
			print("&pushtrue\n");
			break;
		case SWFACTION_PUSHFALSE:
			print("&pushfalse\n");
			break;
		case SWFACTION_PUSH1:
			print("&pushone\n");
			break;
		case SWFACTION_PUSHZEROSETVAR:
			print("&pushzerosv\n");
			break;
		case SWFACTION_PUSH0:
			print("&pushzero\n");
			break;
		case SWFACTION_PUSHBYTE:
			print("&pushbyte %d\n", *(signed char*)p);
			break;
		case SWFACTION_PUSHWORD:
			print("&pushshort %d\n", *(signed short*)p);
			break;
		case SWFACTION_PUSHDWORD:
			print("&pushlong %d\n", *(signed int *)p);
			break;
		case SWFACTION_PUSHTHISVARIABLE:
			print("&pushthisgv\n");
			break;
		case SWFACTION_PUSHGLOBALVARIABLE:
			print("&pushglobalgv\n");
			break;
		case SWFACTION_DICTCALLFUNCPOP:
			{
				char *str = dictionary[(short)*p].value;
				short v = *p;
				++dictionary[v].count;
				if (!isRA3)
				{
					signed char c = v;
					if (c < 0)
					{
						str = "(null)";
					}
					print("&dcallfp %d\t\t\t\t\t\t\t// %s()\n", c, str);
				}
				else
				{
					print("&dcallfp %d\t\t\t\t\t\t\t// %s()\n", v, str);
				}
				break;
			}
		case SWFACTION_TRACESTART:
			print("&apttracestart\n");
			break;
		case SWFACTION_DICTCALLFUNCSETVAR:
			{
				char *str = dictionary[(short)*p].value;
				short v = *p;
				++dictionary[v].count;
				print("&dcallfsv %d\t\t\t\t\t\t\t// %s()\n", v, str);
				break;
			}
		case SWFACTION_DICTCALLMETHODPOP:
			{
				char *str = dictionary[(short)*p].value;
				short v = *p;
				++dictionary[v].count;
				if (!isRA3)
				{
					signed char c = v;
					if (c < 0)
					{
						str = "(null)";
					}
					print("&dcallmp %d\t\t\t\t\t\t\t// %s()\n", c, str);
				}
				else
				{
					print("&dcallmp %d\t\t\t\t\t\t\t// %s()\n", v, str);
				}
				break;
			}
		case SWFACTION_DICTCALLMETHODSETVAR:
			{
				char *str = dictionary[(short)*p].value;
				short v = *p;
				++dictionary[v].count;
				print("&dcallmsv %d\t\t\t\t\t\t\t// %s()\n", v, str);
				break;
			}
		case SWFACTION_PUSHSTRINGGETVAR:
			print("&pushsgv ");
			printstr((char *)p);
			printNoIndent("\n");
			break;
		case SWFACTION_PUSHSTRINGGETMEMBER:
			print("&pushsgm ");
			printstr((char *)p);
			printNoIndent("\n");
			break;
		case SWFACTION_PUSHSTRINGSETVAR:
			print("&pushssv ");
			printstr((char *)p);
			printNoIndent("\n");
			break;
		case SWFACTION_PUSHSTRINGSETMEMBER:
			print("&pushssm ");
			printstr((char *)p);
			printNoIndent("\n");
			break;
		case SWFACTION_PUSHFLOAT:
			print("&pushfloat %.15f\n", *(float *)p);
			break;
		case SWFACTION_CALLFUNCANDPOP:
			print("&callfp\n");
			break;
		case SWFACTION_CALLFUNCSETVAR:
			print("&callfsv\n");
			break;
		case SWFACTION_CALLMETHODPOP:
			print("&callmp\n");
			break;
		case SWFACTION_CALLMETHODSETVAR:
			print("&callmsv\n");
			break;
		case SWFACTION_STRINGDICTBYTEGETVAR:
			{
				char *str = dictionary[(short)*p].value;
				short v = *p;
				++dictionary[v].count;
				print("&pushsdbgv %u\t\t\t\t\t\t\t//", v);
				printstr(str);
				printNoIndent("\n");
				break;
			}
		case SWFACTION_STRINGDICTBYTEGETMEMBER:
			{
				char *str = dictionary[(short)*p].value;
				short v = *p;
				++dictionary[v].count;
				print("&pushsdbgm %u\t\t\t\t\t\t\t//", v);
				printstr(str);
				printNoIndent("\n");
				break;
			}
		case SWFACTION_PUSHSTRING:
			print("&pushs ");
			printstr((char *)p);
			printNoIndent("\n");
			break;
		case SWFACTION_PUSHSTRINGDICTBYTE:
			{
				char *str = dictionary[(short)*p].value;
				short v = *p;
				++dictionary[v].count;
				print("&pushsdb %u\t\t\t\t\t\t\t//", v);
				printstr(str);
				printNoIndent("\n");
				break;
			}
		case SWFACTION_PUSHSTRINGDICTWORD:
			{
				short v = S16(p);
				char *str = dictionary[v].value;
				++dictionary[v].count;
				print("&pushsdw %u\t\t\t\t\t\t\t//", (unsigned short)v);
				printstr(str);
				printNoIndent("\n");
				break;
			}

			/* ops with args */
		case SWFACTION_PUSHDATA:
			{
				byte pushtype;
				byte *start = p;
				long int pushstart;

				/* may need to go back and erase push while processing flasm macros */
				pushstart = ftell(outstream);


				while (p < start + len) {
					print("&push ");
					switch (pushtype = *p++) {
						case 0:														 /* string */
							{
								char *d = (char *) p;
								if (mode >= MODE_UPDATE && (Action) start[len] == SWFACTION_POP) {
									fseek(outstream, pushstart, SEEK_SET);				 /* go back to overwrite 'push'            */
									processASMLine(d);
									p = start + len;								 /* skip to the end of push statement      */
									*lenptr += 1;
								}
								else {
									printNoIndent("%s", "");
									printstr(d);
									p += strlen(d) + 1;
								}
								break;
							}

						case 1:														 /* float, used by flash for properties only */
							{
								float f;
								double prop;

								if (byteorder == FLASM_BIG_ENDIAN) {
									byte *fp = (byte *) (&f);

									fp[0] = p[3];
									fp[1] = p[2];
									fp[2] = p[1];
									fp[3] = p[0];
								}
								else
									f = *(float *) p;

								printNoIndent("%s", "");

								if (modf((double) f, &prop) == 0) {						 /* integer, most likely property */
									switch ((int) prop) {
										case 0:
											printNoIndent("X_PROPERTY");
											break;
										case 1:
											printNoIndent("Y_PROPERTY");
											break;
										case 2:
											printNoIndent("XSCALE_PROPERTY");
											break;
										case 3:
											printNoIndent("YSCALE_PROPERTY");
											break;
										case 4:
											printNoIndent("CURRENTFRAME_PROPERTY");
											break;
										case 5:
											printNoIndent("TOTALFRAMES_PROPERTY");
											break;
										case 6:
											printNoIndent("ALPHA_PROPERTY");
											break;
										case 7:
											printNoIndent("VISIBLE_PROPERTY");
											break;
										case 8:
											printNoIndent("WIDTH_PROPERTY");
											break;
										case 9:
											printNoIndent("HEIGHT_PROPERTY");
											break;
										case 10:
											printNoIndent("ROTATION_PROPERTY");
											break;
										case 11:
											printNoIndent("TARGET_PROPERTY");
											break;
										case 12:
											printNoIndent("FRAMESLOADED_PROPERTY");
											break;
										case 13:
											printNoIndent("NAME_PROPERTY");
											break;
										case 14:
											printNoIndent("DROPTARGET_PROPERTY");
											break;
										case 15:
											printNoIndent("URL_PROPERTY");
											break;
										case 16:
											printNoIndent("HIGHQUALITY_PROPERTY");
											break;
										case 17:
											printNoIndent("FOCUSRECT_PROPERTY");
											break;
										case 18:
											printNoIndent("SOUNDBUFTIME_PROPERTY");
											break;
										case 19:
											printNoIndent("QUALITY_PROPERTY");
											break;
										case 20:
											printNoIndent("XMOUSE_PROPERTY");
											break;
										case 21:
											printNoIndent("YMOUSE_PROPERTY");
											break;
										default:
											printFloat(f, 0);
									}
								}
								else
									printFloat(f, 0);

								p += 4;
								break;
							}

						case 2:
							/* null */
							printNoIndent("%sNULL", "");
							break;

						case 3:
							/* undefined */
							printNoIndent("%sUNDEF", "");
							break;

						case 4:
							/* register */
							if (literalregisters && regtable != NULL && regtable[*p] != NULL && *regtable[*p] != '\0')
								printNoIndent("%sr:%s", "", regtable[*p++]);
							else
								printNoIndent("%sr:%i", "", *p++);

							break;

						case 5:
							/* boolean */
							if (*p++)
								printNoIndent("%s&TRUE", "");
							else
								printNoIndent("%s&FALSE", "");
							break;

						case 6:
							/* double */
							{
								double d;
								byte *dp = (byte *) (&d);
								char s[100];
								char *sp, *xpn;

								if (byteorder == FLASM_BIG_ENDIAN) {
									dp[0] = p[3];
									dp[1] = p[2];
									dp[2] = p[1];
									dp[3] = p[0];
									dp[4] = p[7];
									dp[5] = p[6];
									dp[6] = p[5];
									dp[7] = p[4];
								}
								else {
									dp[0] = p[4];
									dp[1] = p[5];
									dp[2] = p[6];
									dp[3] = p[7];
									dp[4] = p[0];
									dp[5] = p[1];
									dp[6] = p[2];
									dp[7] = p[3];
								}

								/* the old way without '1.5e-24'-like notation
								   fprec = 15-floor(log10(fabs(d)));
								   sprintf(s,"%.*f",fprec,d); */

								printNoIndent("%s", "");

								if (d == 0) {
									if (mode < MODE_UPDATE)
										printNoIndent("0.0");
									else
										printNoIndent("0");									 /* save some bytes in update mode - integer instead of double */
								}
								else if (d != d)
									printNoIndent("_NAN");
								else if (d == (1.0 / zero))
									printNoIndent("POSITIVE_INFINITY");
								else if (d == (-1.0 / zero))
									printNoIndent("NEGATIVE_INFINITY");
								else {
									sprintf(s, "%#.*g", 16, d);

									if ((xpn = strchr(s, 'e')) == NULL)
										sp = s + strlen(s) - 1;
									else
										sp = xpn - 2;									 /* one digit less precision for exp form values
																						    preventing MAX_NUMBER rounding to INFINITY */

									while (*sp == '0')									 /* delete 0's at the end of the number or mantissa */
										--sp;

									if (*sp == '.')										 /* expand values like "1." to "1.0" */
										*++sp = '0';

									*++sp = '\0';										 /* terminate buffer (exponent is cutted off) */

									printNoIndent("%s", s);

									if (xpn != NULL)									 /* if exponent here, print it */
										printNoIndent("%s", xpn);
								}

								p += 8;
								break;
							}

						case 7:
							/* integer */
							{
								int i;

								if (byteorder == FLASM_BIG_ENDIAN) {
									byte *ip = (byte *) (&i);

									ip[0] = p[3];
									ip[1] = p[2];
									ip[2] = p[1];
									ip[3] = p[0];
								}
								else
									i = *(int *) p;

								printNoIndent("%s%i", "", i);
								p += 4;
								break;
							}

						case 8:
							/* dictionary, 1-byte reference */
							{
								char *d = dictionary[*p].value;

								if (mode >= MODE_UPDATE && (Action) start[len] == SWFACTION_POP) {
									fseek(outstream, pushstart, SEEK_SET);				 /* go back to overwrite 'push'            */
									processASMLine(d);
									p = start + len;								 /* skip to the end of push statement      */
									*lenptr += 1;
								}
								else {
									printNoIndent("%s", "");
									printstr(d);
									dictionary[*p].count++;							  /* constant used one more time */
									p++;
								}
								break;
							}

						case 9:
							/* dictionary, 2-byte reference */
							{
								char *d = dictionary[(short)S16(p)].value;

								if (mode >= MODE_UPDATE && (Action) start[len] == SWFACTION_POP) {
									fseek(outstream, pushstart, SEEK_SET);				 /* go back to overwrite 'push'            */
									processASMLine(d);
									p = start + len;								 /* skip to the end of push statement      */
									*lenptr += 1;
								}
								else {
									printNoIndent("%s", "");
									printstr(d);
									dictionary[S16(p)].count++;						  /* constant used one more time */
									p += 2;
								}
								break;
							}

						default:
							printNoIndent("%s%s // unknown push type %i: rest of push skipped", "", "???", pushtype);
							tellUser(0, "Unknown push type %i: rest of push skipped", pushtype);
							p = start + len;
					}
					print("\n");
				}


				break;
			}

		case SWFACTION_GOTOFRAME:
			print("&gotoFrame %u\n", S16(p));
			p += 2;
			break;

			/* eaf ops */
		case SWFACTION_PUSHGLOBAL:
			print("&pushglobal\n");
			break;
		case SWFACTION_PUSHTHIS:
			print("&pushthis\n");
			break;

		case SWFACTION_GETURL:
		{
			char *url = (char *) p;
			p += strlen(url) + 1;
			print("&getURL ");
			printstr(url);
			print(" ");
			printstr((char *) p);
			print("\n");
			break;
		}

		case SWFACTION_BRANCHALWAYS:
		{
			long int l = longintBinaryFind((unsigned long int)(p + 2 + S16signed(p) - buffer), labels, numLabels);
			if (l >= 0) {
				print("&jmp %s%i", mode < MODE_UPDATE ? "label" : "lbl", l + 1, labels);
				if (showoffset == 0)
					print("\n");
				else
					printNoIndent(" // offset %i\n", S16signed(p));
			}
			else {
				print("&jmp %i // branch target not found\n", S16signed(p));
				tellUser(0, "jmp target not found: %li", S16signed(p));
			}
			break;
		}

		case SWFACTION_BRANCHIFTRUE:
		{
			long int l = longintBinaryFind((unsigned long int)(p + 2 + S16signed(p) - buffer), labels, numLabels);
			if (l >= 0) {
				print("&jnz %s%i", mode < MODE_UPDATE ? "label" : "lbl", l + 1, labels);
				if (showoffset == 0)
					print("\n");
				else
					printNoIndent(" // offset %i\n", S16signed(p));
			}
			else {
				print("&jnz %i // branch target not found\n", S16signed(p));
				tellUser(0, "jnz target not found: %li", S16signed(p));
			}
			break;
		}

			/* eaf op */
		case SWFACTION_BRANCHIFFALSE:
		{
			long int l = longintBinaryFind((unsigned long int)(p + 2 + S16signed(p) - buffer), labels, numLabels);
			if (l >= 0) {
				print("&jz %s%i", mode < MODE_UPDATE ? "label" : "lbl", l + 1, labels);
				if (showoffset == 0)
					print("\n");
				else
					printNoIndent(" // offset %i\n", S16signed(p));
			}
			else {
				print("&jz %i // branch target not found\n", S16signed(p));
				tellUser(0, "jz target not found: %li", S16signed(p));
			}
			break;
		}

		case SWFACTION_GETURL2:
			{
				byte flags = *p;
				switch (flags) {
					case 0:
						print("&getURL2\n");
						break;
					case 1:
						print("&getURL2 GET\n");
						break;
					case 2:
						print("&getURL2 POST\n");
						break;
					case 0x40:
						print("&loadMovie\n");
						break;
					case 0x41:
						print("&loadMovie GET\n");
						break;
					case 0x42:
						print("&loadMovie POST\n");
						break;
					case 0x80:
						print("&loadVariablesNum\n");
						break;
					case 0x81:
						print("&loadVariablesNum GET\n");
						break;
					case 0x82:
						print("&loadVariablesNum POST\n");
						break;
					case 0xC0:
						print("&loadVariables\n");
						break;
					case 0xC1:
						print("&loadVariables GET\n");
						break;
					case 0xC2:
						print("&loadVariables POST\n");
						break;
					default:
						print("&getURL2 (0x%x) // unknown flag\n", flags);
						tellUser(0, "Unknown getURL2 flag: 0x%x");
				}

				break;
			}

		case SWFACTION_CALLFRAME:
			print("&callFrame\n");
			break;

		case SWFACTION_GOTOEXPRESSION:
			print("&goto");
			if (*p == 0)
				printNoIndent("AndStop");
			else if (*p == 1)
				printNoIndent("AndPlay");
			else if ((*p == 2) && (len == 3)) {
				/* undocumented additional argument - the number of frames in all previous scenes */
				p++;
				printNoIndent("AndStop skip %u\n", S16(p));
			}
			else if ((*p == 3) && (len == 3)) {
				/* undocumented additional argument - the number of frames in all previous scenes */
				p++;
				printNoIndent("AndPlay skip %u\n", S16(p));
			}
			else {
				/* what the hell is it? assume andPlay, since flag>1 */
				printNoIndent("AndPlay // unknown goto flag %i\n", *p);
				tellUser(0, "Unknown goto flag %i", *p);
			}
			break;

		case SWFACTION_IFFRAMELOADED:
			{
				unsigned int frame = S16(p);
				byte frameLoadedActions;
				p += 2;
				print("&ifFrameLoaded %u\n", frame);
				++indent;
				frameLoadedActions = *p++;
				*lenptr += printActions(p, ANY_VALUE, (unsigned long int) frameLoadedActions, regtable);
				--indent;
				print("&end // of ifFrameLoaded %u\n\n", frame);
				break;
			}

		case SWFACTION_IFFRAMELOADEDEXPRESSION:
			{
				byte frameLoadedActions;
				print("&ifFrameLoadedExpr\n");
				++indent;
				frameLoadedActions = *p++;
				*lenptr += printActions(p, ANY_VALUE, (unsigned long int) frameLoadedActions, regtable);
				--indent;
				print("&end // of ifFrameLoadedExpr\n\n");
				break;
			}

		case SWFACTION_SETTARGET:
			{
				if (targetIndent == 1) {
					--indent;
					print("&end\n");
					targetIndent = 0;
				}
				if (strlen((char *) p) > 0) {
					print("&setTarget '%s'\n", p);
					++indent;
					targetIndent = 1;
				}
				break;
			}

		case SWFACTION_SETTARGETEXPRESSION:
			if (targetIndent == 1) {
				--indent;
				print("&end\n");
				targetIndent = 0;
			}
			print("&setTargetExpr\n");
			++indent;
			targetIndent = 1;
			break;

		case SWFACTION_GOTOLABEL:
			print("&gotoLabel '%s'\n", p);
			break;

		case SWFACTION_END:
			break;

			/* f5 ops */
		case SWFACTION_DELETE:
			print("&delete\n");
			break;
		case SWFACTION_DELETE2:
			print("&delete2\n");
			break;
		case SWFACTION_VAR:
			print("&var\n");
			break;
		case SWFACTION_VAREQUALS:
			print("&varEquals\n");
			break;
		case SWFACTION_CALLFUNCTION:
			print("&callFunction\n");
			break;
		case SWFACTION_RETURN:
			print("&return\n");
			break;
		case SWFACTION_MODULO:
			print("&modulo\n");
			break;
		case SWFACTION_NEW:
			print("&new\n");
			break;
		case SWFACTION_TYPEOF:
			print("&typeof\n");
			break;
		case SWFACTION_TARGETPATH:
			print("&targetPath\n");
			break;
		case SWFACTION_NEWADD:
			print("&add\n");
			break;
		case SWFACTION_NEWLESSTHAN:
			print("&lessThan\n");
			break;
		case SWFACTION_NEWEQUALS:
			print("&equals\n");
			break;
		case SWFACTION_TONUMBER:
			print("&toNumber\n");
			break;
		case SWFACTION_TOSTRING:
			print("&toString\n");
			break;
		case SWFACTION_DUP:
			print("&dup\n");
			break;
		case SWFACTION_GETMEMBER:
			print("&getMember\n");
			break;
		case SWFACTION_SETMEMBER:
			print("&setMember\n");
			break;
		case SWFACTION_INCREMENT:
			print("&increment\n");
			break;
		case SWFACTION_DECREMENT:
			print("&decrement\n");
			break;
		case SWFACTION_NEWMETHOD:
			print("&newMethod\n");
			break;
		case SWFACTION_CALLMETHOD:
			print("&callMethod\n");
			break;
		case SWFACTION_BITWISEAND:
			print("&bitwiseAnd\n");
			break;
		case SWFACTION_BITWISEOR:
			print("&bitwiseOr\n");
			break;
		case SWFACTION_BITWISEXOR:
			print("&bitwiseXor\n");
			break;
		case SWFACTION_SHIFTLEFT:
			print("&shiftLeft\n");
			break;
		case SWFACTION_SHIFTRIGHT:
			print("&shiftRight\n");
			break;
		case SWFACTION_SHIFTRIGHT2:
			print("&shiftRight2\n");
			break;

		case SWFACTION_CONSTANTPOOL:
			{
				unsigned int i, n = S16(p);
				int willInclude = 0;
				unsigned int constLen = 2;

				if (n > MAX_CONSTANTS)
					tellUser(0, "Too many constants");

				p += 2;
				conststart = ftell(outstream);
				print("&constants ");

				nDict = 0;

				for (i = 0; i < n; ++i) {
					if (strIcmp((char *) p, "$include") == 0)
						willInclude = 1;

					dictionary[i].value = (char *) p;
					dictionary[i].count = 0;
					nDict++;

					printstr((char *) p);
					if (i < n - 1)
						printNoIndent("%s", ", ");
					else
						printNoIndent("%s", "  ");

					constLen += strlen((char *) p) + 1;
					p += strlen((char *) p) + 1;
				}

				if (constLen != len) {
					tellUser(0, "Declared constant pool length %u differs from calculated length %u", len, constLen);
					/* try to restore the real constant pool length */
					*lenptr = constLen;
				}

				printNoIndent("%s", "\n");

				/* put some free space after constant pool to add user constants from included file later */
				if (willInclude == 1)
					for (i = 0; i < MAX_INCLUDE_POOL; ++i)
						print(" ");

				constend = ftell(outstream);

				break;
			}

		case SWFACTION_WITH:
			{
				unsigned int withlen = S16(p);

				print("&with\n");

				++indent;
				printActions(p + 2, (unsigned long int) withlen, ANY_VALUE, regtable);
				--indent;

				*lenptr += withlen;

				print("&end\n");

				break;
			}

		case SWFACTION_DEFINEFUNCTION:
			{
				int nargs;
				unsigned int funclen;
				char *name = (char *) p;
				char *argname;

				p += strlen(name) + 1;
				nargs = S16(p);
				p += 2;

				//if (mode < MODE_UPDATE && !isKeyword(name))
				print("&function %s (", name);

				if (nargs > 0) {
					argname = (char *) p;
					printNoIndent("'%s'", argname);
					p += strlen(argname) + 1;
					--nargs;
				}

				for (; nargs > 0; --nargs) {
					argname = (char *) p;
					printNoIndent(", '%s'", argname);
					p += strlen(argname) + 1;
				}

				print(")");
				print("\n");

				funclen = S16(p);
				p += 2;

				++indent;
				printActions(p, (unsigned long int) funclen, ANY_VALUE, NULL);
				--indent;

				print("&end // of function %s\n\n", name);

				*lenptr += funclen;

				break;
			}

		case SWFACTION_ENUMERATE:
			print("&enumerate\n");
			break;

		case SWFACTION_SETREGISTER:
			if (literalregisters && regtable != NULL && regtable[*p] != NULL && *regtable[*p] != '\0')
				print("&setRegister r:%s\n", regtable[*p]);
			else
				print("&setRegister r:%i\n", *p);
			break;

		case SWFACTION_STRICTEQUALS:
			print("&strictEquals\n");
			break;

		case SWFACTION_GREATERTHAN:
			print("&greaterThan\n");
			break;

		case SWFACTION_ENUMERATEVALUE:
			print("&enumerateValue\n");
			break;

		case SWFACTION_INSTANCEOF:
			print("&instanceOf\n");
			break;

		case SWFACTION_STRICTMODE:
			print("&strictMode");
			if (*p > 0)
				printNoIndent(" ON");
			else
				printNoIndent(" OFF");
			break;

		case SWFACTION_DEFINEFUNCTION2:
			{
				unsigned int i, funclen, nargs, autoregFlags;
				byte nregisters, curautoreg;
				char *argnames[MAX_REGISTERS];
				char *name = (char *) p;
				memset(argnames, 0, MAX_REGISTERS * sizeof (char *));

				p += strlen(name) + 1;
				nargs = S16(p);
				p += 2;
				nregisters = *p++;
				autoregFlags = S16(p);
				p += 2;

				//if (mode < MODE_UPDATE && !isKeyword(name))
				if (mode < MODE_UPDATE)
					print("&function2 %s (", name);
				else
					print("&function2 '%s' (", name);

				/* print function arguments, store links to their names in register allocation table */
				for (; nargs > 0; nargs--) {
					byte reg = *p;
					char *arg = (char *)(p+1);

					if (reg != 0) {
						if (argnames[reg] != NULL) {
							tellUser (0, "Duplicate register allocation in function2 %s: %s and %s both go to r:%u", name, argnames[reg], arg, reg);
						}

						argnames[reg] = arg;
						printNoIndent("r:%u='%s'%s", reg, arg, nargs == 1 ? "" : ", ");
					}
					else
						printNoIndent("'%s'%s", arg, nargs == 1 ? "" : ", ");

					p += strlen(arg) + 2;
				}

				printNoIndent("%s", ")");

				/* allocate registers for "automatic" names based on flags */
				curautoreg = 1;

				for (i = 0; i < MAX_AUTO_REGS; i++) {
					if (autoregFlags & arFlags[i]) {
						if (argnames[curautoreg] != NULL && strcmp(argnames[curautoreg], arNames[i])) {
							tellUser (0, "Duplicate register allocation in function2 %s: %s and %s both go to r:%u", name, argnames[curautoreg], arNames[i], curautoreg);
						}
						argnames[curautoreg] = arNames[i];
						autoregFlags -= arFlags[i];
						curautoreg++;
					}
					else
						autoregFlags -= arNotFlags[i];
				}

				if (autoregFlags != 0)
					tellUser(0,"Unknown register flag for function2 %s: %u", name, autoregFlags);

				/* print "automatic" register list */
				printNoIndent("%s", " (");
				for (i = 1; i < curautoreg; i++) {
					if (argnames[i] != NULL)
						printNoIndent("r:%u='%s'%s", i, argnames[i], curautoreg - i - 1 > 0 ? ", " : "");
				}
				/* printNoIndent(") // allocate %u\n", nregisters); */
				printNoIndent("%s", ")\n");

				funclen = S16(p);
				p += 2;

				++indent;
				printActions(p, (unsigned long int) funclen, ANY_VALUE, argnames);
				--indent;

				print("&end // of function %s\n\n", name);

				*lenptr += funclen;

				break;
			}

		case SWFACTION_THROW:
			print("&throw\n");
			break;

		case SWFACTION_EXTENDS:
			print("&extends\n");
			break;

		case SWFACTION_IMPLEMENTS:
			print("&implements\n");
			break;

		case SWFACTION_CAST:
			print("&cast\n");
			break;

		case SWFACTION_TRY:
			{
				unsigned int trylen, catchlen, finallylen;
				/* try type */
				byte catchtype = *p++;
				trylen = S16(p);
				p += 2;
				catchlen = S16(p);
				p += 2;
				finallylen = S16(p);
				p += 2;

				if (catchtype & 4) {
					/* error in register */
					if (literalregisters && regtable != NULL && regtable[*p] != NULL && *regtable[*p] != '\0')
						print("&try r:%s\n", regtable[*p++]);
					else
						print("&try r:%u\n", *p++);
				}
				else {
					/* error in variable */
					if (mode < MODE_UPDATE)
						print("&try %s\n", (char *) p);
					else
						print("&try '%s'\n", (char *) p);
					p += len-7;
				}

				++indent;
				printActions(p, (unsigned long int) trylen, ANY_VALUE, regtable);
				--indent;

				if (catchlen > 0) {
					print("&catch\n");
					++indent;
					printActions(p+trylen, (unsigned long int) catchlen, ANY_VALUE, regtable);
					--indent;
				}
				if (finallylen > 0) {
					print("&finally\n");
					++indent;
					printActions(p+trylen+catchlen, (unsigned long int) finallylen, ANY_VALUE, regtable);
					--indent;
				}

				*lenptr += trylen+catchlen+finallylen;
				print("&end // of try\n");
				break;
			}

		case SWFACTION_PUSHREGISTER:
			{
				print("&pushregister %i\n", *p);
				break;
			}

		default:
			print("&swfAction 0x%02x", type);
			if (len > 0) {
				unsigned int i;
				printNoIndent("%s", " hexdata ");
				for (i = 0; i < len; ++i) {
					printNoIndent("0x%02X", *p);
					if (i < len - 1)
						printNoIndent("%s", ",");
					p++;
				}
			}
			printNoIndent("%s", " // unknown action!\n");
			tellUser(0, "Unknown action 0x%02x", type);
	}
	return;
}

static void rebuildConstantPool(void)
{
	long int curpos = ftell(outstream);
	unsigned long int k;
	int i;
	int constOK = 0;

	fseek(outstream, conststart, SEEK_SET);												 /* go back to the last constants declaration */

	for (i = 0; i < nDict; ++i) {
		/* remove constants used less than 2 times, and empty strings */
		if ((dictionary[i].count > 1) && (strlen(dictionary[i].value) > 0)) {
			if (constOK == 0) {
				print("constants ");
				constOK = 1;
			}

			printstr(dictionary[i].value);
			printNoIndent("%s", ", ");
		}
	}

	if (flasmDict != NULL) {
		if (constOK == 0) {
			print("constants ");
			constOK = 1;
		}
		if (ftell(outstream) + strlen(flasmDict) >= constend)
			tellUser(0, "Too many user constants: %s", flasmDict);
		else
			printNoIndent("%s", flasmDict);													 /* add user constants */
	}
	else if (constOK == 1)
		fseek(outstream, -2, SEEK_CUR);													 /* remove last ", " */

	print("\n");

	for (k = ftell(outstream); k < constend - 1; ++k)										 /* fill the rest of former constants with spaces */
		print(" ");

	print("\n");

	conststart = 0;
	constend = 0;
	if (flasmDict != NULL) {
		free(flasmDict);
		flasmDict = NULL;
	}
	fseek(outstream, curpos, SEEK_SET);
}

static void readActionBuffer(FILE *f, unsigned long int length)
{
	if (length == 0)
		return;

	buffer = (byte *)malloc(length);
	if (buffer == NULL)
		tellUser(1, "Not enough memory to process action block");

	if (fread(buffer, 1, length, f) != length)
		tellUser(1, "Attempt to read beyond EOF");
}

static void createLabels(unsigned long int length)
{
	unsigned long int i;
	unsigned int blocklen;

	numLabels = 0;
	curLabel = 0;
	for (i = 0; i < length; ++i) {
		if (buffer[i] & 0x80) {
			blocklen = S16(buffer + i + 1);

			if ((Action) buffer[i] == SWFACTION_BRANCHALWAYS || (Action) buffer[i] == SWFACTION_BRANCHIFTRUE || (Action) buffer[i] == SWFACTION_BRANCHIFFALSE) {
				if ((signed long int) (i + 3 + blocklen + S16signed(buffer + i + 3)) >= 0) {
					addLabel(i + 3 + blocklen + S16signed(buffer + i + 3));
				}
			}
			else if ((Action) buffer[i] == SWFACTION_CONSTANTPOOL) {
				/* an attempt to fix broken constant pools in "obfuscated" swfs */
				byte *p = buffer + i + 3;
				unsigned int n, nStrings = S16(p);
				p += 2;
				for (n = 0; n < nStrings; ++n)
					p += strlen((char *) p) + 1;

				if (blocklen != p - buffer - i - 3)
					blocklen = p - buffer - i - 3;
			}

			i += blocklen + 2;
		}
	}
}

static void printActionBlock(FILE *f, unsigned long int length, abType abtype, unsigned int flags, byte key)
{
	swfabspos = ftell(f);
	swfrelpos = 0;

	nDict = 0;

	++indent;

	readActionBuffer(f, length);

	createLabels(length);

	qsort(labels, (size_t) numLabels, sizeof (unsigned long int), longintCompare);

	printActions(buffer, length, ANY_VALUE, NULL);

#if 0
	if ((mode >= MODE_UPDATE) && (constend > 0))
		rebuildConstantPool();
#endif

	if (targetIndent == 1) {
		--indent;
		print("&end\n");
		targetIndent = 0;
	}

	--indent;

	if (buffer != NULL) {
		free(buffer);
		buffer = NULL;
	}

	if (labels != NULL) {
		free(labels);
		labels = NULL;
	}

	swfabspos = -1;
	swfrelpos = -1;
}

static void skipMatrix(FILE *f)
{
	InitBits(f);
	if (getBits(f, 1))
		getBits(f, getBits(f, 5) * 2);
	if (getBits(f, 1))
		getBits(f, getBits(f, 5) * 2);
	getBits(f, getBits(f, 5) * 2);
}

static void skipColorTransform(FILE *f)
{
	unsigned int needAdd, needMul, nBits;
	InitBits(f);
	needAdd = getBits(f, 1);
	needMul = getBits(f, 1);
	nBits = getBits(f, 4);
	if (needMul)
		getBits(f, nBits * 4);
	if (needAdd)
		getBits(f, nBits * 4);
}

static void parseKeyPressEvent(byte onKey)
{
	printNoIndent("&keyPress ");

	if ((onKey) == keySpace)
		printNoIndent("&_SPACE");
	else if ((onKey) > 47)
		printNoIndent("'%c'", onKey);
	else
		switch (onKey) {
			case keyLeft:
				printNoIndent("&_LEFT");
				break;
			case keyRight:
				printNoIndent("&_RIGHT");
				break;
			case keyHome:
				printNoIndent("&_HOME");
				break;
			case keyEnd:
				printNoIndent("&_END");
				break;
			case keyInsert:
				printNoIndent("&_INSERT");
				break;
			case keyDelete:
				printNoIndent("&_DELETE");
				break;
			case keyBackspace:
				printNoIndent("&_BACKSPACE");
				break;
			case keyEnter:
				printNoIndent("&_ENTER");
				break;
			case keyUp:
				printNoIndent("&_UP");
				break;
			case keyDown:
				printNoIndent("&_DOWN");
				break;
			case keyPgUp:
				printNoIndent("&_PGUP");
				break;
			case keyPgDn:
				printNoIndent("&_PGDN");
				break;
			case keyTab:
				printNoIndent("&_TAB");
				break;
			case keyEscape:
				printNoIndent("&_ESCAPE");
				break;
			default:
				printNoIndent("unknown key %i", onKey);
				tellUser(0, "Unknown key %i", onKey);
		}
}

void print(char *s, ...)
{
	va_list ap;

	printIndent(indent);

	va_start(ap, s);
	vfprintf(outstream, s, ap);
	va_end(ap);
}

static void parseButtonEvent(FILE *f, unsigned int event, unsigned long int length)
{
	char delim = ' ';
	byte key = 0;

	print("\n");
	++indent;
	print("&on");

	if (event & IdleToOverUp) {
		print("%c", delim);
		printNoIndent("&idleToOverUp");
		delim = ',';
	}

	if (event & OverUpToIdle) {
		print("%c", delim);
		printNoIndent("&overUpToIdle");
		delim = ',';
	}

	if (event & OverUpToOverDown) {
		print("%c", delim);
		printNoIndent("&overUpToOverDown");
		delim = ',';
	}

	if (event & OverDownToOverUp) {
		print("%c", delim);
		printNoIndent("&overDownToOverUp");
		delim = ',';
	}

	if (event & OverDownToOutDown) {
		print("%c", delim);
		printNoIndent("&overDownToOutDown");
		delim = ',';
	}

	if (event & OutDownToOverDown) {
		print("%c", delim);
		printNoIndent("&outDownToOverDown");
		delim = ',';
	}

	if (event & OutDownToIdle) {
		print("%c", delim);
		printNoIndent("&outDownToIdle");
		delim = ',';
	}

	if (event & IdleToOverDown) {
		print("%c", delim);
		printNoIndent("&idleToOverDown");
		delim = ',';
	}

	if (event & OverDownToIdle) {
		print("%c", delim);
		printNoIndent("&overDownToIdle");
		delim = ',';
	}

	/* keyPress */
	if (event > 0x1FF) {
		key = (byte) (event >> 9);
		print("%c", delim);
		parseKeyPressEvent(key);
	}

	printNoIndent("\n");
	printActionBlock(f, length, AB_BUTTONEVENT, event, key);
	print("&end\n");
	--indent;
}

static void parseButton2(FILE *f, unsigned long int length)
{
	unsigned int condition, buttonID, actionOffset;
	unsigned long int lastABLength;

	buttonID = getWord(f);
	/* trackAsMenu */
	fgetc(f);

	actionOffset = getWord(f);
	lastABLength = length - 8 - actionOffset;

	if (actionOffset > 0) {
		printNoIndent("\n");
		print("&defineButton %u\n", buttonID);

		/* skip button data */
		while (actionOffset > 2) {
			fgetc(f);
			--actionOffset;
		}

		while ((actionOffset = getWord(f)) > 0) {
			lastABLength -= actionOffset;
			condition = getWord(f);
			parseButtonEvent(f, condition, actionOffset - 4);
		}

		/* last event */
		condition = getWord(f);
		parseButtonEvent(f, condition, lastABLength);

		print("&end // of defineButton %u\n", buttonID);
	}
	else {
		/* no button events */
		while (lastABLength + 2 > 0) {
			fgetc(f);
			--lastABLength;
		}
	}
	
	/* button end */
	fgetc(f);
}

static int checkEvent(unsigned long int *eventptr, unsigned long int e, char *delimptr, char *str)
{
	if (*eventptr & e) {
		*eventptr -= e;
		printNoIndent("%c%s", *delimptr, str);
		*delimptr = ',';
		return 1;
	}
	else
		return 0;
}

static void parseEvent(FILE *f, unsigned long int event, unsigned long int length)
{
	byte key = 0;
	char delim = ' ';
	unsigned long int event2 = event;
	
	print("\n");
	++indent;
	print("&onClipEvent");

	checkEvent(&event2, eventLoad,			&delim, "&load");
	checkEvent(&event2, eventEnterFrame,	&delim, "&enterFrame");
	checkEvent(&event2, eventUnload,		&delim, "&unload");
	checkEvent(&event2, eventMouseMove,		&delim, "&mouseMove");
	checkEvent(&event2, eventMouseDown,		&delim, "&mouseDown");
	checkEvent(&event2, eventMouseUp,		&delim, "&mouseUp");
	checkEvent(&event2, eventKeyDown,		&delim, "&keyDown");
	checkEvent(&event2, eventKeyUp,			&delim, "&keyUp");
	checkEvent(&event2, eventData,			&delim, "&data");
	checkEvent(&event2, eventInitialize,	&delim, "&initialize");
	checkEvent(&event2, eventConstruct,		&delim, "&construct");
	checkEvent(&event2, eventPress,				&delim, "&press");
	checkEvent(&event2, eventRelease,			&delim, "&release");
	checkEvent(&event2, eventReleaseOutside,	&delim, "&releaseOutside");
	checkEvent(&event2, eventRollOver,			&delim, "&rollOver");
	checkEvent(&event2, eventRollOut,			&delim, "&rollOut");
	checkEvent(&event2, eventDragOver,			&delim, "&dragOver");
	checkEvent(&event2, eventDragOut,			&delim, "&dragOut");

	if (checkEvent(&event2, eventKeyPress, &delim, "")) {
		key = (byte) fgetc(f);
		parseKeyPressEvent(key);
		length--;
		delim = ',';
	}

	if (event2 != 0) {
		printNoIndent("%c%lu // unknown event", delim, event2);
		tellUser(0, "Unknown event: %lu", event2);
	}
	printNoIndent("\n");
	printActionBlock(f, length, AB_MCEVENT, event, key);
	print("&end\n");
	--indent;
}

static void parsePlaceObject2(FILE *f, unsigned long int length)
{
	int i, flags;
	unsigned int clipID = 0, depth;
	unsigned long int curEvent;

	flags = fgetc(f);

	if (flags & splaceOnClipEvents) {
		printNoIndent("\n");

		/* character depth */
		depth = getWord(f);

		/* clipID should always be present */
		if (flags & splaceCharacter)
			print("&placeMovieClip %u ", clipID = getWord(f));
		else {
			print("&placeMovieClip ??? ");
			tellUser(0, "placeMovieClip: clip ID not found");
		}

		if (flags & splaceMatrix)
			skipMatrix(f);
		if (flags & splaceColorTransform)
			skipColorTransform(f);
		if (flags & splaceRatio)
			getWord(f);

		if (flags & splaceName) {
			printNoIndent("&as ");
			printNoIndent("\'");
			while ((i = fgetc(f)) != 0)
				printNoIndent("%c", (char) i);
			printNoIndent("\'");
		}

		if (flags & splaceDefineClip)
			getWord(f);

		printNoIndent("\n");

		/* reserved: always 0 */
		getWord(f);

		if (swfVersion == 5) {
			/* all events */
			getWord(f);
			while ((curEvent = (unsigned long int) getWord(f)) != 0)
				parseEvent(f, curEvent, getDoubleWord(f));
		}
		else if (swfVersion >= 6) {
			/* flash 6 now supports button events for mcs, therefore going long here */
			getDoubleWord(f);

			while ((curEvent = getDoubleWord(f)) != 0)
				parseEvent(f, curEvent, getDoubleWord(f));
		}

		if (flags & splaceCharacter)
			print("&end // of placeMovieClip %u\n", clipID);
		else
			print("&end // of placeMovieClip ???\n");
		
	}
	else {
		/* no events found, skip the rest of placeObject2 */
		skipProtected(f, length - 1);
	}
}

static void parseMovieClip(FILE *f)
{
	unsigned int clipID, frameNum = 0, framesTotal = 0;

	clipID = getWord(f);
	framesTotal = getWord(f);

	printNoIndent("\n");
	print("&defineMovieClip %u // total frames: %u\n", clipID, framesTotal);
	indent++;

	while (!feof(f)) {
		unsigned int type, block;
		unsigned long int length;

		block = getWord(f);
		type = block >> 6;
		length = block & ((1 << 6) - 1);

		if (length == 63)
			length = getDoubleWord(f);

		if (type == 0)
			break;

		switch (type) {
			case TAG_DOACTION:
				printFrameNum(frameNum);
				printActionBlock(f, length, AB_FRAME, frameNum, 0);
				print("&end // of frame %u\n", frameNum);
				break;

			case TAG_PLACEOBJECT2:
				/* possibly onClipEvents inside */
				parsePlaceObject2(f, length);
				break;

			case TAG_SHOWFRAME:
				++frameNum;
				break;

			default:
				if (getTagString(type) == NULL) {
					print("\n");
					print("// unknown tag %lu length %li\n\n", type, length);
				}
				skipProtected(f, length);
		}
	}

	--indent;
	print("&end // of defineMovieClip %u\n", clipID);
}

void disassembleSWF(FILE *f, char *fname, FILE *tac)
{
	unsigned int componentID, frameNum = 0, framesTotal = 0, bits;
	unsigned long int i, size;
	float frameRate, movieWidth, movieHeight;

	outstream = tac;
	swfVersion = fgetc(f);
	size = getDoubleWord(f);

	/* movie bounds */
	InitBits(f);
	bits = getBits(f, 5);
	/* xMin - always 0 */
	getBits(f, bits);
	/* xMax */
	movieWidth = ((float) getBits(f, bits)) / 20;
	/* yMin - always 0 */
	getBits(f, bits);
	/* yMax */
	movieHeight = ((float) getBits(f, bits)) / 20;

	frameRate = ((float) fgetc(f)) / 256;
	frameRate += (float) fgetc(f);

	framesTotal = getWord(f);

	printNoIndent("movie '%s'", fname);

	if (wasCompressed)
		printNoIndent(" &compressed");
	printNoIndent(" // flash %i, total frames: %u, frame rate: ", swfVersion, framesTotal);
	printFloat(frameRate, 1);
	printNoIndent(" fps, ");
	printFloat(movieWidth, 1);
	printNoIndent("x");
	printFloat(movieHeight, 1);
	printNoIndent(" px\n");

	while (!feof(f)) {
		unsigned int type, block;
		unsigned long int length;

		block = getWord(f);
		type = block >> 6;
		length = block & ((1 << 6) - 1);

		if (length == 63)
			length = getDoubleWord(f);

		if (type == 0)
			break;

		switch (type) {
			case TAG_DOACTION:
				printFrameNum(frameNum);
				printActionBlock(f, length, AB_FRAME, frameNum, 0);
				print("&end // of frame %u\n", frameNum);
				break;

			case TAG_INITMOVIECLIP:
				print("\n");
				componentID = getWord(f);
				print("&initMovieClip %i\n", componentID);
				printActionBlock(f, length - 2, AB_INITMC, componentID, 0);
				print("&end // of initMovieClip %i\n", componentID);
				break;

			case TAG_PLACEOBJECT2:
				/* possibly onClipEvents inside */
				parsePlaceObject2(f, length);
				break;

			case TAG_DEFINEBUTTON2:
				/* possibly button events inside */
				parseButton2(f, length);
				break;

			case TAG_SHOWFRAME:
				++frameNum;
				break;

			case TAG_SCRIPTLIMITS: {
				unsigned int recursion = getWord(f);
				unsigned int timeout = getWord(f);
				print("\n");
				print("&scriptLimits recursion %u timeout %u\n", recursion, timeout);
				break;
			}

			case TAG_PROTECT:
				print("\n");
				print("&protect");
				if (length > 0) {
					/* password found */
					printNoIndent(" '");
					/* always 0 - string end */
					getWord(f);
					for (i = 2; i < length - 1; ++i)
						printChar(fgetc(f));
					/* always 0 - string end */
					fgetc(f);
					printNoIndent("\'");
				}
				printNoIndent("\n");
				break;

			case TAG_ENABLEDEBUGGER:
				print("\n");
				print("&enableDebugger");
				if (length > 0) {
					/* password found */
					/* debugger always uses password, even for empty one */
					printNoIndent(" '");
					/* always 0 */
					getWord(f);
					for (i = 2; i < length - 1; ++i)
						printChar(fgetc(f));
					/* always 0 - string end */
					fgetc(f);
					printNoIndent("\'");
				}
				printNoIndent("\n");
				break;

			case TAG_ENABLEDEBUGGER2:
				/* flash MX debugger */
				print("\n");
				print("&enableDebugger2");
				if (length > 0) {
					/* password found */
					/* debugger always uses password, even for empty one */
					printNoIndent(" '");
					/* always 0 */
					getWord(f);
					for (i = 2; i < length - 1; ++i)
						printChar(fgetc(f));
					/* always 0 - string end */
					fgetc(f);
					printNoIndent("\'");
				}
				printNoIndent("\n");
				break;

			case TAG_DEFINEMOVIECLIP:
				parseMovieClip(f);
				break;

			case TAG_EXPORTASSETS: {
				unsigned int assetID, numAssets = getWord(f);
				int n;
				print("\n");
				print("&exportAssets\n");
				++indent;
				while (numAssets--) {
					print("%u &as '", assetID = getWord(f));
					while ((n = fgetc(f)) != 0)
						printChar(n);
					printNoIndent("'\n");
				}
				--indent;
				print("&end // of exportAssets\n");
				break;
			}

			case TAG_IMPORTASSETS: {
				unsigned int assetID, numAssets;
				int n;
				print("\n");
				print("&importAssets &from '");
				while ((n = fgetc(f)) != 0)
					printChar(n);
				printNoIndent("'\n");
				numAssets = getWord(f);
				++indent;
				while (numAssets--) {
					assetID = getWord(f);
					print("'");
					while ((n = fgetc(f)) != 0)
						printChar(n);
					printNoIndent("' &as %u\n", assetID);
				}
				--indent;
				print("&end // of importAssets\n");
				break;
			}

			default:
				if (getTagString(type) == NULL) {
					print("\n");
					print("// unknown tag %lu length %li\n", type, length);
				}
				skipProtected(f, length);
		}
	}

	fclose(f);
	printNoIndent("&end\n");
}
