// THAT WAS MADE BY FOLLOWING THE DSA LAB SCRIPTS.
// SOME CODE MAY BE COPYED FROM THE DSA LAB SCRIPTS.
// http://www.elec.york.ac.uk/internal_web/meng/yr2/modules/DSA/DSA/Labs/Scripts/Lab7-StacksAndQueues.pdf
// THIS IS A NON-GENERIC STACK AS GENERIC PROGRAMMING IN C IS A HARD :'(

//TODO:: maybe look at this http://www.robertgamble.net/2012/01/c11-generic-selections.html and make it generic ish.

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"


/// ====
/// Defines
/// ====
#define INITIAL_STACK_LENGTH 10

/// ====
/// Prototypes
/// ====


/// ====
/// Structures
/// ====
struct Stack
{
	int length;
	int top;
	int *array;
};

/// ====
/// Constructors and Destructor
/// ====
Stack *stack_Constructor()
{
	Stack *stack;
	stack = malloc(sizeof(Stack));

	stack->length = INITIAL_STACK_LENGTH;
	stack->top = 0;
	stack->array = malloc(stack->length * sizeof(int));

	return stack;
}

void stack_Deconstructor(Stack *stack)
{
	free(stack->array);
	free(stack);
}

/// ====
/// Public Functions
/// ====

// Checks to see weather the stack is empty
// Returns 1 if stack is empty
// Returns 0 if stack isnt empty
// Returns -1 if stack is NULL
int stack_isEmpty(Stack *stack)
{
	if (stack == NULL)
	{
		return -1;
	}

	return (stack->top == 0) ? 1 : 0;

}

// Checks to see weather the stack is full
// Returns 1 if stack is full
// Returns 0 if stack isnt full
// Returns -1 if stack is NULL
int stack_isFull(Stack *stack)
{
	if (stack == NULL)
	{
		return -1;
	}

	return (stack->top == (stack->length - 1)) ? 1 : 0;
}

// Pushes an item onto the top of the stack
// Returns 1 if push was successful
// Returns 0 if push was unsuccessful
// Returns -1 if stack is NULL
int stack_Push(Stack *stack, int value)
{
	if (stack == NULL)
	{
		return -1;
	}

	if (stack_isFull(stack) != 0)
	{
		stack->length *= 2;
		stack->array = realloc(stack->array, stack->length * sizeof(int)); 
		// TODO: make this try mallocing a diff buffer if it failes not just die
		if (stack->array == NULL)
		{
			// realloc failed thats bad
			return -1;
		}
	}

	stack->array[stack->top] = value;
	stack->top++;

	return 1;
}

// Pops an item off of the top of the stack
// Returns 1 if pop was successful
// Returns 0 if pop was unsuccessful
// Returns -1 if stack is NULL
int stack_Pop(Stack *stack, int *popped)
{
	if (stack == NULL)
	{
		return -1;
	}

	if (stack_isEmpty(stack) == 0)
	{
		stack->top--;
		(*popped) = stack->array[stack->top];
		return 1;
	}
	else
	{
		// if there's nothing on the stack we cannot pop something off of it
		return 0;
	}
}

// Pops an item off of the top of the stack but does not provide access to the value that was there.
// Returns 1 if pop was successful
// Returns 0 if pop was unsuccessful
// Returns -1 if stack is NULL
int stack_Pop_nv(Stack *stack)
{
	if (stack == NULL)
	{
		return -1;
	}

	int tmp;

	return stack_Pop(stack, &tmp);
}

// Peek an item in the stack
// Returns 1 if peek was successful
// Returns 0 if peek was unsuccessful
// Returns -1 if stack is NULL
int stack_Peek(Stack *stack, int index, int *peeked)
{
	if (stack == NULL)
	{
		return -1;
	}

	if (index < 0 || index > stack->top)
	{
		return 0;
	}

	(*peeked) = stack->array[index];

	return 1;
}

// Returns an array of the values in the stack.
// Returns the array representaion of the values in the stack
// Returns NULL if stack is NULL or unsuccessul
int* stack_ToArray(Stack *stack)
{
	int *array = malloc(stack->top*sizeof(int));

	memcpy(array, stack->array, stack->top);

	return array;
}

/// ====
/// Helper Functions
/// ====