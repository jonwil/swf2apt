/*
flasm, command line assembler & disassembler of flash actionscript bytecode
Copyright (c) 2001 Opaque Industries, (c) 2002-2003 Igor Kogan
All rights reserved. See LICENSE.TXT for terms of use.
*/

#ifndef	UTIL_H_INCLUDED
#define	UTIL_H_INCLUDED

#include <stdio.h>

#define	FLASM_VERSION		"1.51"
#define	MALLOC_INC			16
#define OUTPUT_INC			2048
#define	MAX_BUFFER			1000000
#define	MAX_CONSTANTS		10000
#define	MAX_FUNCDEPTH		10
#define	MAX_ENVIRONMENTS	100
#define	MAX_REGISTERS		256
#define	MAX_FUNCARGS		256
#define	MAX_AUTO_REGS		6
#define	MAX_INCLUDE_POOL	4000
#define	MAX_KEYWORD_LEN		256
#define	DUPCLIP_NUMBER		0x4000
#define	ANY_VALUE			10000000
#define INDENT_LEVEL		2

#define S16(p)       ((p)[0] + (((p)[1])<<8))
#define S16signed(p) ((p)[0] + ((signed char)((p)[1])<<8))

#define SUREALLOC(num,storage,type,size)	if ((num) % MALLOC_INC == 0) storage = (type*)realloc((void*)storage, ((num) + MALLOC_INC + 1) * (size))

typedef unsigned char byte;

enum
{
  FLASM_BIG_ENDIAN,
  FLASM_LITTLE_ENDIAN
};

extern int byteorder;
extern float zero;

struct keyword {
    const char *name;
    int numActions;
    int token;
};

extern struct keyword *in_word_set(register const char *str, register unsigned int len);

void checkByteOrder(void);
int longintCompare(const void *ap, const void *bp);
long int longintBinaryFind(const unsigned long int offset, const unsigned long int *table, const long int tablesize);
char *strIstr(char *String, char *Pattern);
void lowercase(const char *str, char *buf);
int strIcmp(char *s, char *t);
unsigned int getWord(FILE *f);
unsigned long int getDoubleWord(FILE *f);
unsigned long int xtoi(char *p);
char *getTagString(unsigned int tag);
//int isKeyword(char* str);

#endif /* UTIL_H_INCLUDED	*/
