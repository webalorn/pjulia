/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 3 "src/parser.ypp"

	#include <deque>
	struct AstNode;
	struct Declaration;
	struct Expr;
	struct LValue;
	struct BinOp;
	struct UnaryOp;
	struct ExprBlock;
	struct CallParamList;
	struct Ident;
	struct Argument;
	struct DefStruct;
	struct DefFunc;

	class ArgumentList;
	class Ast;

	extern "C" int yylex();

#line 70 "src/parser.tab.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    STRING = 259,                  /* STRING  */
    IDENT = 260,                   /* IDENT  */
    INT_IDENT = 261,               /* INT_IDENT  */
    IDENT_LEFT_PAR = 262,          /* IDENT_LEFT_PAR  */
    INT_LEFT_PAR = 263,            /* INT_LEFT_PAR  */
    RIGHT_PAR_IDENT = 264,         /* RIGHT_PAR_IDENT  */
    ELSE = 265,                    /* ELSE  */
    ELSEIF = 266,                  /* ELSEIF  */
    END = 267,                     /* END  */
    FALSE = 268,                   /* FALSE  */
    FOR = 269,                     /* FOR  */
    FUNCTION = 270,                /* FUNCTION  */
    IF = 271,                      /* IF  */
    MUTABLE = 272,                 /* MUTABLE  */
    RETURN = 273,                  /* RETURN  */
    STRUCT = 274,                  /* STRUCT  */
    TRUE = 275,                    /* TRUE  */
    WHILE = 276,                   /* WHILE  */
    OP_EQ = 277,                   /* OP_EQ  */
    OP_NEQ = 278,                  /* OP_NEQ  */
    OP_LOWER_EQ = 279,             /* OP_LOWER_EQ  */
    OP_GREATER_EQ = 280,           /* OP_GREATER_EQ  */
    OP_AND = 281,                  /* OP_AND  */
    OP_OR = 282,                   /* OP_OR  */
    TYPE_SPEC = 283,               /* TYPE_SPEC  */
    END_FILE = 284,                /* END_FILE  */
    WITHOUT_OPTIO = 285,           /* WITHOUT_OPTIO  */
    RETURN_RULE = 286,             /* RETURN_RULE  */
    UANRY_MINUS = 287              /* UANRY_MINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 48 "src/parser.ypp"

	// Input types
	char *repr;

	// Return types
	AstNode* astNode;
	Declaration* astDeclaration;
	Expr* astExpr;
	LValue* astLvalue;
	BinOp* astBinOp;
	UnaryOp* astUnaryOp;
	ExprBlock* astExprBlock;
	CallParamList* astCallArgList;
	Ident* astIdent;
	Argument* astArgument;
	DefStruct* astStructDef;
	ArgumentList* astArgList;
	DefFunc* astFuncDef;

#line 139 "src/parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (Ast *ast);

#endif /* !YY_YY_SRC_PARSER_TAB_HPP_INCLUDED  */
