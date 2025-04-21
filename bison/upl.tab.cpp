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
#line 1 "upl.y"

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include "lexer.hpp"
#include "upl_types.h"

using namespace std;

// Root của cây cú pháp
ASTNode* program_root = nullptr;

// Lexer hiện tại
Lexer* current_lexer = nullptr;
Token current_token;

// Khai báo các hàm
int yylex();
void yyerror(const char* s);
void printAST(ASTNode* node, int depth = 0);


#line 95 "upl.tab.cpp"

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

#include "upl.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BEGIN_TOKEN = 3,                /* BEGIN_TOKEN  */
  YYSYMBOL_END = 4,                        /* END  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_BOOL = 6,                       /* BOOL  */
  YYSYMBOL_IF = 7,                         /* IF  */
  YYSYMBOL_THEN = 8,                       /* THEN  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_DO = 10,                        /* DO  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_FOR = 12,                       /* FOR  */
  YYSYMBOL_PRINT = 13,                     /* PRINT  */
  YYSYMBOL_PLUS = 14,                      /* PLUS  */
  YYSYMBOL_MULTIPLY = 15,                  /* MULTIPLY  */
  YYSYMBOL_GREATER = 16,                   /* GREATER  */
  YYSYMBOL_GREATER_EQUAL = 17,             /* GREATER_EQUAL  */
  YYSYMBOL_EQUAL = 18,                     /* EQUAL  */
  YYSYMBOL_ASSIGN = 19,                    /* ASSIGN  */
  YYSYMBOL_LEFT_PAREN = 20,                /* LEFT_PAREN  */
  YYSYMBOL_RIGHT_PAREN = 21,               /* RIGHT_PAREN  */
  YYSYMBOL_LEFT_BRACE = 22,                /* LEFT_BRACE  */
  YYSYMBOL_RIGHT_BRACE = 23,               /* RIGHT_BRACE  */
  YYSYMBOL_SEMICOLON = 24,                 /* SEMICOLON  */
  YYSYMBOL_IDENTIFIER = 25,                /* IDENTIFIER  */
  YYSYMBOL_NUMBER = 26,                    /* NUMBER  */
  YYSYMBOL_TRUE = 27,                      /* TRUE  */
  YYSYMBOL_FALSE = 28,                     /* FALSE  */
  YYSYMBOL_ERROR = 29,                     /* ERROR  */
  YYSYMBOL_YYACCEPT = 30,                  /* $accept  */
  YYSYMBOL_program = 31,                   /* program  */
  YYSYMBOL_stmts = 32,                     /* stmts  */
  YYSYMBOL_stmt = 33,                      /* stmt  */
  YYSYMBOL_expression = 34,                /* expression  */
  YYSYMBOL_addition = 35,                  /* addition  */
  YYSYMBOL_multiplication = 36,            /* multiplication  */
  YYSYMBOL_factor = 37,                    /* factor  */
  YYSYMBOL_declaration = 38,               /* declaration  */
  YYSYMBOL_declaration_tail = 39,          /* declaration_tail  */
  YYSYMBOL_assignment = 40,                /* assignment  */
  YYSYMBOL_if_stmt = 41,                   /* if_stmt  */
  YYSYMBOL_else_part = 42,                 /* else_part  */
  YYSYMBOL_do_while_stmt = 43,             /* do_while_stmt  */
  YYSYMBOL_for_stmt = 44,                  /* for_stmt  */
  YYSYMBOL_for_init = 45,                  /* for_init  */
  YYSYMBOL_for_condition = 46,             /* for_condition  */
  YYSYMBOL_for_update = 47,                /* for_update  */
  YYSYMBOL_print_stmt = 48,                /* print_stmt  */
  YYSYMBOL_block_stmt = 49,                /* block_stmt  */
  YYSYMBOL_dtype = 50,                     /* dtype  */
  YYSYMBOL_relop = 51                      /* relop  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  30
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   143

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  48
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  89

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   284


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
      25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    66,    66,    74,    85,    89,    90,    91,    92,    93,
      94,    95,    96,    97,   102,   110,   111,   119,   120,   128,
     129,   137,   141,   144,   147,   150,   156,   164,   168,   176,
     185,   196,   197,   201,   209,   219,   220,   221,   225,   226,
     230,   231,   235,   242,   254,   255,   259,   260,   261
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
  "\"end of file\"", "error", "\"invalid token\"", "BEGIN_TOKEN", "END",
  "INT", "BOOL", "IF", "THEN", "ELSE", "DO", "WHILE", "FOR", "PRINT",
  "PLUS", "MULTIPLY", "GREATER", "GREATER_EQUAL", "EQUAL", "ASSIGN",
  "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE", "SEMICOLON",
  "IDENTIFIER", "NUMBER", "TRUE", "FALSE", "ERROR", "$accept", "program",
  "stmts", "stmt", "expression", "addition", "multiplication", "factor",
  "declaration", "declaration_tail", "assignment", "if_stmt", "else_part",
  "do_while_stmt", "for_stmt", "for_init", "for_condition", "for_update",
  "print_stmt", "block_stmt", "dtype", "relop", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-73)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-5)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       1,    39,    12,   -15,   -73,   -73,    -2,    97,    -1,     6,
      30,    69,     2,   -73,   -73,   -73,    24,    10,    96,    15,
      19,   -73,    17,    18,   -73,    23,   -73,    29,   -73,    14,
     -73,   -73,   -73,    30,    43,     0,    30,   -73,    67,    45,
      30,   -73,   -73,   -73,   -73,   -73,   -73,    30,    30,    30,
     -73,   -73,   -73,   -73,    50,   -73,   110,    57,     2,   -73,
     -73,    54,   116,   -73,   -73,    55,    15,    19,   -73,    30,
      78,    30,    30,   -73,    55,    65,   122,    55,    66,    84,
     -73,    74,    65,   -73,   -73,    79,   -73,    97,   -73
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,    44,    45,     0,     0,     0,     0,
       0,     0,    21,    22,    23,    24,     0,     0,     0,    15,
      17,    19,     0,     0,     8,     0,    10,     0,    12,     0,
       1,    14,    13,     0,     0,    37,     0,    21,     0,     0,
       0,     2,     3,    46,    47,    48,     5,     0,     0,     0,
       7,     6,     9,    11,    27,    26,     0,     0,     0,    35,
      36,     0,     0,    25,    43,    29,    16,    18,    20,     0,
       0,     0,    39,    42,    28,     0,     0,    38,     0,    32,
      33,    41,     0,    30,    40,     0,    31,     0,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -73,   -73,    -4,    -7,    -9,    58,    53,    59,    71,   -73,
     -33,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -72,
     -73,   -73
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,    16,    17,    18,    19,    20,    21,    22,    55,
      23,    24,    83,    25,    26,    61,    78,    85,    27,    28,
      29,    47
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      34,    38,    60,    79,     1,     4,     5,    39,    31,    32,
      86,     3,    30,    42,    -4,     4,     5,     6,    33,    35,
       7,    40,     8,     9,    56,    58,    36,    62,    41,    48,
      10,    65,    11,    -4,    49,    12,    13,    14,    15,    54,
       3,    50,    51,    -4,     4,     5,     6,    52,    84,     7,
      10,     8,     9,    53,    57,    37,    13,    14,    15,    10,
      74,    11,    76,    77,    12,    13,    14,    15,    64,    69,
       3,    43,    44,    45,     4,     5,     6,    71,    72,     7,
      88,     8,     9,    43,    44,    45,    75,    11,    63,    10,
      81,    11,    -4,    82,    12,    13,    14,    15,     3,    58,
      87,    67,     4,     5,     6,    66,    59,     7,    68,     8,
       9,     0,    43,    44,    45,     0,     0,    10,     0,    11,
      46,     0,    12,    13,    14,    15,    43,    44,    45,     0,
       0,    70,    43,    44,    45,     0,     0,    73,    43,    44,
      45,     0,     0,    80
};

static const yytype_int8 yycheck[] =
{
       7,    10,    35,    75,     3,     5,     6,    11,    23,    24,
      82,     1,     0,    17,     4,     5,     6,     7,    20,    20,
      10,    19,    12,    13,    33,    25,    20,    36,     4,    14,
      20,    40,    22,    23,    15,    25,    26,    27,    28,    25,
       1,    24,    24,     4,     5,     6,     7,    24,    81,    10,
      20,    12,    13,    24,    11,    25,    26,    27,    28,    20,
      69,    22,    71,    72,    25,    26,    27,    28,    23,    19,
       1,    16,    17,    18,     5,     6,     7,    20,    24,    10,
      87,    12,    13,    16,    17,    18,     8,    22,    21,    20,
      24,    22,    23,     9,    25,    26,    27,    28,     1,    25,
      21,    48,     5,     6,     7,    47,    35,    10,    49,    12,
      13,    -1,    16,    17,    18,    -1,    -1,    20,    -1,    22,
      24,    -1,    25,    26,    27,    28,    16,    17,    18,    -1,
      -1,    21,    16,    17,    18,    -1,    -1,    21,    16,    17,
      18,    -1,    -1,    21
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    31,     1,     5,     6,     7,    10,    12,    13,
      20,    22,    25,    26,    27,    28,    32,    33,    34,    35,
      36,    37,    38,    40,    41,    43,    44,    48,    49,    50,
       0,    23,    24,    20,    33,    20,    20,    25,    34,    32,
      19,     4,    32,    16,    17,    18,    24,    51,    14,    15,
      24,    24,    24,    24,    25,    39,    34,    11,    25,    38,
      40,    45,    34,    21,    23,    34,    35,    36,    37,    19,
      21,    20,    24,    21,    34,     8,    34,    34,    46,    49,
      21,    24,     9,    42,    40,    47,    49,    21,    33
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    30,    31,    32,    32,    33,    33,    33,    33,    33,
      33,    33,    33,    33,    33,    34,    34,    35,    35,    36,
      36,    37,    37,    37,    37,    37,    38,    39,    39,    40,
      41,    42,    42,    43,    44,    45,    45,    45,    46,    46,
      47,    47,    48,    49,    50,    50,    51,    51,    51
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     0,     2,     2,     2,     1,     2,
       1,     2,     1,     2,     2,     1,     3,     1,     3,     1,
       3,     1,     1,     1,     1,     3,     2,     1,     3,     3,
       7,     2,     0,     6,     9,     1,     1,     0,     1,     0,
       1,     0,     4,     3,     1,     1,     1,     1,     1
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
  case 2: /* program: BEGIN_TOKEN stmts END  */
#line 66 "upl.y"
                            { 
        (yyval.node_ptr) = new ASTNode("program");
        (yyval.node_ptr)->addChild((yyvsp[-1].node_ptr));
        program_root = (yyval.node_ptr);
    }
#line 1201 "upl.tab.cpp"
    break;

  case 3: /* stmts: stmt stmts  */
#line 74 "upl.y"
                 {
        (yyval.node_ptr) = new ASTNode("stmts");
        (yyval.node_ptr)->addChild((yyvsp[-1].node_ptr));
        
        ASTNode* stmtsNode = (yyvsp[0].node_ptr);
        for (auto& child : stmtsNode->children) {
            (yyval.node_ptr)->addChild(child);
        }
        stmtsNode->children.clear();
        delete stmtsNode;
    }
#line 1217 "upl.tab.cpp"
    break;

  case 4: /* stmts: %empty  */
#line 85 "upl.y"
                    { (yyval.node_ptr) = new ASTNode("stmts"); }
#line 1223 "upl.tab.cpp"
    break;

  case 5: /* stmt: expression SEMICOLON  */
#line 89 "upl.y"
                           { (yyval.node_ptr) = (yyvsp[-1].node_ptr); }
#line 1229 "upl.tab.cpp"
    break;

  case 6: /* stmt: assignment SEMICOLON  */
#line 90 "upl.y"
                           { (yyval.node_ptr) = (yyvsp[-1].node_ptr); }
#line 1235 "upl.tab.cpp"
    break;

  case 7: /* stmt: declaration SEMICOLON  */
#line 91 "upl.y"
                            { (yyval.node_ptr) = (yyvsp[-1].node_ptr); }
#line 1241 "upl.tab.cpp"
    break;

  case 8: /* stmt: if_stmt  */
#line 92 "upl.y"
              { (yyval.node_ptr) = (yyvsp[0].node_ptr); }
#line 1247 "upl.tab.cpp"
    break;

  case 9: /* stmt: do_while_stmt SEMICOLON  */
#line 93 "upl.y"
                              { (yyval.node_ptr) = (yyvsp[-1].node_ptr); }
#line 1253 "upl.tab.cpp"
    break;

  case 10: /* stmt: for_stmt  */
#line 94 "upl.y"
               { (yyval.node_ptr) = (yyvsp[0].node_ptr); }
#line 1259 "upl.tab.cpp"
    break;

  case 11: /* stmt: print_stmt SEMICOLON  */
#line 95 "upl.y"
                           { (yyval.node_ptr) = (yyvsp[-1].node_ptr); }
#line 1265 "upl.tab.cpp"
    break;

  case 12: /* stmt: block_stmt  */
#line 96 "upl.y"
                 { (yyval.node_ptr) = (yyvsp[0].node_ptr); }
#line 1271 "upl.tab.cpp"
    break;

  case 13: /* stmt: error SEMICOLON  */
#line 97 "upl.y"
                      {
        // Phục hồi sau khi gặp lỗi và tìm thấy dấu chấm phẩy
        (yyval.node_ptr) = new ASTNode("error");
        yyerrok;  // Báo cho Bison biết đã xử lý lỗi
    }
#line 1281 "upl.tab.cpp"
    break;

  case 14: /* stmt: error RIGHT_BRACE  */
#line 102 "upl.y"
                        {
        // Phục hồi khi gặp dấu } (hữu ích cho lỗi trong khối)
        (yyval.node_ptr) = new ASTNode("error");
        yyerrok;
    }
#line 1291 "upl.tab.cpp"
    break;

  case 15: /* expression: addition  */
#line 110 "upl.y"
               { (yyval.node_ptr) = (yyvsp[0].node_ptr); }
#line 1297 "upl.tab.cpp"
    break;

  case 16: /* expression: expression relop addition  */
#line 111 "upl.y"
                                {
        (yyval.node_ptr) = (yyvsp[-1].node_ptr);
        (yyval.node_ptr)->addChild((yyvsp[-2].node_ptr));
        (yyval.node_ptr)->addChild((yyvsp[0].node_ptr));
    }
#line 1307 "upl.tab.cpp"
    break;

  case 17: /* addition: multiplication  */
#line 119 "upl.y"
                     { (yyval.node_ptr) = (yyvsp[0].node_ptr); }
#line 1313 "upl.tab.cpp"
    break;

  case 18: /* addition: addition PLUS multiplication  */
#line 120 "upl.y"
                                   {
        (yyval.node_ptr) = new ASTNode("addition", "+");
        (yyval.node_ptr)->addChild((yyvsp[-2].node_ptr));
        (yyval.node_ptr)->addChild((yyvsp[0].node_ptr));
    }
#line 1323 "upl.tab.cpp"
    break;

  case 19: /* multiplication: factor  */
#line 128 "upl.y"
             { (yyval.node_ptr) = (yyvsp[0].node_ptr); }
#line 1329 "upl.tab.cpp"
    break;

  case 20: /* multiplication: multiplication MULTIPLY factor  */
#line 129 "upl.y"
                                     {
        (yyval.node_ptr) = new ASTNode("multiplication", "*");
        (yyval.node_ptr)->addChild((yyvsp[-2].node_ptr));
        (yyval.node_ptr)->addChild((yyvsp[0].node_ptr));
    }
#line 1339 "upl.tab.cpp"
    break;

  case 21: /* factor: IDENTIFIER  */
#line 137 "upl.y"
                 {
        (yyval.node_ptr) = new ASTNode("identifier", (yyvsp[0].str_val));
        free((yyvsp[0].str_val));
    }
#line 1348 "upl.tab.cpp"
    break;

  case 22: /* factor: NUMBER  */
#line 141 "upl.y"
             {
        (yyval.node_ptr) = new ASTNode("number", to_string((yyvsp[0].int_val)));
    }
#line 1356 "upl.tab.cpp"
    break;

  case 23: /* factor: TRUE  */
#line 144 "upl.y"
           {
        (yyval.node_ptr) = new ASTNode("boolean", "true");
    }
#line 1364 "upl.tab.cpp"
    break;

  case 24: /* factor: FALSE  */
#line 147 "upl.y"
            {
        (yyval.node_ptr) = new ASTNode("boolean", "false");
    }
#line 1372 "upl.tab.cpp"
    break;

  case 25: /* factor: LEFT_PAREN expression RIGHT_PAREN  */
#line 150 "upl.y"
                                        {
        (yyval.node_ptr) = (yyvsp[-1].node_ptr);
    }
#line 1380 "upl.tab.cpp"
    break;

  case 26: /* declaration: dtype declaration_tail  */
#line 156 "upl.y"
                             {
        (yyval.node_ptr) = new ASTNode("declaration");
        (yyval.node_ptr)->addChild((yyvsp[-1].node_ptr));
        (yyval.node_ptr)->addChild((yyvsp[0].node_ptr));
    }
#line 1390 "upl.tab.cpp"
    break;

  case 27: /* declaration_tail: IDENTIFIER  */
#line 164 "upl.y"
                 {
        (yyval.node_ptr) = new ASTNode("identifier", (yyvsp[0].str_val));
        free((yyvsp[0].str_val));
    }
#line 1399 "upl.tab.cpp"
    break;

  case 28: /* declaration_tail: IDENTIFIER ASSIGN expression  */
#line 168 "upl.y"
                                   {
        (yyval.node_ptr) = new ASTNode("identifier_with_init", (yyvsp[-2].str_val));
        (yyval.node_ptr)->addChild((yyvsp[0].node_ptr));
        free((yyvsp[-2].str_val));
    }
#line 1409 "upl.tab.cpp"
    break;

  case 29: /* assignment: IDENTIFIER ASSIGN expression  */
#line 176 "upl.y"
                                   {
        (yyval.node_ptr) = new ASTNode("assignment");
        (yyval.node_ptr)->addChild(new ASTNode("identifier", (yyvsp[-2].str_val)));
        (yyval.node_ptr)->addChild((yyvsp[0].node_ptr));
        free((yyvsp[-2].str_val));
    }
#line 1420 "upl.tab.cpp"
    break;

  case 30: /* if_stmt: IF LEFT_PAREN expression RIGHT_PAREN THEN block_stmt else_part  */
#line 185 "upl.y"
                                                                     {
        (yyval.node_ptr) = new ASTNode("if_statement");
        (yyval.node_ptr)->addChild((yyvsp[-4].node_ptr)); // condition
        (yyval.node_ptr)->addChild((yyvsp[-1].node_ptr)); // then block
        if ((yyvsp[0].node_ptr)) {
            (yyval.node_ptr)->addChild((yyvsp[0].node_ptr)); // else block (if exists)
        }
    }
#line 1433 "upl.tab.cpp"
    break;

  case 31: /* else_part: ELSE block_stmt  */
#line 196 "upl.y"
                      { (yyval.node_ptr) = (yyvsp[0].node_ptr); }
#line 1439 "upl.tab.cpp"
    break;

  case 32: /* else_part: %empty  */
#line 197 "upl.y"
                    { (yyval.node_ptr) = nullptr; }
#line 1445 "upl.tab.cpp"
    break;

  case 33: /* do_while_stmt: DO stmt WHILE LEFT_PAREN expression RIGHT_PAREN  */
#line 201 "upl.y"
                                                      {
        (yyval.node_ptr) = new ASTNode("do_while");
        (yyval.node_ptr)->addChild((yyvsp[-4].node_ptr)); // body
        (yyval.node_ptr)->addChild((yyvsp[-1].node_ptr)); // condition
    }
#line 1455 "upl.tab.cpp"
    break;

  case 34: /* for_stmt: FOR LEFT_PAREN for_init SEMICOLON for_condition SEMICOLON for_update RIGHT_PAREN stmt  */
#line 209 "upl.y"
                                                                                            {
        (yyval.node_ptr) = new ASTNode("for");
        if ((yyvsp[-6].node_ptr)) (yyval.node_ptr)->addChild((yyvsp[-6].node_ptr)); // init
        if ((yyvsp[-4].node_ptr)) (yyval.node_ptr)->addChild((yyvsp[-4].node_ptr)); // condition
        if ((yyvsp[-2].node_ptr)) (yyval.node_ptr)->addChild((yyvsp[-2].node_ptr)); // update
        (yyval.node_ptr)->addChild((yyvsp[0].node_ptr)); // body
    }
#line 1467 "upl.tab.cpp"
    break;

  case 35: /* for_init: declaration  */
#line 219 "upl.y"
                  { (yyval.node_ptr) = (yyvsp[0].node_ptr); }
#line 1473 "upl.tab.cpp"
    break;

  case 36: /* for_init: assignment  */
#line 220 "upl.y"
                 { (yyval.node_ptr) = (yyvsp[0].node_ptr); }
#line 1479 "upl.tab.cpp"
    break;

  case 37: /* for_init: %empty  */
#line 221 "upl.y"
                    { (yyval.node_ptr) = nullptr; }
#line 1485 "upl.tab.cpp"
    break;

  case 38: /* for_condition: expression  */
#line 225 "upl.y"
                 { (yyval.node_ptr) = (yyvsp[0].node_ptr); }
#line 1491 "upl.tab.cpp"
    break;

  case 39: /* for_condition: %empty  */
#line 226 "upl.y"
                    { (yyval.node_ptr) = nullptr; }
#line 1497 "upl.tab.cpp"
    break;

  case 40: /* for_update: assignment  */
#line 230 "upl.y"
                 { (yyval.node_ptr) = (yyvsp[0].node_ptr); }
#line 1503 "upl.tab.cpp"
    break;

  case 41: /* for_update: %empty  */
#line 231 "upl.y"
                    { (yyval.node_ptr) = nullptr; }
#line 1509 "upl.tab.cpp"
    break;

  case 42: /* print_stmt: PRINT LEFT_PAREN expression RIGHT_PAREN  */
#line 235 "upl.y"
                                              {
        (yyval.node_ptr) = new ASTNode("print");
        (yyval.node_ptr)->addChild((yyvsp[-1].node_ptr));
    }
#line 1518 "upl.tab.cpp"
    break;

  case 43: /* block_stmt: LEFT_BRACE stmts RIGHT_BRACE  */
#line 242 "upl.y"
                                   {
        (yyval.node_ptr) = new ASTNode("block");
        ASTNode* stmtsNode = (yyvsp[-1].node_ptr);
        for (auto& child : stmtsNode->children) {
            (yyval.node_ptr)->addChild(child);
        }
        stmtsNode->children.clear();
        delete stmtsNode;
    }
#line 1532 "upl.tab.cpp"
    break;

  case 44: /* dtype: INT  */
#line 254 "upl.y"
          { (yyval.node_ptr) = new ASTNode("type", "int"); }
#line 1538 "upl.tab.cpp"
    break;

  case 45: /* dtype: BOOL  */
#line 255 "upl.y"
           { (yyval.node_ptr) = new ASTNode("type", "bool"); }
#line 1544 "upl.tab.cpp"
    break;

  case 46: /* relop: GREATER  */
#line 259 "upl.y"
              { (yyval.node_ptr) = new ASTNode("relop", ">"); }
#line 1550 "upl.tab.cpp"
    break;

  case 47: /* relop: GREATER_EQUAL  */
#line 260 "upl.y"
                    { (yyval.node_ptr) = new ASTNode("relop", ">="); }
#line 1556 "upl.tab.cpp"
    break;

  case 48: /* relop: EQUAL  */
#line 261 "upl.y"
            { (yyval.node_ptr) = new ASTNode("relop", "=="); }
#line 1562 "upl.tab.cpp"
    break;


#line 1566 "upl.tab.cpp"

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

#line 264 "upl.y"


int error_count = 0;
bool recovery_mode = false;

// Hàm chuyển đổi từ TokenType sang token Bison
int tokenTypeToBison(TokenType type) {
    switch (type) {
        case L_TOKEN_BEGIN: return BEGIN_TOKEN;
        case L_TOKEN_END: return END;
        case L_TOKEN_INT: return INT;
        case L_TOKEN_BOOL: return BOOL;
        case L_TOKEN_IF: return IF;
        case L_TOKEN_THEN: return THEN;
        case L_TOKEN_ELSE: return ELSE;
        case L_TOKEN_DO: return DO;
        case L_TOKEN_WHILE: return WHILE;
        case L_TOKEN_FOR: return FOR;
        case L_TOKEN_PRINT: return PRINT;
        case L_TOKEN_PLUS: return PLUS;
        case L_TOKEN_MULTIPLY: return MULTIPLY;
        case L_TOKEN_GREATER: return GREATER;
        case L_TOKEN_GREATER_EQUAL: return GREATER_EQUAL;
        case L_TOKEN_EQUAL: return EQUAL;
        case L_TOKEN_ASSIGN: return ASSIGN;
        case L_TOKEN_LEFT_PAREN: return LEFT_PAREN;
        case L_TOKEN_RIGHT_PAREN: return RIGHT_PAREN;
        case L_TOKEN_LEFT_BRACE: return LEFT_BRACE;
        case L_TOKEN_RIGHT_BRACE: return RIGHT_BRACE;
        case L_TOKEN_SEMICOLON: return SEMICOLON;
        case L_TOKEN_IDENTIFIER: return IDENTIFIER;
        case L_TOKEN_NUMBER: return NUMBER;
        case L_TOKEN_TRUE: return TRUE;
        case L_TOKEN_FALSE: return FALSE;
        case L_TOKEN_EOF: return 0;  // Bison sử dụng 0 cho EOF
        default: return -1;  // Token không xác định
    }
}

// Triển khai hàm yylex cho Bison
int yylex() {
    if (!current_lexer) {
        return 0; // EOF nếu không có lexer
    }
    
    current_token = current_lexer->nextToken();
    
    // Bỏ qua token lỗi từ lexer
    while (current_token.type == L_TOKEN_ERROR) {
        cerr << "Lexical error: " << current_token.message << " at line " 
             << current_token.line << ", column " << current_token.column << endl;
        current_token = current_lexer->nextToken();
    }
    
    // Kiểm tra EOF
    if (current_token.type == L_TOKEN_EOF) {
        return 0;
    }
    
    // Xử lý phục hồi lỗi
    if (recovery_mode) {
        // Tìm kiếm điểm đồng bộ hóa
        bool is_sync_point = false;
        
        switch (current_token.type) {
            case L_TOKEN_SEMICOLON:
            case L_TOKEN_RIGHT_BRACE:
            case L_TOKEN_BEGIN:
            case L_TOKEN_END:
            case L_TOKEN_IF:
            case L_TOKEN_ELSE:
            case L_TOKEN_WHILE:
            case L_TOKEN_DO:
            case L_TOKEN_FOR:
            case L_TOKEN_INT:
            case L_TOKEN_BOOL:
                is_sync_point = true;
                break;
            default:
                break;
        }
        
        if (is_sync_point) {
            recovery_mode = false;
            // Reset yyclearin; // Không cần nếu không sử dụng lookahead
        } else {
            // Skip token nếu không phải điểm đồng bộ hóa
            return yylex(); // Đệ quy để tìm điểm đồng bộ
        }
    }
    
    // Chuyển đổi TokenType sang token Bison
    int token = tokenTypeToBison(current_token.type);
    
    // Xử lý giá trị cho các token có giá trị
    if (current_token.type == L_TOKEN_IDENTIFIER) {
        yylval.str_val = strdup(current_token.lexeme.c_str());
    } else if (current_token.type == L_TOKEN_NUMBER) {
        yylval.int_val = stoi(current_token.lexeme);
    }
    
    return token;
}

// Hàm báo lỗi cải tiến
void yyerror(const char* s) {
    error_count++;
    cerr << "Parse error: " << s << " at line " 
         << current_token.line << ", column " << current_token.column;
    
    // Cung cấp thông tin bổ sung về token hiện tại
    if (current_token.type != L_TOKEN_EOF) {
        cerr << ", unexpected token '" << current_token.lexeme << "'";
    }
    
    cerr << endl;
    
    // Chỉ đặt recovery_mode nếu chưa phục hồi
    if (!recovery_mode) {
        recovery_mode = true;
    }
}

// In cây cú pháp
void printAST(ASTNode* node, int depth) {
    if (!node) return;
    
    string indent(depth * 2, ' ');
    cout << indent << node->type;
    if (!node->value.empty()) {
        cout << " (" << node->value << ")";
    }
    cout << endl;
    
    for (auto child : node->children) {
        printAST(child, depth + 1);
    }
}
