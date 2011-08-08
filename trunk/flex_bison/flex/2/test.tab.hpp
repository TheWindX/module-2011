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
     NUMBER = 258,
     ID = 259,
     E_PLUS_E = 260,
     E_MULTI_E = 261
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define ID 259
#define E_PLUS_E 260
#define E_MULTI_E 261




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 7 "d:\\frame\\Package\\module-2011\\trunk\\flex_bison\\flex\\2\\test.y"
typedef union YYSTYPE {
	std::string m_id;
	int m_number;
} YYSTYPE;
/* Line 1447 of yacc.c.  */
#line 55 "d:\\frame\\Package\\module-2011\\trunk\\flex_bison\\flex\\2\\\\test.tab.hpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



