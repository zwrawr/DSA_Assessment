// =====================================================
// <summary>
//  This file is responsible for unit testing the file "Stack.c"
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================
#include <stdlib.h>
#include <stdio.h>
#include "..\Libarys\Stack.h"

/// ====
/// Defines
/// ====


/// ====
/// Prototypes
/// ====
int RunTest_0();
int RunTest_1();
int RunTest_2();
int RunTest_3();
int RunTest_4();
int RunTest_5();
int RunTest_6();
int RunTest_7();
int RunTest_8();
int RunTest_9();
int RunTest_10();
int RunTest_11();


/// ====
/// Public Functions
/// ====

// Returns 1 if all tests passed
int stack_UT_RunTests()
{

    printf("\n==== ==== ==== ==== ==== ==== ==== ==== ==== ==== \n");
    printf(  "====           UNIT TESTING STACKS           ==== \n");
    printf(  "==== ==== ==== ==== ==== ==== ==== ==== ==== ==== \n");
    
    
    int totalFailed = 0;
    
    // run all unit tests
    
    int testInfo_0 = RunTest_0();
    
    if (testInfo_0 != 1)
    {
        totalFailed++;
    }
    
    int testInfo_1 = RunTest_1();
    
    if (testInfo_1 != 1)
    {
        totalFailed++;
    }
    
    int testInfo_2 = RunTest_2();
    
    if (testInfo_2 != 1)
    {
        totalFailed++;
    }
    
    int testInfo_3 = RunTest_3();
    
    if (testInfo_3 != 1)
    {
        totalFailed++;
    }
    
    int testInfo_4 = RunTest_4();
    
    if (testInfo_4 != 1)
    {
        totalFailed++;
    }
    
    int testInfo_5 = RunTest_5();
    
    if (testInfo_5 != 1)
    {
        totalFailed++;
    }
    
    int testInfo_6 = RunTest_6();
    
    if (testInfo_6 != 1)
    {
        totalFailed++;
    }
    
    int testInfo_7 = RunTest_7();
    
    if (testInfo_7 != 1)
    {
        totalFailed++;
    }
    
    int testInfo_8 = RunTest_8();
    
    if (testInfo_8 != 1)
    {
        totalFailed++;
    }
    
    int testInfo_9 = RunTest_9();
    
    if (testInfo_9 != 1)
    {
        totalFailed++;
    }
    
    int testInfo_10 = RunTest_10();
    
    if (testInfo_10 != 1)
    {
        totalFailed++;
    }
    
    int testInfo_11 = RunTest_11();
    
    if (testInfo_11 != 1)
    {
        totalFailed++;
    }
    
    int passed = (totalFailed == 0) ? 1 : 0;
    
    printf("\n==== ==== ==== ==== ==== ==== ==== ==== ==== ==== \n");
    
    if (passed == 1)
    {
        printf(" [PASS] \tAll Unit Tests for stacks passed ! \n");
    }
    else
    {
        printf("*[FAIL]*\t%d Unit Tests for stacks failed ! \n", totalFailed);
    }
    
    return passed;
}



/// ====
/// Hidden Functions
/// ====

int RunTest_0()
{
    // test to see if that a constructed stack isnt null
    
    Stack *stack = stack_Constructor();
    
    int passed = (stack == NULL) ? 0 : 1;
    
    stack_Deconstructor(stack);
    
    if (passed == 1)
    {
        printf(" [PASS] \t Constructed stack pointer isn't null\n");
    }
    else
    {
        printf("*[FAIL]*\t Constructed stack pointer was null\n");
    }
    
    return passed;
}

int RunTest_1()
{
    // test to see if that two constructed stacks dont have the same pointer
    
    Stack *stack1 = stack_Constructor();
    Stack *stack2 = stack_Constructor();
    
    int passed = ((stack1 == NULL) || (stack2 == NULL) || (stack1 == stack2)) ? 0 : 1;
    
    stack_Deconstructor(stack1);
    stack_Deconstructor(stack2);
    
    
    if (passed == 1)
    {
        printf(" [PASS] \t Two constructed stacks dont have the same pointer\n");
    }
    else
    {
        printf("*[FAIL]*\t Two constructed stacks had the same pointer\n");
    }
    
    return passed;
}

int RunTest_2()
{
    // test to see if that pushing a value to a stack is possible
    
    Stack *stack = stack_Constructor();
    
    int info = stack_Push(stack, 1);
    
    int passed = ((stack == NULL) || (info == 0) || (info == -1)) ? 0 : 1;
    
    stack_Deconstructor(stack);
    
    
    if (passed == 1)
    {
        printf(" [PASS] \t Pushing a value to a stack is possible\n");
    }
    else
    {
        printf("*[FAIL]*\t Pushing a value to a stack resulting in error codes\n");
    }
    
    return passed;
}

int RunTest_3()
{
    // test to see if that pushing multiple values to a stack is possible
    
    Stack *stack = stack_Constructor();
    
    const int numTests = 16;
    int info = 0;
    
    for (int i = 0; i < numTests; i++)
    {
        // if the result from stack_Push is 1 we keep info the same , if not we set it to -1
        info = (stack_Push(stack, i) == 1 ) ? info : -1;
    }
    
    int passed = ((stack == NULL) || (info == -1)) ? 0 : 1;
    
    stack_Deconstructor(stack);
    
    
    if (passed == 1)
    {
        printf(" [PASS] \t Pushing multiple values to a stack is possible\n");
    }
    else
    {
        printf("*[FAIL]*\t Pushing multiple values to a stack resulting in error codes\n");
    }
    
    return passed;
}

int RunTest_4()
{
    // test to see if that poping a value off a stack is possible
    
    Stack *stack = stack_Constructor();
    
    int input = 9;
    int info1 = stack_Push(stack, input);
    
    int result = 0;
    int info2 = stack_Pop(stack, &result);
    
    
    int passed = ((stack == NULL) ||
                  (info1 == 0) || (info2 == -1) ||
                  (info2 == 0) || (info2 == -1) ||
                  (result != input)) ? 0 : 1;
                  
    stack_Deconstructor(stack);
    
    
    if (passed == 1)
    {
        printf(" [PASS] \t Popping a value off a stack is possible\n");
    }
    else
    {
        printf("*[FAIL]*\t Popping a value off a stack resulting in error codes\n");
    }
    
    return passed;
}

int RunTest_5()
{
    // test to see if that popping multiple values off a stack is possible
    
    Stack *stack = stack_Constructor();
    const int testLength = 16;
    int inputs[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 22, 333, 4444, -1, -10, -100 };
    
    int info1 = 0;
    
    for (int i = 0; i < testLength; i++)
    {
        // if the result from stack_Push is 1 we keep info the same , if not we set it to -1
        info1 = (stack_Push(stack, inputs[i]) == 1) ? info1 : -1;
    }
    
    int info2 = 0;
    
    for (int i = 0; i < testLength; i++)
    {
        // if the result from stack_Pop is 1 and the result matches the input,
        // we keep info the same , if not we set it to -1
        int result = 0;
        info2 = ((stack_Pop(stack, &result) == 1) && (result == inputs[testLength - i - 1])) ? info1 : -1;
    }
    
    int passed = ((stack == NULL) || (info1 != 0) || (info2 != 0)) ? 0 : 1;
    
    
    stack_Deconstructor(stack);
    
    
    if (passed == 1)
    {
        printf(" [PASS] \t Popping multiple values off a stack is possible\n");
    }
    else
    {
        printf("*[FAIL]*\t Popping multiple values off a stack resulting in error codes\n");
    }
    
    return passed;
}

int RunTest_6()
{
    // test to see if adding a value to one stack affect a diffrent stack
    
    Stack *stack1 = stack_Constructor();
    Stack *stack2 = stack_Constructor();
    
    const int testLength = 16;
    
    int info1 = 0;
    int info2 = 0;
    
    info1 = (stack_Push(stack1, -2) == 1) ? info1 : -1;
    info1 = (stack_Push(stack1, -17) == 1) ? info1 : -1;
    
    info2 = (stack_Push(stack2, 31) == 1) ? info2 : -1;
    info2 = (stack_Push(stack2, 41) == 1) ? info2 : -1;
    
    
    int result1 = 0;
    int result2 = 0;
    
    info1 = ((stack_Pop(stack1, &result1) == 1) && (result1 == -17)) ? info1 : -1;
    info2 = ((stack_Pop(stack2, &result2) == 1) && (result2 == 41)) ? info2 : -1;
    
    info2 = ((stack_Pop(stack2, &result2) == 1) && (result2 == 31)) ? info2 : -1;
    info1 = ((stack_Pop(stack1, &result1) == 1) && (result1 == -2)) ? info1 : -1;
    
    int passed = ((stack1 == NULL) || (stack2 == NULL) || (info1 != 0) || (info2 != 0)) ? 0 : 1;
    
    
    stack_Deconstructor(stack1);
    stack_Deconstructor(stack2);
    
    
    if (passed == 1)
    {
        printf(" [PASS] \t Adding values to one stack doesnt affect the other stack\n");
    }
    else
    {
        printf("*[FAIL]*\t Adding values to one stack does affect the other stack\n");
    }
    
    return passed;
}

int RunTest_7()
{
    // test to see if isEmpty works as expected
    
    Stack *stack = stack_Constructor();
    
    
    int info = 0, result = 0;
    
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
    
    int passed = ((stack == NULL) || (info != 0)) ? 0 : 1;
    
    
    stack_Deconstructor(stack);
    
    
    if (passed == 1)
    {
        printf(" [PASS] \t isEmpty works as expected\n");
    }
    else
    {
        printf("*[FAIL]*\t isEmpty dosent works as expecteds\n");
    }
    
    return passed;
}

int RunTest_8()
{
    // test to see if isFull works as expected
    
    Stack *stack = stack_Constructor();
    
    
    int info = 0, result = 0;
    
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
    
    int passed = ((stack == NULL) || (info != 0)) ? 0 : 1;
    
    
    stack_Deconstructor(stack);
    
    
    if (passed == 1)
    {
        printf(" [PASS] \t isFull works as expected\n");
    }
    else
    {
        printf("*[FAIL]*\t isFull dosent works as expecteds\n");
    }
    
    return passed;
}

int RunTest_9()
{
    // test to see if peeking in the stack is working
    
    Stack *stack = stack_Constructor();
    
    const int testLength = 16;
    int inputs[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 22, 333, 4444, -1, -10, -100 };
    
    int info = 0, result = 0;
    
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
        info = ((stack_Peek(stack, i, &result) == 1) && (result == inputs[testLength - i - 1])) ? info : -1;
    }
    
    for (int i = (testLength - 1); i >= 0; i--)
    {
        // if the result from stack_Peek is 1 and the result matches the input,
        // we keep info the same , if not we set it to -1
        info = ((stack_Peek(stack, i, &result) == 1) && (result == inputs[testLength - i - 1])) ? info : -1;
    }
    
    info = ((stack_Peek(stack, -2, &result) == 0)) ? info : -1;
    info = ((stack_Peek(stack, -1, &result) == 0)) ? info : -1;
    info = ((stack_Peek(stack, testLength, &result) == 0)) ? info : -1;
    info = ((stack_Peek(stack, testLength + 1, &result) == 0)) ? info : -1;
    
    
    
    int passed = ((stack == NULL) || (info == 0)) ? 0 : 1;
    
    stack_Deconstructor(stack);
    
    
    if (passed == 1)
    {
        printf(" [PASS] \t Peeking at a value in a stack works\n");
    }
    else
    {
        printf("*[FAIL]*\t Peeking at a value in a stack dosent works\n");
    }
    
    return passed;
}

int RunTest_10()
{
    // test to see if stack to array works
    
    Stack *stack = stack_Constructor();
    
    const int testLength = 16;
    int inputs[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 22, 333, 4444, -1, -10, -100 };
    
    int info = 0, result = 0;
    
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
    
    int passed = ((stack == NULL) || (info != 0)) ? 0 : 1;
    
    stack_Deconstructor(stack);
    
    if (passed == 1)
    {
        printf(" [PASS] \t Turning a stack into an array work\n");
    }
    else
    {
        printf("*[FAIL]*\t Turning a stack into an array dosent work\n");
    }
    
    return passed;
}

int RunTest_11()
{
    // test to see if stack Height works
    
    Stack *stack = stack_Constructor();
    
    const int testLength = 16;
    int inputs[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 22, 333, 4444, -1, -10, -100 };
    
    int info = 0, result = 0;
    
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
    
    int passed = ((stack == NULL) || (info != 0)) ? 0 : 1;
    
    stack_Deconstructor(stack);
    
    if (passed == 1)
    {
        printf(" [PASS] \t Stack Height works\n");
    }
    else
    {
        printf("*[FAIL]*\t Stack Height dosent work\n");
    }
    
    return passed;
}