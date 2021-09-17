/*
flasm, command line assembler & disassembler of flash actionscript bytecode
Copyright (c) 2001 Opaque Industries, (c) 2002-2003 Igor Kogan
All rights reserved. See LICENSE.TXT for terms of use.
*/

%{

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
%}

%glr-parser
%debug
%union
{
  long int num;
  char *str;
}

%expect 28  /* double nots shift/reduce warning */
%expect-rr 146

%token <str> MOVIENAME
%token <str> STRING
%token <num> INTEGER
%token <str> HEX
%token <str> FLOAT
%token <str> DOUBLE
%token <str> TRUEVAL
%token <str> FALSEVAL
%token <str> NULLVAL
%token <str> UNDEFVAL
%token <num> REGISTER
%token <str> REGISTERALIAS
%token <str> LABEL

%token MOVIE
%token COMPRESSED
%token PROTECT
%token SCRIPTLIMITS
%token RECURSION
%token TIMEOUT
%token ENABLEDEBUGGER
%token ENABLEDEBUGGER2
%token FRAME
%token PLACEMOVIECLIP
%token DEFINEMOVIECLIP
%token INITMOVIECLIP
%token DEFINEBUTTON
%token ON
%token ONCLIPEVENT
%token AS
%token IMPORTASSETS
%token EXPORTASSETS
%token FROM

// special double values
%token _NAN
%token POSITIVE_INFINITY
%token NEGATIVE_INFINITY

// special float values - push type 1
%token _NANF
%token POSITIVE_INFINITYF
%token NEGATIVE_INFINITYF

// button events
%token BIDLETOOVERUP
%token BOVERUPTOIDLE
%token BOVERUPTOOVERDOWN
%token BOVERDOWNTOOVERUP
%token BOVERDOWNTOOUTDOWN
%token BOUTDOWNTOOVERDOWN
%token BOUTDOWNTOIDLE
%token BIDLETOOVERDOWN
%token BOVERDOWNTOIDLE

%token KEYPRESS

// keyPress pre-defined
%token _LEFT
%token _RIGHT
%token _HOME
%token _END
%token _INSERT
%token _DELETE
%token _BACKSPACE
%token _ENTER
%token _UP
%token _DOWN
%token _PGUP
%token _PGDN
%token _TAB
%token _ESCAPE
%token _SPACE

// onClipEvents
%token MCLOAD
%token MCENTERFRAME
%token MCUNLOAD
%token MCMOUSEMOVE
%token MCMOUSEDOWN
%token MCMOUSEUP
%token MCKEYDOWN
%token MCKEYUP
%token MCINITIALIZE
%token MCCONSTRUCT
%token MCDATA
%token MCPRESS
%token MCRELEASE
%token MCRELEASEOUTSIDE
%token MCROLLOVER
%token MCROLLOUT
%token MCDRAGOVER
%token MCDRAGOUT

// old-style properties
%token X_PROPERTY
%token Y_PROPERTY
%token XSCALE_PROPERTY
%token YSCALE_PROPERTY
%token WIDTH_PROPERTY
%token HEIGHT_PROPERTY
%token ALPHA_PROPERTY
%token VISIBLE_PROPERTY
%token ROTATION_PROPERTY
%token CURRENTFRAME_PROPERTY
%token TOTALFRAMES_PROPERTY
%token TARGET_PROPERTY
%token FRAMESLOADED_PROPERTY
%token NAME_PROPERTY
%token DROPTARGET_PROPERTY
%token URL_PROPERTY
%token QUALITY_PROPERTY
%token XMOUSE_PROPERTY
%token YMOUSE_PROPERTY
%token HIGHQUALITY_PROPERTY
%token FOCUSRECT_PROPERTY
%token SOUNDBUFTIME_PROPERTY

%token NEXTFRAME
%token PREVFRAME
%token GOTOFRAME
%token GOTOLABEL
%token PLAY
%token STOP
%token TOGGLEQUALITY
%token STOPSOUNDS
%token FUNCTION
%token FUNCTION2
%token CONSTANTS
%token END
%token DUP
%token SWAP
%token POP
%token WITH
%token PUSH
%token SETREGISTER
%token CALLFUNCTION
%token RETURN
%token NEWMETHOD
%token CALLMETHOD
%token BITWISEAND
%token BITWISEOR
%token BITWISEXOR
%token MODULO
%token NEWADD
%token NEWLESSTHAN
%token NEWEQUALS
%token TONUMBER
%token TOSTRING
%token INCREMENT
%token DECREMENT
%token TYPEOF
%token TARGETPATH
%token ENUMERATE
%token ENUMERATEVALUE
%token INSTANCEOF
%token DELETE
%token DELETE2
%token NEW
%token INITARRAY
%token INITOBJECT
%token GETMEMBER
%token SETMEMBER
%token SHIFTLEFT
%token SHIFTRIGHT
%token SHIFTRIGHT2
%token VAR
%token VAREQUALS
%token OLDADD
%token SUBTRACT
%token MULTIPLY
%token DIVIDE
%token OLDEQUALS
%token OLDLESSTHAN
%token STRICTEQUALS
%token GREATERTHAN
%token LOGICALAND
%token LOGICALOR
%token LOGICALNOT
%token STRINGEQ
%token STRINGLENGTH
%token SUBSTRING
%token INT
%token GETVARIABLE
%token SETVARIABLE
%token SETTARGET
%token SETTARGETEXPR
%token STRINGCONCAT
%token GETPROPERTY
%token SETPROPERTY
%token DUPLICATECLIP
%token REMOVECLIP
%token TRACE
%token STARTDRAGMOVIE
%token STOPDRAGMOVIE
%token STRINGLESSTHAN
%token STRINGGREATERTHAN
%token RANDOM
%token MBLENGTH
%token ORD
%token CHR
%token GETTIMER
%token MBSUBSTRING
%token MBORD
%token MBCHR
%token BRANCHALWAYS
%token GETURL
%token GETURL2
%token LOADMOVIE
%token LOADMOVIENUM
%token LOADVARIABLES
%token LOADVARIABLESNUM
%token POST
%token GET
%token BRANCHIFTRUE
%token CALLFRAME
%token GOTOANDPLAY
%token GOTOANDSTOP
%token SKIP
%token IFFRAMELOADEDEXPR
%token IFFRAMELOADED
%token ELSE
%token STRICTMODE
%token OFF
%token IMPLEMENTS
%token EXTENDS
%token THROW
%token CAST
%token TRY
%token CATCH
%token FINALLY
%token EQUALSIGN
%token PUSHONE
%token PUSHZERO
%token PUSHTRUE
%token PUSHFALSE
%token PUSHBYTE
%token PUSHSHORT
%token PUSHLONG
%token PUSHS
%token PUSHSDB
%token PUSHSDW
%token CALLFP
%token CALLFSV
%token CALLMP
%token CALLMSV
%token PUSHSDBGV
%token PUSHSDBGM
%token PUSHTHIS
%token PUSHGLOBAL
%token PUSHNULL
%token PUSHUNDEF
%token DCALLFP
%token DCALLFSV
%token DCALLMP
%token DCALLMSV
%token PUSHFLOAT
%token PUSHTHISGV
%token PUSHGLOBALGV
%token PUSHSGV
%token PUSHSGM
%token PUSHZEROSV
%token PUSHSSV
%token PUSHSSM
%token BRANCHIFFALSE
%token APTTRACESTART
%token PUSHREGISTER

/* unknown instruction handling */
%token SWFACTION
%token HEXDATA

%token '(' ')' ',' ':' '"' '.'

%type <str> name_opt mcname_opt
%type <num> statements statement statements_opt
%type <num> statementOptimized statementScanned
%type <num> function function_args function2 regarglist regarg autoregarglist autoregarg
%type <num> trycatchfinally catch_opt finally_opt
%type <num> impassets impassetsblocks_opt impassetsblocks impassetsblock
%type <num> expassets expassetsblocks_opt expassetsblocks expassetsblock
%type <num> push_list push_item
%type <num> register
%type <num> with
%type <num> settarget settargetexpression ifframeloaded ifframeloadedexpression
%type <num> actionblocks actionblock actionblocks_opt
%type <num> buttoneventblocks buttoneventblock buttoneventblocks_opt
%type <num> mceventblocks mceventblock mceventblocks_opt
%type <num> mcblocks mcblock mcblocks_opt
%type <num> frame definebutton definemc placemc initmc
%type <num> buttonevent buttonevents mcevent mcevents key property
%type <num> opcode hex_list hexdata_opt
%type <num> opcodeOptimized opcodeScanned

%type <num> urlmethod

%%

/* rules */
program
        : MOVIE MOVIENAME                       {   startUpdate($2);    }
          actionblocks_opt END                  {   finishUpdate();     }
        ;

actionblocks_opt
        : /* empty */                           {   $$ = 0;             }
        | actionblocks                          {   $$ = $1;            }
        ;

actionblocks
        : actionblock                           {   $$ = $1;            }
        | actionblocks actionblock              {   $$ = $1 + $2;       }
        ;

actionblock
        : frame                                 {   $$ = $1;    }
        | definebutton                          {   $$ = $1;    }
        | definemc                              {   $$ = $1;    }
        | placemc                               {   $$ = $1;    }
        | initmc                                {   $$ = $1;    }
        | impassets                             {   $$ = $1;    }
        | expassets                             {   $$ = $1;    }
        | COMPRESSED                            {   compressAfter = 1;          $$ = 0; }
        | PROTECT                               {   writeProtect("");           $$ = 0; }
        | PROTECT STRING                        {   writeProtect($2);           $$ = 0; }
        | ENABLEDEBUGGER                        {   writeEnableDebugger("");    $$ = 0; }
        | ENABLEDEBUGGER STRING                 {   writeEnableDebugger($2);    $$ = 0; }
        | ENABLEDEBUGGER2 STRING                {   writeEnableDebugger2($2);   $$ = 0; }
        | SCRIPTLIMITS RECURSION INTEGER TIMEOUT INTEGER
                                                {
                                                    if ($3>65535)
                                                        yyerror("Recursion depth out of range");
                                                    if ($5>65535)
                                                        yyerror("Timeout out of range");
                                                    writeScriptLimits((unsigned int)$3, (unsigned int)$5);
                                                    $$ = 0;
                                                }
        ;

frame
        : FRAME INTEGER statements_opt END      {
                                                    $$ = $3;
                                                    /*action end*/
                                                    $$ += writeByte(0);
                                                    writeDoAction();
                                                    $$ = 0;
                                                }
        ;

initmc
        : INITMOVIECLIP INTEGER statements_opt END
                                                {
                                                    $$ = $3;
                                                    /*action end*/
                                                    $$ += writeByte(0);
                                                    writeInitMC($2);
                                                    $$ = 0;
                                                }
        ;

definebutton
        : DEFINEBUTTON INTEGER                  {   writeButtonStart($2); }
          buttoneventblocks_opt END             {   $$ = $4; writeButtonEnd();  }
        ;

buttoneventblocks_opt
        : /* empty */                           {   $$ = 0;         }
        | buttoneventblocks                     {   $$ = $1;        }
        ;

buttoneventblocks
        : buttoneventblock                      {   $$ = $1;        }
        | buttoneventblocks buttoneventblock    {   $$ = $1 + $2;   }
        ;

buttoneventblock
        : ON                                    {   curEvent = 0;   }
          buttonevents statements_opt END       {
                                                    $$ = $4;
                                                    /*event action end*/
                                                    $$ += writeByte(0);
                                                    writeButtonEvent((unsigned int)curEvent);
                                                }
        ;

buttonevents
        : buttonevent                           {   $$ = $1;  curEvent += $1;   }
        | buttonevents ',' buttonevent          {   $$ += $3; curEvent += $3;   }
        ;

buttonevent
        : BIDLETOOVERUP                         {   $$ = 0x01;  }
        | BOVERUPTOIDLE                         {   $$ = 0x02;  }
        | BOVERUPTOOVERDOWN                     {   $$ = 0x04;  }
        | BOVERDOWNTOOVERUP                     {   $$ = 0x08;  }
        | BOVERDOWNTOOUTDOWN                    {   $$ = 0x10;  }
        | BOUTDOWNTOOVERDOWN                    {   $$ = 0x20;  }
        | BOUTDOWNTOIDLE                        {   $$ = 0x40;  }
        | BIDLETOOVERDOWN                       {   $$ = 0x80;  }
        | BOVERDOWNTOIDLE                       {   $$ = 0x100; }
        | KEYPRESS key                          {   $$ = $2<<9; }
        ;

key
        : _LEFT                                 {   $$ = 1;     }
        | _RIGHT                                {   $$ = 2;     }
        | _HOME                                 {   $$ = 3;     }
        | _END                                  {   $$ = 4;     }
        | _INSERT                               {   $$ = 5;     }
        | _DELETE                               {   $$ = 6;     }
        | _BACKSPACE                            {   $$ = 8;     }
        | _ENTER                                {   $$ = 13;    }
        | _UP                                   {   $$ = 14;    }
        | _DOWN                                 {   $$ = 15;    }
        | _PGUP                                 {   $$ = 16;    }
        | _PGDN                                 {   $$ = 17;    }
        | _TAB                                  {   $$ = 18;    }
        | _ESCAPE                               {   $$ = 19;    }
        | _SPACE                                {   $$ = 32;    }
        | STRING                                {   $$ = $1[0]; }
        ;

register
        : REGISTER                              {
                                                    /* only 255 regs can be allocated within function2,
                                                       r:0 being the first and r:254 the last;
                                                       outside 4 global registers exist */
                                                    if ($1 >= 255)
                                                        yyerror("Register number out of range");
                                                    if ((byte)$1 > 3 && curFunc < 0)
                                                        warning("Local registers r:4 to r:255 work in function2 context only");
                                                    /* if needed, increase the number of registers
                                                       to allocate for function2 */
                                                    if (curFunc >= 0  &&  $1 + 1 > (long int) numRegisters[curFunc])
                                                        numRegisters[curFunc] = $1 + 1;                                               
                                                    $$ = $1;
                                                }

        | REGISTERALIAS                         {
                                                    unsigned int m;
                                                    int r = -1;
                                                    
                                                    if (curFunc >= 0) {
                                                        for(m = 1; m < numRegisters[curFunc]; ++m) {
                                                            if (regfunc_args[curFunc][m] != NULL && !strcmp($1, regfunc_args[curFunc][m])) {
                                                                r = m;
                                                                break;
                                                            }
                                                        }
                                                    }

                                                    if (r == -1)
                                                        yyerror("Register alias not found");
                                                    
                                                    $$ = r;
                                                }
        ;

definemc
        : DEFINEMOVIECLIP INTEGER               {   writeDefineMCStart($2);   }
          mcblocks_opt END                      {   $$ = $4; writeDefineMCEnd();    }
        ;

mcblocks_opt
        : /* empty */                           {   $$ = 0;     }
        | mcblocks                              {   $$ = $1;    }
        ;

mcblocks
        : mcblock                               {   $$ = $1;        }
        | mcblocks mcblock                      {   $$ = $1 + $2;   }
        ;

mcblock
        : frame                                 {   $$ = $1;    }
        | placemc                               {   $$ = $1;    }
        ;

placemc
        : PLACEMOVIECLIP INTEGER mcname_opt     {   allEvents = 0;  writePlaceMCStart($2);       }
          mceventblocks_opt END                 {   $$ = $5;        writePlaceMCEnd(allEvents);  }
        ;

mcname_opt
        : /* empty */                           {   $$ = "";    }
        | AS STRING                             {   $$ = $2;    }
        ;

mceventblocks_opt
        : /* empty */                           {   $$ = 0;     }
        | mceventblocks                         {   $$ = $1;    }
        ;

mceventblocks
        : mceventblock                          {   $$ = $1;      }
        | mceventblocks mceventblock            {   $$ = $1 + $2; }
        ;

mceventblock
        : ONCLIPEVENT mcevents                  {
                                                    curEvent = $2;
                                                    allEvents |= curEvent;
                                                }

          statements_opt END                    {
                                                    $$ = $4;
                                                    /*event action end*/
                                                    $$ += writeByte(0);
                                                    writeOnClipEvent(curEvent);
                                                    curEvent = 0;
                                                }
        ;

mcevents
        : mcevent                               {   $$ = $1;    curEvent += $1; }
        | mcevents ',' mcevent                  {   $$ += $3;   curEvent += $3; }
        ;

mcevent
        : /* empty */                           {   yyerror("Missing mc event condition"); }
        | MCLOAD                                {   $$ = 0x01;      }
        | MCENTERFRAME                          {   $$ = 0x02;      }
        | MCUNLOAD                              {   $$ = 0x04;      }
        | MCMOUSEMOVE                           {   $$ = 0x08;      }
        | MCMOUSEDOWN                           {   $$ = 0x10;      }
        | MCMOUSEUP                             {   $$ = 0x20;      }
        | MCKEYDOWN                             {   $$ = 0x40;      }
        | MCKEYUP                               {   $$ = 0x80;      }
        | MCDATA                                {   $$ = 0x100;     }
        | MCINITIALIZE                          {   $$ = 0x200;     }
        | MCPRESS                               {   $$ = 0x400;     }
        | MCRELEASE                             {   $$ = 0x800;     }
        | MCRELEASEOUTSIDE                      {   $$ = 0x1000;    }
        | MCROLLOVER                            {   $$ = 0x2000;    }
        | MCROLLOUT                             {   $$ = 0x4000;    }
        | MCDRAGOVER                            {   $$ = 0x8000;    }
        | MCDRAGOUT                             {   $$ = 0x10000;   }
        | KEYPRESS key                          {   $$ = 0x20000; writeByte($2);    }
        | MCCONSTRUCT                           {   $$ = 0x40000;   }
        ;

catch_opt
        : /* empty */                           {   $$ = 0;     }
        | CATCH statements_opt                  {   $$ = $2;    }
        ;

finally_opt
        : /* empty */                           {   $$ = 0;     }
        | FINALLY statements_opt                {   $$ = $2;    }
        ;

trycatchfinally 
        : TRY name_opt                          {
                                                    $$ = writeByte(SWFACTION_TRY);
                                                    /* action length */
                                                    $$ += writeShort(strlen($2)+8);
                                                    /* zero flag */
                                                    $$ += writeByte(0);
                                                    /* zero try length */
                                                    $$ += writeShort(0);
                                                    /* zero catch length */
                                                    $$ += writeShort(0);
                                                    /* zero finally length */
                                                    $$ += writeShort(0);
                                                    /* error variable name */
                                                    $$ += writeString($2);
                                                }

        statements_opt                          {   $$ = $<num>3 + $4; patchLength($$ - 6,  $4);    }
        catch_opt                               {   $$ = $<num>5 + $6; patchLength($$ - 8,  $6);    }
        finally_opt                             {   $$ = $<num>7 + $8; patchLength($$ - 10, $8);    }
        END                                     {
                                                    byte flag = 0;
                                                    $$ = $<num>9;
                                                    if ($6>0)
                                                        flag = flag + 1;
                                                    if ($8>0)
                                                        flag = flag + 2;
                                                    patchFlag($$ - 4, flag);
                                                }

        | TRY register                          {
                                                    $$ = writeByte(SWFACTION_TRY);
                                                    /* action length */
                                                    $$ += writeShort(8);
                                                    /* zero flag */
                                                    $$ += writeByte(0);
                                                    /* zero try length */
                                                    $$ += writeShort(0);
                                                    /* zero catch length */
                                                    $$ += writeShort(0);
                                                    /* zero finally length */
                                                    $$ += writeShort(0);
                                                    /* error register number */
                                                    $$ += writeByte((byte) $2);
                                                }
        ;

statements
        : statement                             {   $$ = $1;        } %dprec 5
        | statements statement                  {   $$ = $1 + $2;   } %dprec 1
        | statementOptimized                    {   $$ = $1;        } %dprec 20
        | statementScanned                      {   $$ = $1;        } %dprec 15
        | statements statementOptimized         {   $$ = $1 + $2;   } %dprec 10
        | statements statementScanned           {   $$ = $1 + $2;   } %dprec 8
        ;

statement
        : label                                 {   $$ = 0;     }
        | function                              {   $$ = $1;    }
        | function2                             {   $$ = $1;    }
        | with                                  {   $$ = $1;    }
        | settarget                             {   $$ = $1;    }
        | settargetexpression                   {   $$ = $1;    }
        | ifframeloaded                         {   $$ = $1;    }
        | ifframeloadedexpression               {   $$ = $1;    }
        | trycatchfinally                       {   $$ = $1;    }
        | opcode                                {   $$ = $1;    }
        ;

statementOptimized
        : opcodeOptimized                       {   $$ = $1;    }

statementScanned
        : opcodeScanned                         {   $$ = $1;    }

label
        : LABEL                                 {   addLabel($1);   }
        ;

/* this is weird/dumb- now we're returning the number of args instead
   of their length, and the args are stored in a global array func_args. */

function_args
        : /* empty */                           {   $$ = 0; }
        | STRING                                {   func_args[0] = $1;  $$ = 1;         }
        | function_args ',' STRING              {   func_args[$1] = $3; $$ = $1 + 1;    }
        ;

statements_opt
        : /* empty */                           {   $$ = 0;     }
        | statements                            {   $$ = $1;    }
        ;

name_opt
        : /* empty */                           {   $$ = "";    }
        | STRING                                {   $$ = $1;    }
        ;

function
        : FUNCTION name_opt                     {
                                                    $$ = writeByte(SWFACTION_DEFINEFUNCTION);
                                                    /* zero block length */
                                                    $$ += writeShort(0);
                                                    $$ += writeString($2);
                                                }

          '(' function_args ')'                 {
                                                    unsigned int i;
                                                    numArgs = $5;

                                                    $$ = $<num>3 + writeShort(numArgs);

                                                    for(i = 0; i < numArgs; ++i)
                                                        $$ += writeString(func_args[i]);

                                                    /* zero function length */
                                                    $$ += writeShort(0);
                                                    /* patch block length */
                                                    patchLength($$-3, $$-3);
                                                }

          statements_opt END                    {
                                                    $$ = $<num>7 + $8;
                                                    /* patch function length */
                                                    patchLength($8, $8);
                                                }
        ;

regarg
        : REGISTER EQUALSIGN STRING             {
                                                    numArgs++;
                                                    $$ = writeByte((byte) $1);

                                                    if ($1 == 0)
                                                        yyerror("Function argument can't be stored in r:0");

                                                    if ($1 + 1 >= MAX_REGISTERS)
                                                        yyerror("Too many registers");
                                                    
                                                    if (numArgs >= MAX_FUNCARGS)
                                                        yyerror("Too many function arguments");

                                                    if (regfunc_args[curFunc][$1] != NULL)
                                                        yyerror("Duplicate register");

                                                    regfunc_args[curFunc][$1] = $3;

                                                    if ($1 + 1 > (long int) numRegisters[curFunc])
                                                        numRegisters[curFunc] = $1 + 1;

                                                    /* if parameter is stored in register, may skip its name */
                                                    if ($1 > 0 && clearregisterargs && mode >= MODE_UPDATE)
                                                        $$ += writeString("");
                                                    else
                                                        $$ += writeString($3);
                                                }
        | STRING                                {
                                                    numArgs++;
                                                    /* r:0 - not stored in register */
                                                    $$ = writeByte(0);
                                                    $$ += writeString($1);
                                                }
        ;

regarglist
        : /* empty */                           {   $$ = 0;         }
        | regarg                                {   $$ = $1;        }
        | regarglist ',' regarg                 {   $$ = $1 + $3;   }
        ;

autoregarg
        : REGISTER EQUALSIGN STRING             {
                                                    unsigned int autoregFlag = 0, i;

                                                    if ($1 == 0 || $1 > MAX_AUTO_REGS)
                                                        yyerror("Automatic values should be placed into consequent registers starting with r:1\nin this order: this, arguments, super, _root, _parent, _global");

                                                    if (regfunc_args[curFunc][$1] != NULL && strcmp(regfunc_args[curFunc][$1], $3))
                                                        yyerror("Duplicate register");

                                                    regfunc_args[curFunc][$1] = $3;

                                                    if ($1 + 1 > (long int) numRegisters[curFunc])
                                                        numRegisters[curFunc] = $1 + 1;
                                                    
                                                    for (i = 0; i < MAX_AUTO_REGS; i++) {
                                                        if (!strcmp($3, arNames[i])) {
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
                                                }
        ;

autoregarglist
        : /* empty */                           {   $$ = 0;         }
        | autoregarg                            {   $$ = 1;         }
        | autoregarglist ',' autoregarg         {   $$ = $1 + 1;    }
        ;

function2
        : FUNCTION2 name_opt                    {
                                                    $$ = writeByte(SWFACTION_DEFINEFUNCTION2);
                                                    /* zero block length */
                                                    $$ += writeShort(0);
                                                    /* function name */
                                                    $$ += writeString($2);
                                                    curFunc++;
                                                    memset(regfunc_args[curFunc], 0, sizeof (regfunc_args[curFunc]));
                                                    numArgs = 0;
                                                    /* zero num of function arguments */
                                                    $$ += writeShort(numArgs);
                                                    /* allocate zero registers */
                                                    numRegisters[curFunc] = 0;
                                                    $$ += writeByte(numRegisters[curFunc]);
                                                    /* zero automatic register flags */
                                                    $$ += writeShort(0);
                                                }

          '(' regarglist ')'                    {
                                                    $$ = $<num>3 + $5;
                                                    /* patch num of function arguments */
                                                    patchLength($5 + 3, numArgs);
                                                    autoregFlags = 0;
                                                }
          
          '(' autoregarglist ')'                {
                                                    byte curautoreg = 1;
                                                    unsigned int i;

                                                    $$ = $<num>7;
                                                    /* zero body length */
                                                    $$ += writeShort(0);
                                                    
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
                                                    patchLength($$ - $<num>3, autoregFlags);
                                                    /* patch block length */
                                                    patchLength($$ - 3, $$ - 3);
                                                }

          statements_opt END                    {
                                                    $$ = $<num>11 + $12;

                                                    /* patch number of registers to allocate */
                                                    if (numRegisters[curFunc] < MAX_REGISTERS)
                                                        patchFlag($$ - $<num>3 + 2, (byte) numRegisters[curFunc]);
                                                    else
                                                        yyerror("Too many registers.");

                                                    /* patch function length */
                                                    patchLength($12, $12);
                                                    curFunc--;
                                                }
        ;

with
        : WITH                                  {
                                                    $$ = writeByte(SWFACTION_WITH);
                                                    /* length of with action */
                                                    $$ += writeShort(2);
                                                    /* length of with block - will be patched */
                                                    $$ += writeShort(0);
                                                }
                                                
          statements_opt END                    { 
                                                    $$ = $<num>2 + $3;
                                                    patchLength($3, $3);
                                                }

        ;

settarget
        : SETTARGET STRING                      {
                                                    $$ = writeByte(SWFACTION_SETTARGET);
                                                    $$ += writeShort(strlen($2)+1);
                                                    $$ += writeString($2);
                                                }

          statements_opt END                    {
                                                    $$ = $4 + writeByte(SWFACTION_SETTARGET);
                                                    $$ += $<num>3 + writeShort(1);
                                                    $$ += writeByte(0);
                                                }
        ;

settargetexpression
        : SETTARGETEXPR                         {   $$ = writeByte(SWFACTION_SETTARGETEXPRESSION);  }
          statements_opt END                    {
                                                    $$ = $3 + writeByte(SWFACTION_SETTARGET);
                                                    $$ += $<num>2 + writeShort(1);
                                                    $$ += writeByte(0);
                                                }
        ;

ifframeloadedexpression
        : IFFRAMELOADEDEXPR                     {
                                                    if (frameloadedStart>-1)
                                                        yyerror("IfFrameLoaded actions can't be nested");
                                                    $$ = writeByte(SWFACTION_IFFRAMELOADEDEXPRESSION);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte(0);
                                                    frameloadedStart = numActions;
                                                }

          statements_opt END                    { 
                                                    $$ = $<num>2 + $3;
                                                    patchFrameLoaded($3, numActions-frameloadedStart);
                                                    frameloadedStart = -1;
                                                }
        ;

ifframeloaded
        : IFFRAMELOADED INTEGER                 {
                                                    if (frameloadedStart>-1)
                                                        yyerror("IfFrameLoaded actions can't be nested");
                                                    $$ = writeByte(SWFACTION_IFFRAMELOADED);
                                                    $$ += writeShort(3);
                                                    $$ += writeShort($2);
                                                    $$ += writeByte(0);
                                                    frameloadedStart = numActions;
                                                }
                                         
          statements_opt END                    { 
                                                    $$ = $<num>3 + $4;
                                                    patchFrameLoaded($4, numActions-frameloadedStart);
                                                    frameloadedStart = -1;
                                                }
        ;

impassets
        : IMPORTASSETS FROM STRING              {   numAssets = 0;  }
          impassetsblocks_opt END               {
                                                    $$ = $5;
                                                    writeImportAssets($3, numAssets);
                                                    $$ = 0;
                                                }
        ;

impassetsblocks_opt
        : /* empty */                           {   $$ = 0;         }
        | impassetsblocks                       {   $$ = $1;        }
        ;

impassetsblocks
        : impassetsblock                        {   $$ = $1;        }
        | impassetsblocks impassetsblock        {   $$ = $1 + $2;   }
        ;

impassetsblock
        : STRING AS INTEGER                     {
                                                    $$ = strlen($1)+3;
                                                    writeShort($3);
                                                    writeString($1);
                                                    numAssets++;
                                                }
        ;

expassets
        : EXPORTASSETS                          {   numAssets = 0;  }
          expassetsblocks_opt END               {
                                                    $$ = $3;
                                                    writeExportAssets(numAssets);
                                                    $$ = 0;
                                                }
        ;

expassetsblocks_opt
        : /* empty */                           {   $$ = 0;         }
        | expassetsblocks                       {   $$ = $1;        }
        ;

expassetsblocks
        : expassetsblock                        {   $$ = $1;        }
        | expassetsblocks expassetsblock        {   $$ = $1 + $2;   }
        ;

expassetsblock
        : INTEGER AS STRING                     {
                                                    $$ = strlen($3)+3;
                                                    writeShort($1);
                                                    writeString($3);
                                                    numAssets++;
                                                }
        ;

push_item
        : STRING                                {   $$ = writePushString($1);   }

        | property                              {
                                                    $$ = writeByte(0x01);
                                                    $$ += writeFloat((float)$1);
                                                }

        | FLOAT                                 {
                                                    float f;
                                                    sscanf($1, "%f", &f);
                                                    $$ = writeByte(0x01);
                                                    $$ += writeFloat(f);
                                                }

        | _NANF                                 {
                                                    $$ = writeByte(0x01);
                                                    $$ += writeFloat(0/zero);
                                                }

        | POSITIVE_INFINITYF                    {
                                                    $$ = writeByte(0x01);
                                                    $$ += writeFloat(1/zero);
                                                }

        | NEGATIVE_INFINITYF                    {
                                                    $$ = writeByte(0x01);
                                                    $$ += writeFloat(-1/zero);
                                                }

        | HEX                                   {
                                                    unsigned long int li = xtoi($1);
                                                    if (li > 65535)
                                                        yyerror("Hex number should be unsigned integer in the range from 0x0000 to 0xFFFF");

                                                    $$ = writeByte(0x07);
                                                    $$ += writeLongInt(xtoi($1));
                                                }

        | INTEGER                               {
                                                    $$ = writeByte(0x07);
                                                    $$ += writeLongInt($1);
                                                }

        | DOUBLE                                {
                                                    $$ = writeByte(0x06);
                                                    $$ += writeDouble(atof($1));
                                                }

        | _NAN                                  {
                                                    $$ = writeByte(0x06);
                                                    $$ += writeDouble(0/zero);
                                                }

        | POSITIVE_INFINITY                     {
                                                    $$ = writeByte(0x06);
                                                    $$ += writeDouble(1/zero);
                                                }

        | NEGATIVE_INFINITY                     {
                                                    $$ = writeByte(0x06);
                                                    $$ += writeDouble(-1/zero);
                                                }

        | TRUEVAL                               {
                                                    $$ = writeByte(0x05);
                                                    $$ += writeByte(1);
                                                }

        | FALSEVAL                              {
                                                    $$ = writeByte(0x05);
                                                    $$ += writeByte(0);
                                                }

        | NULLVAL                               {   $$ = writeByte(2);  }

        | UNDEFVAL                              {   $$ = writeByte(3);  }

        | register                              {
                                                    $$ = writeByte(0x04);
                                                    $$ += writeByte((byte)$1);
                                                }
        ;

property
        : X_PROPERTY                            {   $$ = 0;     }
        | Y_PROPERTY                            {   $$ = 1;     }
        | XSCALE_PROPERTY                       {   $$ = 2;     }
        | YSCALE_PROPERTY                       {   $$ = 3;     }
        | CURRENTFRAME_PROPERTY                 {   $$ = 4;     }
        | TOTALFRAMES_PROPERTY                  {   $$ = 5;     }
        | ALPHA_PROPERTY                        {   $$ = 6;     }
        | VISIBLE_PROPERTY                      {   $$ = 7;     }
        | WIDTH_PROPERTY                        {   $$ = 8;     }
        | HEIGHT_PROPERTY                       {   $$ = 9;     }
        | ROTATION_PROPERTY                     {   $$ = 10;    }
        | TARGET_PROPERTY                       {   $$ = 11;    }
        | FRAMESLOADED_PROPERTY                 {   $$ = 12;    }
        | NAME_PROPERTY                         {   $$ = 13;    }
        | DROPTARGET_PROPERTY                   {   $$ = 14;    }
        | URL_PROPERTY                          {   $$ = 15;    }
        | HIGHQUALITY_PROPERTY                  {   $$ = 16;    }
        | FOCUSRECT_PROPERTY                    {   $$ = 17;    }
        | SOUNDBUFTIME_PROPERTY                 {   $$ = 18;    }
        | QUALITY_PROPERTY                      {   $$ = 19;    }
        | XMOUSE_PROPERTY                       {   $$ = 20;    }
        | YMOUSE_PROPERTY                       {   $$ = 21;    }
        ;

push_list
        : push_item                             {   $$ = $1;    }
        | push_list ',' push_item               {   $$ += $3;   }
        ;

constant_list
        : STRING                                {   addConstant($1);    }
        | constant_list ',' STRING              {   addConstant($3);    }
        ;

hex_list
        : HEX                                   {
                                                    if (xtoi($1)>0xff)
                                                        yyerror("Action data must be a byte list!");
                                                    $$ = writeByte((char)xtoi($1));
                                                }

        | hex_list ',' HEX                      {
                                                    if (xtoi($3)>0xff)
                                                        yyerror("Action data must be a byte list!");
                                                    $$ += writeByte((char)xtoi($3));
                                                }
        ;

hexdata_opt
        : /* empty */                           {   $$ = 0;     }
        | HEXDATA hex_list                      {   $$ = $2;    }
        ;

urlmethod
        : /* empty */                           {   $$ = 0;     }
        | GET                                   {   $$ = 1;     }
        | POST                                  {   $$ = 2;     }
        ;

opcodeOptimized
        : PUSHZERO SETVARIABLE                  {   $$ = writeByte(SWFACTION_PUSHZEROSETVAR);     --numActions;}
        | PUSHTHIS GETVARIABLE                  {   $$ = writeByte(SWFACTION_PUSHTHISVARIABLE);   --numActions;}
        | PUSHGLOBAL GETVARIABLE                {   $$ = writeByte(SWFACTION_PUSHGLOBALVARIABLE); --numActions;}
        | PUSH INTEGER                          {   
                                                    if ($2 == 0) {
                                                        $$ = writeByte(SWFACTION_PUSH0);
                                                    } else if ($2 == 1) {
                                                        $$ = writeByte(SWFACTION_PUSH1);
                                                    } else {
                                                        int val = $2;
                                                        if (val <= -127 || val >= 127) {
                                                            if (val <= -32767 || val >= 32767) {
                                                                $$ = writeByte(SWFACTION_PUSHDWORD);
                                                                $$ += writeShort(4);
                                                                $$ += writeLongInt($2);
                                                            }
                                                            else
                                                            {
                                                                $$ = writeByte(SWFACTION_PUSHWORD);
                                                                $$ += writeShort(2);
                                                                $$ += writeShort($2);
                                                            }
                                                        }
                                                        else
                                                        {
                                                            $$ = writeByte(SWFACTION_PUSHBYTE);
                                                            $$ += writeShort(1);
                                                            $$ += writeByte($2);
                                                        }
                                                    }
                                                }
        | PUSH STRING                           {   $$ = writePushStringDictOpcodes($2, SWFACTION_PUSHSTRINGDICTBYTE, SWFACTION_PUSHSTRINGDICTWORD, SWFACTION_PUSHSTRING);    }
        | PUSH FLOAT                            {
                                                    float val;
                                                    sscanf($2, "%f", &val);
                                                    if (val == 0.0f) {
                                                        $$ = writeByte(SWFACTION_PUSH0);
                                                    } else if (val == 1.0f) {
                                                        $$ = writeByte(SWFACTION_PUSH1);
                                                    } else {
                                                        $$ = writeByte(SWFACTION_PUSHFLOAT);
                                                        $$ += writeShort(4);
                                                        $$ += writeFloat(val);
                                                    }
                                                }
        | PUSH DOUBLE                           {
                                                    float val;
                                                    sscanf($2, "%f", &val);
                                                    if (val == 0.0f) {
                                                        $$ = writeByte(SWFACTION_PUSH0);
                                                    } else if (val == 1.0f) {
                                                        $$ = writeByte(SWFACTION_PUSH1);
                                                    } else {
                                                        $$ = writeByte(SWFACTION_PUSHFLOAT);
                                                        $$ += writeShort(4);
                                                        $$ += writeFloat(val);
                                                    }
                                                }
        | PUSH REGISTER                         {
                                                    if (isRA3)
                                                    {
                                                        $$ = writeByte(SWFACTION_PUSHREGISTER);
                                                        $$ += writeShort(1);
                                                        $$ += writeByte((byte)$2);
                                                    }
                                                    else
                                                    {
                                                        $$ = writeByte(SWFACTION_PUSHDATA);
                                                        $$ += writeByte(2);
                                                        $$ += writeByte(0);
                                                        $$ += writeByte(4);
                                                        $$ += writeByte((byte)$2);
                                                    }
                                                }
        | PUSHS STRING GETVARIABLE              {   $$ = writePushStringOpcodes($2, SWFACTION_PUSHSTRINGGETVAR, SWFACTION_GETVARIABLE, &numActions);     }
        | PUSHS STRING GETMEMBER                {   $$ = writePushStringOpcodes($2, SWFACTION_PUSHSTRINGGETMEMBER, SWFACTION_GETMEMBER, &numActions);    }
        | PUSHS STRING SETVARIABLE              {   $$ = writePushStringOpcodes($2, SWFACTION_PUSHSTRINGSETVAR, SWFACTION_SETVARIABLE, &numActions);     }
        | PUSHS STRING SETMEMBER                {   $$ = writePushStringOpcodes($2, SWFACTION_PUSHSTRINGSETMEMBER, SWFACTION_SETMEMBER, &numActions);    }
        | PUSHSDW INTEGER                       {
                                                    $$ = writeByte(SWFACTION_PUSHSTRINGDICTWORD);
                                                    $$ += writeShort(2);
                                                    $$ += writeShort($2);
                                                } %dprec 21
        | PUSHSDB INTEGER                       {
                                                    $$ = writeByte(SWFACTION_PUSHSTRINGDICTBYTE);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte($2);
                                                } %dprec 21
        | PUSHSDB INTEGER GETVARIABLE           {
                                                    $$ = writeByte(SWFACTION_STRINGDICTBYTEGETVAR);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte($2);
                                                    --numActions;
                                                } %dprec 22
        | PUSHSDB INTEGER GETMEMBER             {
                                                    $$ = writeByte(SWFACTION_STRINGDICTBYTEGETMEMBER);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte($2);
                                                    --numActions;
                                                } %dprec 22
        | PUSHSDBGV INTEGER                     {
                                                    if (isConstant($2, "this")) {
                                                        $$ = writeByte(SWFACTION_PUSHTHISVARIABLE);
                                                    } else if (isConstant($2, "_global")) {
                                                        $$ = writeByte(SWFACTION_PUSHGLOBALVARIABLE);
                                                    } else {
                                                        $$ = writeByte(SWFACTION_STRINGDICTBYTEGETVAR);
                                                        $$ += writeShort(1);
                                                        $$ += writeByte($2);
                                                    }
                                                }
        | CALLFUNCTION POP                      { $$ = writeByte(SWFACTION_CALLFUNCANDPOP); --numActions;   }
        | CALLFUNCTION SETVARIABLE              { $$ = writeByte(SWFACTION_CALLFUNCSETVAR); --numActions;   }
        | CALLMETHOD POP                        { $$ = writeByte(SWFACTION_CALLMETHODPOP); --numActions;    }
        | CALLMETHOD SETVARIABLE                { $$ = writeByte(SWFACTION_CALLMETHODSETVAR); --numActions; }
        | PUSHSDB INTEGER CALLFP                {
                                                    if (isConstant($2, "AptTrace")) {
                                                        $$ = writeByte(SWFACTION_TRACESTART);
                                                        --numActions;
                                                    } else {
                                                        $$ = writeByte(SWFACTION_DICTCALLFUNCPOP);
                                                        $$ += writeShort(1);
                                                        $$ += writeByte($2);
                                                        --numActions;
                                                    }
                                                } %dprec 40
        | PUSHSDW INTEGER CALLFP                {
                                                    if (isConstant($2, "AptTrace")) {
                                                        $$ = writeByte(SWFACTION_TRACESTART);
                                                        --numActions;
                                                    } else {
                                                        $$ = writeByte(SWFACTION_PUSHSTRINGDICTWORD);
                                                        $$ += writeShort(2);
                                                        $$ += writeShort($2);
                                                        $$ += writeByte(SWFACTION_CALLFUNCANDPOP);
                                                    }
                                                } %dprec 21
        | PUSHSDB INTEGER CALLFSV               {
                                                    $$ = writeByte(SWFACTION_DICTCALLFUNCSETVAR);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte($2);
                                                    --numActions;
                                                } %dprec 40
        | PUSHSDB INTEGER CALLMP                {
                                                    $$ = writeByte(SWFACTION_DICTCALLMETHODPOP);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte($2);
                                                    --numActions;
                                                } %dprec 40
        | PUSHSDB INTEGER CALLMSV               {
                                                    $$ = writeByte(SWFACTION_DICTCALLMETHODSETVAR);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte($2);
                                                    --numActions;
                                                } %dprec 40
        | PUSH NULLVAL                          {   $$ = writeByte(SWFACTION_PUSHNULL);        }
        | PUSH UNDEFVAL                         {   $$ = writeByte(SWFACTION_PUSHUNDEFINED);   }
        | PUSH TRUEVAL                          {   $$ = writeByte(SWFACTION_PUSHTRUE);        }
        | PUSH FALSEVAL                         {   $$ = writeByte(SWFACTION_PUSHFALSE);       }
        | LOGICALNOT LOGICALNOT                 {
                                                    if (mode >= MODE_UPDATE) {
                                                        /* strip double nots */
                                                        $$ = 0;
                                                        numActions -= 2;
                                                    }
                                                    else {
                                                        $$ = writeByte(SWFACTION_LOGICALNOT);
                                                        $$ += writeByte(SWFACTION_LOGICALNOT);
                                                    }
                                                }
        ;

opcodeScanned
        : PUSHBYTE INTEGER                      {
                                                    $$ = writeByte(SWFACTION_PUSHBYTE);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte($2);
                                                }
        | PUSHNULL                              {   $$ = writeByte(SWFACTION_PUSHNULL);        }
        | PUSHUNDEF                             {   $$ = writeByte(SWFACTION_PUSHUNDEFINED);   }
        | PUSHTRUE                              {   $$ = writeByte(SWFACTION_PUSHTRUE);        }
        | PUSHFALSE                             {   $$ = writeByte(SWFACTION_PUSHFALSE);       }
        | PUSHZEROSV                            {   $$ = writeByte(SWFACTION_PUSHZEROSETVAR);  }
        | PUSHSHORT INTEGER                     {
                                                    $$ = writeByte(SWFACTION_PUSHWORD);
                                                    $$ += writeShort(2);
                                                    $$ += writeShort($2);
                                                }
        | PUSHLONG INTEGER                      {
                                                    $$ = writeByte(SWFACTION_PUSHDWORD);
                                                    $$ += writeShort(4);
                                                    $$ += writeLongInt($2);
                                                }
        | PUSHFLOAT FLOAT                       {
                                                    float val;
                                                    sscanf($2, "%f", &val);
                                                    $$ = writeByte(SWFACTION_PUSHFLOAT);
                                                    $$ += writeShort(4);
                                                    $$ += writeFloat(val);
                                                }
        | PUSHFLOAT DOUBLE                      {
                                                    float val;
                                                    sscanf($2, "%f", &val);
                                                    $$ = writeByte(SWFACTION_PUSHFLOAT);
                                                    $$ += writeShort(4);
                                                    $$ += writeFloat(val);
                                                }
        | PUSHREGISTER INTEGER                  {
                                                    $$ = writeByte(SWFACTION_PUSHREGISTER);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte((byte)$2);
                                                }
        | PUSHS STRING                          {   $$ = writePushStringOpcodes($2, SWFACTION_PUSHSTRING, SWFACTION_INVALID, &numActions);                }
        | PUSHONE                               {   $$ = writeByte(SWFACTION_PUSH1);                                                              }
        | PUSHZERO                              {   $$ = writeByte(SWFACTION_PUSH0);                                                              }
        | PUSHSGV STRING                        {   $$ = writePushStringOpcodes($2, SWFACTION_PUSHSTRINGGETVAR, SWFACTION_GETVARIABLE, &numActions);      }
        | PUSHSGM STRING                        {   $$ = writePushStringOpcodes($2, SWFACTION_PUSHSTRINGGETMEMBER, SWFACTION_GETMEMBER, &numActions);     }
        | PUSHSSV STRING                        {   $$ = writePushStringOpcodes($2, SWFACTION_PUSHSTRINGSETVAR, SWFACTION_SETVARIABLE, &numActions);      }
        | PUSHSSM STRING                        {   $$ = writePushStringOpcodes($2, SWFACTION_PUSHSTRINGSETMEMBER, SWFACTION_SETMEMBER, &numActions);     }
        | DCALLFP INTEGER                       {
                                                    $$ = writeByte(SWFACTION_DICTCALLFUNCPOP);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte($2);
                                                }
        | DCALLFSV INTEGER                      {
                                                    $$ = writeByte(SWFACTION_DICTCALLFUNCSETVAR);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte($2);
                                                }
        | DCALLMP INTEGER                       {
                                                    if (isConstant($2, "AptTrace")) {
                                                        $$ = writeByte(SWFACTION_TRACESTART);
                                                        --numActions;
                                                    } else {
                                                        $$ = writeByte(SWFACTION_DICTCALLMETHODPOP);
                                                        $$ += writeShort(1);
                                                        $$ += writeByte($2);
                                                    }
                                                }
        | APTTRACESTART                         {   $$ = writeByte(SWFACTION_TRACESTART);   }
        | DCALLMSV INTEGER                      {
                                                    $$ = writeByte(SWFACTION_DICTCALLMETHODSETVAR);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte($2);
                                                }
        | CALLFP                                {   $$ = writeByte(SWFACTION_CALLFUNCANDPOP);       }
        | PUSHTHISGV                            {   $$ = writeByte(SWFACTION_PUSHTHISVARIABLE);     }
        | PUSHGLOBALGV                          {   $$ = writeByte(SWFACTION_PUSHGLOBALVARIABLE);   }
        | CALLFSV                               {   $$ = writeByte(SWFACTION_CALLFUNCSETVAR);       }
        | CALLMP                                {   $$ = writeByte(SWFACTION_CALLMETHODPOP);        }
        | CALLMSV                               {   $$ = writeByte(SWFACTION_CALLMETHODSETVAR);     }
        | PUSHTHIS                              {   $$ = writeByte(SWFACTION_PUSHTHIS);             }
        | PUSHGLOBAL                            {   $$ = writeByte(SWFACTION_PUSHGLOBAL);           }
        | PUSHSDBGM INTEGER                     {
                                                    $$ = writeByte(SWFACTION_STRINGDICTBYTEGETMEMBER);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte($2);
                                                }
        | PUSHSDBGV INTEGER                     {
                                                    $$ = writeByte(SWFACTION_STRINGDICTBYTEGETVAR);
                                                    $$ += writeShort(2);
                                                    $$ += writeShort($2); //needed to match... is this a bug?
                                                }
        ;
opcode
        : CONSTANTS                             {   nConstants = 0;         }
          constant_list                         {   $$ = writeConstants();  }

        | PUSH                                  {
                                                    $$ = writeByte(SWFACTION_PUSHDATA);
                                                    /* length */
                                                    $$ += writeShort(0);
                                                }

          push_list                             {   
                                                    $$ = $<num>2 + $3;
                                                    patchLength($3, $3);
                                                }

        | SWFACTION HEX                         {
                                                    if (xtoi($2)>0xff)
                                                        yyerror("Action code out of range");
                                                    $$ = writeByte((char)xtoi($2));
                                                    if (xtoi($2)>=0x80)
                                                    /* length */
                                                    $$ += writeShort(0);
                                                }

          hexdata_opt                           {
                                                    if (($4>0) && (xtoi($2)>=0x80))
                                                        patchLength($4, $4);
                                                    $$ = $<num>3 + $4;
                                                }

        | SETREGISTER register                  {
                                                    $$ = writeByte(SWFACTION_SETREGISTER);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte((byte)$2);
                                                }

        | STRICTEQUALS                          {   $$ = writeByte(SWFACTION_STRICTEQUALS);     }
        | GREATERTHAN                           {   $$ = writeByte(SWFACTION_GREATERTHAN);      }
        | ENUMERATEVALUE                        {   $$ = writeByte(SWFACTION_ENUMERATEVALUE);   }
        | INSTANCEOF                            {   $$ = writeByte(SWFACTION_INSTANCEOF);       }
        | NEXTFRAME                             {   $$ = writeByte(SWFACTION_NEXTFRAME);        }
        | PREVFRAME                             {   $$ = writeByte(SWFACTION_PREVFRAME);        }
        | PLAY                                  {   $$ = writeByte(SWFACTION_PLAY);             }
        | STOP                                  {   $$ = writeByte(SWFACTION_STOP);             }
        | TOGGLEQUALITY                         {   $$ = writeByte(SWFACTION_TOGGLEQUALITY);    }
        | STOPSOUNDS                            {   $$ = writeByte(SWFACTION_STOPSOUNDS);       }
        | CALLFUNCTION                          {   $$ = writeByte(SWFACTION_CALLFUNCTION);     }
        | RETURN                                {   $$ = writeByte(SWFACTION_RETURN);           }
        | NEWMETHOD                             {   $$ = writeByte(SWFACTION_NEWMETHOD);        }
        | CALLMETHOD                            {   $$ = writeByte(SWFACTION_CALLMETHOD);       }
        | BITWISEAND                            {   $$ = writeByte(SWFACTION_BITWISEAND);       }
        | BITWISEOR                             {   $$ = writeByte(SWFACTION_BITWISEOR);        }
        | BITWISEXOR                            {   $$ = writeByte(SWFACTION_BITWISEXOR);       }
        | MODULO                                {   $$ = writeByte(SWFACTION_MODULO);           }
        | NEWADD                                {   $$ = writeByte(SWFACTION_NEWADD);           }
        | NEWLESSTHAN                           {   $$ = writeByte(SWFACTION_NEWLESSTHAN);      }
        | NEWEQUALS                             {   $$ = writeByte(SWFACTION_NEWEQUALS);        }
        | TONUMBER                              {   $$ = writeByte(SWFACTION_TONUMBER);         }
        | TOSTRING                              {   $$ = writeByte(SWFACTION_TOSTRING);         }
        | INCREMENT                             {   $$ = writeByte(SWFACTION_INCREMENT);        }
        | DECREMENT                             {   $$ = writeByte(SWFACTION_DECREMENT);        }
        | TYPEOF                                {   $$ = writeByte(SWFACTION_TYPEOF);           }
        | TARGETPATH                            {   $$ = writeByte(SWFACTION_TARGETPATH);       }
        | ENUMERATE                             {   $$ = writeByte(SWFACTION_ENUMERATE);        }
        | DELETE                                {   $$ = writeByte(SWFACTION_DELETE);           }
        | DELETE2                               {   $$ = writeByte(SWFACTION_DELETE2);          }
        | NEW                                   {   $$ = writeByte(SWFACTION_NEW);              }
        | INITARRAY                             {   $$ = writeByte(SWFACTION_INITARRAY);        }
        | INITOBJECT                            {   $$ = writeByte(SWFACTION_INITOBJECT);       }
        | GETMEMBER                             {   $$ = writeByte(SWFACTION_GETMEMBER);        }
        | SETMEMBER                             {   $$ = writeByte(SWFACTION_SETMEMBER);        }
        | SHIFTLEFT                             {   $$ = writeByte(SWFACTION_SHIFTLEFT);        }
        | SHIFTRIGHT                            {   $$ = writeByte(SWFACTION_SHIFTRIGHT);       }
        | SHIFTRIGHT2                           {   $$ = writeByte(SWFACTION_SHIFTRIGHT2);      }
        | VAR                                   {   $$ = writeByte(SWFACTION_VAR);              }
        | VAREQUALS                             {   $$ = writeByte(SWFACTION_VAREQUALS);        }
        | OLDADD                                {   $$ = writeByte(SWFACTION_ADD);              }
        | SUBTRACT                              {   $$ = writeByte(SWFACTION_SUBTRACT);         }
        | MULTIPLY                              {   $$ = writeByte(SWFACTION_MULTIPLY);         }
        | DIVIDE                                {   $$ = writeByte(SWFACTION_DIVIDE);           }
        | OLDEQUALS                             {   $$ = writeByte(SWFACTION_EQUALS);           }
        | OLDLESSTHAN                           {   $$ = writeByte(SWFACTION_LESSTHAN);         }
        | LOGICALAND                            {   $$ = writeByte(SWFACTION_LOGICALAND);       }
        | LOGICALOR                             {   $$ = writeByte(SWFACTION_LOGICALOR);        }
        | LOGICALNOT                            {   $$ = writeByte(SWFACTION_LOGICALNOT);       }
        | STRINGEQ                              {   $$ = writeByte(SWFACTION_STRINGEQ);         }
        | STRINGLENGTH                          {   $$ = writeByte(SWFACTION_STRINGLENGTH);     }
        | SUBSTRING                             {   $$ = writeByte(SWFACTION_SUBSTRING);        }
        | INT                                   {   $$ = writeByte(SWFACTION_INT);              }
        | DUP                                   {   $$ = writeByte(SWFACTION_DUP);              }
        | SWAP                                  {   $$ = writeByte(SWFACTION_SWAP);             }
        | POP                                   {   $$ = writeByte(SWFACTION_POP);              }
        | GETVARIABLE                           {   $$ = writeByte(SWFACTION_GETVARIABLE);      }
        | SETVARIABLE                           {   $$ = writeByte(SWFACTION_SETVARIABLE);      }
        | STRINGCONCAT                          {   $$ = writeByte(SWFACTION_STRINGCONCAT);     }
        | GETPROPERTY                           {   $$ = writeByte(SWFACTION_GETPROPERTY);      }
        | SETPROPERTY                           {   $$ = writeByte(SWFACTION_SETPROPERTY);      }
        | DUPLICATECLIP                         {   $$ = writeByte(SWFACTION_DUPLICATECLIP);    }
        | REMOVECLIP                            {   $$ = writeByte(SWFACTION_REMOVECLIP);       }
        | TRACE                                 {   $$ = writeByte(SWFACTION_TRACE);            }
        | STARTDRAGMOVIE                        {   $$ = writeByte(SWFACTION_STARTDRAGMOVIE);   }
        | STOPDRAGMOVIE                         {   $$ = writeByte(SWFACTION_STOPDRAGMOVIE);    }
        | STRINGLESSTHAN                        {   $$ = writeByte(SWFACTION_STRINGLESSTHAN);   }
        | STRINGGREATERTHAN                     {   $$ = writeByte(SWFACTION_STRINGGREATERTHAN);}
        | RANDOM                                {   $$ = writeByte(SWFACTION_RANDOM);           }
        | MBLENGTH                              {   $$ = writeByte(SWFACTION_MBLENGTH);         }
        | ORD                                   {   $$ = writeByte(SWFACTION_ORD);              }
        | CHR                                   {   $$ = writeByte(SWFACTION_CHR);              }
        | GETTIMER                              {   $$ = writeByte(SWFACTION_GETTIMER);         }
        | MBSUBSTRING                           {   $$ = writeByte(SWFACTION_MBSUBSTRING);      }
        | MBORD                                 {   $$ = writeByte(SWFACTION_MBORD);            }
        | MBCHR                                 {   $$ = writeByte(SWFACTION_MBCHR);            }
        | IMPLEMENTS                            {   $$ = writeByte(SWFACTION_IMPLEMENTS);       }
        | EXTENDS                               {   $$ = writeByte(SWFACTION_EXTENDS);          }
        | THROW                                 {   $$ = writeByte(SWFACTION_THROW);            }
        | CAST                                  {   $$ = writeByte(SWFACTION_CAST);             }

        | CALLFRAME                             {
                                                    $$ = writeByte(SWFACTION_CALLFRAME);
                                                    $$ += writeShort(0);
                                                }

        | GOTOANDSTOP                           {   
                                                    $$ = writeByte(SWFACTION_GOTOEXPRESSION);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte(0);
                                                }

        | GOTOANDSTOP SKIP INTEGER              {   
                                                    $$ = writeByte(SWFACTION_GOTOEXPRESSION);
                                                    $$ += writeShort(3);
                                                    $$ += writeByte(2);
                                                    $$ += writeShort($3);
                                                }

        | GOTOANDPLAY                           {
                                                    $$ = writeByte(SWFACTION_GOTOEXPRESSION);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte(1);
                                                }

        | GOTOANDPLAY SKIP INTEGER              {
                                                    $$ = writeByte(SWFACTION_GOTOEXPRESSION);
                                                    $$ += writeShort(3);
                                                    $$ += writeByte(3);
                                                    $$ += writeShort($3);
                                                }

        | GOTOLABEL STRING                      {
                                                    $$ = writeByte(SWFACTION_GOTOLABEL);
                                                    $$ += writeShort(strlen($2)+1);
                                                    $$ += writeString($2);
                                                }

        | BRANCHALWAYS STRING                   {
                                                    $$ = writeByte(SWFACTION_BRANCHALWAYS);
                                                    $$ += writeShort(2);
                                                    $$ += branchTarget($2);
                                                }

        | BRANCHALWAYS INTEGER                  {
                                                    $$ = writeByte(SWFACTION_BRANCHALWAYS);
                                                    $$ += writeShort(2);
                                                    $$ += addNumLabel($2);
                                                }

        | BRANCHIFTRUE STRING                   {
                                                    $$ = writeByte(SWFACTION_BRANCHIFTRUE);
                                                    $$ += writeShort(2);
                                                    $$ += branchTarget($2);
                                                }

        | BRANCHIFTRUE INTEGER                  {
                                                    $$ = writeByte(SWFACTION_BRANCHIFTRUE);
                                                    $$ += writeShort(2);
                                                    $$ += addNumLabel($2);
                                                }

        | BRANCHIFFALSE STRING                  {
                                                    $$ = writeByte(SWFACTION_BRANCHIFFALSE);
                                                    $$ += writeShort(2);
                                                    $$ += branchTarget($2);
                                                }

        | BRANCHIFFALSE INTEGER                 {
                                                    $$ = writeByte(SWFACTION_BRANCHIFFALSE);
                                                    $$ += writeShort(2);
                                                    $$ += addNumLabel($2);
                                                }

        | GOTOFRAME INTEGER                     {
                                                    $$ = writeByte(SWFACTION_GOTOFRAME);
                                                    $$ += writeShort(2);
                                                    $$ += writeShort($2);
                                                }

        | GETURL STRING STRING                  {
                                                    $$ = writeByte(SWFACTION_GETURL);
                                                    $$ += writeShort(strlen($2)+strlen($3)+2);
                                                    $$ += writeString($2); 
                                                    $$ += writeString($3);
                                                }

        | GETURL2 urlmethod                     {
                                                    $$ = writeByte(SWFACTION_GETURL2);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte($2);
                                                }

        | LOADVARIABLES urlmethod               {
                                                    $$ = writeByte(SWFACTION_GETURL2);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte(0xc0 + $2);
                                                }

        | LOADVARIABLESNUM urlmethod            {
                                                    $$ = writeByte(SWFACTION_GETURL2);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte(0x80 + $2);
                                                }

        | LOADMOVIE urlmethod                   {
                                                    $$ = writeByte(SWFACTION_GETURL2);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte(0x40 + $2);
                                                }

        | LOADMOVIENUM urlmethod                {
                                                    $$ = writeByte(SWFACTION_GETURL2);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte($2);
                                                }

        | STRICTMODE ON                         {
                                                    $$ = writeByte(SWFACTION_STRICTMODE);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte(1);
                                                }

        | STRICTMODE OFF                        {
                                                    $$ = writeByte(SWFACTION_STRICTMODE);
                                                    $$ += writeShort(1);
                                                    $$ += writeByte(0);
                                                }

        | MOVIE STRING                          {   yyerror("Movie declaration inside of the action block");    }
        ;
