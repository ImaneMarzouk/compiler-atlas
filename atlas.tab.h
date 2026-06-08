/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_ATLAS_TAB_H_INCLUDED
# define YY_YY_ATLAS_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROGRAMME = 258,               /* PROGRAMME  */
    VAR = 259,                     /* VAR  */
    CONST = 260,                   /* CONST  */
    DEBUT = 261,                   /* DEBUT  */
    FIN = 262,                     /* FIN  */
    LIRE = 263,                    /* LIRE  */
    LIRERC = 264,                  /* LIRERC  */
    ECRIRE = 265,                  /* ECRIRE  */
    ECRIRERC = 266,                /* ECRIRERC  */
    IMPRIMER = 267,                /* IMPRIMER  */
    IMPRIMERRC = 268,              /* IMPRIMERRC  */
    PASSER = 269,                  /* PASSER  */
    SI = 270,                      /* SI  */
    ALORS = 271,                   /* ALORS  */
    SINON = 272,                   /* SINON  */
    FSI = 273,                     /* FSI  */
    POUR = 274,                    /* POUR  */
    DEPUIS = 275,                  /* DEPUIS  */
    JUSQUA = 276,                  /* JUSQUA  */
    PARPAS = 277,                  /* PARPAS  */
    FAIRE = 278,                   /* FAIRE  */
    FPOUR = 279,                   /* FPOUR  */
    TANTQUE = 280,                 /* TANTQUE  */
    FTQ = 281,                     /* FTQ  */
    ENT = 282,                     /* ENT  */
    BOOL_TYPE = 283,               /* BOOL_TYPE  */
    ET = 284,                      /* ET  */
    OU = 285,                      /* OU  */
    NON = 286,                     /* NON  */
    PUISS = 287,                   /* PUISS  */
    VALABS = 288,                  /* VALABS  */
    ASSIGN = 289,                  /* ASSIGN  */
    DIFF = 290,                    /* DIFF  */
    GTE = 291,                     /* GTE  */
    LTE = 292,                     /* LTE  */
    GT = 293,                      /* GT  */
    LT = 294,                      /* LT  */
    EQ = 295,                      /* EQ  */
    PLUS = 296,                    /* PLUS  */
    MINUS = 297,                   /* MINUS  */
    MULT = 298,                    /* MULT  */
    DIV = 299,                     /* DIV  */
    MOD = 300,                     /* MOD  */
    SEMICOLON = 301,               /* SEMICOLON  */
    LPAREN = 302,                  /* LPAREN  */
    RPAREN = 303,                  /* RPAREN  */
    COMMA = 304,                   /* COMMA  */
    ID = 305,                      /* ID  */
    STRING = 306,                  /* STRING  */
    INT = 307,                     /* INT  */
    BOOL_VAL = 308,                /* BOOL_VAL  */
    DOT = 309,                     /* DOT  */
    UMINUS = 310                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 103 "atlas.y"

    int val;
    char *str;
    struct {
        char type[10];
        int value;
    } expr;

#line 128 "atlas.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_ATLAS_TAB_H_INCLUDED  */
