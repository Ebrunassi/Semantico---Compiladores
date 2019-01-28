#include <stdio.h>
#include <stdlib.h>
#include <cmd.h>
#include <table.h>
#include <error.h>
#include <sintatico.tab.h>
/*	Defines	*/

/*	Structures	*/
struct command{
	void *cmd;
	Command *prox;
};

struct command_list{
	int id;
	Command *list;
	CmdList *prox;
};
/*	Variables	*/

/*	Functions	*/
Command *createCommand(void *cmd){
	Command *new;
	new = (Command *) malloc(sizeof(Command));
	new->cmd = cmd;
	new->prox = NULL;
}

CmdList *createCmdList(int id, Command *list){
	CmdList *new;
	new = (CmdList *) malloc(sizeof(CmdList));
	new->id = id;
	new->list = list;
	new->prox = NULL;
}

void addCommand(Command *cmd, void *add){
	Command *p, *new;
	p = cmd;
	new = createCommand(add);
	while(p->prox != NULL){
		p = p->prox;
	}
	p->prox = new;
}

void addCmdList(CmdList *list, CmdList *cmd){
	CmdList *p;
	p = list;
	while(p->prox != NULL){
		p = p->prox;
	}
	p->prox = cmd;
}

/*	Loop	*/
CmdList *createWhile(Node *expression, CmdList *cmd){
	CmdList *new;
	Command *commands;
	commands = createCommand(createExpression(expression));
	addCommand(commands, cmd);
	new = createCmdList(ID_COMMAND_WHILE, commands);
	return new;
}

CmdList *createDo(CmdList *cmd, Node *expression){
	CmdList *new;
	Command *commands;
	commands = createCommand(cmd);
	addCommand(commands, createExpression(expression));
	new = createCmdList(ID_COMMAND_DO, commands);
	return new;
}

CmdList *createFor(CmdList *expression1, CmdList *expression2, Node *expression3, CmdList *cmd){
	CmdList *new;
	Command *commands;
	commands = createCommand(expression1);
	addCommand(commands, expression2);
	if (expression3 != NULL){
		addCommand(commands, createExpression(expression3));
		addCommand(commands, cmd);
		new = createCmdList(ID_COMMAND_FOR_1, commands);
	} else{
		addCommand(commands, cmd);
		new = createCmdList(ID_COMMAND_FOR_2, commands);
	}
	return new;
}

/*	Jump	*/
CmdList *createExit(Node *expression){
	CmdList *new;
	Command *commands;
	commands = createCommand(createExpression(expression));
	new = createCmdList(ID_COMMAND_EXIT, commands);
	return new;
}

CmdList *createReturn(Node *expression, int line,int col,char * linha){
	CmdList *new;
	Command *commands;
	if (expression == NULL){
		expression = createNode(VOID, 0, NULL, line,col,linha);
	}
	commands = createCommand(createExpression(expression));
	new = createCmdList(ID_COMMAND_RETURN, commands);
	return new;
}

/*	Conditional	*/
CmdList *createIf(Node *expression, CmdList *cmd1, CmdList *cmd2){
	CmdList *new;
	Command *commands;
	commands = createCommand(createExpression(expression));
	addCommand(commands, cmd1);
	if (cmd2 != NULL){
		addCommand(commands, cmd2);
		new = createCmdList(ID_COMMAND_IF_ELSE, commands);
	} else{
		new = createCmdList(ID_COMMAND_IF, commands);
	}
	return new;
}

/*	InOut	*/
CmdList *createPrintf(Node *expression, CmdList *cmd){
	CmdList *new;
	Command *commands;
	commands = createCommand(createExpression(expression));
	if (cmd != NULL){
		addCommand(commands, cmd);
		new = createCmdList(ID_COMMAND_PRINTF_2, commands);
	} else{
		new = createCmdList(ID_COMMAND_PRINTF_1, commands);
	}
	
	return new;
}

CmdList *createScanf(Node *expression1, Node *expression2){
	CmdList *new;
	Command *commands;
	commands = createCommand(createExpression(expression1));
	addCommand(commands, createExpression(expression2));
	new = createCmdList(ID_COMMAND_SCANF, commands);
	return new;
}

/*	Expression	*/
CmdList *createExpression(Node *expression){
	CmdList *new;
	Command *commands;
	commands = createCommand(expression);
	new = createCmdList(ID_EXPRESSION, commands);
	return new;
}

/*	NullCmd	*/
CmdList *createNullCmd(){
	CmdList *new;
	Command *commands;
	commands = createCommand(NULL);
	new = createCmdList(ID_NULL_CMD, commands);
	return new;
}

//Gets-Sets
Node *getExpNode(CmdList *expression){
	return (Node *) ((Command *)expression->list)->cmd;
}

void *getCommand(Command *command){
	return command->cmd;
}

Command *getCommandProx(Command *command){
	return command->prox;
}

Command *getCmdListCommand(CmdList *command){
	return command->list;
}

CmdList *getCmdListProx(CmdList *command){
	return command->prox;
}

void *getNodeFromExpression(CmdList *expression){
	return getCommand(getCmdListCommand(expression));
}

void *getNodeFromCommandWithExpression(CmdList *command){
	return getNodeFromExpression(getCommand(getCmdListCommand(command)));
}

//Print-Debug
void printfCommand(Command *cmd){
	Command *p;
	void *command;
	p = cmd;

	while(p != NULL){
		command = p->cmd;
		switch(getId(command)){
			case ID_NODE: printfTree(command); break;
			default: printfCmdList((CmdList *) command); break;
		}
		p = p->prox;
	}
}

void printfCmdList(CmdList *list){
	CmdList *p;
	p = list;
	while(p != NULL){
		switch(getId(p)){
			case ID_COMMAND_WHILE: printf("\n   while "); break;
			case ID_COMMAND_DO: printf("\n   do "); break;
			case ID_COMMAND_FOR_1: printf("\n   for 1 "); break;
			case ID_COMMAND_FOR_2: printf("\n   for 2 "); break;
			case ID_COMMAND_EXIT: printf("\n   exit "); break;
			case ID_COMMAND_RETURN: printf("\n   return "); break;
			case ID_COMMAND_IF: printf("\n   if "); break;
			case ID_COMMAND_IF_ELSE: printf("\n   if else "); break;
			case ID_COMMAND_PRINTF_1: printf("\n   printf 1 "); break;
			case ID_COMMAND_PRINTF_2: printf("\n   printf 2 "); break;
			case ID_COMMAND_SCANF: printf("\n   scanf "); break;
			case ID_EXPRESSION: printf("\n   expression "); break;
			case ID_NULL_CMD: printf("\n   null cmd "); break;
			default:printf("ERROR: INVALID TYPE ");break;
		}
		printf(" {");
		printfCommand(p->list);
		printf(" }");
		p = p->prox;
	}
}













