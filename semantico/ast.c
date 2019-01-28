#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ast.h>
#include <cmd.h>
#include <table.h>
#include <error.h>
#include <sintatico.tab.h>
/*	Defines	*/

/*	Structures	*/
struct node{
	int id;
	int type;
	int value_number;
	char *value_string;
	char *pointer;
	int line;
	int coluna;
	char * linha;
	Node *left, *right;
};
/*	Variables	*/

/*	Functions	*/
int verifyOperatorType(Node *operator, Node *a, Node *b, Variable *table, Variable *function, Variable *var);
Node *expressionCalculator(Variable *table, Variable *function, Node *node, Variable *var, int constante);
char *getVariableTypeError(Variable *table, Variable *function, Node *node);

Node *createNode(int type, int value_number, char *value_string, int line,int coluna,char * linha){
	Node *new;
	new = (Node *) malloc(sizeof(Node));
	new->id = ID_NODE;
	new->type = type;
	new->value_number = value_number;
	new->value_string = value_string;
	new->pointer = NULL;
	new->line = line;
	new->left = NULL;
	new->right = NULL;
	new->coluna = coluna;
	if(linha!=NULL)
	{
	new->linha = malloc(sizeof(char)*(1+strlen(linha)));
	strcpy(new->linha,linha);
	}
	return new;
}

Node *createTreeNode(int type, int value_number, char *value_string, Node *left, Node *right, int line,int coluna,char * linha){
	Node *new;
	new = (Node *) malloc(sizeof(Node));
	new->id = ID_NODE;
	new->type = type;
	new->value_number = value_number;
	new->value_string = value_string;
	new->pointer = NULL;
	new->line = line;
	new->left = left;
	new->right = right;
	new->coluna = coluna;
	if(linha!=NULL)
	{
	new->linha = malloc(sizeof(char)*(1+strlen(linha)));
	strcpy(new->linha,linha);
	}
	return new;
}

int isOperating(Node *node){
	int operating = 0;
	switch(node->type){
		case NUM_HEXA: operating = 1; break;
		case NUM_OCTAL: operating = 1; break;
		case NUM_INTEGER: operating = 1; break;
		case CHARACTER: operating = 1; break;
		case STRING: operating = 1; break;
		case IDENTIFIER: operating = 1; break;
	}

	return operating;
}

int isNumber(Node *node){
	int number = 0;
	switch(node->type){
		case INT: number = 1; break;
		case NUM_HEXA: number = 1; break;
		case NUM_OCTAL: number = 1; break;
		case NUM_INTEGER: number = 1; break;
		case ID_CONS_DEFINE: number = 1; break;
	}

	return number;
}

int isCharacter(Node *node){
	int character = 0;
	switch(node->type){
		case CHARACTER: character = 1; break;
		case STRING: character = 1;	break;
		case IDENTIFIER: character = 1;	break;
	}
	return character;
}

Variable *getVarFromIdentifier(Variable *list, char *id){
	Variable *p, *var;
	var = NULL;
	p = list;
	if (id != NULL){
		while(p != NULL){
			if (strcmp(getVariableName(p), id) == 0){
				var = p;
			}
			p = getVariableProx(p);
		}
	}
	return var;
}
int getNodeColuna(Node * node)
{
	return node->coluna;
}
char *getNodeLinha(Node * node)
{
	return node->linha;
}

void *getVariableFromIdentifier(void *table, void *function, char *id){
	Variable *aux;
	aux = getVarFromIdentifier(function, id);
	if (aux == NULL){
		aux = getVarFromIdentifier(table, id);
	}
	return aux;
}

Node *getVarValue(Variable *table, Variable *function, Node *node){
	Node *aux;
	Variable *p;

	p = getVariableFromIdentifier(table, function, node->value_string);
	if (p != NULL){
		aux = getVariableValue(p);
		if (aux == NULL){
			node->value_number = 0;
		} else{
			node->value_number = aux->value_number;
		}
		node->type = getVariableType(p);
		node->pointer = getVariablePointer(p);
	} else{
		errorVarUndeclared(node->line, node->value_string,node->coluna);
		node->value_number = 0;
	}

	return node;
}

Node *solveGetValue(Variable *table, Variable *function, Node *node, Variable *var, int constante){
	int found;
	Variable *aux;
	if (node != NULL){
		if (isOperating(node)){
			if (getType(node) == CHARACTER){
				node->value_number = node->value_string[0];
			} else if (getType(node) == IDENTIFIER){
				if (constante){
					aux = getVariableFromIdentifier(table, function, node->value_string);
					if (aux != NULL){
						if (getVariableType(aux) != ID_CONS_DEFINE){
							errorInitializerNotConstant(var, node->value_string,node->coluna);	
						}
					}
				}
				node = getVarValue(table, function, node);
			} else if (getType(node) == STRING){
				node->pointer = "*";
			}
		} else{
			node = solveExpression(table, function, node, var, constante);
		}
	}
	return node;
}

char *charToString(char c)
{

	char *string;
	string = (char *) malloc(2 * sizeof(char));
	string[0] = c;
	string[1] = '\0';
	return string;
}

int printComparisonBetweenBinary(Variable *table, Variable *function, Variable *var, char *operand, Node *a, Node *b){
	errorComparisonBetweenBinary(getVariableLine(var), getVariableTypeError(table, function, a), getVariableTypeError(table, function, b), operand,getNodeColuna(a));
	return 1;
}

int printInvalidOperandsBinary(Variable *table, Variable *function, Variable *var, char *operand, Node *a, Node *b){
	errorInvalidOperandsBinary(getVariableLine(var), operand, getVariableTypeError(table, function, a), getVariableTypeError(table, function, b),getVariableColuna(var));
	return 1;
}

Node *solveExpression(void *table, void *function, Node *node, void *var, int constante){
	Variable *aux;
	aux = NULL;
	if (node != NULL){
		if (!isOperating(node)){
			node = expressionCalculator(table, function, node, var, constante);
		} else{
			if (!isNumber(node)){
				node = solveGetValue(table, function, node, var, constante);
			}
		}
	}

	return node;
}

Node *calculateDiv(Node *node, Node *a, Node *b, int line){
	if (b->value_number != 0){
		node->value_number = a->value_number / b->value_number;
	} else{
		errorDivisionByZero(line,a->coluna);
		node = NULL;
	}

	return node;
}

int checkLvalueIncrement(Variable *table, Variable *function, Node *node, Node *b, Variable *var){
	int erro = 0;
	Variable *aux;
	if (b->value_string != NULL){
		aux = getVariableFromIdentifier(table, function, b->value_string);
		if (aux == NULL){
			erro = 1;
			errorLvalueIncrement(getVariableLine(var),getVariableColuna(var));
		}
	} else{
		erro = 1;
		errorLvalueIncrement(getVariableLine(var),getVariableColuna(var));
	}
	return erro;
}

int checkLvalueUnary(Variable *table, Variable *function, Node *node, Node *b, char *operand, Variable *var){
	int erro = 0;
	Variable *aux;
	if (b->value_string != NULL){
		aux = getVariableFromIdentifier(table, function, b->value_string);
		if (aux == NULL){
			erro = 1;
			errorLvalueUnary(getVariableLine(var), operand,getVariableColuna(var));
		}
	} else{
		erro = 1;
		errorLvalueUnary(getVariableLine(var), operand,getVariableColuna(var));
	}
	return erro;
}

int isVariableNumber(Variable *var){
	int number = 0;
	switch(getVariableType(var)){
		case INT: number = 1; break;
		case NUM_HEXA: number = 1; break;
		case NUM_OCTAL: number = 1; break;
		case NUM_INTEGER: number = 1; break;
		case ID_CONS_DEFINE: number = 1; break;
	}

	return number;
}


int isVariableChar(Variable *var){
	int character = 0;
	switch(getVariableType(var)){
		case CHARACTER: character = 1; break;
		case STRING: character = 1;	break;
		case IDENTIFIER: character = 1;	break;
		case CHAR: character = 1; break;
	}

	return character;
}

char *getTypeVariableNode(Variable *var, Node *node){
	char *string = NULL;
	if (node != NULL){
		if (var != NULL){
			if (isVariableNumber(var)){
				if (node->pointer != NULL){
					string = (char *) malloc((strlen(node->pointer) + strlen("int") + 1) * sizeof(char));
					strcpy(string, "int");
					strcat(string, node->pointer);
				} else{
					string = (char *) malloc((strlen("int") + 1) * sizeof(char));
					strcpy(string, "int");
				}
			} else if (isVariableChar(var)){
				if (node->pointer != NULL){
					string = (char *) malloc((strlen(node->pointer) + strlen("char") + 1) * sizeof(char));
					strcpy(string, "char");
					strcat(string, node->pointer);
				} else{
					string = (char *) malloc((strlen("char") + 1)  * sizeof(char));
					strcpy(string, "char");
				}
			} else{
				if (node->pointer != NULL){
					string = (char *) malloc((strlen(node->pointer) + strlen("void") + 1) * sizeof(char));
					strcpy(string, "void");
					strcat(string, node->pointer);
				} else{
					string = (char *) malloc((strlen("void") + 1)  * sizeof(char));
					strcpy(string, "void");
				}
			}
		} else{
			if (isNumber(node)){
				if (node->pointer != NULL){
					string = (char *) malloc((strlen(node->pointer) + strlen("int") + 1) * sizeof(char));
					strcpy(string, "int");
					strcat(string, node->pointer);
				} else{
					string = (char *) malloc((strlen("int") + 1) * sizeof(char));
					strcpy(string, "int");
				}
			} else if (isCharacter(node)){
				if (node->pointer != NULL){
					string = (char *) malloc((strlen(node->pointer) + strlen("char") + 1) * sizeof(char));
					strcpy(string, "char");
					strcat(string, node->pointer);
				} else{
					string = (char *) malloc((strlen("char") + 1) * sizeof(char));
					strcpy(string, "char");
				}
			} else{
				if (node->pointer != NULL){
					string = (char *) malloc((strlen(node->pointer) + strlen("void") + 1) * sizeof(char));
					strcpy(string, "void");
					strcat(string, node->pointer);
				} else{
					string = (char *) malloc((strlen("void") + 1) * sizeof(char));
					strcpy(string, "void");
				}
			}
		}
	}
	return string;
}

int getTypeWarningTernary(Variable *var, Node *node){
	int result = 0;
	int number_void = 0;
	int number_char = 1;
	int number_int = 2;
	int number_void_pointer = 3;
	int number_char_pointer = 4;
	int number_int_pointer = 5;
	if (node != NULL){
		if (var != NULL){
			if (isVariableNumber(var)){
				if (node->pointer != NULL){
					result = 5;
				} else{
					result = 2;
				}
			} else if (isVariableChar(var)){
				if (node->pointer != NULL){
					result = 4;
				} else{
					result = 1;
				}
			} else{
				if (node->pointer != NULL){
					result = 3;
				} else{
					result = 0;
				}
			}
		} else{
			if (isNumber(node)){
				if (node->pointer != NULL){
					result = 5;
				} else{
					result = 2;
				}
			} else if (isCharacter(node)){
				if (node->pointer != NULL){
					result = 4;
				} else{
					result = 1;
				}
			} else{
				if (node->pointer != NULL){
					result = 3;
				} else{
					result = 0;
				}
			}
		}
	}
	return result;
}

Node *expressionCalculator(Variable *table, Variable *function, Node *node, Variable *var, int constante){
	Node *a, *b, *aux;
	Variable *var_aux;
	char *type_one, *type_two; 
	int ternary_one, ternary_two;


	if (getType(node) == INC || getType(node) == DEC){
		a = solveGetValue(table, function, node->left, var, constante);
		switch(getType(node)){
			case INC: 
				if (checkLvalueIncrement(table, function, node, a, var)){
					node = NULL;
				} else{
					node->value_number = ++a->value_number;
				}
				break;
			case DEC: 
				if (checkLvalueUnary(table, function, node, a, "--", var)){
					node = NULL;
				} else{
					node->value_number = ++a->value_number; 
				}
			break;
		}
	} else if (getType(node) == TERNARY_CONDITIONAL) {
		a = (node->right)->left;
		b = (node->right)->right;
		a = solveGetValue(table, function, a, var, constante);
		b = solveGetValue(table, function, b, var, constante);
		if (a->value_string != NULL){
			var_aux = getVariableFromIdentifier(table, function, a->value_string);
			if (var_aux != NULL){
				if (getVariablePointer(var_aux) != NULL){
					a->pointer = getVariablePointer(var_aux);
				}
			}
			type_one = getTypeVariableNode(var_aux, a);
			ternary_one = getTypeWarningTernary(var_aux, a);
		}
		if (b->value_string != NULL){
			var_aux = getVariableFromIdentifier(table, function, b->value_string);
			if (var_aux != NULL){
				if (getVariablePointer(var_aux) != NULL){
					b->pointer = getVariablePointer(var_aux);
				}
			}
			type_two = getTypeVariableNode(var_aux, b);
			ternary_two = getTypeWarningTernary(var_aux, b);
		}
		if (ternary_one != ternary_two){
			warningConditionalExpression(node->line, type_one, type_two,getVariableColuna(var));
		}
		if (ternary_one > ternary_two){
			node = a;
		} else{
			node = b;
		}
	} else{
		if (node->left != NULL && node->right != NULL){
			a = solveGetValue(table, function, node->left, var, constante);
			b = solveGetValue(table, function, node->right, var, constante);
			if (!verifyOperatorType(node, a, b, table, function, var)){
				switch(getType(node)){
					case AST_UNARY_EXPRESSION:
						switch(getType(a)){
							case PLUS:
								if (checkLvalueUnary(table, function, node, b, charToString('+'), var)){
									node = NULL;
								} else{
									node->value_number = +b->value_number;
								}
								break;
							case MINUS: 
								if (checkLvalueUnary(table, function, node, b, charToString('-'), var)){
									node = NULL;
								} else{
									node->value_number = -b->value_number;
								}
								break;
							case MULTIPLY: 
								if (checkLvalueUnary(table, function, node, b, charToString('*'), var)){
									node = NULL;
								} else{
									node->value_number = (getVarValue(table, function, b))->value_number;
								}
								break;
							case BITWISE_NOT: 
								if (checkLvalueUnary(table, function, node, b, charToString('~'), var)){
									node = NULL;
								} else{
									node->value_number = ~b->value_number;
								}
								break;
							case NOT: 
								if (checkLvalueUnary(table, function, node, b, charToString('!'), var)){
									node = NULL;
								} else{
									node->value_number = !b->value_number;
								}
								break;
							case BITWISE_AND:
								if (checkLvalueUnary(table, function, node, b, charToString('&'), var)){
									node = NULL;
								} else{
									a->pointer = (char *) malloc(2 * sizeof(char));
									strcpy(a->pointer, "*");
									node->value_number = 0;
								}
								break;
						}
						break;
					case AST_POSTFIX_EXPRESSION:	
						a->pointer = (char *) malloc(2 * sizeof(char));
						strcpy(a->pointer, "*");
						node->value_number = 0;
						if (!isNumber(node->right)){
							if (getType(node->right) == IDENTIFIER){
								if (getVariableFromIdentifier(table, function, (node->right)->value_string) == NULL){
									errorArraySubscriptNotInteger(node->line,node->coluna);
								} else{
									if (getVariablePointer(getVariableFromIdentifier(table, function, (node->right)->value_string)) != NULL){
										errorArraySubscriptNotInteger(node->line,node->coluna);
									}
								}
							} else{
								errorArraySubscriptNotInteger(node->line,node->coluna);
							}
						}
						if (a->value_string != NULL){
							var_aux = getVariableFromIdentifier(table, function, a->value_string);
							if (var_aux != NULL){
								if (getVariableArray(var_aux) != NULL){
									if (b->value_number >= getVariableArray(var_aux)->value_number){
										warningArrayOutOfBounds(node->line,getVariableColuna(var));
									}
								}
							}
						}

						break;
					case PLUS: node->value_number = a->value_number + b->value_number; break;
					case MINUS: node->value_number = a->value_number - b->value_number; break;
					case MULTIPLY: node->value_number = a->value_number * b->value_number; break;
					case DIV: node = calculateDiv(node, a, b, getVariableLine(var)); break;
					case REMAINDER: node->value_number = a->value_number % b->value_number; break;
					case BITWISE_AND: node->value_number = a->value_number & b->value_number; break;
					case BITWISE_OR: node->value_number = a->value_number | b->value_number; break;
					case BITWISE_XOR: node->value_number = a->value_number ^ b->value_number; break;
					case LOGICAL_AND: node->value_number = a->value_number && b->value_number; break;
					case LOGICAL_OR: node->value_number = a->value_number || b->value_number; break;
					case EQUAL: node->value_number = a->value_number == b->value_number; break;
					case NOT_EQUAL: node->value_number = a->value_number != b->value_number; break;
					case LESS_THAN: node->value_number = a->value_number < b->value_number; break;
					case GREATER_THAN: node->value_number = a->value_number > b->value_number; break;
					case LESS_EQUAL: node->value_number = a->value_number <= b->value_number; break;
					case GREATER_EQUAL: node->value_number = a->value_number >= b->value_number; break;
					case R_SHIFT:
						if (b->value_number >= 0){
							a->value_number >> b->value_number;
						} else{
							errorRShiftNegative(getVariableLine(var),getVariableColuna(var));
						} 
						break;
					case L_SHIFT:
						if (b->value_number >= 0){ 
							node->value_number = a->value_number << b->value_number; 
						} else{
							errorLShiftNegative(getVariableLine(var),getVariableColuna(var));
						}
						break;
				}
				if (node != NULL){
					switch(node->type){
						case BITWISE_AND: node->pointer = NULL; break;
						case BITWISE_OR: node->pointer = NULL; break;
						case BITWISE_XOR: node->pointer = NULL; break;
						case LOGICAL_AND: node->pointer = NULL; break;
						case LOGICAL_OR: node->pointer = NULL; break;
						case EQUAL: node->pointer = NULL; break;
						case NOT_EQUAL: node->pointer = NULL; break;
						case LESS_THAN: node->pointer = NULL; break;
						case GREATER_THAN: node->pointer = NULL; break;
						case LESS_EQUAL: node->pointer = NULL; break;
						case GREATER_EQUAL: node->pointer = NULL; break;
						default: 
							if (a->pointer != NULL){
								node->pointer = a->pointer;
							} else{
								node->pointer = b->pointer;
							}
							break;
					}
					if (node->type == AST_CAST){
						node->type = a->type;
						node->pointer = a->pointer;
					} else{
						node->type = NUM_INTEGER;
					}
					if ((node->left)->value_string != NULL){
						node->value_string = (node->left)->value_string;
					} else{
						node->value_string = (node->right)->value_string;
					}
					node->left = NULL;
					node->right = NULL;
				}
			} else{
				node = NULL;
			}
		}
	}

	return node;
}

int verifyPointers(Variable *table, Variable *function, Node *a, Node *b, Variable *var, char *operand){
	int erro = 0;
	Variable *var_a, *var_b;
	int pointer_a = 0, pointer_b = 0;
	if (a != NULL && b != NULL){
		var_a = getVariableFromIdentifier(table, function, a->value_string);
		var_b = getVariableFromIdentifier(table, function, b->value_string);
		if (a->pointer != NULL){
			pointer_a = strlen(a->pointer);
		}
		if (b->pointer != NULL){
			pointer_b = strlen(b->pointer);
		}
		if (pointer_a != pointer_b){
			if ((pointer_a != 0 && pointer_b == 0) || (pointer_a == 0 && pointer_b != 0)){
				warningComparisonBetweenBinary(a->line, getVariableTypeError(table, function, a), getVariableTypeError(table, function, b), operand,a->coluna);
			} else{
				erro = printComparisonBetweenBinary(table, function, var, operand, a, b);
			}
		} else{
			if (var_a == NULL && var_b != NULL){
				if (getVariableType(var_a) != getVariableType(var_b)){
					erro = printComparisonBetweenBinary(table, function, var, operand, a, b);
				}
			} else{
				if (getType(a) != getType(b)){
					erro = printComparisonBetweenBinary(table, function, var, operand, a, b);
				}
			}
		}
	}
	
	return erro;
}

int verifyOperatorType(Node *operator, Node *a, Node *b, Variable *table, Variable *function, Variable *var){
	int erro = 0;
	switch(getType(operator)){
		//Unary Operators
		case AST_UNARY_EXPRESSION: 
			switch(getType(a)){
				case PLUS: 
					if(b->pointer != NULL){
						erro = errorUnaryPlus(getVariableLine(var),getVariableColuna(var));
					}
					break;

				case MINUS: 
					if(b->pointer != NULL){
						erro = errorUnaryMinus(getVariableLine(var));
					}
					break;

				case MULTIPLY: 
					if(b->pointer == NULL){
						erro = errorInvalidArgumentUnary(getVariableLine(var), charToString('*'), getVariableTypeError(table, function, b),getVariableColuna(var));
					}
					break;

				case BITWISE_NOT: 
					if(b->pointer != NULL){
						erro = errorInvalidArgumentUnary(getVariableLine(var), charToString('~'), getVariableTypeError(table, function, b),getVariableColuna(var));
					}
					break;
			}
			break;

		//Binary Operators
		case PLUS:
			if (b->pointer != NULL){
				erro = printInvalidOperandsBinary(table, function, var, charToString('+'), a, b);
			} 
			break;

		case MINUS:
			if (b->pointer != NULL){
				erro = printInvalidOperandsBinary(table, function, var, charToString('-'), a, b);
			}
			break;

		case MULTIPLY:
			if (a->pointer != NULL || b->pointer != NULL){
				erro = printInvalidOperandsBinary(table, function, var, charToString('*'), a, b);
			}
			break;

		case DIV:
			if (a->pointer != NULL || b->pointer != NULL){
				erro = printInvalidOperandsBinary(table, function, var, charToString('/'), a, b);
			}
			break;

		case REMAINDER:
			if (a->pointer != NULL || b->pointer != NULL){
				erro = printInvalidOperandsBinary(table, function, var, charToString('%'), a, b);
			}
			break;

		case BITWISE_AND:
			if (a->pointer != NULL || b->pointer != NULL){
				erro = printInvalidOperandsBinary(table, function, var, charToString('&'), a, b);
			}
			break;

		case BITWISE_OR:
			if (a->pointer != NULL || b->pointer != NULL){
				erro = printInvalidOperandsBinary(table, function, var, charToString('|'), a, b);
			}
			break;

		case BITWISE_XOR:
			if (a->pointer != NULL || b->pointer != NULL){
				erro = printInvalidOperandsBinary(table, function, var, charToString('^'), a, b);
			}
			break;

		case EQUAL:
			if (a->pointer != NULL || b->pointer != NULL){
				erro = verifyPointers(table, function, a, b, var, "==");
			}
			break;

		case NOT_EQUAL:
			if (a->pointer != NULL || b->pointer != NULL){
				erro = verifyPointers(table, function, a, b, var, "!=");
			}
			break;

		case LESS_THAN:
			if (a->pointer != NULL || b->pointer != NULL){
				erro = verifyPointers(table, function, a, b, var, charToString('<'));
			}
			break;

		case GREATER_THAN:
			if (a->pointer != NULL || b->pointer != NULL){
				erro = verifyPointers(table, function, a, b, var, charToString('>'));
			}
			break;

		case LESS_EQUAL:
			if (a->pointer != NULL || b->pointer != NULL){
				erro = verifyPointers(table, function, a, b, var, "<=");
			}
			break;

		case GREATER_EQUAL:
			if (a->pointer != NULL || b->pointer != NULL){
				erro = verifyPointers(table, function, a, b, var, ">=");
			}
			break;

		case R_SHIFT:
			if (a->type == VOID || isCharacter(a)){
				if (a->pointer == NULL){
					warningRightShift(getNodeLine(a),getNodeColuna(a));
				} else{
					if (isNumber(b) || b->pointer != NULL){
						warningRightShift(getNodeLine(a),getNodeColuna(a));
					}
				}
			} else{
				if (isNumber(b) && b->pointer == NULL){
					if (b->value_number >= a->value_number){
						warningRightShift(getNodeLine(a),getNodeColuna(a));
					}
				} else{
					if (b->pointer != NULL){
						warningRightShift(getNodeLine(a),getNodeColuna(a));
					}
				}
			}
			if (b->pointer != NULL){
				erro = 1;
				errorCannotConvert(getNodeLine(a), getVariableTypeError(table, function, b),getNodeColuna(a));
			}
			break;

		case L_SHIFT:
			if (a->type == VOID || isCharacter(a)){
				if (a->pointer == NULL){
					warningLeftShift(getNodeLine(a),getNodeColuna(a));
				} else{
					if (isNumber(b) || b->pointer != NULL){
						warningLeftShift(getNodeLine(a),getNodeColuna(a));
					}
				}
			} else{
				if (isNumber(b) && b->pointer == NULL){
					if (b->value_number >= a->value_number){
						warningLeftShift(getNodeLine(a),getNodeColuna(a));
					}
				} else{
					if (b->pointer != NULL){
						warningLeftShift(getNodeLine(a),getNodeColuna(a));
					}
				}
			}
			if (b->pointer != NULL){
				erro = 1;
				errorCannotConvert(getNodeLine(a), getVariableTypeError(table, function, b),getNodeColuna(a));
			}
			break;

			case AST_CAST:
				if (a->type == CHAR || a->type == VOID){
					if (isNumber(b) || b->pointer != NULL){
						warningCast(getNodeLine(a), getVariableTypeError(table, function, b), getVariableTypeError(table, function, a),getNodeColuna(a));
					}
				} else if (isNumber(a)){
					if (isCharacter(b) && b->pointer == NULL){
						warningCast(getNodeLine(a), getVariableTypeError(table, function, b), getVariableTypeError(table, function, a),getNodeColuna(a));
					}
				}
			break;

	}

	return erro;
}

//Gets-Sets
int getId(void *obj){
	return *(int *)obj;
}

int getType(Node *node){
	return node->type;
}

int getValueNumber(Node *node){
	return node->value_number;
}

char *getValueString(Node *node){
	return node->value_string;
}

int getNodeLine(Node *node){
	return node->line;
}

char *getNodePointer(Node *node){
	return node->pointer;
}

Node *getNodeLeft(Node *node){
	return node->left;
}

Node *getNodeRight(Node *node){
	return node->right;
}

void setNodeType(Node *node, int type){
	node->type = type;
}

void setFunctionCallType(Node *node){
	if (node->value_string == NULL){
		node->type = ID_FUNCTION_CALL;
		if (node->left != NULL){
			setNodeType(node->left, ID_FUNCTION_CALL);
		}
	} else{
		setNodeType(node, ID_FUNCTION_CALL);
	}
}

void setPointerString(Node *node){
	node->pointer = (char *) malloc(2 * sizeof(char));
	node->pointer[0] = '*';
	node->pointer[1] = '\0';
}

char *getVariableTypeError(Variable *table, Variable *function, Node *node){
	char *result = NULL;
	int type = 0;
	int pointer = 0;
	Variable *p;
	Node *aux;
	
	if (node->pointer != NULL){
		pointer = strlen(node->pointer);
	}
	switch(getType(node)){
		case NUM_INTEGER:
			result = (char *) malloc((strlen("int") + pointer + 1) * sizeof(char));
			strcpy(result, "int");
			if (node->pointer != NULL){
				strcat(result, node->pointer);
			}
			break;

		case NUM_HEXA:
			result = (char *) malloc((strlen("int") + pointer + 1) * sizeof(char));
			strcpy(result, "int");
			if (node->pointer != NULL){
				strcat(result, node->pointer);
			}
			break;

		case NUM_OCTAL:
			result = (char *) malloc((strlen("int") + pointer + 1) * sizeof(char));
			strcpy(result, "int");
			if (node->pointer != NULL){
				strcat(result, node->pointer);
			}
			break;

		case VOID:
			result = (char *) malloc((strlen("void") + pointer + 1) * sizeof(char));
			strcpy(result, "void");
			if (node->pointer != NULL){
				strcat(result, node->pointer);
			}
			break;

		case CHAR:
			result = (char *) malloc((strlen("char") + pointer + 1) * sizeof(char));
			strcpy(result, "char");
			if (node->pointer != NULL){
				strcat(result, node->pointer);
			}
			break;

		case INT:
			result = (char *) malloc((strlen("int") + pointer + 1) * sizeof(char));
			strcpy(result, "int");
			if (node->pointer != NULL){
				strcat(result, node->pointer);
			}
			break;

		case STRING:
			result = (char *) malloc((strlen("char") + pointer + 1) * sizeof(char));
			strcpy(result, "char");
			if (node->pointer != NULL){
				strcat(result, node->pointer);
			}
			break;
		case ID_CONS_DEFINE:
			result = (char *) malloc((strlen("int") + pointer + 1) * sizeof(char));
			strcpy(result, "int");
			if (node->pointer != NULL){
				strcat(result, node->pointer);
			}
			break;

		case IDENTIFIER:
			p = getVariableFromIdentifier(table, function, node->value_string);
			aux = createNode(getVariableType(p), (getVariableValue(p))->value_number, node->value_string, getVariableLine(p),getVariableColuna(p),getVariableLinha(p));
			aux->pointer = getVariablePointer(p);
			result = getVariableTypeError(table, function, aux);
			break;
	}

	return result;
}

char *getIdType(int id){
	switch(id){
		case VOID:
			return "void";
		case CHAR:
			return "char";
		case INT:
			return "int";
		case ID_CONS_DEFINE:
			return "int";
		default:
			return NULL;
	}
}

//Print-Debug
void printfTree(Node *tree){
	if(tree != NULL){
		printfTree(tree->left);
		printfTree(tree->right);
		switch(tree->type){
			case COMMA: printf(", "); break;
			case ASSIGN: printf("= "); break;
			case ADD_ASSIGN: printf("+= "); break;
			case MINUS_ASSIGN: printf("-= "); break;
			case COLON: printf(": "); break;
			case TERNARY_CONDITIONAL: printf("? "); break;
			case LOGICAL_OR: printf("|| "); break;
			case LOGICAL_AND: printf("&& "); break;
			case BITWISE_NOT: printf("~ "); break;
			case BITWISE_OR: printf("| "); break;
			case BITWISE_XOR: printf("^ "); break;
			case BITWISE_AND: printf("& "); break;
			case NOT_EQUAL: printf("!= "); break;
			case EQUAL: printf("== "); break;
			case GREATER_EQUAL: printf(">= "); break;
			case LESS_EQUAL: printf("<= "); break;
			case GREATER_THAN: printf("> "); break;
			case LESS_THAN: printf("< "); break;
			case L_SHIFT: printf("<< "); break;
			case R_SHIFT: printf(">> "); break;
			case PLUS: printf("+ "); break;
			case MINUS: printf("- "); break;
			case MULTIPLY: printf("* "); break;
			case DIV: printf("/ "); break;
			case REMAINDER: printf("%c ", '%'); break;
			case AST_POINTER: printf("%s ", tree->value_string); break;
			case AST_CAST: printf("CAST"); break;
			case NOT: printf("! "); break;
			case AST_UNARY_EXPRESSION: printf("UNARY "); break;
			case INC: printf("++ "); break;
			case DEC: printf("-- "); break;
			case AST_POSTFIX_EXPRESSION: printf("POSTFIX "); break;
			case STRING: printf("%s ", tree->value_string); break;
			case CHARACTER: printf("%s ", tree->value_string); break;
			case IDENTIFIER: printf("%s ", tree->value_string); break;
			case NUM_INTEGER: printf("%d ", tree->value_number); break;
			case NUM_OCTAL: printf("%d ", tree->value_number); break;
			case NUM_HEXA: printf("%d ", tree->value_number); break;
			case VOID: printf("void "); break;
			case CHAR: printf("char "); break;
			case INT: printf("int "); break;
			case ID_FUNCTION_CALL: if (tree->value_string == NULL){printf("%s()", (tree->left)->value_string);} else{printf("%s()", tree->value_string);} break;
			default:printf("ERROR: INVALID TYPE ");break;
		}
	}
}