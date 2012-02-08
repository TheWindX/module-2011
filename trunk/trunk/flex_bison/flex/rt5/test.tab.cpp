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
     EXTERN = 271,
     TRUE = 272,
     FALSE = 273,
     ID = 274,
     NUMBER = 275,
     STRING = 276,
     EMPTY_ELSE = 277,
     ELSE_PRE = 278,
     IF_PRE = 279,
     INDEX = 280
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
#define EXTERN 271
#define TRUE 272
#define FALSE 273
#define ID 274
#define NUMBER 275
#define STRING 276
#define EMPTY_ELSE 277
#define ELSE_PRE 278
#define IF_PRE 279
#define INDEX 280




/* Copy the first part of user declarations.  */
#line 1 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"

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
#line 9 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
typedef union YYSTYPE {
	char* m_id;
	char* m_str;
	int m_number;
} YYSTYPE;
/* Line 196 of yacc.c.  */
#line 148 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\\\test.tab.cpp"
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
#line 172 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\\\test.tab.cpp"

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
#define YYLAST   520

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  61
/* YYNRULES -- Number of rules. */
#define YYNRULES  121
/* YYNRULES -- Number of states. */
#define YYNSTATES  195

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   280

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    44,     2,    32,     2,     2,
      33,    40,    30,    28,    39,    29,    38,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    43,    36,
      26,    25,    27,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    35,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
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
      34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     6,     7,     9,    12,    14,    16,    18,
      20,    22,    24,    27,    29,    31,    33,    35,    37,    42,
      44,    46,    48,    52,    55,    58,    61,    63,    67,    69,
      73,    75,    79,    80,    85,    88,    91,    94,    97,   100,
     104,   108,   112,   116,   120,   124,   128,   132,   136,   138,
     140,   142,   144,   146,   148,   150,   152,   154,   159,   161,
     164,   165,   171,   175,   177,   181,   182,   183,   193,   194,
     195,   206,   207,   209,   210,   212,   216,   218,   219,   223,
     225,   226,   230,   232,   235,   238,   242,   247,   248,   249,
     257,   258,   264,   265,   271,   275,   276,   279,   280,   285,
     286,   291,   292,   296,   302,   303,   308,   309,   310,   311,
     326,   327,   329,   330,   331,   334,   335,   336,   339,   341,
     345,   347
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      46,     0,    -1,    47,    48,    -1,    -1,    49,    -1,    48,
      49,    -1,    51,    -1,    50,    -1,    36,    -1,    55,    -1,
      56,    -1,    57,    -1,    52,    36,    -1,    53,    -1,    61,
      -1,    63,    -1,    76,    -1,    78,    -1,    63,    54,    25,
      63,    -1,    81,    -1,    95,    -1,    71,    -1,    35,    63,
      37,    -1,     7,    58,    -1,     9,    58,    -1,     8,    60,
      -1,    19,    -1,    58,    38,    19,    -1,    64,    -1,    59,
      39,    64,    -1,    19,    -1,    60,    39,    19,    -1,    -1,
      59,    25,    62,    67,    -1,    14,    64,    -1,    15,    64,
      -1,    64,    14,    -1,    64,    15,    -1,    29,    63,    -1,
      63,    28,    63,    -1,    63,    29,    63,    -1,    63,    30,
      63,    -1,    63,    31,    63,    -1,    63,    32,    63,    -1,
      63,     3,    63,    -1,    63,    26,    63,    -1,    63,    27,
      63,    -1,    33,    63,    40,    -1,    65,    -1,    68,    -1,
      64,    -1,    17,    -1,    18,    -1,    20,    -1,    21,    -1,
      89,    -1,    91,    -1,    63,    35,    63,    37,    -1,    58,
      -1,    16,    58,    -1,    -1,    63,    33,    66,    67,    40,
      -1,    63,    33,    40,    -1,    63,    -1,    67,    39,    63,
      -1,    -1,    -1,     6,    69,    33,    75,    40,    70,    41,
      74,    42,    -1,    -1,    -1,     6,    64,    72,    33,    75,
      40,    73,    41,    74,    42,    -1,    -1,    48,    -1,    -1,
      19,    -1,    75,    39,    19,    -1,     5,    -1,    -1,     5,
      77,    67,    -1,     4,    -1,    -1,     4,    79,    67,    -1,
      51,    -1,    80,    51,    -1,    82,    87,    -1,    10,    83,
      84,    -1,    82,    11,    10,    84,    -1,    -1,    -1,    33,
      63,    40,    85,    41,    80,    42,    -1,    -1,    33,    63,
      40,    86,    51,    -1,    -1,    11,    88,    41,    80,    42,
      -1,    11,    88,    51,    -1,    -1,    35,    37,    -1,    -1,
      35,    90,    67,    37,    -1,    -1,    12,    92,    93,    42,
      -1,    -1,    63,    43,    63,    -1,    93,    39,    63,    43,
      63,    -1,    -1,    19,    94,    25,    63,    -1,    -1,    -1,
      -1,    13,    96,    33,   100,    36,    63,    97,    36,   102,
      40,    41,    98,    99,    42,    -1,    -1,    80,    -1,    -1,
      -1,   101,   104,    -1,    -1,    -1,   103,   104,    -1,   105,
      -1,   104,    44,   105,    -1,    52,    -1,    53,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    40,    40,    44,    48,    49,    53,    54,    55,    59,
      60,    61,    65,    66,    70,    71,    72,    73,    74,    78,
      79,    80,    84,    90,    94,    98,   102,   103,   107,   108,
     113,   114,   118,   118,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   150,   151,
     155,   155,   157,   161,   162,   168,   169,   167,   175,   176,
     174,   180,   182,   185,   187,   188,   192,   193,   193,   197,
     198,   198,   202,   203,   207,   211,   213,   217,   221,   221,
     223,   223,   228,   229,   231,   236,   240,   241,   241,   246,
     246,   250,   251,   252,   253,   253,   258,   259,   259,   258,
     262,   263,   266,   267,   267,   270,   271,   271,   275,   276,
     280,   281
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EQUAL", "YIELD", "RETURN", "FUNCTION",
  "MODULE", "EXPORT", "USING", "IF", "ELSE", "TABLE_HEAD", "FOR",
  "SELF_ADD", "SELF_SUB", "EXTERN", "TRUE", "FALSE", "ID", "NUMBER",
  "STRING", "EMPTY_ELSE", "ELSE_PRE", "IF_PRE", "'='", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "'('", "INDEX", "'['", "';'", "']'", "'.'",
  "','", "')'", "'{'", "'}'", "':'", "'#'", "$accept", "root", "prepare",
  "sentences", "sentence", "declare", "statement", "sep_statement",
  "no_sep_statement", "index_list", "module", "using", "export", "path",
  "var_list", "symbol_list", "assignment", "@1", "expr", "expr_var",
  "expr_apply", "@2", "para_list", "expr_function", "@3", "@4",
  "function_def", "@5", "@6", "stats_in_function", "arg_list", "return",
  "@7", "yield", "@8", "statements", "if_stat", "if_list", "if_pre", "if",
  "@9", "@10", "else", "else_pre", "array_expr", "@11", "table_expr",
  "@12", "table_pair_list", "@13", "for_stat", "@14", "@15", "@16",
  "stats_in_for", "stats_option", "@17", "stats_option1", "@18",
  "stats_list", "stat_in_for", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    61,    60,    62,    43,    45,
      42,    47,    37,    40,   280,    91,    59,    93,    46,    44,
      41,   123,   125,    58,    35
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    45,    46,    47,    48,    48,    49,    49,    49,    50,
      50,    50,    51,    51,    52,    52,    52,    52,    52,    53,
      53,    53,    54,    55,    56,    57,    58,    58,    59,    59,
      60,    60,    62,    61,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    64,    64,
      66,    65,    65,    67,    67,    69,    70,    68,    72,    73,
      71,    74,    74,    75,    75,    75,    76,    77,    76,    78,
      79,    78,    80,    80,    81,    82,    82,    83,    85,    84,
      86,    84,    87,    87,    87,    88,    89,    90,    89,    92,
      91,    93,    93,    93,    94,    93,    96,    97,    98,    95,
      99,    99,   100,   101,   100,   102,   103,   102,   104,   104,
     105,   105
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     4,     1,
       1,     1,     3,     2,     2,     2,     1,     3,     1,     3,
       1,     3,     0,     4,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     1,     2,
       0,     5,     3,     1,     3,     0,     0,     9,     0,     0,
      10,     0,     1,     0,     1,     3,     1,     0,     3,     1,
       0,     3,     1,     2,     2,     3,     4,     0,     0,     7,
       0,     5,     0,     5,     3,     0,     2,     0,     4,     0,
       4,     0,     3,     5,     0,     4,     0,     0,     0,    14,
       0,     1,     0,     0,     2,     0,     0,     2,     1,     3,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       3,     0,     0,     1,    80,    77,    65,     0,     0,     0,
      87,    99,   106,     0,     0,     0,    51,    52,    26,    53,
      54,     0,     0,    97,     8,     2,     4,     7,     6,     0,
      13,     9,    10,    11,    58,     0,    14,    15,    50,    48,
      49,    21,    16,    17,    19,    92,    55,    56,    20,     0,
       0,    68,     0,    23,    30,    25,    24,     0,   101,     0,
      34,    35,    59,    65,    38,    50,     0,    96,     0,     5,
      12,     0,    32,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    60,     0,     0,    36,    37,    95,    84,    63,
      81,    78,     0,    73,     0,     0,    85,    26,     0,     0,
     113,     0,    47,     0,    27,     0,    29,    44,    45,    46,
      39,    40,    41,    42,    43,    62,     0,     0,     0,     0,
       0,     0,    73,    74,     0,    31,     0,     0,     0,     0,
     100,     0,     0,     0,    98,    33,     0,    57,    18,    86,
       0,    94,    64,     0,     0,    66,    90,     0,   102,     0,
       0,   120,   121,   114,   118,    57,    61,    82,     0,    69,
      75,     0,     0,     0,   105,     0,   107,     0,    93,    83,
       0,    71,     0,    91,   103,     0,   119,    71,    72,     0,
       0,   116,     0,    67,    89,     0,     0,    70,     0,   117,
     108,   110,   111,     0,   109
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     1,     2,   178,    26,    27,    28,    29,    30,    84,
      31,    32,    33,    34,    35,    55,    36,   105,    37,    65,
      39,   116,    90,    40,    52,   161,    41,    92,   170,   179,
     124,    42,    50,    43,    49,   158,    44,    45,    57,    96,
     162,   163,    88,   120,    46,    68,    47,    58,    99,   127,
      48,    59,   175,   191,   193,   131,   132,   185,   186,   153,
     154
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -168
static const short int yypact[] =
{
    -168,     6,   380,  -168,   -22,   -11,     0,    17,    32,    17,
    -168,  -168,  -168,     0,     0,    17,  -168,  -168,  -168,  -168,
    -168,   463,   463,   -20,  -168,   380,  -168,  -168,  -168,     9,
    -168,  -168,  -168,  -168,    30,   -18,  -168,   399,    -5,  -168,
    -168,  -168,  -168,  -168,  -168,    36,  -168,  -168,  -168,   463,
     463,  -168,    44,    30,  -168,    46,    30,    54,   485,    55,
    -168,  -168,    30,  -168,    48,    13,   300,  -168,   463,  -168,
    -168,    70,  -168,     0,   463,   463,   463,   463,   463,   463,
     463,   463,    50,   463,    66,  -168,  -168,    83,  -168,   409,
      56,    56,    61,    77,    79,   463,  -168,    75,   165,    -1,
      65,   463,  -168,     3,  -168,   463,  -168,    84,    84,    84,
      48,    48,    11,    11,    11,  -168,   463,   331,   463,    54,
     281,   463,    77,  -168,    14,  -168,   315,    80,   463,   463,
    -168,    71,   441,   346,  -168,    56,    26,    81,   409,  -168,
     441,  -168,   409,    33,    89,  -168,    82,   463,   409,   183,
     463,  -168,  -168,    67,  -168,  -168,  -168,  -168,   215,  -168,
    -168,    85,    86,   441,   409,   463,   409,   441,  -168,  -168,
      88,   380,   441,  -168,   409,    96,  -168,   380,   380,    78,
     248,    93,    92,  -168,  -168,    95,   441,  -168,    98,    67,
    -168,   441,   441,    94,  -168
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -168,  -168,  -168,   119,   -24,  -168,   -88,  -119,  -117,  -168,
    -168,  -168,  -168,    28,  -168,  -168,  -168,  -168,   -19,    -2,
    -168,  -168,   -42,  -168,  -168,  -168,  -168,  -168,  -168,   -55,
       2,  -168,  -168,  -168,  -168,  -167,  -168,  -168,  -168,    18,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,   -61,
     -27
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -116
static const short int yytable[] =
{
      38,    69,    64,    66,    51,   180,     3,    72,    91,    85,
      86,    60,    61,   151,   -79,   152,    15,    67,   -79,    18,
     -28,    73,   -79,    38,   192,   -76,   103,    85,    86,   -76,
      89,    89,   141,   -76,   -28,    53,    18,    56,   129,    98,
     134,   130,   121,    62,    82,    70,   101,    87,   151,    89,
     152,    54,   157,   144,   145,   107,   108,   109,   110,   111,
     112,   113,   114,   135,   117,   121,   156,   151,    71,   152,
     169,   106,   144,   159,   136,   173,   126,    93,    79,    80,
      81,    82,   133,   101,   157,    94,    89,    95,   100,   104,
     115,   118,   169,   119,   122,   121,   123,    89,   125,   138,
    -104,  -112,   142,   157,   169,   147,   -22,   150,   160,   148,
     149,   167,    77,    78,    79,    80,    81,    82,    38,   101,
     183,    25,   182,   -88,   143,   189,   171,   172,   164,   177,
      38,   166,   181,  -115,   187,   188,   194,   139,    38,   190,
     176,     0,     0,     0,     0,     0,   174,     0,     0,     0,
       0,     0,     0,     0,    69,     0,    38,     0,     0,     0,
       0,    38,     0,     0,     0,    38,     0,     0,    74,    38,
      38,     0,     0,     0,     0,    38,    38,     0,    38,     0,
       0,     0,     0,     0,    38,     0,    74,     0,     0,    38,
      38,    75,    76,    77,    78,    79,    80,    81,    82,     0,
     101,     0,     0,     0,     0,     0,     0,     0,   128,    75,
      76,    77,    78,    79,    80,    81,    82,     0,   101,     4,
       5,     6,     0,     0,     0,    10,   165,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,     0,     0,     0,
       0,     0,     0,     0,    21,     0,     0,     0,    22,     0,
      23,     0,     4,     5,     6,     0,     0,   168,    10,     0,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
       0,     0,     0,     0,     0,     0,     0,    21,     0,     0,
       0,    22,     0,    23,     0,     4,     5,     6,     0,     0,
     184,    10,     0,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    74,     0,     0,     0,     0,     0,     0,
      21,     0,     0,     0,    22,     0,    23,     0,    74,     0,
       0,     0,   140,     0,     0,     0,    75,    76,    77,    78,
      79,    80,    81,    82,    74,   101,     0,     0,     0,     0,
     102,    75,    76,    77,    78,    79,    80,    81,    82,    74,
     101,     0,     0,     0,     0,   146,     0,    75,    76,    77,
      78,    79,    80,    81,    82,     0,   101,     0,   137,     0,
       0,     0,    75,    76,    77,    78,    79,    80,    81,    82,
       0,   101,     0,   155,     4,     5,     6,     7,     8,     9,
      10,     0,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    74,     0,     0,     0,     0,     0,     0,    21,
       0,     0,    74,    22,     0,    23,    24,     0,     0,     0,
       0,     0,     0,     0,     0,    75,    76,    77,    78,    79,
      80,    81,    82,     0,    83,    75,    76,    77,    78,    79,
      80,    81,    82,     0,   101,     4,     5,     6,     0,     0,
       0,    10,     0,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,     0,     0,     0,     0,     0,     0,    63,
      21,     0,     0,     0,    22,    11,    23,    13,    14,    15,
      16,    17,    18,    19,    20,     0,     0,     0,     0,     0,
       0,    63,    21,     0,     0,     0,    22,    11,    23,    13,
      14,    15,    16,    17,    97,    19,    20,     0,     0,     0,
       0,     0,     0,     0,    21,     0,     0,     0,    22,     0,
      23
};

static const short int yycheck[] =
{
       2,    25,    21,    22,     6,   172,     0,    25,    50,    14,
      15,    13,    14,   132,    36,   132,    16,    37,    40,    19,
      25,    39,    44,    25,   191,    36,    68,    14,    15,    40,
      49,    50,   120,    44,    39,     7,    19,     9,    39,    58,
      37,    42,    39,    15,    33,    36,    35,    11,   167,    68,
     167,    19,   140,    39,    40,    74,    75,    76,    77,    78,
      79,    80,    81,   105,    83,    39,    40,   186,    38,   186,
     158,    73,    39,    40,   116,   163,    95,    33,    30,    31,
      32,    33,   101,    35,   172,    39,   105,    33,    33,    19,
      40,    25,   180,    10,    33,    39,    19,   116,    19,   118,
      25,    36,   121,   191,   192,    25,    25,    36,    19,   128,
     129,    44,    28,    29,    30,    31,    32,    33,   120,    35,
      42,     2,   177,    41,   122,   186,    41,    41,   147,    41,
     132,   150,    36,    40,    42,    40,    42,   119,   140,    41,
     167,    -1,    -1,    -1,    -1,    -1,   165,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   178,    -1,   158,    -1,    -1,    -1,
      -1,   163,    -1,    -1,    -1,   167,    -1,    -1,     3,   171,
     172,    -1,    -1,    -1,    -1,   177,   178,    -1,   180,    -1,
      -1,    -1,    -1,    -1,   186,    -1,     3,    -1,    -1,   191,
     192,    26,    27,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    26,
      27,    28,    29,    30,    31,    32,    33,    -1,    35,     4,
       5,     6,    -1,    -1,    -1,    10,    43,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    33,    -1,
      35,    -1,     4,     5,     6,    -1,    -1,    42,    10,    -1,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    33,    -1,    35,    -1,     4,     5,     6,    -1,    -1,
      42,    10,    -1,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    -1,    -1,    -1,    33,    -1,    35,    -1,     3,    -1,
      -1,    -1,    41,    -1,    -1,    -1,    26,    27,    28,    29,
      30,    31,    32,    33,     3,    35,    -1,    -1,    -1,    -1,
      40,    26,    27,    28,    29,    30,    31,    32,    33,     3,
      35,    -1,    -1,    -1,    -1,    40,    -1,    26,    27,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,     4,     5,     6,     7,     8,     9,
      10,    -1,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     3,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    -1,     3,    33,    -1,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,
      31,    32,    33,    -1,    35,    26,    27,    28,    29,    30,
      31,    32,    33,    -1,    35,     4,     5,     6,    -1,    -1,
      -1,    10,    -1,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,     6,
      29,    -1,    -1,    -1,    33,    12,    35,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,     6,    29,    -1,    -1,    -1,    33,    12,    35,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    33,    -1,
      35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    46,    47,     0,     4,     5,     6,     7,     8,     9,
      10,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    29,    33,    35,    36,    48,    49,    50,    51,    52,
      53,    55,    56,    57,    58,    59,    61,    63,    64,    65,
      68,    71,    76,    78,    81,    82,    89,    91,    95,    79,
      77,    64,    69,    58,    19,    60,    58,    83,    92,    96,
      64,    64,    58,     6,    63,    64,    63,    37,    90,    49,
      36,    38,    25,    39,     3,    26,    27,    28,    29,    30,
      31,    32,    33,    35,    54,    14,    15,    11,    87,    63,
      67,    67,    72,    33,    39,    33,    84,    19,    63,    93,
      33,    35,    40,    67,    19,    62,    64,    63,    63,    63,
      63,    63,    63,    63,    63,    40,    66,    63,    25,    10,
      88,    39,    33,    19,    75,    19,    63,    94,    43,    39,
      42,   100,   101,    63,    37,    67,    67,    37,    63,    84,
      41,    51,    63,    75,    39,    40,    40,    25,    63,    63,
      36,    52,    53,   104,   105,    37,    40,    51,    80,    40,
      19,    70,    85,    86,    63,    43,    63,    44,    42,    51,
      73,    41,    41,    51,    63,    97,   105,    41,    48,    74,
      80,    36,    74,    42,    42,   102,   103,    42,    40,   104,
      41,    98,    80,    99,    42
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
#line 40 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_exit((yylsp[0]).pos, (yylsp[0]).pos+(yylsp[0]).len);;}
    break;

  case 3:
#line 44 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_enter(); g_ast.p_null_path(); g_ast.p_null_stat();;}
    break;

  case 6:
#line 53 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_stat();;}
    break;

  case 9:
#line 59 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_module();;}
    break;

  case 10:
#line 60 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_using();;}
    break;

  case 11:
#line 61 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_export();;}
    break;

  case 18:
#line 74 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_insert(); ;}
    break;

  case 26:
#line 102 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_string((yyvsp[0].m_id));g_ast.p_new_path(); ;}
    break;

  case 27:
#line 103 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_string((yyvsp[0].m_id));g_ast.p_path();;}
    break;

  case 28:
#line 107 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_new_var_list(); ;}
    break;

  case 29:
#line 108 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_var_list(); ;}
    break;

  case 30:
#line 113 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_string((yyvsp[0].m_id)); g_ast.p_new_path(); ;}
    break;

  case 31:
#line 114 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_string((yyvsp[0].m_id));g_ast.p_path();;}
    break;

  case 32:
#line 118 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_para_list(); ;}
    break;

  case 33:
#line 119 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_assign((yylsp[-3]).pos, (yylsp[-3]).pos+(yyloc).len); ;}
    break;

  case 34:
#line 123 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_self_op(true, true); ;}
    break;

  case 35:
#line 124 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_self_op(false, true); ;}
    break;

  case 36:
#line 125 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_self_op(true, false); ;}
    break;

  case 37:
#line 126 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_self_op(false, false); ;}
    break;

  case 38:
#line 127 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_unitop("-");;}
    break;

  case 39:
#line 128 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_binop("+", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 40:
#line 129 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_binop("-", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 41:
#line 130 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_binop("*", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 42:
#line 131 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_binop("/", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 43:
#line 132 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_binop("%", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 44:
#line 133 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_binop("==", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 45:
#line 134 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_binop("<", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 46:
#line 135 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_binop(">", (yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 51:
#line 140 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_bool(true);;}
    break;

  case 52:
#line 141 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_bool(false);;}
    break;

  case 53:
#line 142 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_number((yyvsp[0].m_number), (yylsp[0]).pos, (yylsp[0]).pos+(yylsp[0]).len); ;}
    break;

  case 54:
#line 143 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_quot_string((yyvsp[0].m_str));;}
    break;

  case 57:
#line 146 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_index(); ;}
    break;

  case 58:
#line 150 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_var(false); ;}
    break;

  case 59:
#line 151 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_var(true); ;}
    break;

  case 60:
#line 155 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_para_list(); ;}
    break;

  case 61:
#line 156 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    { g_ast.p_apply((yyloc).pos, (yyloc).pos+(yyloc).len); ;}
    break;

  case 62:
#line 157 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_para_list(); g_ast.p_apply((yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 63:
#line 161 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_para_list();;}
    break;

  case 64:
#line 162 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_para_list();;}
    break;

  case 65:
#line 168 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_enter(); g_ast.p_null_path(); ;}
    break;

  case 66:
#line 169 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 67:
#line 170 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_exit((yyloc).pos, (yyloc).pos+(yyloc).len); ;}
    break;

  case 68:
#line 175 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_new_var_list(); g_ast.p_null_para_list(); g_ast.p_enter(); g_ast.p_null_path(); ;}
    break;

  case 69:
#line 176 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 70:
#line 177 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_exit((yyloc).pos, (yyloc).pos+(yyloc).len); g_ast.p_para_list(); g_ast.p_assign((yyloc).pos, (yyloc).pos+(yyloc).len); ;}
    break;

  case 74:
#line 187 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_string((yyvsp[0].m_id));g_ast.p_path();;}
    break;

  case 75:
#line 188 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_string((yyvsp[0].m_id));g_ast.p_path();;}
    break;

  case 76:
#line 192 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_para_list(); g_ast.p_return(); ;}
    break;

  case 77:
#line 193 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_para_list(); ;}
    break;

  case 78:
#line 193 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_return();;}
    break;

  case 79:
#line 197 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_para_list(); g_ast.p_return(true); ;}
    break;

  case 80:
#line 198 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_para_list(); ;}
    break;

  case 81:
#line 198 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_return(true); ;}
    break;

  case 82:
#line 202 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_stat();;}
    break;

  case 83:
#line 203 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_stat();;}
    break;

  case 85:
#line 212 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_if_comlete((yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 86:
#line 213 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_if_comlete((yyloc).pos, (yyloc).pos+(yyloc).len);;}
    break;

  case 87:
#line 217 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_if();  ;}
    break;

  case 88:
#line 221 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 89:
#line 222 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_then(); ;}
    break;

  case 90:
#line 223 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 91:
#line 224 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_stat(); g_ast.p_then(); ;}
    break;

  case 93:
#line 230 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_else(); ;}
    break;

  case 94:
#line 232 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_stat(); g_ast.p_else(); ;}
    break;

  case 95:
#line 236 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 96:
#line 240 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_array(); g_ast.p_null_para_list(); g_ast.p_array();;}
    break;

  case 97:
#line 241 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_array(); g_ast.p_null_para_list(); ;}
    break;

  case 98:
#line 242 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_array(); ;}
    break;

  case 99:
#line 246 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_map(); ;}
    break;

  case 102:
#line 251 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_map(); ;}
    break;

  case 103:
#line 252 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_map(); ;}
    break;

  case 104:
#line 253 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_quot_string((yyvsp[0].m_id)); ;}
    break;

  case 105:
#line 254 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_map(); ;}
    break;

  case 106:
#line 258 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_for(); ;}
    break;

  case 107:
#line 259 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_for_condition(); ;}
    break;

  case 108:
#line 259 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 109:
#line 260 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_for_stats((yyloc).pos, (yyloc).pos+(yyloc).len); ;}
    break;

  case 113:
#line 267 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 114:
#line 267 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_for_start(); ;}
    break;

  case 116:
#line 271 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_null_stat(); ;}
    break;

  case 117:
#line 271 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_for_every(); ;}
    break;

  case 118:
#line 275 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_stat(); ;}
    break;

  case 119:
#line 276 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"
    {g_ast.p_stat(); ;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 1863 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\\\test.tab.cpp"

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


#line 283 "d:\\frame\\Package\\module-2011_http\\trunk\\trunk\\flex_bison\\flex\\rt5\\test.y"


