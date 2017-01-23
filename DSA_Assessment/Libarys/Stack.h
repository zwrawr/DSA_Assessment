// =====================================================
// <summary>
//  This file provides a public interface for the file
//  "Stack.c".
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

/// ====
/// Defines
/// ====
#define INITIAL_STACK_LENGTH 10


/// ====
/// TypeDefs
/// ====
typedef struct Stack Stack;


/// ====
/// Constructors and Destructor
/// ====
Stack *stack_Constructor();
void stack_Deconstructor(Stack *stack);


/// ====
/// Functions
/// ====

// Checks to see weather the stack is empty
// Returns 1 if stack is empty
// Returns 0 if stack isn't empty
// Returns -1 if stack is NULL
int stack_isEmpty(Stack *stack);

// Checks to see weather the stack is full
// Returns 1 if stack is full
// Returns 0 if stack isn't full
// Returns -1 if stack is NULL
int stack_isFull(Stack *stack);

// Pushes an item onto the top of the stack
// Returns 1 if push was successful
// Returns 0 if push was unsuccessful
// Returns -1 if stack is NULL
int stack_Push(Stack *stack, int value);

// Pops an item off of the top of the stack
// Returns 1 if pop was successful
// Returns 0 if pop was unsuccessful
// Returns -1 if stack is NULL
int stack_Pop(Stack *stack, int *popped);

// Peek an item in the stack
// Returns 1 if peek was successful
// Returns 0 if peek was unsuccessful
// Returns -1 if stack is NULL
int stack_Peek(Stack *stack, int index, int *peeked);

// Pops an item off of the top of the stack but does not provide access to the value that was there.
// Returns 1 if pop was successful
// Returns 0 if pop was unsuccessful
// Returns -1 if stack is NULL
int stack_Pop_nv(Stack *stack);

// Creates an array of the values in the stack.
// Returns the array representation of the values in the stack
// Returns NULL if stack is NULL or unsuccessful
int *stack_ToArray(Stack *stack);

// Gets the height of the stack.
// Returns the Height of the stack
// Returns -1 if stack is NULL or unsuccessful
int stack_GetHeight(Stack *stack);

#endif // STACK_H_INCLUDED