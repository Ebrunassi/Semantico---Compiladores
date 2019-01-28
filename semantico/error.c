#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <ast.h>
#include <cmd.h>
#include <sintatico.tab.h>
/*	Defines	*/

/*	Structures	*/
struct error{
	int line;
	char *msg;
	Error *prox;
};

struct stack{
	int line;
	Stack *prox;
};

/*	Variables	*/
extern int warning;
extern Error *error_list, *warning_list;
extern Stack *stack_line;
char buffer[500];

/*	Functions	*/
Stack *createStack(int line){
	Stack *new;
	new = (Stack *) malloc(sizeof(Stack));
	new->line = line;
	new->prox = NULL;
}

void pushStack(int line){
	Stack *p;
	p = stack_line;
	if (p->line == -1){
		p->line = line;
	} else{
		while(p->prox != NULL){
			p = p->prox;
		}
		p->prox = createStack(line);
	}
}

int popStack(){
	Stack *p, *paux;
	int value = 1;
	p = stack_line;
	paux = stack_line;
	if (p->line != -1){
		p = p->prox;
		if (p == NULL){
			value = paux->line;
			paux->line = -1;
		} else{
			while(p->prox != NULL){
				paux = paux->prox;
				p = p->prox;
			}
			value = p->line;
			paux->prox = NULL;
			free(p);
		}
	}
	return value;
}


Error *createError(int line, char *msg){
	Error *new;
	new = (Error *) malloc(sizeof(Error));
	new->line = line;
	if (msg != NULL){
		new->msg = (char *) malloc((strlen(msg) + 1) * sizeof(char));
		strcpy(new->msg, msg);
	} else{
		new->msg = NULL;
	}
	new->prox = NULL;
	return new;
}

void insertError(Error *list, int line, char *msg){
	Error *p;
	p = list;
	if (p->msg == NULL){
		p->line = line;
		p->msg = (char *) malloc((strlen(msg) + 1) * sizeof(char));
		strcpy(p->msg, msg);
	} else{
		while(p->prox != NULL){
			p = p->prox;
		}
		p->prox = createError(line, msg);
	}
}

Error *getError(){
	int menor = 9999;
	Error *error, *p;
	error = NULL;
	p = error_list;
	while(p != NULL){
		if (p->msg != NULL){
			if (p->line < menor){
				menor = p->line;
				error = p;
			}
		}
		p = p->prox;
	}
	return error;
}

int getListSize(Error *list){
	int count = 0;
	Error *p;
	p = list;
	if (list != NULL){
		if (p->prox == NULL){
			if (p->msg != NULL){
				count = 1;
			}
		} else{
			while(p != NULL){
				count++;
				p = p->prox;
			}
		}
	}

	return count;
}

Error *listToArray(Error *list, int size){
	Error *array, *p, *paux;
	int i;
	array = NULL;
	if (size > 0){
		array = (Error *) malloc(size * sizeof(Error));
	}
	p = list;
	paux = array;
	for (i=0; i<size; i++){
		paux->line = p->line;
		paux->msg = (char *) malloc((strlen(p->msg) + 1) * sizeof(char));
		strcpy(paux->msg, p->msg);
		paux->prox = NULL;
		paux = paux + 1;
		p = p->prox; 
	}

	return array;
}

Error *orderByLine(Error list[], int size){
	Error p;
	int i, j;
	if (list != NULL){
		for (i=0; i<size; i++){
			for(j=i+1;j<size; j++){
				p = list[i];
				if (list[j].line < list[i].line){
					list[i] = list[j];
					list[j] = p;
				}
			}
		}
	}

	return list;
}

Error *getWarning(){
	Error *p;
	p = listToArray(warning_list, getListSize(warning_list));
	p = orderByLine(p, getListSize(warning_list));
	return p;
}

int printfError(){
	int erro = 0;
	int count = 0;
	Error *error, *warning_aux, *p;
	error = getError();
	warning_aux = getWarning();

	//Warnings:
	p = warning_aux;
	while(count < getListSize(warning_list)){
		if (error != NULL){
			if (p->line <= error->line){
				if (count == 0){
					printf("%s", p->msg);
				} else{
					printf("\n%s", p->msg);
				}
			}
		} else{
			if (count == 0){
				printf("%s", p->msg);
			} else{
				printf("\n%s", p->msg);
			}
		}
		warning = 1;
		count++;
		p = p + 1;
	}
	//Error:
	p = error;
	if (getListSize(error_list) > 0){
		erro = 1;
		if (count == 0){
			printf("%s", p->msg);
		} else{
			printf("\n%s", p->msg);
		}
		exit(0);
	}
	return erro;
}
int getInicioReturn(int coluna,char * linha)
{
	int i;
	i=coluna;
	do
	{
		if(linha[i]=='r'&&linha[i+1]=='e'&& linha[i+2]=='t'&&linha[i+3]=='u'&&linha[i+4]=='r'&&linha[i+5]=='n')
		{
			return i+1;
		}
		i--;
	}while(1);
} 
int getNextEqual(int pos,char * palavra)
{
	do
	{
		if(palavra[pos]=='=')
		{
			return pos+1;
		}
		else
		{
			pos++;
		}
	}while(1);
}
int getNextAspas(char * palavra)
{
	int pos = 0;
	do
	{
		if(palavra[pos]=='"')
		{
			return pos+1;
		}
		else
		{
			pos++;
		}
	}while(1);
}
int getNextSimbol(char *palavra,int pos)
{
	do
	{
		if(palavra[pos]!='('&&palavra[pos]!=' ')
		{
			return pos+1;
		}
		else
		{
			pos++;
		}
	}while(1);
}

/*	Errors 	*/

//Declaracoes de variaveis/funcoes/prototipos
int errorVarRedefinition(Variable *list, Variable *var){ 
	int j=0;
	int i;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<getVariableLine(list);i++)
	{
		fgets(aux,5000,f);
	}
	fclose(f);
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: redefinition of '%s' previous defined in line %d column %d\n%s\n", getVariableLine(list),getVariableColuna(list), getVariableName(list), getVariableLine(var),getVariableColuna(var),aux);
	for(i=0;i<getVariableColuna(list)-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)," ");
	}
	j+=snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, getVariableLine(list), buffer);
	return 1;
}

void errorVarDeclaredVoid(Variable *var){
	int j=0;
	int i;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<getVariableLine(var);i++)
	{
		fgets(aux,5000,f);
	}
	fclose(f);
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	j=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: variable '%s' declared void\n%s\n", getVariableLine(var),getVariableColuna(var), getVariableName(var),aux);
	for(i=0;i<getVariableColuna(var)-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)," ");
	}
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, getVariableLine(var), buffer);
}

int errorVarAlreadyDeclared(Variable *list,Variable *var){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<getVariableLine(list);i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: variable '%s' already declared, previous declaration in line %d column %d\n%s\n", getVariableLine(list),getVariableColuna(list), getVariableName(var),getVariableLine(var),getVariableColuna(var),aux);
	for(i=0;i<getVariableColuna(list)-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, getVariableLine(var), buffer);
	return 1;
}

void errorParamVoid(Variable *var){
	snprintf(buffer, sizeof(buffer), "error:semantic:%d: parameter '%s' declared void", getVariableLine(var), getVariableName(var));
	insertError(error_list, getVariableLine(var), buffer);
}

int errorPrototypeArgumentNotMatch(Variable *var){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<getVariableLine(var);i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: argument '%s' does not match prototype\n%s\n", getVariableLine(var),getVariableColuna(var),getVariableName(var),aux);
	for(i=0;i<getVariableColuna(var)-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, getVariableLine(var), buffer);
	return 1;
}

void errorPrototypeFewerArguments(Function *function){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<getFunctionLine(function);i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux,'\n')) != NULL)
    *pos = '\0';
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: prototype for '%s' declares fewer arguments\n%s\n", getFunctionLine(function),getFunctionColuna(function), getFunctionName(function),aux);
	for(i=0;i<getFunctionColuna(function)-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, getFunctionLine(function), buffer);
	return;
}

int errorPrototypeMoreArguments(Function *function){
	snprintf(buffer, sizeof(buffer), "error:semantic:%d: prototype for '%s' declares more arguments", getFunctionLine(function), getFunctionName(function));
	insertError(error_list, getFunctionLine(function), buffer);
	return 1;
}

int errorPrototypeConflictingTypes(Function *function){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<getFunctionLine(function);i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: conflicting types for '%s'\n%s\n", getFunctionLine(function),getFunctionColuna(function), getFunctionName(function),aux);
	for(i=0;i<getFunctionColuna(function)-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, getFunctionLine(function), buffer);
	return 1;
}

void errorArrayNegative(Variable *var){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<getVariableLine(var);i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	i=0;
while(aux[i]!='[')
    {
    	i++;
    }
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: size of array '%s' is negative\n%s\n", getVariableLine(var),i, getVariableName(var),aux);
	i = i-strlen(getVariableName(var));
	while(i)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
		i--;
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, getVariableLine(var), buffer);
	return;
}

void errorArrayZero(Variable *var){
	int i;
	int j=0;
	char *pos;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<getVariableLine(var);i++)
	{
		fgets(aux,5000,f);
	}if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
		j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: size of array '%s' is zero\n%s\n", getVariableLine(var),getVariableColuna(var)-2, getVariableName(var),aux);
	for(i=0;i<getVariableColuna(var)-3;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, getVariableLine(var), buffer);
	return;
}

//Chamadas de funcao
void errorNotFunction(int line, char *name,int col){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	col = getNextSimbol(aux,col);
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d called object '%s' is not a function or function pointer\n%s\n", line,col,name,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;


}

void errorFunctionUndeclared(int line, char *name){
	snprintf(buffer, sizeof(buffer), "error:semantic:%d: '%s' undeclared", line, name);
	insertError(error_list, line, buffer);
}

void errorFewArgumentsToFunction(int line, char *name,int col){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	col = col - strlen(name);
	//col = getNextSimbol(aux,col);
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: too few arguments to function '%s'\n%s\n", line,col, name,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;


}

void errorManyArgumentsToFunction(int line, char *name){
	snprintf(buffer, sizeof(buffer), "error:semantic:%d: too many arguments to function '%s'", line, name);
	insertError(error_list, line, buffer);
}

void errorIncompatibleTypeForArgument(int line, int argument, char *name, char *type_one, char *type_two,int col){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	col = col - strlen(name);
	//col = getNextSimbol(aux,col);
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: incompatible type for argument '%d' of '%s' expected '%s' but argument is of type '%s'\n%s\n", line,col, argument, name, type_one, type_two,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;
	
}
//Retornos de funcao
void errorNoReturnStatement(Function *function){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<getFunctionLine(function);i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: no return statement in function returning non-void\n%s\n", getFunctionLine(function),getFunctionColuna(function),aux);
	for(i=0;i<getFunctionColuna(function)-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, getFunctionLine(function), buffer);
	return;
}

void errorReturnWithValueReturningVoid(Function * function){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<getFunctionLine(function);i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: return with a value, in function returning void\n%s\n", getFunctionLine(function),getFunctionColuna(function),aux);
	for(i=0;i<getFunctionColuna(function)-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, getFunctionLine(function), buffer);
	return;
}

void errorReturnWithNoValueReturningNonVoid(int line,int coluna){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	coluna = getInicioReturn(coluna,aux);
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: return with no value, in function returning non-void\n%s\n", line,coluna,aux);
	for(i=0;i<coluna-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;
}

void errorIncompatibleTypes(int line, char *type_one, char *type_two, int coluna){
	
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	coluna = getInicioReturn(coluna,aux);
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: incompatible types when returning type '%s' but '%s' was expected\n%s\n", line,coluna, type_one, type_two,aux);
	for(i=0;i<coluna-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;

}

//Verificacao de tipos em comandos/expressoes
void errorVarUndeclared(int line, char *name,int col){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	//col= getInicioVar(col,aux,name);
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d '%s' undeclared\n%s\n", line,col-strlen(name),name,aux);
	for(i=0;i<col-1-strlen(name);i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;
	
}

void errorLvalueIncrement(int line,int col){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	//col= getInicioVar(col,aux,name);
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: lvalue required as increment operand\n%s\n", line,col,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;

}

void errorLvalueAssign(int line,int col){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	col= getNextEqual(col,aux);
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d lvalue required as left operand of assignment\n%s\n", line,col,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;
}

void errorInitializerNotConstant(Variable *var, char *name,int coluna){
	int i;
	int j=0;
	char *pos;
	char aux[5000];
	coluna--;
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<getVariableLine(var);i++)
	{
		fgets(aux,5000,f);
	}if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d '%s' initializer element is not constant\n%s\n", getVariableLine(var),coluna, name,aux);
	for(i=0;i<coluna-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, getVariableLine(var), buffer);
	return;
	
}

void errorRShiftNegative(int line,int coluna){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	//col= getNextEqual(col,aux);
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: rigth shift count is negative\n%s\n", line,coluna,aux);
	for(i=0;i<coluna-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	
	return;
}

void errorLShiftNegative(int line,int coluna){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	//col= getNextEqual(col,aux);
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: left shift count is negative\n%s\n", line,coluna,aux);
	for(i=0;i<coluna-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	
	return;
}

void errorDefineString(Variable *var,int coluna){
	int i;
	int j=0;
	char *pos;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<getVariableLine(var);i++)
	{
		fgets(aux,5000,f);
	}if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
    coluna = getNextAspas(aux);
	j+=	snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: string type is not compatible with define\n%s\n", getVariableLine(var),coluna,aux);
	for(i=0;i<coluna-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, getVariableLine(var), buffer);
	return;

	
}

void errorDivisionByZero(int line,int col){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	//col= getNextEqual(col,aux);
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: division by zero\n%s\n", line,col,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;

}

void errorVoidValueNotIgnored(int line,int col){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	col = getNextSimbol(aux,col);
	j+=	snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: void value not ignored as it ought to be\n%s\n", line,col,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;


}

void errorSubscriptedValue(int line,int col){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	//col = getNextSimbol(aux,col);
	j+=	snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: subscripted value is neither array nor pointer\n%s\n", line,col,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;
	

}

void errorLvalueUnary(int line, char *operand,int col){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	while(aux[col]!=operand[0])
	{
		col++;
	}
	col++;
	//col = getNextSimbol(aux,col);
	j+=	snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: lvalue required as unary '%s' operand\n%s\n", line,col, operand,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;
	

}

int errorInvalidArgumentUnary(int line, char *operand, char *type,int col){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	col--;
	//col = getNextSimbol(aux,col);
	j+=	snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: invalid type argument of unary '%s' (have '%s')\n%s\n", line,col, operand, type,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);



	return 1;
}

void errorArraySubscriptNotInteger(int line,int col){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	//col = getNextSimbol(aux,col);
	j+=		snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d array subscript is not an integer\n%s\n", line,col,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;
}

void errorComparisonBetweenBinary(int line, char *type_one, char *type_two, char *operand,int col){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	col--;
	while(aux[col-1]=='='||aux[col-1]=='<'||aux[col-1]=='>')
	{
		col--;
	}
	col++;
	//col = getNextSimbol(aux,col);
	j+=	snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: comparison between '%s' and '%s' operator '%s'\n%s\n", line,col ,type_one, type_two, operand,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;

	insertError(error_list, line, buffer);
}

void errorCannotConvert(int line, char *type,int col ){
	int i;
	int j=0;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	col = getNextSimbol(aux,col);
	j+=		snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: cannot convert from '%s' to int\n%s\n", line,col, type,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;


}

void errorAssignOfReadOnlyString(int line, char *string,int col){
	int i;
	int j=0;
	col--;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	//col = getNextSimbol(aux,col);
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d assignment of read-only location \"%s\"\n%s\n", line,col, string,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;


}

void errorAssignOfReadOnlyCaractere(int line, char *string){
	snprintf(buffer, sizeof(buffer), "error:semantic:%d: assignment of read-only location '%s'", line, string);
	insertError(error_list, line, buffer);
}

void errorIncompatibleTypesWhenAssigning(int line, char *type_one, char *type_two,int col){

	int i;
	int j=0;
	col--;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	//col = getNextSimbol(aux,col);
	j+=	snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: incompatible types when assigning to type '%s' from type '%s'\n%s\n", line,col, type_one, type_two,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;


}

void errorInvalidOperandsBinary(int line, char *operand, char *type_one, char *type_two,int col){
	int i;
	int j=0;
	col--;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	//col = getNextSimbol(aux,col);
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d: invalid operands to binary '%s' (have '%s' and '%s')\n%s\n", line,col, operand, type_one, type_two,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	return;
}

int errorUnaryPlus(int line,int col){
	int i;
	int j=0;
	col--;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	//col = getNextSimbol(aux,col);
	j+=snprintf(buffer, sizeof(buffer), "error:semantic:%d:%d wrong type argument to unary plus\n%s\n", line,col,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(error_list, line, buffer);
	

	return 1;
}

int errorUnaryMinus(int line){
	snprintf(buffer, sizeof(buffer), "error:semantic:%d: wrong type argument to unary minus", line);
	insertError(error_list, line, buffer);
	return 1;
}

/*	Warnings 	*/
void warningLeftShift(int line,int col){
	int i;
	int j=0;
	col--;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	while(aux[col]!='<')
	{
		col++;
	}
	col++;
	//col = getNextSimbol(aux,col);
	j+=snprintf(buffer, sizeof(buffer), "warning:%d:%d: right shift count <= width of type\n%s\n", line,col,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");	
	insertError(warning_list, line, buffer);
}

void warningRightShift(int line,int col){
	int i;
	int j=0;
	col--;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	while(aux[col]!='>')
	{
		col++;
	}
	col++;
	//col = getNextSimbol(aux,col);
	j+=snprintf(buffer, sizeof(buffer), "warning:%d:%d: right shift count >= width of type\n%s\n", line,col,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");	
	insertError(warning_list, line, buffer);
}

void warningArrayOutOfBounds(int line,int col){
	int i;
	int j=0;
	col--;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	//col = getNextSimbol(aux,col);
	while(aux[col]!='[')
	{
		col++;
	}
	col++;
	j+=snprintf(buffer, sizeof(buffer), "warning:%d:%d: array index out of bounds\n%s\n", line,col,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");	
	insertError(warning_list, line, buffer);
}

void warningComparisonBetweenBinary(int line, char *type_one, char *type_two, char *operand,int col){
	int i;
	int j=0;
	col--;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	col = getNextSimbol(aux,col);
	j+=snprintf(buffer, sizeof(buffer), "warning:%d:%d: comparison between '%s' and '%s' operator '%s'\n%s\n", line,col, type_one, type_two, operand,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(warning_list, line, buffer);
	return;
}

void warningCast(int line, char *type_one, char *type_two,int col){
	int i;
	int j=0;
	col--;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	while(aux[col]!='(')
	{
		col--;
	}
	col++;
	j+=snprintf(buffer, sizeof(buffer), "warning:%d:%d: cast from '%s' to '%s' of different size\n%s\n", line,col, type_one, type_two,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(warning_list, line, buffer);
	return;
}

void warningConditionalExpression(int line, char *type_one, char *type_two,int col){
	int i;
	int j=0;
	col--;
	char aux[5000];
	FILE *f = fopen("gambiarra.txt","r");
	for(i=0;i<line;i++)
	{
		fgets(aux,5000,f);
	}
	char *pos;
	if ((pos=strchr(aux, '\n')) != NULL)
    *pos = '\0';
	while(aux[col]!=':')
	{
		col++;
	}
	col++;
	j+=snprintf(buffer, sizeof(buffer), "warning:%d:%d: '%s'/'%s' type mismatch in conditional expression\n%s\n", line,col, type_one, type_two,aux);
	for(i=0;i<col-1;i++)
	{
		j+=snprintf(buffer+j,sizeof(buffer)+j," ");
	}
	fclose(f);
	snprintf(buffer+j,sizeof(buffer),"^");
	insertError(warning_list, line, buffer);
	return;
}

//Gets-Sets

//Print-Debug