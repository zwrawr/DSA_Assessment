// =====================================================
// <summary>
//  This file is responsible for unit testing the file "Stack.c"
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================
#include <stdlib.h>
#include <stdio.h>
#include "..\UnitTests\UnitTestRunner.h"
#include "..\Libarys\Stack.h"

/// ====
/// Defines
/// ====
#define DEFAULT 0

/// ====
/// Prototypes
/// ====


// These are all of our tests
// They all retrun 1 if they passed

int RunTest_ConstructedStackNotNull(UTRunner *utr);
int RunTest_TwoStackDontHaveSamePointer(UTRunner *utr);
int RunTest_StackPush(UTRunner *utr);
int RunTest_StackMultiplePushes(UTRunner *utr);
int RunTest_StackPop(UTRunner *utr);
int RunTest_StackMultiplePops(UTRunner *utr);
int RunTest_TwoStacksPushAndPop(UTRunner *utr);
int RunTest_StackIsEmpty(UTRunner *utr);
int RunTest_StackIsFull(UTRunner *utr);
int RunTest_StackPeeking(UTRunner *utr);
int RunTest_StackToArray(UTRunner *utr);
int RunTest_StackHeight(UTRunner *utr);


/// ====
/// Public Functions
/// ====

// Returns 1 if all tests passed
int stack_UT_RunTests(FILE *log)
{
    int(*TestFunctions[])(UTRunner * utr) =
    {
        RunTest_ConstructedStackNotNull,
        RunTest_TwoStackDontHaveSamePointer,
        RunTest_StackPush,
        RunTest_StackMultiplePushes,
        RunTest_StackPop,
        RunTest_StackMultiplePops,
        RunTest_TwoStacksPushAndPop,
        RunTest_StackIsEmpty,
        RunTest_StackIsFull,
        RunTest_StackPeeking,
        RunTest_StackToArray,
        RunTest_StackHeight
    };
    int numTestFunctions = sizeof(TestFunctions) / sizeof(TestFunctions[0]);
    
    UTRunner *utr = utr_Constructor(numTestFunctions, TestFunctions, "Stacks", log);
    int result = utr_RunTests(utr);
    utr_Deconstructor(utr);
    
    return result;
}



/// ====
/// Hidden Functions
/// ====

int RunTest_ConstructedStackNotNull(UTRunner *utr)
{
    // test to see if that a constructed stack isnt null
    Stack *stack = stack_Constructor();
    
    int passed = (stack == NULL) ? 0 : 1;
    
    stack_Deconstructor(stack);
    utr_PrintMessage(utr, passed, "Constructed stack pointer was not null", "Constructed stack pointer was null");
    return passed;
}

int RunTest_TwoStackDontHaveSamePointer(UTRunner *utr)
{
    // test to see if that two constructed stacks dont have the same pointer
    Stack *stack1 = stack_Constructor();
    Stack *stack2 = stack_Constructor();
    
    int passed = ((stack1 == NULL) || (stack2 == NULL) || (stack1 == stack2)) ? 0 : 1;
    
    stack_Deconstructor(stack1);
    stack_Deconstructor(stack2);
    utr_PrintMessage(utr, passed, "Two constructed stacks did not have the same pointer", "Two constructed stacks had the same pointer");
    return passed;
}

int RunTest_StackPush(UTRunner *utr)
{
    // test to see if that pushing a value to a stack is possible
    Stack *stack = stack_Constructor();
    
    int info = stack_Push(stack, 1);
    int passed = ((stack == NULL) || (info == 0) || (info == -1)) ? 0 : 1;
    
    stack_Deconstructor(stack);
    utr_PrintMessage(utr, passed, "Pushing a value to a stack worked", "Pushing a value to a stack did not work");
    return passed;
}

int RunTest_StackMultiplePushes(UTRunner *utr)
{
    // test to see if that pushing multiple values to a stack is possible
    Stack *stack = stack_Constructor();
    
    const int numTests = 16;
    int info = DEFAULT;
    
    for (int i = 0; i < numTests; i++)
    {
        // if the result from stack_Push is 1 we keep info the same , if not we set it to -1
        info = (stack_Push(stack, i) == 1 ) ? info : -1;
    }
    
    int passed = ((stack == NULL) || (info != DEFAULT)) ? 0 : 1;
    
    stack_Deconstructor(stack);
    utr_PrintMessage(utr, passed, "Pushing multiple values to a stack worked", "Pushing multiple values to a stack did not work");
    return passed;
}

int RunTest_StackPop(UTRunner *utr)
{
    // test to see if that poping a value off a stack is possible
    Stack *stack = stack_Constructor();
    
    int input = 9;
    int info = DEFAULT;
    info = (stack_Push(stack, input) == 1) ? info : -1;;
    
    int result = 0;
    info = (stack_Pop(stack, &result) == 1) ? info : -1;
    
    int passed = ((stack == NULL) ||
                  (info != DEFAULT) ||
                  (result != input)) ? 0 : 1;
                  
    stack_Deconstructor(stack);
    utr_PrintMessage(utr, passed, "Popping a value off a stack worked", "Popping a value off a stack did not work");
    return passed;
}

int RunTest_StackMultiplePops(UTRunner *utr)
{
    // test to see if that popping multiple values off a stack is possible
    Stack *stack = stack_Constructor();
    
    const int testLength = 16;
    int inputs[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 22, 333, 4444, -1, -10, -100 };
    
    int info = DEFAULT;
    
    for (int i = 0; i < testLength; i++)
    {
        // if the result from stack_Push is 1 we keep info the same , if not we set it to -1
        info = (stack_Push(stack, inputs[i]) == 1) ? info : -1;
    }
    
    for (int i = 0; i < testLength; i++)
    {
        // if the result from stack_Pop is 1 and the result matches the input,
        // we keep info the same , if not we set it to -1
        int result = 0;
        info = ((stack_Pop(stack, &result) == 1) && (result == inputs[testLength - i - 1])) ? info : -1;
    }
    
    int passed = ((stack == NULL) || (info != DEFAULT)) ? 0 : 1;
    
    stack_Deconstructor(stack);
    utr_PrintMessage(utr, passed, "Popping multiple values off a stack worked", "Popping multiple values off a stack did not work");
    return passed;
}

int RunTest_TwoStacksPushAndPop(UTRunner *utr)
{
    // test to see if adding a value to one stack affect a diffrent stack
    Stack *stack1 = stack_Constructor();
    Stack *stack2 = stack_Constructor();
    
    const int testLength = 16;
    int info = DEFAULT;
    
    // add some values to the stack
    info = (stack_Push(stack1, -2) == 1) ? info : -1;
    info = (stack_Push(stack1, -17) == 1) ? info : -1;
    info = (stack_Push(stack2, 31) == 1) ? info : -1;
    info = (stack_Push(stack2, 41) == 1) ? info : -1;
    
    int result1 = 0;
    int result2 = 0;
    
    // make sure the values were poping off match the values we added
    info = ((stack_Pop(stack1, &result1) == 1) && (result1 == -17)) ? info : -1;
    info = ((stack_Pop(stack2, &result2) == 1) && (result2 == 41)) ? info : -1;
    info = ((stack_Pop(stack2, &result2) == 1) && (result2 == 31)) ? info : -1;
    info = ((stack_Pop(stack1, &result1) == 1) && (result1 == -2)) ? info : -1;
    
    int passed = ((stack1 == NULL) || (stack2 == NULL) || (info != DEFAULT)) ? 0 : 1;
    
    stack_Deconstructor(stack1);
    stack_Deconstructor(stack2);
    utr_PrintMessage(utr, passed, "Adding values to one stack doesnt affect the other stack", "Adding values to one stack does affect the other stack");
    return passed;
}

int RunTest_StackIsEmpty(UTRunner *utr)
{
    // test to see if isEmpty works as expected
    Stack *stack = stack_Constructor();
    int info = DEFAULT, result = 0;
    
    // check to see if a stack isEmpty before we've added anything to it
    info = (stack_isEmpty(stack) == 1) ? info : -1;
    
    // add a value to the stack and make sure its not still empty
    info = (stack_Push(stack, 4) == 1) ? info : -1;
    info = (stack_isEmpty(stack) == 0) ? info : -1;
    
    // add another value to the stack and make sure its not still empty
    info = (stack_Push(stack, 5) == 1) ? info : -1;
    info = (stack_isEmpty(stack) == 0) ? info : -1;
    
    // remove one value and make sure that the stack is still not empty ( had 2 items removed one so still has one)
    info = ((stack_Pop(stack, &result) == 1) && (result == 5)) ? info : -1;
    info = (stack_isEmpty(stack) == 0) ? info : -1;
    
    // remove the last item and make sure that the stack is now empty
    info = ((stack_Pop(stack, &result) == 1) && (result == 4)) ? info : -1;
    info = (stack_isEmpty(stack) == 1) ? info : -1;
    
    int passed = ((stack == NULL) || (info != DEFAULT)) ? 0 : 1;
    
    stack_Deconstructor(stack);
    utr_PrintMessage(utr, passed, "Checking if a stack isEmpty worked", "Checking if a stack isEmpty did not work");
    return passed;
}

int RunTest_StackIsFull(UTRunner *utr)
{
    // test to see if isFull works as expected
    Stack *stack = stack_Constructor();
    int info = DEFAULT, result = 0;
    
    // check to see if a stack isFull before we've added anything to it (hint: it shouldn't be  . . . )
    info = (stack_isFull(stack) == 0) ? info : -1;
    
    for (int i = 0; i < (INITIAL_STACK_LENGTH - 1); i++)
    {
        // add a value to the stack and make sure its still not full
        info = (stack_Push(stack, 4) == 1) ? info : -1;
        info = (stack_isFull(stack) == 0) ? info : -1;
    }
    
    // add a value to the stack and make sure its now full
    info = (stack_Push(stack, 4) == 1) ? info : -1;
    info = (stack_isFull(stack) == 1) ? info : -1;
    
    // remove one value and make sure that the stack is not full
    info = ((stack_Pop(stack, &result) == 1) && (result == 4)) ? info : -1;
    info = (stack_isFull(stack) == 0) ? info : -1;
    
    // add another value to the stack and make sure it now full again
    info = (stack_Push(stack, 4) == 1) ? info : -1;
    info = (stack_isFull(stack) == 1) ? info : -1;
    
    // add another value to the stack and make sure it no longer full (made to auto resize when it full and you push)
    info = (stack_Push(stack, 4) == 1) ? info : -1;
    info = (stack_isFull(stack) == 0) ? info : -1;
    
    int passed = ((stack == NULL) || (info != DEFAULT)) ? 0 : 1;
    
    stack_Deconstructor(stack);
    utr_PrintMessage(utr, passed, "Checking if a stack isFull worked", "Checking if a stack isFull did not work");
    return passed;
}

int RunTest_StackPeeking(UTRunner *utr)
{
    // test to see if peeking in the stack is working
    Stack *stack = stack_Constructor();
    
    const int testLength = 16;
    int inputs[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 22, 333, 4444, -1, -10, -100 };
    
    int info = DEFAULT, result = 0;
    
    // try to peek at an empty array
    info = ((stack_Peek(stack, 0, &result) == 0)) ? info : -1;
    info = ((stack_Peek(stack, -1, &result) == 0)) ? info : -1;
    
    for (int i = 0; i < testLength; i++)
    {
        // if the result from stack_Push is 1 we keep info the same , if not we set it to -1
        info = (stack_Push(stack, inputs[i]) == 1) ? info : -1;
    };
    
    for (int i = 0; i < testLength; i++)
    {
        // if the result from stack_Peek is 1 and the result matches the input,
        // we keep info the same , if not we set it to -1
        info = ((stack_Peek(stack, i, &result) == 1) && (result == inputs[i])) ? info : -1;
    }
    
    for (int i = (testLength - 1); i >= 0; i--)
    {
        // if the result from stack_Peek is 1 and the result matches the input,
        // we keep info the same , if not we set it to -1
        info = ((stack_Peek(stack, i, &result) == 1) && (result == inputs[i])) ? info : -1;
    }
    
    // try peeking at some invalid indexes
    info = ((stack_Peek(stack, -2, &result) == 0)) ? info : -1;
    info = ((stack_Peek(stack, -1, &result) == 0)) ? info : -1;
    info = ((stack_Peek(stack, testLength, &result) == 0)) ? info : -1;
    info = ((stack_Peek(stack, testLength + 1, &result) == 0)) ? info : -1;
    
    int passed = ((stack == NULL) || (info != DEFAULT)) ? 0 : 1;
    
    stack_Deconstructor(stack);
    utr_PrintMessage(utr, passed, "Peeking at a value in a stack worked", "Peeking at a value in a stack did not work");
    return passed;
}

int RunTest_StackToArray(UTRunner *utr)
{
    // test to see if stack to array works
    Stack *stack = stack_Constructor();
    
    const int testLength = 16;
    int inputs[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 22, 333, 4444, -1, -10, -100 };
    
    int info = DEFAULT, result = 0;
    
    // try to get an array from an empty stack
    int *array = stack_ToArray(stack);
    info = (( array == NULL)) ? info : -1;
    
    // add a bunch of values to a stack
    for (int i = 0; i < testLength - 4; i++)
    {
        // if the result from stack_Push is 1 we keep info the same , if not we set it to -1
        info = (stack_Push(stack, inputs[i]) == 1) ? info : -1;
    };
    
    array = stack_ToArray(stack);
    
    info = ((array != NULL)) ? info : -1;
    
    // make sure the array matches the inputs
    for (int i = 0; i < testLength - 4; i++)
    {
        // if the result matches the input we keep info the same , if not we set it to -1
        info = (inputs[i] == array[i]) ? info : -1;
    };
    
    free(array);
    
    // add some more values to a stack that weve already turned into an array
    for (int i = (testLength - 4); i < testLength; i++)
    {
        info = (stack_Push(stack, inputs[i]) == 1) ? info : -1;
    };
    
    array = stack_ToArray(stack);
    
    info = ((array != NULL)) ? info : -1;
    
    // make sure the array matches the inputs
    for (int i = 0; i < testLength; i++)
    {
        info = (inputs[i] == array[i]) ? info : -1;
    };
    
    free(array);
    
    int passed = ((stack == NULL) || (info != DEFAULT)) ? 0 : 1;
    
    stack_Deconstructor(stack);
    
    utr_PrintMessage(utr, passed, "Turning a stack into an array worked", "Turning a stack into an array did not work");
    
    return passed;
}

int RunTest_StackHeight(UTRunner *utr)
{
    // test to see if stack Height works
    Stack *stack = stack_Constructor();
    
    const int testLength = 16;
    int inputs[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 22, 333, 4444, -1, -10, -100 };
    
    int info = DEFAULT, result = 0;
    
    // try to get the height of an empty stack
    info = ((stack_GetHeight(stack) == 0)) ? info : -1;
    
    // add a bunch of values to a stack and make sure the stack height is incressing
    for (int i = 0; i < testLength; i++)
    {
        info = (stack_Push(stack, inputs[i]) == 1) ? info : -1;
        info = (stack_GetHeight(stack) == i + 1) ? info : -1;
    };
    
    // pop a value from the stack and make sure the height is decressing
    info = (stack_Pop(stack, &result) == 1) ? info : -1;
    
    info = (stack_GetHeight(stack) == testLength - 1) ? info : -1;
    
    info = (stack_Pop(stack, &result) == 1) ? info : -1;
    
    info = (stack_GetHeight(stack) == testLength - 2) ? info : -1;
    
    // make sure the height goes back up as we push morew stuff on to the stack
    info = (stack_Push(stack, 1) == 1) ? info : -1;
    
    info = (stack_GetHeight(stack) == testLength - 1) ? info : -1;
    
    info = (stack_Push(stack, 1) == 1) ? info : -1;
    
    info = (stack_Push(stack, 1) == 1) ? info : -1;
    
    info = (stack_GetHeight(stack) == testLength + 1) ? info : -1;
    
    int passed = ((stack == NULL) || (info != DEFAULT)) ? 0 : 1;
    
    stack_Deconstructor(stack);
    
    utr_PrintMessage(utr, passed, "Checking a stacks Height worked", "Checking a stacks Height did not work");
    
    return passed;
}