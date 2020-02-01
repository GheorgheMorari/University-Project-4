#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct StackStruct {
	int top;
	unsigned capacity;
	int* array;
} stack_t;

int isEmpty(stack_t* stack)
{
	return stack->top == -1;
}

int pop(stack_t* stack)
{
	if (isEmpty(stack))
		return INT_MIN;
	return stack->array[stack->top--];
}

int peek(stack_t* stack)
{
	if (isEmpty(stack))
		return INT_MIN;
	return stack->array[stack->top];
}
void push(stack_t* stack, int item)
{
	stack->array[++stack->top] = item;
}

 stack_t* createStack(unsigned capacity)
{
	stack_t* stack = (stack_t*) malloc(sizeof(stack_t));

	if (!stack)
		return NULL;

	stack->top = -1;
	stack->capacity = capacity;

	stack->array = (int*)malloc(stack->capacity * sizeof(int));

	if (!stack->array)
		return NULL;
	return stack;
}

