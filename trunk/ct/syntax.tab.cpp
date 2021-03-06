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

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



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
     XF = 276,
     ID = 277,
     NUMBER = 278,
     STRING = 279,
     EMPTY_ELSE = 280,
     ELSE_PRE = 281,
     IF_PRE = 282,
     INDEX = 283
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
#define XF 276
#define ID 277
#define NUMBER 278
#define STRING 279
#define EMPTY_ELSE 280
#define ELSE_PRE 281
#define IF_PRE 282
#define INDEX 283




/* Copy the first part of user declarations.  */
#line 1 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"

#include "flex_user.h"
#include "bison_header.h"
#include <string>
#include "context.h"


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 9 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
typedef union YYSTYPE {
	char* m_id;
	char* m_str;
	int m_number;
} YYSTYPE;
/* Line 196 of yacc.c.  */
#line 154 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\\\syntax.tab.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 219 of yacc.c.  */
#line 178 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\\\syntax.tab.cpp"

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T) && (defined (__STDC__) || defined (__cplusplus))
# include <stddef.h> /* INFRINGES ON USER NAME SPACE */
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if defined (__STDC__) || defined (__cplusplus)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     define YYINCLUDED_STDLIB_H
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2005 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM ((YYSIZE_T) -1)
#  endif
#  ifdef __cplusplus
extern "C" {
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if (! defined (malloc) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if (! defined (free) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifdef __cplusplus
}
#  endif
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYLTYPE_IS_TRIVIAL) && YYLTYPE_IS_TRIVIAL \
             && defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   524

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  63
/* YYNRULES -- Number of rules. */
#define YYNRULES  125
/* YYNRULES -- Number of states. */
#define YYNSTATES  199

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    47,     2,    35,     2,     2,
      36,    43,    33,    31,    42,    32,    41,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,    39,
      29,    28,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    40,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,    45,     2,     2,     2,     2,
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
      25,    26,    27,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     6,     7,     9,    12,    14,    16,    18,
      20,    22,    24,    27,    29,    31,    33,    35,    37,    39,
      41,    46,    48,    50,    52,    56,    59,    62,    65,    67,
      71,    73,    77,    79,    83,    84,    89,    92,    95,    98,
     101,   104,   108,   112,   116,   120,   124,   128,   132,   136,
     140,   142,   144,   146,   148,   150,   152,   154,   156,   158,
     163,   165,   168,   169,   175,   179,   181,   185,   186,   187,
     197,   198,   199,   210,   211,   213,   214,   216,   220,   222,
     224,   226,   227,   231,   233,   234,   238,   240,   243,   246,
     250,   255,   256,   257,   265,   266,   272,   273,   279,   283,
     284,   287,   288,   293,   294,   299,   300,   304,   310,   311,
     316,   317,   318,   319,   334,   335,   337,   338,   339,   342,
     343,   344,   347,   349,   353,   355
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      49,     0,    -1,    50,    51,    -1,    -1,    52,    -1,    51,
      52,    -1,    54,    -1,    53,    -1,    39,    -1,    58,    -1,
      59,    -1,    60,    -1,    55,    39,    -1,    56,    -1,    64,
      -1,    66,    -1,    81,    -1,    83,    -1,    79,    -1,    80,
      -1,    66,    57,    28,    66,    -1,    86,    -1,   100,    -1,
      74,    -1,    38,    66,    40,    -1,     7,    61,    -1,     9,
      61,    -1,     8,    63,    -1,    22,    -1,    61,    41,    22,
      -1,    67,    -1,    62,    42,    67,    -1,    22,    -1,    63,
      42,    22,    -1,    -1,    62,    28,    65,    70,    -1,    14,
      67,    -1,    15,    67,    -1,    67,    14,    -1,    67,    15,
      -1,    32,    66,    -1,    66,    31,    66,    -1,    66,    32,
      66,    -1,    66,    33,    66,    -1,    66,    34,    66,    -1,
      66,    35,    66,    -1,    66,     3,    66,    -1,    66,    29,
      66,    -1,    66,    30,    66,    -1,    36,    66,    43,    -1,
      68,    -1,    71,    -1,    67,    -1,    17,    -1,    18,    -1,
      23,    -1,    24,    -1,    94,    -1,    96,    -1,    66,    38,
      66,    40,    -1,    61,    -1,    16,    61,    -1,    -1,    66,
      36,    69,    70,    43,    -1,    66,    36,    43,    -1,    66,
      -1,    70,    42,    66,    -1,    -1,    -1,     6,    72,    36,
      78,    43,    73,    44,    77,    45,    -1,    -1,    -1,     6,
      67,    75,    36,    78,    43,    76,    44,    77,    45,    -1,
      -1,    51,    -1,    -1,    22,    -1,    78,    42,    22,    -1,
      19,    -1,    20,    -1,     5,    -1,    -1,     5,    82,    70,
      -1,     4,    -1,    -1,     4,    84,    70,    -1,    54,    -1,
      85,    54,    -1,    87,    92,    -1,    10,    88,    89,    -1,
      87,    11,    10,    89,    -1,    -1,    -1,    36,    66,    43,
      90,    44,    85,    45,    -1,    -1,    36,    66,    43,    91,
      54,    -1,    -1,    11,    93,    44,    85,    45,    -1,    11,
      93,    54,    -1,    -1,    38,    40,    -1,    -1,    38,    95,
      70,    40,    -1,    -1,    12,    97,    98,    45,    -1,    -1,
      66,    46,    66,    -1,    98,    42,    66,    46,    66,    -1,
      -1,    22,    99,    28,    66,    -1,    -1,    -1,    -1,    13,
     101,    36,   105,    39,    66,   102,    39,   107,    43,    44,
     103,   104,    45,    -1,    -1,    85,    -1,    -1,    -1,   106,
     109,    -1,    -1,    -1,   108,   109,    -1,   110,    -1,   109,
      47,   110,    -1,    55,    -1,    56,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    43,    43,    47,    51,    52,    56,    57,    58,    62,
      63,    64,    68,    69,    73,    74,    75,    76,    77,    78,
      79,    82,    83,    84,    88,    94,    98,   102,   106,   107,
     111,   112,   117,   118,   122,   122,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     154,   155,   159,   159,   161,   165,   166,   172,   173,   171,
     179,   180,   178,   184,   186,   189,   191,   192,   196,   200,
     203,   204,   204,   208,   209,   209,   213,   214,   218,   222,
     224,   228,   232,   232,   234,   234,   239,   240,   242,   247,
     251,   252,   252,   257,   257,   261,   262,   263,   264,   264,
     269,   270,   270,   269,   273,   274,   277,   278,   278,   281,
     282,   282,   286,   287,   291,   292
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EQUAL", "YIELD", "RETURN", "FUNCTION",
  "MODULE", "EXPORT", "USING", "IF", "ELSE", "TABLE_HEAD", "FOR",
  "SELF_ADD", "SELF_SUB", "GLOBAL", "TRUE", "FALSE", "BREAK", "CONTINUE",
  "XF", "ID", "NUMBER", "STRING", "EMPTY_ELSE", "ELSE_PRE", "IF_PRE",
  "'='", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'('", "INDEX",
  "'['", "';'", "']'", "'.'", "','", "')'", "'{'", "'}'", "':'", "'#'",
  "$accept", "root", "prepare", "sentences", "sentence", "declare",
  "statement", "sep_statement", "no_sep_statement", "index_list", "module",
  "using", "export", "path", "var_list", "symbol_list", "assignment", "@1",
  "expr", "expr_var", "expr_apply", "@2", "para_list", "expr_function",
  "@3", "@4", "function_def", "@5", "@6", "stats_in_function", "arg_list",
  "break", "continue", "return", "@7", "yield", "@8", "statements",
  "if_stat", "if_list", "if_pre", "if", "@9", "@10", "else", "else_pre",
  "array_expr", "@11", "table_expr", "@12", "table_pair_list", "@13",
  "for_stat", "@14", "@15", "@16", "stats_in_for", "stats_option", "@17",
  "stats_option1", "@18", "stats_list", "stat_in_for", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    61,    60,
      62,    43,    45,    42,    47,    37,    40,   283,    91,    59,
      93,    46,    44,    41,   123,   125,    58,    35
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    48,    49,    50,    51,    51,    52,    52,    52,    53,
      53,    53,    54,    54,    55,    55,    55,    55,    55,    55,
      55,    56,    56,    56,    57,    58,    59,    60,    61,    61,
      62,    62,    63,    63,    65,    64,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      67,    67,    69,    68,    68,    70,    70,    72,    73,    71,
      75,    76,    74,    77,    77,    78,    78,    78,    79,    80,
      81,    82,    81,    83,    84,    83,    85,    85,    86,    87,
      87,    88,    90,    89,    91,    89,    92,    92,    92,    93,
      94,    95,    94,    97,    96,    98,    98,    98,    99,    98,
     101,   102,   103,   100,   104,   104,   105,   106,   105,   107,
     108,   107,   109,   109,   110,   110
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     1,     1,     3,     2,     2,     2,     1,     3,
       1,     3,     1,     3,     0,     4,     2,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     2,     0,     5,     3,     1,     3,     0,     0,     9,
       0,     0,    10,     0,     1,     0,     1,     3,     1,     1,
       1,     0,     3,     1,     0,     3,     1,     2,     2,     3,
       4,     0,     0,     7,     0,     5,     0,     5,     3,     0,
       2,     0,     4,     0,     4,     0,     3,     5,     0,     4,
       0,     0,     0,    14,     0,     1,     0,     0,     2,     0,
       0,     2,     1,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       3,     0,     0,     1,    84,    81,    67,     0,     0,     0,
      91,   103,   110,     0,     0,     0,    53,    54,    78,    79,
      28,    55,    56,     0,     0,   101,     8,     2,     4,     7,
       6,     0,    13,     9,    10,    11,    60,     0,    14,    15,
      52,    50,    51,    23,    18,    19,    16,    17,    21,    96,
      57,    58,    22,     0,     0,    70,     0,    25,    32,    27,
      26,     0,   105,     0,    36,    37,    61,    67,    40,    52,
       0,   100,     0,     5,    12,     0,    34,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    62,     0,     0,    38,
      39,    99,    88,    65,    85,    82,     0,    75,     0,     0,
      89,    28,     0,     0,   117,     0,    49,     0,    29,     0,
      31,    46,    47,    48,    41,    42,    43,    44,    45,    64,
       0,     0,     0,     0,     0,     0,    75,    76,     0,    33,
       0,     0,     0,     0,   104,     0,     0,     0,   102,    35,
       0,    59,    20,    90,     0,    98,    66,     0,     0,    68,
      94,     0,   106,     0,     0,   124,   125,   118,   122,    59,
      63,    86,     0,    71,    77,     0,     0,     0,   109,     0,
     111,     0,    97,    87,     0,    73,     0,    95,   107,     0,
     123,    73,    74,     0,     0,   120,     0,    69,    93,     0,
       0,    72,     0,   121,   112,   114,   115,     0,   113
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     1,     2,   182,    28,    29,    30,    31,    32,    88,
      33,    34,    35,    36,    37,    59,    38,   109,    39,    69,
      41,   120,    94,    42,    56,   165,    43,    96,   174,   183,
     128,    44,    45,    46,    54,    47,    53,   162,    48,    49,
      61,   100,   166,   167,    92,   124,    50,    72,    51,    62,
     103,   131,    52,    63,   179,   195,   197,   135,   136,   189,
     190,   157,   158
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -172
static const short int yypact[] =
{
    -172,     9,   398,  -172,   -24,   -17,    20,    -5,    18,    -5,
    -172,  -172,  -172,    20,    20,    -5,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,   103,   103,   -13,  -172,   398,  -172,  -172,
    -172,    11,  -172,  -172,  -172,  -172,     3,   -22,  -172,   416,
      -7,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,    60,
    -172,  -172,  -172,   103,   103,  -172,    37,     3,  -172,    32,
       3,    43,   486,    51,  -172,  -172,     3,  -172,    47,    24,
     311,  -172,   103,  -172,  -172,    67,  -172,    20,   103,   103,
     103,   103,   103,   103,   103,   103,    48,   103,    62,  -172,
    -172,    82,  -172,   426,    53,    53,    57,    74,    75,   103,
    -172,    70,   167,     1,    61,   103,  -172,     5,  -172,   103,
    -172,   119,   119,   119,    47,    47,   -20,   -20,   -20,  -172,
     103,   345,   103,    43,   293,   103,    74,  -172,    10,  -172,
     327,    79,   103,   103,  -172,    63,   461,   361,  -172,    53,
      13,    80,   426,  -172,   461,  -172,   426,    27,    81,  -172,
      66,   103,   426,   186,   103,  -172,  -172,    69,  -172,  -172,
    -172,  -172,   221,  -172,  -172,    84,    85,   461,   426,   103,
     426,   461,  -172,  -172,    87,   398,   461,  -172,   426,    93,
    -172,   398,   398,    68,   257,    71,    78,  -172,  -172,    94,
     461,  -172,    92,    69,  -172,   461,   461,    95,  -172
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -172,  -172,  -172,   122,   -26,  -172,   -90,  -123,  -122,  -172,
    -172,  -172,  -172,    22,  -172,  -172,  -172,  -172,   -21,    -2,
    -172,  -172,   -44,  -172,  -172,  -172,  -172,  -172,  -172,   -43,
      17,  -172,  -172,  -172,  -172,  -172,  -172,  -171,  -172,  -172,
    -172,    21,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,   -45,   -25
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -120
static const short int yytable[] =
{
      40,    73,    68,    70,    55,   184,    76,    89,    90,     3,
      95,    64,    65,   155,   156,   -83,    86,    20,   105,   -83,
      77,   -30,   -80,   -83,   196,    40,   -80,    71,   107,    57,
     -80,    60,    93,    93,   145,   -30,    15,    66,    89,    90,
      58,   102,    20,   133,    75,   138,   134,   125,   155,   156,
      74,    93,   148,   149,   161,   125,   160,   111,   112,   113,
     114,   115,   116,   117,   118,   139,   121,   155,   156,   148,
     163,    91,   173,    97,    98,   110,   140,   177,   130,    99,
      83,    84,    85,    86,   137,   105,   161,   104,    93,   108,
     122,   119,   123,   126,   173,   125,   127,   129,  -108,    93,
    -116,   142,   154,   164,   146,   161,   173,   151,   -24,    67,
     -92,   152,   153,   187,  -119,    11,   171,    13,    14,    15,
      16,    17,    40,   191,    27,    20,    21,    22,   175,   176,
     168,   181,   185,   170,    40,    23,   194,   192,   186,    24,
     198,    25,    40,   147,   143,   193,   180,     0,   178,     0,
      81,    82,    83,    84,    85,    86,    73,   105,     0,     0,
      40,     0,     0,     0,     0,    40,     0,     0,     0,    40,
      78,     0,     0,    40,    40,     0,     0,     0,     0,    40,
      40,     0,    40,     0,     0,     0,     0,     0,    40,    78,
       0,     0,     0,    40,    40,     0,    79,    80,    81,    82,
      83,    84,    85,    86,     0,   105,     0,     0,     0,     0,
       0,     0,     0,   132,     0,    79,    80,    81,    82,    83,
      84,    85,    86,     0,   105,     4,     5,     6,     0,     0,
       0,    10,   169,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,     0,
       0,     0,     0,    23,     0,     0,     0,    24,     0,    25,
       0,     4,     5,     6,     0,     0,   172,    10,     0,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,     0,     0,     0,     0,    23,
       0,     0,     0,    24,     0,    25,     0,     4,     5,     6,
       0,     0,   188,    10,     0,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    78,    20,    21,    22,     0,     0,
       0,     0,     0,     0,     0,    23,     0,     0,     0,    24,
      78,    25,     0,     0,     0,     0,     0,   144,     0,     0,
      79,    80,    81,    82,    83,    84,    85,    86,    78,   105,
       0,     0,     0,     0,   106,     0,    79,    80,    81,    82,
      83,    84,    85,    86,    78,   105,     0,     0,     0,     0,
     150,     0,     0,     0,    79,    80,    81,    82,    83,    84,
      85,    86,     0,   105,     0,   141,     0,     0,     0,     0,
      79,    80,    81,    82,    83,    84,    85,    86,     0,   105,
       0,   159,     4,     5,     6,     7,     8,     9,    10,     0,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    78,
      20,    21,    22,     0,     0,     0,     0,     0,     0,    78,
      23,     0,     0,     0,    24,     0,    25,    26,     0,     0,
       0,     0,     0,     0,     0,    79,    80,    81,    82,    83,
      84,    85,    86,     0,    87,    79,    80,    81,    82,    83,
      84,    85,    86,     0,   105,     4,     5,     6,     0,     0,
       0,    10,     0,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,     0,
       0,     0,    67,    23,     0,     0,     0,    24,    11,    25,
      13,    14,    15,    16,    17,     0,     0,     0,   101,    21,
      22,     0,     0,     0,     0,     0,     0,     0,    23,     0,
       0,     0,    24,     0,    25
};

static const short int yycheck[] =
{
       2,    27,    23,    24,     6,   176,    28,    14,    15,     0,
      54,    13,    14,   136,   136,    39,    36,    22,    38,    43,
      42,    28,    39,    47,   195,    27,    43,    40,    72,     7,
      47,     9,    53,    54,   124,    42,    16,    15,    14,    15,
      22,    62,    22,    42,    41,    40,    45,    42,   171,   171,
      39,    72,    42,    43,   144,    42,    43,    78,    79,    80,
      81,    82,    83,    84,    85,   109,    87,   190,   190,    42,
      43,    11,   162,    36,    42,    77,   120,   167,    99,    36,
      33,    34,    35,    36,   105,    38,   176,    36,   109,    22,
      28,    43,    10,    36,   184,    42,    22,    22,    28,   120,
      39,   122,    39,    22,   125,   195,   196,    28,    28,     6,
      44,   132,   133,    45,    43,    12,    47,    14,    15,    16,
      17,    18,   124,    45,     2,    22,    23,    24,    44,    44,
     151,    44,    39,   154,   136,    32,    44,    43,   181,    36,
      45,    38,   144,   126,   123,   190,   171,    -1,   169,    -1,
      31,    32,    33,    34,    35,    36,   182,    38,    -1,    -1,
     162,    -1,    -1,    -1,    -1,   167,    -1,    -1,    -1,   171,
       3,    -1,    -1,   175,   176,    -1,    -1,    -1,    -1,   181,
     182,    -1,   184,    -1,    -1,    -1,    -1,    -1,   190,     3,
      -1,    -1,    -1,   195,   196,    -1,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    38,     4,     5,     6,    -1,    -1,
      -1,    10,    46,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    -1,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    36,    -1,    38,
      -1,     4,     5,     6,    -1,    -1,    45,    10,    -1,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    -1,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    36,    -1,    38,    -1,     4,     5,     6,
      -1,    -1,    45,    10,    -1,    12,    13,    14,    15,    16,
      17,    18,    19,    20,     3,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,    36,
       3,    38,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    36,     3,    38,
      -1,    -1,    -1,    -1,    43,    -1,    29,    30,    31,    32,
      33,    34,    35,    36,     3,    38,    -1,    -1,    -1,    -1,
      43,    -1,    -1,    -1,    29,    30,    31,    32,    33,    34,
      35,    36,    -1,    38,    -1,    40,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    38,
      -1,    40,     4,     5,     6,     7,     8,     9,    10,    -1,
      12,    13,    14,    15,    16,    17,    18,    19,    20,     3,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      32,    -1,    -1,    -1,    36,    -1,    38,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    38,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    38,     4,     5,     6,    -1,    -1,
      -1,    10,    -1,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    -1,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,     6,    32,    -1,    -1,    -1,    36,    12,    38,
      14,    15,    16,    17,    18,    -1,    -1,    -1,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    36,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    49,    50,     0,     4,     5,     6,     7,     8,     9,
      10,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      22,    23,    24,    32,    36,    38,    39,    51,    52,    53,
      54,    55,    56,    58,    59,    60,    61,    62,    64,    66,
      67,    68,    71,    74,    79,    80,    81,    83,    86,    87,
      94,    96,   100,    84,    82,    67,    72,    61,    22,    63,
      61,    88,    97,   101,    67,    67,    61,     6,    66,    67,
      66,    40,    95,    52,    39,    41,    28,    42,     3,    29,
      30,    31,    32,    33,    34,    35,    36,    38,    57,    14,
      15,    11,    92,    66,    70,    70,    75,    36,    42,    36,
      89,    22,    66,    98,    36,    38,    43,    70,    22,    65,
      67,    66,    66,    66,    66,    66,    66,    66,    66,    43,
      69,    66,    28,    10,    93,    42,    36,    22,    78,    22,
      66,    99,    46,    42,    45,   105,   106,    66,    40,    70,
      70,    40,    66,    89,    44,    54,    66,    78,    42,    43,
      43,    28,    66,    66,    39,    55,    56,   109,   110,    40,
      43,    54,    85,    43,    22,    73,    90,    91,    66,    46,
      66,    47,    45,    54,    76,    44,    44,    54,    66,   102,
     110,    44,    51,    77,    85,    39,    77,    45,    45,   107,
     108,    45,    43,   109,    44,   103,    85,   104,    45
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (0)
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
              (Loc).first_line, (Loc).first_column,	\
              (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr,					\
                  Type, Value, Location);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname[yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");

# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()
    ;
#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended. */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to look-ahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
  *++yylsp = yylloc;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, yylsp - yylen, yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 43 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_exit((yylsp[0]).pos, (yylsp[0]).pos+(yylsp[0]).len);;}
    break;

  case 3:
#line 47 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_enter(); g_ast.p_null_path(); g_ast.p_null_stat();;}
    break;

  case 6:
#line 56 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_stat();;}
    break;

  case 9:
#line 62 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_module();;}
    break;

  case 10:
#line 63 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_using();;}
    break;

  case 11:
#line 64 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_export();;}
    break;

  case 20:
#line 79 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_insert(); ;}
    break;

  case 28:
#line 106 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_string((yyvsp[0].m_id));g_ast.p_new_path(); ;}
    break;

  case 29:
#line 107 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_string((yyvsp[0].m_id));g_ast.p_path();;}
    break;

  case 30:
#line 111 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_new_var_list(); ;}
    break;

  case 31:
#line 112 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_var_list(); ;}
    break;

  case 32:
#line 117 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_string((yyvsp[0].m_id)); g_ast.p_new_path(); ;}
    break;

  case 33:
#line 118 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_string((yyvsp[0].m_id));g_ast.p_path();;}
    break;

  case 34:
#line 122 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_para_list(); ;}
    break;

  case 35:
#line 123 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_assign((yylsp[-3]).pos, (yylsp[-3]).pos+(yyloc).len); ;}
    break;

  case 36:
#line 127 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_self_op(true, true); ;}
    break;

  case 37:
#line 128 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_self_op(false, true); ;}
    break;

  case 38:
#line 129 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_self_op(true, false); ;}
    break;

  case 39:
#line 130 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_self_op(false, false); ;}
    break;

  case 40:
#line 131 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_unitop("-");;}
    break;

  case 41:
#line 132 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_binop("+", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 42:
#line 133 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_binop("-", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 43:
#line 134 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_binop("*", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 44:
#line 135 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_binop("/", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 45:
#line 136 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_binop("%", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 46:
#line 137 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_binop("==", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 47:
#line 138 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_binop("<", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 48:
#line 139 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_binop(">", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 53:
#line 144 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_bool(true);;}
    break;

  case 54:
#line 145 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_bool(false);;}
    break;

  case 55:
#line 146 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_number((yyvsp[0].m_number), (yylsp[0]).pos, (yylsp[0]).pos+(yylsp[0]).len); ;}
    break;

  case 56:
#line 147 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_quot_string((yyvsp[0].m_str));;}
    break;

  case 59:
#line 150 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_index(); ;}
    break;

  case 60:
#line 154 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_var(false); ;}
    break;

  case 61:
#line 155 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_var(true); ;}
    break;

  case 62:
#line 159 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_para_list(); ;}
    break;

  case 63:
#line 160 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    { g_ast.p_apply((yyloc).pos, (yyloc).pos+(yyloc).len); ;}
    break;

  case 64:
#line 161 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_para_list(); g_ast.p_apply((yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 65:
#line 165 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_para_list();;}
    break;

  case 66:
#line 166 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_para_list();;}
    break;

  case 67:
#line 172 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_enter(); g_ast.p_null_path(); ;}
    break;

  case 68:
#line 173 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 69:
#line 174 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_exit((yyloc).pos, (yyloc).pos+(yyloc).len); ;}
    break;

  case 70:
#line 179 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_new_var_list(); g_ast.p_null_para_list(); g_ast.p_enter(); g_ast.p_null_path(); ;}
    break;

  case 71:
#line 180 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 72:
#line 181 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_exit((yyloc).pos, (yyloc).pos+(yyloc).len); g_ast.p_para_list(); g_ast.p_assign((yyloc).pos, (yyloc).pos+(yyloc).len); ;}
    break;

  case 76:
#line 191 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_string((yyvsp[0].m_id));g_ast.p_path();;}
    break;

  case 77:
#line 192 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_string((yyvsp[0].m_id));g_ast.p_path();;}
    break;

  case 78:
#line 196 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_break();;}
    break;

  case 79:
#line 200 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_continue();;}
    break;

  case 80:
#line 203 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_para_list(); g_ast.p_return(); ;}
    break;

  case 81:
#line 204 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_para_list(); ;}
    break;

  case 82:
#line 204 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_return();;}
    break;

  case 83:
#line 208 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_para_list(); g_ast.p_return(true); ;}
    break;

  case 84:
#line 209 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_para_list(); ;}
    break;

  case 85:
#line 209 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_return(true); ;}
    break;

  case 86:
#line 213 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_stat();;}
    break;

  case 87:
#line 214 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_stat();;}
    break;

  case 89:
#line 223 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_if_comlete((yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 90:
#line 224 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_if_comlete((yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 91:
#line 228 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_if();  ;}
    break;

  case 92:
#line 232 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 93:
#line 233 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_then(); ;}
    break;

  case 94:
#line 234 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 95:
#line 235 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_stat(); g_ast.p_then(); ;}
    break;

  case 97:
#line 241 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_else(); ;}
    break;

  case 98:
#line 243 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_stat(); g_ast.p_else(); ;}
    break;

  case 99:
#line 247 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 100:
#line 251 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_array(); g_ast.p_null_para_list(); g_ast.p_array();;}
    break;

  case 101:
#line 252 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_array(); g_ast.p_null_para_list(); ;}
    break;

  case 102:
#line 253 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_array(); ;}
    break;

  case 103:
#line 257 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_map(); ;}
    break;

  case 106:
#line 262 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_map(); ;}
    break;

  case 107:
#line 263 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_map(); ;}
    break;

  case 108:
#line 264 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_quot_string((yyvsp[0].m_id)); ;}
    break;

  case 109:
#line 265 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_map(); ;}
    break;

  case 110:
#line 269 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_for(); ;}
    break;

  case 111:
#line 270 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_for_condition(); ;}
    break;

  case 112:
#line 270 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 113:
#line 271 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_for_stats((yyloc).pos, (yyloc).pos+(yyloc).len); ;}
    break;

  case 117:
#line 278 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 118:
#line 278 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_for_start(); ;}
    break;

  case 120:
#line 282 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 121:
#line 282 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_for_every(); ;}
    break;

  case 122:
#line 286 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_stat(); ;}
    break;

  case 123:
#line 287 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"
    {g_ast.p_stat(); ;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 1880 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\\\syntax.tab.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;
  yylsp -= yylen;

  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  int yytype = YYTRANSLATE (yychar);
	  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
	  YYSIZE_T yysize = yysize0;
	  YYSIZE_T yysize1;
	  int yysize_overflow = 0;
	  char *yymsg = 0;
#	  define YYERROR_VERBOSE_ARGS_MAXIMUM 5
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;

#if 0
	  /* This is so xgettext sees the translatable formats that are
	     constructed on the fly.  */
	  YY_("syntax error, unexpected %s");
	  YY_("syntax error, unexpected %s, expecting %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
#endif
	  char *yyfmt;
	  char const *yyf;
	  static char const yyunexpected[] = "syntax error, unexpected %s";
	  static char const yyexpecting[] = ", expecting %s";
	  static char const yyor[] = " or %s";
	  char yyformat[sizeof yyunexpected
			+ sizeof yyexpecting - 1
			+ ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
			   * (sizeof yyor - 1))];
	  char const *yyprefix = yyexpecting;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 1;

	  yyarg[0] = yytname[yytype];
	  yyfmt = yystpcpy (yyformat, yyunexpected);

	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
		  {
		    yycount = 1;
		    yysize = yysize0;
		    yyformat[sizeof yyunexpected - 1] = '\0';
		    break;
		  }
		yyarg[yycount++] = yytname[yyx];
		yysize1 = yysize + yytnamerr (0, yytname[yyx]);
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + yystrlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow && yysize <= YYSTACK_ALLOC_MAXIMUM)
	    yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg)
	    {
	      /* Avoid sprintf, as that infringes on the user's name space.
		 Don't have undefined behavior even if the translation
		 produced a string with the wrong number of "%s"s.  */
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
		{
		  if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		    {
		      yyp += yytnamerr (yyp, yyarg[yyi++]);
		      yyf += 2;
		    }
		  else
		    {
		      yyp++;
		      yyf++;
		    }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      goto yyexhaustedlab;
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  yylsp -= yylen;
  yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping", yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though. */
  YYLLOC_DEFAULT (yyloc, yyerror_range - 1, 2);
  *++yylsp = yyloc;

  /* Shift the error token. */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK;
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 294 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\ct\\syntax.y"


