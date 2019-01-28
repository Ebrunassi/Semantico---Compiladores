/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "sintatico.y" /* yacc.c:339  */


#include <stdlib.h>
#include<stdio.h>
#include <ast.h>
#include <cmd.h>
#include <table.h>
#include <error.h>
#include <string.h>
extern FILE* yyin;
extern int yyrestart(FILE *f);
extern int yylex();
extern char* yytext;
extern int yyleng;
extern int yymore();

void yyerror(char* );
int lines = 0;
int col = 1;
int col_last_id;
int quebra_linha = 1;
int syntax_error = 0;
int tab = 0;
char linha_toda[500000];
char linha_atual[500000];
char *error;

Program *program = NULL;
Table *table = NULL;
int erro = 0;
int define_line = 0;


#line 100 "sintatico.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "sintatico.tab.h".  */
#ifndef YY_YY_SINTATICO_TAB_H_INCLUDED
# define YY_YY_SINTATICO_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VOID = 258,
    INT = 259,
    CHAR = 260,
    RETURN = 261,
    BREAK = 262,
    SWITCH = 263,
    CASE = 264,
    DEFAULT = 265,
    DO = 266,
    WHILE = 267,
    FOR = 268,
    IF = 269,
    ELSE = 270,
    TYPEDEF = 271,
    STRUCT = 272,
    PLUS = 273,
    MINUS = 274,
    MULTIPLY = 275,
    DIV = 276,
    REMAINDER = 277,
    INC = 278,
    DEC = 279,
    BITWISE_AND = 280,
    BITWISE_OR = 281,
    BITWISE_NOT = 282,
    BITWISE_XOR = 283,
    NOT = 284,
    LOGICAL_AND = 285,
    LOGICAL_OR = 286,
    EQUAL = 287,
    NOT_EQUAL = 288,
    LESS_THAN = 289,
    GREATER_THAN = 290,
    LESS_EQUAL = 291,
    GREATER_EQUAL = 292,
    R_SHIFT = 293,
    L_SHIFT = 294,
    ASSIGN = 295,
    ADD_ASSIGN = 296,
    MINUS_ASSIGN = 297,
    SEMICOLON = 298,
    COMMA = 299,
    COLON = 300,
    L_PAREN = 301,
    R_PAREN = 302,
    L_CURLY_BRACKET = 303,
    R_CURLY_BRACKET = 304,
    L_SQUARE_BRACKET = 305,
    R_SQUARE_BRACKET = 306,
    TERNARY_CONDITIONAL = 307,
    NUMBER_SIGN = 308,
    POINTER = 309,
    PRINTF = 310,
    SCANF = 311,
    DEFINE = 312,
    EXIT = 313,
    NUM_HEXA = 314,
    NUM_OCTAL = 315,
    NUM_INTEGER = 316,
    CHARACTER = 317,
    STRING = 318,
    IDENTIFIER = 319,
    BREAKLINE = 320,
    END_OF_FILE = 321
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 34 "sintatico.y" /* yacc.c:355  */

	Function *fun;
	Variable *var;
	CmdList *cmd;
	Node *ast;
	char *str;
	int num;


#line 217 "sintatico.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SINTATICO_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 234 "sintatico.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   815

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  136
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  258

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   321

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   166,   166,   177,   180,   181,   185,   188,   192,   195,
     198,   204,   211,   214,   217,   223,   226,   240,   243,   247,
     251,   259,   262,   269,   272,   278,   281,   287,   290,   296,
     299,   306,   309,   312,   315,   320,   323,   329,   335,   338,
     341,   344,   347,   350,   353,   360,   363,   366,   369,   375,
     378,   384,   387,   390,   396,   399,   405,   411,   417,   425,
     428,   434,   437,   440,   443,   448,   452,   455,   462,   465,
     468,   474,   477,   480,   483,   489,   495,   498,   501,   505,
     508,   511,   517,   520,   526,   529,   532,   535,   541,   544,
     547,   550,   553,   556,   562,   565,   568,   574,   577,   580,
     583,   589,   592,   595,   600,   604,   611,   614,   617,   623,
     626,   629,   632,   635,   641,   644,   647,   653,   656,   662,
     665,   671,   674,   680,   683,   689,   692,   698,   701,   708,
     712,   715,   721,   724,   727,   733,   736
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VOID", "INT", "CHAR", "RETURN", "BREAK",
  "SWITCH", "CASE", "DEFAULT", "DO", "WHILE", "FOR", "IF", "ELSE",
  "TYPEDEF", "STRUCT", "PLUS", "MINUS", "MULTIPLY", "DIV", "REMAINDER",
  "INC", "DEC", "BITWISE_AND", "BITWISE_OR", "BITWISE_NOT", "BITWISE_XOR",
  "NOT", "LOGICAL_AND", "LOGICAL_OR", "EQUAL", "NOT_EQUAL", "LESS_THAN",
  "GREATER_THAN", "LESS_EQUAL", "GREATER_EQUAL", "R_SHIFT", "L_SHIFT",
  "ASSIGN", "ADD_ASSIGN", "MINUS_ASSIGN", "SEMICOLON", "COMMA", "COLON",
  "L_PAREN", "R_PAREN", "L_CURLY_BRACKET", "R_CURLY_BRACKET",
  "L_SQUARE_BRACKET", "R_SQUARE_BRACKET", "TERNARY_CONDITIONAL",
  "NUMBER_SIGN", "POINTER", "PRINTF", "SCANF", "DEFINE", "EXIT",
  "NUM_HEXA", "NUM_OCTAL", "NUM_INTEGER", "CHARACTER", "STRING",
  "IDENTIFIER", "BREAKLINE", "END_OF_FILE", "$accept", "start", "s",
  "program", "declarations", "declarations_unit", "var_declarations_unit",
  "type", "pointer", "init_desc", "init_decla", "decla",
  "prototip_declarations_unit", "parametros", "parameter_list",
  "parameter", "comandos", "bloco", "command_list", "loop_command",
  "expr_stat", "jump_command", "conditional_command", "io_command",
  "print_stat", "function_declarations", "idf", "var_list", "number",
  "primary_expression", "postfix_expression", "argument_expression_list",
  "unary_expression", "unary_operator", "cast_expression",
  "multiplicative_expression", "additive_expression", "minus", "plus",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "colon", "assignment_expression",
  "assignment_operator", "expression", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321
};
# endif

#define YYPACT_NINF -120

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-120)))

#define YYTABLE_NINF -66

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      35,  -120,  -120,  -120,   -42,    17,  -120,    35,  -120,  -120,
    -120,   -12,  -120,  -120,   -39,  -120,  -120,     8,    51,    -4,
       3,  -120,    47,    71,   727,  -120,   727,  -120,    71,  -120,
      -9,   727,    39,   -16,  -120,  -120,  -120,   751,   751,  -120,
    -120,  -120,   248,  -120,  -120,  -120,  -120,  -120,  -120,  -120,
    -120,    70,   116,   727,  -120,    90,    85,    88,    87,   141,
      73,    91,   120,   134,   -19,  -120,  -120,   106,   -30,    52,
     112,   103,  -120,  -120,  -120,    25,   -13,  -120,  -120,   201,
     727,  -120,  -120,     6,    61,  -120,  -120,   614,   727,  -120,
    -120,  -120,   727,  -120,  -120,   727,   727,   727,  -120,  -120,
     727,   727,   727,   727,   727,   727,   727,   727,   727,   727,
     727,   727,   727,   727,   727,   727,   727,  -120,  -120,   201,
    -120,   131,   124,   166,  -120,   626,   143,   146,   147,   150,
    -120,   567,   151,   153,   154,  -120,    -9,   272,  -120,  -120,
    -120,  -120,  -120,  -120,   201,   132,   727,   155,  -120,  -120,
      84,  -120,   -21,  -120,  -120,  -120,  -120,    90,    90,    85,
      85,    88,    88,    88,    88,    87,    87,   141,    73,    91,
     120,   134,   133,  -120,   331,   201,   727,   158,  -120,  -120,
     136,   197,   727,   673,   727,   390,   159,   160,   727,   103,
    -120,  -120,  -120,   449,  -120,  -120,   727,   727,  -120,  -120,
    -120,   727,  -120,   508,   -15,   727,  -120,   164,    93,  -120,
     673,   140,    94,  -120,    95,   172,   100,  -120,  -120,  -120,
    -120,  -120,  -120,    40,   727,   143,   702,  -120,   143,   727,
     174,   101,   193,   184,  -120,   107,  -120,   143,   108,   214,
    -120,  -120,   727,   188,   168,  -120,   190,  -120,   143,   143,
    -120,  -120,   187,  -120,  -120,  -120,   192,  -120
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    12,    14,    13,     0,     0,     2,     3,     4,     7,
       9,     0,    10,     6,     0,     1,     5,    15,    23,     0,
       0,    17,    21,     0,     0,    16,     0,    18,     0,    11,
       0,     0,     0,     0,    90,    91,    89,     0,     0,    88,
      92,    93,     0,    70,    69,    68,    73,    74,    71,    72,
      76,    84,    94,     0,    97,   101,   106,   109,   114,   117,
     119,   121,   123,   125,   127,   130,   135,     8,     0,     0,
      23,     0,    19,    22,    27,     0,     0,    29,    25,     0,
       0,    85,    86,     0,     0,    80,    81,     0,     0,   132,
     133,   134,     0,    94,    87,     0,     0,     0,   105,   104,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    24,    26,     0,
      20,    31,     0,     0,    28,     0,     0,     0,     0,     0,
      42,     0,     0,     0,     0,    66,     0,     0,    44,    35,
      39,    40,    41,    38,     0,     0,     0,     0,    75,    78,
       0,    82,     0,   131,    98,    99,   100,   103,   102,   108,
     107,   110,   111,   112,   113,   115,   116,   118,   120,   122,
     124,   126,     0,   136,     0,     0,     0,    32,    30,    52,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      61,    36,    67,     0,    43,    96,     0,     0,    79,    77,
     129,     0,    62,     0,     0,     0,    53,     0,     0,    49,
       0,     0,     0,    37,     0,     0,     0,    63,    95,    83,
     128,    64,    33,     0,     0,     0,     0,    50,     0,     0,
       0,     0,     0,     0,    34,     0,    45,     0,     0,    54,
      59,    56,     0,     0,     0,    51,     0,    47,     0,     0,
      60,    57,     0,    46,    48,    55,     0,    58
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -120,  -120,  -120,  -120,   229,  -120,   -61,     9,     7,  -120,
     -17,  -120,  -120,   209,  -120,   115,  -109,  -119,   -78,  -120,
      30,  -120,  -120,  -120,  -120,  -120,   220,   122,  -120,  -120,
    -120,  -120,   -33,  -120,   -47,    89,    83,  -120,  -120,    29,
      86,   135,   137,   130,   142,   129,  -120,    45,  -120,   -31,
    -120,   -23
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,     8,     9,    10,   136,    19,    20,
      21,    22,    12,    33,    76,    77,   137,   138,   139,   140,
     210,   141,   142,   143,   231,    13,    23,   144,    49,    50,
      51,   150,    52,    53,    54,    55,    56,   100,   101,    57,
      58,    59,    60,    61,    62,    63,    64,    65,   201,    66,
      92,   145
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      73,    67,    27,    68,    81,    82,    94,   181,    17,    11,
     174,    17,   114,    72,   116,    14,    11,    15,   135,    84,
      93,   117,   185,   116,    25,    24,    17,    78,    17,   116,
     199,   123,    79,   115,   124,   193,   222,    71,     1,     2,
       3,    75,     1,     2,     3,    17,    29,    30,   154,   155,
     156,    83,    18,   146,   120,    70,   151,    84,   135,   191,
      18,   153,    93,    93,    93,   152,   203,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,   122,   192,   116,   173,    74,    31,     4,   121,
     147,   234,   172,    85,    86,   118,   191,   -65,   110,   195,
     119,    26,   180,    98,    99,   116,   236,   191,   148,   239,
      95,    96,    97,    93,   192,   191,    87,    32,   247,   111,
      88,   104,   105,   106,   107,   191,   102,   103,   197,   254,
     255,   198,    75,   161,   162,   163,   164,   116,   116,   229,
     225,   228,   230,   189,   116,   242,   112,   233,   243,   218,
     116,   116,   116,   204,   246,   248,    89,    90,    91,   208,
     211,   212,    26,    93,   113,   216,   219,    70,    93,     1,
       2,     3,    27,   108,   109,   194,   116,   116,   200,   206,
     116,   176,   223,   227,   116,   159,   160,   211,   177,   157,
     158,   131,   182,   183,   165,   166,   184,   186,   240,   187,
     188,   235,   196,   238,     1,     2,     3,   125,   205,   207,
     224,   250,   126,   127,   128,   129,   232,   241,   244,    34,
      35,    36,   214,   215,    37,    38,    39,   245,    40,   249,
      41,   251,   252,   253,   256,   257,    16,    69,   178,    28,
     226,   175,   169,   171,   130,   167,   220,    42,   168,   131,
       0,     1,     2,     3,     0,   170,   132,   133,     0,   134,
      43,    44,    45,    46,    47,    48,    34,    35,    36,     0,
       0,    37,    38,    39,     0,    40,     0,    41,   125,     0,
       0,     0,     0,   126,   127,   128,   129,     0,     0,     0,
      34,    35,    36,     0,    42,    37,    38,    39,     0,    40,
       0,    41,     0,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,     0,     0,   130,     0,     0,    42,     0,
     131,   190,     0,     0,     0,     0,     0,   132,   133,     0,
     134,    43,    44,    45,    46,    47,    48,   125,     0,     0,
       0,     0,   126,   127,   128,   129,     0,     0,     0,    34,
      35,    36,     0,     0,    37,    38,    39,     0,    40,     0,
      41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   130,     0,     0,    42,     0,   131,
     202,     0,     0,     0,     0,     0,   132,   133,     0,   134,
      43,    44,    45,    46,    47,    48,   125,     0,     0,     0,
       0,   126,   127,   128,   129,     0,     0,     0,    34,    35,
      36,     0,     0,    37,    38,    39,     0,    40,     0,    41,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   130,     0,     0,    42,     0,   131,   213,
       0,     0,     0,     0,     0,   132,   133,     0,   134,    43,
      44,    45,    46,    47,    48,   125,     0,     0,     0,     0,
     126,   127,   128,   129,     0,     0,     0,    34,    35,    36,
       0,     0,    37,    38,    39,     0,    40,     0,    41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,     0,     0,    42,     0,   131,   217,     0,
       0,     0,     0,     0,   132,   133,     0,   134,    43,    44,
      45,    46,    47,    48,   125,     0,     0,     0,     0,   126,
     127,   128,   129,     0,     0,     0,    34,    35,    36,     0,
       0,    37,    38,    39,     0,    40,     0,    41,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   130,     0,     0,    42,     0,   131,   221,     0,     0,
       0,     0,     0,   132,   133,     0,   134,    43,    44,    45,
      46,    47,    48,   125,     0,     0,     0,     0,   126,   127,
     128,   129,     0,     0,     0,    34,    35,    36,     0,     0,
      37,    38,    39,     0,    40,     0,    41,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     130,     0,     0,    42,     0,   131,     0,     0,     0,     0,
       0,     0,   132,   133,     0,   134,    43,    44,    45,    46,
      47,    48,    34,    35,    36,     0,     0,    37,    38,    39,
       0,    40,     0,    41,    34,    35,    36,     0,     0,    37,
      38,    39,     0,    40,     0,    41,     0,     0,     0,     0,
      42,   149,     0,     0,     0,     0,     0,     0,     0,   179,
       0,     0,    42,    43,    44,    45,    46,    47,    48,     0,
       0,     0,     0,     0,     0,    43,    44,    45,    46,    47,
      48,    34,    35,    36,     0,     0,    37,    38,    39,     0,
      40,     0,    41,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   209,     0,     0,    42,
      34,    35,    36,     0,     0,    37,    38,    39,     0,    40,
       0,    41,    43,    44,    45,    46,    47,    48,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,    42,   237,
      37,    38,    39,     0,    40,     0,    41,     0,     0,     0,
       0,    43,    44,    45,    46,    47,    48,     0,     0,    34,
      35,    36,     0,    42,    37,    38,    39,     0,    40,     0,
      41,     0,     0,     0,     0,     0,    43,    44,    45,    46,
      47,    48,     0,     0,     0,     0,     0,    80,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      43,    44,    45,    46,    47,    48
};

static const yytype_int16 yycheck[] =
{
      31,    24,    19,    26,    37,    38,    53,   126,    20,     0,
     119,    20,    31,    30,    44,    57,     7,     0,    79,    42,
      53,    51,   131,    44,    17,    64,    20,    43,    20,    44,
      51,    44,    48,    52,    47,   144,    51,    30,     3,     4,
       5,    32,     3,     4,     5,    20,    43,    44,    95,    96,
      97,    42,    64,    47,    71,    64,    87,    80,   119,   137,
      64,    92,    95,    96,    97,    88,   175,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,    75,   144,    44,   116,    47,    40,    53,    64,
      83,    51,   115,    23,    24,    43,   174,    46,    25,   146,
      48,    50,   125,    18,    19,    44,   225,   185,    47,   228,
      20,    21,    22,   146,   175,   193,    46,    46,   237,    28,
      50,    34,    35,    36,    37,   203,    38,    39,    44,   248,
     249,    47,   123,   104,   105,   106,   107,    44,    44,    44,
      47,    47,    47,   136,    44,    44,    26,    47,    47,   196,
      44,    44,    44,   176,    47,    47,    40,    41,    42,   182,
     183,   184,    50,   196,    30,   188,   197,    64,   201,     3,
       4,     5,   189,    32,    33,    43,    44,    44,    45,    43,
      44,    50,   205,    43,    44,   102,   103,   210,    64,   100,
     101,    48,    46,    46,   108,   109,    46,    46,   229,    46,
      46,   224,    47,   226,     3,     4,     5,     6,    50,    12,
      46,   242,    11,    12,    13,    14,    44,    43,    25,    18,
      19,    20,    63,    63,    23,    24,    25,    43,    27,    15,
      29,    43,    64,    43,    47,    43,     7,    28,   123,    19,
     210,   119,   112,   114,    43,   110,   201,    46,   111,    48,
      -1,     3,     4,     5,    -1,   113,    55,    56,    -1,    58,
      59,    60,    61,    62,    63,    64,    18,    19,    20,    -1,
      -1,    23,    24,    25,    -1,    27,    -1,    29,     6,    -1,
      -1,    -1,    -1,    11,    12,    13,    14,    -1,    -1,    -1,
      18,    19,    20,    -1,    46,    23,    24,    25,    -1,    27,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,
      62,    63,    64,    -1,    -1,    43,    -1,    -1,    46,    -1,
      48,    49,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,
      58,    59,    60,    61,    62,    63,    64,     6,    -1,    -1,
      -1,    -1,    11,    12,    13,    14,    -1,    -1,    -1,    18,
      19,    20,    -1,    -1,    23,    24,    25,    -1,    27,    -1,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    -1,    48,
      49,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    58,
      59,    60,    61,    62,    63,    64,     6,    -1,    -1,    -1,
      -1,    11,    12,    13,    14,    -1,    -1,    -1,    18,    19,
      20,    -1,    -1,    23,    24,    25,    -1,    27,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    46,    -1,    48,    49,
      -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    58,    59,
      60,    61,    62,    63,    64,     6,    -1,    -1,    -1,    -1,
      11,    12,    13,    14,    -1,    -1,    -1,    18,    19,    20,
      -1,    -1,    23,    24,    25,    -1,    27,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    -1,    46,    -1,    48,    49,    -1,
      -1,    -1,    -1,    -1,    55,    56,    -1,    58,    59,    60,
      61,    62,    63,    64,     6,    -1,    -1,    -1,    -1,    11,
      12,    13,    14,    -1,    -1,    -1,    18,    19,    20,    -1,
      -1,    23,    24,    25,    -1,    27,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    -1,    46,    -1,    48,    49,    -1,    -1,
      -1,    -1,    -1,    55,    56,    -1,    58,    59,    60,    61,
      62,    63,    64,     6,    -1,    -1,    -1,    -1,    11,    12,
      13,    14,    -1,    -1,    -1,    18,    19,    20,    -1,    -1,
      23,    24,    25,    -1,    27,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    -1,    -1,    46,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    -1,    58,    59,    60,    61,    62,
      63,    64,    18,    19,    20,    -1,    -1,    23,    24,    25,
      -1,    27,    -1,    29,    18,    19,    20,    -1,    -1,    23,
      24,    25,    -1,    27,    -1,    29,    -1,    -1,    -1,    -1,
      46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    46,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    18,    19,    20,    -1,    -1,    23,    24,    25,    -1,
      27,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,    46,
      18,    19,    20,    -1,    -1,    23,    24,    25,    -1,    27,
      -1,    29,    59,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    18,    19,    20,    46,    47,
      23,    24,    25,    -1,    27,    -1,    29,    -1,    -1,    -1,
      -1,    59,    60,    61,    62,    63,    64,    -1,    -1,    18,
      19,    20,    -1,    46,    23,    24,    25,    -1,    27,    -1,
      29,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    61,    62,    63,    64
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,    53,    68,    69,    70,    71,    72,
      73,    74,    79,    92,    57,     0,    71,    20,    64,    75,
      76,    77,    78,    93,    64,    75,    50,    77,    93,    43,
      44,    40,    46,    80,    18,    19,    20,    23,    24,    25,
      27,    29,    46,    59,    60,    61,    62,    63,    64,    95,
      96,    97,    99,   100,   101,   102,   103,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   116,   118,   118,    80,
      64,    75,    77,   116,    47,    74,    81,    82,    43,    48,
      46,    99,    99,    74,   118,    23,    24,    46,    50,    40,
      41,    42,   117,    99,   101,    20,    21,    22,    18,    19,
     104,   105,    38,    39,    34,    35,    36,    37,    32,    33,
      25,    28,    26,    30,    31,    52,    44,    51,    43,    48,
      77,    64,    75,    44,    47,     6,    11,    12,    13,    14,
      43,    48,    55,    56,    58,    73,    74,    83,    84,    85,
      86,    88,    89,    90,    94,   118,    47,    75,    47,    47,
      98,   116,   118,   116,   101,   101,   101,   102,   102,   103,
     103,   106,   106,   106,   106,   107,   107,   108,   109,   110,
     111,   112,   118,   116,    83,    94,    50,    64,    82,    43,
     118,    84,    46,    46,    46,    83,    46,    46,    46,    75,
      49,    85,    73,    83,    43,   101,    47,    44,    47,    51,
      45,   115,    49,    83,   118,    50,    43,    12,   118,    43,
      87,   118,   118,    49,    63,    63,   118,    49,   101,   116,
     114,    49,    51,   118,    46,    47,    87,    43,    47,    44,
      47,    91,    44,    47,    51,   118,    84,    47,   118,    84,
     116,    43,    44,    47,    25,    43,    47,    84,    47,    15,
     116,    43,    64,    43,    84,    84,    47,    43
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    67,    68,    69,    70,    70,    71,    71,    72,    72,
      72,    73,    74,    74,    74,    75,    75,    76,    76,    76,
      76,    77,    77,    78,    78,    79,    79,    80,    80,    81,
      81,    82,    82,    82,    82,    83,    83,    84,    85,    85,
      85,    85,    85,    85,    85,    86,    86,    86,    86,    87,
      87,    88,    88,    88,    89,    89,    90,    90,    90,    91,
      91,    92,    92,    92,    92,    93,    94,    94,    95,    95,
      95,    96,    96,    96,    96,    96,    97,    97,    97,    97,
      97,    97,    98,    98,    99,    99,    99,    99,   100,   100,
     100,   100,   100,   100,   101,   101,   101,   102,   102,   102,
     102,   103,   103,   103,   104,   105,   106,   106,   106,   107,
     107,   107,   107,   107,   108,   108,   108,   109,   109,   110,
     110,   111,   111,   112,   112,   113,   113,   114,   114,   115,
     116,   116,   117,   117,   117,   118,   118
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     1,     1,     4,     1,
       1,     3,     1,     1,     1,     1,     2,     1,     2,     3,
       4,     1,     3,     1,     4,     4,     5,     2,     3,     1,
       3,     2,     3,     5,     6,     1,     2,     3,     1,     1,
       1,     1,     1,     2,     1,     5,     7,     6,     7,     1,
       2,     5,     2,     3,     5,     7,     5,     6,     8,     2,
       3,     6,     7,     7,     8,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     4,     3,     4,
       2,     2,     1,     3,     1,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     5,     4,     1,     3,     3,
       3,     1,     3,     3,     1,     1,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     5,     1,
       1,     3,     1,     1,     1,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
      YYSIZE_T yyn = 0;
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 2:
#line 166 "sintatico.y" /* yacc.c:1646  */
    {
		//Print-Debug
		//printfProgram(program, table);
		semanticError(program, table);
		printfError();
		
		}
#line 1628 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 185 "sintatico.y" /* yacc.c:1646  */
    {
		addProgram(program, (yyvsp[0].fun));
	}
#line 1636 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 192 "sintatico.y" /* yacc.c:1646  */
    {
		addTableVariable(table, createVariable(ID_CONS_DEFINE, NULL, (yyvsp[-1].str), NULL, (yyvsp[0].ast), define_line,col,linha_toda));
	}
#line 1644 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 195 "sintatico.y" /* yacc.c:1646  */
    {
		addTableVariable(table, (yyvsp[0].var));
	}
#line 1652 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 198 "sintatico.y" /* yacc.c:1646  */
    {
		addTableFunction(table, (yyvsp[0].fun));
	}
#line 1660 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 204 "sintatico.y" /* yacc.c:1646  */
    {
		setVariableListType((yyvsp[-2].ast), (yyvsp[-1].var));
		(yyval.var) = (yyvsp[-1].var);
	}
#line 1669 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 211 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(VOID, 0, NULL, lines + 1,col,linha_toda);
	}
#line 1677 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 214 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(CHAR, 0, NULL, lines + 1,col,linha_toda);
	}
#line 1685 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 217 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(INT, 0, NULL, lines + 1,col,linha_toda);
	}
#line 1693 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 223 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(AST_POINTER, 0, "*", lines + 1,col,linha_toda);
	}
#line 1701 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 226 "sintatico.y" /* yacc.c:1646  */
    {
		int i;
		char *pointers;
		pointers = (char *) malloc((strlen(getValueString((yyvsp[0].ast))) + 2) * sizeof(char));
		for (i=0; i<strlen(getValueString((yyvsp[0].ast))); i++){
			pointers[i] = '*';		
		}
		pointers[i] = '*';
		pointers[i + 1] = '\0';
		(yyval.ast) = createNode(AST_POINTER, 0, pointers, lines + 1,col,linha_toda);
	}
#line 1717 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 240 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.var) = (yyvsp[0].var);
	}
#line 1725 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 243 "sintatico.y" /* yacc.c:1646  */
    {
		setVariablePointer((yyvsp[0].var), (yyvsp[-1].ast));
		(yyval.var) = (yyvsp[0].var);
	}
#line 1734 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 247 "sintatico.y" /* yacc.c:1646  */
    {
		addVariable((yyvsp[-2].var), (yyvsp[0].var));
		(yyval.var) = (yyvsp[-2].var);
	}
#line 1743 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 251 "sintatico.y" /* yacc.c:1646  */
    {
		setVariablePointer((yyvsp[0].var), (yyvsp[-1].ast));
		addVariable((yyvsp[-3].var), (yyvsp[0].var));
		(yyval.var) = (yyvsp[-3].var);
	}
#line 1753 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 259 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.var) = (yyvsp[0].var);
	}
#line 1761 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 262 "sintatico.y" /* yacc.c:1646  */
    {
		setVariableValue((yyvsp[-2].var), (yyvsp[0].ast));
		(yyval.var) = (yyvsp[-2].var);
	}
#line 1770 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 269 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.var) = createVariable(0, NULL, (yyvsp[0].str), NULL, NULL, popStack(),col,linha_toda);
	}
#line 1778 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 272 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.var) = createVariable(0, NULL, (yyvsp[-3].str), (yyvsp[-1].ast), NULL, popStack(),col,linha_toda);
	}
#line 1786 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 278 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.fun) = createFunction((yyvsp[-3].ast), NULL, (yyvsp[-2].str), (yyvsp[-1].var), NULL, NULL, popStack(),col_last_id);
	}
#line 1794 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 281 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.fun) = createFunction((yyvsp[-4].ast), (yyvsp[-3].ast), (yyvsp[-2].str), (yyvsp[-1].var), NULL, NULL, popStack(),col_last_id);
	}
#line 1802 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 287 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.var) = NULL;
	}
#line 1810 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 290 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.var) = (yyvsp[-1].var);
	}
#line 1818 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 296 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.var) = (yyvsp[0].var);
	}
#line 1826 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 299 "sintatico.y" /* yacc.c:1646  */
    {
		addVariable((yyvsp[-2].var), (yyvsp[0].var));
		(yyval.var) = (yyvsp[-2].var);
	}
#line 1835 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 306 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.var) = createVariable(getType((yyvsp[-1].ast)), NULL, (yyvsp[0].str), NULL, NULL, popStack(),col,linha_toda);
	}
#line 1843 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 309 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.var) = createVariable(getType((yyvsp[-2].ast)), (yyvsp[-1].ast), (yyvsp[0].str), NULL, NULL, popStack(),col,linha_toda);
	}
#line 1851 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 312 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.var) = createVariable(getType((yyvsp[-4].ast)), NULL, (yyvsp[-3].str), (yyvsp[-1].ast), NULL, popStack(),col,linha_toda);
	}
#line 1859 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 315 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.var) = createVariable(getType((yyvsp[-5].ast)), (yyvsp[-4].ast), (yyvsp[-3].str), (yyvsp[-1].ast), NULL, popStack(),col,linha_toda);
	}
#line 1867 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 320 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = (yyvsp[0].cmd);
	}
#line 1875 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 323 "sintatico.y" /* yacc.c:1646  */
    {
		addCmdList((yyvsp[-1].cmd), (yyvsp[0].cmd));
		(yyval.cmd) = (yyvsp[-1].cmd);
	}
#line 1884 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 329 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = (yyvsp[-1].cmd);
	}
#line 1892 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 335 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = (yyvsp[0].cmd);
	}
#line 1900 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 338 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = (yyvsp[0].cmd);
	}
#line 1908 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 341 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = (yyvsp[0].cmd);
	}
#line 1916 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 344 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = (yyvsp[0].cmd);
	}
#line 1924 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 347 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = createNullCmd();
	}
#line 1932 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 350 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = createExpression((yyvsp[-1].ast));
	}
#line 1940 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 353 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = (yyvsp[0].cmd);
	}
#line 1948 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 360 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = createWhile((yyvsp[-2].ast), (yyvsp[0].cmd));
	}
#line 1956 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 363 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = createDo((yyvsp[-5].cmd), (yyvsp[-2].ast));
	}
#line 1964 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 366 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = createFor((yyvsp[-3].cmd), (yyvsp[-2].cmd), NULL, (yyvsp[0].cmd));
	}
#line 1972 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 369 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = createFor((yyvsp[-4].cmd), (yyvsp[-3].cmd), (yyvsp[-2].ast), (yyvsp[0].cmd));
	}
#line 1980 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 375 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = createNullCmd();
	}
#line 1988 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 378 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = createExpression((yyvsp[-1].ast));
	}
#line 1996 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 384 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = createExit((yyvsp[-2].ast));
	}
#line 2004 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 387 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = createReturn(NULL, lines + 1,col,linha_toda);
	}
#line 2012 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 390 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = createReturn((yyvsp[-1].ast), lines + 1,col,linha_toda);
	}
#line 2020 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 396 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = createIf((yyvsp[-2].ast), (yyvsp[0].cmd), NULL);
	}
#line 2028 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 399 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = createIf((yyvsp[-4].ast), (yyvsp[-2].cmd), (yyvsp[0].cmd));
	}
#line 2036 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 405 "sintatico.y" /* yacc.c:1646  */
    {
		Node *node;
		node = createNode(STRING, 0, (yyvsp[-2].str), lines + 1,col,linha_toda);
		setPointerString(node);
		(yyval.cmd) = createPrintf(node, NULL);
	}
#line 2047 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 411 "sintatico.y" /* yacc.c:1646  */
    {
		Node *node;
		node = createNode(STRING, 0, (yyvsp[-3].str), lines + 1,col,linha_toda);
		setPointerString(node);
		(yyval.cmd) = createPrintf(node, (yyvsp[-2].cmd));
	}
#line 2058 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 417 "sintatico.y" /* yacc.c:1646  */
    {
		Node *node;
		node = createNode(STRING, 0, (yyvsp[-5].str), lines + 1,col,linha_toda);
		setPointerString(node);
		(yyval.cmd) = createScanf(node, createNode(IDENTIFIER, 0, (yyvsp[-2].str), lines + 1,col,linha_toda));
	}
#line 2069 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 425 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = createExpression((yyvsp[0].ast));
	}
#line 2077 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 428 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.cmd) = createExpression(createTreeNode(COMMA, 0, NULL, getExpNode((yyvsp[-2].cmd)), (yyvsp[0].ast), lines + 1,col,linha_toda));
	}
#line 2085 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 434 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.fun) = createFunction((yyvsp[-5].ast), NULL, (yyvsp[-4].str), (yyvsp[-3].var), NULL, (yyvsp[-1].cmd), popStack(),col_last_id);
	}
#line 2093 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 437 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.fun) = createFunction((yyvsp[-6].ast), (yyvsp[-5].ast), (yyvsp[-4].str), (yyvsp[-3].var), NULL, (yyvsp[-1].cmd), popStack(),col_last_id);
	}
#line 2101 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 440 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.fun) = createFunction((yyvsp[-6].ast), NULL, (yyvsp[-5].str), (yyvsp[-4].var), (yyvsp[-2].var), (yyvsp[-1].cmd), popStack(),col_last_id);
	}
#line 2109 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 443 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.fun) = createFunction((yyvsp[-7].ast), (yyvsp[-6].ast), (yyvsp[-5].str), (yyvsp[-4].var), (yyvsp[-2].var), (yyvsp[-1].cmd), popStack(),col_last_id);
	}
#line 2117 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 448 "sintatico.y" /* yacc.c:1646  */
    {(yyval.str) = (yyvsp[0].str);col_last_id = col;}
#line 2123 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 452 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.var) = (yyvsp[0].var);	
	}
#line 2131 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 455 "sintatico.y" /* yacc.c:1646  */
    {
		addVariable((yyvsp[-1].var), (yyvsp[0].var));
		(yyval.var) = (yyvsp[-1].var);
	}
#line 2140 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 462 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(NUM_INTEGER, (yyvsp[0].num), NULL, lines + 1,col,linha_toda);
	}
#line 2148 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 465 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(NUM_OCTAL, (yyvsp[0].num), NULL, lines + 1,col,linha_toda);
	}
#line 2156 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 468 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(NUM_HEXA, (yyvsp[0].num), NULL, lines + 1,col,linha_toda);
	}
#line 2164 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 474 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(IDENTIFIER, 0, (yyvsp[0].str), lines + 1,col,linha_toda);
	}
#line 2172 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 477 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2180 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 480 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(CHARACTER, 0, (yyvsp[0].str), lines + 1,col,linha_toda);
	}
#line 2188 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 483 "sintatico.y" /* yacc.c:1646  */
    {
		Node *node;
		node = createNode(STRING, 0, (yyvsp[0].str), lines + 1,col,linha_toda);
		setPointerString(node);
		(yyval.ast) = node;
	}
#line 2199 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 489 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
	}
#line 2207 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 495 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2215 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 498 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(AST_POSTFIX_EXPRESSION, 0, NULL, (yyvsp[-3].ast), (yyvsp[-1].ast), lines + 1,col,linha_toda);
	}
#line 2223 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 501 "sintatico.y" /* yacc.c:1646  */
    {
		setNodeType((yyvsp[-2].ast), ID_FUNCTION_CALL);
		(yyval.ast) = (yyvsp[-2].ast);
	}
#line 2232 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 505 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(ID_FUNCTION_CALL, 0, NULL, (yyvsp[-3].ast), (yyvsp[-1].ast), lines + 1,col,linha_toda);
	}
#line 2240 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 508 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(INC, 0, NULL, (yyvsp[-1].ast), NULL, lines + 1,col,linha_toda);
	}
#line 2248 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 511 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(DEC, 0, NULL, (yyvsp[-1].ast), NULL, lines + 1,col,linha_toda);
	}
#line 2256 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 517 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2264 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 520 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(COMMA, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2272 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 526 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2280 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 529 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(INC, 0, NULL, (yyvsp[0].ast), NULL, lines + 1,col,linha_toda);
	}
#line 2288 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 532 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(DEC, 0, NULL, (yyvsp[0].ast), NULL, lines + 1,col,linha_toda);
	}
#line 2296 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 535 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(AST_UNARY_EXPRESSION, 0, NULL, (yyvsp[-1].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2304 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 541 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(BITWISE_AND, 0, NULL, lines + 1,col,linha_toda);
	}
#line 2312 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 544 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(MULTIPLY, 0, NULL, lines + 1,col,linha_toda);
	}
#line 2320 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 547 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(PLUS, 0, NULL, lines + 1,col,linha_toda);
	}
#line 2328 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 550 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(MINUS, 0, NULL, lines + 1,col,linha_toda);
	}
#line 2336 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 553 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(BITWISE_NOT, 0, NULL, lines + 1,col,linha_toda);
	}
#line 2344 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 556 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(NOT, 0, NULL, lines + 1,col,linha_toda);
	}
#line 2352 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 562 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2360 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 565 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(AST_CAST, 0, getValueString((yyvsp[-2].ast)), (yyvsp[-3].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);	
	}
#line 2368 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 568 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(AST_CAST, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);	
	}
#line 2376 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 574 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2384 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 577 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(MULTIPLY, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2392 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 580 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(DIV, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2400 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 583 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(REMAINDER, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2408 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 589 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2416 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 592 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(PLUS, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,(yyvsp[-1].num),linha_toda);
	}
#line 2424 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 595 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(MINUS, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,(yyvsp[-1].num),linha_toda);
	}
#line 2432 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 600 "sintatico.y" /* yacc.c:1646  */
    {(yyval.num) = col;}
#line 2438 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 604 "sintatico.y" /* yacc.c:1646  */
    {		
		(yyval.num)=col;
	}
#line 2446 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 611 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2454 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 614 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(L_SHIFT, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2462 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 617 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(R_SHIFT, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2470 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 623 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2478 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 626 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(LESS_THAN, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2486 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 629 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(GREATER_THAN, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2494 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 632 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(LESS_EQUAL, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2502 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 635 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(GREATER_EQUAL, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2510 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 641 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2518 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 644 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(EQUAL, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2526 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 647 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(NOT_EQUAL, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2534 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 653 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2542 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 656 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(BITWISE_AND, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2550 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 662 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2558 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 665 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(BITWISE_XOR, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2566 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 671 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2574 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 674 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(BITWISE_OR, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2582 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 680 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2590 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 683 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(LOGICAL_AND, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2598 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 689 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2606 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 692 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(LOGICAL_OR, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2614 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 698 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2622 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 701 "sintatico.y" /* yacc.c:1646  */
    {
		Node *node;
		node = createTreeNode(COLON, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,(yyvsp[-1].num),linha_toda);
		(yyval.ast) = createTreeNode(TERNARY_CONDITIONAL, 0, NULL, (yyvsp[-4].ast), node, lines + 1,(yyvsp[-1].num),linha_toda);
	}
#line 2632 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 708 "sintatico.y" /* yacc.c:1646  */
    {(yyval.num) = col;}
#line 2638 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 712 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2646 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 715 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(getType((yyvsp[-1].ast)), 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,getNodeColuna((yyvsp[-2].ast)),linha_toda);
	}
#line 2654 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 721 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(ASSIGN, 0, NULL, lines + 1,col,linha_toda);
	}
#line 2662 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 724 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(ADD_ASSIGN, 0, NULL, lines + 1,col,linha_toda);
	}
#line 2670 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 727 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createNode(MINUS_ASSIGN, 0, NULL, lines + 1,col,linha_toda);
	}
#line 2678 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 733 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2686 "sintatico.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 736 "sintatico.y" /* yacc.c:1646  */
    {
		(yyval.ast) = createTreeNode(COMMA, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), lines + 1,col,linha_toda);
	}
#line 2694 "sintatico.tab.c" /* yacc.c:1646  */
    break;


#line 2698 "sintatico.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 741 "sintatico.y" /* yacc.c:1906  */


void yyerror(char *s)
{
	int token_atual;
	quebra_linha = 0;
	char linha_atual_aux[5000000];
	char token_text[4096];
	token_text[0]='\0';
	strcpy(token_text,yytext);
	linha_atual_aux[0]='\0';
	int tab_atual = tab;
	int copiar = 1;
	int col_local = col;
	int linha_local = lines;
	int entrou = 0;
	while((token_atual = yylex())!=0){
		entrou = 1;
		if(quebra_linha == 1 && copiar){
			strcpy(linha_atual_aux,linha_atual);
			copiar = 0;
		}
	}
	if(linha_atual_aux[0]=='\0'){
		strcpy(linha_atual_aux,linha_atual);
	}
	
	int tam = strlen(token_text);
	fprintf(stdout, "error:syntax:%d:%d: %s\n", linha_local+1, col_local-tam,token_text);
	fprintf(stdout,"%s\n",linha_atual_aux);
	int tabulacoes = 0;
	tab = tab_atual;
	for(tabulacoes =0;tabulacoes < tab;tabulacoes++){
		fprintf(stdout,"\t");
		tam++;
	}	
	fprintf(stdout,"%*s",col_local-tam,"^");

	exit(0);
}

int main(int argc, char **argv)
{
	yydebug = 0;
	char aux[5000];
	program = createProgram();
	table = createTable();
	stack_line = createStack(-1);
	error_list = createError(-1, NULL);
	warning_list = createError(-1, NULL);
	warning = 0;
	FILE *f;
	f = fopen("gambiarra.txt","w");
	while(!feof(stdin))
	{
		fgets(aux,5000,stdin);
		fprintf(f,"%s",aux);
	}
	fclose(f);
	yyin = fopen("gambiarra.txt", "r");
    
	yyparse();
	if(warning)
	{
		printf("\n");
	}
	printf("SUCCESSFUL COMPILATION.");
	fclose(yyin);
}
