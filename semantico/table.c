#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <table.h>
#include <error.h>
#include <sintatico.tab.h>
/*	Defines	*/

/*	Structures	*/
struct variable{
	int id;
	int type;
	char *pointer;
	char *name;
	Node *array;
	Node *value;
	int line;
	int coluna;
	char * linha;
	Variable *prox;
};

struct function{
	int id;
	int type;
	char *pointer;
	char *name;
	Variable *param;
	Variable *var_list;
	CmdList *commands;
	int line;
	char * linha;
	int coluna;
	Function *prox;
};

struct table{
	Variable *variable;
	Function *function;
};

struct program{
	Function *function;
};
/*	Variables	*/

Variable *function_call_list;
int function_return;

/*	Functions	*/
char *getVarTypeError(Variable *var);
char *getFunctionTypeError(Function *fun);
char *getNodeTypeError(Node *node);

Variable *createVariable(int type, Node *pointer, char *name, Node *array, Node *value, int line,int coluna,char * linha){
	Variable *new;
	new = (Variable *) malloc(sizeof(Variable));
	new->name = name;
	new->type = type;
	if (array != NULL){
		if (pointer != NULL){
			new->id = ID_VARIABLE_POINTER_ARRAY;
			new->pointer = getValueString(pointer);
		} else{
			new->id = ID_VARIABLE_ARRAY;
			new->pointer = NULL;
		}
		new->array = array;
	} else if (pointer != NULL){
		new->id = ID_VARIABLE_POINTER;
		new->pointer = getValueString(pointer);
		new->array = NULL;
	} else{
		new->id = ID_VARIABLE;
		new->pointer = NULL;
		new->array = NULL;
	}
	if (value != NULL){
		new->value = value;
	} else{
		new->value = NULL;
	}
	new->line = line;
	if(name!=NULL)new->coluna = coluna-strlen(name)-1;
	else
		new->coluna = coluna;
	new->prox = NULL;
	return new;
}

Function *createFunction(Node *type, Node *pointer, char *name, Variable *param, Variable *var_list, CmdList *commands, int line,int coluna){
	Function *new;
	new = (Function *) malloc(sizeof(Function));
	new->type = getType(type);
	if (pointer != NULL){
		new->id = ID_FUNCTION_POINTER;
		new->pointer = getValueString(pointer);
	} else{
		new->id = ID_FUNCTION;
		new->pointer = NULL;
	}
	new->name = name;
	new->param = param;
	new->var_list = var_list;
	new->commands = commands;
	new->line = line;
	new->prox = NULL;
	new->coluna = coluna-strlen(name)-1;
	return new;
}

Table *createTable(){
	Table *new;
	new = (Table *) malloc(sizeof(Table));
	new->variable = NULL;
	new->function = NULL;
	return new;
}

Program *createProgram(){
	Program *new;
	new = (Program *) malloc(sizeof(Program));
	new->function = NULL;
	return new;
}

void addVariable(Variable *list, Variable *var){
	Variable *p;
	p = list;
	while(p->prox != NULL){
		p = p->prox;
	}
	p->prox = var;
}

void addFunction(Function *list, Function *fun){
	Function *p;
	p = list;
	while(p->prox != NULL){
		p = p->prox;
	}
	p->prox = fun;
}

void addTableVariable(Table *table, Variable *variable){
	if (table->variable == NULL){
		table->variable = variable;
	} else{
		addVariable(table->variable, variable);
	}
}

void addTableFunction(Table *table, Function *function){
	if (table->function == NULL){
		table->function = function;
	} else{
		addFunction(table->function, function);
	}
}

void addProgram(Program *program, Function *function){
	if (program->function == NULL){
		program->function = function;
	} else{
		addFunction(program->function, function);
	}
}

//Get Errors
void checkVariableTypeVoid(Variable *var){
	if (var->pointer == NULL && var->type == VOID){
		errorVarDeclaredVoid(var);
	}
}

int checkVariableAlreadyDeclared(Variable *list, Variable *var){
	int erro = 0;
	if (strcmp(list->name, var->name) == 0){
		if (list->type == var->type){
			erro = errorVarAlreadyDeclared(list,var);
		}
	}
	return erro;
}

int checkVariableRedefinition(Variable *list, Variable *var){
	int erro = 0;
	if (strcmp(list->name, var->name) == 0){
		if (list->type != var->type){
			erro = errorVarRedefinition(list, var);
		}
	}
	return erro;
}

int checkVariableCompare(Variable *list, Variable *var, int error){
	int erro = error;
	Variable *p;
	p = list;
	/*	Errors	*/
	checkVariableTypeVoid(var);
	while(p != NULL){
		if (p != var){
			if (!erro){
				erro = checkVariableAlreadyDeclared(p, var);
			} 
			if (!erro){
				erro = checkVariableRedefinition(p, var);
			}
		}
		p = p->prox;
	}
	return erro;
}

void checkVariableList(Variable *list, Variable *var){
	int erro = 0;
	Variable *p;
	p = var;
	while(p != NULL){
		erro = checkVariableCompare(list, p, erro);
		p = p->prox;
	}
}

void checkVariable(Variable *list){
	checkVariableList(list, list);
}

void checkParamVoid(Variable *list){
	Variable *p;
	p = list;
	while(p != NULL){
		if (p->pointer == NULL && p->type == VOID){
			errorParamVoid(p);
		}
		p = p->prox;
	}
}

void checkPrototypeMatch(Function *definition, Function *function){
	int erro = 0;
	Variable *pdef, *pfun, *paux;
	pdef = definition->param;
	pfun = function->param;
	paux = function->param;
	if (definition->type != function->type){
		erro = errorPrototypeConflictingTypes(function);
	}
	if (!erro){
		while(pdef != NULL){
			if (!erro){
				if (pfun != NULL){
					if (!(strcmp(pdef->name, pfun->name) == 0 && pdef->type == pfun->type)){
						erro = errorPrototypeArgumentNotMatch(pfun);
					}
				} else{
					erro = errorPrototypeMoreArguments(function);
				}
			}
			pdef = pdef->prox;
			if (!erro){
				pfun = pfun->prox;
			}
		}
	}
	if (!erro){
		if (pfun != NULL){
			errorPrototypeFewerArguments(function);
		}
	}

}

void checkPrototypeCompare(Function *definition, Function *function){
	Function *p;
	p = definition;
	while(p != NULL){
		if (strcmp(p->name, function->name) == 0){
			checkPrototypeMatch(p, function);
		}
		p = p->prox;
	}
}

void checkPrototype(Function *definition, Function *function){
	Function *p;
	p = function;
	while(p != NULL){
		checkPrototypeCompare(definition, p);
		p = p->prox;
	}
}

void calculateVariableValue(Variable *table, Variable *list){
	int erro = 0;
	Variable *p;
	p = list;
	while(p != NULL){
		if (!erro){
			if (p->type == ID_CONS_DEFINE){
				p->value = solveExpression(table, list, p->value, p, 1);
			} else{
				p->value = solveExpression(table, list, p->value, p, 0);
			}
			if (p->value != NULL){
				//Erro define = string
				if (p->type == ID_CONS_DEFINE && !isNumber(p->value)){
					errorDefineString(p,table->coluna);
				}
				
			}
			//Erro array <= 0
			p->array = solveExpression(table, list, p->array, p, 1);
			if (p->array != NULL){
				if (getValueNumber(p->array) == 0){
					errorArrayZero(p);
				} else if (getValueNumber(p->array) < 0){
					errorArrayNegative(p);
				}
			}
		}
		p = p->prox;
	}
}



void checkLvalueForUnaryOperands(Variable *table, Variable *function, Node *node, Node *value, char *operand){
	Variable *var;
	if (getValueString(node) != NULL){
		var = getVariableFromIdentifier(table, function, getValueString(node));
		if (var != NULL){
			if (value != NULL){
				var->value = solveExpression(table, function, value, var, 0);
			}
		} else{
			if (strcmp(operand, "++") == 0){
				errorLvalueIncrement(getNodeLine(node),getNodeColuna(node));
			} else{
				errorLvalueUnary(getNodeLine(node), operand,getNodeColuna(node));
			}
		}
	} else{
		if (strcmp(operand, "++") == 0){
			errorLvalueIncrement(getNodeLine(node),getNodeColuna(node));
		} else{
			errorLvalueUnary(getNodeLine(node), operand,getNodeColuna(node));
		}
	}
}

void verifyPointersErrors(Variable *table, Variable *function, Node *a, Node *b, int line, char *operand){
	int erro = 0;
	Variable *var_a, *var_b;
	int pointer_a = 0, pointer_b = 0;
	char *type_one = NULL, *type_two = NULL;
	if (a != NULL && b != NULL){
		var_a = getVariableFromIdentifier(table, function, getValueString(a));
		var_b = getVariableFromIdentifier(table, function, getValueString(b));
		if (var_a != NULL){
			type_one = getVarTypeError(var_a);
		} else{
			type_one = getNodeTypeError(a);
		}
		if (var_b != NULL){
			type_two = getVarTypeError(var_b);
		} else{
			type_two = getNodeTypeError(b);
		}
		if (getNodePointer(a) != NULL){
			pointer_a = strlen(getNodePointer(a));
		}
		if (getNodePointer(b) != NULL){
			pointer_b = strlen(getNodePointer(b));
		}
		if (pointer_a != pointer_b){
			if ((pointer_a != 0 && pointer_b == 0) || (pointer_a == 0 && pointer_b != 0)){
				warningComparisonBetweenBinary(line, type_one, type_two, operand,getNodeColuna(a));
			} else{
				errorComparisonBetweenBinary(line, type_one, type_two, operand,getVariableColuna(function));
			}
		} else{
			if (var_a == NULL && var_b != NULL){
				if (getVariableType(var_a) != getVariableType(var_b)){
					errorComparisonBetweenBinary(line, type_one, type_two, operand,getVariableColuna(function));
				}
			} else{
				if (getType(a) != getType(b)){
					errorComparisonBetweenBinary(line, type_one, type_two, operand,getVariableColuna(function));
				}
			}
		}
	}
}

void verifyOperatorTypeErrors(Node *operator, Node *a, Node *b, Variable *table, Variable *function){
	int erro = 0;
	Variable *var_a = NULL, *var_b = NULL;
	char *type_one = NULL, *type_two = NULL;
	if (a != NULL){ 
		if (getValueString(a) != NULL){
			var_a = getVariableFromIdentifier(table, function, getValueString(a));
			if (var_a != NULL){
				type_one = getVarTypeError(var_a);
			} else{
				type_one = getNodeTypeError(a);
			}
		}
	}
	if (b != NULL){ 
		if (getValueString(b) != NULL){
			var_b = getVariableFromIdentifier(table, function, getValueString(b));
			if (var_b != NULL){
				type_two = getVarTypeError(var_b);
			} else{
				type_two = getNodeTypeError(b);
			}
		}
	}
	switch(getType(operator)){
		//Binary Operators
		case PLUS:
			if (getNodePointer(b) != NULL){
				errorInvalidOperandsBinary(getNodeLine(operator), charToString('+'), type_one, type_two,getNodeColuna(operator));
			} 
			break;

		case MINUS:
			if (getNodePointer(b) != NULL){
				errorInvalidOperandsBinary(getNodeLine(operator), charToString('-'), type_one, type_two,getNodeColuna(operator));
			}
			break;

		case MULTIPLY:
			if (getNodePointer(a) != NULL || getNodePointer(b) != NULL){
				errorInvalidOperandsBinary(getNodeLine(operator), charToString('*'), type_one, type_two,getNodeColuna(operator));
			}
			break;

		case DIV:{
				errorInvalidOperandsBinary(getNodeLine(operator), charToString('/'), type_one, type_two,getNodeColuna(operator));
			}
			break;

		case REMAINDER:
			if (getNodePointer(a) != NULL || getNodePointer(b) != NULL){
				errorInvalidOperandsBinary(getNodeLine(operator), charToString('%'), type_one, type_two,getNodeColuna(operator));
			}
			break;

		case BITWISE_AND:
			if (getNodePointer(a) != NULL || getNodePointer(b) != NULL){
				errorInvalidOperandsBinary(getNodeLine(operator), charToString('&'), type_one, type_two,getNodeColuna(operator));
			}
			break;

		case BITWISE_OR:
			if (getNodePointer(a) != NULL || getNodePointer(b) != NULL){
				errorInvalidOperandsBinary(getNodeLine(operator), charToString('|'), type_one, type_two,getNodeColuna(operator));
			}
			break;

		case BITWISE_XOR:
			if (getNodePointer(a) != NULL || getNodePointer(b) != NULL){
				errorInvalidOperandsBinary(getNodeLine(operator), charToString('^'), type_one, type_two,getNodeColuna(operator));
			}
			break;

		case EQUAL:
			if (getNodePointer(a) != NULL || getNodePointer(b) != NULL){
				verifyPointersErrors(table, function, a, b, getNodeLine(operator), "==");
			}
			break;

		case NOT_EQUAL:
			if (getNodePointer(a) != NULL || getNodePointer(b) != NULL){
				verifyPointersErrors(table, function, a, b, getNodeLine(operator), "!=");
			}
			break;

		case LESS_THAN:
			if (getNodePointer(a) != NULL || getNodePointer(b) != NULL){
				verifyPointersErrors(table, function, a, b, getNodeLine(operator), charToString('<'));
			}
			break;

		case GREATER_THAN:
			if (getNodePointer(a) != NULL || getNodePointer(b) != NULL){
				verifyPointersErrors(table, function, a, b, getNodeLine(operator), charToString('>'));
			}
			break;

		case LESS_EQUAL:
			if (getNodePointer(a) != NULL || getNodePointer(b) != NULL){
				verifyPointersErrors(table, function, a, b, getNodeLine(operator), "<=");
			}
			break;

		case GREATER_EQUAL:
			if (getNodePointer(a) != NULL || getNodePointer(b) != NULL){
				verifyPointersErrors(table, function, a, b, getNodeLine(operator), ">=");
			}
			break;

		case R_SHIFT:
			if (getNodePointer(b) != NULL){
				errorCannotConvert(getNodeLine(a), getNodeTypeError(b),getNodeColuna(getNodeLeft(a)));
			}
			break;

		case L_SHIFT:
			if (getNodePointer(b) != NULL){
				errorCannotConvert(getNodeLine(a), getNodeTypeError(b),getNodeColuna(getNodeLeft(a)));
			}
			break;
	}
}

void expression(Variable *table, Variable *function, Command *command){
	Node *node = NULL, *nodeaux = NULL;
	Variable *var = NULL, *var_aux = NULL;
	char *operand = NULL;
	int erro = 0;
	node = getCommand(command);
	switch(getType(node)){
		case ASSIGN:
			if (getNodeLeft(node) != NULL){
				var = getVariableFromIdentifier(table, function, getValueString(getNodeLeft(node)));
				if (var != NULL){
					var->value = solveExpression(table, function, getNodeRight(node), var, 0);

					if (getValueString(var->value) != NULL){
						var_aux = getVariableFromIdentifier(table, function, getValueString(var->value));
						if (var_aux != NULL){
							if (!(var->pointer != NULL || var->array != NULL) && var_aux->array != NULL){
								errorSubscriptedValue(getNodeLine(node),getNodeColuna(getNodeLeft(node)));
							}
						}
					}

					if (var->type != getType(var->value)){
						if (var->type == CHAR){
							if (isNumber(var->value) || getType(var->value) == VOID){
								errorIncompatibleTypesWhenAssigning(getNodeLine(node), getVarTypeError(var), getNodeTypeError(var->value),getNodeColuna(node));
							} else if (var->pointer == NULL && getNodePointer(var->value) != NULL){
								errorIncompatibleTypesWhenAssigning(getNodeLine(node), getVarTypeError(var), getNodeTypeError(var->value),getNodeColuna(node));
							}
						} 
						else if (getNodePointer(var->value) == NULL && !isNumber(var->value)){
							errorIncompatibleTypesWhenAssigning(getNodeLine(node), getVarTypeError(var), getNodeTypeError(var->value),getNodeColuna(node));
						}
					} else if (var->pointer == NULL && getNodePointer(var->value) != NULL){
						errorIncompatibleTypesWhenAssigning(getNodeLine(node), getVarTypeError(var), getNodeTypeError(var->value),getNodeColuna(node));
					}
					
				} else{
					switch(getType(getNodeLeft(node))){
						case STRING: errorAssignOfReadOnlyString(getNodeLine(node), getValueString(getNodeLeft(node)),getNodeColuna(node)); break;
						case CHARACTER: errorAssignOfReadOnlyCaractere(getNodeLine(node), getValueString(getNodeLeft(node))); break;
						default: errorLvalueAssign(getNodeLine(node),getNodeColuna(getNodeLeft(node))); break;
					}
				}
			}
			break;

		case ADD_ASSIGN:
			if (getNodeLeft(node) != NULL){
				var = getVariableFromIdentifier(table, function, getValueString(getNodeLeft(node)));
				if (var != NULL){
					var->value = solveExpression(table, function, getNodeRight(node), var, 0);

					if (getValueString(var->value) != NULL){
						var_aux = getVariableFromIdentifier(table, function, getValueString(var->value));
						if (var_aux != NULL){
							if (!(var->pointer != NULL || var->array != NULL) && var_aux->array != NULL){
								errorSubscriptedValue(getNodeLine(node),getNodeColuna(getNodeLeft(node)));
							}
						}
					}

					if (var->type != getType(var->value)){
						if (var->type == CHAR){
							if (isNumber(var->value) || getType(var->value) == VOID){
								errorIncompatibleTypesWhenAssigning(getNodeLine(node), getVarTypeError(var), getNodeTypeError(var->value),getNodeColuna(node));
							} else if (var->pointer == NULL && getNodePointer(var->value) != NULL){
								errorIncompatibleTypesWhenAssigning(getNodeLine(node), getVarTypeError(var), getNodeTypeError(var->value),getNodeColuna(node));
							}
						} 
						else if (getNodePointer(var->value) == NULL && !isNumber(var->value)){
							errorIncompatibleTypesWhenAssigning(getNodeLine(node), getVarTypeError(var), getNodeTypeError(var->value),getNodeColuna(node));
						}
					} else if (var->pointer == NULL && getNodePointer(var->value) != NULL){
						errorIncompatibleTypesWhenAssigning(getNodeLine(node), getVarTypeError(var), getNodeTypeError(var->value),getNodeColuna(node));
					}
					
				} else{
					switch(getType(getNodeLeft(node))){
						case STRING: errorAssignOfReadOnlyString(getNodeLine(node), getValueString(getNodeLeft(node)),getNodeColuna(node)); break;
						case CHARACTER: errorAssignOfReadOnlyCaractere(getNodeLine(node), getValueString(getNodeLeft(node))); break;
						default: errorLvalueAssign(getNodeLine(node),getNodeColuna(getNodeLeft(node))); break;
					}
				}
			}
			break;

		case MINUS_ASSIGN:
			if (getNodeLeft(node) != NULL){
				var = getVariableFromIdentifier(table, function, getValueString(getNodeLeft(node)));
				if (var != NULL){
					var->value = solveExpression(table, function, getNodeRight(node), var, 0);

					if (getValueString(var->value) != NULL){
						var_aux = getVariableFromIdentifier(table, function, getValueString(var->value));
						if (var_aux != NULL){
							if (!(var->pointer != NULL || var->array != NULL) && var_aux->array != NULL){
								errorSubscriptedValue(getNodeLine(node),getNodeColuna(getNodeLeft(node)));
							}
						}
					}

					if (var->type != getType(var->value)){
						if (var->type == CHAR){
							if (isNumber(var->value) || getType(var->value) == VOID){
								errorIncompatibleTypesWhenAssigning(getNodeLine(node), getVarTypeError(var), getNodeTypeError(var->value),getNodeColuna(node));
							} else if (var->pointer == NULL && getNodePointer(var->value) != NULL){
								errorIncompatibleTypesWhenAssigning(getNodeLine(node), getVarTypeError(var), getNodeTypeError(var->value),getNodeColuna(node));
							}
						} 
						else if (getNodePointer(var->value) == NULL && !isNumber(var->value)){
							errorIncompatibleTypesWhenAssigning(getNodeLine(node), getVarTypeError(var), getNodeTypeError(var->value),getNodeColuna(node));
						}
					} else if (var->pointer == NULL && getNodePointer(var->value) != NULL){
						errorIncompatibleTypesWhenAssigning(getNodeLine(node), getVarTypeError(var), getNodeTypeError(var->value),getNodeColuna(node));
					}
					
				} else{
					switch(getType(getNodeLeft(node))){
						case STRING: errorAssignOfReadOnlyString(getNodeLine(node), getValueString(getNodeLeft(node)),getNodeColuna(node)); break;
						case CHARACTER: errorAssignOfReadOnlyCaractere(getNodeLine(node), getValueString(getNodeLeft(node))); break;
						default: errorLvalueAssign(getNodeLine(node),getNodeColuna(getNodeLeft(node))); break;
					}
				}
			}
			break;

		//Checagem Unary operands:
		case INC:
			checkLvalueForUnaryOperands(table, function, getNodeLeft(node), getNodeRight(node), "++");
			break;

		case DEC:
			checkLvalueForUnaryOperands(table, function, getNodeLeft(node), getNodeRight(node), "--");
			break;

		case PLUS:
			checkLvalueForUnaryOperands(table, function, getNodeLeft(node), getNodeRight(node), charToString('+'));

			break;

		case MINUS: 
			checkLvalueForUnaryOperands(table, function, getNodeLeft(node), getNodeRight(node), charToString('-'));
			break;

		case MULTIPLY: 
			checkLvalueForUnaryOperands(table, function, getNodeLeft(node), getNodeRight(node), charToString('*'));		
			break;

		case BITWISE_NOT: 
			checkLvalueForUnaryOperands(table, function, getNodeLeft(node), getNodeRight(node), charToString('~'));					
			break;

		case NOT: 
			checkLvalueForUnaryOperands(table, function, getNodeLeft(node), getNodeRight(node), charToString('!'));			
			break;

		case BITWISE_AND:
			checkLvalueForUnaryOperands(table, function, getNodeLeft(node), getNodeRight(node), charToString('&'));					
			break;

		case L_SHIFT:
			var = getVariableFromIdentifier(table, function, getValueString(getNodeRight(node)));
			if (var != NULL){
				if (var->pointer != NULL){
					errorCannotConvert(getNodeLine(node), getVarTypeError(var),getNodeColuna(getNodeLeft(node)));
				}
			} else{
				if (getNodePointer(getNodeRight(node)) != NULL){
					errorCannotConvert(getNodeLine(node), getNodeTypeError(getNodeRight(node)),getNodeColuna(getNodeLeft(node)));
				}
			}
			break;

		case R_SHIFT:
			var = getVariableFromIdentifier(table, function, getValueString(getNodeRight(node)));
			if (var != NULL){
				if (var->pointer != NULL){
					errorCannotConvert(getNodeLine(node), getVarTypeError(var),getNodeColuna(getNodeLeft(node)));
				}
			} else{
				if (getNodePointer(getNodeRight(node)) != NULL){
					errorCannotConvert(getNodeLine(node), getNodeTypeError(getNodeRight(node)),getNodeColuna(getNodeLeft(node)));
				}
			}
			break;

		case AST_POSTFIX_EXPRESSION:
			if (!isNumber(getNodeRight(node))){
				if (getType(getNodeRight(node)) == IDENTIFIER){
					var = getVariableFromIdentifier(table, function, getValueString(getNodeRight(node)));
					if (var == NULL){
						errorArraySubscriptNotInteger(getNodeLine(node),getNodeColuna(getNodeLeft(node)));
					} else{
						if (var->pointer != NULL){
							errorArraySubscriptNotInteger(getNodeLine(node),getNodeColuna(getNodeLeft(node)));
						}
					}
				} else{
					errorArraySubscriptNotInteger(getNodeLine(node),getNodeColuna(getNodeLeft(node)));
				}
			}
			break;

		case AST_UNARY_EXPRESSION:
			switch(getType(getNodeLeft(node))){
				case PLUS: 
					operand = (char *) malloc(2 * sizeof(char)); strcpy(operand, charToString('+')); 
					var = getVariableFromIdentifier(table, function, getValueString(getNodeRight(node)));
					if (var != NULL){
						nodeaux = solveExpression(table, function, getNodeRight(node), var, 0);
						if (getNodePointer(nodeaux) != NULL){
							erro = errorUnaryPlus(getNodeLine(node),getNodeColuna(getNodeLeft(node)));
						}
					}
					break;

				case MINUS: 
					operand = (char *) malloc(2 * sizeof(char)); strcpy(operand, charToString('-')); 
					var = getVariableFromIdentifier(table, function, getValueString(getNodeRight(node)));
					if (var != NULL){
						nodeaux = solveExpression(table, function, getNodeRight(node), var, 0);
						if (getNodePointer(nodeaux) != NULL){
							erro = errorUnaryMinus(getNodeLine(node));
						}
					}
					break;

				case MULTIPLY: 
					operand = (char *) malloc(2 * sizeof(char)); strcpy(operand, charToString('*')); 
					var = getVariableFromIdentifier(table, function, getValueString(getNodeRight(node)));
					if (var != NULL){
						nodeaux = solveExpression(table, function, getNodeRight(node), var, 0);
						if (getNodePointer(nodeaux) == NULL){
							erro = errorInvalidArgumentUnary(getNodeLine(node), charToString('*'), getVarTypeError(getVariableFromIdentifier(table, function, getValueString(getNodeRight(node)))),getNodeColuna(getNodeLeft(node)));
						}
					}
					break;

				case BITWISE_NOT: 
					operand = (char *) malloc(2 * sizeof(char)); strcpy(operand, charToString('~')); 
					var = getVariableFromIdentifier(table, function, getValueString(getNodeRight(node)));
					if (var != NULL){
						nodeaux = solveExpression(table, function, getNodeRight(node), var, 0);
						if (getNodePointer(nodeaux) != NULL){
							erro = errorInvalidArgumentUnary(getNodeLine(node), charToString('~'), getVarTypeError(getVariableFromIdentifier(table, function, getValueString(getNodeRight(node)))),getNodeColuna(getNodeLeft(node)));
						}
					}
					break;
			}
			if (!erro){
				checkLvalueForUnaryOperands(table, function, getNodeRight(node), NULL, operand);
			}
			break;
	}
	if (node != NULL){
		verifyOperatorTypeErrors(node, getNodeLeft(node), getNodeRight(node), table, function);
	}
}

void functionCallGetVariables(Variable *table, Variable *function, Node *node){
	Variable *var, *p;
	Node *aux;

	if (node){
		functionCallGetVariables(table, function, getNodeLeft(node));
		functionCallGetVariables(table, function, getNodeRight(node));

		if (isNumber(node)){
			var = createVariable(getType(node), NULL, NULL, NULL, node, getNodeLine(node),0,0);
			addVariable(function_call_list, var);
	
		} else if (getType(node) == IDENTIFIER){
			p = getVariableFromIdentifier(table, function, getValueString(node));
			if (p != NULL){
				var = createVariable(p->type, NULL, p->name, p->array, p->value, p->line,p->coluna,p->linha);
				var->pointer = p->pointer;
				addVariable(function_call_list, var);
			} else{
				errorVarUndeclared(getNodeLine(node), getValueString(node),getNodeColuna(node));
			}

		} else if (isCharacter(node)){
			var = createVariable(getType(node), NULL, NULL, NULL, node, getNodeLine(node),0,0);
			addVariable(function_call_list, var);

		} else if (getType(node) == AST_UNARY_EXPRESSION){
			if (getType(getNodeLeft(node)) == BITWISE_AND && getValueString(getNodeRight(node)) != NULL){
				p = getVariableFromIdentifier(table, function, getValueString(getNodeRight(node)));
				if (p != NULL){
					var = function_call_list;
					while(var != NULL){
						if (var->name == p->name){
							var->pointer = (char *) malloc(2 * sizeof(char));
							strcpy(var->pointer, "*");
						}
						var = var->prox;
					}
				} else{
					errorVarUndeclared(getNodeLine(node), getValueString(getNodeRight(node)),getNodeColuna(node));
				}
			}
		}
	}
}

char *functionGetNameCall(Node *node){
	char *string;
	string = NULL;
	if (node){
		if (getValueString(getNodeLeft(node)) == NULL){
			string = functionGetNameCall(getNodeLeft(node));
		} else{
			string = getValueString(getNodeLeft(node));
		}
	}
	return string;
}

void functionCallFound(Variable *table, Variable *function, Node *node){
	if (getNodeLeft(node) == NULL){
		function_call_list = createVariable(IDENTIFIER, NULL, getValueString(node), NULL, NULL, getNodeLine(node),getNodeColuna(node),getNodeLinha(node));
	} else{
		function_call_list = createVariable(IDENTIFIER, NULL, functionGetNameCall(node), NULL, NULL, getNodeLine(node),getNodeColuna(node),getNodeLinha(node));
	}
	functionCallGetVariables(table, function, getNodeRight(node));
}

void checkFunctionCallNode(Variable *table, Variable *function, Node *node){
	if (node){
		if (getType(node) == ID_FUNCTION_CALL){
			functionCallFound(table, function, node);
		} else{
			checkFunctionCallNode(table, function, getNodeLeft(node));
			checkFunctionCallNode(table, function, getNodeRight(node));
		}
	}
}

int getVarType(Variable *var){
	switch(var->type){
		case INT: return INT; break;
		case NUM_HEXA: return INT; break;
		case NUM_OCTAL: return INT; break;
		case NUM_INTEGER: return INT; break;
		case ID_CONS_DEFINE: return INT; break;
		case CHARACTER: return CHAR; break;
		case STRING: return CHAR; break;
		case IDENTIFIER: return CHAR; break;
	}
}

char *getVarTypeError(Variable *var){
	char *string = NULL;
	switch(getVarType(var)){
		case INT:
			if (var->pointer != NULL){
				string = (char *) malloc((strlen(var->pointer) + strlen("int") + 1) * sizeof(char));
				strcpy(string, "int");
				strcat(string, var->pointer);
			} else{
				string = (char *) malloc((strlen("int") + 1) * sizeof(char));
				strcpy(string, "int");
			}
			break;

		case CHAR:
			if (var->pointer != NULL){
				string = (char *) malloc((strlen(var->pointer) + strlen("char") + 1) * sizeof(char));
				strcpy(string, "char");
				strcat(string, var->pointer);
			} else{
				string = (char *) malloc((strlen("char") + 1) * sizeof(char));
				strcpy(string, "char");
			}
			break;
	}
	return string;
}

char *getFunctionTypeError(Function *fun){
	char *string = NULL;
	switch(fun->type){
		case INT:
			if (fun->pointer != NULL){
				string = (char *) malloc((strlen(fun->pointer) + strlen("int") + 1) * sizeof(char));
				strcpy(string, "int");
				strcat(string, fun->pointer);
			} else{
				string = (char *) malloc((strlen("int") + 1) * sizeof(char));
				strcpy(string, "int");
			}
			break;

		case CHAR:
			if (fun->pointer != NULL){
				string = (char *) malloc((strlen(fun->pointer) + strlen("char") + 1) * sizeof(char));
				strcpy(string, "char");
				strcat(string, fun->pointer);
			} else{
				string = (char *) malloc((strlen("char") + 1) * sizeof(char));
				strcpy(string, "char");
			}
			break;
		
		case VOID:
			if (fun->pointer != NULL){
				string = (char *) malloc((strlen(fun->pointer) + strlen("void") + 1) * sizeof(char));
				strcpy(string, "void");
				strcat(string, fun->pointer);
			} else{
				string = (char *) malloc((strlen("void") + 1) * sizeof(char));
				strcpy(string, "void");
			}
			break;
	}
	return string;
}

int getNodeType(Node *node){
	switch(getType(node)){
		case INT: return INT; break;
		case NUM_HEXA: return INT; break;
		case NUM_OCTAL: return INT; break;
		case NUM_INTEGER: return INT; break;
		case ID_CONS_DEFINE: return INT; break;
		case CHARACTER: return CHAR; break;
		case STRING: return CHAR; break;
		case IDENTIFIER: return CHAR; break;
	}
}

char *getNodeTypeError(Node *node){
	char *string = NULL;
	switch(getNodeType(node)){
		case INT:
			if (getNodePointer(node) != NULL){
				string = (char *) malloc((strlen(getNodePointer(node)) + strlen("int") + 1) * sizeof(char));
				strcpy(string, "int");
				strcat(string, getNodePointer(node));
			} else{
				string = (char *) malloc((strlen("int") + 1) * sizeof(char));
				strcpy(string, "int");
			}
			break;

		case CHAR:
			if (getNodePointer(node) != NULL){
				string = (char *) malloc((strlen(getNodePointer(node)) + strlen("char") + 1) * sizeof(char));
				strcpy(string, "char");
				strcat(string, getNodePointer(node));
			} else{
				string = (char *) malloc((strlen("char") + 1) * sizeof(char));
				strcpy(string, "char");
			}
			break;
	}
	return string;
}

void checkFunctionCall(Function *program, Table *table, Function *function, Node *node){
	Variable *p, *aux;
	Function *aux_function, *function_found;
	int erro = 0, count = 1, found = 0;
	function_call_list = NULL;

	checkFunctionCallNode(table->variable, function->var_list, node);
	//Verificar se funcao existe na tabela de simbolos:
	p = function_call_list;
	if (p != NULL){
		if (p->name != NULL){
			aux_function = table->function;
			while(aux_function != NULL){
				if (strcmp(aux_function->name, p->name) == 0){
					found = 1;
					function_found = aux_function;
					aux = aux_function->param;
				}
				aux_function = aux_function->prox;
			}
			//Verificar se funcao existe no programa:
			if (!found){
				aux_function = program;
				while(aux_function != NULL){
					if (strcmp(aux_function->name, p->name) == 0){
						found = 1;
						function_found = aux_function;
						aux = aux_function->param;
					}
					aux_function = aux_function->prox;
				}
			}
		}
	}

	if (found){
		p = p->prox;
		while(aux != NULL){
			if (!erro){
				if (p != NULL){
					if (getVarType(p) != aux->type){
						erro = 1;
						errorIncompatibleTypeForArgument(getNodeLine(node), count, function_found->name, getVarTypeError(aux), getVarTypeError(p),getNodeColuna(getNodeLeft(node)));
					}
				} else{
					erro = 1;
					errorFewArgumentsToFunction(getNodeLine(node), function_found->name,getNodeColuna(getNodeLeft(node)));
				}
			}

			count++;
			aux = aux->prox;
			if (p != NULL){
				p = p->prox;
			}
		}
		if (p != NULL){
			errorManyArgumentsToFunction(getNodeLine(node), function_found->name);
		}
		if (function->type == VOID){
			errorVoidValueNotIgnored(getNodeLine(node),getFunctionColuna(program));
		}
	} else{
		if (p != NULL && p->name != NULL){
			aux = getVariableFromIdentifier(table->variable, function->var_list, p->name);
			if (aux == NULL){
				errorFunctionUndeclared(getNodeLine(node), p->name);
			} else{
				errorNotFunction(getNodeLine(node), p->name,getNodeColuna(node));
			}
		}
	}
}

void calculateCommands(Function *program, Table *table, Function *function, CmdList *commands){
	CmdList *p;
	p = commands;
	Node *node;
	void *command;
	while(p != NULL){
		switch(getId(p)){
			case ID_COMMAND_WHILE:
				command = getCommand(getCmdListCommand(p));
				//Expressao
				calculateCommands(program, table, function, command);
				getCommandProx(command);
				//Command
				calculateCommands(program, table, function, command);
				break;

			case ID_COMMAND_DO:
				command = getCommand(getCmdListCommand(p));
				//Expressao
				calculateCommands(program, table, function, command);
				getCommandProx(command);
				//Command
				calculateCommands(program, table, function, command);
				break;

			case ID_COMMAND_FOR_1:
				command = getCommand(getCmdListCommand(p));
				//Expressao
				calculateCommands(program, table, function, command);
				getCommandProx(command);
				//Command
				calculateCommands(program, table, function, command);
				getCommandProx(command);
				//Command
				calculateCommands(program, table, function, command);
				getCommandProx(command);
				//Command
				calculateCommands(program, table, function, command);
				break;

			case ID_COMMAND_FOR_2:
				command = getCommand(getCmdListCommand(p));
				//Expressao
				calculateCommands(program, table, function, command);
				getCommandProx(command);
				//Command
				calculateCommands(program, table, function, command);
				getCommandProx(command);
				//Command
				calculateCommands(program, table, function, command);
				break;

			case ID_COMMAND_EXIT:
				command = getCommand(getCmdListCommand(p));
				//Expressao
				calculateCommands(program, table, function, command);
				break;

			case ID_COMMAND_RETURN: 
				if (getType(getNodeFromCommandWithExpression(p)) == VOID){
					function_return = 1;
					if (function->type != VOID){
						errorReturnWithNoValueReturningNonVoid(getNodeLine(getNodeFromCommandWithExpression(p)),getNodeColuna(getNodeFromCommandWithExpression(p)));
					}
				} else{
					function_return = 2; 
					if (function->type == VOID){
						errorReturnWithValueReturningVoid(function);
					} else{
						node = solveExpression(table->variable, function->var_list, getNodeFromCommandWithExpression(p), NULL, 0);
						if (function->type != getType(node)){

							errorIncompatibleTypes(getNodeLine(node), getNodeTypeError(node), getFunctionTypeError(function),getNodeColuna(node));
						}
					}
				}
				break;

			case ID_COMMAND_IF:
				command = getCommand(getCmdListCommand(p));
				//Expressao
				calculateCommands(program, table, function, command);
				getCommandProx(command);
				//Then
				calculateCommands(program, table, function, command);
				break;

			case ID_COMMAND_IF_ELSE:
				command = getCommand(getCmdListCommand(p));
				//Expressao
				calculateCommands(program, table, function, command);
				getCommandProx(command);
				//Then
				calculateCommands(program, table, function, command);
				getCommandProx(command);
				//Else
				calculateCommands(program, table, function, command);
				break;

			case ID_COMMAND_PRINTF_1:
				command = getCommand(getCmdListCommand(p));
				//Expressao
				calculateCommands(program, table, function, command);		
				break;

			case ID_COMMAND_PRINTF_2:
				command = getCommand(getCmdListCommand(p));
				//Expressao
				calculateCommands(program, table, function, command);
				getCommandProx(command);
				//Command
				calculateCommands(program, table, function, command);
				break;

			case ID_COMMAND_SCANF:
				command = getCommand(getCmdListCommand(p));
				//Expressao
				calculateCommands(program, table, function, command);
				getCommandProx(command);
				//Command
				calculateCommands(program, table, function, command);
				break;

			case ID_EXPRESSION:	
				checkFunctionCall(program, table, function, getCommand(getCmdListCommand(p))); 
				expression(table->variable, function->var_list, getCmdListCommand(p)); 
				break;

		}
		p = getCmdListProx(p);
	}
}

void semanticError(Program *program, Table *table){
	Function *function;
	//Checar erros em declaracoes e valores, tabela de simbolos:
	checkVariable(table->variable);
	calculateVariableValue(table->variable, table->variable);
	function = table->function;
	while(function != NULL){
		checkParamVoid(function->param);
		function = function->prox;
	}

	//Checar erros em funcoes: 
	function = program->function;
	while(function != NULL){
		function_return = 0;
		//Parametros:
		checkParamVoid(function->param);
		checkPrototype(table->function, function);
		//Variaveis:
		checkVariable(function->var_list);
		calculateVariableValue(table->variable, function->var_list);
		//Comandos:
		calculateCommands(program->function, table, function, function->commands);


		if (function_return == 0){
			if (function->type != VOID){
				errorNoReturnStatement(function);
			}
		}
		function = function->prox;
	}

}

//Gets-Sets
void setVariableType(Variable *var, int type){
	var->type = type;
}
void setVariableColuna(Variable *var, int coluna)
{
	var->coluna = coluna-strlen(var->name)-1;
}

void setVariableValue(Variable *var, Node *expression){
	var->value = expression;
}

void setVariablePointer(Variable *var, Node *pointer){
	var->pointer = getValueString(pointer);
}

void setVariableListType(Node *type, Variable *var){
	Variable *p;
	p = var;
	while(p != NULL){
		setVariableType(p, getType(type));
		p = p->prox;
	}
}
void setVariableLinha(Variable *var,char * linha)
{
	var->linha = malloc(sizeof(char)*(strlen(linha)+1));
	strcpy(var->linha,linha);
}
char * getVariableLinha(Variable * var)
{
	return var->linha;
}
int getVariableType(Variable *var){
	return var->type;
}
int getVariableColuna(Variable *var)
{
	return var->coluna;
}

int getVariableLine(Variable *var){
	return var->line;
}

char *getVariableName(Variable *var){
	return var->name;
}

Variable *getVariableProx(Variable *var){
	return var->prox;
}

Node *getVariableArray(Variable *var){
	return var->array;
}

Node *getVariableValue(Variable *var){
	return var->value;
}

char *getVariablePointer(Variable *var){
	return var->pointer;
}

char *getFunctionName(Function *function){
	return function->name;
}

int getFunctionLine(Function *function){
	return function->line;
}

//Print-Debug
void printfVariable(Variable *var, int op){
	Variable *p;
	p = var;
	if (p != NULL){
		while(p != NULL){
			if (op == 0){
				printf("\n %s", getIdType(p->type));
			} else if (op == 1){
				printf("%s", getIdType(p->type));
			} else{
				printf("\n   %s", getIdType(p->type));
			}
			if (p->pointer != NULL){
				printf(" %s", p->pointer);
			}
			printf(" %s", p->name);
			if (p->array != NULL){
				printf(" [ ");
				printfTree(p->array);
				printf(" ]");
			}
			if (p->value != NULL){
				printf(" = (");
				printfTree(p->value);
				printf(")");
			}
			p = p->prox;
			if (p != NULL && op != 0){
				printf(", ");
			}
		}
	}
}

void printfFunction(Function *function){
	Function *p;
	p = function;
	if (p != NULL){
		while(p != NULL){
			printf("\n %s", getIdType(p->type));
			if (p->pointer != NULL){
				printf(" %s", p->pointer);
			}
			printf(" %s (", p->name);
			if (p->param != NULL){
				printfVariable(p->param, 1);
			}
			printf(") {");
			if (p->var_list != NULL){
				printfVariable(p->var_list, 2);
			}
			if (p->commands != NULL){
				printfCmdList(p->commands);
			}
			printf("\n }\n");
			p = p->prox;
		}
	}
}
int getFunctionColuna(Function *f)
{
	return f->coluna;
}

void printfProgram(Program *program, Table *table){
	printf("\n ***** Declarations(Symbol Table) *****");
	printfFunction(table->function);
	printfVariable(table->variable, 0);
	printf("\n\n ***** Program *****");
	printfFunction(program->function);
}