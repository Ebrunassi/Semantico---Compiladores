#ifndef ERROR_H
#define ERROR_H
//Defines:
#include <def.h>
#include <table.h>

//Structures:
typedef struct error Error;
typedef struct stack Stack;

//Variables:
int warning;
Error *error_list, *warning_list;
Stack *stack_line;

//Functions:
Stack *createStack(int line);
void pushStack(int line);
int popStack();
Error *createError();
int printfError();
/*	Errors 	*/
//Declaracoes de variaveis/funcoes/prototipos
int errorVarRedefinition(Variable *list, Variable *var);
void errorVarDeclaredVoid(Variable *var);
int errorVarAlreadyDeclared(Variable *list,Variable *var);
void errorParamVoid(Variable *var);
int errorPrototypeArgumentNotMatch(Variable *var);
void errorPrototypeFewerArguments(Function *function);
int errorPrototypeMoreArguments(Function *function);
int errorPrototypeConflictingTypes(Function *function);
void errorArrayNegative(Variable *var);
void errorArrayZero(Variable *var);
//Chamadas de funcao
void errorNotFunction(int line, char *name,int col);
void errorFunctionUndeclared(int line, char *name);
void errorFewArgumentsToFunction(int line, char *name,int col);
void errorManyArgumentsToFunction(int line, char *name);
void errorIncompatibleTypeForArgument(int line, int argument, char *name, char *type_one, char *type_two,int col);
//Retornos de funcao
void errorNoReturnStatement(Function *function);
void errorReturnWithValueReturningVoid(Function * function);
void errorReturnWithNoValueReturningNonVoid(int line,int coluna);
void errorIncompatibleTypes(int line, char *type_one, char *type_two,int coluna);
//Verificacao de tipos em comandos/expressoes
void errorVarUndeclared(int line, char *name,int coluna);
void errorLvalueIncrement(int line,int col);
void errorLvalueAssign(int line,int col);
void errorInitializerNotConstant(Variable *var, char *name,int coluna);
void errorRShiftNegative(int line,int coluna);
void errorLShiftNegative(int line,int coluna);
void errorDefineString(Variable *var,int coluna);
void errorDivisionByZero(int line, int col);
void errorVoidValueNotIgnored(int line,int col);
void errorSubscriptedValue(int line,int col);
void errorLvalueUnary(int line, char *operand,int col);
int errorInvalidArgumentUnary(int line, char *operand, char *type,int col);
void errorArraySubscriptNotInteger(int line,int col);
void errorComparisonBetweenBinary(int line, char *type_one, char *type_two, char *operand,int col);
void errorCannotConvert(int line, char *type,int col);
void errorAssignOfReadOnlyString(int line, char *string,int col);
void errorAssignOfReadOnlyCaractere(int line, char *string);
void errorIncompatibleTypesWhenAssigning(int line, char *type_one, char *type_two,int col);
void errorInvalidOperandsBinary(int line, char *operand, char *type_one, char *type_two,int col);
int errorUnaryPlus(int line,int col);
int errorUnaryMinus(int line);
/*	Warnings 	*/
void warningLeftShift(int line,int col);
void warningRightShift(int line,int col);
void warningArrayOutOfBounds(int line,int col);
void warningComparisonBetweenBinary(int line, char *type_one, char *type_two, char *operand,int col);
void warningCast(int line, char *type_one, char *type_two,int col);
void warningConditionalExpression(int line, char *type_one, char *type_two,int col);
//Gets-Sets

//Print-Debug

#endif