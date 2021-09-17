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

#include "util.h"
#include "action.h"

int byteorder;
float zero;

void checkByteOrder(void)
{
  unsigned int x;
  unsigned char *p;

  x = 0x01020304;
  p = (unsigned char *)&x;

  if(*p == 1)
    byteorder = FLASM_BIG_ENDIAN;
  else
    byteorder = FLASM_LITTLE_ENDIAN;
}

int longintCompare(const void *ap, const void *bp)
{
	unsigned long int a = *(const unsigned long int *) ap;
	unsigned long int b = *(const unsigned long int *) bp;

	if (a < b)
		return -1;
	else if (a > b)
		return 1;
	else
		return 0;
}

long int longintBinaryFind(const unsigned long int offset, const unsigned long int *table, const long int tablesize)
{
	long int left, right, middle;

	left = 0;
	right = tablesize;

	while (left < right) {
		middle = (left + right) / 2;
		if (table[middle] < offset)
			left = middle + 1;
		else
			right = middle;
	}

	if (table[right] == offset)
		return(right);
	else
		return(-1);
}

char *strIstr(char *String, char *Pattern)
{
	char *pptr, *sptr, *start;
	size_t slen, plen;

	if (String == NULL)
		return (NULL);

	for (start = String, pptr = Pattern, slen = strlen(String), plen = strlen(Pattern); slen >= plen; start++, slen--) {
		while (toupper(*start) != toupper(*Pattern)) {
			start++;
			slen--;

			if (slen < plen)
				return (NULL);
		}

		sptr = start;
		pptr = Pattern;

		while (toupper(*sptr) == toupper(*pptr)) {
			sptr++;
			pptr++;

			if (*pptr == '\0')
				return (start);
		}
	}
	return (NULL);
}

int strIcmp(char *s, char *t)
{
	int d = 0;
	do {
		d = toupper(*s) - toupper(*t);
	} while (*s++ && *t++ && !d);
	return (d);
}

void lowercase(const char *str, char *buf)
{
	while (*str)
		*buf++ = tolower(*str++);

	*buf = '\0';
}

unsigned long int xtoi(char *p)
{
	unsigned long int num = 0;
	char c;

	while ((c = tolower(*p)) != '\0') {
		num <<= 4;

		if (isdigit(c))
			num += c - '0';
		else if (c >= 'a' && c <= 'f')
			num += c - 'a' + 10;
		else
			return 0;

		++p;
	}

	return num;
}

unsigned int getWord(FILE *f)
{
	unsigned int byte1 = (unsigned int) fgetc(f);
	unsigned int byte2 = (unsigned int) fgetc(f);
	return (byte1 + (byte2 << 8));
}

unsigned long int getDoubleWord(FILE *f)
{
	return ((unsigned long int) getWord(f) + ((unsigned long int) getWord(f) << 16));
}

#if 0
int isKeyword(char* str)
{
	char buf[MAX_KEYWORD_LEN];
	lowercase(str, buf);
	if (in_word_set(buf, strlen(buf)) != NULL)
		return 1;
	else
		return 0;
}
#endif

char *getTagString(unsigned int tag)
{
	switch(tag) {
		case TAG_END:					return"TAG_END";
		case TAG_SHOWFRAME:				return"TAG_SHOWFRAME";
		case TAG_DEFINESHAPE:			return"TAG_DEFINESHAPE";
		case TAG_FREECHARACTER:			return"TAG_FREECHARACTER";
		case TAG_PLACEOBJECT:			return"TAG_PLACEOBJECT";
		case TAG_REMOVEOBJECT:			return"TAG_REMOVEOBJECT";
		case TAG_DEFINEBITS:			return"TAG_DEFINEBITS";
		case TAG_DEFINEBUTTON:			return"TAG_DEFINEBUTTON";
		case TAG_JPEGTABLES:			return"TAG_JPEGTABLES";
		case TAG_SETBACKGROUNDCOLOR:	return"TAG_SETBACKGROUNDCOLOR";
		case TAG_DEFINEFONT:			return"TAG_DEFINEFONT";
		case TAG_DEFINETEXT:			return"TAG_DEFINETEXT";
		case TAG_DOACTION:				return"TAG_DOACTION";
		case TAG_DEFINEFONTINFO:		return"TAG_DEFINEFONTINFO";
		case TAG_DEFINESOUND:			return"TAG_DEFINESOUND";
		case TAG_STARTSOUND:			return"TAG_STARTSOUND";
		case TAG_STOPSOUND:				return"TAG_STOPSOUND";
		case TAG_DEFINEBUTTONSOUND:		return"TAG_DEFINEBUTTONSOUND";
		case TAG_SOUNDSTREAMHEAD:		return"TAG_SOUNDSTREAMHEAD";
		case TAG_SOUNDSTREAMBLOCK:		return"TAG_SOUNDSTREAMBLOCK";
		case TAG_DEFINEBITSLOSSLESS:	return"TAG_DEFINEBITSLOSSLESS";
		case TAG_DEFINEBITSJPEG2:		return"TAG_DEFINEBITSJPEG2";
		case TAG_DEFINESHAPE2:			return"TAG_DEFINESHAPE2";
		case TAG_DEFINEBUTTONCXFORM:	return"TAG_DEFINEBUTTONCXFORM";
		case TAG_PROTECT:				return"TAG_PROTECT";
		case TAG_PATHSAREPOSTSCRIPT:	return"TAG_PATHSAREPOSTSCRIPT";
		case TAG_PLACEOBJECT2:			return"TAG_PLACEOBJECT2";
		case TAG_REMOVEOBJECT2:			return"TAG_REMOVEOBJECT2";
		case TAG_SYNCFRAME:				return"TAG_SYNCFRAME";
		case TAG_FREEALL:				return"TAG_FREEALL";
		case TAG_DEFINESHAPE3:			return"TAG_DEFINESHAPE3";
		case TAG_DEFINETEXT2:			return"TAG_DEFINETEXT2";
		case TAG_DEFINEBUTTON2:			return"TAG_DEFINEBUTTON2";
		case TAG_DEFINEBITSJPEG3:		return"TAG_DEFINEBITSJPEG3";
		case TAG_DEFINEBITSLOSSLESS2:	return"TAG_DEFINEBITSLOSSLESS2";
		case TAG_DEFINEEDITTEXT:		return"TAG_DEFINEEDITTEXT";
		case TAG_DEFINEVIDEO:			return"TAG_DEFINEVIDEO";
		case TAG_DEFINEMOVIECLIP:		return"TAG_DEFINEMOVIECLIP";
		case TAG_NAMECHARACTER:			return"TAG_NAMECHARACTER";
		case TAG_SERIALNUMBER:			return"TAG_SERIALNUMBER";
		case TAG_DEFINETEXTFORMAT:		return"TAG_DEFINETEXTFORMAT";
		case TAG_FRAMELABEL:			return"TAG_FRAMELABEL";
		case TAG_SOUNDSTREAMHEAD2:		return"TAG_SOUNDSTREAMHEAD2";
		case TAG_DEFINEMORPHSHAPE:		return"TAG_DEFINEMORPHSHAPE";
		case TAG_GENFRAME:				return"TAG_GENFRAME";
		case TAG_DEFINEFONT2:			return"TAG_DEFINEFONT2";
		case TAG_GENCOMMAND:			return"TAG_GENCOMMAND";
		case TAG_DEFINECOMMANDOBJ:		return"TAG_DEFINECOMMANDOBJ";
		case TAG_CHARACTERSET:			return"TAG_CHARACTERSET";
		case TAG_FONTREF:				return"TAG_FONTREF";
		case TAG_EXPORTASSETS:			return"TAG_EXPORTASSETS";
		case TAG_IMPORTASSETS:			return"TAG_IMPORTASSETS";
		case TAG_ENABLEDEBUGGER:		return"TAG_ENABLEDEBUGGER";
		case TAG_INITMOVIECLIP:			return"TAG_INITMOVIECLIP";
		case TAG_DEFINEVIDEOSTREAM:		return"TAG_DEFINEVIDEOSTREAM";
		case TAG_VIDEOFRAME:			return"TAG_VIDEOFRAME";
		case TAG_DEFINEFONTINFO2:		return"TAG_DEFINEFONTINFO2";
		case TAG_ENABLEDEBUGGER2:		return"TAG_ENABLEDEBUGGER2";
		case TAG_SCRIPTLIMITS:			return"TAG_SCRIPTLIMITS";
		case TAG_SETTABINDEX:			return"TAG_SETTABINDEX";
		case TAG_DEFINEBITSPTR:			return"TAG_DEFINEBITSPTR";
		default:						return NULL;
	}
}
