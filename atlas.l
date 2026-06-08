%{
#include "atlas.tab.h"
#include <string.h>
#include <stdlib.h>

int line_num = 1;
%}

%option noyywrap

DIGIT           [0-9]
LETTER          [a-zA-Z_]
ID              {LETTER}({LETTER}|{DIGIT})*
INT             {DIGIT}+

%%

"//".* { /* ignorer les commentaires */ }
[ \t\r]+                        { /* ignorer espaces et tabulations */ }
\n                              { line_num++; }

"programme"                     { return PROGRAMME; }
"var"                           { return VAR; }
"const"                         { return CONST; }
"debut"                         { return DEBUT; }
"fin"                           { return FIN; }
"lire"                          { return LIRE; }
"lireRC"                        { return LIRERC; }
"ecrire"                        { return ECRIRE; }
"ecrireRC"                      { return ECRIRERC; }
"imprimer"                      { return IMPRIMER; }
"imprimerRC"                    { return IMPRIMERRC; }
"passer"                        { return PASSER; }
"si"                            { return SI; }
"alors"                         { return ALORS; }
"sinon"                         { return SINON; }
"fsi"                           { return FSI; }
"pour"                          { return POUR; }
"depuis"                        { return DEPUIS; }
"jusqua"                        { return JUSQUA; }
"parpas"                        { return PARPAS; }
"faire"                         { return FAIRE; }
"fpour"                         { return FPOUR; }
"tantque"                       { return TANTQUE; }
"ftq"                           { return FTQ; }
"ent"                           { return ENT; }
"bool"                          { return BOOL_TYPE; }
"et"                            { return ET; }
"ou"                            { return OU; }
"non"                           { return NON; }
"puiss"                         { return PUISS; }
"valabs"                        { return VALABS; }

"vrai"                          { yylval.val = 1; return BOOL_VAL; }
"faux"                          { yylval.val = 0; return BOOL_VAL; }

":="                            { return ASSIGN; }
"<>"                            { return DIFF; }
">="                            { return GTE; }
"<="                            { return LTE; }
">"                             { return GT; }
"<"                             { return LT; }
"="                             { return EQ; }
"+"                             { return PLUS; }
"-"                             { return MINUS; }
"*"                             { return MULT; }
"/"                             { return DIV; }
"%"                             { return MOD; }
";"                             { return SEMICOLON; }
"("                             { return LPAREN; }
")"                             { return RPAREN; }
","                             { return COMMA; }

\'([^\'\\]|\\.)*\'              {
                                  yylval.str = strdup(yytext);
                                  return STRING;
                                }

{ID}                            {
                                  yylval.str = strdup(yytext);
                                  return ID;
                                }

{INT}                           {
                                  yylval.val = atoi(yytext);
                                  return INT;
                                }

 "."     { return DOT; }

%%