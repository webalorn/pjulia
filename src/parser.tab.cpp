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

	BinOp* newOp(const YYLTYPE loc, BinaryOperation op, Expr* left, Expr* right) {
		return new BinOp(loc, op, sptOf(left), sptOf(right));
	}
	UnaryOp* newOp(const YYLTYPE loc, UnaryOperation op, Expr* expr) {
		return new UnaryOp(loc, op, sptOf(expr));
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
  YYSYMBOL_WITHOUT_OPTIO = 30,             /* WITHOUT_OPTIO  */
  YYSYMBOL_REDUCE_BLOCK_RULE = 31,         /* REDUCE_BLOCK_RULE  */
  YYSYMBOL_FLOW_RULE = 32,                 /* FLOW_RULE  */
  YYSYMBOL_RETURN_RULE = 33,               /* RETURN_RULE  */
  YYSYMBOL_EMPTY = 34,                     /* EMPTY  */
  YYSYMBOL_35_ = 35,                       /* '='  */
  YYSYMBOL_36_ = 36,                       /* '<'  */
  YYSYMBOL_37_ = 37,                       /* '>'  */
  YYSYMBOL_UANRY_MINUS = 38,               /* UANRY_MINUS  */
  YYSYMBOL_39_ = 39,                       /* '+'  */
  YYSYMBOL_40_ = 40,                       /* '-'  */
  YYSYMBOL_41_ = 41,                       /* '!'  */
  YYSYMBOL_42_ = 42,                       /* '*'  */
  YYSYMBOL_43_ = 43,                       /* '%'  */
  YYSYMBOL_44_ = 44,                       /* '^'  */
  YYSYMBOL_45_ = 45,                       /* '.'  */
  YYSYMBOL_46_ = 46,                       /* ';'  */
  YYSYMBOL_47_ = 47,                       /* ')'  */
  YYSYMBOL_48_ = 48,                       /* '('  */
  YYSYMBOL_49_ = 49,                       /* ':'  */
  YYSYMBOL_50_ = 50,                       /* ','  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_prog_file = 52,                 /* prog_file  */
  YYSYMBOL_prog = 53,                      /* prog  */
  YYSYMBOL_decl = 54,                      /* decl  */
  YYSYMBOL_maybeExpr = 55,                 /* maybeExpr  */
  YYSYMBOL_exprBlock = 56,                 /* exprBlock  */
  YYSYMBOL_exprBlocLeastOne = 57,          /* exprBlocLeastOne  */
  YYSYMBOL_expr = 58,                      /* expr  */
  YYSYMBOL_binOpRule = 59,                 /* binOpRule  */
  YYSYMBOL_unaryOpRule = 60,               /* unaryOpRule  */
  YYSYMBOL_lvalue = 61,                    /* lvalue  */
  YYSYMBOL_callArgListLeastOne = 62,       /* callArgListLeastOne  */
  YYSYMBOL_callArgList = 63,               /* callArgList  */
  YYSYMBOL_elseRule = 64,                  /* elseRule  */
  YYSYMBOL_typeSpec = 65,                  /* typeSpec  */
  YYSYMBOL_argRule = 66,                   /* argRule  */
  YYSYMBOL_structRule = 67,                /* structRule  */
  YYSYMBOL_structDef = 68,                 /* structDef  */
  YYSYMBOL_structArgs = 69,                /* structArgs  */
  YYSYMBOL_funcRule = 70,                  /* funcRule  */
  YYSYMBOL_funcArgs = 71,                  /* funcArgs  */
  YYSYMBOL_funcArgsLeastOne = 72           /* funcArgsLeastOne  */
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

#if 1

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
#endif /* 1 */

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
#define YYLAST   451

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


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
       2,     2,     2,    41,     2,     2,     2,    43,     2,     2,
      48,    47,    42,    39,    50,    40,    45,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    49,    46,
      36,    35,    37,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   119,   119,   122,   127,   132,   133,   134,   139,   140,
     144,   145,   146,   149,   150,   154,   155,   156,   163,   164,
     165,   176,   185,   186,   193,   202,   203,   204,   205,   209,
     219,   224,   227,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   249,   250,   254,   255,
     262,   263,   266,   267,   271,   272,   273,   276,   282,   283,
     286,   294,   295,   299,   307,   308,   309,   313,   321,   331,
     332,   335,   339
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "INT", "STRING", "IDENT",
  "INT_IDENT", "IDENT_LEFT_PAR", "INT_LEFT_PAR", "RIGHT_PAR_IDENT", "ELSE",
  "ELSEIF", "END", "FALSE", "FOR", "FUNCTION", "IF", "MUTABLE", "RETURN",
  "STRUCT", "TRUE", "WHILE", "OP_EQ", "OP_NEQ", "OP_LOWER_EQ",
  "OP_GREATER_EQ", "OP_AND", "OP_OR", "TYPE_SPEC", "END_FILE",
  "WITHOUT_OPTIO", "REDUCE_BLOCK_RULE", "FLOW_RULE", "RETURN_RULE",
  "EMPTY", "'='", "'<'", "'>'", "UANRY_MINUS", "'+'", "'-'", "'!'", "'*'",
  "'%'", "'^'", "'.'", "';'", "')'", "'('", "':'", "','", "$accept",
  "prog_file", "prog", "decl", "maybeExpr", "exprBlock",
  "exprBlocLeastOne", "expr", "binOpRule", "unaryOpRule", "lvalue",
  "callArgListLeastOne", "callArgList", "elseRule", "typeSpec", "argRule",
  "structRule", "structDef", "structArgs", "funcRule", "funcArgs",
  "funcArgsLeastOne", YY_NULLPTR
  };
  return yy_sname[yysymbol];
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
     285,   286,   287,   288,   289,    61,    60,    62,   290,    43,
      45,    33,    42,    37,    94,    46,    59,    41,    40,    58,
      44
};
#endif

#define YYPACT_NINF (-122)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -122,     5,   162,  -122,  -122,  -122,  -122,  -122,   220,   220,
    -122,     4,    10,   220,    -7,   220,    15,  -122,   220,  -122,
     220,   220,  -122,   220,  -122,  -122,   322,  -122,  -122,  -122,
    -122,  -122,  -122,   265,  -122,   -17,   -10,   347,    -4,    33,
     116,  -122,   372,    -3,   116,   -16,    -9,    14,   240,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,   220,
     220,   220,   220,    39,  -122,   220,  -122,  -122,    85,   220,
      17,    12,    19,  -122,   220,    85,    30,  -122,    -3,     0,
      52,    57,  -122,  -122,   396,   396,   396,   396,   406,   406,
     372,   396,   396,    -9,    -9,   -30,   -30,    25,  -122,  -122,
    -122,   294,    66,  -122,    33,    17,    -9,  -122,   191,   220,
    -122,  -122,  -122,    -3,  -122,  -122,   220,  -122,  -122,    85,
     220,    61,   116,  -122,   116,    62,   116,  -122,    30,    63,
    -122,    30,  -122,  -122,    65,  -122
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
       0,     0,     0,     0,     9,     0,    24,    21,    10,     0,
      58,    72,     0,    70,     0,    10,     0,    12,    64,    67,
       0,     0,    22,    23,    40,    41,    42,    43,    44,    45,
      29,    33,    34,    35,    36,    37,    38,    39,    49,    51,
      14,     0,     0,    60,     0,    58,    36,    11,    10,     0,
      54,    32,    65,    64,    63,    31,     0,    59,    71,    10,
       0,     0,    10,    66,    10,     0,    10,    55,     0,     0,
      68,     0,    56,    30,    32,    57
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -122,  -122,  -122,  -122,  -122,   -43,    -1,    -2,  -122,  -122,
    -122,    13,  -122,  -121,   -25,   -36,  -122,    68,   -74,  -122,
    -122,   -20
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
      26,    81,    70,    71,   112,     3,    33,   132,    36,    38,
     134,    40,    16,    42,    62,    63,    44,    39,    45,    46,
      43,    48,    47,    58,    59,   100,    60,    61,    62,    63,
      66,    69,   107,    60,    61,    62,    63,    67,    70,   123,
     108,   109,   110,    78,    98,   102,   113,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    82,   104,    33,   114,   121,   105,   101,    71,   115,
      63,   117,   106,   127,   130,   133,   125,   135,    99,   128,
     119,   129,    41,   131,   118,     0,     0,     0,     4,     5,
       6,     7,     8,     9,     0,     0,     0,     0,    10,    11,
       0,    13,     0,    15,     0,    17,    18,   122,     0,     0,
       0,     0,     0,     0,   124,     0,     0,     0,   126,     4,
       5,     6,     7,     8,     9,    20,    21,     0,     0,    10,
      11,    75,    13,    23,    15,     0,    17,    18,    49,    50,
      51,    52,    53,    54,     0,     0,     0,     0,     0,     0,
       0,    55,    56,    57,     0,    58,    74,    21,    60,    61,
      62,    63,    75,     0,    23,     4,     5,     6,     7,     8,
       9,     0,     0,     0,     0,    10,    11,    12,    13,    14,
      15,    16,    17,    18,     0,     0,     0,     0,     0,     0,
       0,    19,     0,     0,     4,     5,     6,     7,     8,     9,
       0,     0,    20,    21,    10,    11,     0,   120,    22,    15,
      23,    17,    18,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     4,     5,     6,     7,     8,     9,     0,
       0,    20,    21,    10,    11,     0,    13,    75,    15,    23,
      17,    18,     0,     0,     0,     0,     0,     0,     0,    83,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      20,    21,    49,    50,    51,    52,    53,    54,    23,     0,
       0,     0,     0,     0,     0,    55,    56,    57,     0,    58,
      59,     0,    60,    61,    62,    63,    68,    49,    50,    51,
      52,    53,    54,     0,     0,     0,     0,     0,     0,     0,
      55,    56,    57,     0,    58,    59,     0,    60,    61,    62,
      63,     0,     0,     0,     0,    65,    49,    50,    51,    52,
      53,    54,     0,     0,     0,     0,     0,     0,     0,    55,
      56,    57,     0,    58,    59,     0,    60,    61,    62,    63,
       0,     0,     0,   116,    49,    50,    51,    52,    53,    54,
       0,     0,     0,     0,     0,     0,     0,    55,    56,    57,
       0,    58,    59,     0,    60,    61,    62,    63,    64,    49,
      50,    51,    52,    53,    54,     0,     0,     0,     0,     0,
       0,     0,    55,    56,    57,     0,    58,    59,     0,    60,
      61,    62,    63,    68,    49,    50,    51,    52,    53,    54,
       0,     0,     0,     0,     0,     0,     0,    55,    56,    57,
       0,    58,    59,     0,    60,    61,    62,    63,    -1,    -1,
      -1,    -1,     0,     0,     0,     0,     0,     0,    49,    50,
      51,    52,    -1,    -1,     0,    58,    59,     0,    60,    61,
      62,    63,    56,    57,     0,    58,    59,     0,    60,    61,
      62,    63
};

static const yytype_int16 yycheck[] =
{
       2,    44,     5,    39,    78,     0,     8,   128,     9,     5,
     131,    13,    19,    15,    44,    45,    18,     7,    20,    21,
       5,    23,    23,    39,    40,    68,    42,    43,    44,    45,
      47,    35,    75,    42,    43,    44,    45,    47,     5,   113,
      10,    11,    12,    46,     5,    28,    46,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    47,    50,    65,    12,   108,    47,    69,   104,    12,
      45,     5,    74,    12,    12,    12,   119,    12,    65,   122,
     105,   124,    14,   126,   104,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    13,    14,
      -1,    16,    -1,    18,    -1,    20,    21,   109,    -1,    -1,
      -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,   120,     3,
       4,     5,     6,     7,     8,    40,    41,    -1,    -1,    13,
      14,    46,    16,    48,    18,    -1,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    -1,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    48,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    -1,    -1,     3,     4,     5,     6,     7,     8,
      -1,    -1,    40,    41,    13,    14,    -1,    16,    46,    18,
      48,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,    -1,
      -1,    40,    41,    13,    14,    -1,    16,    46,    18,    48,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    41,    22,    23,    24,    25,    26,    27,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    -1,    39,
      40,    -1,    42,    43,    44,    45,    46,    22,    23,    24,
      25,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,    -1,    39,    40,    -1,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    50,    22,    23,    24,    25,
      26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    -1,    39,    40,    -1,    42,    43,    44,    45,
      -1,    -1,    -1,    49,    22,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,
      -1,    39,    40,    -1,    42,    43,    44,    45,    46,    22,
      23,    24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    -1,    39,    40,    -1,    42,
      43,    44,    45,    46,    22,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,
      -1,    39,    40,    -1,    42,    43,    44,    45,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    36,    37,    -1,    39,    40,    -1,    42,    43,
      44,    45,    36,    37,    -1,    39,    40,    -1,    42,    43,
      44,    45
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    52,    53,     0,     3,     4,     5,     6,     7,     8,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    29,
      40,    41,    46,    48,    54,    55,    58,    59,    60,    61,
      67,    68,    70,    58,    62,    63,    57,    58,     5,     7,
      58,    68,    58,     5,    58,    58,    58,    57,    58,    22,
      23,    24,    25,    26,    27,    35,    36,    37,    39,    40,
      42,    43,    44,    45,    46,    50,    47,    47,    46,    35,
       5,    66,    71,    72,    40,    46,    56,    57,    46,    66,
      69,    56,    47,     9,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,     5,    62,
      56,    58,    28,    65,    50,    47,    58,    56,    10,    11,
      12,    64,    69,    46,    12,    12,    49,     5,    72,    65,
      16,    56,    58,    69,    58,    56,    58,    12,    56,    56,
      12,    56,    64,    12,    64,    12
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    54,    55,    55,
      56,    56,    56,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    60,    60,    61,    61,
      62,    62,    63,    63,    64,    64,    64,    64,    65,    65,
      66,    67,    67,    68,    69,    69,    69,    69,    70,    71,
      71,    72,    72
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif



static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yystrlen (yysymbol_name (yyarg[yyi]));
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
#line 119 "src/parser.ypp"
                         {}
#line 1624 "src/parser.tab.cpp"
    break;

  case 3: /* prog: prog decl  */
#line 122 "src/parser.ypp"
                  {
		if ((yyvsp[0].astDeclaration)) {
			ast->addDeclaration(sptOf((yyvsp[0].astDeclaration)));
		}
	}
#line 1634 "src/parser.tab.cpp"
    break;

  case 4: /* prog: %empty  */
#line 127 "src/parser.ypp"
                             {}
#line 1640 "src/parser.tab.cpp"
    break;

  case 5: /* decl: maybeExpr  */
#line 132 "src/parser.ypp"
                     { (yyval.astDeclaration) = (yyvsp[0].astExpr); }
#line 1646 "src/parser.tab.cpp"
    break;

  case 6: /* decl: structRule  */
#line 133 "src/parser.ypp"
                     { (yyval.astDeclaration) = (yyvsp[0].astStructDef); }
#line 1652 "src/parser.tab.cpp"
    break;

  case 7: /* decl: funcRule  */
#line 134 "src/parser.ypp"
                     { (yyval.astDeclaration) = (yyvsp[0].astFuncDef); }
#line 1658 "src/parser.tab.cpp"
    break;

  case 8: /* maybeExpr: ';'  */
#line 139 "src/parser.ypp"
            { (yyval.astExpr) = nullptr; }
#line 1664 "src/parser.tab.cpp"
    break;

  case 9: /* maybeExpr: expr ';'  */
#line 140 "src/parser.ypp"
                   { (yyval.astExpr) = (yyvsp[-1].astExpr); }
#line 1670 "src/parser.tab.cpp"
    break;

  case 10: /* exprBlock: %empty  */
#line 144 "src/parser.ypp"
                                                   { (yyval.astExprBlock) = new ExprBlock((yyloc)); }
#line 1676 "src/parser.tab.cpp"
    break;

  case 11: /* exprBlock: ';' exprBlock  */
#line 145 "src/parser.ypp"
                                                   { (yyval.astExprBlock) = (yyvsp[0].astExprBlock); (yyval.astExprBlock)->loc = (yyloc); }
#line 1682 "src/parser.tab.cpp"
    break;

  case 12: /* exprBlock: exprBlocLeastOne  */
#line 146 "src/parser.ypp"
                                                   { (yyval.astExprBlock) = (yyvsp[0].astExprBlock); (yyval.astExprBlock)->loc = (yyloc); }
#line 1688 "src/parser.tab.cpp"
    break;

  case 13: /* exprBlocLeastOne: expr  */
#line 149 "src/parser.ypp"
                                     { (yyval.astExprBlock) = new ExprBlock((yyloc)); (yyval.astExprBlock)->add((yyvsp[0].astExpr)); }
#line 1694 "src/parser.tab.cpp"
    break;

  case 14: /* exprBlocLeastOne: expr ';' exprBlock  */
#line 150 "src/parser.ypp"
                                                      { (yyval.astExprBlock) = (yyvsp[0].astExprBlock); (yyval.astExprBlock)->add_front((yyvsp[-2].astExpr)); (yyval.astExprBlock)->loc = (yyloc); }
#line 1700 "src/parser.tab.cpp"
    break;

  case 15: /* expr: lvalue  */
#line 154 "src/parser.ypp"
               { (yyval.astExpr) = (yyvsp[0].astLvalue); }
#line 1706 "src/parser.tab.cpp"
    break;

  case 16: /* expr: INT  */
#line 155 "src/parser.ypp"
              { (yyval.astExpr) = new IntConst((yyloc), (yyvsp[0].repr)); free((yyvsp[0].repr)); }
#line 1712 "src/parser.tab.cpp"
    break;

  case 17: /* expr: STRING  */
#line 156 "src/parser.ypp"
                 {
		std::string value((yyvsp[0].repr)); // Still need to remove ""
		StrConst* s = new StrConst((yyloc), std::string((yyvsp[0].repr), 1, value.size()-2));
		s->convertSpecialChars();
		(yyval.astExpr) = s;
		free((yyvsp[0].repr));
	}
#line 1724 "src/parser.tab.cpp"
    break;

  case 18: /* expr: TRUE  */
#line 163 "src/parser.ypp"
               { (yyval.astExpr) = new BoolConst((yyloc), true); }
#line 1730 "src/parser.tab.cpp"
    break;

  case 19: /* expr: FALSE  */
#line 164 "src/parser.ypp"
                { (yyval.astExpr) = new BoolConst((yyloc), false); }
#line 1736 "src/parser.tab.cpp"
    break;

  case 20: /* expr: INT_IDENT  */
#line 165 "src/parser.ypp"
                    {
		char* splitPt = (yyvsp[0].repr);
		while ('0' <= *splitPt && *splitPt <= '9') {
			splitPt++;
		}
		(yyval.astExpr) = new BinOp((yyloc), OpTimes,
			sptOf(new IntConst(locLeft((yyloc), splitPt-(yyvsp[0].repr)), std::string((yyvsp[0].repr), 0, splitPt-(yyvsp[0].repr)))),
			sptOf(new Ident(locRight((yyloc), splitPt-(yyvsp[0].repr)), std::string(splitPt)))
		);
		free((yyvsp[0].repr));
	}
#line 1752 "src/parser.tab.cpp"
    break;

  case 21: /* expr: INT_LEFT_PAR exprBlocLeastOne ')'  */
#line 176 "src/parser.ypp"
                                            {
		std::string intPart((yyvsp[-2].repr));
		intPart.pop_back(); // Remove '('
		(yyval.astExpr) = new BinOp((yyloc), OpTimes,
			sptOf(new IntConst(locLeft((yylsp[-2]), intPart.size()), intPart)),
			sptOf((yyvsp[-1].astExprBlock))
		);
		free((yyvsp[-2].repr));
	}
#line 1766 "src/parser.tab.cpp"
    break;

  case 22: /* expr: '(' exprBlocLeastOne ')'  */
#line 185 "src/parser.ypp"
                                   { (yyval.astExpr) = (yyvsp[-1].astExprBlock); }
#line 1772 "src/parser.tab.cpp"
    break;

  case 23: /* expr: '(' expr RIGHT_PAR_IDENT  */
#line 186 "src/parser.ypp"
                                   {
		(yyval.astExpr) = new BinOp((yyloc), OpTimes,
			sptOf((yyvsp[-1].astExpr)),
			sptOf(new Ident(locRight((yylsp[0]), 1), std::string((yyvsp[0].repr)+1)))
		);
		free((yyvsp[0].repr));
	}
#line 1784 "src/parser.tab.cpp"
    break;

  case 24: /* expr: IDENT_LEFT_PAR callArgList ')'  */
#line 193 "src/parser.ypp"
                                         {
		std::string indentPart((yyvsp[-2].repr));
		indentPart.pop_back(); // Remove '('
		(yyval.astExpr) = new CallFunction((yyloc),
			sptOf(new Ident(locLeft((yylsp[-2]), indentPart.size()), indentPart)),
			sptOf((yyvsp[-1].astCallArgList))
		);
		free((yyvsp[-2].repr));
	}
#line 1798 "src/parser.tab.cpp"
    break;

  case 25: /* expr: RETURN expr  */
#line 202 "src/parser.ypp"
                                        { (yyval.astExpr) = new ReturnVal((yyloc), sptOf((yyvsp[0].astExpr))); }
#line 1804 "src/parser.tab.cpp"
    break;

  case 26: /* expr: RETURN  */
#line 203 "src/parser.ypp"
                                     { (yyval.astExpr) = new ReturnVal((yyloc), nullptr); }
#line 1810 "src/parser.tab.cpp"
    break;

  case 27: /* expr: binOpRule  */
#line 204 "src/parser.ypp"
                      { (yyval.astExpr) = (yyvsp[0].astBinOp); }
#line 1816 "src/parser.tab.cpp"
    break;

  case 28: /* expr: unaryOpRule  */
#line 205 "src/parser.ypp"
                      { (yyval.astExpr) = (yyvsp[0].astUnaryOp); }
#line 1822 "src/parser.tab.cpp"
    break;

  case 29: /* expr: expr '=' expr  */
#line 209 "src/parser.ypp"
                        { // Workaround because bison does strange things with %prec
		LValue* lval = dynamic_cast<LValue*>((yyvsp[-2].astExpr));
		if (lval == nullptr) {
			throw ParseError((yylsp[-1]), "Can't assign to an expression");
		} else {
			(yyval.astExpr) = new Assignment((yyloc), sptOf(lval), sptOf((yyvsp[0].astExpr)));
		}
	}
#line 1835 "src/parser.tab.cpp"
    break;

  case 30: /* expr: FOR IDENT '=' expr ':' expr exprBlock END  */
#line 219 "src/parser.ypp"
                                                                    {
		(yyval.astExpr) = new FlowFor((yyloc), sptOf(new Ident((yylsp[-6]), (yyvsp[-6].repr))), sptOf((yyvsp[-4].astExpr)),
			sptOf((yyvsp[-2].astExpr)), sptOf((yyvsp[-1].astExprBlock)));
		free((yyvsp[-6].repr));
	}
#line 1845 "src/parser.tab.cpp"
    break;

  case 31: /* expr: WHILE expr exprBlock END  */
#line 224 "src/parser.ypp"
                                                   {
		(yyval.astExpr) = new FlowWhile((yyloc), sptOf((yyvsp[-2].astExpr)), sptOf((yyvsp[-1].astExprBlock)));
	}
#line 1853 "src/parser.tab.cpp"
    break;

  case 32: /* expr: IF expr exprBlock elseRule  */
#line 227 "src/parser.ypp"
                                                     {
		(yyval.astExpr) = new FlowIfElse((yyloc), sptOf((yyvsp[-2].astExpr)), sptOf((yyvsp[-1].astExprBlock)), sptOf((yyvsp[0].astExpr)));
	}
#line 1861 "src/parser.tab.cpp"
    break;

  case 33: /* binOpRule: expr '<' expr  */
#line 233 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpLower, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));   }
#line 1867 "src/parser.tab.cpp"
    break;

  case 34: /* binOpRule: expr '>' expr  */
#line 234 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpGreater, (yyvsp[-2].astExpr), (yyvsp[0].astExpr)); }
#line 1873 "src/parser.tab.cpp"
    break;

  case 35: /* binOpRule: expr '+' expr  */
#line 235 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpPlus, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));    }
#line 1879 "src/parser.tab.cpp"
    break;

  case 36: /* binOpRule: expr '-' expr  */
#line 236 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpMinus, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));   }
#line 1885 "src/parser.tab.cpp"
    break;

  case 37: /* binOpRule: expr '*' expr  */
#line 237 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpTimes, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));   }
#line 1891 "src/parser.tab.cpp"
    break;

  case 38: /* binOpRule: expr '%' expr  */
#line 238 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpMod, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));     }
#line 1897 "src/parser.tab.cpp"
    break;

  case 39: /* binOpRule: expr '^' expr  */
#line 239 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpPower, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));   }
#line 1903 "src/parser.tab.cpp"
    break;

  case 40: /* binOpRule: expr OP_EQ expr  */
#line 240 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpEq, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));      }
#line 1909 "src/parser.tab.cpp"
    break;

  case 41: /* binOpRule: expr OP_NEQ expr  */
#line 241 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpNotEq, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));   }
#line 1915 "src/parser.tab.cpp"
    break;

  case 42: /* binOpRule: expr OP_LOWER_EQ expr  */
#line 242 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpLowerEq, (yyvsp[-2].astExpr), (yyvsp[0].astExpr)); }
#line 1921 "src/parser.tab.cpp"
    break;

  case 43: /* binOpRule: expr OP_GREATER_EQ expr  */
#line 243 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpGreater, (yyvsp[-2].astExpr), (yyvsp[0].astExpr)); }
#line 1927 "src/parser.tab.cpp"
    break;

  case 44: /* binOpRule: expr OP_AND expr  */
#line 244 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpAnd, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));     }
#line 1933 "src/parser.tab.cpp"
    break;

  case 45: /* binOpRule: expr OP_OR expr  */
#line 245 "src/parser.ypp"
                                   { (yyval.astBinOp) = newOp((yyloc), OpAnd, (yyvsp[-2].astExpr), (yyvsp[0].astExpr));     }
#line 1939 "src/parser.tab.cpp"
    break;

  case 46: /* unaryOpRule: '!' expr  */
#line 249 "src/parser.ypp"
                   { (yyval.astUnaryOp) = newOp((yyloc), UnaryNot, (yyvsp[0].astExpr));   }
#line 1945 "src/parser.tab.cpp"
    break;

  case 47: /* unaryOpRule: '-' expr  */
#line 250 "src/parser.ypp"
                                     { (yyval.astUnaryOp) = newOp((yyloc), UnaryMinus, (yyvsp[0].astExpr)); }
#line 1951 "src/parser.tab.cpp"
    break;

  case 48: /* lvalue: IDENT  */
#line 254 "src/parser.ypp"
              { (yyval.astLvalue) = new Ident((yylsp[0]), (yyvsp[0].repr)); free((yyvsp[0].repr)); }
#line 1957 "src/parser.tab.cpp"
    break;

  case 49: /* lvalue: expr '.' IDENT  */
#line 255 "src/parser.ypp"
                         {
		(yyval.astLvalue) = new DotOp((yyloc), sptOf((yyvsp[-2].astExpr)), sptOf(new Ident((yylsp[0]), (yyvsp[0].repr))));
		free((yyvsp[0].repr));
	}
#line 1966 "src/parser.tab.cpp"
    break;

  case 50: /* callArgListLeastOne: expr  */
#line 262 "src/parser.ypp"
             { (yyval.astCallArgList) = new CallParamList((yyloc)); (yyval.astCallArgList)->add((yyvsp[0].astExpr)); }
#line 1972 "src/parser.tab.cpp"
    break;

  case 51: /* callArgListLeastOne: expr ',' callArgListLeastOne  */
#line 263 "src/parser.ypp"
                                       { (yyval.astCallArgList) = (yyvsp[0].astCallArgList); (yyval.astCallArgList)->add_front((yyvsp[-2].astExpr)); }
#line 1978 "src/parser.tab.cpp"
    break;

  case 52: /* callArgList: %empty  */
#line 266 "src/parser.ypp"
                              { (yyval.astCallArgList) = new CallParamList((yyloc)); }
#line 1984 "src/parser.tab.cpp"
    break;

  case 53: /* callArgList: callArgListLeastOne  */
#line 267 "src/parser.ypp"
                              { (yyval.astCallArgList) = (yyvsp[0].astCallArgList); }
#line 1990 "src/parser.tab.cpp"
    break;

  case 54: /* elseRule: END  */
#line 271 "src/parser.ypp"
                              { (yyval.astExpr) = new ExprBlock((yyloc)); }
#line 1996 "src/parser.tab.cpp"
    break;

  case 55: /* elseRule: ELSE exprBlock END  */
#line 272 "src/parser.ypp"
                              { (yyval.astExpr) = (yyvsp[-1].astExprBlock); }
#line 2002 "src/parser.tab.cpp"
    break;

  case 56: /* elseRule: ELSEIF expr exprBlock elseRule  */
#line 273 "src/parser.ypp"
                                         {
		(yyval.astExpr) = new FlowIfElse((yyloc), sptOf((yyvsp[-2].astExpr)), sptOf((yyvsp[-1].astExprBlock)), sptOf((yyvsp[0].astExpr)));
	}
#line 2010 "src/parser.tab.cpp"
    break;

  case 57: /* elseRule: ELSE IF expr exprBlock elseRule END  */
#line 276 "src/parser.ypp"
                                              {
		throw ParseError((yylsp[-5]), "syntax: use \"elseif\" instead of \"else if\"");
	}
#line 2018 "src/parser.tab.cpp"
    break;

  case 58: /* typeSpec: %empty  */
#line 282 "src/parser.ypp"
                             { (yyval.astIdent) = new Ident((yyloc), "Any");        }
#line 2024 "src/parser.tab.cpp"
    break;

  case 59: /* typeSpec: TYPE_SPEC IDENT  */
#line 283 "src/parser.ypp"
                             { (yyval.astIdent) = new Ident((yylsp[0]), (yyvsp[0].repr)); free((yyvsp[0].repr)); }
#line 2030 "src/parser.tab.cpp"
    break;

  case 60: /* argRule: IDENT typeSpec  */
#line 286 "src/parser.ypp"
                       {
		(yyval.astArgument) = new Argument((yyloc), sptOf(new Ident((yylsp[-1]), (yyvsp[-1].repr))), sptOf((yyvsp[0].astIdent)));
		free((yyvsp[-1].repr));
	}
#line 2039 "src/parser.tab.cpp"
    break;

  case 61: /* structRule: MUTABLE structDef  */
#line 294 "src/parser.ypp"
                          { (yyval.astStructDef) = (yyvsp[0].astStructDef); (yyval.astStructDef)->isMutable = true; }
#line 2045 "src/parser.tab.cpp"
    break;

  case 62: /* structRule: structDef  */
#line 295 "src/parser.ypp"
                          { (yyval.astStructDef) = (yyvsp[0].astStructDef); }
#line 2051 "src/parser.tab.cpp"
    break;

  case 63: /* structDef: STRUCT IDENT structArgs END  */
#line 299 "src/parser.ypp"
                                    {
		(yyval.astStructDef) = new DefStruct((yyloc), false, sptOf(new Ident((yylsp[-2]), (yyvsp[-2].repr))));
		(yyval.astStructDef)->members = *((yyvsp[-1].astArgList));
		free((yyvsp[-2].repr)); free((yyvsp[-1].astArgList));
	}
#line 2061 "src/parser.tab.cpp"
    break;

  case 64: /* structArgs: %empty  */
#line 307 "src/parser.ypp"
                           { (yyval.astArgList) = new ArgumentList(); }
#line 2067 "src/parser.tab.cpp"
    break;

  case 65: /* structArgs: ';' structArgs  */
#line 308 "src/parser.ypp"
                           { (yyval.astArgList) = (yyvsp[0].astArgList); }
#line 2073 "src/parser.tab.cpp"
    break;

  case 66: /* structArgs: argRule ';' structArgs  */
#line 309 "src/parser.ypp"
                                 {
		(yyval.astArgList) = (yyvsp[0].astArgList);
		(yyval.astArgList)->push_front(sptOf((yyvsp[-2].astArgument)));
	}
#line 2082 "src/parser.tab.cpp"
    break;

  case 67: /* structArgs: argRule  */
#line 313 "src/parser.ypp"
                  {
		(yyval.astArgList) = new ArgumentList();;
		(yyval.astArgList)->push_front(sptOf((yyvsp[0].astArgument)));
	}
#line 2091 "src/parser.tab.cpp"
    break;

  case 68: /* funcRule: FUNCTION IDENT_LEFT_PAR funcArgs ')' typeSpec exprBlock END  */
#line 321 "src/parser.ypp"
                                                                    {
		std::string name((yyvsp[-5].repr));
		name.pop_back();
		(yyval.astFuncDef) = new DefFunc((yyloc), sptOf(new Ident(locLeft((yylsp[-5]), name.size()), name)),
			sptOf((yyvsp[-2].astIdent)), spt<ExprBlock>((yyvsp[-1].astExprBlock)));
		(yyval.astFuncDef)->args = *((yyvsp[-4].astArgList));
		free((yyvsp[-5].repr)); free((yyvsp[-4].astArgList));
	}
#line 2104 "src/parser.tab.cpp"
    break;

  case 69: /* funcArgs: %empty  */
#line 331 "src/parser.ypp"
                           { (yyval.astArgList) = new ArgumentList(); }
#line 2110 "src/parser.tab.cpp"
    break;

  case 70: /* funcArgs: funcArgsLeastOne  */
#line 332 "src/parser.ypp"
                           { (yyval.astArgList) = (yyvsp[0].astArgList); }
#line 2116 "src/parser.tab.cpp"
    break;

  case 71: /* funcArgsLeastOne: argRule ',' funcArgsLeastOne  */
#line 335 "src/parser.ypp"
                                     {
		(yyval.astArgList) = (yyvsp[0].astArgList);
		(yyval.astArgList)->push_front(sptOf((yyvsp[-2].astArgument)));
	}
#line 2125 "src/parser.tab.cpp"
    break;

  case 72: /* funcArgsLeastOne: argRule  */
#line 339 "src/parser.ypp"
                  {
		(yyval.astArgList) = new ArgumentList();;
		(yyval.astArgList)->push_front(sptOf((yyvsp[0].astArgument)));
	}
#line 2134 "src/parser.tab.cpp"
    break;


#line 2138 "src/parser.tab.cpp"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (ast, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
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


#if 1
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 345 "src/parser.ypp"


void yyerror(Ast*, const char *s) {
	throw ParseError(yylloc, std::string(s));
}
