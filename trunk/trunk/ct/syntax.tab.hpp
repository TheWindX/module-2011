/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     EQUAL = 258,
     YIELD = 259,
     RETURN = 260,
     FUNCTION = 261,
     MODULE = 262,
     EXPORT = 263,
     USING = 264,
     IF = 265,
     ELSE = 266,
     TABLE_HEAD = 267,
     FOR = 268,
     SELF_ADD = 269,
     SELF_SUB = 270,
     GLOBAL = 271,
     TRUE = 272,
     FALSE = 273,
     BREAK = 274,
     CONTINUE = 275,
     ID = 276,
     NUMBER = 277,
     STRING = 278,
     EMPTY_ELSE = 279,
     ELSE_PRE = 280,
     IF_PRE = 281,
     INDEX = 282
   };
#endif
/* Tokens.  */
#define EQUAL 258
#define YIELD 259
#define RETURN 260
#define FUNCTION 261
#define MODULE 262
#define EXPORT 263
#define USING 264
#define IF 265
#define ELSE 266
#define TABLE_HEAD 267
#define FOR 268
#define SELF_ADD 269
#define SELF_SUB 270
#define GLOBAL 271
#define TRUE 272
#define FALSE 273
#define BREAK 274
#define CONTINUE 275
#define ID 276
#define NUMBER 277
#define STRING 278
#define EMPTY_ELSE 279
#define ELSE_PRE 280
#define IF_PRE 281
#define INDEX 282




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 9 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
typedef union YYSTYPE {
	char* m_id;
	char* m_str;
	int m_number;
} YYSTYPE;
/* Line 1447 of yacc.c.  */
#line 98 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\\\syntax.tab.hpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined (YYLTYPE) && ! defined (YYLTYPE_IS_DECLARED)
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;


