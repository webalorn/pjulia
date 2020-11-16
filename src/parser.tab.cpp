/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON 30704

/* Bison version string.  */
#define YYBISON_VERSION "3.7.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 24 "src/parser.ypp"

	#define YYDEBUG 1

	#include <iostream>
	#include "util.hpp"
	#include "comp/ast.hpp"
	#include "parser.tab.hpp"

	extern "C" FILE *yyin;

	void yyerror(Ast* ast, const char *s);

	BinOp* newOp(const YYLTYPE loc, BinaryOperation op, AstNode* left, AstNode* right) {
		return new BinOp(loc, op, sptOf<Expr>(left), sptOf<Expr>(right));
	}
	UnaryOp* newOp(const YYLTYPE loc, UnaryOperation op, AstNode* expr) {
		return new UnaryOp(loc, op, sptOf<Expr>(expr));
	}

#line 91 "src/parser.tab.cpp"

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

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_IDENT = 5,                      /* IDENT  */
  YYSYMBOL_INT_IDENT = 6,                  /* INT_IDENT  */
  YYSYMBOL_IDENT_LEFT_PAR = 7,             /* IDENT_LEFT_PAR  */
  YYSYMBOL_INT_LEFT_PAR = 8,               /* INT_LEFT_PAR  */
  YYSYMBOL_RIGHT_PAR_IDENT = 9,            /* RIGHT_PAR_IDENT  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_ELSEIF = 11,                    /* ELSEIF  */
  YYSYMBOL_END = 12,                       /* END  */
  YYSYMBOL_FALSE = 13,                     /* FALSE  */
  YYSYMBOL_FOR = 14,                       /* FOR  */
  YYSYMBOL_FUNCTION = 15,                  /* FUNCTION  */
  YYSYMBOL_IF = 16,                        /* IF  */
  YYSYMBOL_MUTABLE = 17,                   /* MUTABLE  */
  YYSYMBOL_RETURN = 18,                    /* RETURN  */
  YYSYMBOL_STRUCT = 19,                    /* STRUCT  */
  YYSYMBOL_TRUE = 20,                      /* TRUE  */
  YYSYMBOL_WHILE = 21,                     /* WHILE  */
  YYSYMBOL_OP_EQ = 22,                     /* OP_EQ  */
  YYSYMBOL_OP_NEQ = 23,                    /* OP_NEQ  */
  YYSYMBOL_OP_LOWER_EQ = 24,               /* OP_LOWER_EQ  */
  YYSYMBOL_OP_GREATER_EQ = 25,             /* OP_GREATER_EQ  */
  YYSYMBOL_OP_AND = 26,                    /* OP_AND  */
  YYSYMBOL_OP_OR = 27,                     /* OP_OR  */
  YYSYMBOL_TYPE_SPEC = 28,                 /* TYPE_SPEC  */
  YYSYMBOL_END_FILE = 29,                  /* END_FILE  */
  YYSYMBOL_30_ = 30,                       /* '<'  */
  YYSYMBOL_31_ = 31,                       /* '>'  */
  YYSYMBOL_32_ = 32,                       /* '+'  */
  YYSYMBOL_33_ = 33,                       /* '-'  */
  YYSYMBOL_34_ = 34,                       /* '*'  */
  YYSYMBOL_35_ = 35,                       /* '%'  */
  YYSYMBOL_UANRY_MINUS = 36,               /* UANRY_MINUS  */
  YYSYMBOL_37_ = 37,                       /* '!'  */
  YYSYMBOL_38_ = 38,                       /* '.'  */
  YYSYMBOL_39_ = 39,                       /* ';'  */
  YYSYMBOL_40_ = 40,                       /* ')'  */
  YYSYMBOL_41_ = 41,                       /* '('  */
  YYSYMBOL_42_ = 42,                       /* '='  */
  YYSYMBOL_43_ = 43,                       /* ':'  */
  YYSYMBOL_44_ = 44,                       /* '^'  */
  YYSYMBOL_45_ = 45,                       /* ','  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_prog_file = 47,                 /* prog_file  */
  YYSYMBOL_prog = 48,                      /* prog  */
  YYSYMBOL_decl = 49,                      /* decl  */
  YYSYMBOL_maybeExpr = 50,                 /* maybeExpr  */
  YYSYMBOL_exprBlock = 51,                 /* exprBlock  */
  YYSYMBOL_exprBlocLeastOne = 52,          /* exprBlocLeastOne  */
  YYSYMBOL_expr = 53,                      /* expr  */
  YYSYMBOL_binOpRule = 54,                 /* binOpRule  */
  YYSYMBOL_unaryOpRule = 55,               /* unaryOpRule  */
  YYSYMBOL_lvalue = 56,                    /* lvalue  */
  YYSYMBOL_callArgListLeastOne = 57,       /* callArgListLeastOne  */
  YYSYMBOL_callArgList = 58,               /* callArgList  */
  YYSYMBOL_elseRule = 59,                  /* elseRule  */
  YYSYMBOL_typeSpec = 60,                  /* typeSpec  */
  YYSYMBOL_argRule = 61,                   /* argRule  */
  YYSYMBOL_structRule = 62,                /* structRule  */
  YYSYMBOL_structDef = 63,                 /* structDef  */
  YYSYMBOL_structArgs = 64,                /* structArgs  */
  YYSYMBOL_funcRule = 65,                  /* funcRule  */
  YYSYMBOL_funcArgs = 66,                  /* funcArgs  */
  YYSYMBOL_funcArgsLeastOne = 67           /* funcArgsLeastOne  */
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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   432

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


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
       2,     2,     2,    37,     2,     2,     2,    35,     2,     2,
      41,    40,    34,    32,    45,    33,    38,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    43,    39,
      30,    42,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    44,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    36
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   106,   106,   109,   114,   119,   120,   121,   126,   127,
     131,   132,   133,   136,   137,   141,   142,   143,   149,   150,
     151,   161,   169,   170,   176,   184,   185,   186,   187,   188,
     193,   197,   200,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   222,   223,   227,   228,
     232,   233,   236,   237,   241,   242,   243,   246,   254,   255,
     258,   263,   264,   268,   276,   277,   278,   282,   290,   300,
     301,   304,   308
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "STRING",
  "IDENT", "INT_IDENT", "IDENT_LEFT_PAR", "INT_LEFT_PAR",
  "RIGHT_PAR_IDENT", "ELSE", "ELSEIF", "END", "FALSE", "FOR", "FUNCTION",
  "IF", "MUTABLE", "RETURN", "STRUCT", "TRUE", "WHILE", "OP_EQ", "OP_NEQ",
  "OP_LOWER_EQ", "OP_GREATER_EQ", "OP_AND", "OP_OR", "TYPE_SPEC",
  "END_FILE", "'<'", "'>'", "'+'", "'-'", "'*'", "'%'", "UANRY_MINUS",
  "'!'", "'.'", "';'", "')'", "'('", "'='", "':'", "'^'", "','", "$accept",
  "prog_file", "prog", "decl", "maybeExpr", "exprBlock",
  "exprBlocLeastOne", "expr", "binOpRule", "unaryOpRule", "lvalue",
  "callArgListLeastOne", "callArgList", "elseRule", "typeSpec", "argRule",
  "structRule", "structDef", "structArgs", "funcRule", "funcArgs",
  "funcArgsLeastOne", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
      60,    62,    43,    45,    42,    37,   285,    33,    46,    59,
      41,    40,    61,    58,    94,    44
};
#endif

#define YYPACT_NINF (-122)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-48)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -122,     5,   158,  -122,  -122,  -122,  -122,  -122,   241,   241,
    -122,     7,     8,   241,     1,   241,    12,  -122,   241,  -122,
     241,   241,  -122,   241,  -122,  -122,   285,  -122,  -122,   -20,
    -122,  -122,  -122,   261,  -122,   -16,   -12,   308,   -13,    26,
     116,  -122,   354,    -1,   116,   -30,   -30,     2,    62,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,    34,  -122,   241,   241,   241,  -122,  -122,   197,   241,
      13,    -5,     3,  -122,   241,   197,    23,  -122,    -1,     6,
      32,    47,  -122,  -122,   371,   371,   371,   371,   388,   388,
     371,   371,    -8,    -8,   -30,   -30,  -122,   354,   354,  -122,
    -122,   331,    41,  -122,    26,    13,    64,  -122,   219,   241,
    -122,  -122,  -122,    -1,  -122,  -122,   241,  -122,  -122,   197,
     241,    48,   116,  -122,   116,    52,   116,  -122,    23,    54,
    -122,    23,  -122,  -122,    57,  -122
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,    16,    17,    48,    20,    52,     0,
      19,     0,     0,     0,     0,    26,     0,    18,     0,     2,
       0,     0,     8,     0,     3,     5,     0,    27,    28,    15,
       6,    62,     7,    50,    53,     0,     0,    13,     0,    69,
      10,    61,    25,    64,    10,    47,    46,     0,    13,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     9,     0,     0,     0,    24,    21,    10,     0,
      58,    72,     0,    70,     0,    10,     0,    12,    64,    67,
       0,     0,    22,    23,    40,    41,    42,    43,    44,    45,
      33,    34,    35,    36,    37,    38,    49,    39,    29,    51,
      14,     0,     0,    60,     0,    58,    36,    11,    10,     0,
      54,    32,    65,    64,    63,    31,     0,    59,    71,    10,
       0,     0,    10,    66,    10,     0,    10,    55,     0,     0,
      68,     0,    56,    30,    32,    57
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -122,  -122,  -122,  -122,  -122,   -43,     0,    -2,  -122,  -122,
    -122,     9,  -122,  -121,   -35,   -36,  -122,    59,   -76,  -122,
    -122,   -29
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    24,    25,    76,    77,    37,    27,    28,
      29,    34,    35,   111,   103,    79,    30,    31,    80,    32,
      72,    73
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      26,    81,   112,    71,    70,     3,    33,   132,    61,    36,
     134,    40,    38,    42,    63,    39,    44,    43,    45,    46,
      16,    48,    64,    47,    66,   100,    59,    60,    67,    69,
      61,    70,   107,   108,   109,   110,    63,   123,    78,    96,
     104,   102,    82,   105,   114,   113,   117,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,   115,
     127,    97,    98,    33,   130,   121,   133,   101,    71,   135,
     119,    83,   106,    41,    99,   118,   125,     0,     0,   128,
       0,   129,     0,   131,    49,    50,    51,    52,    53,    54,
       0,     0,    55,    56,    57,    58,    59,    60,   -47,   -47,
      61,    68,    61,     0,     0,     0,    63,   122,    63,     0,
       0,     0,     0,     0,   124,     0,     0,     0,   126,     4,
       5,     6,     7,     8,     9,     0,     0,     0,     0,    10,
      11,     0,    13,     0,    15,     0,    17,    18,    49,    50,
      51,    52,    53,    54,     0,     0,    55,    56,    57,    74,
      59,    60,     0,    21,    61,    75,     0,    23,     0,     0,
      63,     4,     5,     6,     7,     8,     9,     0,     0,     0,
       0,    10,    11,    12,    13,    14,    15,    16,    17,    18,
       0,     0,     0,     0,     0,     0,     0,    19,     0,     0,
       0,    20,     0,     0,     0,    21,     0,    22,     0,    23,
       4,     5,     6,     7,     8,     9,     0,     0,     0,     0,
      10,    11,     0,    13,     0,    15,     0,    17,    18,     0,
       0,     0,     4,     5,     6,     7,     8,     9,     0,     0,
      20,     0,    10,    11,    21,   120,    75,    15,    23,    17,
      18,     0,     0,     0,     4,     5,     6,     7,     8,     9,
       0,     0,    20,     0,    10,    11,    21,    13,    75,    15,
      23,    17,    18,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,     0,     0,     0,    21,     0,
       0,     0,    23,    49,    50,    51,    52,    53,    54,     0,
       0,    55,    56,    57,    58,    59,    60,     0,     0,    61,
       0,     0,     0,     0,     0,    63,    65,    49,    50,    51,
      52,    53,    54,     0,     0,    55,    56,    57,    58,    59,
      60,     0,     0,    61,    62,     0,     0,     0,     0,    63,
      49,    50,    51,    52,    53,    54,     0,     0,    55,    56,
      57,    58,    59,    60,     0,     0,    61,    68,     0,     0,
       0,     0,    63,    49,    50,    51,    52,    53,    54,     0,
       0,    55,    56,    57,    58,    59,    60,     0,     0,    61,
       0,     0,     0,     0,   116,    63,    49,    50,    51,    52,
      53,    54,     0,     0,    55,    56,    57,    58,    59,    60,
       0,     0,    61,   -48,   -48,   -48,   -48,     0,    63,     0,
       0,   -48,   -48,    57,    58,    59,    60,     0,     0,    61,
      49,    50,    51,    52,     0,    63,     0,     0,    55,    56,
      57,    58,    59,    60,     0,     0,    61,     0,     0,     0,
       0,     0,    63
};

static const yytype_int16 yycheck[] =
{
       2,    44,    78,    39,     5,     0,     8,   128,    38,     9,
     131,    13,     5,    15,    44,     7,    18,     5,    20,    21,
      19,    23,    42,    23,    40,    68,    34,    35,    40,    42,
      38,     5,    75,    10,    11,    12,    44,   113,    39,     5,
      45,    28,    40,    40,    12,    39,     5,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    12,
      12,    63,    64,    65,    12,   108,    12,    69,   104,    12,
     105,     9,    74,    14,    65,   104,   119,    -1,    -1,   122,
      -1,   124,    -1,   126,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    33,    34,    35,    34,    35,
      38,    39,    38,    -1,    -1,    -1,    44,   109,    44,    -1,
      -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,   120,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,    13,
      14,    -1,    16,    -1,    18,    -1,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    37,    38,    39,    -1,    41,    -1,    -1,
      44,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    33,    -1,    -1,    -1,    37,    -1,    39,    -1,    41,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      13,    14,    -1,    16,    -1,    18,    -1,    20,    21,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,    -1,    -1,
      33,    -1,    13,    14,    37,    16,    39,    18,    41,    20,
      21,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
      -1,    -1,    33,    -1,    13,    14,    37,    16,    39,    18,
      41,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    37,    -1,
      -1,    -1,    41,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    -1,    44,    45,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    38,    39,    -1,    -1,    -1,    -1,    44,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    38,    39,    -1,    -1,
      -1,    -1,    44,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    43,    44,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    22,    23,    24,    25,    -1,    44,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    38,
      22,    23,    24,    25,    -1,    44,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    44
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    47,    48,     0,     3,     4,     5,     6,     7,     8,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    29,
      33,    37,    39,    41,    49,    50,    53,    54,    55,    56,
      62,    63,    65,    53,    57,    58,    52,    53,     5,     7,
      53,    63,    53,     5,    53,    53,    53,    52,    53,    22,
      23,    24,    25,    26,    27,    30,    31,    32,    33,    34,
      35,    38,    39,    44,    42,    45,    40,    40,    39,    42,
       5,    61,    66,    67,    33,    39,    51,    52,    39,    61,
      64,    51,    40,     9,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,     5,    53,    53,    57,
      51,    53,    28,    60,    45,    40,    53,    51,    10,    11,
      12,    59,    64,    39,    12,    12,    43,     5,    67,    60,
      16,    51,    53,    64,    53,    51,    53,    12,    51,    51,
      12,    51,    59,    12,    59,    12
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    49,    50,    50,
      51,    51,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    55,    55,    56,    56,
      57,    57,    58,    58,    59,    59,    59,    59,    60,    60,
      61,    62,    62,    63,    64,    64,    64,    64,    65,    66,
      66,    67,    67
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     1,     1,     1,     1,     2,
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     2,     1,     1,     1,     3,
       8,     4,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     3,
       1,     3,     0,     1,     1,     3,     4,     6,     0,     2,
       2,     2,     1,     4,     0,     2,     3,     1,     7,     0,
       1,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
        yyerror (ast, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, ast); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Ast *ast)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (ast);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Ast *ast)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, ast);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, Ast *ast)
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), ast);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, ast); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, Ast *ast)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (ast);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (Ast *ast)
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
    goto yyexhaustedlab;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* prog_file: prog END_FILE  */
#line 106 "src/parser.ypp"
                         {}
#line 1393 "src/parser.tab.cpp"
    break;

  case 3: /* prog: prog decl  */
#line 109 "src/parser.ypp"
                  {
		if ((yyvsp[0].astDeclaration)) {
			ast->declarations.push_back(sptOf<Declaration>((yyvsp[0].astDeclaration)));
		}
	}
#line 1403 "src/parser.tab.cpp"
    break;

  case 4: /* prog: %empty  */
#line 114 "src/parser.ypp"
                 {}
#line 1409 "src/parser.tab.cpp"
    break;

  case 5: /* decl: maybeExpr  */
#line 119 "src/parser.ypp"
                     { (yyval.astDeclaration) = (yyvsp[0].astExpr); }
#line 1415 "src/parser.tab.cpp"
    break;

  case 6: /* decl: structRule  */
#line 120 "src/parser.ypp"
                     { (yyval.astDeclaration) = (yyvsp[0].astStructDef); }
#line 1421 "src/parser.tab.cpp"
    break;

  case 7: /* decl: funcRule  */
#line 121 "src/parser.ypp"
                     { (yyval.astDeclaration) = (yyvsp[0].astFuncDef); }
#line 1427 "src/parser.tab.cpp"
    break;

  case 8: /* maybeExpr: ';'  */
#line 126 "src/parser.ypp"
            { (yyval.astExpr) = nullptr; }
#line 1433 "src/parser.tab.cpp"
    break;

  case 9: /* maybeExpr: expr ';'  */
#line 127 "src/parser.ypp"
                   { (yyval.astExpr) = (yyvsp[-1].astExpr); }
#line 1439 "src/parser.tab.cpp"
    break;

  case 10: /* exprBlock: %empty  */
#line 131 "src/parser.ypp"
               { (yyval.astExprBlock) = new ExprBlock((yyloc)); }
#line 1445 "src/parser.tab.cpp"
    break;

  case 11: /* exprBlock: ';' exprBlock  */
#line 132 "src/parser.ypp"
                        { (yyval.astExprBlock) = (yyvsp[0].astExprBlock); (yyval.astExprBlock)->loc = (yyloc); }
#line 1451 "src/parser.tab.cpp"
    break;

  case 12: /* exprBlock: exprBlocLeastOne  */
#line 133 "src/parser.ypp"
                           { (yyval.astExprBlock) = (yyvsp[0].astExprBlock); (yyval.astExprBlock)->loc = (yyloc); }
#line 1457 "src/parser.tab.cpp"
    break;

  case 13: /* exprBlocLeastOne: expr  */
#line 136 "src/parser.ypp"
             { (yyval.astExprBlock) = new ExprBlock((yyloc)); (yyval.astExprBlock)->add((yyvsp[0].astExpr)); }
#line 1463 "src/parser.tab.cpp"
    break;

  case 14: /* exprBlocLeastOne: expr ';' exprBlock  */
#line 137 "src/parser.ypp"
                             { (yyval.astExprBlock) = (yyvsp[0].astExprBlock); (yyval.astExprBlock)->add_front((yyvsp[-2].astExpr)); (yyval.astExprBlock)->loc = (yyloc); }
#line 1469 "src/parser.tab.cpp"
    break;

  case 15: /* expr: lvalue  */
#line 141 "src/parser.ypp"
               { (yyval.astExpr) = (yyvsp[0].astLvalue); }
#line 1475 "src/parser.tab.cpp"
    break;

  case 16: /* expr: INT  */
#line 142 "src/parser.ypp"
              { (yyval.astExpr) = new IntConst((yyloc), (yyvsp[0].repr)); }
#line 1481 "src/parser.tab.cpp"
    break;

  case 17: /* expr: STRING  */
#line 143 "src/parser.ypp"
                 {
		std::string value((yyvsp[0].repr)); // Still need to remove ""
		StrConst* s = new StrConst((yyloc), std::string((yyvsp[0].repr), 1, value.size()-2));
		s->convertSpecialChars();
		(yyval.astExpr) = s;
	}
#line 1492 "src/parser.tab.cpp"
    break;

  case 18: /* expr: TRUE  */
#line 149 "src/parser.ypp"
               { (yyval.astExpr) = new BoolConst((yyloc), true); }
#line 1498 "src/parser.tab.cpp"
    break;

  case 19: /* expr: FALSE  */
#line 150 "src/parser.ypp"
                { (yyval.astExpr) = new BoolConst((yyloc), false); }
#line 1504 "src/parser.tab.cpp"
    break;

  case 20: /* expr: INT_IDENT  */
#line 151 "src/parser.ypp"
                    {
		char* splitPt = (yyvsp[0].repr);
		while ('0' <= *splitPt && *splitPt <= '9') {
			splitPt++;
		}
		(yyval.astExpr) = new BinOp((yyloc), OpTimes,
			sptOf<Expr>(new IntConst(locLeft((yyloc), splitPt-(yyvsp[0].repr)), std::string((yyvsp[0].repr), 0, splitPt-(yyvsp[0].repr)))),
			sptOf<Expr>(new Ident(locRight((yyloc), splitPt-(yyvsp[0].repr)), std::string(splitPt)))
		);
	}
#line 1519 "src/parser.tab.cpp"
    break;

  case 21: /* expr: INT_LEFT_PAR exprBlocLeastOne ')'  */
#line 161 "src/parser.ypp"
                                            {
		std::string intPart((yyvsp[-2].repr));
		intPart.pop_back(); // Remove '('
		(yyval.astExpr) = new BinOp((yyloc), OpTimes,
			sptOf<Expr>(new IntConst(locLeft((yylsp[-2]), intPart.size()), intPart)),
			sptOf<Expr>((yyvsp[-1].astExprBlock))
		);
	}
#line 1532 "src/parser.tab.cpp"
    break;

  case 22: /* expr: '(' exprBlocLeastOne ')'  */
#line 169 "src/parser.ypp"
                                   { (yyval.astExpr) = (yyvsp[-1].astExprBlock); }
#line 1538 "src/parser.tab.cpp"
    break;

  case 23: /* expr: '(' expr RIGHT_PAR_IDENT  */
#line 170 "src/parser.ypp"
                                   {
		(yyval.astExpr) = new BinOp((yyloc), OpTimes,
			sptOf<Expr>((yyvsp[-1].astExpr)),
			sptOf<Expr>(new Ident(locRight((yylsp[0]), 1), std::string((yyvsp[0].repr)+1)))
		);
	}
#line 1549 "src/parser.tab.cpp"
    break;

  case 24: /* expr: IDENT_LEFT_PAR callArgList ')'  */
#line 176 "src/parser.ypp"
                                         {
		std::string indentPart((yyvsp[-2].repr));
		indentPart.pop_back(); // Remove '('
		(yyval.astExpr) = new CallFunction((yyloc),
			sptOf<Ident>(new Ident(locLeft((yylsp[-2]), indentPart.size()), indentPart)),
			sptOf<CallParamList>((yyvsp[-1].astCallArgList))
		);
	}
#line 1562 "src/parser.tab.cpp"
    break;

  case 25: /* expr: RETURN expr  */
#line 184 "src/parser.ypp"
                      { (yyval.astExpr) = new ReturnVal((yyloc), sptOf<Expr>((yyvsp[0].astExpr))); }
#line 1568 "src/parser.tab.cpp"
    break;

  case 26: /* expr: RETURN  */
#line 185 "src/parser.ypp"
                 { (yyval.astExpr) = new ReturnVal((yyloc), nullptr); }
#line 1574 "src/parser.tab.cpp"
    break;

  case 27: /* expr: binOpRule  */
#line 186 "src/parser.ypp"
                      { (yyval.astExpr) = (yyvsp[0].astBinOp); }
#line 1580 "src/parser.tab.cpp"
    break;

  case 28: /* expr: unaryOpRule  */
#line 187 "src/parser.ypp"
                      { (yyval.astExpr) = (yyvsp[0].astUnaryOp); }
#line 1586 "src/parser.tab.cpp"
    break;

  case 29: /* expr: lvalue '=' expr  */
#line 188 "src/parser.ypp"
                          {
		(yyval.astExpr) = new Assignment((yyloc), sptOf<LValue>((yyvsp[-2].astLvalue)), sptOf<Expr>((yyvsp[0].astExpr)));
	}
#line 1594 "src/parser.tab.cpp"
    break;

  case 30: /* expr: FOR IDENT '=' expr ':' expr exprBlock END  */
#line 193 "src/parser.ypp"
                                                    {
		(yyval.astExpr) = new FlowFor((yyloc), sptOf<Ident>(new Ident((yylsp[-6]), (yyvsp[-6].repr))), sptOf<Expr>((yyvsp[-4].astExpr)),
			sptOf<Expr>((yyvsp[-2].astExpr)), sptOf<ExprBlock>((yyvsp[-1].astExprBlock)));
	}
#line 1603 "src/parser.tab.cpp"
    break;

  case 31: /* expr: WHILE expr exprBlock END  */
#line 197 "src/parser.ypp"
                                   {
		(yyval.astExpr) = new FlowWhile((yyloc), sptOf<Expr>((yyvsp[-2].astExpr)), sptOf<ExprBlock>((yyvsp[-1].astExprBlock)));
	}
#line 1611 "src/parser.tab.cpp"
    break;

  case 32: /* expr: IF expr exprBlock elseRule  */
#line 200 "src/parser.ypp"
                                     {
		(yyval.astExpr) = new FlowIfElse((yyloc), sptOf<Expr>((yyvsp[-2].astExpr)), sptOf<Expr>((yyvsp[-1].astExprBlock)), sptOf<Expr>((yyvsp[0].astExpr)));
	}
#line 1619 "src/parser.tab.cpp"
    break;

  case 33: /* binOpRule: expr '<' expr  */
#line 206 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpLower, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));   }
#line 1625 "src/parser.tab.cpp"
    break;

  case 34: /* binOpRule: expr '>' expr  */
#line 207 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpGreater, (yyvsp[-2].astExpr), (yyvsp[0].astExpr)); }
#line 1631 "src/parser.tab.cpp"
    break;

  case 35: /* binOpRule: expr '+' expr  */
#line 208 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpPlus, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));    }
#line 1637 "src/parser.tab.cpp"
    break;

  case 36: /* binOpRule: expr '-' expr  */
#line 209 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpMinus, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));   }
#line 1643 "src/parser.tab.cpp"
    break;

  case 37: /* binOpRule: expr '*' expr  */
#line 210 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpTimes, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));   }
#line 1649 "src/parser.tab.cpp"
    break;

  case 38: /* binOpRule: expr '%' expr  */
#line 211 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpMod, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));     }
#line 1655 "src/parser.tab.cpp"
    break;

  case 39: /* binOpRule: expr '^' expr  */
#line 212 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpPower, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));   }
#line 1661 "src/parser.tab.cpp"
    break;

  case 40: /* binOpRule: expr OP_EQ expr  */
#line 213 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpEq, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));      }
#line 1667 "src/parser.tab.cpp"
    break;

  case 41: /* binOpRule: expr OP_NEQ expr  */
#line 214 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpNotEq, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));   }
#line 1673 "src/parser.tab.cpp"
    break;

  case 42: /* binOpRule: expr OP_LOWER_EQ expr  */
#line 215 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpLowerEq, (yyvsp[-2].astExpr), (yyvsp[0].astExpr)); }
#line 1679 "src/parser.tab.cpp"
    break;

  case 43: /* binOpRule: expr OP_GREATER_EQ expr  */
#line 216 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpGreater, (yyvsp[-2].astExpr), (yyvsp[0].astExpr)); }
#line 1685 "src/parser.tab.cpp"
    break;

  case 44: /* binOpRule: expr OP_AND expr  */
#line 217 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpAnd, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));     }
#line 1691 "src/parser.tab.cpp"
    break;

  case 45: /* binOpRule: expr OP_OR expr  */
#line 218 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpAnd, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));     }
#line 1697 "src/parser.tab.cpp"
    break;

  case 46: /* unaryOpRule: '!' expr  */
#line 222 "src/parser.ypp"
                   { (yyval.astUnaryOp) = newOp((yyloc), UnaryNot, (yyvsp[0].astExpr));   }
#line 1703 "src/parser.tab.cpp"
    break;

  case 47: /* unaryOpRule: '-' expr  */
#line 223 "src/parser.ypp"
                   { (yyval.astUnaryOp) = newOp((yyloc), UnaryMinus, (yyvsp[0].astExpr)); }
#line 1709 "src/parser.tab.cpp"
    break;

  case 48: /* lvalue: IDENT  */
#line 227 "src/parser.ypp"
              { (yyval.astLvalue) = new Ident((yylsp[0]), (yyvsp[0].repr)); }
#line 1715 "src/parser.tab.cpp"
    break;

  case 49: /* lvalue: expr '.' IDENT  */
#line 228 "src/parser.ypp"
                         { (yyval.astLvalue) = new DotOp((yyloc), sptOf<Expr>((yyvsp[-2].astExpr)), sptOf<Ident>(new Ident((yylsp[0]), (yyvsp[0].repr)))); }
#line 1721 "src/parser.tab.cpp"
    break;

  case 50: /* callArgListLeastOne: expr  */
#line 232 "src/parser.ypp"
             { (yyval.astCallArgList) = new CallParamList((yyloc)); (yyval.astCallArgList)->add((yyvsp[0].astExpr)); }
#line 1727 "src/parser.tab.cpp"
    break;

  case 51: /* callArgListLeastOne: expr ',' callArgListLeastOne  */
#line 233 "src/parser.ypp"
                                       { (yyval.astCallArgList) = (yyvsp[0].astCallArgList); (yyval.astCallArgList)->add_front((yyvsp[-2].astExpr)); }
#line 1733 "src/parser.tab.cpp"
    break;

  case 52: /* callArgList: %empty  */
#line 236 "src/parser.ypp"
               { (yyval.astCallArgList) = new CallParamList((yyloc)); }
#line 1739 "src/parser.tab.cpp"
    break;

  case 53: /* callArgList: callArgListLeastOne  */
#line 237 "src/parser.ypp"
                              { (yyval.astCallArgList) = (yyvsp[0].astCallArgList); }
#line 1745 "src/parser.tab.cpp"
    break;

  case 54: /* elseRule: END  */
#line 241 "src/parser.ypp"
                              { (yyval.astExpr) = new ExprBlock((yyloc)); }
#line 1751 "src/parser.tab.cpp"
    break;

  case 55: /* elseRule: ELSE exprBlock END  */
#line 242 "src/parser.ypp"
                              { (yyval.astExpr) = (yyvsp[-1].astExprBlock); }
#line 1757 "src/parser.tab.cpp"
    break;

  case 56: /* elseRule: ELSEIF expr exprBlock elseRule  */
#line 243 "src/parser.ypp"
                                         {
		(yyval.astExpr) = new FlowIfElse((yyloc), sptOf<Expr>((yyvsp[-2].astExpr)), sptOf<Expr>((yyvsp[-1].astExprBlock)), sptOf<Expr>((yyvsp[0].astExpr)));
	}
#line 1765 "src/parser.tab.cpp"
    break;

  case 57: /* elseRule: ELSE IF expr exprBlock elseRule END  */
#line 246 "src/parser.ypp"
                                              {
		throw ParseError((yylsp[-5]), "syntax: use \"elseif\" instead of \"else if\"");
	}
#line 1773 "src/parser.tab.cpp"
    break;

  case 58: /* typeSpec: %empty  */
#line 254 "src/parser.ypp"
                          { (yyval.astIdent) = new Ident((yyloc), "Any"); }
#line 1779 "src/parser.tab.cpp"
    break;

  case 59: /* typeSpec: TYPE_SPEC IDENT  */
#line 255 "src/parser.ypp"
                          { (yyval.astIdent) = new Ident((yylsp[0]), (yyvsp[0].repr));    }
#line 1785 "src/parser.tab.cpp"
    break;

  case 60: /* argRule: IDENT typeSpec  */
#line 258 "src/parser.ypp"
                       { (yyval.astArgument) = new Argument((yyloc), sptOf<Ident>(new Ident((yylsp[-1]), (yyvsp[-1].repr))), sptOf<Ident>((yyvsp[0].astIdent))); }
#line 1791 "src/parser.tab.cpp"
    break;

  case 61: /* structRule: MUTABLE structDef  */
#line 263 "src/parser.ypp"
                          { (yyval.astStructDef) = (yyvsp[0].astStructDef); (yyval.astStructDef)->isMutable = true; }
#line 1797 "src/parser.tab.cpp"
    break;

  case 62: /* structRule: structDef  */
#line 264 "src/parser.ypp"
                          { (yyval.astStructDef) = (yyvsp[0].astStructDef); }
#line 1803 "src/parser.tab.cpp"
    break;

  case 63: /* structDef: STRUCT IDENT structArgs END  */
#line 268 "src/parser.ypp"
                                    {
		(yyval.astStructDef) = new DefStruct((yyloc), false, sptOf<Ident>(new Ident((yylsp[-2]), (yyvsp[-2].repr))));
		(yyval.astStructDef)->members = *((yyvsp[-1].astArgList));
		free((yyvsp[-1].astArgList));
	}
#line 1813 "src/parser.tab.cpp"
    break;

  case 64: /* structArgs: %empty  */
#line 276 "src/parser.ypp"
               { (yyval.astArgList) = new ArgumentList(); }
#line 1819 "src/parser.tab.cpp"
    break;

  case 65: /* structArgs: ';' structArgs  */
#line 277 "src/parser.ypp"
                         { (yyval.astArgList) = (yyvsp[0].astArgList); }
#line 1825 "src/parser.tab.cpp"
    break;

  case 66: /* structArgs: argRule ';' structArgs  */
#line 278 "src/parser.ypp"
                                 {
		(yyval.astArgList) = (yyvsp[0].astArgList);
		(yyval.astArgList)->push_front(sptOf<Argument>((yyvsp[-2].astArgument)));
	}
#line 1834 "src/parser.tab.cpp"
    break;

  case 67: /* structArgs: argRule  */
#line 282 "src/parser.ypp"
                  {
		(yyval.astArgList) = new ArgumentList();;
		(yyval.astArgList)->push_front(sptOf<Argument>((yyvsp[0].astArgument)));
	}
#line 1843 "src/parser.tab.cpp"
    break;

  case 68: /* funcRule: FUNCTION IDENT_LEFT_PAR funcArgs ')' typeSpec exprBlock END  */
#line 290 "src/parser.ypp"
                                                                    {
		std::string name((yyvsp[-5].repr));
		name.pop_back();
		(yyval.astFuncDef) = new DefFunc((yyloc), sptOf<Ident>(new Ident(locLeft((yylsp[-5]), name.size()), name)),
			sptOf<Ident>((yyvsp[-2].astIdent)), spt<ExprBlock>((yyvsp[-1].astExprBlock)));
		(yyval.astFuncDef)->args = *((yyvsp[-4].astArgList));
		free((yyvsp[-4].astArgList));
	}
#line 1856 "src/parser.tab.cpp"
    break;

  case 69: /* funcArgs: %empty  */
#line 300 "src/parser.ypp"
               { (yyval.astArgList) = new ArgumentList(); }
#line 1862 "src/parser.tab.cpp"
    break;

  case 70: /* funcArgs: funcArgsLeastOne  */
#line 301 "src/parser.ypp"
                           { (yyval.astArgList) = (yyvsp[0].astArgList); }
#line 1868 "src/parser.tab.cpp"
    break;

  case 71: /* funcArgsLeastOne: argRule ',' funcArgsLeastOne  */
#line 304 "src/parser.ypp"
                                     {
		(yyval.astArgList) = (yyvsp[0].astArgList);
		(yyval.astArgList)->push_front(sptOf<Argument>((yyvsp[-2].astArgument)));
	}
#line 1877 "src/parser.tab.cpp"
    break;

  case 72: /* funcArgsLeastOne: argRule  */
#line 308 "src/parser.ypp"
                  {
		(yyval.astArgList) = new ArgumentList();;
		(yyval.astArgList)->push_front(sptOf<Argument>((yyvsp[0].astArgument)));
	}
#line 1886 "src/parser.tab.cpp"
    break;


#line 1890 "src/parser.tab.cpp"

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
  *++yylsp = yyloc;

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
      yyerror (ast, YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc, ast);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, ast);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (ast, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, ast);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, ast);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 314 "src/parser.ypp"


void yyerror(Ast*, const char *s) {
	throw ParseError(yylloc, "[bison error] " + std::string(s));
}
