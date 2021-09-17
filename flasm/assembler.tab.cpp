/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for GLR parsing with Bison,
   Copyright (C) 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* This is the parser code for GLR (Generalized LR) parser. */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MOVIENAME = 258,
     STRING = 259,
     INTEGER = 260,
     HEX = 261,
     FLOAT = 262,
     DOUBLE = 263,
     TRUEVAL = 264,
     FALSEVAL = 265,
     NULLVAL = 266,
     UNDEFVAL = 267,
     REGISTER = 268,
     REGISTERALIAS = 269,
     LABEL = 270,
     MOVIE = 271,
     COMPRESSED = 272,
     PROTECT = 273,
     SCRIPTLIMITS = 274,
     RECURSION = 275,
     TIMEOUT = 276,
     ENABLEDEBUGGER = 277,
     ENABLEDEBUGGER2 = 278,
     FRAME = 279,
     PLACEMOVIECLIP = 280,
     DEFINEMOVIECLIP = 281,
     INITMOVIECLIP = 282,
     DEFINEBUTTON = 283,
     ON = 284,
     ONCLIPEVENT = 285,
     AS = 286,
     IMPORTASSETS = 287,
     EXPORTASSETS = 288,
     FROM = 289,
     _NAN = 290,
     POSITIVE_INFINITY = 291,
     NEGATIVE_INFINITY = 292,
     _NANF = 293,
     POSITIVE_INFINITYF = 294,
     NEGATIVE_INFINITYF = 295,
     BIDLETOOVERUP = 296,
     BOVERUPTOIDLE = 297,
     BOVERUPTOOVERDOWN = 298,
     BOVERDOWNTOOVERUP = 299,
     BOVERDOWNTOOUTDOWN = 300,
     BOUTDOWNTOOVERDOWN = 301,
     BOUTDOWNTOIDLE = 302,
     BIDLETOOVERDOWN = 303,
     BOVERDOWNTOIDLE = 304,
     KEYPRESS = 305,
     _LEFT = 306,
     _RIGHT = 307,
     _HOME = 308,
     _END = 309,
     _INSERT = 310,
     _DELETE = 311,
     _BACKSPACE = 312,
     _ENTER = 313,
     _UP = 314,
     _DOWN = 315,
     _PGUP = 316,
     _PGDN = 317,
     _TAB = 318,
     _ESCAPE = 319,
     _SPACE = 320,
     MCLOAD = 321,
     MCENTERFRAME = 322,
     MCUNLOAD = 323,
     MCMOUSEMOVE = 324,
     MCMOUSEDOWN = 325,
     MCMOUSEUP = 326,
     MCKEYDOWN = 327,
     MCKEYUP = 328,
     MCINITIALIZE = 329,
     MCCONSTRUCT = 330,
     MCDATA = 331,
     MCPRESS = 332,
     MCRELEASE = 333,
     MCRELEASEOUTSIDE = 334,
     MCROLLOVER = 335,
     MCROLLOUT = 336,
     MCDRAGOVER = 337,
     MCDRAGOUT = 338,
     X_PROPERTY = 339,
     Y_PROPERTY = 340,
     XSCALE_PROPERTY = 341,
     YSCALE_PROPERTY = 342,
     WIDTH_PROPERTY = 343,
     HEIGHT_PROPERTY = 344,
     ALPHA_PROPERTY = 345,
     VISIBLE_PROPERTY = 346,
     ROTATION_PROPERTY = 347,
     CURRENTFRAME_PROPERTY = 348,
     TOTALFRAMES_PROPERTY = 349,
     TARGET_PROPERTY = 350,
     FRAMESLOADED_PROPERTY = 351,
     NAME_PROPERTY = 352,
     DROPTARGET_PROPERTY = 353,
     URL_PROPERTY = 354,
     QUALITY_PROPERTY = 355,
     XMOUSE_PROPERTY = 356,
     YMOUSE_PROPERTY = 357,
     HIGHQUALITY_PROPERTY = 358,
     FOCUSRECT_PROPERTY = 359,
     SOUNDBUFTIME_PROPERTY = 360,
     NEXTFRAME = 361,
     PREVFRAME = 362,
     GOTOFRAME = 363,
     GOTOLABEL = 364,
     PLAY = 365,
     STOP = 366,
     TOGGLEQUALITY = 367,
     STOPSOUNDS = 368,
     FUNCTION = 369,
     FUNCTION2 = 370,
     CONSTANTS = 371,
     END = 372,
     DUP = 373,
     SWAP = 374,
     POP = 375,
     WITH = 376,
     PUSH = 377,
     SETREGISTER = 378,
     CALLFUNCTION = 379,
     RETURN = 380,
     NEWMETHOD = 381,
     CALLMETHOD = 382,
     BITWISEAND = 383,
     BITWISEOR = 384,
     BITWISEXOR = 385,
     MODULO = 386,
     NEWADD = 387,
     NEWLESSTHAN = 388,
     NEWEQUALS = 389,
     TONUMBER = 390,
     TOSTRING = 391,
     INCREMENT = 392,
     DECREMENT = 393,
     TYPEOF = 394,
     TARGETPATH = 395,
     ENUMERATE = 396,
     ENUMERATEVALUE = 397,
     INSTANCEOF = 398,
     DELETE = 399,
     DELETE2 = 400,
     NEW = 401,
     INITARRAY = 402,
     INITOBJECT = 403,
     GETMEMBER = 404,
     SETMEMBER = 405,
     SHIFTLEFT = 406,
     SHIFTRIGHT = 407,
     SHIFTRIGHT2 = 408,
     VAR = 409,
     VAREQUALS = 410,
     OLDADD = 411,
     SUBTRACT = 412,
     MULTIPLY = 413,
     DIVIDE = 414,
     OLDEQUALS = 415,
     OLDLESSTHAN = 416,
     STRICTEQUALS = 417,
     GREATERTHAN = 418,
     LOGICALAND = 419,
     LOGICALOR = 420,
     LOGICALNOT = 421,
     STRINGEQ = 422,
     STRINGLENGTH = 423,
     SUBSTRING = 424,
     INT = 425,
     GETVARIABLE = 426,
     SETVARIABLE = 427,
     SETTARGET = 428,
     SETTARGETEXPR = 429,
     STRINGCONCAT = 430,
     GETPROPERTY = 431,
     SETPROPERTY = 432,
     DUPLICATECLIP = 433,
     REMOVECLIP = 434,
     TRACE = 435,
     STARTDRAGMOVIE = 436,
     STOPDRAGMOVIE = 437,
     STRINGLESSTHAN = 438,
     STRINGGREATERTHAN = 439,
     RANDOM = 440,
     MBLENGTH = 441,
     ORD = 442,
     CHR = 443,
     GETTIMER = 444,
     MBSUBSTRING = 445,
     MBORD = 446,
     MBCHR = 447,
     BRANCHALWAYS = 448,
     GETURL = 449,
     GETURL2 = 450,
     LOADMOVIE = 451,
     LOADMOVIENUM = 452,
     LOADVARIABLES = 453,
     LOADVARIABLESNUM = 454,
     POST = 455,
     GET = 456,
     BRANCHIFTRUE = 457,
     CALLFRAME = 458,
     GOTOANDPLAY = 459,
     GOTOANDSTOP = 460,
     SKIP = 461,
     IFFRAMELOADEDEXPR = 462,
     IFFRAMELOADED = 463,
     ELSE = 464,
     STRICTMODE = 465,
     OFF = 466,
     IMPLEMENTS = 467,
     EXTENDS = 468,
     THROW = 469,
     CAST = 470,
     TRY = 471,
     CATCH = 472,
     FINALLY = 473,
     EQUALSIGN = 474,
     PUSHONE = 475,
     PUSHZERO = 476,
     PUSHTRUE = 477,
     PUSHFALSE = 478,
     PUSHBYTE = 479,
     PUSHSHORT = 480,
     PUSHLONG = 481,
     PUSHS = 482,
     PUSHSDB = 483,
     PUSHSDW = 484,
     CALLFP = 485,
     CALLFSV = 486,
     CALLMP = 487,
     CALLMSV = 488,
     PUSHSDBGV = 489,
     PUSHSDBGM = 490,
     PUSHTHIS = 491,
     PUSHGLOBAL = 492,
     PUSHNULL = 493,
     PUSHUNDEF = 494,
     DCALLFP = 495,
     DCALLFSV = 496,
     DCALLMP = 497,
     DCALLMSV = 498,
     PUSHFLOAT = 499,
     PUSHTHISGV = 500,
     PUSHGLOBALGV = 501,
     PUSHSGV = 502,
     PUSHSGM = 503,
     PUSHZEROSV = 504,
     PUSHSSV = 505,
     PUSHSSM = 506,
     BRANCHIFFALSE = 507,
     APTTRACESTART = 508,
     PUSHREGISTER = 509,
     SWFACTION = 510,
     HEXDATA = 511
   };
#endif
/* Tokens.  */
#define MOVIENAME 258
#define STRING 259
#define INTEGER 260
#define HEX 261
#define FLOAT 262
#define DOUBLE 263
#define TRUEVAL 264
#define FALSEVAL 265
#define NULLVAL 266
#define UNDEFVAL 267
#define REGISTER 268
#define REGISTERALIAS 269
#define LABEL 270
#define MOVIE 271
#define COMPRESSED 272
#define PROTECT 273
#define SCRIPTLIMITS 274
#define RECURSION 275
#define TIMEOUT 276
#define ENABLEDEBUGGER 277
#define ENABLEDEBUGGER2 278
#define FRAME 279
#define PLACEMOVIECLIP 280
#define DEFINEMOVIECLIP 281
#define INITMOVIECLIP 282
#define DEFINEBUTTON 283
#define ON 284
#define ONCLIPEVENT 285
#define AS 286
#define IMPORTASSETS 287
#define EXPORTASSETS 288
#define FROM 289
#define _NAN 290
#define POSITIVE_INFINITY 291
#define NEGATIVE_INFINITY 292
#define _NANF 293
#define POSITIVE_INFINITYF 294
#define NEGATIVE_INFINITYF 295
#define BIDLETOOVERUP 296
#define BOVERUPTOIDLE 297
#define BOVERUPTOOVERDOWN 298
#define BOVERDOWNTOOVERUP 299
#define BOVERDOWNTOOUTDOWN 300
#define BOUTDOWNTOOVERDOWN 301
#define BOUTDOWNTOIDLE 302
#define BIDLETOOVERDOWN 303
#define BOVERDOWNTOIDLE 304
#define KEYPRESS 305
#define _LEFT 306
#define _RIGHT 307
#define _HOME 308
#define _END 309
#define _INSERT 310
#define _DELETE 311
#define _BACKSPACE 312
#define _ENTER 313
#define _UP 314
#define _DOWN 315
#define _PGUP 316
#define _PGDN 317
#define _TAB 318
#define _ESCAPE 319
#define _SPACE 320
#define MCLOAD 321
#define MCENTERFRAME 322
#define MCUNLOAD 323
#define MCMOUSEMOVE 324
#define MCMOUSEDOWN 325
#define MCMOUSEUP 326
#define MCKEYDOWN 327
#define MCKEYUP 328
#define MCINITIALIZE 329
#define MCCONSTRUCT 330
#define MCDATA 331
#define MCPRESS 332
#define MCRELEASE 333
#define MCRELEASEOUTSIDE 334
#define MCROLLOVER 335
#define MCROLLOUT 336
#define MCDRAGOVER 337
#define MCDRAGOUT 338
#define X_PROPERTY 339
#define Y_PROPERTY 340
#define XSCALE_PROPERTY 341
#define YSCALE_PROPERTY 342
#define WIDTH_PROPERTY 343
#define HEIGHT_PROPERTY 344
#define ALPHA_PROPERTY 345
#define VISIBLE_PROPERTY 346
#define ROTATION_PROPERTY 347
#define CURRENTFRAME_PROPERTY 348
#define TOTALFRAMES_PROPERTY 349
#define TARGET_PROPERTY 350
#define FRAMESLOADED_PROPERTY 351
#define NAME_PROPERTY 352
#define DROPTARGET_PROPERTY 353
#define URL_PROPERTY 354
#define QUALITY_PROPERTY 355
#define XMOUSE_PROPERTY 356
#define YMOUSE_PROPERTY 357
#define HIGHQUALITY_PROPERTY 358
#define FOCUSRECT_PROPERTY 359
#define SOUNDBUFTIME_PROPERTY 360
#define NEXTFRAME 361
#define PREVFRAME 362
#define GOTOFRAME 363
#define GOTOLABEL 364
#define PLAY 365
#define STOP 366
#define TOGGLEQUALITY 367
#define STOPSOUNDS 368
#define FUNCTION 369
#define FUNCTION2 370
#define CONSTANTS 371
#define END 372
#define DUP 373
#define SWAP 374
#define POP 375
#define WITH 376
#define PUSH 377
#define SETREGISTER 378
#define CALLFUNCTION 379
#define RETURN 380
#define NEWMETHOD 381
#define CALLMETHOD 382
#define BITWISEAND 383
#define BITWISEOR 384
#define BITWISEXOR 385
#define MODULO 386
#define NEWADD 387
#define NEWLESSTHAN 388
#define NEWEQUALS 389
#define TONUMBER 390
#define TOSTRING 391
#define INCREMENT 392
#define DECREMENT 393
#define TYPEOF 394
#define TARGETPATH 395
#define ENUMERATE 396
#define ENUMERATEVALUE 397
#define INSTANCEOF 398
#define DELETE 399
#define DELETE2 400
#define NEW 401
#define INITARRAY 402
#define INITOBJECT 403
#define GETMEMBER 404
#define SETMEMBER 405
#define SHIFTLEFT 406
#define SHIFTRIGHT 407
#define SHIFTRIGHT2 408
#define VAR 409
#define VAREQUALS 410
#define OLDADD 411
#define SUBTRACT 412
#define MULTIPLY 413
#define DIVIDE 414
#define OLDEQUALS 415
#define OLDLESSTHAN 416
#define STRICTEQUALS 417
#define GREATERTHAN 418
#define LOGICALAND 419
#define LOGICALOR 420
#define LOGICALNOT 421
#define STRINGEQ 422
#define STRINGLENGTH 423
#define SUBSTRING 424
#define INT 425
#define GETVARIABLE 426
#define SETVARIABLE 427
#define SETTARGET 428
#define SETTARGETEXPR 429
#define STRINGCONCAT 430
#define GETPROPERTY 431
#define SETPROPERTY 432
#define DUPLICATECLIP 433
#define REMOVECLIP 434
#define TRACE 435
#define STARTDRAGMOVIE 436
#define STOPDRAGMOVIE 437
#define STRINGLESSTHAN 438
#define STRINGGREATERTHAN 439
#define RANDOM 440
#define MBLENGTH 441
#define ORD 442
#define CHR 443
#define GETTIMER 444
#define MBSUBSTRING 445
#define MBORD 446
#define MBCHR 447
#define BRANCHALWAYS 448
#define GETURL 449
#define GETURL2 450
#define LOADMOVIE 451
#define LOADMOVIENUM 452
#define LOADVARIABLES 453
#define LOADVARIABLESNUM 454
#define POST 455
#define GET 456
#define BRANCHIFTRUE 457
#define CALLFRAME 458
#define GOTOANDPLAY 459
#define GOTOANDSTOP 460
#define SKIP 461
#define IFFRAMELOADEDEXPR 462
#define IFFRAMELOADED 463
#define ELSE 464
#define STRICTMODE 465
#define OFF 466
#define IMPLEMENTS 467
#define EXTENDS 468
#define THROW 469
#define CAST 470
#define TRY 471
#define CATCH 472
#define FINALLY 473
#define EQUALSIGN 474
#define PUSHONE 475
#define PUSHZERO 476
#define PUSHTRUE 477
#define PUSHFALSE 478
#define PUSHBYTE 479
#define PUSHSHORT 480
#define PUSHLONG 481
#define PUSHS 482
#define PUSHSDB 483
#define PUSHSDW 484
#define CALLFP 485
#define CALLFSV 486
#define CALLMP 487
#define CALLMSV 488
#define PUSHSDBGV 489
#define PUSHSDBGM 490
#define PUSHTHIS 491
#define PUSHGLOBAL 492
#define PUSHNULL 493
#define PUSHUNDEF 494
#define DCALLFP 495
#define DCALLFSV 496
#define DCALLMP 497
#define DCALLMSV 498
#define PUSHFLOAT 499
#define PUSHTHISGV 500
#define PUSHGLOBALGV 501
#define PUSHSGV 502
#define PUSHSGM 503
#define PUSHZEROSV 504
#define PUSHSSV 505
#define PUSHSSM 506
#define BRANCHIFFALSE 507
#define APTTRACESTART 508
#define PUSHREGISTER 509
#define SWFACTION 510
#define HEXDATA 511




/* Copy the first part of user declarations.  */
#line 7 "assembler.y"


#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "util.h"
#include "flasm.h"

void yyerror(const char *s);
void warning(char *msg);
int yylex(void);

extern char *yytext;
extern long int len;
extern unsigned int nConstants;
extern int mode;
extern char compressAfter;
extern int numActions;
extern int clearregisterargs;
extern char *arNames[];
extern unsigned int arFlags[];
extern unsigned int arNotFlags[];

static char *func_args[MAX_FUNCARGS];
static char *regfunc_args[MAX_FUNCDEPTH][MAX_REGISTERS];
static unsigned int numRegisters[MAX_FUNCDEPTH];
static int curFunc = -1;
static unsigned int numAssets;
static unsigned long int curEvent, allEvents;
static int frameloadedStart = -1;
static unsigned int numArgs;
static unsigned int autoregFlags;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 44 "assembler.y"
typedef union YYSTYPE {
  long int num;
  char *str;
} YYSTYPE;
/* Line 186 of glr.c.  */
#line 623 "assembler.tab.c"
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined (YYLTYPE) && ! defined (YYLTYPE_IS_DECLARED)
typedef struct YYLTYPE
{

  char yydummy;

} YYLTYPE;
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template,
   here we set the default value of $$ to a zeroed-out value.
   Since the default value is undefined, this behavior is
   technically correct. */
static YYSTYPE yyval_default;

/* Copy the second part of user declarations.  */


/* Line 217 of glr.c.  */
#line 650 "assembler.tab.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#define YYSIZEMAX ((size_t) -1)

#ifdef __cplusplus
   typedef bool yybool;
#else
   typedef unsigned char yybool;
#endif
#define yytrue 1
#define yyfalse 0

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(env) setjmp (env)
# define YYLONGJMP(env, val) longjmp (env, val)
#endif

/*-----------------.
| GCC extensions.  |
`-----------------*/

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (!defined (__GNUC__) || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5) || __STRICT_ANSI__)
#  define __attribute__(Spec) /* empty */
# endif
#endif


#ifdef __cplusplus
# define YYOPTIONAL_LOC(Name) /* empty */
#else
# define YYOPTIONAL_LOC(Name) Name __attribute__ ((__unused__))
#endif

#ifndef YYASSERT
# define YYASSERT(condition) ((void) ((condition) || (abort (), 0)))
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   982

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  263
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  91
/* YYNRULES -- Number of rules. */
#define YYNRULES  400
/* YYNRULES -- Number of states. */
#define YYNSTATES  513
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule. */
#define YYMAXRHS 13
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule. */
#define YYMAXLEFT 0

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   511

#define YYTRANSLATE(YYX)						\
  ((YYX <= 0) ? YYEOF :							\
   (unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned short int yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   261,     2,     2,     2,     2,     2,
     257,   258,     2,     2,   259,     2,   262,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   260,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     4,    10,    11,    13,    15,    18,    20,
      22,    24,    26,    28,    30,    32,    34,    36,    39,    41,
      44,    47,    53,    58,    63,    64,    70,    71,    73,    75,
      78,    79,    85,    87,    91,    93,    95,    97,    99,   101,
     103,   105,   107,   109,   112,   114,   116,   118,   120,   122,
     124,   126,   128,   130,   132,   134,   136,   138,   140,   142,
     144,   146,   148,   149,   155,   156,   158,   160,   163,   165,
     167,   168,   175,   176,   179,   180,   182,   184,   187,   188,
     194,   196,   200,   201,   203,   205,   207,   209,   211,   213,
     215,   217,   219,   221,   223,   225,   227,   229,   231,   233,
     235,   238,   240,   241,   244,   245,   248,   249,   250,   251,
     252,   263,   266,   268,   271,   273,   275,   278,   281,   283,
     285,   287,   289,   291,   293,   295,   297,   299,   301,   303,
     305,   307,   308,   310,   314,   315,   317,   318,   320,   321,
     322,   332,   336,   338,   339,   341,   345,   349,   350,   352,
     356,   357,   358,   359,   373,   374,   379,   380,   386,   387,
     392,   393,   398,   399,   405,   406,   413,   414,   416,   418,
     421,   425,   426,   431,   432,   434,   436,   439,   443,   445,
     447,   449,   451,   453,   455,   457,   459,   461,   463,   465,
     467,   469,   471,   473,   475,   477,   479,   481,   483,   485,
     487,   489,   491,   493,   495,   497,   499,   501,   503,   505,
     507,   509,   511,   513,   515,   517,   519,   521,   523,   527,
     529,   533,   535,   539,   540,   543,   544,   546,   548,   551,
     554,   557,   560,   563,   566,   569,   572,   576,   580,   584,
     588,   591,   594,   598,   602,   605,   608,   611,   614,   617,
     621,   625,   629,   633,   637,   640,   643,   646,   649,   652,
     655,   657,   659,   661,   663,   665,   668,   671,   674,   677,
     680,   683,   685,   687,   690,   693,   696,   699,   702,   705,
     708,   710,   713,   715,   717,   719,   721,   723,   725,   727,
     729,   732,   735,   736,   740,   741,   745,   746,   751,   754,
     756,   758,   760,   762,   764,   766,   768,   770,   772,   774,
     776,   778,   780,   782,   784,   786,   788,   790,   792,   794,
     796,   798,   800,   802,   804,   806,   808,   810,   812,   814,
     816,   818,   820,   822,   824,   826,   828,   830,   832,   834,
     836,   838,   840,   842,   844,   846,   848,   850,   852,   854,
     856,   858,   860,   862,   864,   866,   868,   870,   872,   874,
     876,   878,   880,   882,   884,   886,   888,   890,   892,   894,
     896,   898,   900,   902,   904,   906,   908,   910,   912,   914,
     916,   918,   922,   924,   928,   931,   934,   937,   940,   943,
     946,   949,   952,   956,   959,   962,   965,   968,   971,   974,
     977
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
     264,     0,    -1,    -1,    16,     3,   265,   266,   117,    -1,
      -1,   267,    -1,   268,    -1,   267,   268,    -1,   269,    -1,
     271,    -1,   281,    -1,   286,    -1,   270,    -1,   331,    -1,
     336,    -1,    17,    -1,    18,    -1,    18,     4,    -1,    22,
      -1,    22,     4,    -1,    23,     4,    -1,    19,    20,     5,
      21,     5,    -1,    24,     5,   308,   117,    -1,    27,     5,
     308,   117,    -1,    -1,    28,     5,   272,   273,   117,    -1,
      -1,   274,    -1,   275,    -1,   274,   275,    -1,    -1,    29,
     276,   277,   308,   117,    -1,   278,    -1,   277,   259,   278,
      -1,    41,    -1,    42,    -1,    43,    -1,    44,    -1,    45,
      -1,    46,    -1,    47,    -1,    48,    -1,    49,    -1,    50,
     279,    -1,    51,    -1,    52,    -1,    53,    -1,    54,    -1,
      55,    -1,    56,    -1,    57,    -1,    58,    -1,    59,    -1,
      60,    -1,    61,    -1,    62,    -1,    63,    -1,    64,    -1,
      65,    -1,     4,    -1,    13,    -1,    14,    -1,    -1,    26,
       5,   282,   283,   117,    -1,    -1,   284,    -1,   285,    -1,
     284,   285,    -1,   269,    -1,   286,    -1,    -1,    25,     5,
     288,   287,   289,   117,    -1,    -1,    31,     4,    -1,    -1,
     290,    -1,   291,    -1,   290,   291,    -1,    -1,    30,   293,
     292,   308,   117,    -1,   294,    -1,   293,   259,   294,    -1,
      -1,    66,    -1,    67,    -1,    68,    -1,    69,    -1,    70,
      -1,    71,    -1,    72,    -1,    73,    -1,    76,    -1,    74,
      -1,    77,    -1,    78,    -1,    79,    -1,    80,    -1,    81,
      -1,    82,    -1,    83,    -1,    50,   279,    -1,    75,    -1,
      -1,   217,   308,    -1,    -1,   218,   308,    -1,    -1,    -1,
      -1,    -1,   216,   309,   298,   308,   299,   295,   300,   296,
     301,   117,    -1,   216,   280,    -1,   303,    -1,   302,   303,
      -1,   304,    -1,   305,    -1,   302,   304,    -1,   302,   305,
      -1,   306,    -1,   310,    -1,   317,    -1,   321,    -1,   323,
      -1,   325,    -1,   329,    -1,   327,    -1,   297,    -1,   350,
      -1,   348,    -1,   349,    -1,    15,    -1,    -1,     4,    -1,
     307,   259,     4,    -1,    -1,   302,    -1,    -1,     4,    -1,
      -1,    -1,   114,   309,   311,   257,   307,   258,   312,   308,
     117,    -1,    13,   219,     4,    -1,     4,    -1,    -1,   313,
      -1,   314,   259,   313,    -1,    13,   219,     4,    -1,    -1,
     315,    -1,   316,   259,   315,    -1,    -1,    -1,    -1,   115,
     309,   318,   257,   314,   258,   319,   257,   316,   258,   320,
     308,   117,    -1,    -1,   121,   322,   308,   117,    -1,    -1,
     173,     4,   324,   308,   117,    -1,    -1,   174,   326,   308,
     117,    -1,    -1,   207,   328,   308,   117,    -1,    -1,   208,
       5,   330,   308,   117,    -1,    -1,    32,    34,     4,   332,
     333,   117,    -1,    -1,   334,    -1,   335,    -1,   334,   335,
      -1,     4,    31,     5,    -1,    -1,    33,   337,   338,   117,
      -1,    -1,   339,    -1,   340,    -1,   339,   340,    -1,     5,
      31,     4,    -1,     4,    -1,   342,    -1,     7,    -1,    38,
      -1,    39,    -1,    40,    -1,     6,    -1,     5,    -1,     8,
      -1,    35,    -1,    36,    -1,    37,    -1,     9,    -1,    10,
      -1,    11,    -1,    12,    -1,   280,    -1,    84,    -1,    85,
      -1,    86,    -1,    87,    -1,    93,    -1,    94,    -1,    90,
      -1,    91,    -1,    88,    -1,    89,    -1,    92,    -1,    95,
      -1,    96,    -1,    97,    -1,    98,    -1,    99,    -1,   103,
      -1,   104,    -1,   105,    -1,   100,    -1,   101,    -1,   102,
      -1,   341,    -1,   343,   259,   341,    -1,     4,    -1,   344,
     259,     4,    -1,     6,    -1,   345,   259,     6,    -1,    -1,
     256,   345,    -1,    -1,   201,    -1,   200,    -1,   221,   172,
      -1,   236,   171,    -1,   237,   171,    -1,   122,     5,    -1,
     122,     4,    -1,   122,     7,    -1,   122,     8,    -1,   122,
      13,    -1,   227,     4,   171,    -1,   227,     4,   149,    -1,
     227,     4,   172,    -1,   227,     4,   150,    -1,   229,     5,
      -1,   228,     5,    -1,   228,     5,   171,    -1,   228,     5,
     149,    -1,   234,     5,    -1,   124,   120,    -1,   124,   172,
      -1,   127,   120,    -1,   127,   172,    -1,   228,     5,   230,
      -1,   229,     5,   230,    -1,   228,     5,   231,    -1,   228,
       5,   232,    -1,   228,     5,   233,    -1,   122,    11,    -1,
     122,    12,    -1,   122,     9,    -1,   122,    10,    -1,   166,
     166,    -1,   224,     5,    -1,   238,    -1,   239,    -1,   222,
      -1,   223,    -1,   249,    -1,   225,     5,    -1,   226,     5,
      -1,   244,     7,    -1,   244,     8,    -1,   254,     5,    -1,
     227,     4,    -1,   220,    -1,   221,    -1,   247,     4,    -1,
     248,     4,    -1,   250,     4,    -1,   251,     4,    -1,   240,
       5,    -1,   241,     5,    -1,   242,     5,    -1,   253,    -1,
     243,     5,    -1,   230,    -1,   245,    -1,   246,    -1,   231,
      -1,   232,    -1,   233,    -1,   236,    -1,   237,    -1,   235,
       5,    -1,   234,     5,    -1,    -1,   116,   351,   344,    -1,
      -1,   122,   352,   343,    -1,    -1,   255,     6,   353,   346,
      -1,   123,   280,    -1,   162,    -1,   163,    -1,   142,    -1,
     143,    -1,   106,    -1,   107,    -1,   110,    -1,   111,    -1,
     112,    -1,   113,    -1,   124,    -1,   125,    -1,   126,    -1,
     127,    -1,   128,    -1,   129,    -1,   130,    -1,   131,    -1,
     132,    -1,   133,    -1,   134,    -1,   135,    -1,   136,    -1,
     137,    -1,   138,    -1,   139,    -1,   140,    -1,   141,    -1,
     144,    -1,   145,    -1,   146,    -1,   147,    -1,   148,    -1,
     149,    -1,   150,    -1,   151,    -1,   152,    -1,   153,    -1,
     154,    -1,   155,    -1,   156,    -1,   157,    -1,   158,    -1,
     159,    -1,   160,    -1,   161,    -1,   164,    -1,   165,    -1,
     166,    -1,   167,    -1,   168,    -1,   169,    -1,   170,    -1,
     118,    -1,   119,    -1,   120,    -1,   171,    -1,   172,    -1,
     175,    -1,   176,    -1,   177,    -1,   178,    -1,   179,    -1,
     180,    -1,   181,    -1,   182,    -1,   183,    -1,   184,    -1,
     185,    -1,   186,    -1,   187,    -1,   188,    -1,   189,    -1,
     190,    -1,   191,    -1,   192,    -1,   212,    -1,   213,    -1,
     214,    -1,   215,    -1,   203,    -1,   205,    -1,   205,   206,
       5,    -1,   204,    -1,   204,   206,     5,    -1,   109,     4,
      -1,   193,     4,    -1,   193,     5,    -1,   202,     4,    -1,
     202,     5,    -1,   252,     4,    -1,   252,     5,    -1,   108,
       5,    -1,   194,     4,     4,    -1,   195,   347,    -1,   198,
     347,    -1,   199,   347,    -1,   196,   347,    -1,   197,   347,
      -1,   210,    29,    -1,   210,   211,    -1,    16,     4,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   352,   352,   352,   357,   358,   362,   363,   367,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
     379,   380,   392,   402,   413,   413,   418,   419,   423,   424,
     428,   428,   438,   439,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     475,   490,   511,   511,   516,   517,   521,   522,   526,   527,
     531,   531,   536,   537,   541,   542,   546,   547,   551,   551,
     566,   567,   571,   572,   573,   574,   575,   576,   577,   578,
     579,   580,   581,   582,   583,   584,   585,   586,   587,   588,
     589,   590,   594,   595,   599,   600,   604,   620,   621,   622,
     604,   633,   651,   652,   653,   654,   655,   656,   660,   661,
     662,   663,   664,   665,   666,   667,   668,   669,   673,   676,
     679,   686,   687,   688,   692,   693,   697,   698,   702,   709,
     702,   732,   759,   768,   769,   770,   774,   806,   807,   808,
     812,   830,   837,   812,   879,   879,   895,   895,   909,   909,
     918,   918,   935,   935,   953,   953,   962,   963,   967,   968,
     972,   981,   981,   990,   991,   995,   996,  1000,  1009,  1011,
    1016,  1023,  1028,  1033,  1038,  1047,  1052,  1057,  1062,  1067,
    1072,  1077,  1082,  1084,  1086,  1093,  1094,  1095,  1096,  1097,
    1098,  1099,  1100,  1101,  1102,  1103,  1104,  1105,  1106,  1107,
    1108,  1109,  1110,  1111,  1112,  1113,  1114,  1118,  1119,  1123,
    1124,  1128,  1134,  1142,  1143,  1147,  1148,  1149,  1153,  1154,
    1155,  1156,  1184,  1185,  1198,  1211,  1227,  1228,  1229,  1230,
    1231,  1236,  1241,  1247,  1253,  1264,  1265,  1266,  1267,  1268,
    1279,  1290,  1296,  1302,  1308,  1309,  1310,  1311,  1312,  1326,
    1331,  1332,  1333,  1334,  1335,  1336,  1341,  1346,  1353,  1360,
    1365,  1366,  1367,  1368,  1369,  1370,  1371,  1372,  1377,  1382,
    1392,  1393,  1398,  1399,  1400,  1401,  1402,  1403,  1404,  1405,
    1406,  1411,  1418,  1418,  1421,  1421,  1432,  1432,  1447,  1453,
    1454,  1455,  1456,  1457,  1458,  1459,  1460,  1461,  1462,  1463,
    1464,  1465,  1466,  1467,  1468,  1469,  1470,  1471,  1472,  1473,
    1474,  1475,  1476,  1477,  1478,  1479,  1480,  1481,  1482,  1483,
    1484,  1485,  1486,  1487,  1488,  1489,  1490,  1491,  1492,  1493,
    1494,  1495,  1496,  1497,  1498,  1499,  1500,  1501,  1502,  1503,
    1504,  1505,  1506,  1507,  1508,  1509,  1510,  1511,  1512,  1513,
    1514,  1515,  1516,  1517,  1518,  1519,  1520,  1521,  1522,  1523,
    1524,  1525,  1526,  1527,  1528,  1529,  1530,  1531,  1532,  1534,
    1539,  1545,  1552,  1558,  1565,  1571,  1577,  1583,  1589,  1595,
    1601,  1607,  1613,  1620,  1626,  1632,  1638,  1644,  1650,  1656,
    1662
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MOVIENAME", "STRING", "INTEGER", "HEX",
  "FLOAT", "DOUBLE", "TRUEVAL", "FALSEVAL", "NULLVAL", "UNDEFVAL",
  "REGISTER", "REGISTERALIAS", "LABEL", "MOVIE", "COMPRESSED", "PROTECT",
  "SCRIPTLIMITS", "RECURSION", "TIMEOUT", "ENABLEDEBUGGER",
  "ENABLEDEBUGGER2", "FRAME", "PLACEMOVIECLIP", "DEFINEMOVIECLIP",
  "INITMOVIECLIP", "DEFINEBUTTON", "ON", "ONCLIPEVENT", "AS",
  "IMPORTASSETS", "EXPORTASSETS", "FROM", "_NAN", "POSITIVE_INFINITY",
  "NEGATIVE_INFINITY", "_NANF", "POSITIVE_INFINITYF", "NEGATIVE_INFINITYF",
  "BIDLETOOVERUP", "BOVERUPTOIDLE", "BOVERUPTOOVERDOWN",
  "BOVERDOWNTOOVERUP", "BOVERDOWNTOOUTDOWN", "BOUTDOWNTOOVERDOWN",
  "BOUTDOWNTOIDLE", "BIDLETOOVERDOWN", "BOVERDOWNTOIDLE", "KEYPRESS",
  "_LEFT", "_RIGHT", "_HOME", "_END", "_INSERT", "_DELETE", "_BACKSPACE",
  "_ENTER", "_UP", "_DOWN", "_PGUP", "_PGDN", "_TAB", "_ESCAPE", "_SPACE",
  "MCLOAD", "MCENTERFRAME", "MCUNLOAD", "MCMOUSEMOVE", "MCMOUSEDOWN",
  "MCMOUSEUP", "MCKEYDOWN", "MCKEYUP", "MCINITIALIZE", "MCCONSTRUCT",
  "MCDATA", "MCPRESS", "MCRELEASE", "MCRELEASEOUTSIDE", "MCROLLOVER",
  "MCROLLOUT", "MCDRAGOVER", "MCDRAGOUT", "X_PROPERTY", "Y_PROPERTY",
  "XSCALE_PROPERTY", "YSCALE_PROPERTY", "WIDTH_PROPERTY",
  "HEIGHT_PROPERTY", "ALPHA_PROPERTY", "VISIBLE_PROPERTY",
  "ROTATION_PROPERTY", "CURRENTFRAME_PROPERTY", "TOTALFRAMES_PROPERTY",
  "TARGET_PROPERTY", "FRAMESLOADED_PROPERTY", "NAME_PROPERTY",
  "DROPTARGET_PROPERTY", "URL_PROPERTY", "QUALITY_PROPERTY",
  "XMOUSE_PROPERTY", "YMOUSE_PROPERTY", "HIGHQUALITY_PROPERTY",
  "FOCUSRECT_PROPERTY", "SOUNDBUFTIME_PROPERTY", "NEXTFRAME", "PREVFRAME",
  "GOTOFRAME", "GOTOLABEL", "PLAY", "STOP", "TOGGLEQUALITY", "STOPSOUNDS",
  "FUNCTION", "FUNCTION2", "CONSTANTS", "END", "DUP", "SWAP", "POP",
  "WITH", "PUSH", "SETREGISTER", "CALLFUNCTION", "RETURN", "NEWMETHOD",
  "CALLMETHOD", "BITWISEAND", "BITWISEOR", "BITWISEXOR", "MODULO",
  "NEWADD", "NEWLESSTHAN", "NEWEQUALS", "TONUMBER", "TOSTRING",
  "INCREMENT", "DECREMENT", "TYPEOF", "TARGETPATH", "ENUMERATE",
  "ENUMERATEVALUE", "INSTANCEOF", "DELETE", "DELETE2", "NEW", "INITARRAY",
  "INITOBJECT", "GETMEMBER", "SETMEMBER", "SHIFTLEFT", "SHIFTRIGHT",
  "SHIFTRIGHT2", "VAR", "VAREQUALS", "OLDADD", "SUBTRACT", "MULTIPLY",
  "DIVIDE", "OLDEQUALS", "OLDLESSTHAN", "STRICTEQUALS", "GREATERTHAN",
  "LOGICALAND", "LOGICALOR", "LOGICALNOT", "STRINGEQ", "STRINGLENGTH",
  "SUBSTRING", "INT", "GETVARIABLE", "SETVARIABLE", "SETTARGET",
  "SETTARGETEXPR", "STRINGCONCAT", "GETPROPERTY", "SETPROPERTY",
  "DUPLICATECLIP", "REMOVECLIP", "TRACE", "STARTDRAGMOVIE",
  "STOPDRAGMOVIE", "STRINGLESSTHAN", "STRINGGREATERTHAN", "RANDOM",
  "MBLENGTH", "ORD", "CHR", "GETTIMER", "MBSUBSTRING", "MBORD", "MBCHR",
  "BRANCHALWAYS", "GETURL", "GETURL2", "LOADMOVIE", "LOADMOVIENUM",
  "LOADVARIABLES", "LOADVARIABLESNUM", "POST", "GET", "BRANCHIFTRUE",
  "CALLFRAME", "GOTOANDPLAY", "GOTOANDSTOP", "SKIP", "IFFRAMELOADEDEXPR",
  "IFFRAMELOADED", "ELSE", "STRICTMODE", "OFF", "IMPLEMENTS", "EXTENDS",
  "THROW", "CAST", "TRY", "CATCH", "FINALLY", "EQUALSIGN", "PUSHONE",
  "PUSHZERO", "PUSHTRUE", "PUSHFALSE", "PUSHBYTE", "PUSHSHORT", "PUSHLONG",
  "PUSHS", "PUSHSDB", "PUSHSDW", "CALLFP", "CALLFSV", "CALLMP", "CALLMSV",
  "PUSHSDBGV", "PUSHSDBGM", "PUSHTHIS", "PUSHGLOBAL", "PUSHNULL",
  "PUSHUNDEF", "DCALLFP", "DCALLFSV", "DCALLMP", "DCALLMSV", "PUSHFLOAT",
  "PUSHTHISGV", "PUSHGLOBALGV", "PUSHSGV", "PUSHSGM", "PUSHZEROSV",
  "PUSHSSV", "PUSHSSM", "BRANCHIFFALSE", "APTTRACESTART", "PUSHREGISTER",
  "SWFACTION", "HEXDATA", "'('", "')'", "','", "':'", "'\"'", "'.'",
  "$accept", "program", "@1", "actionblocks_opt", "actionblocks",
  "actionblock", "frame", "initmc", "definebutton", "@2",
  "buttoneventblocks_opt", "buttoneventblocks", "buttoneventblock", "@3",
  "buttonevents", "buttonevent", "key", "register", "definemc", "@4",
  "mcblocks_opt", "mcblocks", "mcblock", "placemc", "@5", "mcname_opt",
  "mceventblocks_opt", "mceventblocks", "mceventblock", "@6", "mcevents",
  "mcevent", "catch_opt", "finally_opt", "trycatchfinally", "@7", "@8",
  "@9", "@10", "statements", "statement", "statementOptimized",
  "statementScanned", "label", "function_args", "statements_opt",
  "name_opt", "function", "@11", "@12", "regarg", "regarglist",
  "autoregarg", "autoregarglist", "function2", "@13", "@14", "@15", "with",
  "@16", "settarget", "@17", "settargetexpression", "@18",
  "ifframeloadedexpression", "@19", "ifframeloaded", "@20", "impassets",
  "@21", "impassetsblocks_opt", "impassetsblocks", "impassetsblock",
  "expassets", "@22", "expassetsblocks_opt", "expassetsblocks",
  "expassetsblock", "push_item", "property", "push_list", "constant_list",
  "hex_list", "hexdata_opt", "urlmethod", "opcodeOptimized",
  "opcodeScanned", "opcode", "@23", "@24", "@25", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned short int yyr1[] =
{
       0,   263,   265,   264,   266,   266,   267,   267,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   269,   270,   272,   271,   273,   273,   274,   274,
     276,   275,   277,   277,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     280,   280,   282,   281,   283,   283,   284,   284,   285,   285,
     287,   286,   288,   288,   289,   289,   290,   290,   292,   291,
     293,   293,   294,   294,   294,   294,   294,   294,   294,   294,
     294,   294,   294,   294,   294,   294,   294,   294,   294,   294,
     294,   294,   295,   295,   296,   296,   298,   299,   300,   301,
     297,   297,   302,   302,   302,   302,   302,   302,   303,   303,
     303,   303,   303,   303,   303,   303,   303,   303,   304,   305,
     306,   307,   307,   307,   308,   308,   309,   309,   311,   312,
     310,   313,   313,   314,   314,   314,   315,   316,   316,   316,
     318,   319,   320,   317,   322,   321,   324,   323,   326,   325,
     328,   327,   330,   329,   332,   331,   333,   333,   334,   334,
     335,   337,   336,   338,   338,   339,   339,   340,   341,   341,
     341,   341,   341,   341,   341,   341,   341,   341,   341,   341,
     341,   341,   341,   341,   341,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   342,   342,   343,   343,   344,
     344,   345,   345,   346,   346,   347,   347,   347,   348,   348,
     348,   348,   348,   348,   348,   348,   348,   348,   348,   348,
     348,   348,   348,   348,   348,   348,   348,   348,   348,   348,
     348,   348,   348,   348,   348,   348,   348,   348,   348,   349,
     349,   349,   349,   349,   349,   349,   349,   349,   349,   349,
     349,   349,   349,   349,   349,   349,   349,   349,   349,   349,
     349,   349,   349,   349,   349,   349,   349,   349,   349,   349,
     349,   349,   351,   350,   352,   350,   353,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     5,     0,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       2,     5,     4,     4,     0,     5,     0,     1,     1,     2,
       0,     5,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     5,     0,     1,     1,     2,     1,     1,
       0,     6,     0,     2,     0,     1,     1,     2,     0,     5,
       1,     3,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     0,     2,     0,     2,     0,     0,     0,     0,
      10,     2,     1,     2,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     3,     0,     1,     0,     1,     0,     0,
       9,     3,     1,     0,     1,     3,     3,     0,     1,     3,
       0,     0,     0,    13,     0,     4,     0,     5,     0,     4,
       0,     4,     0,     5,     0,     6,     0,     1,     1,     2,
       3,     0,     4,     0,     1,     1,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     1,     3,     0,     2,     0,     1,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       2,     2,     3,     3,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     0,     3,     0,     3,     0,     4,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     2,     2,     2,     2,     2,     2,     2,
       2
};

/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none). */
static const unsigned char yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     5,     1,    20,    15,    10,     8,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      21,    21,    22,    22,     0,     0,     0,     0,     0,    40,
      21,    40,    40,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM. */
static const unsigned char yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error.  */
static const unsigned short int yydefact[] =
{
       0,     0,     0,     2,     1,     4,    15,    16,     0,    18,
       0,     0,     0,     0,     0,     0,     0,   171,     0,     5,
       6,     8,    12,     9,    10,    11,    13,    14,    17,     0,
      19,    20,   134,    72,    62,   134,    24,     0,   173,     3,
       7,     0,   130,     0,   303,   304,     0,     0,   305,   306,
     307,   308,   136,   136,   292,   352,   353,   354,   154,   294,
       0,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   301,
     302,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   299,
     300,   345,   346,   347,   348,   349,   350,   351,   355,   356,
       0,   158,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
       0,     0,   225,   225,   225,   225,   225,     0,   379,   382,
     380,   160,     0,     0,   375,   376,   377,   378,   136,   271,
     272,   262,   263,     0,     0,     0,     0,     0,     0,   282,
     285,   286,   287,     0,     0,   288,   289,   260,   261,     0,
       0,     0,     0,     0,   283,   284,     0,     0,   264,     0,
       0,     0,   280,     0,     0,   126,   135,   112,   114,   115,
     118,     0,   119,   120,   121,   122,   123,   125,   124,   128,
     129,   127,     0,    70,    64,     0,    26,   164,     0,     0,
     174,   175,     0,   400,   391,   384,   137,   138,   150,     0,
     134,   232,   231,   233,   234,   256,   257,   254,   255,   235,
       0,    60,    61,   298,   245,   246,   247,   248,   258,   156,
     134,   385,   386,     0,   227,   226,   393,   396,   397,   394,
     395,   387,   388,     0,     0,   134,   162,   398,   399,   111,
     106,   228,   259,   265,   266,   270,   241,   240,   244,   290,
     229,   230,   277,   278,   279,   281,   267,   268,   273,   274,
     275,   276,   389,   390,   269,   296,   113,   116,   117,    22,
      73,    74,    68,     0,    65,    66,    69,    23,    30,     0,
      27,    28,   166,     0,   172,   176,    21,     0,     0,   219,
     293,     0,   178,   185,   184,   180,   186,   190,   191,   192,
     193,   187,   188,   189,   181,   182,   183,   195,   196,   197,
     198,   203,   204,   201,   202,   205,   199,   200,   206,   207,
     208,   209,   210,   214,   215,   216,   211,   212,   213,   194,
     217,   179,   295,   134,     0,   392,   383,   381,     0,   134,
     134,   237,   239,   236,   238,   243,   242,   249,   251,   252,
     253,   250,   223,    82,     0,    75,    76,    63,    67,     0,
      25,    29,     0,     0,   167,   168,   177,   131,   143,     0,
     155,     0,     0,   159,   161,     0,   107,     0,   297,     0,
      83,    84,    85,    86,    87,    88,    89,    90,    92,   101,
      91,    93,    94,    95,    96,    97,    98,    99,    78,    80,
      71,    77,    34,    35,    36,    37,    38,    39,    40,    41,
      42,     0,   134,    32,     0,   165,   169,   132,     0,   142,
       0,   144,     0,   220,   218,   157,   163,   102,   221,   224,
      59,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,   100,    82,   134,    43,
       0,     0,   170,   139,     0,     0,   151,     0,   134,   108,
       0,    81,     0,    33,    31,   134,   133,   141,     0,   145,
     103,   104,   222,    79,     0,   147,   134,   109,   140,     0,
     148,     0,   105,     0,     0,   152,     0,   110,   146,   134,
     149,     0,   153
};

/* YYPDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     2,     5,    18,    19,    20,    21,    22,    23,   206,
     299,   300,   301,   379,   432,   433,   466,   349,    24,   204,
     293,   294,   295,    25,   291,   203,   374,   375,   376,   468,
     418,   419,   479,   497,   185,   360,   447,   491,   503,   186,
     187,   188,   189,   190,   438,   191,   217,   192,   307,   485,
     441,   442,   500,   501,   193,   308,   488,   509,   194,   220,
     195,   353,   196,   240,   197,   255,   198,   359,    26,   302,
     383,   384,   385,    27,    38,   209,   210,   211,   350,   351,
     352,   310,   449,   398,   246,   199,   200,   201,   219,   230,
     372
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -233
static const short int yypact[] =
{
       1,    26,    22,  -233,  -233,    29,  -233,    41,    40,    45,
     139,   160,   161,   162,   163,   164,   136,  -233,    55,    29,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,   166,
    -233,  -233,   727,   142,  -233,   727,  -233,   170,   171,  -233,
    -233,   154,  -233,   173,  -233,  -233,   174,   176,  -233,  -233,
    -233,  -233,   177,   177,  -233,  -233,  -233,  -233,  -233,   137,
      11,   -94,  -233,  -233,   -93,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,    16,  -233,  -233,  -233,  -233,  -233,  -233,
     180,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
      35,   182,  -157,  -157,  -157,  -157,  -157,    54,  -233,   -19,
     -18,  -233,   184,   -28,  -233,  -233,  -233,  -233,    17,  -233,
       6,  -233,  -233,   185,   186,   187,   189,   190,   191,  -233,
    -233,  -233,  -233,   192,   193,    23,    28,  -233,  -233,   195,
     196,   197,   198,    73,  -233,  -233,   200,   202,  -233,   203,
     204,   151,  -233,   205,   206,  -233,   727,  -233,  -233,  -233,
    -233,    92,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,   207,  -233,   133,    96,   188,  -233,   183,    98,
     171,  -233,   211,  -233,  -233,  -233,  -233,  -233,  -233,   214,
     727,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
      -2,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
     727,  -233,  -233,   215,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,   216,   217,   727,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -130,  -121,    -7,   542,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,   194,  -233,   108,   133,  -233,  -233,  -233,  -233,   109,
     188,  -233,   223,   224,  -233,  -233,  -233,   -27,   -26,  -233,
     -30,   115,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,   -25,   727,   116,  -233,  -233,  -233,   118,   727,
     727,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,   -20,    57,   120,   194,  -233,  -233,  -233,    72,
    -233,  -233,   208,   121,   223,  -233,  -233,   236,    19,   237,
    -233,    -2,   125,  -233,  -233,   126,  -233,   238,  -233,    12,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,   -14,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,    12,   357,  -233,   241,  -233,  -233,  -233,   -99,  -233,
      30,  -233,   -97,  -233,  -233,  -233,  -233,    31,  -233,   -12,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,    57,   727,  -233,
      72,   134,  -233,  -233,   246,   248,  -233,    19,   727,  -233,
     247,  -233,   138,  -233,  -233,   727,  -233,  -233,    -3,  -233,
    -233,    38,  -233,  -233,   140,   245,   727,  -233,  -233,    42,
    -233,   -95,  -233,   143,   255,  -233,   245,  -233,  -233,   727,
    -233,   145,  -233
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -233,  -233,  -233,  -233,  -233,   244,  -190,  -233,  -233,  -233,
    -233,  -233,   -36,  -233,  -233,  -205,  -165,   -42,  -233,  -233,
    -233,  -233,   -24,  -189,  -233,  -233,  -233,  -233,  -108,  -233,
    -233,  -199,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
      83,    85,    86,  -233,  -233,   -35,   -40,  -233,  -233,  -233,
    -204,  -233,  -232,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -109,  -233,  -233,  -233,  -233,    66,  -114,  -233,
    -233,  -233,  -233,  -233,    18,  -233,  -233,  -233,  -233,  -233,
    -233
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -245
static const short int yytable[] =
{
     205,   257,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   231,   232,   218,   292,   296,   450,     1,   233,   361,
     362,   216,     4,   439,   231,   232,   234,   236,   365,     3,
     231,   232,   440,   321,   322,   323,   324,   325,   326,   241,
     242,   363,   364,   244,   245,    28,     6,     7,     8,    30,
     366,     9,    10,    11,    12,    13,    14,    15,   251,   252,
      29,    16,    17,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   460,   461,   462,   463,   464,   465,   235,   237,
     276,   277,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   292,   296,   259,   399,   260,   367,
     368,   369,   370,   422,   423,   424,   425,   426,   427,   428,
     429,   430,   431,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   411,   412,   413,   414,   415,   416,
     417,   221,   222,    31,   223,   224,   225,   226,   227,   228,
     229,   247,   248,   249,   250,   282,   283,    11,    12,   473,
     474,   476,   477,   505,   506,    32,    33,    34,    35,    36,
      37,    41,    39,   202,   207,   212,   208,   213,   261,   214,
     215,   216,   238,   258,   239,   311,   243,   253,   254,   256,
     262,   263,   264,   265,   270,   266,   267,   268,   269,   271,
     272,   273,   274,   275,   278,   354,   279,   280,   281,   289,
     284,   290,   285,   297,   303,   304,   306,   298,   309,   355,
     358,   356,   357,   371,   373,   377,   380,   382,   386,   389,
     387,   388,   390,   393,   391,   394,   397,   420,   435,   434,
     437,   443,   445,   446,   448,   467,   472,   480,   478,   475,
     486,   484,   487,   492,   495,   493,   496,   498,   499,   508,
     507,   504,   512,    40,   381,   483,   469,   421,   481,   286,
     378,   287,   288,   489,   510,   436,   305,   444,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   392,     0,
       0,     0,     0,     0,   395,   396,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    42,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   471,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   482,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   490,     0,     0,     0,     0,     0,     0,
     494,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   502,     0,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,   511,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,  -244,  -244,   137,
     138,   139,   140,     0,   141,   142,     0,   143,     0,   144,
     145,   146,   147,   148,     0,     0,     0,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,     0,     0,     0,   470,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,    42,    43,  -244,  -244,  -244,  -244,     0,  -244,
    -244,     0,  -244,     0,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,     0,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,     0,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,     0,     0,   137,
     138,   139,   140,     0,   141,   142,     0,   143,     0,   144,
     145,   146,   147,   148,     0,     0,     0,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned short int yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
      37,     0,     0,     0,     0,     0,    19,    23,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    39,    41,     0,     0,     0,     0,     0,     0,     0,
      45,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,    25,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    47,
      49,    51,    53,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     3,     0,     5,     7,     9,    11,    13,    15,
      17,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,     0,
       0,     0,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    31,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    55,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    57,    59,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,    63,
      65,    67,    69,    71,    73,    75,    77,    79,    81,    83,
      85,    87,    89,    91,    93,    95,    97,    99,   101,   103,
     105,   107,   109,   111,   113,   115,   117,   119,   121,   123,
     125,   127,   129,   131,   133,   135,   137,   139,   141,   143,
     145,   147,   149,   151,   153,   155,   157,   159,   161,   163,
     165,   167,   169,   171,   173,   175,   177,   179,   181,   183,
     185,   187,   189,   191,   193,   195,   197,   199,   201,   203,
     205,   207,   209,   211,   213,   215,   217,   219,   221,   223,
     225,   227,   229,   231,   233,   235,   237,   239,   241,   243,
     245,   247,     0,     0,   249,   251,   253,   255,     0,   257,
     259,     0,   261,     0,   263,   265,   267,   269,   271,   273,
     275,     0,   277,   279,   281,   283,   285,   287,   289,   291,
     293,   295,   297,   299,   301,   303,   305,   307,   309,   311,
     313,   315,   317,   319,   321,   323,   325,   327,   329,   331,
     333,   335,   337,   339,   341,   343,   345,   347,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short int yyconfl[] =
{
       0,   294,     0,   294,     0,   294,     0,   294,     0,   294,
       0,   294,     0,   294,     0,   294,     0,   294,     0,   309,
       0,   309,     0,   312,     0,   312,     0,   347,     0,   272,
       0,   288,     0,   289,     0,   270,     0,   270,     0,   270,
       0,   270,     0,   241,     0,   241,     0,   241,     0,   241,
       0,   241,     0,   241,     0,   240,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0,   291,
       0,   291,     0,   291,     0,   291,     0,   291,     0
};

static const short int yycheck[] =
{
      35,    29,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    53,   204,   204,     4,    16,    60,   149,
     150,     4,     0,     4,    13,    14,   120,   120,   149,     3,
      13,    14,    13,    35,    36,    37,    38,    39,    40,     4,
       5,   171,   172,   200,   201,     4,    17,    18,    19,     4,
     171,    22,    23,    24,    25,    26,    27,    28,     4,     5,
      20,    32,    33,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,   172,   172,
       7,     8,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   294,   294,   148,    50,   148,   230,
     231,   232,   233,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,     4,     5,     4,     7,     8,     9,    10,    11,    12,
      13,   133,   134,   135,   136,     4,     5,    24,    25,   258,
     259,   258,   259,   258,   259,     5,     5,     5,     5,     5,
      34,     5,   117,    31,     4,    21,     5,     4,   172,     5,
       4,     4,   166,   211,     4,   220,     4,   206,   206,     5,
       5,     5,     5,     4,   171,     5,     5,     5,     5,   171,
       5,     5,     5,     5,     4,   240,     4,     4,     4,   117,
       5,     4,     6,   117,    31,   117,     5,    29,     4,     4,
     255,     5,     5,   230,    30,   117,   117,     4,     4,   259,
     257,   257,   117,   117,   259,   117,   256,   117,   117,    31,
       4,     4,   117,   117,     6,   259,     5,   259,   217,   219,
       4,   117,     4,     6,   257,   117,   218,   117,    13,     4,
     117,   219,   117,    19,   300,   470,   431,   375,   467,   186,
     294,   186,   186,   477,   506,   384,   210,   391,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   353,    -1,
      -1,    -1,    -1,    -1,   359,   360,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   432,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   468,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   478,    -1,    -1,    -1,    -1,    -1,    -1,
     485,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   496,    -1,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   509,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,    15,    16,   202,
     203,   204,   205,    -1,   207,   208,    -1,   210,    -1,   212,
     213,   214,   215,   216,    -1,    -1,    -1,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,    -1,    -1,    -1,   259,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,    15,    16,   202,   203,   204,   205,    -1,   207,
     208,    -1,   210,    -1,   212,   213,   214,   215,   216,   217,
     218,    -1,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,    -1,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,    -1,    -1,   202,
     203,   204,   205,    -1,   207,   208,    -1,   210,    -1,   212,
     213,   214,   215,   216,    -1,    -1,    -1,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned short int yystos[] =
{
       0,    16,   264,     3,     0,   265,    17,    18,    19,    22,
      23,    24,    25,    26,    27,    28,    32,    33,   266,   267,
     268,   269,   270,   271,   281,   286,   331,   336,     4,    20,
       4,     4,     5,     5,     5,     5,     5,    34,   337,   117,
     268,     5,    15,    16,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   202,   203,   204,
     205,   207,   208,   210,   212,   213,   214,   215,   216,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   297,   302,   303,   304,   305,
     306,   308,   310,   317,   321,   323,   325,   327,   329,   348,
     349,   350,    31,   288,   282,   308,   272,     4,     5,   338,
     339,   340,    21,     4,     5,     4,     4,   309,   309,   351,
     322,     4,     5,     7,     8,     9,    10,    11,    12,    13,
     352,    13,    14,   280,   120,   172,   120,   172,   166,     4,
     326,     4,     5,     4,   200,   201,   347,   347,   347,   347,
     347,     4,     5,   206,   206,   328,     5,    29,   211,   280,
     309,   172,     5,     5,     5,     4,     5,     5,     5,     5,
     171,   171,     5,     5,     5,     5,     7,     8,     4,     4,
       4,     4,     4,     5,     5,     6,   303,   304,   305,   117,
       4,   287,   269,   283,   284,   285,   286,   117,    29,   273,
     274,   275,   332,    31,   117,   340,     5,   311,   318,     4,
     344,   308,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    35,    36,    37,    38,    39,    40,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   280,
     341,   342,   343,   324,   308,     4,     5,     5,   308,   330,
     298,   149,   150,   171,   172,   149,   171,   230,   231,   232,
     233,   230,   353,    30,   289,   290,   291,   117,   285,   276,
     117,   275,     4,   333,   334,   335,     4,   257,   257,   259,
     117,   259,   308,   117,   117,   308,   308,   256,   346,    50,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,   293,   294,
     117,   291,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,   277,   278,    31,   117,   335,     4,   307,     4,
      13,   313,   314,     4,   341,   117,   117,   299,     6,   345,
       4,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,   279,   259,   292,   279,
     259,   308,     5,   258,   259,   219,   258,   259,   217,   295,
     259,   294,   308,   278,   117,   312,     4,     4,   319,   313,
     308,   300,     6,   117,   308,   257,   218,   296,   117,    13,
     315,   316,   308,   301,   219,   258,   259,   117,     4,   320,
     315,   308,   117
};


/* Prevent warning if -Wmissing-prototypes.  */
int yyparse (void);

/* Error token number */
#define YYTERROR 1

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */


#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N) ((void) 0)
#endif


#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#define YYLEX yylex ()

YYSTYPE yylval;

YYLTYPE yylloc;

int yynerrs;
int yychar;

static const int YYEOF = 0;
static const int YYEMPTY = -2;

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)							     \
   do { YYRESULTTAG yyflag = YYE; if (yyflag != yyok) return yyflag; }	     \
   while (0)

#if YYDEBUG

#if ! defined (YYFPRINTF)
#  define YYFPRINTF fprintf
#endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr,					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

#else /* !YYDEBUG */

# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data. */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
# if (! defined (__cplusplus) \
      || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL))
#  define YYSTACKEXPANDABLE 1
# else
#  define YYSTACKEXPANDABLE 0
# endif
#endif

#if YYERROR_VERBOSE

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static size_t
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return strlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* !YYERROR_VERBOSE */

/** State numbers, as in LALR(1) machine */
typedef int yyStateNum;

/** Rule numbers, as in LALR(1) machine */
typedef int yyRuleNum;

/** Grammar symbol */
typedef short int yySymbol;

/** Item references, as in LALR(1) machine */
typedef short int yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;
typedef struct yyGLRStateSet yyGLRStateSet;

struct yyGLRState {
  /** Type tag: always true. */
  yybool yyisState;
  /** Type tag for yysemantics. If true, yysval applies, otherwise
   *  yyfirstVal applies. */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state. */
  yyStateNum yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the first token produced by my symbol */
  size_t yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  non-terminal corresponding to this state, threaded through
     *  yynext. */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state. */
    YYSTYPE yysval;
  } yysemantics;
  /** Source location for this state. */
  YYLTYPE yyloc;
};

struct yyGLRStateSet {
  yyGLRState** yystates;
  size_t yysize, yycapacity;
};

struct yySemanticOption {
  /** Type tag: always false. */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced. */
  yyGLRState* yystate;
  /** Next sibling in chain of options. To facilitate merging,
   *  options are chained in decreasing order by address. */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack. The yyisState field
 *  indicates which item of the union is valid. */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;


  yySymbol* yytokenp;
  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  size_t yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

static void yyexpandGLRStack (yyGLRStack* yystack);

static void yyFail (yyGLRStack* yystack, const char* yymsg)
  __attribute__ ((__noreturn__));
static void
yyFail (yyGLRStack* yystack, const char* yymsg)
{
  if (yymsg != NULL)
    yyerror (yymsg);
  YYLONGJMP (yystack->yyexception_buffer, 1);
}

static void yyMemoryExhausted (yyGLRStack* yystack)
  __attribute__ ((__noreturn__));
static void
yyMemoryExhausted (yyGLRStack* yystack)
{
  YYLONGJMP (yystack->yyexception_buffer, 2);
}

#if YYDEBUG || YYERROR_VERBOSE
/** A printable representation of TOKEN.  */
static inline const char*
yytokenName (yySymbol yytoken)
{
  if (yytoken == YYEMPTY)
    return "";

  return yytname[yytoken];
}
#endif

/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain. Assumes
 *  YYLOW1 < YYLOW0.  */
static void yyfillin (yyGLRStackItem *, int, int) __attribute__ ((__unused__));
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  yyGLRState* s;
  int i;
  s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
      YYASSERT (s->yyresolved);
      yyvsp[i].yystate.yyresolved = yytrue;
      yyvsp[i].yystate.yysemantics.yysval = s->yysemantics.yysval;
      yyvsp[i].yystate.yyloc = s->yyloc;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
   YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
   For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     __attribute__ ((__unused__));
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$). Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT. */
static YYRESULTTAG
yyuserAction (yyRuleNum yyn, int yyrhslen, yyGLRStackItem* yyvsp,
	      YYSTYPE* yyvalp,
	      YYLTYPE* YYOPTIONAL_LOC (yylocp),
	      yyGLRStack* yystack
              )
{
  yybool yynormal __attribute__ ((__unused__)) =
    (yystack->yysplitPoint == NULL);
  int yylow;

# undef yyerrok
# define yyerrok (yystack->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING (yystack->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = *(yystack->yytokenp) = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, N, yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)						     \
  return yyerror (YY_("syntax error: cannot back up")),     \
	 yyerrok, yyerr

  yylow = 1;
  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yysval;
  YYLLOC_DEFAULT (*yylocp, yyvsp - yyrhslen, yyrhslen);

  switch (yyn)
    {
        case 2:
#line 352 "assembler.y"
    {   startUpdate((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));    ;}
    break;

  case 3:
#line 353 "assembler.y"
    {   finishUpdate();     ;}
    break;

  case 4:
#line 357 "assembler.y"
    {   ((*yyvalp).num) = 0;             ;}
    break;

  case 5:
#line 358 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);            ;}
    break;

  case 6:
#line 362 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);            ;}
    break;

  case 7:
#line 363 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);       ;}
    break;

  case 8:
#line 367 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 9:
#line 368 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 10:
#line 369 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 11:
#line 370 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 12:
#line 371 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 13:
#line 372 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 14:
#line 373 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 15:
#line 374 "assembler.y"
    {   compressAfter = 1;          ((*yyvalp).num) = 0; ;}
    break;

  case 16:
#line 375 "assembler.y"
    {   writeProtect("");           ((*yyvalp).num) = 0; ;}
    break;

  case 17:
#line 376 "assembler.y"
    {   writeProtect((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));           ((*yyvalp).num) = 0; ;}
    break;

  case 18:
#line 377 "assembler.y"
    {   writeEnableDebugger("");    ((*yyvalp).num) = 0; ;}
    break;

  case 19:
#line 378 "assembler.y"
    {   writeEnableDebugger((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));    ((*yyvalp).num) = 0; ;}
    break;

  case 20:
#line 379 "assembler.y"
    {   writeEnableDebugger2((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));   ((*yyvalp).num) = 0; ;}
    break;

  case 21:
#line 381 "assembler.y"
    {
                                                    if ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num)>65535)
                                                        yyerror("Recursion depth out of range");
                                                    if ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num)>65535)
                                                        yyerror("Timeout out of range");
                                                    writeScriptLimits((unsigned int)(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num), (unsigned int)(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                    ((*yyvalp).num) = 0;
                                                ;}
    break;

  case 22:
#line 392 "assembler.y"
    {
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num);
                                                    /*action end*/
                                                    ((*yyvalp).num) += writeByte(0);
                                                    writeDoAction();
                                                    ((*yyvalp).num) = 0;
                                                ;}
    break;

  case 23:
#line 403 "assembler.y"
    {
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num);
                                                    /*action end*/
                                                    ((*yyvalp).num) += writeByte(0);
                                                    writeInitMC((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num));
                                                    ((*yyvalp).num) = 0;
                                                ;}
    break;

  case 24:
#line 413 "assembler.y"
    {   writeButtonStart((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num)); ;}
    break;

  case 25:
#line 414 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num); writeButtonEnd();  ;}
    break;

  case 26:
#line 418 "assembler.y"
    {   ((*yyvalp).num) = 0;         ;}
    break;

  case 27:
#line 419 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);        ;}
    break;

  case 28:
#line 423 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);        ;}
    break;

  case 29:
#line 424 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);   ;}
    break;

  case 30:
#line 428 "assembler.y"
    {   curEvent = 0;   ;}
    break;

  case 31:
#line 429 "assembler.y"
    {
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num);
                                                    /*event action end*/
                                                    ((*yyvalp).num) += writeByte(0);
                                                    writeButtonEvent((unsigned int)curEvent);
                                                ;}
    break;

  case 32:
#line 438 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);  curEvent += (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);   ;}
    break;

  case 33:
#line 439 "assembler.y"
    {   ((*yyvalp).num) += (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num); curEvent += (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);   ;}
    break;

  case 34:
#line 443 "assembler.y"
    {   ((*yyvalp).num) = 0x01;  ;}
    break;

  case 35:
#line 444 "assembler.y"
    {   ((*yyvalp).num) = 0x02;  ;}
    break;

  case 36:
#line 445 "assembler.y"
    {   ((*yyvalp).num) = 0x04;  ;}
    break;

  case 37:
#line 446 "assembler.y"
    {   ((*yyvalp).num) = 0x08;  ;}
    break;

  case 38:
#line 447 "assembler.y"
    {   ((*yyvalp).num) = 0x10;  ;}
    break;

  case 39:
#line 448 "assembler.y"
    {   ((*yyvalp).num) = 0x20;  ;}
    break;

  case 40:
#line 449 "assembler.y"
    {   ((*yyvalp).num) = 0x40;  ;}
    break;

  case 41:
#line 450 "assembler.y"
    {   ((*yyvalp).num) = 0x80;  ;}
    break;

  case 42:
#line 451 "assembler.y"
    {   ((*yyvalp).num) = 0x100; ;}
    break;

  case 43:
#line 452 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num)<<9; ;}
    break;

  case 44:
#line 456 "assembler.y"
    {   ((*yyvalp).num) = 1;     ;}
    break;

  case 45:
#line 457 "assembler.y"
    {   ((*yyvalp).num) = 2;     ;}
    break;

  case 46:
#line 458 "assembler.y"
    {   ((*yyvalp).num) = 3;     ;}
    break;

  case 47:
#line 459 "assembler.y"
    {   ((*yyvalp).num) = 4;     ;}
    break;

  case 48:
#line 460 "assembler.y"
    {   ((*yyvalp).num) = 5;     ;}
    break;

  case 49:
#line 461 "assembler.y"
    {   ((*yyvalp).num) = 6;     ;}
    break;

  case 50:
#line 462 "assembler.y"
    {   ((*yyvalp).num) = 8;     ;}
    break;

  case 51:
#line 463 "assembler.y"
    {   ((*yyvalp).num) = 13;    ;}
    break;

  case 52:
#line 464 "assembler.y"
    {   ((*yyvalp).num) = 14;    ;}
    break;

  case 53:
#line 465 "assembler.y"
    {   ((*yyvalp).num) = 15;    ;}
    break;

  case 54:
#line 466 "assembler.y"
    {   ((*yyvalp).num) = 16;    ;}
    break;

  case 55:
#line 467 "assembler.y"
    {   ((*yyvalp).num) = 17;    ;}
    break;

  case 56:
#line 468 "assembler.y"
    {   ((*yyvalp).num) = 18;    ;}
    break;

  case 57:
#line 469 "assembler.y"
    {   ((*yyvalp).num) = 19;    ;}
    break;

  case 58:
#line 470 "assembler.y"
    {   ((*yyvalp).num) = 32;    ;}
    break;

  case 59:
#line 471 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)[0]; ;}
    break;

  case 60:
#line 475 "assembler.y"
    {
                                                    /* only 255 regs can be allocated within function2,
                                                       r:0 being the first and r:254 the last;
                                                       outside 4 global registers exist */
                                                    if ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num) >= 255)
                                                        yyerror("Register number out of range");
                                                    if ((byte)(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num) > 3 && curFunc < 0)
                                                        warning("Local registers r:4 to r:255 work in function2 context only");
                                                    /* if needed, increase the number of registers
                                                       to allocate for function2 */
                                                    if (curFunc >= 0  &&  (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num) + 1 > (long int) numRegisters[curFunc])
                                                        numRegisters[curFunc] = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num) + 1;                                               
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);
                                                ;}
    break;

  case 61:
#line 490 "assembler.y"
    {
                                                    unsigned int m;
                                                    int r = -1;
                                                    
                                                    if (curFunc >= 0) {
                                                        for(m = 1; m < numRegisters[curFunc]; ++m) {
                                                            if (regfunc_args[curFunc][m] != NULL && !strcmp((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), regfunc_args[curFunc][m])) {
                                                                r = m;
                                                                break;
                                                            }
                                                        }
                                                    }

                                                    if (r == -1)
                                                        yyerror("Register alias not found");
                                                    
                                                    ((*yyvalp).num) = r;
                                                ;}
    break;

  case 62:
#line 511 "assembler.y"
    {   writeDefineMCStart((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));   ;}
    break;

  case 63:
#line 512 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num); writeDefineMCEnd();    ;}
    break;

  case 64:
#line 516 "assembler.y"
    {   ((*yyvalp).num) = 0;     ;}
    break;

  case 65:
#line 517 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 66:
#line 521 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);        ;}
    break;

  case 67:
#line 522 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);   ;}
    break;

  case 68:
#line 526 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 69:
#line 527 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 70:
#line 531 "assembler.y"
    {   allEvents = 0;  writePlaceMCStart((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));       ;}
    break;

  case 71:
#line 532 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num);        writePlaceMCEnd(allEvents);  ;}
    break;

  case 72:
#line 536 "assembler.y"
    {   ((*yyvalp).str) = "";    ;}
    break;

  case 73:
#line 537 "assembler.y"
    {   ((*yyvalp).str) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str);    ;}
    break;

  case 74:
#line 541 "assembler.y"
    {   ((*yyvalp).num) = 0;     ;}
    break;

  case 75:
#line 542 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 76:
#line 546 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);      ;}
    break;

  case 77:
#line 547 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num); ;}
    break;

  case 78:
#line 551 "assembler.y"
    {
                                                    curEvent = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);
                                                    allEvents |= curEvent;
                                                ;}
    break;

  case 79:
#line 556 "assembler.y"
    {
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num);
                                                    /*event action end*/
                                                    ((*yyvalp).num) += writeByte(0);
                                                    writeOnClipEvent(curEvent);
                                                    curEvent = 0;
                                                ;}
    break;

  case 80:
#line 566 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    curEvent += (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num); ;}
    break;

  case 81:
#line 567 "assembler.y"
    {   ((*yyvalp).num) += (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);   curEvent += (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num); ;}
    break;

  case 82:
#line 571 "assembler.y"
    {   yyerror("Missing mc event condition"); ;}
    break;

  case 83:
#line 572 "assembler.y"
    {   ((*yyvalp).num) = 0x01;      ;}
    break;

  case 84:
#line 573 "assembler.y"
    {   ((*yyvalp).num) = 0x02;      ;}
    break;

  case 85:
#line 574 "assembler.y"
    {   ((*yyvalp).num) = 0x04;      ;}
    break;

  case 86:
#line 575 "assembler.y"
    {   ((*yyvalp).num) = 0x08;      ;}
    break;

  case 87:
#line 576 "assembler.y"
    {   ((*yyvalp).num) = 0x10;      ;}
    break;

  case 88:
#line 577 "assembler.y"
    {   ((*yyvalp).num) = 0x20;      ;}
    break;

  case 89:
#line 578 "assembler.y"
    {   ((*yyvalp).num) = 0x40;      ;}
    break;

  case 90:
#line 579 "assembler.y"
    {   ((*yyvalp).num) = 0x80;      ;}
    break;

  case 91:
#line 580 "assembler.y"
    {   ((*yyvalp).num) = 0x100;     ;}
    break;

  case 92:
#line 581 "assembler.y"
    {   ((*yyvalp).num) = 0x200;     ;}
    break;

  case 93:
#line 582 "assembler.y"
    {   ((*yyvalp).num) = 0x400;     ;}
    break;

  case 94:
#line 583 "assembler.y"
    {   ((*yyvalp).num) = 0x800;     ;}
    break;

  case 95:
#line 584 "assembler.y"
    {   ((*yyvalp).num) = 0x1000;    ;}
    break;

  case 96:
#line 585 "assembler.y"
    {   ((*yyvalp).num) = 0x2000;    ;}
    break;

  case 97:
#line 586 "assembler.y"
    {   ((*yyvalp).num) = 0x4000;    ;}
    break;

  case 98:
#line 587 "assembler.y"
    {   ((*yyvalp).num) = 0x8000;    ;}
    break;

  case 99:
#line 588 "assembler.y"
    {   ((*yyvalp).num) = 0x10000;   ;}
    break;

  case 100:
#line 589 "assembler.y"
    {   ((*yyvalp).num) = 0x20000; writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));    ;}
    break;

  case 101:
#line 590 "assembler.y"
    {   ((*yyvalp).num) = 0x40000;   ;}
    break;

  case 102:
#line 594 "assembler.y"
    {   ((*yyvalp).num) = 0;     ;}
    break;

  case 103:
#line 595 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 104:
#line 599 "assembler.y"
    {   ((*yyvalp).num) = 0;     ;}
    break;

  case 105:
#line 600 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 106:
#line 604 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_TRY);
                                                    /* action length */
                                                    ((*yyvalp).num) += writeShort(strlen((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str))+8);
                                                    /* zero flag */
                                                    ((*yyvalp).num) += writeByte(0);
                                                    /* zero try length */
                                                    ((*yyvalp).num) += writeShort(0);
                                                    /* zero catch length */
                                                    ((*yyvalp).num) += writeShort(0);
                                                    /* zero finally length */
                                                    ((*yyvalp).num) += writeShort(0);
                                                    /* error variable name */
                                                    ((*yyvalp).num) += writeString((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));
                                                ;}
    break;

  case 107:
#line 620 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num); patchLength(((*yyvalp).num) - 6,  (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));    ;}
    break;

  case 108:
#line 621 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num); patchLength(((*yyvalp).num) - 8,  (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));    ;}
    break;

  case 109:
#line 622 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num); patchLength(((*yyvalp).num) - 10, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));    ;}
    break;

  case 110:
#line 623 "assembler.y"
    {
                                                    byte flag = 0;
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num);
                                                    if ((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.num)>0)
                                                        flag = flag + 1;
                                                    if ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num)>0)
                                                        flag = flag + 2;
                                                    patchFlag(((*yyvalp).num) - 4, flag);
                                                ;}
    break;

  case 111:
#line 633 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_TRY);
                                                    /* action length */
                                                    ((*yyvalp).num) += writeShort(8);
                                                    /* zero flag */
                                                    ((*yyvalp).num) += writeByte(0);
                                                    /* zero try length */
                                                    ((*yyvalp).num) += writeShort(0);
                                                    /* zero catch length */
                                                    ((*yyvalp).num) += writeShort(0);
                                                    /* zero finally length */
                                                    ((*yyvalp).num) += writeShort(0);
                                                    /* error register number */
                                                    ((*yyvalp).num) += writeByte((byte) (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 112:
#line 651 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);        ;}
    break;

  case 113:
#line 652 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);   ;}
    break;

  case 114:
#line 653 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);        ;}
    break;

  case 115:
#line 654 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);        ;}
    break;

  case 116:
#line 655 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);   ;}
    break;

  case 117:
#line 656 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);   ;}
    break;

  case 118:
#line 660 "assembler.y"
    {   ((*yyvalp).num) = 0;     ;}
    break;

  case 119:
#line 661 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 120:
#line 662 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 121:
#line 663 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 122:
#line 664 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 123:
#line 665 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 124:
#line 666 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 125:
#line 667 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 126:
#line 668 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 127:
#line 669 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 128:
#line 673 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 129:
#line 676 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 130:
#line 679 "assembler.y"
    {   addLabel((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));   ;}
    break;

  case 131:
#line 686 "assembler.y"
    {   ((*yyvalp).num) = 0; ;}
    break;

  case 132:
#line 687 "assembler.y"
    {   func_args[0] = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str);  ((*yyvalp).num) = 1;         ;}
    break;

  case 133:
#line 688 "assembler.y"
    {   func_args[(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num)] = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str); ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) + 1;    ;}
    break;

  case 134:
#line 692 "assembler.y"
    {   ((*yyvalp).num) = 0;     ;}
    break;

  case 135:
#line 693 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 136:
#line 697 "assembler.y"
    {   ((*yyvalp).str) = "";    ;}
    break;

  case 137:
#line 698 "assembler.y"
    {   ((*yyvalp).str) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str);    ;}
    break;

  case 138:
#line 702 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_DEFINEFUNCTION);
                                                    /* zero block length */
                                                    ((*yyvalp).num) += writeShort(0);
                                                    ((*yyvalp).num) += writeString((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));
                                                ;}
    break;

  case 139:
#line 709 "assembler.y"
    {
                                                    unsigned int i;
                                                    numArgs = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num);

                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num) + writeShort(numArgs);

                                                    for(i = 0; i < numArgs; ++i)
                                                        ((*yyvalp).num) += writeString(func_args[i]);

                                                    /* zero function length */
                                                    ((*yyvalp).num) += writeShort(0);
                                                    /* patch block length */
                                                    patchLength(((*yyvalp).num)-3, ((*yyvalp).num)-3);
                                                ;}
    break;

  case 140:
#line 724 "assembler.y"
    {
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num);
                                                    /* patch function length */
                                                    patchLength((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 141:
#line 732 "assembler.y"
    {
                                                    numArgs++;
                                                    ((*yyvalp).num) = writeByte((byte) (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num));

                                                    if ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) == 0)
                                                        yyerror("Function argument can't be stored in r:0");

                                                    if ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) + 1 >= MAX_REGISTERS)
                                                        yyerror("Too many registers");
                                                    
                                                    if (numArgs >= MAX_FUNCARGS)
                                                        yyerror("Too many function arguments");

                                                    if (regfunc_args[curFunc][(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num)] != NULL)
                                                        yyerror("Duplicate register");

                                                    regfunc_args[curFunc][(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num)] = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str);

                                                    if ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) + 1 > (long int) numRegisters[curFunc])
                                                        numRegisters[curFunc] = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) + 1;

                                                    /* if parameter is stored in register, may skip its name */
                                                    if ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) > 0 && clearregisterargs && mode >= MODE_UPDATE)
                                                        ((*yyvalp).num) += writeString("");
                                                    else
                                                        ((*yyvalp).num) += writeString((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));
                                                ;}
    break;

  case 142:
#line 759 "assembler.y"
    {
                                                    numArgs++;
                                                    /* r:0 - not stored in register */
                                                    ((*yyvalp).num) = writeByte(0);
                                                    ((*yyvalp).num) += writeString((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));
                                                ;}
    break;

  case 143:
#line 768 "assembler.y"
    {   ((*yyvalp).num) = 0;         ;}
    break;

  case 144:
#line 769 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);        ;}
    break;

  case 145:
#line 770 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);   ;}
    break;

  case 146:
#line 774 "assembler.y"
    {
                                                    unsigned int autoregFlag = 0, i;

                                                    if ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) == 0 || (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) > MAX_AUTO_REGS)
                                                        yyerror("Automatic values should be placed into consequent registers starting with r:1\nin this order: this, arguments, super, _root, _parent, _global");

                                                    if (regfunc_args[curFunc][(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num)] != NULL && strcmp(regfunc_args[curFunc][(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num)], (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)))
                                                        yyerror("Duplicate register");

                                                    regfunc_args[curFunc][(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num)] = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str);

                                                    if ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) + 1 > (long int) numRegisters[curFunc])
                                                        numRegisters[curFunc] = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) + 1;
                                                    
                                                    for (i = 0; i < MAX_AUTO_REGS; i++) {
                                                        if (!strcmp((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), arNames[i])) {
                                                            autoregFlag = arFlags[i];
                                                            break;
                                                        }
                                                    }

                                                    if (autoregFlag == 0)
                                                        yyerror("Only automatic values (this, arguments, super, _root, _parent, _global) are allowed here");
                                                    
                                                    if (!(autoregFlags & autoregFlag))
                                                        autoregFlags += autoregFlag;
                                                    else
                                                        yyerror("Duplicate automatic value");
                                                ;}
    break;

  case 147:
#line 806 "assembler.y"
    {   ((*yyvalp).num) = 0;         ;}
    break;

  case 148:
#line 807 "assembler.y"
    {   ((*yyvalp).num) = 1;         ;}
    break;

  case 149:
#line 808 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) + 1;    ;}
    break;

  case 150:
#line 812 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_DEFINEFUNCTION2);
                                                    /* zero block length */
                                                    ((*yyvalp).num) += writeShort(0);
                                                    /* function name */
                                                    ((*yyvalp).num) += writeString((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));
                                                    curFunc++;
                                                    memset(regfunc_args[curFunc], 0, sizeof (regfunc_args[curFunc]));
                                                    numArgs = 0;
                                                    /* zero num of function arguments */
                                                    ((*yyvalp).num) += writeShort(numArgs);
                                                    /* allocate zero registers */
                                                    numRegisters[curFunc] = 0;
                                                    ((*yyvalp).num) += writeByte(numRegisters[curFunc]);
                                                    /* zero automatic register flags */
                                                    ((*yyvalp).num) += writeShort(0);
                                                ;}
    break;

  case 151:
#line 830 "assembler.y"
    {
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num);
                                                    /* patch num of function arguments */
                                                    patchLength((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + 3, numArgs);
                                                    autoregFlags = 0;
                                                ;}
    break;

  case 152:
#line 837 "assembler.y"
    {
                                                    byte curautoreg = 1;
                                                    unsigned int i;

                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num);
                                                    /* zero body length */
                                                    ((*yyvalp).num) += writeShort(0);
                                                    
                                                    /* make sure auto registers are allocated in the right order */
                                                    for (i = 0; i < MAX_AUTO_REGS; i++) {
                                                        if (autoregFlags & arFlags[i]) {
                                                            if (regfunc_args[curFunc][curautoreg] != NULL && !strcmp(regfunc_args[curFunc][curautoreg], arNames[i]))
                                                                curautoreg++;
                                                            else
                                                                yyerror("Automatic values should be placed into consequent registers starting with r:1\nin this order: this, arguments, super, _root, _parent, _global");
                                                        }
                                                        else
                                                            autoregFlags += arNotFlags[i];
                                                    }

                                                    /* patch automatic register flags */
                                                    patchLength(((*yyvalp).num) - (((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.num), autoregFlags);
                                                    /* patch block length */
                                                    patchLength(((*yyvalp).num) - 3, ((*yyvalp).num) - 3);
                                                ;}
    break;

  case 153:
#line 863 "assembler.y"
    {
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num);

                                                    /* patch number of registers to allocate */
                                                    if (numRegisters[curFunc] < MAX_REGISTERS)
                                                        patchFlag(((*yyvalp).num) - (((yyGLRStackItem const *)yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval.num) + 2, (byte) numRegisters[curFunc]);
                                                    else
                                                        yyerror("Too many registers.");

                                                    /* patch function length */
                                                    patchLength((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
                                                    curFunc--;
                                                ;}
    break;

  case 154:
#line 879 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_WITH);
                                                    /* length of with action */
                                                    ((*yyvalp).num) += writeShort(2);
                                                    /* length of with block - will be patched */
                                                    ((*yyvalp).num) += writeShort(0);
                                                ;}
    break;

  case 155:
#line 887 "assembler.y"
    { 
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num);
                                                    patchLength((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 156:
#line 895 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_SETTARGET);
                                                    ((*yyvalp).num) += writeShort(strlen((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str))+1);
                                                    ((*yyvalp).num) += writeString((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));
                                                ;}
    break;

  case 157:
#line 901 "assembler.y"
    {
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + writeByte(SWFACTION_SETTARGET);
                                                    ((*yyvalp).num) += (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) + writeShort(1);
                                                    ((*yyvalp).num) += writeByte(0);
                                                ;}
    break;

  case 158:
#line 909 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_SETTARGETEXPRESSION);  ;}
    break;

  case 159:
#line 910 "assembler.y"
    {
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + writeByte(SWFACTION_SETTARGET);
                                                    ((*yyvalp).num) += (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) + writeShort(1);
                                                    ((*yyvalp).num) += writeByte(0);
                                                ;}
    break;

  case 160:
#line 918 "assembler.y"
    {
                                                    if (frameloadedStart>-1)
                                                        yyerror("IfFrameLoaded actions can't be nested");
                                                    ((*yyvalp).num) = writeByte(SWFACTION_IFFRAMELOADEDEXPRESSION);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte(0);
                                                    frameloadedStart = numActions;
                                                ;}
    break;

  case 161:
#line 927 "assembler.y"
    { 
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num);
                                                    patchFrameLoaded((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num), numActions-frameloadedStart);
                                                    frameloadedStart = -1;
                                                ;}
    break;

  case 162:
#line 935 "assembler.y"
    {
                                                    if (frameloadedStart>-1)
                                                        yyerror("IfFrameLoaded actions can't be nested");
                                                    ((*yyvalp).num) = writeByte(SWFACTION_IFFRAMELOADED);
                                                    ((*yyvalp).num) += writeShort(3);
                                                    ((*yyvalp).num) += writeShort((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                    ((*yyvalp).num) += writeByte(0);
                                                    frameloadedStart = numActions;
                                                ;}
    break;

  case 163:
#line 945 "assembler.y"
    { 
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num);
                                                    patchFrameLoaded((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num), numActions-frameloadedStart);
                                                    frameloadedStart = -1;
                                                ;}
    break;

  case 164:
#line 953 "assembler.y"
    {   numAssets = 0;  ;}
    break;

  case 165:
#line 954 "assembler.y"
    {
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num);
                                                    writeImportAssets((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.str), numAssets);
                                                    ((*yyvalp).num) = 0;
                                                ;}
    break;

  case 166:
#line 962 "assembler.y"
    {   ((*yyvalp).num) = 0;         ;}
    break;

  case 167:
#line 963 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);        ;}
    break;

  case 168:
#line 967 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);        ;}
    break;

  case 169:
#line 968 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);   ;}
    break;

  case 170:
#line 972 "assembler.y"
    {
                                                    ((*yyvalp).num) = strlen((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.str))+3;
                                                    writeShort((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                    writeString((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.str));
                                                    numAssets++;
                                                ;}
    break;

  case 171:
#line 981 "assembler.y"
    {   numAssets = 0;  ;}
    break;

  case 172:
#line 982 "assembler.y"
    {
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num);
                                                    writeExportAssets(numAssets);
                                                    ((*yyvalp).num) = 0;
                                                ;}
    break;

  case 173:
#line 990 "assembler.y"
    {   ((*yyvalp).num) = 0;         ;}
    break;

  case 174:
#line 991 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);        ;}
    break;

  case 175:
#line 995 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);        ;}
    break;

  case 176:
#line 996 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);   ;}
    break;

  case 177:
#line 1000 "assembler.y"
    {
                                                    ((*yyvalp).num) = strlen((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str))+3;
                                                    writeShort((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.num));
                                                    writeString((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));
                                                    numAssets++;
                                                ;}
    break;

  case 178:
#line 1009 "assembler.y"
    {   ((*yyvalp).num) = writePushString((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));   ;}
    break;

  case 179:
#line 1011 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(0x01);
                                                    ((*yyvalp).num) += writeFloat((float)(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 180:
#line 1016 "assembler.y"
    {
                                                    float f;
                                                    sscanf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), "%f", &f);
                                                    ((*yyvalp).num) = writeByte(0x01);
                                                    ((*yyvalp).num) += writeFloat(f);
                                                ;}
    break;

  case 181:
#line 1023 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(0x01);
                                                    ((*yyvalp).num) += writeFloat(0/zero);
                                                ;}
    break;

  case 182:
#line 1028 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(0x01);
                                                    ((*yyvalp).num) += writeFloat(1/zero);
                                                ;}
    break;

  case 183:
#line 1033 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(0x01);
                                                    ((*yyvalp).num) += writeFloat(-1/zero);
                                                ;}
    break;

  case 184:
#line 1038 "assembler.y"
    {
                                                    unsigned long int li = xtoi((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));
                                                    if (li > 65535)
                                                        yyerror("Hex number should be unsigned integer in the range from 0x0000 to 0xFFFF");

                                                    ((*yyvalp).num) = writeByte(0x07);
                                                    ((*yyvalp).num) += writeLongInt(xtoi((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)));
                                                ;}
    break;

  case 185:
#line 1047 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(0x07);
                                                    ((*yyvalp).num) += writeLongInt((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 186:
#line 1052 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(0x06);
                                                    ((*yyvalp).num) += writeDouble(atof((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)));
                                                ;}
    break;

  case 187:
#line 1057 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(0x06);
                                                    ((*yyvalp).num) += writeDouble(0/zero);
                                                ;}
    break;

  case 188:
#line 1062 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(0x06);
                                                    ((*yyvalp).num) += writeDouble(1/zero);
                                                ;}
    break;

  case 189:
#line 1067 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(0x06);
                                                    ((*yyvalp).num) += writeDouble(-1/zero);
                                                ;}
    break;

  case 190:
#line 1072 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(0x05);
                                                    ((*yyvalp).num) += writeByte(1);
                                                ;}
    break;

  case 191:
#line 1077 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(0x05);
                                                    ((*yyvalp).num) += writeByte(0);
                                                ;}
    break;

  case 192:
#line 1082 "assembler.y"
    {   ((*yyvalp).num) = writeByte(2);  ;}
    break;

  case 193:
#line 1084 "assembler.y"
    {   ((*yyvalp).num) = writeByte(3);  ;}
    break;

  case 194:
#line 1086 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(0x04);
                                                    ((*yyvalp).num) += writeByte((byte)(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 195:
#line 1093 "assembler.y"
    {   ((*yyvalp).num) = 0;     ;}
    break;

  case 196:
#line 1094 "assembler.y"
    {   ((*yyvalp).num) = 1;     ;}
    break;

  case 197:
#line 1095 "assembler.y"
    {   ((*yyvalp).num) = 2;     ;}
    break;

  case 198:
#line 1096 "assembler.y"
    {   ((*yyvalp).num) = 3;     ;}
    break;

  case 199:
#line 1097 "assembler.y"
    {   ((*yyvalp).num) = 4;     ;}
    break;

  case 200:
#line 1098 "assembler.y"
    {   ((*yyvalp).num) = 5;     ;}
    break;

  case 201:
#line 1099 "assembler.y"
    {   ((*yyvalp).num) = 6;     ;}
    break;

  case 202:
#line 1100 "assembler.y"
    {   ((*yyvalp).num) = 7;     ;}
    break;

  case 203:
#line 1101 "assembler.y"
    {   ((*yyvalp).num) = 8;     ;}
    break;

  case 204:
#line 1102 "assembler.y"
    {   ((*yyvalp).num) = 9;     ;}
    break;

  case 205:
#line 1103 "assembler.y"
    {   ((*yyvalp).num) = 10;    ;}
    break;

  case 206:
#line 1104 "assembler.y"
    {   ((*yyvalp).num) = 11;    ;}
    break;

  case 207:
#line 1105 "assembler.y"
    {   ((*yyvalp).num) = 12;    ;}
    break;

  case 208:
#line 1106 "assembler.y"
    {   ((*yyvalp).num) = 13;    ;}
    break;

  case 209:
#line 1107 "assembler.y"
    {   ((*yyvalp).num) = 14;    ;}
    break;

  case 210:
#line 1108 "assembler.y"
    {   ((*yyvalp).num) = 15;    ;}
    break;

  case 211:
#line 1109 "assembler.y"
    {   ((*yyvalp).num) = 16;    ;}
    break;

  case 212:
#line 1110 "assembler.y"
    {   ((*yyvalp).num) = 17;    ;}
    break;

  case 213:
#line 1111 "assembler.y"
    {   ((*yyvalp).num) = 18;    ;}
    break;

  case 214:
#line 1112 "assembler.y"
    {   ((*yyvalp).num) = 19;    ;}
    break;

  case 215:
#line 1113 "assembler.y"
    {   ((*yyvalp).num) = 20;    ;}
    break;

  case 216:
#line 1114 "assembler.y"
    {   ((*yyvalp).num) = 21;    ;}
    break;

  case 217:
#line 1118 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 218:
#line 1119 "assembler.y"
    {   ((*yyvalp).num) += (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);   ;}
    break;

  case 219:
#line 1123 "assembler.y"
    {   addConstant((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));    ;}
    break;

  case 220:
#line 1124 "assembler.y"
    {   addConstant((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));    ;}
    break;

  case 221:
#line 1128 "assembler.y"
    {
                                                    if (xtoi((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str))>0xff)
                                                        yyerror("Action data must be a byte list!");
                                                    ((*yyvalp).num) = writeByte((char)xtoi((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)));
                                                ;}
    break;

  case 222:
#line 1134 "assembler.y"
    {
                                                    if (xtoi((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str))>0xff)
                                                        yyerror("Action data must be a byte list!");
                                                    ((*yyvalp).num) += writeByte((char)xtoi((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)));
                                                ;}
    break;

  case 223:
#line 1142 "assembler.y"
    {   ((*yyvalp).num) = 0;     ;}
    break;

  case 224:
#line 1143 "assembler.y"
    {   ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);    ;}
    break;

  case 225:
#line 1147 "assembler.y"
    {   ((*yyvalp).num) = 0;     ;}
    break;

  case 226:
#line 1148 "assembler.y"
    {   ((*yyvalp).num) = 1;     ;}
    break;

  case 227:
#line 1149 "assembler.y"
    {   ((*yyvalp).num) = 2;     ;}
    break;

  case 228:
#line 1153 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHZEROSETVAR);     --numActions;;}
    break;

  case 229:
#line 1154 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHTHISVARIABLE);   --numActions;;}
    break;

  case 230:
#line 1155 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHGLOBALVARIABLE); --numActions;;}
    break;

  case 231:
#line 1156 "assembler.y"
    {   
                                                    if ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num) == 0) {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_PUSH0);
                                                    } else if ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num) == 1) {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_PUSH1);
                                                    } else {
                                                        int val = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);
                                                        if (val <= -127 || val >= 127) {
                                                            if (val <= -32767 || val >= 32767) {
                                                                ((*yyvalp).num) = writeByte(SWFACTION_PUSHDWORD);
                                                                ((*yyvalp).num) += writeShort(4);
                                                                ((*yyvalp).num) += writeLongInt((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                            }
                                                            else
                                                            {
                                                                ((*yyvalp).num) = writeByte(SWFACTION_PUSHWORD);
                                                                ((*yyvalp).num) += writeShort(2);
                                                                ((*yyvalp).num) += writeShort((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                            }
                                                        }
                                                        else
                                                        {
                                                            ((*yyvalp).num) = writeByte(SWFACTION_PUSHBYTE);
                                                            ((*yyvalp).num) += writeShort(1);
                                                            ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                        }
                                                    }
                                                ;}
    break;

  case 232:
#line 1184 "assembler.y"
    {   ((*yyvalp).num) = writePushStringDictOpcodes((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), SWFACTION_PUSHSTRINGDICTBYTE, SWFACTION_PUSHSTRINGDICTWORD, SWFACTION_PUSHSTRING);    ;}
    break;

  case 233:
#line 1185 "assembler.y"
    {
                                                    float val;
                                                    sscanf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), "%f", &val);
                                                    if (val == 0.0f) {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_PUSH0);
                                                    } else if (val == 1.0f) {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_PUSH1);
                                                    } else {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_PUSHFLOAT);
                                                        ((*yyvalp).num) += writeShort(4);
                                                        ((*yyvalp).num) += writeFloat(val);
                                                    }
                                                ;}
    break;

  case 234:
#line 1198 "assembler.y"
    {
                                                    float val;
                                                    sscanf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), "%f", &val);
                                                    if (val == 0.0f) {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_PUSH0);
                                                    } else if (val == 1.0f) {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_PUSH1);
                                                    } else {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_PUSHFLOAT);
                                                        ((*yyvalp).num) += writeShort(4);
                                                        ((*yyvalp).num) += writeFloat(val);
                                                    }
                                                ;}
    break;

  case 235:
#line 1211 "assembler.y"
    {
                                                    if (isRA3)
                                                    {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_PUSHREGISTER);
                                                        ((*yyvalp).num) += writeShort(1);
                                                        ((*yyvalp).num) += writeByte((byte)(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                    }
                                                    else
                                                    {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_PUSHDATA);
                                                        ((*yyvalp).num) += writeByte(2);
                                                        ((*yyvalp).num) += writeByte(0);
                                                        ((*yyvalp).num) += writeByte(4);
                                                        ((*yyvalp).num) += writeByte((byte)(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                    }
                                                ;}
    break;

  case 236:
#line 1227 "assembler.y"
    {   ((*yyvalp).num) = writePushStringOpcodes((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.str), SWFACTION_PUSHSTRINGGETVAR, SWFACTION_GETVARIABLE, &numActions);     ;}
    break;

  case 237:
#line 1228 "assembler.y"
    {   ((*yyvalp).num) = writePushStringOpcodes((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.str), SWFACTION_PUSHSTRINGGETMEMBER, SWFACTION_GETMEMBER, &numActions);    ;}
    break;

  case 238:
#line 1229 "assembler.y"
    {   ((*yyvalp).num) = writePushStringOpcodes((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.str), SWFACTION_PUSHSTRINGSETVAR, SWFACTION_SETVARIABLE, &numActions);     ;}
    break;

  case 239:
#line 1230 "assembler.y"
    {   ((*yyvalp).num) = writePushStringOpcodes((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.str), SWFACTION_PUSHSTRINGSETMEMBER, SWFACTION_SETMEMBER, &numActions);    ;}
    break;

  case 240:
#line 1231 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_PUSHSTRINGDICTWORD);
                                                    ((*yyvalp).num) += writeShort(2);
                                                    ((*yyvalp).num) += writeShort((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 241:
#line 1236 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_PUSHSTRINGDICTBYTE);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 242:
#line 1241 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_STRINGDICTBYTEGETVAR);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
                                                    --numActions;
                                                ;}
    break;

  case 243:
#line 1247 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_STRINGDICTBYTEGETMEMBER);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
                                                    --numActions;
                                                ;}
    break;

  case 244:
#line 1253 "assembler.y"
    {
                                                    if (isConstant((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num), "this")) {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_PUSHTHISVARIABLE);
                                                    } else if (isConstant((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num), "_global")) {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_PUSHGLOBALVARIABLE);
                                                    } else {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_STRINGDICTBYTEGETVAR);
                                                        ((*yyvalp).num) += writeShort(1);
                                                        ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                    }
                                                ;}
    break;

  case 245:
#line 1264 "assembler.y"
    { ((*yyvalp).num) = writeByte(SWFACTION_CALLFUNCANDPOP); --numActions;   ;}
    break;

  case 246:
#line 1265 "assembler.y"
    { ((*yyvalp).num) = writeByte(SWFACTION_CALLFUNCSETVAR); --numActions;   ;}
    break;

  case 247:
#line 1266 "assembler.y"
    { ((*yyvalp).num) = writeByte(SWFACTION_CALLMETHODPOP); --numActions;    ;}
    break;

  case 248:
#line 1267 "assembler.y"
    { ((*yyvalp).num) = writeByte(SWFACTION_CALLMETHODSETVAR); --numActions; ;}
    break;

  case 249:
#line 1268 "assembler.y"
    {
                                                    if (isConstant((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num), "AptTrace")) {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_TRACESTART);
                                                        --numActions;
                                                    } else {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_DICTCALLFUNCPOP);
                                                        ((*yyvalp).num) += writeShort(1);
                                                        ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
                                                        --numActions;
                                                    }
                                                ;}
    break;

  case 250:
#line 1279 "assembler.y"
    {
                                                    if (isConstant((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num), "AptTrace")) {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_TRACESTART);
                                                        --numActions;
                                                    } else {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_PUSHSTRINGDICTWORD);
                                                        ((*yyvalp).num) += writeShort(2);
                                                        ((*yyvalp).num) += writeShort((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
                                                        ((*yyvalp).num) += writeByte(SWFACTION_CALLFUNCANDPOP);
                                                    }
                                                ;}
    break;

  case 251:
#line 1290 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_DICTCALLFUNCSETVAR);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
                                                    --numActions;
                                                ;}
    break;

  case 252:
#line 1296 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_DICTCALLMETHODPOP);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
                                                    --numActions;
                                                ;}
    break;

  case 253:
#line 1302 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_DICTCALLMETHODSETVAR);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
                                                    --numActions;
                                                ;}
    break;

  case 254:
#line 1308 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHNULL);        ;}
    break;

  case 255:
#line 1309 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHUNDEFINED);   ;}
    break;

  case 256:
#line 1310 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHTRUE);        ;}
    break;

  case 257:
#line 1311 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHFALSE);       ;}
    break;

  case 258:
#line 1312 "assembler.y"
    {
                                                    if (mode >= MODE_UPDATE) {
                                                        /* strip double nots */
                                                        ((*yyvalp).num) = 0;
                                                        numActions -= 2;
                                                    }
                                                    else {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_LOGICALNOT);
                                                        ((*yyvalp).num) += writeByte(SWFACTION_LOGICALNOT);
                                                    }
                                                ;}
    break;

  case 259:
#line 1326 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_PUSHBYTE);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 260:
#line 1331 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHNULL);        ;}
    break;

  case 261:
#line 1332 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHUNDEFINED);   ;}
    break;

  case 262:
#line 1333 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHTRUE);        ;}
    break;

  case 263:
#line 1334 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHFALSE);       ;}
    break;

  case 264:
#line 1335 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHZEROSETVAR);  ;}
    break;

  case 265:
#line 1336 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_PUSHWORD);
                                                    ((*yyvalp).num) += writeShort(2);
                                                    ((*yyvalp).num) += writeShort((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 266:
#line 1341 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_PUSHDWORD);
                                                    ((*yyvalp).num) += writeShort(4);
                                                    ((*yyvalp).num) += writeLongInt((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 267:
#line 1346 "assembler.y"
    {
                                                    float val;
                                                    sscanf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), "%f", &val);
                                                    ((*yyvalp).num) = writeByte(SWFACTION_PUSHFLOAT);
                                                    ((*yyvalp).num) += writeShort(4);
                                                    ((*yyvalp).num) += writeFloat(val);
                                                ;}
    break;

  case 268:
#line 1353 "assembler.y"
    {
                                                    float val;
                                                    sscanf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), "%f", &val);
                                                    ((*yyvalp).num) = writeByte(SWFACTION_PUSHFLOAT);
                                                    ((*yyvalp).num) += writeShort(4);
                                                    ((*yyvalp).num) += writeFloat(val);
                                                ;}
    break;

  case 269:
#line 1360 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_PUSHREGISTER);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte((byte)(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 270:
#line 1365 "assembler.y"
    {   ((*yyvalp).num) = writePushStringOpcodes((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), SWFACTION_PUSHSTRING, SWFACTION_INVALID, &numActions);                ;}
    break;

  case 271:
#line 1366 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSH1);                                                              ;}
    break;

  case 272:
#line 1367 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSH0);                                                              ;}
    break;

  case 273:
#line 1368 "assembler.y"
    {   ((*yyvalp).num) = writePushStringOpcodes((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), SWFACTION_PUSHSTRINGGETVAR, SWFACTION_GETVARIABLE, &numActions);      ;}
    break;

  case 274:
#line 1369 "assembler.y"
    {   ((*yyvalp).num) = writePushStringOpcodes((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), SWFACTION_PUSHSTRINGGETMEMBER, SWFACTION_GETMEMBER, &numActions);     ;}
    break;

  case 275:
#line 1370 "assembler.y"
    {   ((*yyvalp).num) = writePushStringOpcodes((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), SWFACTION_PUSHSTRINGSETVAR, SWFACTION_SETVARIABLE, &numActions);      ;}
    break;

  case 276:
#line 1371 "assembler.y"
    {   ((*yyvalp).num) = writePushStringOpcodes((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), SWFACTION_PUSHSTRINGSETMEMBER, SWFACTION_SETMEMBER, &numActions);     ;}
    break;

  case 277:
#line 1372 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_DICTCALLFUNCPOP);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 278:
#line 1377 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_DICTCALLFUNCSETVAR);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 279:
#line 1382 "assembler.y"
    {
                                                    if (isConstant((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num), "AptTrace")) {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_TRACESTART);
                                                        --numActions;
                                                    } else {
                                                        ((*yyvalp).num) = writeByte(SWFACTION_DICTCALLMETHODPOP);
                                                        ((*yyvalp).num) += writeShort(1);
                                                        ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                    }
                                                ;}
    break;

  case 280:
#line 1392 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_TRACESTART);   ;}
    break;

  case 281:
#line 1393 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_DICTCALLMETHODSETVAR);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 282:
#line 1398 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_CALLFUNCANDPOP);       ;}
    break;

  case 283:
#line 1399 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHTHISVARIABLE);     ;}
    break;

  case 284:
#line 1400 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHGLOBALVARIABLE);   ;}
    break;

  case 285:
#line 1401 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_CALLFUNCSETVAR);       ;}
    break;

  case 286:
#line 1402 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_CALLMETHODPOP);        ;}
    break;

  case 287:
#line 1403 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_CALLMETHODSETVAR);     ;}
    break;

  case 288:
#line 1404 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHTHIS);             ;}
    break;

  case 289:
#line 1405 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PUSHGLOBAL);           ;}
    break;

  case 290:
#line 1406 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_STRINGDICTBYTEGETMEMBER);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 291:
#line 1411 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_STRINGDICTBYTEGETVAR);
                                                    ((*yyvalp).num) += writeShort(2);
                                                    ((*yyvalp).num) += writeShort((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num)); //needed to match... is this a bug?
                                                ;}
    break;

  case 292:
#line 1418 "assembler.y"
    {   nConstants = 0;         ;}
    break;

  case 293:
#line 1419 "assembler.y"
    {   ((*yyvalp).num) = writeConstants();  ;}
    break;

  case 294:
#line 1421 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_PUSHDATA);
                                                    /* length */
                                                    ((*yyvalp).num) += writeShort(0);
                                                ;}
    break;

  case 295:
#line 1427 "assembler.y"
    {   
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);
                                                    patchLength((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 296:
#line 1432 "assembler.y"
    {
                                                    if (xtoi((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str))>0xff)
                                                        yyerror("Action code out of range");
                                                    ((*yyvalp).num) = writeByte((char)xtoi((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)));
                                                    if (xtoi((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str))>=0x80)
                                                    /* length */
                                                    ((*yyvalp).num) += writeShort(0);
                                                ;}
    break;

  case 297:
#line 1441 "assembler.y"
    {
                                                    if (((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num)>0) && (xtoi((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.str))>=0x80))
                                                        patchLength((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                    ((*yyvalp).num) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num);
                                                ;}
    break;

  case 298:
#line 1447 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_SETREGISTER);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte((byte)(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 299:
#line 1453 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_STRICTEQUALS);     ;}
    break;

  case 300:
#line 1454 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_GREATERTHAN);      ;}
    break;

  case 301:
#line 1455 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_ENUMERATEVALUE);   ;}
    break;

  case 302:
#line 1456 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_INSTANCEOF);       ;}
    break;

  case 303:
#line 1457 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_NEXTFRAME);        ;}
    break;

  case 304:
#line 1458 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PREVFRAME);        ;}
    break;

  case 305:
#line 1459 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_PLAY);             ;}
    break;

  case 306:
#line 1460 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_STOP);             ;}
    break;

  case 307:
#line 1461 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_TOGGLEQUALITY);    ;}
    break;

  case 308:
#line 1462 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_STOPSOUNDS);       ;}
    break;

  case 309:
#line 1463 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_CALLFUNCTION);     ;}
    break;

  case 310:
#line 1464 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_RETURN);           ;}
    break;

  case 311:
#line 1465 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_NEWMETHOD);        ;}
    break;

  case 312:
#line 1466 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_CALLMETHOD);       ;}
    break;

  case 313:
#line 1467 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_BITWISEAND);       ;}
    break;

  case 314:
#line 1468 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_BITWISEOR);        ;}
    break;

  case 315:
#line 1469 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_BITWISEXOR);       ;}
    break;

  case 316:
#line 1470 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_MODULO);           ;}
    break;

  case 317:
#line 1471 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_NEWADD);           ;}
    break;

  case 318:
#line 1472 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_NEWLESSTHAN);      ;}
    break;

  case 319:
#line 1473 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_NEWEQUALS);        ;}
    break;

  case 320:
#line 1474 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_TONUMBER);         ;}
    break;

  case 321:
#line 1475 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_TOSTRING);         ;}
    break;

  case 322:
#line 1476 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_INCREMENT);        ;}
    break;

  case 323:
#line 1477 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_DECREMENT);        ;}
    break;

  case 324:
#line 1478 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_TYPEOF);           ;}
    break;

  case 325:
#line 1479 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_TARGETPATH);       ;}
    break;

  case 326:
#line 1480 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_ENUMERATE);        ;}
    break;

  case 327:
#line 1481 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_DELETE);           ;}
    break;

  case 328:
#line 1482 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_DELETE2);          ;}
    break;

  case 329:
#line 1483 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_NEW);              ;}
    break;

  case 330:
#line 1484 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_INITARRAY);        ;}
    break;

  case 331:
#line 1485 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_INITOBJECT);       ;}
    break;

  case 332:
#line 1486 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_GETMEMBER);        ;}
    break;

  case 333:
#line 1487 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_SETMEMBER);        ;}
    break;

  case 334:
#line 1488 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_SHIFTLEFT);        ;}
    break;

  case 335:
#line 1489 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_SHIFTRIGHT);       ;}
    break;

  case 336:
#line 1490 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_SHIFTRIGHT2);      ;}
    break;

  case 337:
#line 1491 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_VAR);              ;}
    break;

  case 338:
#line 1492 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_VAREQUALS);        ;}
    break;

  case 339:
#line 1493 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_ADD);              ;}
    break;

  case 340:
#line 1494 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_SUBTRACT);         ;}
    break;

  case 341:
#line 1495 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_MULTIPLY);         ;}
    break;

  case 342:
#line 1496 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_DIVIDE);           ;}
    break;

  case 343:
#line 1497 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_EQUALS);           ;}
    break;

  case 344:
#line 1498 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_LESSTHAN);         ;}
    break;

  case 345:
#line 1499 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_LOGICALAND);       ;}
    break;

  case 346:
#line 1500 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_LOGICALOR);        ;}
    break;

  case 347:
#line 1501 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_LOGICALNOT);       ;}
    break;

  case 348:
#line 1502 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_STRINGEQ);         ;}
    break;

  case 349:
#line 1503 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_STRINGLENGTH);     ;}
    break;

  case 350:
#line 1504 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_SUBSTRING);        ;}
    break;

  case 351:
#line 1505 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_INT);              ;}
    break;

  case 352:
#line 1506 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_DUP);              ;}
    break;

  case 353:
#line 1507 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_SWAP);             ;}
    break;

  case 354:
#line 1508 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_POP);              ;}
    break;

  case 355:
#line 1509 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_GETVARIABLE);      ;}
    break;

  case 356:
#line 1510 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_SETVARIABLE);      ;}
    break;

  case 357:
#line 1511 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_STRINGCONCAT);     ;}
    break;

  case 358:
#line 1512 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_GETPROPERTY);      ;}
    break;

  case 359:
#line 1513 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_SETPROPERTY);      ;}
    break;

  case 360:
#line 1514 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_DUPLICATECLIP);    ;}
    break;

  case 361:
#line 1515 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_REMOVECLIP);       ;}
    break;

  case 362:
#line 1516 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_TRACE);            ;}
    break;

  case 363:
#line 1517 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_STARTDRAGMOVIE);   ;}
    break;

  case 364:
#line 1518 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_STOPDRAGMOVIE);    ;}
    break;

  case 365:
#line 1519 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_STRINGLESSTHAN);   ;}
    break;

  case 366:
#line 1520 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_STRINGGREATERTHAN);;}
    break;

  case 367:
#line 1521 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_RANDOM);           ;}
    break;

  case 368:
#line 1522 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_MBLENGTH);         ;}
    break;

  case 369:
#line 1523 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_ORD);              ;}
    break;

  case 370:
#line 1524 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_CHR);              ;}
    break;

  case 371:
#line 1525 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_GETTIMER);         ;}
    break;

  case 372:
#line 1526 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_MBSUBSTRING);      ;}
    break;

  case 373:
#line 1527 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_MBORD);            ;}
    break;

  case 374:
#line 1528 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_MBCHR);            ;}
    break;

  case 375:
#line 1529 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_IMPLEMENTS);       ;}
    break;

  case 376:
#line 1530 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_EXTENDS);          ;}
    break;

  case 377:
#line 1531 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_THROW);            ;}
    break;

  case 378:
#line 1532 "assembler.y"
    {   ((*yyvalp).num) = writeByte(SWFACTION_CAST);             ;}
    break;

  case 379:
#line 1534 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_CALLFRAME);
                                                    ((*yyvalp).num) += writeShort(0);
                                                ;}
    break;

  case 380:
#line 1539 "assembler.y"
    {   
                                                    ((*yyvalp).num) = writeByte(SWFACTION_GOTOEXPRESSION);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte(0);
                                                ;}
    break;

  case 381:
#line 1545 "assembler.y"
    {   
                                                    ((*yyvalp).num) = writeByte(SWFACTION_GOTOEXPRESSION);
                                                    ((*yyvalp).num) += writeShort(3);
                                                    ((*yyvalp).num) += writeByte(2);
                                                    ((*yyvalp).num) += writeShort((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 382:
#line 1552 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_GOTOEXPRESSION);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte(1);
                                                ;}
    break;

  case 383:
#line 1558 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_GOTOEXPRESSION);
                                                    ((*yyvalp).num) += writeShort(3);
                                                    ((*yyvalp).num) += writeByte(3);
                                                    ((*yyvalp).num) += writeShort((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 384:
#line 1565 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_GOTOLABEL);
                                                    ((*yyvalp).num) += writeShort(strlen((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str))+1);
                                                    ((*yyvalp).num) += writeString((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));
                                                ;}
    break;

  case 385:
#line 1571 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_BRANCHALWAYS);
                                                    ((*yyvalp).num) += writeShort(2);
                                                    ((*yyvalp).num) += branchTarget((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));
                                                ;}
    break;

  case 386:
#line 1577 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_BRANCHALWAYS);
                                                    ((*yyvalp).num) += writeShort(2);
                                                    ((*yyvalp).num) += addNumLabel((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 387:
#line 1583 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_BRANCHIFTRUE);
                                                    ((*yyvalp).num) += writeShort(2);
                                                    ((*yyvalp).num) += branchTarget((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));
                                                ;}
    break;

  case 388:
#line 1589 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_BRANCHIFTRUE);
                                                    ((*yyvalp).num) += writeShort(2);
                                                    ((*yyvalp).num) += addNumLabel((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 389:
#line 1595 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_BRANCHIFFALSE);
                                                    ((*yyvalp).num) += writeShort(2);
                                                    ((*yyvalp).num) += branchTarget((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));
                                                ;}
    break;

  case 390:
#line 1601 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_BRANCHIFFALSE);
                                                    ((*yyvalp).num) += writeShort(2);
                                                    ((*yyvalp).num) += addNumLabel((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 391:
#line 1607 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_GOTOFRAME);
                                                    ((*yyvalp).num) += writeShort(2);
                                                    ((*yyvalp).num) += writeShort((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 392:
#line 1613 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_GETURL);
                                                    ((*yyvalp).num) += writeShort(strlen((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.str))+strlen((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str))+2);
                                                    ((*yyvalp).num) += writeString((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.str)); 
                                                    ((*yyvalp).num) += writeString((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));
                                                ;}
    break;

  case 393:
#line 1620 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_GETURL2);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 394:
#line 1626 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_GETURL2);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte(0xc0 + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 395:
#line 1632 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_GETURL2);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte(0x80 + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 396:
#line 1638 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_GETURL2);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte(0x40 + (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 397:
#line 1644 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_GETURL2);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.num));
                                                ;}
    break;

  case 398:
#line 1650 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_STRICTMODE);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte(1);
                                                ;}
    break;

  case 399:
#line 1656 "assembler.y"
    {
                                                    ((*yyvalp).num) = writeByte(SWFACTION_STRICTMODE);
                                                    ((*yyvalp).num) += writeShort(1);
                                                    ((*yyvalp).num) += writeByte(0);
                                                ;}
    break;

  case 400:
#line 1662 "assembler.y"
    {   yyerror("Movie declaration inside of the action block");    ;}
    break;


      default: break;
    }

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
/* Line 872 of glr.c.  */
#line 4896 "assembler.tab.c"
}


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  /* `Use' the arguments.  */
  (void) yy0;
  (void) yy1;

  switch (yyn)
    {
      
      default: break;
    }
}

			      /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yystos[yys->yylrState],
		&yys->yysemantics.yysval);
  else
    {
#if YYDEBUG
      if (yydebug)
	{
	  YYFPRINTF (stderr, "%s unresolved ", yymsg);
	  yysymprint (stderr, yystos[yys->yylrState],
		      &yys->yysemantics.yysval);
	  YYFPRINTF (stderr, "\n");
	}
#endif

      if (yys->yysemantics.yyfirstVal)
        {
          yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
          yyGLRState *yyrh;
          int yyn;
          for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
               yyn > 0;
               yyrh = yyrh->yypred, yyn -= 1)
            yydestroyGLRState (yymsg, yyrh);
        }
    }
}

/** Left-hand-side symbol for rule #RULE. */
static inline yySymbol
yylhsNonterm (yyRuleNum yyrule)
{
  return yyr1[yyrule];
}

#define yyis_pact_ninf(yystate) \
  ((yystate) == YYPACT_NINF)

/** True iff LR state STATE has only a default reduction (regardless
 *  of token). */
static inline yybool
yyisDefaultedState (yyStateNum yystate)
{
  return yyis_pact_ninf (yypact[yystate]);
}

/** The default reduction for STATE, assuming it has one. */
static inline yyRuleNum
yydefaultAction (yyStateNum yystate)
{
  return yydefact[yystate];
}

#define yyis_table_ninf(yytable_value) \
  0

/** Set *YYACTION to the action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *CONFLICTS to a pointer into yyconfl to 0-terminated list of
 *  conflicting reductions.
 */
static inline void
yygetLRActions (yyStateNum yystate, int yytoken,
	        int* yyaction, const short int** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyaction = -yydefact[yystate];
      *yyconflicts = yyconfl;
    }
  else if (! yyis_table_ninf (yytable[yyindex]))
    {
      *yyaction = yytable[yyindex];
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
  else
    {
      *yyaction = 0;
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
}

static inline yyStateNum
yyLRgotoState (yyStateNum yystate, yySymbol yylhs)
{
  int yyr;
  yyr = yypgoto[yylhs - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yylhs - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

				/* GLRStates */

static void
yyaddDeferredAction (yyGLRStack* yystack, yyGLRState* yystate,
		     yyGLRState* rhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewItem;
  yynewItem = &yystack->yynextFree->yyoption;
  yystack->yyspaceLeft -= 1;
  yystack->yynextFree += 1;
  yynewItem->yyisState = yyfalse;
  yynewItem->yystate = rhs;
  yynewItem->yyrule = yyrule;
  yynewItem->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewItem;
  if (yystack->yyspaceLeft < YYHEADROOM)
    yyexpandGLRStack (yystack);
}

				/* GLRStacks */

/** Initialize SET to a singleton set containing an empty stack. */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates = (yyGLRState**) YYMALLOC (16 * sizeof yyset->yystates[0]);
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = NULL;
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
}

/** Initialize STACK to a single empty stack, with total maximum
 *  capacity for all stacks of SIZE. */
static yybool
yyinitGLRStack (yyGLRStack* yystack, size_t yysize)
{
  yystack->yyerrState = 0;
  yynerrs = 0;
  yystack->yyspaceLeft = yysize;
  yystack->yyitems =
    (yyGLRStackItem*) YYMALLOC (yysize * sizeof yystack->yynextFree[0]);
  if (!yystack->yyitems)
    return yyfalse;
  yystack->yynextFree = yystack->yyitems;
  yystack->yysplitPoint = NULL;
  yystack->yylastDeleted = NULL;
  return yyinitStateSet (&yystack->yytops);
}

#define YYRELOC(YYFROMITEMS,YYTOITEMS,YYX,YYTYPE) \
  &((YYTOITEMS) - ((YYFROMITEMS) - (yyGLRStackItem*) (YYX)))->YYTYPE

/** If STACK is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation. */
static void
yyexpandGLRStack (yyGLRStack* yystack)
{
#if YYSTACKEXPANDABLE
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  size_t yysize, yynewSize;
  size_t yyn;
  yysize = yystack->yynextFree - yystack->yyitems;
  if (YYMAXDEPTH <= yysize)
    yyMemoryExhausted (yystack);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems = (yyGLRStackItem*) YYMALLOC (yynewSize * sizeof yynewItems[0]);
  if (! yynewItems)
    yyMemoryExhausted (yystack);
  for (yyp0 = yystack->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*(yybool *) yyp0)
	{
	  yyGLRState* yys0 = &yyp0->yystate;
	  yyGLRState* yys1 = &yyp1->yystate;
	  if (yys0->yypred != NULL)
	    yys1->yypred =
	      YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
	  if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != NULL)
	    yys1->yysemantics.yyfirstVal =
	      YYRELOC(yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
	}
      else
	{
	  yySemanticOption* yyv0 = &yyp0->yyoption;
	  yySemanticOption* yyv1 = &yyp1->yyoption;
	  if (yyv0->yystate != NULL)
	    yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
	  if (yyv0->yynext != NULL)
	    yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
	}
    }
  if (yystack->yysplitPoint != NULL)
    yystack->yysplitPoint = YYRELOC (yystack->yyitems, yynewItems,
				 yystack->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystack->yytops.yysize; yyn += 1)
    if (yystack->yytops.yystates[yyn] != NULL)
      yystack->yytops.yystates[yyn] =
	YYRELOC (yystack->yyitems, yynewItems,
		 yystack->yytops.yystates[yyn], yystate);
  YYFREE (yystack->yyitems);
  yystack->yyitems = yynewItems;
  yystack->yynextFree = yynewItems + yysize;
  yystack->yyspaceLeft = yynewSize - yysize;

#else
  yyMemoryExhausted (yystack);
#endif
}

static void
yyfreeGLRStack (yyGLRStack* yystack)
{
  YYFREE (yystack->yyitems);
  yyfreeStateSet (&yystack->yytops);
}

/** Assuming that S is a GLRState somewhere on STACK, update the
 *  splitpoint of STACK, if needed, so that it is at least as deep as
 *  S. */
static inline void
yyupdateSplit (yyGLRStack* yystack, yyGLRState* yys)
{
  if (yystack->yysplitPoint != NULL && yystack->yysplitPoint > yys)
    yystack->yysplitPoint = yys;
}

/** Invalidate stack #K in STACK. */
static inline void
yymarkStackDeleted (yyGLRStack* yystack, size_t yyk)
{
  if (yystack->yytops.yystates[yyk] != NULL)
    yystack->yylastDeleted = yystack->yytops.yystates[yyk];
  yystack->yytops.yystates[yyk] = NULL;
}

/** Undelete the last stack that was marked as deleted.  Can only be
    done once after a deletion, and only when all other stacks have
    been deleted. */
static void
yyundeleteLastStack (yyGLRStack* yystack)
{
  if (yystack->yylastDeleted == NULL || yystack->yytops.yysize != 0)
    return;
  yystack->yytops.yystates[0] = yystack->yylastDeleted;
  yystack->yytops.yysize = 1;
  YYDPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystack->yylastDeleted = NULL;
}

static inline void
yyremoveDeletes (yyGLRStack* yystack)
{
  size_t yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystack->yytops.yysize)
    {
      if (yystack->yytops.yystates[yyi] == NULL)
	{
	  if (yyi == yyj)
	    {
	      YYDPRINTF ((stderr, "Removing dead stacks.\n"));
	    }
	  yystack->yytops.yysize -= 1;
	}
      else
	{
	  yystack->yytops.yystates[yyj] = yystack->yytops.yystates[yyi];
	  if (yyj != yyi)
	    {
	      YYDPRINTF ((stderr, "Rename stack %lu -> %lu.\n",
			  (unsigned long int) yyi, (unsigned long int) yyj));
	    }
	  yyj += 1;
	}
      yyi += 1;
    }
}

/** Shift to a new state on stack #K of STACK, corresponding to LR state
 * LRSTATE, at input position POSN, with (resolved) semantic value SVAL. */
static inline void
yyglrShift (yyGLRStack* yystack, size_t yyk, yyStateNum yylrState,
	    size_t yyposn,
	    YYSTYPE yysval, YYLTYPE* yylocp)
{
  yyGLRStackItem* yynewItem;

  yynewItem = yystack->yynextFree;
  yystack->yynextFree += 1;
  yystack->yyspaceLeft -= 1;
  yynewItem->yystate.yyisState = yytrue;
  yynewItem->yystate.yylrState = yylrState;
  yynewItem->yystate.yyposn = yyposn;
  yynewItem->yystate.yyresolved = yytrue;
  yynewItem->yystate.yypred = yystack->yytops.yystates[yyk];
  yystack->yytops.yystates[yyk] = &yynewItem->yystate;
  yynewItem->yystate.yysemantics.yysval = yysval;
  yynewItem->yystate.yyloc = *yylocp;
  if (yystack->yyspaceLeft < YYHEADROOM)
    yyexpandGLRStack (yystack);
}

/** Shift stack #K of YYSTACK, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE. */
static inline void
yyglrShiftDefer (yyGLRStack* yystack, size_t yyk, yyStateNum yylrState,
		 size_t yyposn, yyGLRState* rhs, yyRuleNum yyrule)
{
  yyGLRStackItem* yynewItem;

  yynewItem = yystack->yynextFree;
  yynewItem->yystate.yyisState = yytrue;
  yynewItem->yystate.yylrState = yylrState;
  yynewItem->yystate.yyposn = yyposn;
  yynewItem->yystate.yyresolved = yyfalse;
  yynewItem->yystate.yypred = yystack->yytops.yystates[yyk];
  yynewItem->yystate.yysemantics.yyfirstVal = NULL;
  yystack->yytops.yystates[yyk] = &yynewItem->yystate;
  yystack->yynextFree += 1;
  yystack->yyspaceLeft -= 1;
  yyaddDeferredAction (yystack, &yynewItem->yystate, rhs, yyrule);
}

/** Pop the symbols consumed by reduction #RULE from the top of stack
 *  #K of STACK, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved. Set *VALP to the resulting value,
 *  and *LOCP to the computed location (if any).  Return value is as
 *  for userAction. */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystack, size_t yyk, yyRuleNum yyrule,
	    YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystack->yysplitPoint == NULL)
    {
      /* Standard special case: single stack. */
      yyGLRStackItem* rhs = (yyGLRStackItem*) yystack->yytops.yystates[yyk];
      YYASSERT (yyk == 0);
      yystack->yynextFree -= yynrhs;
      yystack->yyspaceLeft += yynrhs;
      yystack->yytops.yystates[0] = & yystack->yynextFree[-1].yystate;
      return yyuserAction (yyrule, yynrhs, rhs,
			   yyvalp, yylocp, yystack);
    }
  else
    {
      int yyi;
      yyGLRState* yys;
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
	= yystack->yytops.yystates[yyk];
      for (yyi = 0; yyi < yynrhs; yyi += 1)
	{
	  yys = yys->yypred;
	  YYASSERT (yys);
	}
      yyupdateSplit (yystack, yys);
      yystack->yytops.yystates[yyk] = yys;
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
			   yyvalp, yylocp, yystack);
    }
}

#if !YYDEBUG
# define YY_REDUCE_PRINT(K, Rule)
#else
# define YY_REDUCE_PRINT(K, Rule)	\
do {					\
  if (yydebug)				\
    yy_reduce_print (K, Rule);		\
} while (0)

/*----------------------------------------------------------.
| Report that the RULE is going to be reduced on stack #K.  |
`----------------------------------------------------------*/

static inline void
yy_reduce_print (size_t yyk, yyRuleNum yyrule)
{
  int yyi;
  YYFPRINTF (stderr, "Reducing stack %lu by rule %d (line %lu), ",
	     (unsigned long int) yyk, yyrule - 1,
	     (unsigned long int) yyrline[yyrule]);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytokenName (yyrhs[yyi]));
  YYFPRINTF (stderr, "-> %s\n", yytokenName (yyr1[yyrule]));
}
#endif

/** Pop items off stack #K of STACK according to grammar rule RULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with RULE and store its value with the
 *  newly pushed state, if FORCEEVAL or if STACK is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #K from
 *  the STACK. In this case, the (necessarily deferred) semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystack, size_t yyk, yyRuleNum yyrule,
             yybool yyforceEval)
{
  size_t yyposn = yystack->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystack->yysplitPoint == NULL)
    {
      YYSTYPE yysval;
      YYLTYPE yyloc;

      YY_REDUCE_PRINT (yyk, yyrule);
      YYCHK (yydoAction (yystack, yyk, yyrule, &yysval, &yyloc));
      yyglrShift (yystack, yyk,
		  yyLRgotoState (yystack->yytops.yystates[yyk]->yylrState,
				 yylhsNonterm (yyrule)),
		  yyposn, yysval, &yyloc);
    }
  else
    {
      size_t yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystack->yytops.yystates[yyk];
      yyStateNum yynewLRState;

      for (yys = yystack->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
	   0 < yyn; yyn -= 1)
	{
	  yys = yys->yypred;
	  YYASSERT (yys);
	}
      yyupdateSplit (yystack, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YYDPRINTF ((stderr,
		  "Reduced stack %lu by rule #%d; action deferred. Now in state %d.\n",
		  (unsigned long int) yyk, yyrule - 1, yynewLRState));
      for (yyi = 0; yyi < yystack->yytops.yysize; yyi += 1)
	if (yyi != yyk && yystack->yytops.yystates[yyi] != NULL)
	  {
	    yyGLRState* yyp, *yysplit = yystack->yysplitPoint;
	    yyp = yystack->yytops.yystates[yyi];
	    while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
	      {
		if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
		  {
		    yyaddDeferredAction (yystack, yyp, yys0, yyrule);
		    yymarkStackDeleted (yystack, yyk);
		    YYDPRINTF ((stderr, "Merging stack %lu into stack %lu.\n",
				(unsigned long int) yyk,
				(unsigned long int) yyi));
		    return yyok;
		  }
		yyp = yyp->yypred;
	      }
	  }
      yystack->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystack, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static size_t
yysplitStack (yyGLRStack* yystack, size_t yyk)
{
  if (yystack->yysplitPoint == NULL)
    {
      YYASSERT (yyk == 0);
      yystack->yysplitPoint = yystack->yytops.yystates[yyk];
    }
  if (yystack->yytops.yysize >= yystack->yytops.yycapacity)
    {
      yyGLRState** yynewStates;
      if (! ((yystack->yytops.yycapacity
	      <= (YYSIZEMAX / (2 * sizeof yynewStates[0])))
	     && (yynewStates =
		 (yyGLRState**) YYREALLOC (yystack->yytops.yystates,
					   ((yystack->yytops.yycapacity *= 2)
					    * sizeof yynewStates[0])))))
	yyMemoryExhausted (yystack);
      yystack->yytops.yystates = yynewStates;
    }
  yystack->yytops.yystates[yystack->yytops.yysize]
    = yystack->yytops.yystates[yyk];
  yystack->yytops.yysize += 1;
  return yystack->yytops.yysize-1;
}

/** True iff Y0 and Y1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols. */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
	   yyn = yyrhsLength (yyy0->yyrule);
	   yyn > 0;
	   yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
	if (yys0->yyposn != yys1->yyposn)
	  return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (Y0,Y1), destructively merge the
 *  alternative semantic values for the RHS-symbols of Y1 and Y0. */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       yyn > 0;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
	break;
      else if (yys0->yyresolved)
	{
	  yys1->yyresolved = yytrue;
	  yys1->yysemantics.yysval = yys0->yysemantics.yysval;
	}
      else if (yys1->yyresolved)
	{
	  yys0->yyresolved = yytrue;
	  yys0->yysemantics.yysval = yys1->yysemantics.yysval;
	}
      else
	{
	  yySemanticOption** yyz0p;
	  yySemanticOption* yyz1;
	  yyz0p = &yys0->yysemantics.yyfirstVal;
	  yyz1 = yys1->yysemantics.yyfirstVal;
	  while (yytrue)
	    {
	      if (yyz1 == *yyz0p || yyz1 == NULL)
		break;
	      else if (*yyz0p == NULL)
		{
		  *yyz0p = yyz1;
		  break;
		}
	      else if (*yyz0p < yyz1)
		{
		  yySemanticOption* yyz = *yyz0p;
		  *yyz0p = yyz1;
		  yyz1 = yyz1->yynext;
		  (*yyz0p)->yynext = yyz;
		}
	      yyz0p = &(*yyz0p)->yynext;
	    }
	  yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
	}
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred. */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
	return 0;
      else
	return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG yyresolveValue (yySemanticOption* yyoptionList,
				   yyGLRStack* yystack, YYSTYPE* yyvalp,
				   YYLTYPE* yylocp);

static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn, yyGLRStack* yystack)
{
  YYRESULTTAG yyflag;
  if (0 < yyn)
    {
      YYASSERT (yys->yypred);
      yyflag = yyresolveStates (yys->yypred, yyn-1, yystack);
      if (yyflag != yyok)
	return yyflag;
      if (! yys->yyresolved)
	{
	  yyflag = yyresolveValue (yys->yysemantics.yyfirstVal, yystack,
				   &yys->yysemantics.yysval, &yys->yyloc
				  );
	  if (yyflag != yyok)
	    return yyflag;
	  yys->yyresolved = yytrue;
	}
    }
  return yyok;
}

static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystack,
	         YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs;

  yynrhs = yyrhsLength (yyopt->yyrule);
  YYCHK (yyresolveStates (yyopt->yystate, yynrhs, yystack));
  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  return yyuserAction (yyopt->yyrule, yynrhs,
		       yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
		       yyvalp, yylocp, yystack);
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == NULL)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, empty>\n",
	       yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
	       yyx->yyrule);
  else
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, tokens %lu .. %lu>\n",
	       yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
	       yyx->yyrule, (unsigned long int) (yys->yyposn + 1),
	       (unsigned long int) yyx->yystate->yyposn);
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
	{
	  if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
	    YYFPRINTF (stderr, "%*s%s <empty>\n", yyindent+2, "",
		       yytokenName (yyrhs[yyprhs[yyx->yyrule]+yyi-1]));
	  else
	    YYFPRINTF (stderr, "%*s%s <tokens %lu .. %lu>\n", yyindent+2, "",
		       yytokenName (yyrhs[yyprhs[yyx->yyrule]+yyi-1]),
		       (unsigned long int) (yystates[yyi - 1]->yyposn + 1),
		       (unsigned long int) yystates[yyi]->yyposn);
	}
      else
	yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

static void yyreportAmbiguity (yySemanticOption* yyx0, yySemanticOption* yyx1,
			       yyGLRStack* yystack)
  __attribute__ ((__noreturn__));
static void
yyreportAmbiguity (yySemanticOption* yyx0, yySemanticOption* yyx1,
		   yyGLRStack* yystack)
{
  /* `Unused' warnings.  */
  (void) yyx0;
  (void) yyx1;

#if YYDEBUG
  YYFPRINTF (stderr, "Ambiguity detected.\n");
  YYFPRINTF (stderr, "Option 1,\n");
  yyreportTree (yyx0, 2);
  YYFPRINTF (stderr, "\nOption 2,\n");
  yyreportTree (yyx1, 2);
  YYFPRINTF (stderr, "\n");
#endif
  yyFail (yystack, YY_("syntax is ambiguous"));
}


/** Resolve the ambiguity represented by OPTIONLIST, perform the indicated
 *  actions, and return the result. */
static YYRESULTTAG
yyresolveValue (yySemanticOption* yyoptionList, yyGLRStack* yystack,
		YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yySemanticOption* yybest;
  yySemanticOption** yypp;
  yybool yymerge;

  yybest = yyoptionList;
  yymerge = yyfalse;
  for (yypp = &yyoptionList->yynext; *yypp != NULL; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
	{
	  yymergeOptionSets (yybest, yyp);
	  *yypp = yyp->yynext;
	}
      else
	{
	  switch (yypreference (yybest, yyp))
	    {
	    case 0:
	      yyreportAmbiguity (yybest, yyp, yystack);
	      break;
	    case 1:
	      yymerge = yytrue;
	      break;
	    case 2:
	      break;
	    case 3:
	      yybest = yyp;
	      yymerge = yyfalse;
	      break;
	    default:
	      /* This cannot happen so it is not worth a YYASSERT (yyfalse),
	         but some compilers complain if the default case is
		 omitted.  */
	      break;
	    }
	  yypp = &yyp->yynext;
	}
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      YYCHK (yyresolveAction (yybest, yystack, yyvalp, yylocp));
      for (yyp = yybest->yynext; yyp != NULL; yyp = yyp->yynext)
	{
	  if (yyprec == yydprec[yyp->yyrule])
	    {
	      YYSTYPE yyval1;
	      YYLTYPE yydummy;
	      YYCHK (yyresolveAction (yyp, yystack, &yyval1, &yydummy));
	      yyuserMerge (yymerger[yyp->yyrule], yyvalp, &yyval1);
	    }
	}
      return yyok;
    }
  else
    return yyresolveAction (yybest, yystack, yyvalp, yylocp);
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystack)
{
  if (yystack->yysplitPoint != NULL)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystack->yytops.yystates[0];
	   yys != yystack->yysplitPoint;
	   yys = yys->yypred, yyn += 1)
	continue;
      YYCHK (yyresolveStates (yystack->yytops.yystates[0], yyn, yystack
			     ));
    }
  return yyok;
}

static void
yycompressStack (yyGLRStack* yystack)
{
  yyGLRState* yyp, *yyq, *yyr;

  if (yystack->yytops.yysize != 1 || yystack->yysplitPoint == NULL)
    return;

  for (yyp = yystack->yytops.yystates[0], yyq = yyp->yypred, yyr = NULL;
       yyp != yystack->yysplitPoint;
       yyr = yyp, yyp = yyq, yyq = yyp->yypred)
    yyp->yypred = yyr;

  yystack->yyspaceLeft += yystack->yynextFree - yystack->yyitems;
  yystack->yynextFree = ((yyGLRStackItem*) yystack->yysplitPoint) + 1;
  yystack->yyspaceLeft -= yystack->yynextFree - yystack->yyitems;
  yystack->yysplitPoint = NULL;
  yystack->yylastDeleted = NULL;

  while (yyr != NULL)
    {
      yystack->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystack->yynextFree->yystate.yypred = & yystack->yynextFree[-1].yystate;
      yystack->yytops.yystates[0] = &yystack->yynextFree->yystate;
      yystack->yynextFree += 1;
      yystack->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystack, size_t yyk,
	           size_t yyposn, YYSTYPE* yylvalp, YYLTYPE* yyllocp
		  )
{
  int yyaction;
  const short int* yyconflicts;
  yyRuleNum yyrule;
  yySymbol* const yytokenp = yystack->yytokenp;

  while (yystack->yytops.yystates[yyk] != NULL)
    {
      yyStateNum yystate = yystack->yytops.yystates[yyk]->yylrState;
      YYDPRINTF ((stderr, "Stack %lu Entering state %d\n",
		  (unsigned long int) yyk, yystate));

      YYASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
	{
	  yyrule = yydefaultAction (yystate);
	  if (yyrule == 0)
	    {
	      YYDPRINTF ((stderr, "Stack %lu dies.\n",
			  (unsigned long int) yyk));
	      yymarkStackDeleted (yystack, yyk);
	      return yyok;
	    }
	  YYCHK (yyglrReduce (yystack, yyk, yyrule, yyfalse));
	}
      else
	{
	  if (*yytokenp == YYEMPTY)
	    {
	      YYDPRINTF ((stderr, "Reading a token: "));
	      yychar = YYLEX;
	      *yytokenp = YYTRANSLATE (yychar);
	      YY_SYMBOL_PRINT ("Next token is", *yytokenp, yylvalp, yyllocp);
	    }
	  yygetLRActions (yystate, *yytokenp, &yyaction, &yyconflicts);

	  while (*yyconflicts != 0)
	    {
	      size_t yynewStack = yysplitStack (yystack, yyk);
	      YYDPRINTF ((stderr, "Splitting off stack %lu from %lu.\n",
			  (unsigned long int) yynewStack,
			  (unsigned long int) yyk));
	      YYCHK (yyglrReduce (yystack, yynewStack,
				  *yyconflicts, yyfalse));
	      YYCHK (yyprocessOneStack (yystack, yynewStack, yyposn,
					yylvalp, yyllocp));
	      yyconflicts += 1;
	    }

	  if (yyisShiftAction (yyaction))
	    {
	      YYDPRINTF ((stderr, "On stack %lu, ", (unsigned long int) yyk));
	      YY_SYMBOL_PRINT ("shifting", *yytokenp, yylvalp, yyllocp);
	      yyglrShift (yystack, yyk, yyaction, yyposn+1,
			  *yylvalp, yyllocp);
	      YYDPRINTF ((stderr, "Stack %lu now in state #%d\n",
			  (unsigned long int) yyk,
			  yystack->yytops.yystates[yyk]->yylrState));
	      break;
	    }
	  else if (yyisErrorAction (yyaction))
	    {
	      YYDPRINTF ((stderr, "Stack %lu dies.\n",
			  (unsigned long int) yyk));
	      yymarkStackDeleted (yystack, yyk);
	      break;
	    }
	  else
	    YYCHK (yyglrReduce (yystack, yyk, -yyaction, yyfalse));
	}
    }
  return yyok;
}

static void
yyreportSyntaxError (yyGLRStack* yystack,
		     YYSTYPE* yylvalp, YYLTYPE* yyllocp)
{
  /* `Unused' warnings. */
  (void) yylvalp;
  (void) yyllocp;

  if (yystack->yyerrState == 0)
    {
#if YYERROR_VERBOSE
      yySymbol* const yytokenp = yystack->yytokenp;
      int yyn;
      yyn = yypact[yystack->yytops.yystates[0]->yylrState];
      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  size_t yysize0 = yytnamerr (NULL, yytokenName (*yytokenp));
	  size_t yysize = yysize0;
	  size_t yysize1;
	  yybool yysize_overflow = yyfalse;
	  char* yymsg = NULL;
	  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;
	  char *yyfmt;
	  char const *yyf;
	  static char const yyunexpected[] = "syntax error, unexpected %s";
	  static char const yyexpecting[] = ", expecting %s";
	  static char const yyor[] = " or %s";
	  char yyformat[sizeof yyunexpected
			+ sizeof yyexpecting - 1
			+ ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
			   * (sizeof yyor - 1))];
	  char const *yyprefix = yyexpecting;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 1;

	  yyarg[0] = yytokenName (*yytokenp);
	  yyfmt = yystpcpy (yyformat, yyunexpected);

	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
		  {
		    yycount = 1;
		    yysize = yysize0;
		    yyformat[sizeof yyunexpected - 1] = '\0';
		    break;
		  }
		yyarg[yycount++] = yytokenName (yyx);
		yysize1 = yysize + yytnamerr (NULL, yytokenName (yyx));
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + strlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow)
	    yymsg = (char *) YYMALLOC (yysize);

	  if (yymsg)
	    {
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
		{
		  if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		    {
		      yyp += yytnamerr (yyp, yyarg[yyi++]);
		      yyf += 2;
		    }
		  else
		    {
		      yyp++;
		      yyf++;
		    }
		}
	      yyerror (yymsg);
	      YYFREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      yyMemoryExhausted (yystack);
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
      yynerrs += 1;
    }
}

/* Recover from a syntax error on YYSTACK, assuming that YYTOKENP,
   YYLVALP, and YYLLOCP point to the syntactic category, semantic
   value, and location of the look-ahead.  */
static void
yyrecoverSyntaxError (yyGLRStack* yystack,
		      YYSTYPE* yylvalp,
		      YYLTYPE* YYOPTIONAL_LOC (yyllocp)
		      )
{
  yySymbol* const yytokenp = yystack->yytokenp;
  size_t yyk;
  int yyj;

  if (yystack->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (yytrue)
      {
	if (*yytokenp == YYEOF)
	  yyFail (yystack, NULL);
	if (*yytokenp != YYEMPTY)
	  {
	    yydestruct ("Error: discarding",
			*yytokenp, yylvalp);
	  }
	YYDPRINTF ((stderr, "Reading a token: "));
	yychar = YYLEX;
	*yytokenp = YYTRANSLATE (yychar);
	YY_SYMBOL_PRINT ("Next token is", *yytokenp, yylvalp, yyllocp);
	yyj = yypact[yystack->yytops.yystates[0]->yylrState];
	if (yyis_pact_ninf (yyj))
	  return;
	yyj += *yytokenp;
	if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != *yytokenp)
	  {
	    if (yydefact[yystack->yytops.yystates[0]->yylrState] != 0)
	      return;
	  }
	else if (yytable[yyj] != 0 && ! yyis_table_ninf (yytable[yyj]))
	  return;
      }

  /* Reduce to one stack.  */
  for (yyk = 0; yyk < yystack->yytops.yysize; yyk += 1)
    if (yystack->yytops.yystates[yyk] != NULL)
      break;
  if (yyk >= yystack->yytops.yysize)
    yyFail (yystack, NULL);
  for (yyk += 1; yyk < yystack->yytops.yysize; yyk += 1)
    yymarkStackDeleted (yystack, yyk);
  yyremoveDeletes (yystack);
  yycompressStack (yystack);

  /* Now pop stack until we find a state that shifts the error token. */
  yystack->yyerrState = 3;
  while (yystack->yytops.yystates[0] != NULL)
    {
      yyGLRState *yys = yystack->yytops.yystates[0];
      yyj = yypact[yys->yylrState];
      if (! yyis_pact_ninf (yyj))
	{
	  yyj += YYTERROR;
	  if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYTERROR
	      && yyisShiftAction (yytable[yyj]))
	    {
	      /* Shift the error token having adjusted its location.  */
	      YYLTYPE yyerrloc;
	      YY_SYMBOL_PRINT ("Shifting", yystos[yytable[yyj]],
			       yylvalp, &yyerrloc);
	      yyglrShift (yystack, 0, yytable[yyj],
			  yys->yyposn, *yylvalp, &yyerrloc);
	      yys = yystack->yytops.yystates[0];
	      break;
	    }
	}

      yydestroyGLRState ("Error: popping", yys);
      yystack->yytops.yystates[0] = yys->yypred;
      yystack->yynextFree -= 1;
      yystack->yyspaceLeft += 1;
    }
  if (yystack->yytops.yystates[0] == NULL)
    yyFail (yystack, NULL);
}

#define YYCHK1(YYE)							     \
  do {									     \
    switch (YYE) {							     \
    case yyok:								     \
      break;								     \
    case yyabort:							     \
      goto yyabortlab;							     \
    case yyaccept:							     \
      goto yyacceptlab;							     \
    case yyerr:								     \
      goto yyuser_error;						     \
    default:								     \
      goto yybuglab;							     \
    }									     \
  } while (0)


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
  int yyresult;
  yySymbol yytoken;
  yyGLRStack yystack;
  size_t yyposn;


  YYSTYPE* const yylvalp = &yylval;
  YYLTYPE* const yyllocp = &yylloc;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yytoken = YYEMPTY;
  yylval = yyval_default;


  if (! yyinitGLRStack (&yystack, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yystack.yytokenp = &yytoken;
  yyglrShift (&yystack, 0, 0, 0, yylval, &yylloc);
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
	 specialized to deterministic operation (single stack, no
	 potential ambiguity).  */
      /* Standard mode */
      while (yytrue)
	{
	  yyRuleNum yyrule;
	  int yyaction;
	  const short int* yyconflicts;

	  yyStateNum yystate = yystack.yytops.yystates[0]->yylrState;
          YYDPRINTF ((stderr, "Entering state %d\n", yystate));
	  if (yystate == YYFINAL)
	    goto yyacceptlab;
	  if (yyisDefaultedState (yystate))
	    {
	      yyrule = yydefaultAction (yystate);
	      if (yyrule == 0)
		{

		  yyreportSyntaxError (&yystack, yylvalp, yyllocp);
		  goto yyuser_error;
		}
	      YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue));
	    }
	  else
	    {
	      if (yytoken == YYEMPTY)
		{
		  YYDPRINTF ((stderr, "Reading a token: "));
		  yychar = YYLEX;
		  yytoken = YYTRANSLATE (yychar);
                  YY_SYMBOL_PRINT ("Next token is", yytoken, yylvalp, yyllocp);
		}
	      yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);
	      if (*yyconflicts != 0)
		break;
	      if (yyisShiftAction (yyaction))
		{
		  YY_SYMBOL_PRINT ("Shifting", yytoken, yylvalp, yyllocp);
		  if (yytoken != YYEOF)
		    yytoken = YYEMPTY;
		  yyposn += 1;
		  yyglrShift (&yystack, 0, yyaction, yyposn, yylval, yyllocp);
		  if (0 < yystack.yyerrState)
		    yystack.yyerrState -= 1;
		}
	      else if (yyisErrorAction (yyaction))
		{

		  yyreportSyntaxError (&yystack, yylvalp, yyllocp);
		  goto yyuser_error;
		}
	      else
		YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue));
	    }
	}

      while (yytrue)
	{
	  size_t yys;
	  size_t yyn = yystack.yytops.yysize;
	  for (yys = 0; yys < yyn; yys += 1)
	    YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn,
				       yylvalp, yyllocp));
	  yytoken = YYEMPTY;
	  yyposn += 1;
	  yyremoveDeletes (&yystack);
	  if (yystack.yytops.yysize == 0)
	    {
	      yyundeleteLastStack (&yystack);
	      if (yystack.yytops.yysize == 0)
		yyFail (&yystack, YY_("syntax error"));
	      YYCHK1 (yyresolveStack (&yystack));
	      YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));

	      yyreportSyntaxError (&yystack, yylvalp, yyllocp);
	      goto yyuser_error;
	    }
	  else if (yystack.yytops.yysize == 1)
	    {
	      YYCHK1 (yyresolveStack (&yystack));
	      YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
	      yycompressStack (&yystack);
	      break;
	    }
	}
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack, yylvalp, yyllocp);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturn;

 yybuglab:
  YYASSERT (yyfalse);
  /* Fall through.  */

 yyabortlab:
  yyresult = 1;
  goto yyreturn;

 yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */

 yyreturn:
  if (yytoken != YYEOF && yytoken != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
                yytoken, yylvalp);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
	while (yystates[0])
	  {
	    yyGLRState *yys = yystates[0];
	    yydestroyGLRState ("Cleanup: popping", yys);
	    yystates[0] = yys->yypred;
	    yystack.yynextFree -= 1;
	    yystack.yyspaceLeft += 1;
	  }
      yyfreeGLRStack (&yystack);
    }

  return yyresult;
}

/* DEBUGGING ONLY */
#ifdef YYDEBUG
static void yypstack (yyGLRStack* yystack, size_t yyk)
  __attribute__ ((__unused__));
static void yypdumpstack (yyGLRStack* yystack) __attribute__ ((__unused__));

static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      fprintf (stderr, " -> ");
    }
  fprintf (stderr, "%d@%lu", yys->yylrState, (unsigned long int) yys->yyposn);
}

static void
yypstates (yyGLRState* yyst)
{
  if (yyst == NULL)
    fprintf (stderr, "<null>");
  else
    yy_yypstack (yyst);
  fprintf (stderr, "\n");
}

static void
yypstack (yyGLRStack* yystack, size_t yyk)
{
  yypstates (yystack->yytops.yystates[yyk]);
}

#define YYINDEX(YYX)							     \
    ((YYX) == NULL ? -1 : (yyGLRStackItem*) (YYX) - yystack->yyitems)


static void
yypdumpstack (yyGLRStack* yystack)
{
  yyGLRStackItem* yyp;
  size_t yyi;
  for (yyp = yystack->yyitems; yyp < yystack->yynextFree; yyp += 1)
    {
      fprintf (stderr, "%3lu. ", (unsigned long int) (yyp - yystack->yyitems));
      if (*(yybool *) yyp)
	{
	  fprintf (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
		   yyp->yystate.yyresolved, yyp->yystate.yylrState,
		   (unsigned long int) yyp->yystate.yyposn,
		   (long int) YYINDEX (yyp->yystate.yypred));
	  if (! yyp->yystate.yyresolved)
	    fprintf (stderr, ", firstVal: %ld",
		     (long int) YYINDEX (yyp->yystate.yysemantics.yyfirstVal));
	}
      else
	{
	  fprintf (stderr, "Option. rule: %d, state: %ld, next: %ld",
		   yyp->yyoption.yyrule,
		   (long int) YYINDEX (yyp->yyoption.yystate),
		   (long int) YYINDEX (yyp->yyoption.yynext));
	}
      fprintf (stderr, "\n");
    }
  fprintf (stderr, "Tops:");
  for (yyi = 0; yyi < yystack->yytops.yysize; yyi += 1)
    fprintf (stderr, "%lu: %ld; ", (unsigned long int) yyi,
	     (long int) YYINDEX (yystack->yytops.yystates[yyi]));
  fprintf (stderr, "\n");
}
#endif



