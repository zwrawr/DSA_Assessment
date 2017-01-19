// =====================================================
// <summary>
//  This file creates and manages a stack data structure for the storage
//  of integers.
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================

// =====================================================
// This file was created when following the University of York,
// Dept. of Electronics Data Structures and Algorithms Lab Scripts.
// http://www.elec.york.ac.uk/internal_web/meng/yr2/modules/DSA/DSA/Labs/Scripts/Lab7-StacksAndQueues.pdf
// Some of the code below may be from the source above.
// =====================================================

//TODO:: maybe look at this http://www.robertgamble.net/2012/01/c11-generic-selections.html and make it generic ish.

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"


/// ====
/// Defines
/// ====


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
    
    return (stack->top == (stack->length)) ? 1 : 0;
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
            return 0;
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
    
    if (stack_isEmpty(stack) != 1)
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
int *stack_ToArray(Stack *stack)
{

    if (stack == NULL || stack_isEmpty(stack) == 1)
    {
        return NULL;
    }

    int height = stack_GetHeight(stack);
    int *array = malloc(height * sizeof(int));
    
    memcpy(array, stack->array, height * sizeof(int));
    
    return array;
}

// Gets the height of the stack.
// Returns the Height of the stack
// Returns -1 if stack is NULL or unsuccessul
int stack_GetHeight(Stack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }
    
    return stack->top;
}

/// ====
/// Helper Functions
/// ====