/*
flasm, command line assembler & disassembler of flash actionscript bytecode
Copyright (c) 2001 Opaque Industries, (c) 2002-2003 Igor Kogan
All rights reserved. See LICENSE.TXT for terms of use.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <io.h>

#if defined(__DJGPP__) || defined(__MINGW32__)
#include <conio.h>
#endif

#include "zlib.h"
#include "util.h"
#include "flasm.h"

extern FILE *yyin;
extern void skipProtected(FILE * f, unsigned long int length);
extern void disassembleSWF(FILE * in, char *fname, FILE *tac);

int swfVersion;

char *inputName;				/* actual command-line parameter */
char outputName[512];
static char *updateName = NULL;	/* swf file name found in disassembly's first line (movie foo.swf...) */
static char *tempName = NULL;	/* temporary file during assembling */
static char *flmName = NULL;	/* temporary disassembly during update */
static char *backupName = NULL;	/* foo.$wf if foo.swf is updated */
static FILE *updateFile = NULL;
static FILE *tempFile = NULL;
static FILE *inputFile = NULL;

static char swfHeader[4];
static long int flength = 0;
static char backupCreated = 0;

char wasCompressed = 0;
char compressAfter = 0;
int mode;
char isRA3 = 0;

/* ini entries */
int showoffset = 0, hexoffset = 0, showregs = 0, showstack = 0, literalregisters = 0, clearregisterargs = 0;
static char *flaplayer = NULL, *flabrowser = NULL, *flatest = NULL;
static char flapath[1000];

void yyerror(const char *s);
void warning(char *s);
int yyparse(void);

static byte *output = NULL;

static void decompressSWF(FILE * f, char *fname);
static void compressSWF(FILE * f, char *fname);

static long int defineMCLengthPos = 0;
static long int buttonLengthPos = 0;
static long int buttonLastOffsetPos = 0;
static long int placeMCLengthPos = 0;
static long int MCAllEventsPos = 0;
static long int len;

static unsigned int nLabels = 0;
struct _label {
	char *name;
	/* offset >=0 if actual label definition, -1 if predefinition from branch */
	long int offset;
};
static struct _label *labels = NULL;

static void waitUserInput(void)
{
#if defined(__DJGPP__) || defined(__MINGW32__)
	/* make sure we have kbhit(), otherwise do nothing */
	fprintf(stderr, "Hit any key to continue..");
	while (!kbhit()) {
#ifdef __DJGPP__
		/*
		   cygwin/mingw don't have pause()
		   it seems also no need for it there,
		   since kbhit() looping doesn't hang the CPU
		   djgpp executables, however, do need it 
		 */
		pause();
#endif
	}
#endif
}

unsigned long int nStrings = 0;
char **aStrings = NULL;

static void mexit(int msg)
{
	unsigned long int i;
	for (i = 0; i < nStrings; ++i)
		free(aStrings[i]);

	if (output != NULL)
		free(output);

	if (aStrings != NULL)
		free(aStrings);

	if (nLabels > 0 && labels != NULL)
		free(labels);

	if (flabrowser != NULL)
		free(flabrowser);

	if (flaplayer != NULL)
		free(flaplayer);

	if (flatest != NULL)
		free(flatest);

	exit(msg);
}

void tellUser(int isError, char *s, ...)
{
	va_list ap;
	FILE *f = isError ? stderr : stdout;
	if (strlen(s) > 0) {
		va_start(ap, s);
		vfprintf(f, s, ap);
		va_end(ap);
		fputc('\n', f);
	}

	if (isError) {
		if (mode != MODE_ASSEMBLE)
			waitUserInput();

		if (tempFile != NULL) {
			fclose(tempFile);
			remove(tempName);
		}

		if (updateFile != NULL)
			fclose(updateFile);

		if (wasCompressed && backupCreated && updateName != NULL && access(backupName, 0) == 0) {
			remove(updateName);
			rename(backupName, updateName);
		}

		mexit(EXIT_FAILURE);
	}
}

char *mstrdup(const char *String)
{
	SUREALLOC(nStrings, aStrings, char *, sizeof (char *));

	if (String == NULL) {
		if ((aStrings[nStrings] = (char*)malloc(256)) == NULL)
			tellUser(1, "Not enough memory to allocate a string");
	}
	else {
		size_t slen = strlen(String);

		if ((aStrings[nStrings] = (char*)malloc(slen + 1)) != NULL)
			memcpy(aStrings[nStrings], String, slen + 1);
		else
			tellUser(1, "Not enough memory to allocate a string");
	}

	return aStrings[nStrings++];
}

static unsigned int newLabel(char *name, long int offset)
{
	unsigned int i = nLabels;

	/* first search if label exists, and update offset if needed */
	if (name != NULL && nLabels>0) {
		do {
			i--;
			if (labels[i].name != NULL && strcmp(name, labels[i].name) == 0) {
				if (offset >= 0) {
					if (labels[i].offset == -1)
						labels[i].offset = offset;
					else
						yyerror("Label defined twice");
				}
				return i;
			}
		} while (i>0);
	}

	SUREALLOC(nLabels, labels, _label, sizeof (struct _label));
	labels[nLabels].name = name;
	labels[nLabels].offset = offset;
	return (nLabels++);
}

void addLabel(char *label)
{
	newLabel(label, len);
}

int branchTarget(char *label)
{
	return writeShort(newLabel(label, -1));
}

int addNumLabel(int numLabel)
{
	/* numerical offset given in a branch */

	if (len + numLabel + 2 < 0)
		yyerror("Branch target out of range");

	return writeShort(newLabel(NULL, len + numLabel + 2));
}

int writeByte(byte num)
{
	if (len % OUTPUT_INC == 0)
		output = (byte *)realloc(output, len + OUTPUT_INC);

	output[len++] = num;
	return 1;
}

int writeShort(unsigned int num)
{
	writeByte(num & 0xff);
	writeByte((num >> 8) & 0xff);

	return 2;
}

int writeFloat(float num)
{
	byte *p = (byte *) &num;

	if (byteorder == FLASM_BIG_ENDIAN) {
		writeByte(p[3]);
		writeByte(p[2]);
		writeByte(p[1]);
		writeByte(p[0]);
	}
	else {
		writeByte(p[0]);
		writeByte(p[1]);
		writeByte(p[2]);
		writeByte(p[3]);
	}

	return 4;
}

int writeDouble(double num)
{
	byte *p = (byte *) &num;

	if (byteorder == FLASM_BIG_ENDIAN) {
		writeByte(p[3]);
		writeByte(p[2]);
		writeByte(p[1]);
		writeByte(p[0]);
		writeByte(p[7]);
		writeByte(p[6]);
		writeByte(p[5]);
		writeByte(p[4]);
	}
	else {
		writeByte(p[4]);
		writeByte(p[5]);
		writeByte(p[6]);
		writeByte(p[7]);
		writeByte(p[0]);
		writeByte(p[1]);
		writeByte(p[2]);
		writeByte(p[3]);
	}

	return 8;
}

int writeLongInt(long int num)
{
	byte *p = (byte *) &num;

	if (byteorder == FLASM_BIG_ENDIAN) {
		writeByte(p[3]);
		writeByte(p[2]);
		writeByte(p[1]);
		writeByte(p[0]);
	}
	else {
		writeByte(p[0]);
		writeByte(p[1]);
		writeByte(p[2]);
		writeByte(p[3]);
	}

	return 4;
}

int writeString(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; ++i)
		writeByte((byte) str[i]);

	writeByte(0);

	return i + 1;
}

unsigned int nConstants = 0;
static char *constants[MAX_CONSTANTS];

void addConstant(char *str)
{
	constants[nConstants] = str;
	++nConstants;

	if (nConstants > MAX_CONSTANTS)
		yyerror("Too many constants");
}

unsigned int writeConstants(void)
{
	unsigned int i;
	unsigned long int clen = 2;

	writeByte(SWFACTION_CONSTANTPOOL);
	/* length */
	writeShort(0);
	writeShort(nConstants);

	for (i = 0; i < nConstants; ++i)
		clen += writeString(constants[i]);

	if (clen < 65533)
		patchLength((unsigned int) clen, (unsigned int) clen);
	else
		tellUser(1, "Constant pool exceeds 64k");

	return (unsigned int) clen + 3;
}

unsigned int writePushString(char *str)
{
	unsigned int i;

	for (i = 0; i < nConstants; ++i) {
		if (strcmp(constants[i], str) == 0)
			break;
	}

	if (i < nConstants) {
		if (i < 256) {
			/* constant, 1-byte reference */
			writeByte(0x08);
			writeByte((byte) i);
			return 2;
		}
		else {
			/* constant, 2-byte reference */
			writeByte(0x09);
			writeShort(i);
			return 3;
		}
	}

	/* string */
	writeByte(0);
	return writeString(str) + 1;
}

int isConstant(unsigned int number, const char *name)
{
	int result = 0;
	if (number < nConstants)
	{
		result = stricmp(constants[number], name) == 0;
	}
	return result;
}

int writePushStringOpcodes(char *name, int opcode1, int opcode2, int *actions)
{
	int result;
	if (!stricmp(name, "this"))
	{
		if (opcode2 == SWFACTION_GETVARIABLE)
		{
			result = writeByte(SWFACTION_PUSHTHISVARIABLE);
			--*actions;
		} else {
			result = writeByte(SWFACTION_PUSHTHIS);
			if (opcode2 >= SWFACTION_END)
			{
				result += writeByte(opcode2);
			}
		}
		return result;
	}
	if (!stricmp(name, "_global"))
	{
		if (opcode2 == SWFACTION_GETVARIABLE)
		{
			result = writeByte(SWFACTION_PUSHGLOBALVARIABLE);
			--*actions;
		} else {
			result = writeByte(SWFACTION_PUSHGLOBAL);
			if (opcode2 >= SWFACTION_END)
			{
				result += writeByte(opcode2);
			}
		}
		return result;
	}
	if (!stricmp(name, "NULL"))
	{
		result = writeByte(SWFACTION_PUSHNULL);
		if (opcode2 >= SWFACTION_END)
		{
			result += writeByte(opcode2);
		}
		return result;
	}
	if (!stricmp(name, "UNDEF"))
	{
		result = writeByte(SWFACTION_PUSHUNDEFINED);
		if (opcode2 >= SWFACTION_END)
		{
			result += writeByte(opcode2);
		}
		return result;
	}
	int len = strlen(name) + 1;
	writeByte(opcode1);
	writeShort(len);
	writeString(name);
	if (opcode1 != SWFACTION_PUSHSTRING)
	{
		--*actions;
	}
	return len + 3;
}

int writePushStringDictOpcodes(char *name, int opcode1, int opcode2, int opcode3)
{
	if (!stricmp(name, "this")) {
		return writeByte(SWFACTION_PUSHTHIS);
	}
	if (!stricmp(name, "_global")) {
		return writeByte(SWFACTION_PUSHGLOBAL);
	}
	if (!stricmp(name, "UNDEF")) {
		return writeByte(SWFACTION_PUSHUNDEFINED);
	}

	unsigned int i;
	for (i = 0; i < nConstants; ++i) {
		if (strcmp(constants[i], name) == 0) {
			break;
		}
	}

	if (i < nConstants) {
		if (i < 256) {
			writeByte(opcode1);
			writeByte(1);
			writeByte(0);
			writeByte(i);
			return 4;
		} else {
			writeByte(opcode2);
			writeByte(2);
			writeByte(0);
			writeShort(i);
			return 5;
		}
	}

	if (!stricmp(name, "this")) {
		int size = writeByte(SWFACTION_PUSHTHIS);
		return size + writeByte(SWFACTION_PUSHSTRING);
	}

	if (!stricmp(name, "_global")) {
		int size = writeByte(SWFACTION_PUSHGLOBAL);
		return size + writeByte(SWFACTION_PUSHSTRING);
	}

	if (!stricmp(name, "NULL")) {
		int size = writeByte(SWFACTION_PUSHNULL);
		return size + writeByte(SWFACTION_PUSHSTRING);
	}

	if (!stricmp(name, "UNDEF")) {
		int size = writeByte(SWFACTION_PUSHUNDEFINED);
		return size + writeByte(SWFACTION_PUSHSTRING);
	}

	unsigned int len = strlen(name) + 1;
	writeByte(opcode3);
	writeShort(len);
	writeString(name);
	return len + 3;
}

static void patchTargets(void)
{
	long int i = 0;

	while (i < len) {
		Action op = (Action) output[i++];
		if (op & 0x80) {
			unsigned int blocklen = S16(output + i);
			i += 2;

			if (op == SWFACTION_BRANCHALWAYS || op == SWFACTION_BRANCHIFTRUE || op == SWFACTION_BRANCHIFFALSE) {
				long int offset;
				unsigned int target = S16(output+i);

				if (labels[target].offset < 0) {
					char msg[256] = "Label not found: ";
					yyerror(strcat(msg, labels[target].name));
				}

				offset = labels[target].offset - (i + 2);
				if (offset > 32767 || offset < -32768) {
					char msg[256] = "Label too far away from branch: ";
					yyerror(strcat(msg, labels[target].name));
				}

				output[i] = (byte) (offset & 0xff);
				output[i+1] = (byte) ((offset >> 8) & 0xff);
			}
			i += blocklen;	
		}
	}
}


static int flput(char b)
{
	++flength;
	return fputc(b, tempFile);
}

static void flputShort(unsigned int w)
{
	fputc(0xff & w, tempFile);
	fputc(0xff & (w >> 8), tempFile);
	flength += 2;
}

static void flputLong(unsigned long int l)
{
	fputc(0xff & l, tempFile);
	fputc(0xff & (l >> 8), tempFile);
	fputc(0xff & (l >> 16), tempFile);
	fputc(0xff & (l >> 24), tempFile);
	flength += 4;
}

static void flputString(char *s)
{
	fwrite(s, strlen(s)+1, 1, tempFile);
	flength += strlen(s)+1;
}

static int dupByte(void)
{
	return flput(fgetc(updateFile));
}

static unsigned int dupWord(void)
{
	int b1, b2;
	b1 = fgetc(updateFile);
	flput(b1);
	b2 = fgetc(updateFile);
	flput(b2);
	return ((unsigned int) b1 + ((unsigned int) b2 << 8));
}

static unsigned long int dupLong(void)
{
	return ((unsigned long int) dupWord() + ((unsigned long int) dupWord() << 16));
}

static void dupBuffered(unsigned long int length)
{
	static byte dupBuffer[MAX_BUFFER];

	flength += length;

	while (length > MAX_BUFFER) {
		if (fread(dupBuffer, 1, MAX_BUFFER, updateFile) == MAX_BUFFER) {
			fwrite(dupBuffer, 1, MAX_BUFFER, tempFile);
			length -= MAX_BUFFER;
		}
		else
			yyerror("Couldn't update because of unexpected swf structure");
	}

	if (length > 0) {
		if (fread(dupBuffer, 1, length, updateFile) == length)
			fwrite(dupBuffer, 1, length, tempFile);
		else
			yyerror("Couldn't update because of unexpected swf structure");
	}
}

void patchLength(unsigned int back, unsigned int blen)
{
	output[len - back - 1] = (blen >> 8) & 0xff;
	output[len - back - 2] = blen & 0xff;
}

void patchFlag(unsigned int back, byte flag)
{
	output[len - back - 1] = flag;
}

void patchFrameLoaded(unsigned int back, int numActions)
{
	if (numActions > 0 || numActions < 256)
		output[len - back - 1] = (byte) numActions;
	else
		yyerror("IfFrameLoaded block larger then 255 bytes is not allowed");
}

static void updateTmpLength(long int lenpos, long int reallen)
{
	long int curpos;
	curpos = ftell(tempFile);

	fseek(tempFile, lenpos, SEEK_SET);

	/* update long length */
	/* dont use flput to not affect the file size calculation */
	fputc((reallen & 0xff), tempFile);
	fputc((reallen >> 8) & 0xff, tempFile);
	fputc((reallen >> 16) & 0xff, tempFile);
	fputc((reallen >> 24) & 0xff, tempFile);

	fseek(tempFile, curpos, SEEK_SET);
}

static void updateShort(long int lenpos, unsigned int reallen)
{
	long int curpos = ftell(tempFile);

	fseek(tempFile, lenpos, SEEK_SET);

	/* update short length */
	/* dont use flput to not affect the file size calculation */
	fputc(reallen & 0xff, tempFile);
	fputc((reallen >> 8) & 0xff, tempFile);

	fseek(tempFile, curpos, SEEK_SET);
}

static void flushOutput(void)
{
	patchTargets();

	if (fwrite(output, 1, (size_t) len, tempFile) != (size_t) len)
		tellUser(1, "Error writing action block");

	flength += len;

	len = 0;

	if (nLabels > 0) {
		nLabels = 0;
		free(labels);
		labels = NULL;
	}

	nConstants = 0;
}

static void writeTagHeader(unsigned int type, unsigned long int length)
{
	if (length >= 63 || type == TAG_DEFINEBITSLOSSLESS || type == TAG_DEFINEBITSLOSSLESS2 || type == TAG_SOUNDSTREAMBLOCK) {
		/*
		   long length, and also workaround for a really strange bug in flash player:
		   the above tags must always have long length to work
		 */
		flputShort((type << 6) + 63);
		flputLong(length);
	}
	else {
		/* short length */
		flputShort((type << 6) + length);
	}
}

static unsigned long int findNextBlock(unsigned int typeneeded)
{
	/*
	   dumps all blocks of the updateFile to the tempFile
	   until required block found, returns its length 
	 */

	while (!feof(updateFile)) {
		unsigned int type, tagHeader;
		unsigned long int length;

		tagHeader = getWord(updateFile);
		type = tagHeader >> 6;

		length = tagHeader & ((1 << 6) - 1);

		if (length == 63)
			length = getDoubleWord(updateFile);

		if (type == typeneeded)
			return length;

		if (type == TAG_PROTECT || type == TAG_ENABLEDEBUGGER || type == TAG_ENABLEDEBUGGER2 ||	type == TAG_SCRIPTLIMITS) {
			/* skip tags flasm itself handles */
			skipProtected(updateFile, length);
		}
		else {
			/* dump others */
			writeTagHeader(type, length);
			dupBuffered(length);
		}
	}
	tellUser(1, "Couldn't update because of unexpected swf structure:\nunexpected end of SWF looking for Tag %04x", typeneeded);
	return (0);
}

void writeDoAction()
{
	unsigned long int oldLength = findNextBlock(TAG_DOACTION);

	/* skip old action  */
	skipProtected(updateFile, oldLength);

	writeTagHeader(TAG_DOACTION, len);

	/* write bison output from buffer to file and empty buffer */
	flushOutput();
}

void writeInitMC(unsigned int clipID)
{
	unsigned int oldID;
	unsigned long int oldLength = findNextBlock(TAG_INITMOVIECLIP);

	writeTagHeader(TAG_INITMOVIECLIP, len + 2);

	oldID = dupWord();
	if (oldID != clipID)
		tellUser(1, "Couldn't update because of unexpected swf structure:\nold initMovieClip ID %u doesn't match new ID %u", oldID, clipID);

	skipProtected(updateFile, oldLength - 2);

	flushOutput();
}

static unsigned int bitPos;
static unsigned int bitBuf;

static unsigned int dupBits(unsigned int n)
{
	unsigned long int v = 0;

	while (n > bitPos) {
		n -= bitPos;
		v |= bitBuf << n;
		bitBuf = (unsigned int) dupByte();
		bitPos = 8;
	}

	bitPos -= n;
	v |= bitBuf >> bitPos;
	bitBuf &= 0xff >> (8 - bitPos);
	/* never need more than 16 bits */
	return (unsigned int) v;
}

static void dupMatrix(void)
{
	bitPos = 8;
	bitBuf = (unsigned int) dupByte();

	if (dupBits(1))
		dupBits(dupBits(5) * 2);
	if (dupBits(1))
		dupBits(dupBits(5) * 2);
	dupBits(dupBits(5) * 2);
}

static void dupColorTransform(void)
{
	unsigned int needAdd, needMul, nBits;

	bitPos = 8;
	bitBuf = (unsigned int) dupByte();

	needAdd = dupBits(1);
	needMul = dupBits(1);
	nBits = dupBits(4);
	if (needMul)
		dupBits(nBits * 4);
	if (needAdd)
		dupBits(nBits * 4);
}

void writePlaceMCStart(unsigned int clipID)
{
	unsigned int oldID = 0;
	int flags, i;
	unsigned long int length, curEvent, eventLength;

	/* skip all mcs without onClipEvent actions */
	do {
		length = findNextBlock(TAG_PLACEOBJECT2);
		flags = fgetc(updateFile);

		if (flags & splaceOnClipEvents)
			break;

		writeTagHeader(TAG_PLACEOBJECT2, length);
		flput(flags);

		/* copy the rest of the placeobject2 */
		dupBuffered(length - 1);
	} while (1);

	/* placemc header, temporary long length, save length pos */
	writeTagHeader(TAG_PLACEOBJECT2, 0xFF);
	placeMCLengthPos = ftell(tempFile) - 4;

	flput(flags);

	/* character depth */
	dupWord();

	if (flags & splaceCharacter)
		oldID = dupWord();
	else
		tellUser(1, "Couldn't update because of unexpected swf structure:\nold placeMovieClip ID missing, new ID %u", clipID);

	if (oldID != clipID)
		tellUser(1, "Couldn't update because of unexpected swf structure:\nold placeMovieClip ID %u doesn't match new ID %u", oldID, clipID);

	if (flags & splaceMatrix)
		dupMatrix();
	if (flags & splaceColorTransform)
		dupColorTransform();
	if (flags & splaceRatio)
		dupWord();
	if (flags & splaceName)
		while ((i = dupByte()) != 0);
	if (flags & splaceDefineClip)
		dupWord();

	/* reserved: always 0 */
	dupWord();

	/* save the pos for logical or of all events */
	MCAllEventsPos = ftell(tempFile);

	/* skip old events */
	if (swfVersion == 5) {
		/* dup logical or of all events - temporary */
		dupWord();
		while (getWord(updateFile) > 0) {
			eventLength = getDoubleWord(updateFile);
			skipProtected(updateFile, eventLength);
		}
	}
	else if (swfVersion >= 6) {
		/* dup logical or of all events - temporary */
		dupLong();
		while ((curEvent = getDoubleWord(updateFile)) != 0) {
			eventLength = getDoubleWord(updateFile);
			skipProtected(updateFile, eventLength);
		}
	}
}

void writePlaceMCEnd(unsigned long int flags)
{
	/* write empty event */
	flputShort(0);
	if (swfVersion >= 6)
		flputShort(0);

	updateTmpLength(placeMCLengthPos, ftell(tempFile) - placeMCLengthPos - 4);

	if (swfVersion == 5)
		updateShort(MCAllEventsPos, (unsigned int) flags);
	else if (swfVersion >= 6) {
		updateShort(MCAllEventsPos, (unsigned int) (flags & 0xFFFF));
		updateShort(MCAllEventsPos + 2, (unsigned int) ((flags >> 16) & 0xFFFF));
	}

	placeMCLengthPos = 0;
	MCAllEventsPos = 0;
}

void writeOnClipEvent(unsigned long int flag)
{
	/* write event flag */
	flputShort(flag);
	if (swfVersion >= 6)
		flputShort((unsigned int) (flag >> 16));

	/* write action length */
	flputLong(len);

	flushOutput();
}

void writeButtonStart(unsigned int buttonID)
{
	int trackAsMenu;
	unsigned int oldID, actionOffset;
	unsigned long int length;

	/* skip all buttons without actions */
	do {
		length = findNextBlock(TAG_DEFINEBUTTON2);
		oldID = getWord(updateFile);
		trackAsMenu = fgetc(updateFile);
		actionOffset = getWord(updateFile);

		if (actionOffset > 0)
			break;

		writeTagHeader(TAG_DEFINEBUTTON2, length);
		flputShort(oldID);
		flput(trackAsMenu);
		/* put action offset = 0 */
		flputShort(0);
		/* copy the rest of the button */
		dupBuffered(length - 5);
	} while(1);

	if (oldID != buttonID)
		tellUser(1, "Couldn't update because of unexpected swf structure:\nold defineButton ID %u doesn't match new ID %u", oldID, buttonID);

	/* defineButton2 header, temporary long length, save length pos */
	writeTagHeader(TAG_DEFINEBUTTON2, 0xFF);
	buttonLengthPos = ftell(tempFile) - 4;

	flputShort(oldID);
	flput(trackAsMenu);
	flputShort(actionOffset);

	/* copy button visual part */
	dupBuffered(actionOffset - 2);

	/* skip old button actions part */
	skipProtected(updateFile, length - 3 - actionOffset);
}

void writeButtonEnd(void)
{
	updateTmpLength(buttonLengthPos, ftell(tempFile) - buttonLengthPos - 4);

	/* last offset is always 0 */
	updateShort(buttonLastOffsetPos, 0);

	buttonLengthPos = 0;
	buttonLastOffsetPos = 0;
}

void writeButtonEvent(unsigned int flags)
{
	/* write offset to the next condition */
	buttonLastOffsetPos = ftell(tempFile);
	flputShort(len+4);

	/* write button event flags */
	flputShort(flags);
	flushOutput();
}

void writeDefineMCStart(unsigned int clipID)
{
	unsigned int oldID;

	findNextBlock(TAG_DEFINEMOVIECLIP);

	/* defineMovieClip header, temporary long length, save length pos */
	writeTagHeader(TAG_DEFINEMOVIECLIP, 0xFF);
	defineMCLengthPos = ftell(tempFile) - 4;

	oldID = dupWord();
	if (oldID != clipID)
		tellUser(1, "Couldn't update because of unexpected swf structure:\nold defineMovieClip ID %u doesn't match new ID %u", oldID, clipID);
	
	/* frames total */
	dupWord();
}

void writeDefineMCEnd(void)
{
	/* dump the rest of movie clip */
	findNextBlock(TAG_END);

	/* write movie clip end tag */
	flputShort(0);

	updateTmpLength(defineMCLengthPos, ftell(tempFile) - defineMCLengthPos - 4);

	defineMCLengthPos = 0;
}

void writeProtect(char *str)
{
	if (strlen(str) == 0) {
		/* no password */
		writeTagHeader(TAG_PROTECT, 0);
	}
	else {
		/* password found */
		writeTagHeader(TAG_PROTECT, strlen(str) + 3);
		flputShort(0);
		flputString(str);
	}
}

void writeScriptLimits(unsigned int recursion, unsigned int timeout)
{
	writeTagHeader(TAG_SCRIPTLIMITS, 4);
	flputShort(recursion);
	flputShort(timeout);
}

void writeEnableDebugger(char *str)
{
	if (strlen(str) == 0) {
		/* no password, probably impossible? */
		writeTagHeader(TAG_ENABLEDEBUGGER, 0);
	}
	else {
		/* password found */
		writeTagHeader(TAG_ENABLEDEBUGGER, strlen(str) + 3);
		flputShort(0);
		flputString(str);
	}
}

void writeEnableDebugger2(char *str)
{
	if (strlen(str) == 0) {
		/* no password, probably impossible? */
		writeTagHeader(TAG_ENABLEDEBUGGER2, 0);
	}
	else {
		/* password found */
		writeTagHeader(TAG_ENABLEDEBUGGER2, strlen(str) + 3);
		flputShort(0);
		flputString(str);
	}
}

void writeImportAssets(char *from, unsigned int numAssets)
{
	if (numAssets>0) {
		skipProtected(updateFile, findNextBlock(TAG_IMPORTASSETS));
		writeTagHeader(TAG_IMPORTASSETS, len + strlen(from)+3);
		flputString(from);
		flputShort(numAssets);

		if (fwrite(output, 1, (size_t) len, tempFile) != (size_t) len)
			tellUser(1, "Error writing importAssets");

		flength += len;
	}
	len = 0;
}

void writeExportAssets(unsigned int numAssets)
{
	if (numAssets>0) {
		skipProtected(updateFile, findNextBlock(TAG_EXPORTASSETS));
		writeTagHeader(TAG_EXPORTASSETS, len+2);
		flputShort(numAssets);

		if (fwrite(output, 1, (size_t) len, tempFile) != (size_t) len)
			tellUser(1, "Error writing exportAssets");

		flength += len;
	}
	len = 0;
}

static void finalizeTemporaryFile(char *name)
{
	fclose(updateFile);
	fclose(tempFile);
	remove(name);
	rename(tempName, name);
#if 0
	if (!backupCreated) {
		backupName = mstrdup(name);
		backupCreated = 1;
		strcpy(backupName + strlen(backupName) - 4, ".$wf");
		/* remove evtl. existing previous backup foo.$wf */
		remove(backupName);
		/* foo.swf -> foo.$wf */
		if (rename(name, backupName) != 0)
			tellUser(1, "couldn't update: file %s is in use", name);
		/* foo.tmp (assemble) or flasm.tmp (compress/decompress) -> foo.swf */
		rename(tempName, name);
	}
	else {
		/* backup already here, just make temp file our final file */
		if (remove(name) != 0)
			tellUser(1, "couldn't update: file %s is in use", name);
		rename(tempName, name);
	}
#endif
}

static void getSWFHeader(FILE * f)
{
	fread(swfHeader, 1, 3, f);
	swfHeader[3] = '\0';
}

void finishUpdate(void)
{
	/* dump the rest of swf */
	findNextBlock(0);
	/* write movie end */
	flputShort(0);

	updateTmpLength(4, flength);

	fclose(updateFile);

	finalizeTemporaryFile(updateName);

	if (compressAfter) {
		updateFile = fopen(updateName, "rb");
		getSWFHeader(updateFile);
		compressSWF(updateFile, updateName);
	}

	if (mode == MODE_UPDATE)
		tellUser(0, "%s successfully updated, %li bytes", updateName, flength);
	else if (mode == MODE_ASSEMBLE)
		tellUser(0, "aTack Msg: %s decompiled\naTack Msg: %s assembled", inputName, updateName);
}

void startUpdate(char *outputName)
{
	int b, i, bitstotal;

	if ((updateFile = fopen(outputName, "rb")) == NULL)
		tellUser(1, "Couldn't open file %s for update", outputName);

	getSWFHeader(updateFile);

	if (strcmp(swfHeader, "FWS") != 0) {
		if (strcmp(swfHeader, "CWS") == 0) {
			/* decompresses foo.swf, foo.$wf backup is created */
			decompressSWF(updateFile, outputName);
			updateFile = fopen(outputName, "rb");
			/* now we are just after the header in decompressed file */
			getSWFHeader(updateFile);
		}
		else
			tellUser(1, "Input file %s doesn't appear to be an SWF file", outputName);
	}

	flength = 0;

	updateName = mstrdup(outputName);
	tempName = mstrdup(outputName);
	strcpy(tempName + strlen(tempName) - 4, ".tmp");

	if ((tempFile = fopen(tempName, "wb")) == NULL)
		tellUser(1, "Couldn't create temporary file");

	/* swf header */
	flput('F');
	flput('W');
	flput('S');

	/* version */
	flput(swfVersion = fgetc(updateFile));

	/* file length - temporary! */
	flput(fgetc(updateFile));
	flput(fgetc(updateFile));
	flput(fgetc(updateFile));
	flput(fgetc(updateFile));

	/* movie bounds */
	b = fgetc(updateFile);
	bitstotal = 5 + 4 * ((b & 0xf8) >> 3);
	flput(b);
	for (i = 0; i < (bitstotal + 7) / 8 - 1; ++i)
		flput(fgetc(updateFile));

	/* frame rate and # of frames */
	flput(fgetc(updateFile));
	flput(fgetc(updateFile));
	flput(fgetc(updateFile));
	flput(fgetc(updateFile));
}

static void createTemporaryFile(void)
{
	tempName = mstrdup("flasm.tmp");
	if ((tempFile = fopen(tempName, "wb+")) == NULL)
		tellUser(1, "Couldn't create file: %s", tempName);
}

static void decompressSWF(FILE * f, char *fname)
{
	z_stream stream;
	static byte inputBuffer[MAX_BUFFER], outputBuffer[MAX_BUFFER];
	int status, count;

	flength = 0;
	createTemporaryFile();

	/* swf header */
	flput('F');
	flput('W');
	flput('S');

	/* version */
	flput(fgetc(f));

	flput(fgetc(f));
	flput(fgetc(f));
	flput(fgetc(f));
	flput(fgetc(f));

	stream.avail_in = 0;
	stream.next_in = inputBuffer;
	stream.next_out = outputBuffer;
	stream.zalloc = (alloc_func) NULL;
	stream.zfree = (free_func) NULL;
	stream.opaque = (voidpf) 0;
	stream.avail_out = MAX_BUFFER;

	status = inflateInit(&stream);
	if (status != Z_OK)
		tellUser(1, "Zlib error: %s\n", stream.msg);

	do {
		if (stream.avail_in == 0) {
			stream.next_in = inputBuffer;
			stream.avail_in = fread(inputBuffer, 1, MAX_BUFFER, f);
		}

		if (stream.avail_in == 0)
			break;

		status = inflate(&stream, Z_SYNC_FLUSH);

		count = MAX_BUFFER - stream.avail_out;
		if (count) {
			fwrite(outputBuffer, 1, count, tempFile);
			flength += count;
		}

		stream.next_out = outputBuffer;
		stream.avail_out = MAX_BUFFER;
	}
	while (status == Z_OK);

	if (status != Z_STREAM_END)
		tellUser(1, "Zlib error: %s\n", stream.msg);

	inflateEnd(&stream);

	fclose(f);

	if (mode != MODE_DISASSEMBLE)
		finalizeTemporaryFile(fname);

	if (mode == MODE_DECOMPRESS)
		tellUser(0, "%s successfully decompressed, %li bytes", fname, flength);

	wasCompressed = 1;
}

static void compressSWF(FILE * f, char *fname)
{
	z_stream stream;
	static byte inputBuffer[MAX_BUFFER], outputBuffer[MAX_BUFFER];
	int status, count;

	flength = 0;
	createTemporaryFile();

	/* swf header  */
	flput('C');
	flput('W');
	flput('S');

	/* version */
	flput(fgetc(f));

	flput(fgetc(f));
	flput(fgetc(f));
	flput(fgetc(f));
	flput(fgetc(f));

	stream.avail_in = 0;
	stream.next_out = outputBuffer;
	stream.avail_out = MAX_BUFFER;
	stream.zalloc = (alloc_func) NULL;
	stream.zfree = (free_func) NULL;
	stream.opaque = (voidpf) 0;
	stream.next_in = inputBuffer;

	status = deflateInit(&stream, Z_BEST_COMPRESSION);

	if (status != Z_OK)
		tellUser(1, "Zlib error: %s\n", stream.msg);

	while (1) {
		if (stream.avail_in == 0) {
			stream.next_in = inputBuffer;
			stream.avail_in = fread(inputBuffer, 1, MAX_BUFFER, f);
		}

		if (stream.avail_in == 0)
			break;

		status = deflate(&stream, Z_NO_FLUSH);
		if (status != Z_OK)
			tellUser(1, "Zlib error: %s\n", stream.msg);

		count = MAX_BUFFER - stream.avail_out;
		if (count) {
			fwrite(outputBuffer, 1, count, tempFile);
			flength += count;
		}

		stream.next_out = outputBuffer;
		stream.avail_out = MAX_BUFFER;
	}

	stream.next_out = outputBuffer;
	stream.avail_out = MAX_BUFFER;

	do {
		status = deflate(&stream, Z_FINISH);

		count = MAX_BUFFER - stream.avail_out;
		if (count) {
			fwrite(outputBuffer, 1, count, tempFile);
			flength += count;
		}

		stream.next_out = outputBuffer;
		stream.avail_out = MAX_BUFFER;
	}
	while (status == Z_OK);

	if (status != Z_STREAM_END)
		tellUser(1, "Zlib error: %s\n", stream.msg);

	status = deflateEnd(&stream);
	if (status != Z_OK)
		tellUser(1, "Zlib error: %d\n", stream.msg);

	fclose(f);

	finalizeTemporaryFile(fname);

	if (mode == MODE_COMPRESS)
		tellUser(0, "%s successfully compressed, %li bytes", fname, flength);

}

extern int yydebug;

static void usage(void)
{
	puts("");
	printf("flasm %s build %s\n", FLASM_VERSION, __DATE__);
	puts("");
	puts("Usage: flasm infile outfile --ra3");
	puts("");
	puts("infile is the name of the input file");
	puts("outfile is the name of the output file");
	puts("pass --ra3 if you are exporting for RA3 rather than C&C3");
	puts("");

	mexit(EXIT_FAILURE);
}

static void unescapePath(char *argument)
{
	int n = 0;
	char esc[3];
	char *s = argument;

	inputName = mstrdup(NULL);

	while ((inputName[n] = *s++) != 0) {
		if ((inputName[n] == '.') && (*s == 'h') && (*(s + 1) == 't') && (*(s + 2) == 'm'))
			/* extension found */
			break;

		if (inputName[n] == '%') {
			/* unescape URL encoded char */
			esc[0] = *s++;
			esc[1] = *s++;
			esc[2] = 0;

			inputName[n] = (char) (xtoi(esc));
		}
		n++;
	}

	inputName[n] = '\0';
	strcat(inputName, ".swf");
}

static int readINI(char *flasmpath, char *names, char *types, ...)
{
	/* slightly changed INITVARS from SNIPPETS collection, public domain by Raymond Gardner, Sept. 1991 */
	FILE *iniFile;
	int pathlen = strlen(flasmpath);
	char *inipath;
	char ln[256];
	char *p, *inipathptr;
	va_list arglist;
	char *namep, *typep, name[40], *e;
	void *argp;
	int k;

	inipath = new char[pathlen + 10];

	strcpy(inipath, flasmpath);
	inipathptr = inipath + pathlen;
	while (*inipathptr != '\\' && *inipathptr != '/' && *inipathptr != ':' && inipathptr>=inipath)
		inipathptr--;

	strcpy(inipathptr + 1, "flasm.ini");
	/* tellUser(0, "ini is here: %s", inipath); */
	if ((iniFile = fopen(inipath, "r")) == NULL) {
		delete [] inipath;
		return -1;
	}

	while (fgets(ln, 256, iniFile)) {													 /* read ini file */
		while (isspace(ln[0]))															 /* drop leading whitespace */
			memmove(ln, ln + 1, strlen(ln));
		if (ln[0] == '\0' || ln[0] == '#')												 /* skip if blank line or comment */
			continue;

		p = strchr(ln, '=');															 /* find equal sign */
		if (p == NULL)																	 /* error if none */
			tellUser(1, "Error parsing flasm.ini: %s", ln);

		while (p > ln && isspace(p[-1])) {												 /* remove whitespace before eq sign */
			memmove(p - 1, p, strlen(p - 1));
			--p;
		}
		*p++ = '\0';																	 /* plug EOS over eq sign */

		while (isspace(p[0]))															 /* remove leading space on init string */
			memmove(p, p + 1, strlen(p));

		k = strlen(p) - 1;																 /* init string length */
		if (k < 0)
			tellUser(1, "Error parsing flasm.ini: %s", ln);

		if (p[k] == '\n')
			p[k] = '\0';																 /* plug EOS over newline */
		else if (feof(iniFile))															 /* '\n' is missing - last line or buffer exceeded? */
			p[k + 1] = '\0';
		else
			tellUser(1, "Line too long in flasm.ini: %s", ln);

		va_start(arglist, types);														 /* setup for arglist search */

		namep = names;																	 /* init ptr to var names */
		typep = types;																	 /* init ptr to var types */

		while (*namep == ' ')															 /* skip blanks before namelist */
			++namep;

		while (*typep) {																 /* while any typelist items left... */
			argp = (void *) va_arg(arglist, void *);									 /* get var arg */

			k = strcspn(namep, " ");													 /* length of namelist entry */
			memmove(name, namep, k);													 /* put into name hold area */
			name[k] = '\0';																 /* terminate it */
			if (strIcmp(name, ln) != 0) {												 /* if it doesn't match... */
				namep += k;																 /* get next name */
				while (*namep == ' ')
					++namep;
				++typep;																 /* get next type */
			}
			else {																		 /* else name is found... */
				if (*typep == 'i') {													 /* if it's an int, init it */
					*(int *) argp = atoi(p);
				}
				else if (*typep == 's' || *typep == 'p') {
					if (*p == '"') {													 /* is string in quotes? */
						++p;															 /* skip leading quote, and */
						e = strchr(p, '"');												 /* look for trailing quote */
						if (e)															 /* terminate string if found */
							*e = '\0';
					}
					if (*typep == 'p') {												 /* if it's a char *ptr */
						e = (char *)malloc(strlen(p) + 1);										 /* get space */
						if (e == 0)
							tellUser(1, "Not enough memory to read flasm.ini");
						*(char **) argp = e;
						strcpy(*(char **) argp, p);										 /* copy in string */
					}
					else																 /* must be char array */
						strcpy((char*)argp, p);												 /* copy in string */
				}
				else
					tellUser(1, "Contact developer: bad argument type in readINI() call");

				break;																	 /* break search; get next line */
			}
		}
		va_end(arglist);
	}

	fclose(iniFile);
	delete [] inipath;

	return 0;
}

static void parseArgs(int argc, char *argv[])
{
	int ini;

	if (argc == 4 && !stricmp(argv[3], "--ra3") && argv[1] != NULL) {
		isRA3 = true;
	}
	else if (argc != 3 || argv[1] == NULL) {
		usage();
		return;
	}

	ini = readINI(argv[0],
			"flabrowser flaplayer flatest showoffset hexoffset showregs showstack literalregisters clearregisterargs",
			"pppiiiiii",
			&flabrowser, &flaplayer, &flatest, &showoffset, &hexoffset, &showregs, &showstack, &literalregisters, &clearregisterargs);

	/* tellUser(0, "showoffset = %i; hexoffset = %i; literalregisters = %i, clearregisterargs = %i", showoffset, hexoffset, literalregisters, clearregisterargs); */
	if ((strstr(argv[1], ".htm") != NULL) || (strstr(argv[1], "http://") != NULL)) {
		mode = MODE_IDE;

		if (ini != 0)
			tellUser(1, "flasm.ini not found in flasm's directory");

		if ((strIstr(argv[1], "ContextHelp") != NULL) || (strIstr(argv[1], "http://") != NULL)) {
			/* an attempt to access flash help */
			mode = MODE_FLASH_HELP;

			if (strlen(flabrowser) == 0)
				tellUser(1, "You must define 'flabrowser' value in flasm.ini to access flash help");

			if (access(flabrowser, 1) != 0)
				tellUser(1, "Couldn't start browser: %s", flabrowser);

			strcpy(flapath, flabrowser);
			strcat(flapath, " ");
			strcat(flapath, argv[1]);
			return;
		}

		if (strIstr(flatest, "FLAPLAYER") != NULL)
			strcpy(flapath, flaplayer);
		else if (strIstr(flatest, "FLABROWSER") != NULL)
			strcpy(flapath, flabrowser);
		else
			tellUser(1, "Invalid or missing 'flatest' value in flasm.ini");

		if (strlen(flapath) == 0)
			tellUser(1, "You must define '%s' value in flasm.ini for debugging", flatest);

		if (access(flapath, 1) != 0)
			tellUser(1, "Couldn't start: %s", flapath);

		if (strstr(argv[1], "file:///") != NULL)
			/* +8: skip "file:///" */
			unescapePath(argv[1] + 8);
		else
			unescapePath(argv[1]);

		if ((inputFile = fopen(inputName, "rb")) == NULL)
			tellUser(1, "Couldn't open input file %s for reading", inputName);

		strcat(flapath, " ");
		strcat(flapath, argv[1]);

		if (strIstr(flatest, "FLAPLAYER") != NULL)
			strcpy(strstr(flapath, ".htm"), ".swf\0");

		return;
	}

	if (argv[1][0] == '-') {
#if 0
		int i;
		if (argc < 3)
			usage();
#endif
		inputName = mstrdup(NULL);
		strcpy(inputName, argv[2]);

#if 0
		/* join all arguments into one string - to support spaces in file names */
		for (i = 3; i < argc; i++) {
			strcat(inputName, " ");
			strcat(inputName, argv[i]);
		}

		switch (argv[1][1]) {
			case 'd':
				mode = MODE_DISASSEMBLE;
				break;

			case 'a':
				mode = MODE_ASSEMBLE;
				break;

			case 'u':
				mode = MODE_UPDATE;
				break;

			case 'x':
				mode = MODE_DECOMPRESS;
				break;

			case 'z':
				mode = MODE_COMPRESS;
				break;

			default:
				usage();
		}
#endif
	}
	else {
//		int i;
		inputName = mstrdup(NULL);
		strcpy(inputName, argv[1]);
		strcpy(outputName, argv[2]);

#if 0
		/* join all arguments into one string - to support spaces in file names */
		for (i = 2; i < argc; i++) {
			strcat(inputName, " ");
			strcat(inputName, argv[i]);
		}
#endif

		if (strIstr(inputName, ".swf") != NULL || strIstr(inputName, ".eaf") != NULL) {
			flmName = mstrdup(inputName);
			char *name = strIstr(flmName, ".swf");
			if (name == NULL){
				name = strIstr(flmName, ".eaf");
			}
			strcpy(name, ".flm");
			/* redirect stdout to inputName.flm; should close it later? */
			if (freopen(flmName, "wb", stdout) == NULL) {
				tellUser(1, "Couldn't open output file %s for writing", flmName);
			}


		}
		else
			usage();
	}

	mode = MODE_DISASSEMBLE;
	if (inputName == NULL)
		usage();
#if 0
	if ((inputFile = fopen(inputName, "rb")) == NULL)
		tellUser(1, "Couldn't open input file %s for reading", inputName);
#endif
}

int countInstancesOfString(char *buffer, char *string)
{
	int count = 0;
	int len = strlen(string);
	for (char *i = strstr(buffer, string); i; i = strstr(&i[len], string))
		count++;
	return count;
}

char *replaceString(char *buffer, char *oldstr, char *newstr)
{
	int count = countInstancesOfString(buffer, oldstr);
	int oldlen = strlen(oldstr);
	int newlen = strlen(newstr);
	int len = strlen(buffer) + 1 + count * (newlen - oldlen);
	char *newbuf = new char[len];
	memset(newbuf, 0, len);
	char *newbuf2 = newbuf;
	for (char *i = strstr(buffer, oldstr); i; i = strstr(&i[oldlen], oldstr))
	{
		memcpy(newbuf, buffer, i - buffer);
		char *pos = &newbuf[i - buffer];
		memcpy(pos, newstr, newlen);
		newbuf = &pos[newlen];
		buffer = &i[oldlen];
	}
	int len2 = strlen(buffer);
	memcpy(newbuf, buffer, len2);
	return newbuf2;
}

void replaceNullStrings(const char *filename)
{
	int handle = open(filename, 0);
	int len = filelength(handle);
	char *buffer = new char[len + 1];
	read(handle, buffer, len);
	buffer[len] = 0;
	close(handle);
	char *newbuf = replaceString(buffer, "&push NULL", "&pushnull");
	delete[] buffer;
	int handle2 = open(filename, 1);
	write(handle2, newbuf, strlen(newbuf));
	close(handle2);
	delete[] newbuf;
}

void CopyFile(const char* infile, const char *outfile)
{
	FILE* f = fopen(infile, "rb");
	fseek(f, 0, SEEK_END);
	int len = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* buffer = new char[len];
	fread(buffer, 1, len, f);
	fclose(f);
	FILE* f2 = fopen(outfile, "wb");
	fwrite(buffer, 1, len, f2);
	fclose(f2);
	delete[] buffer;
}

int main(int argc, char *argv[])
{
	yydebug = 0;

	checkByteOrder();

	parseArgs(argc, argv);

	if (mode == MODE_DISASSEMBLE) {
		FILE *stdoutTempFile;

		if ( strIstr(inputName, ".swf") )
		{
			CopyFile(inputName, outputName);
		}

		FILE *file = fopen(outputName, "rb");
		if ( !file ) {
			tellUser(1, "Can't open source EAF file");
		}

		getSWFHeader(file);

		FILE *workfile = NULL;
		if (strcmp(swfHeader, "FWS") != 0) {
			if (strcmp(swfHeader, "CWS") != 0) {
				tellUser(1, "Input file doesn't appear to be an SWF file..");
				mexit(1);
			}
			else {
				decompressSWF(file, inputName);
				fseek(tempFile, 3, 0);
				workfile = tempFile;
				remove(tempName);
			}
		} else {
			workfile  = file;
		}

		char *name = mstrdup(outputName);
		strcpy(strIstr(name, ".eaf"), ".tac");

		stdoutTempFile = fopen(name, "wb");

		if (stdoutTempFile == NULL)
			tellUser(1, "Couldn't create .tac file");

		disassembleSWF(workfile, outputName, stdoutTempFile);
		fclose(stdoutTempFile);
		
		fclose(file);
		replaceNullStrings(name);
		
		FILE *eafFile = fopen(name, "rb");
		rewind(eafFile);
		mode = MODE_ASSEMBLE;
		yyin = eafFile;
		yyparse();
		
		fclose(eafFile);
		exit(printActionRecordCallCount);
	}

	mexit(EXIT_SUCCESS);
}

/* indent -l200 --ignore-newlines -bap -nbc -fc1 -npsl -sob -ncdb -brs -br -nce -cdw -npcs -i4 -ts4 -c60 -cd30 -cli4 -cbi4 -bs -nss flasm.c */
/* splint -retvalint +posixlib -boolops -retvalother -realcompare -predboolint unflasm.c flasm.c endian.c assembler.tab.c > flasm.lint */
