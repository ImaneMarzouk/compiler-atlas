/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "atlas.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern int line_num;
extern FILE *yyin;

typedef struct {
    char name[50];
    char genre[10];
    char type[10];
    int address;
    int value;
    int initialized;
} Symbol;

Symbol symbol_table[100];
int symbol_count = 0;
int label_counter = 1000; /* Labels >= 1000 pour ne pas collisionner avec instruction_counter */
FILE *output_file;
int instruction_counter = 1;
int const_values[100];
int const_count = 0;
int lbl_sinon_global = 0;
int lbl_fin_global = 0;
/* Pile pour les labels SI imbriqués */
int sinon_stack[100];
int sinon_top = -1;

void push_sinon(int lbl) { sinon_stack[++sinon_top] = lbl; }
int  pop_sinon()         { return sinon_stack[sinon_top--]; }
int  peek_sinon()        { return sinon_stack[sinon_top]; }

int fin_stack[100];
int fin_top = -1;

void push_fin(int lbl) { fin_stack[++fin_top] = lbl; }
int  pop_fin()         { return fin_stack[fin_top--]; }

int lookup(const char *name) {
    for (int i = 0; i < symbol_count; i++)
        if (strcmp(symbol_table[i].name, name) == 0) return i;
    return -1;
}

void put_symbol(const char *name, const char *genre, const char *type, int value) {
    if (lookup(name) != -1) {
        fprintf(stderr, "Erreur ligne %d: Declaration multiple de '%s'\n", line_num, name);
        exit(1);
    }
    if (symbol_count >= 100) { fprintf(stderr, "Erreur: Table des symboles pleine\n"); exit(1); }
    strcpy(symbol_table[symbol_count].name, name);
    strcpy(symbol_table[symbol_count].genre, genre);
    strcpy(symbol_table[symbol_count].type, type);
    symbol_table[symbol_count].address = symbol_count;
    symbol_table[symbol_count].value = value;
    if (strcmp(genre, "const") == 0) const_values[const_count++] = value;
    symbol_table[symbol_count].initialized = (strcmp(genre, "const") == 0);
    symbol_count++;
}

int getAdr(const char *name) {
    int idx = lookup(name);
    if (idx == -1) {
        fprintf(stderr, "Erreur ligne %d: Identificateur '%s' non declare\n", line_num, name);
        exit(1);
    }
    return symbol_table[idx].address;
}

char *getGenre(const char *name) {
    int idx = lookup(name);
    if (idx == -1) return NULL;
    return symbol_table[idx].genre;
}

char *getType(const char *name) {
    int idx = lookup(name);
    if (idx == -1) return NULL;
    return symbol_table[idx].type;
}

int getLabel() { return label_counter++; }

void emit(const char *instruction, const char *arg) {
    if (arg)
        fprintf(output_file, "%d\t%s %s\n", instruction_counter, instruction, arg);
    else
        fprintf(output_file, "%d\t%s\n", instruction_counter, instruction);
    instruction_counter++;
}

void yyerror(const char *s) {
    fprintf(stderr, "Erreur syntaxique ligne %d: %s\n", line_num, s);
    exit(1);
}

extern int yylex();

#line 173 "atlas.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "atlas.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAMME = 3,                  /* PROGRAMME  */
  YYSYMBOL_VAR = 4,                        /* VAR  */
  YYSYMBOL_CONST = 5,                      /* CONST  */
  YYSYMBOL_DEBUT = 6,                      /* DEBUT  */
  YYSYMBOL_FIN = 7,                        /* FIN  */
  YYSYMBOL_LIRE = 8,                       /* LIRE  */
  YYSYMBOL_LIRERC = 9,                     /* LIRERC  */
  YYSYMBOL_ECRIRE = 10,                    /* ECRIRE  */
  YYSYMBOL_ECRIRERC = 11,                  /* ECRIRERC  */
  YYSYMBOL_IMPRIMER = 12,                  /* IMPRIMER  */
  YYSYMBOL_IMPRIMERRC = 13,                /* IMPRIMERRC  */
  YYSYMBOL_PASSER = 14,                    /* PASSER  */
  YYSYMBOL_SI = 15,                        /* SI  */
  YYSYMBOL_ALORS = 16,                     /* ALORS  */
  YYSYMBOL_SINON = 17,                     /* SINON  */
  YYSYMBOL_FSI = 18,                       /* FSI  */
  YYSYMBOL_POUR = 19,                      /* POUR  */
  YYSYMBOL_DEPUIS = 20,                    /* DEPUIS  */
  YYSYMBOL_JUSQUA = 21,                    /* JUSQUA  */
  YYSYMBOL_PARPAS = 22,                    /* PARPAS  */
  YYSYMBOL_FAIRE = 23,                     /* FAIRE  */
  YYSYMBOL_FPOUR = 24,                     /* FPOUR  */
  YYSYMBOL_TANTQUE = 25,                   /* TANTQUE  */
  YYSYMBOL_FTQ = 26,                       /* FTQ  */
  YYSYMBOL_ENT = 27,                       /* ENT  */
  YYSYMBOL_BOOL_TYPE = 28,                 /* BOOL_TYPE  */
  YYSYMBOL_ET = 29,                        /* ET  */
  YYSYMBOL_OU = 30,                        /* OU  */
  YYSYMBOL_NON = 31,                       /* NON  */
  YYSYMBOL_PUISS = 32,                     /* PUISS  */
  YYSYMBOL_VALABS = 33,                    /* VALABS  */
  YYSYMBOL_ASSIGN = 34,                    /* ASSIGN  */
  YYSYMBOL_DIFF = 35,                      /* DIFF  */
  YYSYMBOL_GTE = 36,                       /* GTE  */
  YYSYMBOL_LTE = 37,                       /* LTE  */
  YYSYMBOL_GT = 38,                        /* GT  */
  YYSYMBOL_LT = 39,                        /* LT  */
  YYSYMBOL_EQ = 40,                        /* EQ  */
  YYSYMBOL_PLUS = 41,                      /* PLUS  */
  YYSYMBOL_MINUS = 42,                     /* MINUS  */
  YYSYMBOL_MULT = 43,                      /* MULT  */
  YYSYMBOL_DIV = 44,                       /* DIV  */
  YYSYMBOL_MOD = 45,                       /* MOD  */
  YYSYMBOL_SEMICOLON = 46,                 /* SEMICOLON  */
  YYSYMBOL_LPAREN = 47,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 48,                    /* RPAREN  */
  YYSYMBOL_COMMA = 49,                     /* COMMA  */
  YYSYMBOL_ID = 50,                        /* ID  */
  YYSYMBOL_STRING = 51,                    /* STRING  */
  YYSYMBOL_INT = 52,                       /* INT  */
  YYSYMBOL_BOOL_VAL = 53,                  /* BOOL_VAL  */
  YYSYMBOL_DOT = 54,                       /* DOT  */
  YYSYMBOL_UMINUS = 55,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_programme = 57,                 /* programme  */
  YYSYMBOL_58_1 = 58,                      /* $@1  */
  YYSYMBOL_corps = 59,                     /* corps  */
  YYSYMBOL_60_2 = 60,                      /* $@2  */
  YYSYMBOL_declarations_opt = 61,          /* declarations_opt  */
  YYSYMBOL_const_section = 62,             /* const_section  */
  YYSYMBOL_var_section = 63,               /* var_section  */
  YYSYMBOL_const_decl_list = 64,           /* const_decl_list  */
  YYSYMBOL_const_decl = 65,                /* const_decl  */
  YYSYMBOL_var_decl_list = 66,             /* var_decl_list  */
  YYSYMBOL_var_decl = 67,                  /* var_decl  */
  YYSYMBOL_type_decl = 68,                 /* type_decl  */
  YYSYMBOL_list_vars = 69,                 /* list_vars  */
  YYSYMBOL_instructions = 70,              /* instructions  */
  YYSYMBOL_instruction = 71,               /* instruction  */
  YYSYMBOL_72_3 = 72,                      /* $@3  */
  YYSYMBOL_73_4 = 73,                      /* $@4  */
  YYSYMBOL_74_5 = 74,                      /* @5  */
  YYSYMBOL_75_6 = 75,                      /* @6  */
  YYSYMBOL_76_7 = 76,                      /* $@7  */
  YYSYMBOL_77_8 = 77,                      /* $@8  */
  YYSYMBOL_78_9 = 78,                      /* @9  */
  YYSYMBOL_79_10 = 79,                     /* $@10  */
  YYSYMBOL_80_11 = 80,                     /* @11  */
  YYSYMBOL_sinon_opt = 81,                 /* sinon_opt  */
  YYSYMBOL_pas_opt = 82,                   /* pas_opt  */
  YYSYMBOL_condition = 83,                 /* condition  */
  YYSYMBOL_expression = 84                 /* expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   261

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  153

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   310


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      55
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   136,   136,   136,   146,   146,   170,   172,   173,   174,
     177,   178,   181,   182,   186,   187,   191,   192,   195,   198,
     199,   203,   204,   208,   209,   215,   215,   234,   244,   254,
     262,   270,   273,   276,   288,   288,   307,   310,   307,   325,
     335,   341,   352,   358,   325,   392,   399,   415,   416,   420,
     430,   435,   440,   452,   457,   462,   467,   472,   477,   483,
     488,   494,   495,   496,   497,   498,   499,   501,   506,   511,
     516
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAMME", "VAR",
  "CONST", "DEBUT", "FIN", "LIRE", "LIRERC", "ECRIRE", "ECRIRERC",
  "IMPRIMER", "IMPRIMERRC", "PASSER", "SI", "ALORS", "SINON", "FSI",
  "POUR", "DEPUIS", "JUSQUA", "PARPAS", "FAIRE", "FPOUR", "TANTQUE", "FTQ",
  "ENT", "BOOL_TYPE", "ET", "OU", "NON", "PUISS", "VALABS", "ASSIGN",
  "DIFF", "GTE", "LTE", "GT", "LT", "EQ", "PLUS", "MINUS", "MULT", "DIV",
  "MOD", "SEMICOLON", "LPAREN", "RPAREN", "COMMA", "ID", "STRING", "INT",
  "BOOL_VAL", "DOT", "UMINUS", "$accept", "programme", "$@1", "corps",
  "$@2", "declarations_opt", "const_section", "var_section",
  "const_decl_list", "const_decl", "var_decl_list", "var_decl",
  "type_decl", "list_vars", "instructions", "instruction", "$@3", "$@4",
  "@5", "@6", "$@7", "$@8", "@9", "$@10", "@11", "sinon_opt", "pas_opt",
  "condition", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-93)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      41,     0,    51,     6,   -93,   -93,    -2,   -16,   -10,    46,
     -93,    52,   -93,   -93,   -93,   -16,   -93,     5,    20,    22,
     -10,   -93,    19,    70,   -93,   -93,   -93,    -4,    39,    43,
     -93,   -93,    50,   -93,    31,    32,    33,    42,    44,    45,
      49,    40,    65,    47,    54,    67,   -93,    62,    50,   -93,
     -93,    72,    73,    87,    89,    90,   105,   106,   107,   -93,
      35,   -93,   -93,    54,   -93,   -93,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,   -93,    35,   121,   122,    35,    35,   -93,
     -93,   -93,   102,   154,   165,   -93,    35,   -93,    35,    35,
     -93,   119,    35,    35,    35,    35,    35,    35,    35,    35,
      35,    35,    35,    35,    35,   -93,    50,   -93,   163,   170,
      85,   136,   -93,   216,   205,   -35,   -35,   -35,   -35,   -35,
     -35,     3,     3,   -93,   -93,   -93,    24,    35,    50,   -93,
      35,   -93,    50,   169,   188,   176,   153,    50,   -93,   182,
     158,   -93,   -93,   -93,    35,    68,   167,   -93,   -93,   197,
      50,   198,   -93
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     2,     6,     0,     0,     0,
       4,     8,     9,    19,    20,    11,    16,     0,     0,     0,
      10,    12,     0,     0,     7,    17,    21,     0,     0,     0,
      13,     3,     0,    18,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,     0,     5,    23,
      22,     0,     0,     0,     0,     0,     0,     0,     0,    33,
       0,    34,    39,     0,    25,    24,    14,    15,    27,    28,
      29,    30,    31,    32,     0,     0,     0,     0,     0,    52,
      50,    51,     0,     0,     0,    37,     0,    69,     0,     0,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,     0,    40,     0,     0,
       0,     0,    70,    67,    68,    62,    66,    65,    64,    63,
      61,    53,    54,    55,    56,    57,    45,     0,     0,    26,
       0,    59,     0,     0,    41,     0,     0,    46,    35,     0,
       0,    58,    42,    38,     0,    47,     0,    43,    48,     0,
       0,     0,    44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -93,   -93,   -93,   -93,   -93,   -93,   -93,   210,   -93,   215,
     -93,   221,   -93,   -93,   -92,   -48,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,   -93,   -93,   -93,   -93,   174,   -73
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     6,     9,    23,    10,    11,    12,    20,    21,
      15,    16,    17,    27,    48,    49,    86,    83,    63,   108,
      84,   127,   139,   144,   149,   133,   147,    61,    82
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      65,    87,     7,     8,    90,    91,   100,   101,   102,   103,
     104,    13,    14,   109,   126,   110,   111,    18,    19,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,    37,    38,    39,    40,    41,    42,    43,    44,
     137,   132,    33,    45,     1,    34,   102,   103,   104,    46,
       3,     4,     5,    22,   134,    26,     7,   136,    37,    38,
      39,    40,    41,    42,    43,    44,    74,    75,    76,    45,
      28,   145,    29,    31,    47,    46,    32,    77,    65,    35,
     135,    50,    78,    36,    51,    79,    52,    80,    81,    65,
     146,    57,    53,    59,    54,    55,    64,    92,    93,    56,
      47,    60,   151,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,    92,    93,    58,    62,    66,    67,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,    92,    93,    68,   130,    69,    70,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,    92,    93,
     105,    71,    72,    73,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,    92,    93,   112,    88,    89,
     106,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,    92,    93,   131,   107,   128,   138,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,    92,
      93,   141,   140,   142,   143,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   129,    92,    93,   148,
     150,    24,   152,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,    92,    30,    25,    85,     0,     0,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104
};

static const yytype_int16 yycheck[] =
{
      48,    74,     4,     5,    77,    78,    41,    42,    43,    44,
      45,    27,    28,    86,   106,    88,    89,    27,    28,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,     8,     9,    10,    11,    12,    13,    14,    15,
     132,    17,    46,    19,     3,    49,    43,    44,    45,    25,
      50,     0,    46,     7,   127,    50,     4,   130,     8,     9,
      10,    11,    12,    13,    14,    15,    31,    32,    33,    19,
      50,   144,    50,    54,    50,    25,     6,    42,   126,    40,
     128,    50,    47,    40,    52,    50,    53,    52,    53,   137,
      22,    51,    50,    46,    50,    50,    34,    29,    30,    50,
      50,    47,   150,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    29,    30,    51,    50,    46,    46,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    29,    30,    46,    49,    46,    46,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    29,    30,
      48,    46,    46,    46,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    29,    30,    48,    47,    47,
      16,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    29,    30,    48,    20,    23,    18,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    29,
      30,    48,    26,    21,    46,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    29,    30,    52,
      23,    11,    24,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    29,    20,    15,    63,    -1,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    57,    50,     0,    46,    58,     4,     5,    59,
      61,    62,    63,    27,    28,    66,    67,    68,    27,    28,
      64,    65,     7,    60,    63,    67,    50,    69,    50,    50,
      65,    54,     6,    46,    49,    40,    40,     8,     9,    10,
      11,    12,    13,    14,    15,    19,    25,    50,    70,    71,
      50,    52,    53,    50,    50,    50,    50,    51,    51,    46,
      47,    83,    50,    74,    34,    71,    46,    46,    46,    46,
      46,    46,    46,    46,    31,    32,    33,    42,    47,    50,
      52,    53,    84,    73,    76,    83,    72,    84,    47,    47,
      84,    84,    29,    30,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    48,    16,    20,    75,    84,
      84,    84,    48,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    70,    77,    23,    46,
      49,    48,    17,    81,    84,    71,    84,    70,    18,    78,
      26,    48,    21,    46,    79,    84,    22,    82,    52,    80,
      23,    71,    24
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    58,    57,    60,    59,    61,    61,    61,    61,
      62,    63,    64,    64,    65,    65,    66,    66,    67,    68,
      68,    69,    69,    70,    70,    72,    71,    71,    71,    71,
      71,    71,    71,    71,    73,    71,    74,    75,    71,    76,
      77,    78,    79,    80,    71,    81,    81,    82,    82,    83,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     7,     0,     4,     0,     2,     1,     1,
       2,     2,     1,     2,     5,     5,     1,     2,     3,     1,
       1,     1,     3,     1,     2,     0,     5,     3,     3,     3,
       3,     3,     3,     2,     0,     7,     0,     0,     8,     0,
       0,     0,     0,     0,    15,     0,     2,     0,     2,     3,
       1,     1,     1,     3,     3,     3,     3,     3,     6,     4,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 136 "atlas.y"
                           {
        emit("ouverture-bloc", NULL);
    }
#line 1371 "atlas.tab.c"
    break;

  case 3: /* programme: PROGRAMME ID SEMICOLON $@1 corps FIN DOT  */
#line 139 "atlas.y"
                  {
        emit("fermeture-bloc", NULL);
        printf("\nCode MAP genere avec succes.\n");
    }
#line 1380 "atlas.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 146 "atlas.y"
                     {
        int num_consts = 0, num_vars = 0;
        for (int i = 0; i < symbol_count; i++) {
            if (strcmp(symbol_table[i].genre, "const") == 0) num_consts++;
            else num_vars++;
        }
        if (const_count > 0) {
            fprintf(output_file, ".global ");
            for (int i = 0; i < const_count; i++)
                fprintf(output_file, "%d ", const_values[i]);
            fprintf(output_file, "\n");
        }
        if (num_consts > 0) {
            char buf[20]; sprintf(buf, "%d", num_consts);
            emit("reserver-kst", buf);
        }
        if (num_vars > 0) {
            char buf[20]; sprintf(buf, "%d", num_vars);
            emit("reserver-var", buf);
        }
    }
#line 1406 "atlas.tab.c"
    break;

  case 14: /* const_decl: ENT ID EQ INT SEMICOLON  */
#line 186 "atlas.y"
                                   { put_symbol((yyvsp[-3].str), "const", "ent",  (yyvsp[-1].val)); }
#line 1412 "atlas.tab.c"
    break;

  case 15: /* const_decl: BOOL_TYPE ID EQ BOOL_VAL SEMICOLON  */
#line 187 "atlas.y"
                                         { put_symbol((yyvsp[-3].str), "const", "bool", (yyvsp[-1].val)); }
#line 1418 "atlas.tab.c"
    break;

  case 19: /* type_decl: ENT  */
#line 198 "atlas.y"
               { (yyval.str) = "ent";  }
#line 1424 "atlas.tab.c"
    break;

  case 20: /* type_decl: BOOL_TYPE  */
#line 199 "atlas.y"
                 { (yyval.str) = "bool"; }
#line 1430 "atlas.tab.c"
    break;

  case 21: /* list_vars: ID  */
#line 203 "atlas.y"
                         { put_symbol((yyvsp[0].str), "var", (yyvsp[-1].str), 0); }
#line 1436 "atlas.tab.c"
    break;

  case 22: /* list_vars: list_vars COMMA ID  */
#line 204 "atlas.y"
                         { put_symbol((yyvsp[0].str), "var", (yyvsp[-3].str), 0); }
#line 1442 "atlas.tab.c"
    break;

  case 25: /* $@3: %empty  */
#line 215 "atlas.y"
              {
        char *genre = getGenre((yyvsp[-1].str));
        if (!genre) {
            fprintf(stderr, "Erreur ligne %d: '%s' non declare\n", line_num, (yyvsp[-1].str)); exit(1);
        }
        if (strcmp(genre, "const") == 0) {
            fprintf(stderr, "Erreur ligne %d: '%s' est une constante, affectation impossible\n", line_num, (yyvsp[-1].str)); exit(1);
        }
        char buf[20]; sprintf(buf, "%d", getAdr((yyvsp[-1].str)));
        emit("empiler-adr", buf);
    }
#line 1458 "atlas.tab.c"
    break;

  case 26: /* instruction: ID ASSIGN $@3 expression SEMICOLON  */
#line 226 "atlas.y"
                         {
        if (strcmp(getType((yyvsp[-4].str)), (yyvsp[-1].expr).type) != 0) {
            fprintf(stderr, "Erreur ligne %d: Incompatibilite de type dans l'affectation\n", line_num); exit(1);
        }
        emit("affect", NULL);
    }
#line 1469 "atlas.tab.c"
    break;

  case 27: /* instruction: LIRE ID SEMICOLON  */
#line 234 "atlas.y"
                        {
        char *genre = getGenre((yyvsp[-1].str));
        if (!genre) { fprintf(stderr, "Erreur ligne %d: '%s' non declare\n", line_num, (yyvsp[-1].str)); exit(1); }
        if (strcmp(genre, "const") == 0) { fprintf(stderr, "Erreur ligne %d: '%s' est une constante\n", line_num, (yyvsp[-1].str)); exit(1); }
        char buf[20]; sprintf(buf, "%d", getAdr((yyvsp[-1].str)));
        emit("empiler-adr", buf);
        emit("lire", NULL);
    }
#line 1482 "atlas.tab.c"
    break;

  case 28: /* instruction: LIRERC ID SEMICOLON  */
#line 244 "atlas.y"
                          {
        char *genre = getGenre((yyvsp[-1].str));
        if (!genre) { fprintf(stderr, "Erreur ligne %d: '%s' non declare\n", line_num, (yyvsp[-1].str)); exit(1); }
        if (strcmp(genre, "const") == 0) { fprintf(stderr, "Erreur ligne %d: '%s' est une constante\n", line_num, (yyvsp[-1].str)); exit(1); }
        char buf[20]; sprintf(buf, "%d", getAdr((yyvsp[-1].str)));
        emit("empiler-adr", buf);
        emit("lireRC", NULL);
    }
#line 1495 "atlas.tab.c"
    break;

  case 29: /* instruction: ECRIRE ID SEMICOLON  */
#line 254 "atlas.y"
                          {
        char buf[20]; sprintf(buf, "%d", getAdr((yyvsp[-1].str)));
        emit("empiler-adr", buf);
        emit("valeur-pile", NULL);
        emit("ecrire", NULL);
    }
#line 1506 "atlas.tab.c"
    break;

  case 30: /* instruction: ECRIRERC ID SEMICOLON  */
#line 262 "atlas.y"
                            {
        char buf[20]; sprintf(buf, "%d", getAdr((yyvsp[-1].str)));
        emit("empiler-adr", buf);
        emit("valeur-pile", NULL);
        emit("ecrireRC", NULL);
    }
#line 1517 "atlas.tab.c"
    break;

  case 31: /* instruction: IMPRIMER STRING SEMICOLON  */
#line 270 "atlas.y"
                                  { emit("imprimer",   (yyvsp[-1].str)); }
#line 1523 "atlas.tab.c"
    break;

  case 32: /* instruction: IMPRIMERRC STRING SEMICOLON  */
#line 273 "atlas.y"
                                  { emit("imprimerRC", (yyvsp[-1].str)); }
#line 1529 "atlas.tab.c"
    break;

  case 33: /* instruction: PASSER SEMICOLON  */
#line 276 "atlas.y"
                       { /* rien a generer */ }
#line 1535 "atlas.tab.c"
    break;

  case 34: /* $@4: %empty  */
#line 288 "atlas.y"
                   {
        int lbl_sinon = getLabel();
        int lbl_fin   = getLabel();

        push_sinon(lbl_sinon); 
        push_fin(lbl_fin);

        char buf[20]; 
        sprintf(buf, "%d", lbl_sinon);
        emit("bsf", buf);
    }
#line 1551 "atlas.tab.c"
    break;

  case 35: /* instruction: SI condition $@4 ALORS instructions sinon_opt FSI  */
#line 299 "atlas.y"
                                     {
        int lbl_fin = pop_fin();
        char buf[20];
        sprintf(buf, "%d", lbl_fin);
        emit("bra", buf);
    }
#line 1562 "atlas.tab.c"
    break;

  case 36: /* @5: %empty  */
#line 307 "atlas.y"
              {
        (yyval.val) = instruction_counter; /* memoriser le debut du test */
    }
#line 1570 "atlas.tab.c"
    break;

  case 37: /* @6: %empty  */
#line 310 "atlas.y"
              {
        int lbl_fin = getLabel();
        (yyval.val) = lbl_fin;
        char buf[20]; sprintf(buf, "%d", lbl_fin);
        emit("bsf", buf);
    }
#line 1581 "atlas.tab.c"
    break;

  case 38: /* instruction: TANTQUE @5 condition @6 FAIRE instruction FTQ SEMICOLON  */
#line 316 "atlas.y"
                                    {
        int lbl_debut = (yyvsp[-6].val);
        int lbl_fin   = (yyvsp[-4].val);
        char buf[20]; sprintf(buf, "%d", lbl_debut);
        emit("bra", buf);
        instruction_counter = lbl_fin;
    }
#line 1593 "atlas.tab.c"
    break;

  case 39: /* $@7: %empty  */
#line 325 "atlas.y"
          {
    if (strcmp(getType((yyvsp[0].str)), "ent") != 0) {
        fprintf(stderr, "Erreur ligne %d: La variable de boucle '%s' doit etre entiere\n", line_num, (yyvsp[0].str));
        exit(1);
    }
    if (strcmp(getGenre((yyvsp[0].str)), "const") == 0) {
        fprintf(stderr, "Erreur ligne %d: '%s' est une constante, impossible comme variable de boucle\n", line_num, (yyvsp[0].str));
        exit(1);
    }
}
#line 1608 "atlas.tab.c"
    break;

  case 40: /* $@8: %empty  */
#line 335 "atlas.y"
       {
    /* Empiler l'adresse de i AVANT d'évaluer vi */
    char buf[20]; sprintf(buf, "%d", getAdr((yyvsp[-2].str)));
    emit("empiler-adr", buf);
    /* pile : [adr_i]  → vi sera empilé après par expression */
}
#line 1619 "atlas.tab.c"
    break;

  case 41: /* @9: %empty  */
#line 341 "atlas.y"
           {
    if (strcmp((yyvsp[0].expr).type, "ent") != 0) {
        fprintf(stderr, "Erreur ligne %d: La valeur initiale doit etre entiere\n", line_num);
        exit(1);
    }
    /* pile : [adr_i, vi] → affect correct ✓ */
    emit("affect", NULL);

    /* lbl_debut APRÈS affect, AVANT le test */
    (yyval.val) = instruction_counter;
}
#line 1635 "atlas.tab.c"
    break;

  case 42: /* $@10: %empty  */
#line 352 "atlas.y"
       {
    /* Empiler i EN PREMIER */
    char buf[20]; sprintf(buf, "%d", getAdr((yyvsp[-6].str)));
    emit("empiler-adr", buf);
    emit("valeur-pile", NULL);
}
#line 1646 "atlas.tab.c"
    break;

  case 43: /* @11: %empty  */
#line 358 "atlas.y"
                   {
    if (strcmp((yyvsp[-1].expr).type, "ent") != 0) {
        fprintf(stderr, "Erreur ligne %d: La valeur finale doit etre entiere\n", line_num);
        exit(1);
    }
    /* pile : [i, vf] → pp-egal : i <= vf ✓ */
    emit("pp-egal", NULL);

    int lbl_fin = getLabel();
    (yyval.val) = lbl_fin;
    char buf[20]; sprintf(buf, "%d", lbl_fin);
    emit("bsf", buf);
}
#line 1664 "atlas.tab.c"
    break;

  case 44: /* instruction: POUR ID $@7 DEPUIS $@8 expression @9 JUSQUA $@10 expression pas_opt @11 FAIRE instruction FPOUR  */
#line 371 "atlas.y"
                        {
    int lbl_debut = (yyvsp[-8].val);    /* action après affect      */
    int lbl_fin   = (yyvsp[-3].val);   /* action après pas_opt     */
    int pas       = (yyvsp[-4].val);   /* pas_opt                  */

    char buf[20]; sprintf(buf, "%d", getAdr((yyvsp[-13].str)));
    emit("empiler-adr", buf);
    emit("empiler-adr", buf);
    emit("valeur-pile", NULL);
    char pas_str[20]; sprintf(pas_str, "%d", pas);
    emit("empiler-val", pas_str);
    emit("plus", NULL);
    emit("affect", NULL);

    char buf2[20]; sprintf(buf2, "%d", lbl_debut);
    emit("bra", buf2);
    instruction_counter = lbl_fin;
}
#line 1687 "atlas.tab.c"
    break;

  case 45: /* sinon_opt: %empty  */
#line 392 "atlas.y"
    {
        int lbl_sinon = pop_sinon();
        int lbl_fin   = pop_fin();

        (yyval.val) = lbl_fin;  
    }
#line 1698 "atlas.tab.c"
    break;

  case 46: /* sinon_opt: SINON instructions  */
#line 400 "atlas.y"
    {
        int lbl_fin = pop_fin();

        char buf[20];
        sprintf(buf, "%d", lbl_fin);
        emit("bra", buf);

        int lbl_sinon = pop_sinon();
        

        (yyval.val) = lbl_fin;
    }
#line 1715 "atlas.tab.c"
    break;

  case 47: /* pas_opt: %empty  */
#line 415 "atlas.y"
               { (yyval.val) = 1; }
#line 1721 "atlas.tab.c"
    break;

  case 48: /* pas_opt: PARPAS INT  */
#line 416 "atlas.y"
                 { (yyval.val) = (yyvsp[0].val); }
#line 1727 "atlas.tab.c"
    break;

  case 49: /* condition: LPAREN expression RPAREN  */
#line 420 "atlas.y"
                             {
        if (strcmp((yyvsp[-1].expr).type, "bool") != 0) {
            fprintf(stderr, "Erreur ligne %d: La condition doit etre un booleen\n", line_num);
            exit(1);
        }
        (yyval.expr) = (yyvsp[-1].expr);
    }
#line 1739 "atlas.tab.c"
    break;

  case 50: /* expression: INT  */
#line 430 "atlas.y"
        {
        strcpy((yyval.expr).type, "ent"); (yyval.expr).value = (yyvsp[0].val);
        char buf[20]; sprintf(buf, "%d", (yyvsp[0].val));
        emit("empiler-val", buf);
    }
#line 1749 "atlas.tab.c"
    break;

  case 51: /* expression: BOOL_VAL  */
#line 435 "atlas.y"
               {
        strcpy((yyval.expr).type, "bool"); (yyval.expr).value = (yyvsp[0].val);
        char buf[20]; sprintf(buf, "%d", (yyvsp[0].val));
        emit("empiler-val", buf);
    }
#line 1759 "atlas.tab.c"
    break;

  case 52: /* expression: ID  */
#line 440 "atlas.y"
         {
        int idx = lookup((yyvsp[0].str));
        if (idx == -1) {
            fprintf(stderr, "Erreur ligne %d: '%s' non declare\n", line_num, (yyvsp[0].str)); exit(1);
        }
        strcpy((yyval.expr).type, symbol_table[idx].type);
        (yyval.expr).value = symbol_table[idx].value;
        char buf[20]; sprintf(buf, "%d", symbol_table[idx].address);
        emit("empiler-adr", buf);
        emit("valeur-pile", NULL);
    }
#line 1775 "atlas.tab.c"
    break;

  case 53: /* expression: expression PLUS expression  */
#line 452 "atlas.y"
                                 {
        if (strcmp((yyvsp[-2].expr).type, "ent") != 0 || strcmp((yyvsp[0].expr).type, "ent") != 0)
            yyerror("Les operandes de '+' doivent etre des entiers");
        strcpy((yyval.expr).type, "ent"); emit("plus", NULL);
    }
#line 1785 "atlas.tab.c"
    break;

  case 54: /* expression: expression MINUS expression  */
#line 457 "atlas.y"
                                  {
        if (strcmp((yyvsp[-2].expr).type, "ent") != 0 || strcmp((yyvsp[0].expr).type, "ent") != 0)
            yyerror("Les operandes de '-' doivent etre des entiers");
        strcpy((yyval.expr).type, "ent"); emit("moins", NULL);
    }
#line 1795 "atlas.tab.c"
    break;

  case 55: /* expression: expression MULT expression  */
#line 462 "atlas.y"
                                 {
        if (strcmp((yyvsp[-2].expr).type, "ent") != 0 || strcmp((yyvsp[0].expr).type, "ent") != 0)
            yyerror("Les operandes de '*' doivent etre des entiers");
        strcpy((yyval.expr).type, "ent"); emit("mult", NULL);
    }
#line 1805 "atlas.tab.c"
    break;

  case 56: /* expression: expression DIV expression  */
#line 467 "atlas.y"
                                {
        if (strcmp((yyvsp[-2].expr).type, "ent") != 0 || strcmp((yyvsp[0].expr).type, "ent") != 0)
            yyerror("Les operandes de '/' doivent etre des entiers");
        strcpy((yyval.expr).type, "ent"); emit("div", NULL);
    }
#line 1815 "atlas.tab.c"
    break;

  case 57: /* expression: expression MOD expression  */
#line 472 "atlas.y"
                                {
        if (strcmp((yyvsp[-2].expr).type, "ent") != 0 || strcmp((yyvsp[0].expr).type, "ent") != 0)
            yyerror("Les operandes de '%' doivent etre des entiers");
        strcpy((yyval.expr).type, "ent"); emit("mod", NULL);
    }
#line 1825 "atlas.tab.c"
    break;

  case 58: /* expression: PUISS LPAREN expression COMMA expression RPAREN  */
#line 477 "atlas.y"
                                                      {
    if (strcmp((yyvsp[-3].expr).type, "ent") != 0 || strcmp((yyvsp[-1].expr).type, "ent") != 0)
        yyerror("Les operandes de 'puiss' doivent etre des entiers");
    strcpy((yyval.expr).type, "ent");
    emit("puiss", NULL);
}
#line 1836 "atlas.tab.c"
    break;

  case 59: /* expression: VALABS LPAREN expression RPAREN  */
#line 483 "atlas.y"
                                      {
        if (strcmp((yyvsp[-1].expr).type, "ent") != 0)
            yyerror("L'operande de 'valabs' doit etre un entier");
        strcpy((yyval.expr).type, "ent"); emit("valabs", NULL);
    }
#line 1846 "atlas.tab.c"
    break;

  case 60: /* expression: MINUS expression  */
#line 488 "atlas.y"
                                    {
        if (strcmp((yyvsp[0].expr).type, "ent") != 0)
            yyerror("L'operande du moins unaire doit etre un entier");
        strcpy((yyval.expr).type, "ent"); emit("neg", NULL);
    }
#line 1856 "atlas.tab.c"
    break;

  case 61: /* expression: expression EQ expression  */
#line 494 "atlas.y"
                                { strcpy((yyval.expr).type, "bool"); emit("egal",    NULL); }
#line 1862 "atlas.tab.c"
    break;

  case 62: /* expression: expression DIFF expression  */
#line 495 "atlas.y"
                                 { strcpy((yyval.expr).type, "bool"); emit("dif",    NULL); }
#line 1868 "atlas.tab.c"
    break;

  case 63: /* expression: expression LT expression  */
#line 496 "atlas.y"
                                { strcpy((yyval.expr).type, "bool"); emit("pps",     NULL); }
#line 1874 "atlas.tab.c"
    break;

  case 64: /* expression: expression GT expression  */
#line 497 "atlas.y"
                                { strcpy((yyval.expr).type, "bool"); emit("pgs",     NULL); }
#line 1880 "atlas.tab.c"
    break;

  case 65: /* expression: expression LTE expression  */
#line 498 "atlas.y"
                                { strcpy((yyval.expr).type, "bool"); emit("pp-egal", NULL); }
#line 1886 "atlas.tab.c"
    break;

  case 66: /* expression: expression GTE expression  */
#line 499 "atlas.y"
                                { strcpy((yyval.expr).type, "bool"); emit("pg-egal", NULL); }
#line 1892 "atlas.tab.c"
    break;

  case 67: /* expression: expression ET expression  */
#line 501 "atlas.y"
                               {
        if (strcmp((yyvsp[-2].expr).type, "bool") != 0 || strcmp((yyvsp[0].expr).type, "bool") != 0)
            yyerror("Les operandes de 'et' doivent etre des booleens");
        strcpy((yyval.expr).type, "bool"); emit("et", NULL);
    }
#line 1902 "atlas.tab.c"
    break;

  case 68: /* expression: expression OU expression  */
#line 506 "atlas.y"
                               {
        if (strcmp((yyvsp[-2].expr).type, "bool") != 0 || strcmp((yyvsp[0].expr).type, "bool") != 0)
            yyerror("Les operandes de 'ou' doivent etre des booleens");
        strcpy((yyval.expr).type, "bool"); emit("ou", NULL);
    }
#line 1912 "atlas.tab.c"
    break;

  case 69: /* expression: NON expression  */
#line 511 "atlas.y"
                     {
        if (strcmp((yyvsp[0].expr).type, "bool") != 0)
            yyerror("L'operande de 'non' doit etre un booleen");
        strcpy((yyval.expr).type, "bool"); emit("non", NULL);
    }
#line 1922 "atlas.tab.c"
    break;

  case 70: /* expression: LPAREN expression RPAREN  */
#line 516 "atlas.y"
                               { (yyval.expr) = (yyvsp[-1].expr); }
#line 1928 "atlas.tab.c"
    break;


#line 1932 "atlas.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 519 "atlas.y"

