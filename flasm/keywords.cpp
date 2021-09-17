/* ANSI-C code produced by gperf version 2.7.2 */
/* Command-line: gperf --language=ANSI-C -t -T -E -D -k '1-7,$' -S1 keywords.gperf  */
/*
flasm, command line assembler & disassembler of flash actionscript bytecode
Copyright (c) 2001 Opaque Industries, (c) 2002-2003 Igor Kogan
All rights reserved. See LICENSE.TXT for terms of use.
*/

#include <string.h>
#include "assembler.tab.h"
#include "util.h"
struct keyword *in_word_set(register const char *str, register unsigned int len);
/* maximum key range = 1463, duplicates = 5 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (register const char *str, register unsigned int len)
{
  static unsigned short asso_values[] =
    {
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,    0, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
        90, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466,   79, 1466,  165,   28,  175,
       113,    0,  190,  142,  110,   20,    0,   65,  235,   70,
         0,   88,  229,  115,    0,    0,    0,   45,   65,   35,
       135,  247,    0, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466, 1466,
      1466, 1466, 1466, 1466, 1466, 1466
    };
  register int hval = len;

  switch (hval)
    {
      default:
      case 7:
        hval += asso_values[(unsigned char)str[6]];
      case 6:
        hval += asso_values[(unsigned char)str[5]];
      case 5:
        hval += asso_values[(unsigned char)str[4]];
      case 4:
        hval += asso_values[(unsigned char)str[3]];
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      case 2:
        hval += asso_values[(unsigned char)str[1]];
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

#ifdef __GNUC__
__inline
#endif
struct keyword *
in_word_set (register const char *str, register unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 248,
      MIN_WORD_LENGTH = 3,
      MAX_WORD_LENGTH = 22,
      MIN_HASH_VALUE = 3,
      MAX_HASH_VALUE = 1465
    };

  static struct keyword wordlist[] =
    {
      {"&jz",                     1,              BRANCHIFFALSE},
      {"&jnz",                    1,              BRANCHIFTRUE},
      {"&int",                    1,              INT },
      {"&true",                   0,              TRUEVAL },
      {"&return",                 1,              RETURN },
      {"&new",                    1,              NEW },
      {"&_enter",                 0,              _ENTER },
      {"&on",                    -1,              ON},
      {"&or",                     1,              LOGICALOR },
      {"&not",                    1,              LOGICALNOT },
      {"&_insert",                0,              _INSERT },
      {"&bitwiseor",              1,              BITWISEOR },
      {"&bitwisexor",             1,              BITWISEXOR },
      {"&enumerate",              1,              ENUMERATE },
      {"&enumeratevalue",         1,              ENUMERATEVALUE },
      {"&get",                    0,              GET },
      {"&setmember",              1,              SETMEMBER },
      {"&setregister",            1,              SETREGISTER },
      {"&initobject",             1,              INITOBJECT },
      {"&as",                     0,              AS },
      {"&settarget",              2,              SETTARGET },
      {"&stringlessthan",         1,              STRINGLESSTHAN },
      {"&settargetexpr",          2,              SETTARGETEXPR },
      {"&stringgreaterthan",      1,              STRINGGREATERTHAN },
      {"&enterframe",             0,              MCENTERFRAME },
      {"&newequals",              1,              NEWEQUALS },
      {"&strictmode",             1,              STRICTMODE },
      {"&strictequals",           1,              STRICTEQUALS },
      {"&substring",              1,              SUBSTRING },
      {"&bitwiseand",             1,              BITWISEAND },
      {"&newmethod",              1,              NEWMETHOD },
      {"&end",                    0,              END },
      {"&recursion",              0,              RECURSION},
      {"&timeout",                0,              TIMEOUT},
      {"&var",                    1,              VAR },
      {"&press",                  0,              MCPRESS },
      {"&initialize",             0,              MCINITIALIZE },
      {"&tonumber",               1,              TONUMBER },
      {"&gettimer",               1,              GETTIMER },
      {"&setvariable",            1,              SETVARIABLE },
      {"&subtract",               1,              SUBTRACT },
      {"&_nan",                   0,              _NAN },
      {"&extends",                1,              EXTENDS },
      {"&tostring",               1,              TOSTRING },
      {"&construct",              0,              MCCONSTRUCT },
      {"&throw",                  1,              THROW },
      {"&increment",              1,              INCREMENT },
      {"&with",                   1,              WITH },
      {"&newlessthan",            1,              NEWLESSTHAN },
      {"&mousemove",              0,              MCMOUSEMOVE },
      {"&stringlength",           1,              STRINGLENGTH },
      {"&stringeq",               1,              STRINGEQ },
      {"&chr",                    1,              CHR },
      {"&getmember",              1,              GETMEMBER },
      {"&_tab",                   0,              _TAB },
      {"&_end",                   0,              _END },
      {"&ord",                    1,              ORD },
      {"&greaterthan",            1,              GREATERTHAN },
      {"&_down",                  0,              _DOWN },
      {"&post",                   0,              POST },
      {"&mbsubstring",            1,              MBSUBSTRING },
      {"&mousedown",              0,              MCMOUSEDOWN },
      {"&shiftright",             1,              SHIFTRIGHT },
      {"&nextframe",              1,              NEXTFRAME },
      {"&definebutton",           0,              DEFINEBUTTON },
      {"&divide",                 1,              DIVIDE },
      {"&cast",                   1,              CAST },
      {"&trace",                  1,              TRACE },
      {"&_home",                  0,              _HOME },
      {"&lessthan",               1,              NEWLESSTHAN },
      {"&delete",                 1,              DELETE },
      {"&_right",                 0,              _RIGHT },
      {"&decrement",              1,              DECREMENT },
      {"&overdowntoidle",         0,              BOVERDOWNTOIDLE},
      {"&overdowntooutdown",      0,              BOVERDOWNTOOUTDOWN},
      {"&outdowntoidle",          0,              BOUTDOWNTOIDLE },
      {"&getvariable",            1,              GETVARIABLE },
      {"&instanceof",             1,              INSTANCEOF },
      {"&outdowntooverdown",      0,              BOUTDOWNTOOVERDOWN},
      {"&mbchr",                  1,              MBCHR },
      {"&pushs",                  1,              PUSHS},
      {"&pushtrue",               1,              PUSHTRUE},
      {"&and",                    1,              LOGICALAND },
      {"&pushregister",           1,              PUSHREGISTER},
      {"&varequals",              1,              VAREQUALS },
      {"&release",                0,              MCRELEASE },
      {"&releaseoutside",         0,              MCRELEASEOUTSIDE },
      {"&stopsounds",             1,              STOPSOUNDS },
      {"&mbord",                  1,              MBORD },
      {"&importassets",           0,              IMPORTASSETS },
      {"&shiftright2",            1,              SHIFTRIGHT2 },
      {"&from",                   0,              FROM},
      {"&targetpath",             1,              TARGETPATH},
      {"&startdrag",              1,              STARTDRAGMOVIE },
      {"&frame",                 -1,              FRAME},
      {"&_delete",                0,              _DELETE },
      {"&scriptlimits",           0,              SCRIPTLIMITS},
      {"&constants",              1,              CONSTANTS },
      {"&function",               1,              FUNCTION },
      {"&overuptoidle",           0,              BOVERUPTOIDLE },
      {"&initmovieclip",         -1,              INITMOVIECLIP},
      {"&enabledebugger",         0,              ENABLEDEBUGGER },
      {"&overuptooverdown",       0,              BOVERUPTOOVERDOWN },
      {"&delete2",                1,              DELETE2 },
      {"&pushssv",                1,              PUSHSSV},
      {"&pushzerosv",             1,              PUSHZEROSV},
      {"&pushssm",                1,              PUSHSSM},
      {"&initarray",              1,              INITARRAY },
      {"&removeclip",             1,              REMOVECLIP },
      {"&exportassets",           0,              EXPORTASSETS },
      {"&idletooverdown",         0,              BIDLETOOVERDOWN },
      {"&pushone",                1,              PUSHONE},
      {"&pushzero",               1,              PUSHZERO},
      {"&mouseup",                0,              MCMOUSEUP },
      {"&currentframe_property",  0,              CURRENTFRAME_PROPERTY },
      {"&branchalways",           1,              BRANCHALWAYS },
      {"&branchiftrue",           1,              BRANCHIFTRUE },
      {"&prevframe",              1,              PREVFRAME },
      {"&try",                    1,              TRY },
      {"&push",                   1,              PUSH },
      {"&protect",                0,              PROTECT},
      {"&pushthis",               1,              PUSHTHIS},
      {"&pushshort",              1,              PUSHSHORT},
      {"&add",                    1,              NEWADD },
      {"&_left",                  0,              _LEFT },
      {"&random",                 1,              RANDOM },
      {"&gotoframe",              1,              GOTOFRAME },
      {"&geturl2",                1,              GETURL2 },
      {"&_backspace",             0,              _BACKSPACE},
      {"&function2",              1,              FUNCTION2 },
      {"&jmp",                    1,              BRANCHALWAYS},
      {"&pushsdb",                1,              PUSHSDB},
      {"&enabledebugger2",        0,              ENABLEDEBUGGER2 },
      {"&negative_infinityf",     0,              NEGATIVE_INFINITYF },
      {"&rotation_property",      0,              ROTATION_PROPERTY },
      {"&pushsdw",                1,              PUSHSDW},
      {"&soundbuftime_property",  0,              SOUNDBUFTIME_PROPERTY },
      {"&undef",                  0,              UNDEFVAL },
      {"&newadd",                 1,              NEWADD },
      {"&skip",                   0,              SKIP },
      {"&keypress",               0,              KEYPRESS },
      {"&stop",                   1,              STOP },
      {"&keydown",                0,              MCKEYDOWN },
      {"&dragout",                0,              MCDRAGOUT },
      {"&shiftleft",              1,              SHIFTLEFT },
      {"&positive_infinityf",     0,              POSITIVE_INFINITYF },
      {"&equals",                 1,              NEWEQUALS },
      {"&definemovieclip",        0,              DEFINEMOVIECLIP },
      {"&_pgdn",                  0,              _PGDN },
      {"&target_property",        0,              TARGET_PROPERTY },
      {"&pushthisgv",             1,              PUSHTHISGV},
      {"&pushsdbgv",              1,              PUSHSDBGV},
      {"&apttracestart",          1,              APTTRACESTART},
      {"&swfaction",              1,              SWFACTION},
      {"&setproperty",            1,              SETPROPERTY },
      {"&pushsdbgm",              1,              PUSHSDBGM},
      {"&stopdrag",               1,              STOPDRAGMOVIE },
      {"&dragover",               0,              MCDRAGOVER },
      {"&_up",                    0,              _UP },
      {"&negative_infinity",      0,              NEGATIVE_INFINITY },
      {"&mblength",               1,              MBLENGTH },
      {"&branch",                 1,              BRANCHALWAYS },
      {"&false",                  0,              FALSEVAL },
      {"&pushsgv",                1,              PUSHSGV},
      {"&overdowntooverup",       0,              BOVERDOWNTOOVERUP },
      {"&xmouse_property",        0,              XMOUSE_PROPERTY },
      {"&pushsgm",                1,              PUSHSGM},
      {"&oldequals",              1,              OLDEQUALS },
      {"&concat",                 1,              STRINGCONCAT },
      {"&data",                   0,              MCDATA },
      {"&width_property",         0,              WIDTH_PROPERTY },
      {"&dup",                    1,              DUP },
      {"&positive_infinity",      0,              POSITIVE_INFINITY },
      {"&pushundef",              1,              PUSHUNDEF},
      {"&_nanf",                  0,              _NANF },
      {"&visible_property",       0,              VISIBLE_PROPERTY },
      {"&implements",             1,              IMPLEMENTS },
      {"&height_property",        0,              HEIGHT_PROPERTY },
      {"&ifframeloadedexpr",      1,              IFFRAMELOADEDEXPR },
      {"&_space",                 0,              _SPACE },
      {"&_escape",                0,              _ESCAPE },
      {"&off",                    0,              OFF },
      {"&swap",                   1,              SWAP },
      {"&geturl",                 1,              GETURL },
      {"&pushbyte",               1,              PUSHBYTE},
      {"&pushnull",               1,              PUSHNULL},
      {"&oldlessthan",            1,              OLDLESSTHAN },
      {"&compressed",             0,              COMPRESSED},
      {"&framesloaded_property",  0,              FRAMESLOADED_PROPERTY },
      {"&hexdata",                0,              HEXDATA },
      {"&idletooverup",           0,              BIDLETOOVERUP },
      {"&rollout",                0,              MCROLLOUT },
      {"&ymouse_property",        0,              YMOUSE_PROPERTY },
      {"&getproperty",            1,              GETPROPERTY },
      {"&load",                   0,              MCLOAD },
      {"&rollover",               0,              MCROLLOVER },
      {"&gotoandstop",            1,              GOTOANDSTOP },
      {"&modulo",                 1,              MODULO },
      {"&catch",                  0,              CATCH },
      {"&gotoandplay",            1,              GOTOANDPLAY },
      {"&pushfalse",              1,              PUSHFALSE},
      {"&null",                   0,              NULLVAL },
      {"&onclipevent",           -1,              ONCLIPEVENT},
      {"&ifframeloaded",          1,              IFFRAMELOADED },
      {"&focusrect_property",     0,              FOCUSRECT_PROPERTY },
      {"&unload",                 0,              MCUNLOAD },
      {"&loadmovie",              1,              LOADMOVIE },
      {"&pop",                    1,              POP },
      {"&name_property",          0,              NAME_PROPERTY },
      {"&highquality_property",   0,              HIGHQUALITY_PROPERTY },
      {"&pushfloat",              1,              PUSHFLOAT},
      {"&keyup",                  0,              MCKEYUP },
      {"&pushglobalgv",           1,              PUSHGLOBALGV},
      {"&loadmovienum",           1,              LOADMOVIENUM },
      {"&quality_property",       0,              QUALITY_PROPERTY },
      {"&loadvariables",          1,              LOADVARIABLES },
      {"&url_property",           0,              URL_PROPERTY },
      {"&multiply",               1,              MULTIPLY },
      {"&pushlong",               1,              PUSHLONG},
      {"&droptarget_property",    0,              DROPTARGET_PROPERTY },
      {"&togglequality",          1,              TOGGLEQUALITY },
      {"&loadvariablesnum",       1,              LOADVARIABLESNUM },
      {"&totalframes_property",   0,              TOTALFRAMES_PROPERTY },
      {"&oldadd",                 1,              OLDADD },
      {"&typeof",                 1,              TYPEOF },
      {"&callmsv",                1,              CALLMSV},
      {"&_pgup",                  0,              _PGUP },
      {"&gotolabel",              1,              GOTOLABEL },
      {"&xscale_property",        0,              XSCALE_PROPERTY },
      {"&callmethod",             1,              CALLMETHOD },
      {"&pushglobal",             1,              PUSHGLOBAL},
      {"&callframe",              1,              CALLFRAME },
      {"&x_property",             0,              X_PROPERTY },
      {"&callfunction",           1,              CALLFUNCTION },
      {"&duplicateclip",          1,              DUPLICATECLIP },
      {"&dcallmsv",               1,              DCALLMSV},
      {"&callfsv",                1,              CALLFSV},
      {"&yscale_property",        0,              YSCALE_PROPERTY },
      {"&finally",                0,              FINALLY },
      {"&placemovieclip",         0,              PLACEMOVIECLIP },
      {"&play",                   1,              PLAY },
      {"&y_property",             0,              Y_PROPERTY },
      {"&dcallfsv",               1,              DCALLFSV},
      {"&dcallmp",                1,              DCALLMP},
      {"&alpha_property",         0,              ALPHA_PROPERTY },
      {"&callmp",                 1,              CALLMP},
      {"&dcallfp",                1,              DCALLFP},
      {"&callfp",                 1,              CALLFP}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE)
        {
          register struct keyword *wordptr;
          register struct keyword *wordendptr;
          register struct keyword *resword;

          switch (key - 3)
            {
              case 0:
                resword = &wordlist[0];
                goto compare;
              case 1:
                resword = &wordlist[1];
                goto compare;
              case 21:
                resword = &wordlist[2];
                goto compare;
              case 47:
                resword = &wordlist[3];
                goto compare;
              case 49:
                resword = &wordlist[4];
                goto compare;
              case 71:
                resword = &wordlist[5];
                goto compare;
              case 83:
                resword = &wordlist[6];
                goto compare;
              case 88:
                wordptr = &wordlist[7];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 89:
                resword = &wordlist[9];
                goto compare;
              case 104:
                resword = &wordlist[10];
                goto compare;
              case 110:
                resword = &wordlist[11];
                goto compare;
              case 111:
                resword = &wordlist[12];
                goto compare;
              case 122:
                resword = &wordlist[13];
                goto compare;
              case 127:
                resword = &wordlist[14];
                goto compare;
              case 143:
                resword = &wordlist[15];
                goto compare;
              case 147:
                resword = &wordlist[16];
                goto compare;
              case 151:
                resword = &wordlist[17];
                goto compare;
              case 164:
                resword = &wordlist[18];
                goto compare;
              case 165:
                resword = &wordlist[19];
                goto compare;
              case 172:
                resword = &wordlist[20];
                goto compare;
              case 174:
                resword = &wordlist[21];
                goto compare;
              case 176:
                resword = &wordlist[22];
                goto compare;
              case 177:
                resword = &wordlist[23];
                goto compare;
              case 198:
                resword = &wordlist[24];
                goto compare;
              case 202:
                resword = &wordlist[25];
                goto compare;
              case 203:
                resword = &wordlist[26];
                goto compare;
              case 205:
                resword = &wordlist[27];
                goto compare;
              case 222:
                resword = &wordlist[28];
                goto compare;
              case 224:
                resword = &wordlist[29];
                goto compare;
              case 225:
                resword = &wordlist[30];
                goto compare;
              case 227:
                wordptr = &wordlist[31];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 228:
                resword = &wordlist[33];
                goto compare;
              case 231:
                resword = &wordlist[34];
                goto compare;
              case 232:
                resword = &wordlist[35];
                goto compare;
              case 233:
                resword = &wordlist[36];
                goto compare;
              case 237:
                resword = &wordlist[37];
                goto compare;
              case 238:
                resword = &wordlist[38];
                goto compare;
              case 239:
                resword = &wordlist[39];
                goto compare;
              case 244:
                resword = &wordlist[40];
                goto compare;
              case 246:
                resword = &wordlist[41];
                goto compare;
              case 253:
                resword = &wordlist[42];
                goto compare;
              case 256:
                resword = &wordlist[43];
                goto compare;
              case 270:
                resword = &wordlist[44];
                goto compare;
              case 271:
                resword = &wordlist[45];
                goto compare;
              case 272:
                resword = &wordlist[46];
                goto compare;
              case 277:
                resword = &wordlist[47];
                goto compare;
              case 279:
                resword = &wordlist[48];
                goto compare;
              case 280:
                resword = &wordlist[49];
                goto compare;
              case 282:
                resword = &wordlist[50];
                goto compare;
              case 283:
                resword = &wordlist[51];
                goto compare;
              case 286:
                resword = &wordlist[52];
                goto compare;
              case 289:
                resword = &wordlist[53];
                goto compare;
              case 302:
                resword = &wordlist[54];
                goto compare;
              case 307:
                resword = &wordlist[55];
                goto compare;
              case 315:
                resword = &wordlist[56];
                goto compare;
              case 316:
                resword = &wordlist[57];
                goto compare;
              case 318:
                resword = &wordlist[58];
                goto compare;
              case 319:
                resword = &wordlist[59];
                goto compare;
              case 322:
                resword = &wordlist[60];
                goto compare;
              case 323:
                resword = &wordlist[61];
                goto compare;
              case 328:
                resword = &wordlist[62];
                goto compare;
              case 332:
                resword = &wordlist[63];
                goto compare;
              case 333:
                resword = &wordlist[64];
                goto compare;
              case 335:
                resword = &wordlist[65];
                goto compare;
              case 342:
                resword = &wordlist[66];
                goto compare;
              case 343:
                resword = &wordlist[67];
                goto compare;
              case 350:
                resword = &wordlist[68];
                goto compare;
              case 351:
                resword = &wordlist[69];
                goto compare;
              case 352:
                resword = &wordlist[70];
                goto compare;
              case 355:
                resword = &wordlist[71];
                goto compare;
              case 365:
                resword = &wordlist[72];
                goto compare;
              case 366:
                resword = &wordlist[73];
                goto compare;
              case 369:
                resword = &wordlist[74];
                goto compare;
              case 380:
                resword = &wordlist[75];
                goto compare;
              case 381:
                resword = &wordlist[76];
                goto compare;
              case 383:
                resword = &wordlist[77];
                goto compare;
              case 384:
                resword = &wordlist[78];
                goto compare;
              case 386:
                resword = &wordlist[79];
                goto compare;
              case 387:
                resword = &wordlist[80];
                goto compare;
              case 390:
                resword = &wordlist[81];
                goto compare;
              case 392:
                resword = &wordlist[82];
                goto compare;
              case 394:
                resword = &wordlist[83];
                goto compare;
              case 397:
                resword = &wordlist[84];
                goto compare;
              case 405:
                resword = &wordlist[85];
                goto compare;
              case 412:
                resword = &wordlist[86];
                goto compare;
              case 413:
                resword = &wordlist[87];
                goto compare;
              case 415:
                resword = &wordlist[88];
                goto compare;
              case 417:
                resword = &wordlist[89];
                goto compare;
              case 419:
                resword = &wordlist[90];
                goto compare;
              case 420:
                resword = &wordlist[91];
                goto compare;
              case 425:
                resword = &wordlist[92];
                goto compare;
              case 427:
                resword = &wordlist[93];
                goto compare;
              case 428:
                resword = &wordlist[94];
                goto compare;
              case 432:
                resword = &wordlist[95];
                goto compare;
              case 434:
                resword = &wordlist[96];
                goto compare;
              case 435:
                resword = &wordlist[97];
                goto compare;
              case 436:
                resword = &wordlist[98];
                goto compare;
              case 437:
                resword = &wordlist[99];
                goto compare;
              case 438:
                resword = &wordlist[100];
                goto compare;
              case 440:
                resword = &wordlist[101];
                goto compare;
              case 441:
                resword = &wordlist[102];
                goto compare;
              case 443:
                resword = &wordlist[103];
                goto compare;
              case 454:
                resword = &wordlist[104];
                goto compare;
              case 457:
                resword = &wordlist[105];
                goto compare;
              case 459:
                wordptr = &wordlist[106];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 460:
                resword = &wordlist[108];
                goto compare;
              case 462:
                resword = &wordlist[109];
                goto compare;
              case 468:
                resword = &wordlist[110];
                goto compare;
              case 477:
                resword = &wordlist[111];
                goto compare;
              case 478:
                resword = &wordlist[112];
                goto compare;
              case 482:
                resword = &wordlist[113];
                goto compare;
              case 486:
                resword = &wordlist[114];
                goto compare;
              case 488:
                wordptr = &wordlist[115];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 491:
                resword = &wordlist[117];
                goto compare;
              case 495:
                resword = &wordlist[118];
                goto compare;
              case 496:
                resword = &wordlist[119];
                goto compare;
              case 497:
                resword = &wordlist[120];
                goto compare;
              case 500:
                resword = &wordlist[121];
                goto compare;
              case 501:
                resword = &wordlist[122];
                goto compare;
              case 505:
                resword = &wordlist[123];
                goto compare;
              case 507:
                resword = &wordlist[124];
                goto compare;
              case 510:
                resword = &wordlist[125];
                goto compare;
              case 515:
                resword = &wordlist[126];
                goto compare;
              case 517:
                resword = &wordlist[127];
                goto compare;
              case 520:
                resword = &wordlist[128];
                goto compare;
              case 527:
                resword = &wordlist[129];
                goto compare;
              case 529:
                resword = &wordlist[130];
                goto compare;
              case 530:
                resword = &wordlist[131];
                goto compare;
              case 531:
                resword = &wordlist[132];
                goto compare;
              case 533:
                resword = &wordlist[133];
                goto compare;
              case 535:
                resword = &wordlist[134];
                goto compare;
              case 537:
                resword = &wordlist[135];
                goto compare;
              case 540:
                resword = &wordlist[136];
                goto compare;
              case 541:
                resword = &wordlist[137];
                goto compare;
              case 543:
                resword = &wordlist[138];
                goto compare;
              case 545:
                resword = &wordlist[139];
                goto compare;
              case 547:
                resword = &wordlist[140];
                goto compare;
              case 548:
                resword = &wordlist[141];
                goto compare;
              case 553:
                resword = &wordlist[142];
                goto compare;
              case 558:
                resword = &wordlist[143];
                goto compare;
              case 562:
                resword = &wordlist[144];
                goto compare;
              case 563:
                resword = &wordlist[145];
                goto compare;
              case 564:
                resword = &wordlist[146];
                goto compare;
              case 565:
                resword = &wordlist[147];
                goto compare;
              case 566:
                resword = &wordlist[148];
                goto compare;
              case 567:
                wordptr = &wordlist[149];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 569:
                resword = &wordlist[151];
                goto compare;
              case 570:
                resword = &wordlist[152];
                goto compare;
              case 572:
                resword = &wordlist[153];
                goto compare;
              case 573:
                resword = &wordlist[154];
                goto compare;
              case 574:
                resword = &wordlist[155];
                goto compare;
              case 578:
                resword = &wordlist[156];
                goto compare;
              case 579:
                resword = &wordlist[157];
                goto compare;
              case 583:
                resword = &wordlist[158];
                goto compare;
              case 589:
                resword = &wordlist[159];
                goto compare;
              case 591:
                resword = &wordlist[160];
                goto compare;
              case 592:
                resword = &wordlist[161];
                goto compare;
              case 593:
                resword = &wordlist[162];
                goto compare;
              case 596:
                resword = &wordlist[163];
                goto compare;
              case 597:
                resword = &wordlist[164];
                goto compare;
              case 598:
                resword = &wordlist[165];
                goto compare;
              case 601:
                resword = &wordlist[166];
                goto compare;
              case 603:
                resword = &wordlist[167];
                goto compare;
              case 607:
                resword = &wordlist[168];
                goto compare;
              case 610:
                resword = &wordlist[169];
                goto compare;
              case 616:
                resword = &wordlist[170];
                goto compare;
              case 617:
                resword = &wordlist[171];
                goto compare;
              case 619:
                resword = &wordlist[172];
                goto compare;
              case 626:
                resword = &wordlist[173];
                goto compare;
              case 627:
                resword = &wordlist[174];
                goto compare;
              case 629:
                resword = &wordlist[175];
                goto compare;
              case 632:
                resword = &wordlist[176];
                goto compare;
              case 642:
                resword = &wordlist[177];
                goto compare;
              case 650:
                resword = &wordlist[178];
                goto compare;
              case 652:
                resword = &wordlist[179];
                goto compare;
              case 653:
                resword = &wordlist[180];
                goto compare;
              case 659:
                resword = &wordlist[181];
                goto compare;
              case 660:
                resword = &wordlist[182];
                goto compare;
              case 661:
                resword = &wordlist[183];
                goto compare;
              case 665:
                resword = &wordlist[184];
                goto compare;
              case 670:
                resword = &wordlist[185];
                goto compare;
              case 680:
                resword = &wordlist[186];
                goto compare;
              case 683:
                resword = &wordlist[187];
                goto compare;
              case 691:
                resword = &wordlist[188];
                goto compare;
              case 693:
                resword = &wordlist[189];
                goto compare;
              case 695:
                resword = &wordlist[190];
                goto compare;
              case 696:
                resword = &wordlist[191];
                goto compare;
              case 710:
                resword = &wordlist[192];
                goto compare;
              case 715:
                resword = &wordlist[193];
                goto compare;
              case 716:
                resword = &wordlist[194];
                goto compare;
              case 717:
                resword = &wordlist[195];
                goto compare;
              case 721:
                resword = &wordlist[196];
                goto compare;
              case 731:
                resword = &wordlist[197];
                goto compare;
              case 738:
                resword = &wordlist[198];
                goto compare;
              case 739:
                resword = &wordlist[199];
                goto compare;
              case 746:
                resword = &wordlist[200];
                goto compare;
              case 752:
                resword = &wordlist[201];
                goto compare;
              case 756:
                resword = &wordlist[202];
                goto compare;
              case 759:
                resword = &wordlist[203];
                goto compare;
              case 761:
                resword = &wordlist[204];
                goto compare;
              case 763:
                resword = &wordlist[205];
                goto compare;
              case 766:
                resword = &wordlist[206];
                goto compare;
              case 776:
                resword = &wordlist[207];
                goto compare;
              case 801:
                resword = &wordlist[208];
                goto compare;
              case 807:
                resword = &wordlist[209];
                goto compare;
              case 816:
                resword = &wordlist[210];
                goto compare;
              case 818:
                resword = &wordlist[211];
                goto compare;
              case 836:
                resword = &wordlist[212];
                goto compare;
              case 839:
                resword = &wordlist[213];
                goto compare;
              case 841:
                resword = &wordlist[214];
                goto compare;
              case 842:
                resword = &wordlist[215];
                goto compare;
              case 845:
                resword = &wordlist[216];
                goto compare;
              case 852:
                resword = &wordlist[217];
                goto compare;
              case 855:
                resword = &wordlist[218];
                goto compare;
              case 859:
                resword = &wordlist[219];
                goto compare;
              case 865:
                resword = &wordlist[220];
                goto compare;
              case 915:
                resword = &wordlist[221];
                goto compare;
              case 943:
                resword = &wordlist[222];
                goto compare;
              case 944:
                resword = &wordlist[223];
                goto compare;
              case 948:
                resword = &wordlist[224];
                goto compare;
              case 950:
                resword = &wordlist[225];
                goto compare;
              case 956:
                resword = &wordlist[226];
                goto compare;
              case 960:
                resword = &wordlist[227];
                goto compare;
              case 970:
                resword = &wordlist[228];
                goto compare;
              case 1001:
                resword = &wordlist[229];
                goto compare;
              case 1004:
                resword = &wordlist[230];
                goto compare;
              case 1007:
                resword = &wordlist[231];
                goto compare;
              case 1015:
                resword = &wordlist[232];
                goto compare;
              case 1055:
                resword = &wordlist[233];
                goto compare;
              case 1057:
                resword = &wordlist[234];
                goto compare;
              case 1064:
                resword = &wordlist[235];
                goto compare;
              case 1070:
                resword = &wordlist[236];
                goto compare;
              case 1082:
                resword = &wordlist[237];
                goto compare;
              case 1097:
                resword = &wordlist[238];
                goto compare;
              case 1115:
                resword = &wordlist[239];
                goto compare;
              case 1125:
                resword = &wordlist[240];
                goto compare;
              case 1127:
                resword = &wordlist[241];
                goto compare;
              case 1184:
                resword = &wordlist[242];
                goto compare;
              case 1227:
                resword = &wordlist[243];
                goto compare;
              case 1242:
                resword = &wordlist[244];
                goto compare;
              case 1342:
                resword = &wordlist[245];
                goto compare;
              case 1347:
                resword = &wordlist[246];
                goto compare;
              case 1462:
                resword = &wordlist[247];
                goto compare;
            }
          return 0;
        multicompare:
          while (wordptr < wordendptr)
            {
              register const char *s = wordptr->name;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return wordptr;
              wordptr++;
            }
          return 0;
        compare:
          {
            register const char *s = resword->name;

            if (*str == *s && !strcmp (str + 1, s + 1))
              return resword;
          }
        }
    }
  return 0;
}
