#ifndef TABLE_H
#define TABLE_H
//Defines:
#include <def.h>
#include <cmd.h>

//Structures:
typedef struct variable Variable;
typedef struct function Function;
typedef struct table Table;
typedef struct program Program;

//Functions:
Variable *createVariable(int type, Node *pointer, char *name, Node *array, Node *value, int line,int coluna,char * linha);
Function *createFunction(Node *type, Node *pointer, char *name, Variable *param, Variable *var_list, CmdList *commands, int line,int coluna);
Table *createTable();
Program *createProgram();
void addVariable(Variable *list, Variable *var);
void addFunction(Function *list, Function *fun);
void addTableVariable(Table *table, Variable *variable);
void addTableFunction(Table *table, Function *function);
void addProgram(Program *program, Function *function);
void setVariableListType(Node *type, Variable *var);
//Get Errors
void semanticError(Program *program, Table *table);
//Gets-Sets
void setVariableType(Variable *var, int type);
void setVariableValue(Variable *var, Node *expression);
void setVariablePointer(Variable *var, Node *pointer);
int getVariableType(Variable *var);
int getVariableLine(Variable *var);
char *getVariableName(Variable *var);
Variable *getVariableProx(Variable *var);
Node *getVariableArray(Variable *var);
Node *getVariableValue(Variable *var);
char *getVariablePointer(Variable *var);
char *getFunctionName(Function *function);
int getFunctionLine(Function *function);
void setVariableColuna(Variable *var, int coluna);
int getVariableColuna(Variable *var);
void setVariableLinha(Variable *var,char * linha);
char * getVariableLinha(Variable * var);
//Print-Debug
void printfProgram(Program *program, Table *table);
int getFunctionColuna(Function *Function);

#endif