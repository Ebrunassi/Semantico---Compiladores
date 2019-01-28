/* Nao usar a biblioteca do flex*/
%option noyywrap

%x NO_COMENTARIO

%{
#include <string.h>
#include <ast.h>
#include <cmd.h>
#include <table.h>
#include <error.h>
#include <sintatico.tab.h>

extern int lines;
extern int col;
extern int col_last_id;
extern int quebra_linha;
extern int syntax_error;
extern int tab;
extern char linha_toda[500000];
extern char linha_atual[500000];
extern char *error;
extern int define_line;

int chars=0;
int colcment;
int lncoment;
int cont;
int whereBreak = 1;


void remover(char *str){
        int i = 1;
        for(i=1;i<strlen(str)-1;i++){
                str[i-1]=str[i];
        }
        str[i-1]='\0';
}


%}

%%
"void"     {strcat(linha_toda,yytext);col+=4; pushStack(lines + 1);return VOID;}
"int"	     {strcat(linha_toda,yytext);col+=3; pushStack(lines + 1);return INT;}
"char"     {strcat(linha_toda,yytext);col+=4; pushStack(lines + 1);return CHAR;}
"return"   {strcat(linha_toda,yytext);col+=6;return RETURN;}
"break"    {strcat(linha_toda,yytext);col+=5;return BREAK;}
"switch"   {strcat(linha_toda,yytext);col+=6;return SWITCH;}
"case"     {strcat(linha_toda,yytext);col+=4;return CASE;}
"default"  {strcat(linha_toda,yytext);col+=7;return DEFAULT;}
"do"	     {strcat(linha_toda,yytext);col+=2;return DO;}
"while"    {strcat(linha_toda,yytext);col+=5;return WHILE;}
"for"      {strcat(linha_toda,yytext);col+=3;return FOR;}
"if"       {strcat(linha_toda,yytext);col+=2;return IF;}
"else"     {strcat(linha_toda,yytext);col+=4;return ELSE;}
"typedef"  {strcat(linha_toda,yytext);col+=7;return TYPEDEF;}
"struct"   {strcat(linha_toda,yytext);col+=6;return STRUCT;}
"+"        {strcat(linha_toda,yytext);col+=1;return PLUS;}
"-"	       {strcat(linha_toda,yytext);col+=1;return MINUS;}
"*"        {strcat(linha_toda,yytext);col+=1;return MULTIPLY;}
"/"	       {strcat(linha_toda,yytext);col+=1;return DIV;}
"%"	       {strcat(linha_toda,yytext);col+=1;return REMAINDER;}
"++"       {strcat(linha_toda,yytext);col+=2;return INC;}
"--"	     {strcat(linha_toda,yytext);col+=2;return DEC;}
"&"        {strcat(linha_toda,yytext);col++;return BITWISE_AND;}
"|"        {strcat(linha_toda,yytext);col++;return BITWISE_OR;}
"~"        {strcat(linha_toda,yytext);col++;return BITWISE_NOT;}
"^"        {strcat(linha_toda,yytext);col++;return BITWISE_XOR;}
"!"        {strcat(linha_toda,yytext);col++;return NOT;}
"&&"       {strcat(linha_toda,yytext);col+=2;return LOGICAL_AND;}
"||"       {strcat(linha_toda,yytext);col+=2;return LOGICAL_OR;}
"=="       {strcat(linha_toda,yytext);col+=2;return EQUAL;}
"!="       {strcat(linha_toda,yytext);col+=2;return NOT_EQUAL;}
"<"        {strcat(linha_toda,yytext);col++;return LESS_THAN;}
">"        {strcat(linha_toda,yytext);col++;return GREATER_THAN;}
"<="       {strcat(linha_toda,yytext);col+=2;return LESS_EQUAL;}
">="       {strcat(linha_toda,yytext);col+=2;return GREATER_EQUAL;}
">>"       {strcat(linha_toda,yytext);col+=2;return R_SHIFT;}
"<<"       {strcat(linha_toda,yytext);col+=2;return L_SHIFT;}
"="        {strcat(linha_toda,yytext);col++;return ASSIGN;}
"+="       {strcat(linha_toda,yytext);col+=2;return ADD_ASSIGN;}
"-="       {strcat(linha_toda,yytext);col+=2;return MINUS_ASSIGN;}
";"        {strcat(linha_toda,yytext);col++;return SEMICOLON;}
","        {strcat(linha_toda,yytext);col++;return COMMA;}
":"        {strcat(linha_toda,yytext);col++;return COLON;}
"("        {strcat(linha_toda,yytext);col++;return L_PAREN;}
")"        {strcat(linha_toda,yytext);col++;return R_PAREN;}
"{"        {strcat(linha_toda,yytext);col++;return L_CURLY_BRACKET;}
"}"        {strcat(linha_toda,yytext);col++;return R_CURLY_BRACKET;}
"["        {strcat(linha_toda,yytext);col++;return L_SQUARE_BRACKET;}
"]"        {strcat(linha_toda,yytext);col++;return R_SQUARE_BRACKET;}
"?"        {strcat(linha_toda,yytext);col++;return TERNARY_CONDITIONAL;}
"#"        {strcat(linha_toda,yytext);col++;return NUMBER_SIGN;}
"->"       {strcat(linha_toda,yytext);col+=2;return POINTER;}
"printf"   {strcat(linha_toda,yytext);col+=6;return PRINTF;}
"scanf"    {strcat(linha_toda,yytext);col+=5;return SCANF;}
"define"   {strcat(linha_toda,yytext);col+=6; define_line = lines + 1;return DEFINE;}
"exit"     {strcat(linha_toda,yytext);col+=4;return EXIT;}

"0"[xX][0-9A-Fa-f]+              {strcat(linha_toda,yytext);col+=strlen(yytext);
                                        yylval.num = strtol(yytext,NULL,16);return NUM_HEXA;}

"0"[1-7][0-7]*                {strcat(linha_toda,yytext);col+=strlen(yytext);
                                yylval.num = strtol(yytext,NULL,8);return NUM_OCTAL;}

[0-9]+                   {strcat(linha_toda,yytext);col+=strlen(yytext);
                                yylval.num = atoi(yytext);return NUM_INTEGER;}

'[\\]?(.){1}'     {strcat(linha_toda,yytext);col+=yyleng;
                    yylval.str = strdup(yytext);remover(yylval.str);return CHARACTER;}

\"([^\\\"]|\\.)*\"  {strcat(linha_toda,yytext);col+=yyleng;
                      yylval.str = strdup(yytext);remover(yylval.str);return STRING;}

<INITIAL>{
     "/*"              {lncoment = lines+1; colcment = col;col+=2;strcat(linha_toda,yytext);BEGIN(NO_COMENTARIO);}
     }
<NO_COMENTARIO>{
     "*/"      {BEGIN(INITIAL);col+=2;strcat(linha_toda,yytext);};
     <<EOF>>   {printf("error:lexical:%d:%d: unterminated comment",lncoment,colcment);exit(0);BEGIN(INITIAL);}
     .         {strcat(linha_toda,yytext);col++;}
     \n        {yylineno++;lines++;col=1;if(!quebra_linha){strcpy(linha_atual,linha_toda);quebra_linha = 1;}linha_toda[0]='\0';tab=0;}
     }


"//"([^\n])*             {col=1;strcat(linha_toda,yytext);if(!quebra_linha){strcpy(linha_atual,linha_toda);quebra_linha = 1;}linha_toda[0]='\0';tab=0;}
[ \t]                    {chars++;col++;if(yytext[0]=='\t'){tab++;}strcat(linha_toda,yytext);}
[\n]                     {lines++;col=1;if(!quebra_linha){strcpy(linha_atual,linha_toda);quebra_linha = 1;}linha_toda[0]='\0';tab=0;}
[_a-zA-Z][_a-zA-Z0-9]*   {strcat(linha_toda,yytext);col+=yyleng;yylval.str = strdup(yytext);return IDENTIFIER;}
.                        {printf("error:lexical:%d:%d: %s",lines+1,col,yytext); col++;exit(0);}

%%
