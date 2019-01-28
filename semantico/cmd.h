#ifndef CMD_H
#define CMD_H
//Defines:
#include <def.h>
#include <ast.h>

//Structures:
typedef struct command Command;
typedef struct command_list CmdList;

//Functions:
void addCmdList(CmdList *list, CmdList *cmd);
/*	Loop	*/
CmdList *createWhile(Node *expression, CmdList *cmd);
CmdList *createDo(CmdList *cmd, Node *expression);
CmdList *createFor(CmdList *expression1, CmdList *expression2, Node *expression3, CmdList *cmd);

/*	Jump	*/
CmdList *createExit(Node *expression);
CmdList *createReturn(Node *expression, int line,int col,char * linha);

/*	Conditional	*/
CmdList *createIf(Node *expression, CmdList *cmd1, CmdList *cmd2);

/*	InOut	*/
CmdList *createPrintf(Node *expression, CmdList *cmd);
CmdList *createScanf(Node *expression1, Node *expression2);

/*	Expression	*/
CmdList *createExpression(Node *expression);

/*	NullCmd	*/
CmdList *createNullCmd();

//Gets-Sets
Node *getExpNode(CmdList *expression);
void *getCommand(Command *command);
Command *getCommandProx(Command *command);
Command *getCmdListCommand(CmdList *command);
CmdList *getCmdListProx(CmdList *command);
void *getNodeFromExpression(CmdList *expression);
void *getNodeFromCommandWithExpression(CmdList *command);
//Print-Debug
void printfCmdList(CmdList *list);

#endif