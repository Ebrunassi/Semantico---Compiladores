#ifndef AST_H
#define AST_H
//Defines:
#include <def.h>

//Structures:
typedef struct node Node;

//Functions:
Node *createNode(int type, int value_number, char *value_string, int line,int coluna,char * linha);
Node *createTreeNode(int type, int value_number, char *value_string, Node *left, Node *right, int line,int coluna,char * linha);
Node *solveExpression(void *table, void *function, Node *node, void *var, int constante);
int isNumber(Node *node);
int isCharacter(Node *node);
int isOperating(Node *node);
char *charToString(char c);

//void = Variable
void *getVariableFromIdentifier(void *table, void *function, char *id);
char *getIdType(int id);

//Gets-Sets
int getId(void *obj);
int getType(Node *node);
int getValueNumber(Node *node);
char *getValueString(Node *node);
int getNodeLine(Node *node);
char *getNodePointer(Node *node);
Node *getNodeLeft(Node *node);
Node *getNodeRight(Node *node);
void setNodeType(Node *node, int type);
void setFunctionCallType(Node *node);
void setPointerString(Node *node);
int getNodeColuna(Node *node);
char * getNodeLinha(Node *node);

//Print-Debug
char *getIdType(int id);
void printfTree(Node *tree);

#endif
