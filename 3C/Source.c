#include <stdio.h>
#include <stdlib.h>    
#include "input.h"
#include "stacks.h"  //type is stack_t

/*Logical Operators
	Not	!
	And	*
	Or	+
    Xor	^
  Equal	=
Implies >
*/

struct variable {
	int a,b,c,d,e,result;
};
struct variable abcde;
struct variable* results;

char* infixToPostfix(char* exp,int* len)
{
	int i, k,length = len[0], lengthDiff = 0;

	// Create a stack of capacity equal to expression size  
	stack_t* stack = createStack(length);

	for (i = 0, k = -1; i < length; ++i)
	{
		// If the scanned character is an operand, add it to output. 
		if (isOperand(exp[i]))
			exp[++k] = exp[i];

		// If the scanned character is an ‘(‘, push it to the stack. 
		else if (exp[i] == '(') {
			lengthDiff--;
			push(stack, exp[i]);
		}

		// If the scanned character is an ‘)’, pop and output from the stack  
		// until an ‘(‘ is encountered. 
		else if (exp[i] == ')')
		{
			lengthDiff--;
			while (!isEmpty(stack) && peek(stack) != '(')
				exp[++k] = pop(stack);
			if (!isEmpty(stack) && peek(stack) != '(')
				return "invalid expression"; // invalid expression              
			else
				pop(stack);
		}
		else // an operator is encountered 
		{
			while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack)))
				exp[++k] = pop(stack);
			push(stack, exp[i]);
		}
	}

	// pop all the operators from the stack 
	while (!isEmpty(stack))
		exp[++k] = pop(stack);  
	len[0] = lengthDiff+length-1;
	//exp[++k] = '\0';
	return exp;
}

int evaluatePostfix(char* exp, int length)
{
	// Create a stack of capacity equal to expression size 
	stack_t* stack = createStack(length);
	int i;

	// Scan all characters one by one 
	for (i = 0; i < length; ++i)
	{
		// If the scanned character is an operand (number here), 
		// push it to the stack. 
		if (isOperand(exp[i]))
			push(stack, charToVal(exp[i]));

		// If the scanned character is an operator, pop two 
		// elements from stack apply the operator 
		else if (exp[i] == '!') {
			int val1 = pop(stack);
			push(stack,!(val1));
		} else 
		{	
			int val1 = pop(stack);
			int val2 = pop(stack);
			switch (exp[i])
			{
			case '+': push(stack, (val2 || val1)); break;
			case '^': push(stack, val2 != val1); break;
			case '*': push(stack, val2 * val1); break;
			case '=': push(stack, val2 == val1); break;
			case '>': push(stack, val2 || !(val1)); break;
			}
		}
	}
	return pop(stack);
}

int checkIfNecesary(struct variable abcde, int a, int b, int c, int d, int e, int n) {
	if (n > 0 && abcde.a != a) 
		return 1;
	if (n > 1 && abcde.b != b) 
		return 1;
	if (n > 2 && abcde.c != c) 
		return 1;
	if (n > 3 && abcde.d != d) 
		return 1;
	if (n > 4 && abcde.e != e) 
		return 1;
	return 0;
}

struct variable set(struct variable result, int a, int b, int c, int d, int e) {
	result.a = a;
	result.b = b;
	result.c = c;
	result.d = d;
	result.e = e;
	return result;
}

void disjunctive(struct variable result, int numOfVariables, int placeplus) {
	int i;
	if (placeplus)
		printf("+");

	for (i = 0; i < numOfVariables; i++) {
		switch (i) {
		case 0:
			(result.a) ? 0:printf("!");
			printf("a");
			break;
		case 1:
			(result.b) ? 0 : printf("!");
			printf("b");
			break;
		case 2:
			(result.c) ? 0 : printf("!");
			printf("c");
			break;
		case 3:
			if (!(result.d))
				printf("!");
			printf("d");
			break;
		case 4:
			if (!(result.e))
				printf("!");
			printf("e");
			break;
		}
		if (!(i == numOfVariables - 1)) {
			printf("*");
		}
	}
}
void conjunctive(struct variable result, int numOfVariables, int placemult) {
	int i;
	if (placemult)
		printf("*");
	printf("(");
	for (i = 0; i < numOfVariables; i++) {
		switch (i) {
		case 0:
			if (result.a)
				printf("!");
			printf("a");
			break;
		case 1:
			if (result.b)
				printf("!");
			printf("b");
			break;
		case 2:
			if (result.c)
				printf("!");
			printf("c");
			break;
		case 3:
			if (result.d)
				printf("!");
			printf("d");
			break;
		case 4:
			if (result.e)
				printf("!");
			printf("e");
			break;
		}
		if (!(i == numOfVariables - 1)) {
			printf("+");
		}
	}
	printf(")");
}

void increment(int numOfVariables, char* postfixed, int length) {
	int a, b, c, d, e, index = 0;
	abcde = set(abcde,0,0,0,0,0);
	results[index].result = evaluatePostfix(postfixed, length);
	results[index] = set(results[index], 0, 0, 0, 0, 0);
	index++; 

	for(a = 0; a < 2; a++)
		for(b = 0; b < 2; b++)
			for(c = 0; c < 2; c++)
				for(d = 0; d < 2; d++)
					for (e = 0; e < 2; e++) 
						if (checkIfNecesary(abcde, a, b, c, d, e, numOfVariables)) {
							abcde =	set(abcde, a, b, c, d, e);
							results[index] = set(results[index], a, b, c, d, e);
							results[index].result = evaluatePostfix(postfixed, length);
							index++;
						}
					
}

int charToVal(char ch) {
	if (ch == 'a')
		return abcde.a;
	if (ch == 'b')
		return abcde.b;
	if (ch == 'c')
		return abcde.c;
	if (ch == 'd')
		return abcde.d;
	if (ch == 'e')
		return abcde.e;

	return 0;
}


int main() {
	int i,length,numOfVariables;

	char* arr = inputText(&length);
	printf("Infix:  ");
	printArr(arr, length);

	char* postfixed = infixToPostfix(arr,&length);

	numOfVariables = numOfVar(postfixed, length);
	printf("Postfix:");
	printArr(postfixed,length);

	results = (struct variable*)malloc(sizeof(struct variable)* pow(2,numOfVariables));

	increment(numOfVariables, postfixed,length);

	printf("\ntrue:");
	for (i = 0; i < pow(2,numOfVariables); i++) {
		if (results[i].result)
			printf(" %d", i);
	}
	printf("\nfalse:");
	for (i = 0; i < pow(2, numOfVariables); i++) {
		if (!(results[i].result))
			printf(" %d", i);
	}
	printf("\n\nDisjunctive form: \n");
	int trig = 0;
	for (i = 0; i < pow(2, numOfVariables); i++) 
		if (results[i].result) {
			disjunctive(results[i],numOfVariables, trig);
			trig = 1;
		}
	printf("\nConjunctive form: \n");
	trig = 0;
	for (i = 0; i < pow(2, numOfVariables); i++)
		if (!(results[i].result)) {
			conjunctive(results[i], numOfVariables, trig);
			trig = 1;
		}
	free(results);
	//free(arr);
	free(postfixed);
	return 0;
}