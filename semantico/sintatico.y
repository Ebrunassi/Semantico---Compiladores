%{

#include <stdlib.h>
#include <stdio.h>
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

%}
%union{
	Function *fun;
	Variable *var;
	CmdList *cmd;
	Node *ast;
	char *str;
	int num;

}
%token VOID
%token INT
%token CHAR
%token RETURN
%token BREAK
%token SWITCH
%token CASE
%token DEFAULT
%token DO
%token WHILE
%token FOR
%token IF
%token ELSE
%token TYPEDEF
%token STRUCT
%token PLUS
%token MINUS
%token MULTIPLY
%token DIV
%token REMAINDER
%token INC
%token DEC
%token BITWISE_AND
%token BITWISE_OR
%token BITWISE_NOT
%token BITWISE_XOR
%token NOT
%token LOGICAL_AND
%token LOGICAL_OR
%token EQUAL
%token NOT_EQUAL
%token LESS_THAN
%token GREATER_THAN
%token LESS_EQUAL
%token GREATER_EQUAL
%token R_SHIFT
%token L_SHIFT
%token ASSIGN
%token ADD_ASSIGN
%token MINUS_ASSIGN
%token SEMICOLON
%token COMMA
%token COLON
%token L_PAREN
%token R_PAREN
%token L_CURLY_BRACKET
%token R_CURLY_BRACKET
%token L_SQUARE_BRACKET
%token R_SQUARE_BRACKET
%token TERNARY_CONDITIONAL
%token NUMBER_SIGN
%token POINTER
%token PRINTF
%token SCANF
%token DEFINE
%token EXIT
%token NUM_HEXA
%token NUM_OCTAL
%token NUM_INTEGER
%token CHARACTER
%token STRING
%token IDENTIFIER
%token BREAKLINE
%token END_OF_FILE
%type <str> idf
%type <num> plus
%type <num> minus
%type <num> colon
%type <ast> expression
%type <ast> assignment_operator
%type <ast> assignment_expression
%type <ast> conditional_expression
%type <ast> logical_or_expression
%type <ast> logical_and_expression
%type <ast> inclusive_or_expression
%type <ast> exclusive_or_expression
%type <ast> and_expression
%type <ast> equality_expression
%type <ast> relational_expression
%type <ast> shift_expression
%type <ast> additive_expression
%type <ast> multiplicative_expression
%type <ast> cast_expression
%type <ast> unary_operator
%type <ast> unary_expression
%type <ast> argument_expression_list
%type <ast> postfix_expression
%type <ast> primary_expression
%type <ast> number
%type <ast> type
%type <ast> pointer

%type <cmd> comandos
%type <cmd> command_list
%type <cmd> bloco
%type <cmd> io_command
%type <cmd> loop_command
%type <cmd> jump_command
%type <cmd> conditional_command
%type <cmd> expr_stat
%type <cmd> print_stat

%type <fun> prototip_declarations_unit
%type <fun> function_declarations

%type <var> parametros
%type <var> parameter_list
%type <var> parameter
%type <var> var_list
%type <var> var_declarations_unit
%type <var> init_desc
%type <var> init_decla
%type <var> decla

%type <num> NUM_INTEGER
%type <num> NUM_OCTAL
%type <num> NUM_HEXA
%type <str> IDENTIFIER
%type <str> STRING
%type <str> CHARACTER
%debug
%start start
%%
start : s {
		//Print-Debug
		//printfProgram(program, table);
		semanticError(program, table);
		printfError();
		
		}
		
	
;

s: program;

program: 
	declarations		
	| program declarations  
;

declarations: 
	function_declarations {
		addProgram(program, $1);
	}
	|     declarations_unit    
;

declarations_unit:
	NUMBER_SIGN DEFINE IDENTIFIER expression {
		addTableVariable(table, createVariable(ID_CONS_DEFINE, NULL, $3, NULL, $4, define_line,col,linha_toda));
	}
	| var_declarations_unit {
		addTableVariable(table, $1);
	}
	| prototip_declarations_unit {
		addTableFunction(table, $1);
	}
;

var_declarations_unit:
	type init_desc SEMICOLON{
		setVariableListType($1, $2);
		$$ = $2;
	}
;

type:
	VOID {
		$$ = createNode(VOID, 0, NULL, lines + 1,col,linha_toda);
	}
	| CHAR {
		$$ = createNode(CHAR, 0, NULL, lines + 1,col,linha_toda);
	}
	| INT {
		$$ = createNode(INT, 0, NULL, lines + 1,col,linha_toda);
	}
;

pointer:
	MULTIPLY {
		$$ = createNode(AST_POINTER, 0, "*", lines + 1,col,linha_toda);
	}
	| MULTIPLY pointer {
		int i;
		char *pointers;
		pointers = (char *) malloc((strlen(getValueString($2)) + 2) * sizeof(char));
		for (i=0; i<strlen(getValueString($2)); i++){
			pointers[i] = '*';		
		}
		pointers[i] = '*';
		pointers[i + 1] = '\0';
		$$ = createNode(AST_POINTER, 0, pointers, lines + 1,col,linha_toda);
	}
;

init_desc:
	init_decla {
		$$ = $1;
	}
	| pointer init_decla {
		setVariablePointer($2, $1);
		$$ = $2;
	} 
	| init_desc COMMA init_decla {
		addVariable($1, $3);
		$$ = $1;
	}
	| init_desc COMMA pointer init_decla{
		setVariablePointer($4, $3);
		addVariable($1, $4);
		$$ = $1;
	}
;

init_decla:
	decla {
		$$ = $1;
	}
	| decla ASSIGN assignment_expression {
		setVariableValue($1, $3);
		$$ = $1;
	}
;

decla:
	IDENTIFIER {
		$$ = createVariable(0, NULL, $1, NULL, NULL, popStack(),col,linha_toda);
	}
	| IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET {
		$$ = createVariable(0, NULL, $1, $3, NULL, popStack(),col,linha_toda);
	}
;

prototip_declarations_unit:
	type idf parametros SEMICOLON {
		$$ = createFunction($1, NULL, $2, $3, NULL, NULL, popStack(),col_last_id);
	}
	| type pointer idf parametros SEMICOLON {
		$$ = createFunction($1, $2, $3, $4, NULL, NULL, popStack(),col_last_id);
	}
;

parametros:
	L_PAREN R_PAREN {
		$$ = NULL;
	}
	| L_PAREN parameter_list R_PAREN {
		$$ = $2;
	}
;

parameter_list:
	parameter {
		$$ = $1;
	}
	| parameter_list COMMA parameter {
		addVariable($1, $3);
		$$ = $1;
	}
;

parameter:
	type IDENTIFIER {
		$$ = createVariable(getType($1), NULL, $2, NULL, NULL, popStack(),col,linha_toda);
	}
	| type pointer IDENTIFIER {
		$$ = createVariable(getType($1), $2, $3, NULL, NULL, popStack(),col,linha_toda);
	}
	| type IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET {
		$$ = createVariable(getType($1), NULL, $2, $4, NULL, popStack(),col,linha_toda);
	}
	| type pointer IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET {
		$$ = createVariable(getType($1), $2, $3, $5, NULL, popStack(),col,linha_toda);
	}
;

comandos: command_list {
		$$ = $1;
	}
	| comandos command_list {
		addCmdList($1, $2);
		$$ = $1;
	}
;

bloco: L_CURLY_BRACKET comandos R_CURLY_BRACKET {
		$$ = $2;
	}
;

command_list:
	io_command {
		$$ = $1;
	}
	| loop_command {
		$$ = $1;
	}
	| jump_command {
		$$ = $1;
	}
	| conditional_command {
		$$ = $1;
	}
	| SEMICOLON {
		$$ = createNullCmd();
	}
	| expression SEMICOLON {
		$$ = createExpression($1);
	}
	| bloco {
		$$ = $1;
	}
;


loop_command:
	WHILE L_PAREN expression R_PAREN bloco {
		$$ = createWhile($3, $5);
	}
	| DO bloco WHILE L_PAREN expression R_PAREN SEMICOLON {
		$$ = createDo($2, $5);
	}
	| FOR L_PAREN expr_stat expr_stat R_PAREN bloco {
		$$ = createFor($3, $4, NULL, $6);
	}
	| FOR L_PAREN expr_stat expr_stat expression R_PAREN bloco {
		$$ = createFor($3, $4, $5, $7);
	}
;

expr_stat:
	SEMICOLON {
		$$ = createNullCmd();
	}
	| expression SEMICOLON {
		$$ = createExpression($1);
	}
;

jump_command:
	EXIT L_PAREN expression R_PAREN SEMICOLON {
		$$ = createExit($3);
	}
	| RETURN SEMICOLON {
		$$ = createReturn(NULL, lines + 1,col,linha_toda);
	}
	| RETURN expression SEMICOLON {
		$$ = createReturn($2, lines + 1,col,linha_toda);
	}
;

conditional_command:
	IF L_PAREN expression R_PAREN bloco {
		$$ = createIf($3, $5, NULL);
	}
	|	IF L_PAREN expression R_PAREN bloco ELSE bloco {
		$$ = createIf($3, $5, $7);
	}
;

io_command:
	PRINTF L_PAREN STRING R_PAREN SEMICOLON {
		Node *node;
		node = createNode(STRING, 0, $3, lines + 1,col,linha_toda);
		setPointerString(node);
		$$ = createPrintf(node, NULL);
	}
	| PRINTF L_PAREN STRING print_stat R_PAREN SEMICOLON {
		Node *node;
		node = createNode(STRING, 0, $3, lines + 1,col,linha_toda);
		setPointerString(node);
		$$ = createPrintf(node, $4);
	}
	| SCANF L_PAREN STRING COMMA BITWISE_AND IDENTIFIER R_PAREN SEMICOLON {
		Node *node;
		node = createNode(STRING, 0, $3, lines + 1,col,linha_toda);
		setPointerString(node);
		$$ = createScanf(node, createNode(IDENTIFIER, 0, $6, lines + 1,col,linha_toda));
	}
;

print_stat: COMMA assignment_expression {
		$$ = createExpression($2);
	}
	| print_stat COMMA assignment_expression {
		$$ = createExpression(createTreeNode(COMMA, 0, NULL, getExpNode($1), $3, lines + 1,col,linha_toda));
	}
;

function_declarations:
	type idf parametros L_CURLY_BRACKET comandos R_CURLY_BRACKET {
		$$ = createFunction($1, NULL, $2, $3, NULL, $5, popStack(),col_last_id);
	}
	| type pointer idf parametros L_CURLY_BRACKET comandos R_CURLY_BRACKET {
		$$ = createFunction($1, $2, $3, $4, NULL, $6, popStack(),col_last_id);
	}
	| type idf parametros L_CURLY_BRACKET var_list comandos R_CURLY_BRACKET {
		$$ = createFunction($1, NULL, $2, $3, $5, $6, popStack(),col_last_id);
	}
	| type pointer idf parametros L_CURLY_BRACKET var_list comandos R_CURLY_BRACKET {
		$$ = createFunction($1, $2, $3, $4, $6, $7, popStack(),col_last_id);
	}
;
idf:
	IDENTIFIER{$$ = $1;col_last_id = col;}
	;

var_list:
	var_declarations_unit {
		$$ = $1;	
	}
	| var_list var_declarations_unit {
		addVariable($1, $2);
		$$ = $1;
	}
;

number:
	NUM_INTEGER {
		$$ = createNode(NUM_INTEGER, $1, NULL, lines + 1,col,linha_toda);
	}
	| NUM_OCTAL {
		$$ = createNode(NUM_OCTAL, $1, NULL, lines + 1,col,linha_toda);
	}
	| NUM_HEXA {
		$$ = createNode(NUM_HEXA, $1, NULL, lines + 1,col,linha_toda);
	}
;

primary_expression
	: IDENTIFIER {
		$$ = createNode(IDENTIFIER, 0, $1, lines + 1,col,linha_toda);
	}
	| number {
		$$ = $1;
	}
	| CHARACTER {
		$$ = createNode(CHARACTER, 0, $1, lines + 1,col,linha_toda);
	}
	| STRING {
		Node *node;
		node = createNode(STRING, 0, $1, lines + 1,col,linha_toda);
		setPointerString(node);
		$$ = node;
	}
	| L_PAREN expression R_PAREN {
		$$ = $2;
	}
;

postfix_expression
	: primary_expression {
		$$ = $1;
	}
	| postfix_expression L_SQUARE_BRACKET expression R_SQUARE_BRACKET {
		$$ = createTreeNode(AST_POSTFIX_EXPRESSION, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
	| postfix_expression L_PAREN R_PAREN {
		setNodeType($1, ID_FUNCTION_CALL);
		$$ = $1;
	}
	| postfix_expression L_PAREN argument_expression_list R_PAREN {
		$$ = createTreeNode(ID_FUNCTION_CALL, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
	| postfix_expression INC {
		$$ = createTreeNode(INC, 0, NULL, $1, NULL, lines + 1,col,linha_toda);
	}
	| postfix_expression DEC {
		$$ = createTreeNode(DEC, 0, NULL, $1, NULL, lines + 1,col,linha_toda);
	}
;

argument_expression_list
	: assignment_expression {
		$$ = $1;
	}
	| argument_expression_list COMMA assignment_expression {
		$$ = createTreeNode(COMMA, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
;

unary_expression
	: postfix_expression {
		$$ = $1;
	}
	| INC unary_expression {
		$$ = createTreeNode(INC, 0, NULL, $2, NULL, lines + 1,col,linha_toda);
	}
	| DEC unary_expression {
		$$ = createTreeNode(DEC, 0, NULL, $2, NULL, lines + 1,col,linha_toda);
	}
	| unary_operator cast_expression{
		$$ = createTreeNode(AST_UNARY_EXPRESSION, 0, NULL, $1, $2, lines + 1,col,linha_toda);
	}
;

unary_operator
	: BITWISE_AND {
		$$ = createNode(BITWISE_AND, 0, NULL, lines + 1,col,linha_toda);
	}
	| MULTIPLY {
		$$ = createNode(MULTIPLY, 0, NULL, lines + 1,col,linha_toda);
	}
	| PLUS {
		$$ = createNode(PLUS, 0, NULL, lines + 1,col,linha_toda);
	}
	| MINUS {
		$$ = createNode(MINUS, 0, NULL, lines + 1,col,linha_toda);
	}
	| BITWISE_NOT {
		$$ = createNode(BITWISE_NOT, 0, NULL, lines + 1,col,linha_toda);
	}
	| NOT {
		$$ = createNode(NOT, 0, NULL, lines + 1,col,linha_toda);
	}
;

cast_expression
	: unary_expression {
		$$ = $1;
	}
	| L_PAREN type pointer R_PAREN cast_expression {
		$$ = createTreeNode(AST_CAST, 0, getValueString($3), $2, $5, lines + 1,col,linha_toda);	
	}
	| L_PAREN type R_PAREN cast_expression {
		$$ = createTreeNode(AST_CAST, 0, NULL, $2, $4, lines + 1,col,linha_toda);	
	}
;

multiplicative_expression
	: cast_expression {
		$$ = $1;
	}
	| multiplicative_expression MULTIPLY cast_expression {
		$$ = createTreeNode(MULTIPLY, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
	| multiplicative_expression DIV cast_expression {
		$$ = createTreeNode(DIV, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
	| multiplicative_expression REMAINDER cast_expression {
		$$ = createTreeNode(REMAINDER, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
;

additive_expression
	: multiplicative_expression {
		$$ = $1;
	}
	| additive_expression plus multiplicative_expression {
		$$ = createTreeNode(PLUS, 0, NULL, $1, $3, lines + 1,$2,linha_toda);
	}
	| additive_expression minus multiplicative_expression {
		$$ = createTreeNode(MINUS, 0, NULL, $1, $3, lines + 1,$2,linha_toda);
	}
;
minus:
	MINUS{$$ = col;}
	;

plus:
	PLUS{		
		$$=col;
	}
	;
	

shift_expression
	: additive_expression {
		$$ = $1;
	}
	| shift_expression L_SHIFT additive_expression {
		$$ = createTreeNode(L_SHIFT, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
	| shift_expression R_SHIFT additive_expression {
		$$ = createTreeNode(R_SHIFT, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
;

relational_expression
	: shift_expression {
		$$ = $1;
	}
	| relational_expression LESS_THAN shift_expression {
		$$ = createTreeNode(LESS_THAN, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
	| relational_expression GREATER_THAN shift_expression {
		$$ = createTreeNode(GREATER_THAN, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
	| relational_expression LESS_EQUAL shift_expression {
		$$ = createTreeNode(LESS_EQUAL, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
	| relational_expression GREATER_EQUAL shift_expression {
		$$ = createTreeNode(GREATER_EQUAL, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
;

equality_expression
	: relational_expression {
		$$ = $1;
	}
	| equality_expression EQUAL relational_expression {
		$$ = createTreeNode(EQUAL, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
	| equality_expression NOT_EQUAL relational_expression {
		$$ = createTreeNode(NOT_EQUAL, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
;

and_expression
	: equality_expression {
		$$ = $1;
	}
	| and_expression BITWISE_AND equality_expression {
		$$ = createTreeNode(BITWISE_AND, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
;

exclusive_or_expression
	: and_expression {
		$$ = $1;
	}
	| exclusive_or_expression BITWISE_XOR and_expression {
		$$ = createTreeNode(BITWISE_XOR, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
;

inclusive_or_expression
	: exclusive_or_expression {
		$$ = $1;
	}
	| inclusive_or_expression BITWISE_OR exclusive_or_expression {
		$$ = createTreeNode(BITWISE_OR, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
;

logical_and_expression
	: inclusive_or_expression {
		$$ = $1;
	}
	| logical_and_expression LOGICAL_AND inclusive_or_expression {
		$$ = createTreeNode(LOGICAL_AND, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
;

logical_or_expression
	: logical_and_expression {
		$$ = $1;
	}
	| logical_or_expression LOGICAL_OR logical_and_expression {
		$$ = createTreeNode(LOGICAL_OR, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
;

conditional_expression
	: logical_or_expression {
		$$ = $1;
	}
	| logical_or_expression TERNARY_CONDITIONAL expression colon conditional_expression{
		Node *node;
		node = createTreeNode(COLON, 0, NULL, $3, $5, lines + 1,$4,linha_toda);
		$$ = createTreeNode(TERNARY_CONDITIONAL, 0, NULL, $1, node, lines + 1,$4,linha_toda);
	}
;
colon:
	COLON{$$ = col;}
	;

assignment_expression
	: conditional_expression {
		$$ = $1;
	}
	| unary_expression assignment_operator assignment_expression{
		$$ = createTreeNode(getType($2), 0, NULL, $1, $3, lines + 1,getNodeColuna($1),linha_toda);
	}
;

assignment_operator
	: ASSIGN {
		$$ = createNode(ASSIGN, 0, NULL, lines + 1,col,linha_toda);
	}
	| ADD_ASSIGN {
		$$ = createNode(ADD_ASSIGN, 0, NULL, lines + 1,col,linha_toda);
	}
	| MINUS_ASSIGN {
		$$ = createNode(MINUS_ASSIGN, 0, NULL, lines + 1,col,linha_toda);
	}
;

expression
	: assignment_expression {
		$$ = $1;
	}
	| expression COMMA assignment_expression {
		$$ = createTreeNode(COMMA, 0, NULL, $1, $3, lines + 1,col,linha_toda);
	}
;

%%

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
