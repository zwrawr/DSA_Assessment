// =====================================================
// <summary>
//  This file is responsible for unit testing the file "List.c",
//  The list implementation is generic but it is only used for
//  char* in the code base so that what I am testing it with.
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "..\UnitTests\UnitTestRunner.h"

// Under test
#include "..\Libarys\List.h"

/// ====
/// Defines
/// ====
#define DEFAULT 0

#define STRING_LENGTH 32


/// ====
/// Prototypes
/// ====


// These are all of our tests
// They all return 1 if they passed

int RunTest_ConstructedListNotNull(UTRunner *utr);
int RunTest_TwoListsDontHaveSamePointer(UTRunner *utr);
int RunTest_ListAdd(UTRunner *utr);
int RunTest_ListMultipleAdd(UTRunner *utr);
int RunTest_ListRead(UTRunner *utr);
int RunTest_ListIsEmpty(UTRunner *utr);
int RunTest_ListSize(UTRunner *utr);


/// ====
/// Public Functions
/// ====

// Returns 1 if all tests passed
int list_UT_RunTests(FILE *log)
{
    int(*TestFunctions[])(UTRunner * utr) =
    {
        RunTest_ConstructedListNotNull,
        RunTest_TwoListsDontHaveSamePointer,
        RunTest_ListAdd,
        RunTest_ListMultipleAdd,
        RunTest_ListRead,
        RunTest_ListIsEmpty,
        RunTest_ListSize
    };
    int numTestFunctions = sizeof(TestFunctions) / sizeof(TestFunctions[0]);
    
    UTRunner *utr = utr_Constructor(numTestFunctions, TestFunctions, "Lists", log);
    int result = utr_RunTests(utr);
    utr_Deconstructor(utr);
    
    return result;
}



/// ====
/// Hidden Functions
/// ====

int RunTest_ConstructedListNotNull(UTRunner *utr)
{
    // test to see if that a constructed list isn't null
    List *list = list_Constructor(STRING_LENGTH);
    
    int passed = (list == NULL) ? 0 : 1;
    
    list_Deconstructor(list);
    utr_PrintMessage(utr, passed, "Constructed list pointer was not null", "Constructed list pointer was null");
    return passed;
}

int RunTest_TwoListsDontHaveSamePointer(UTRunner *utr)
{
    // test to see if that two constructed lists don't have the same pointer
    List *list1 = list_Constructor(STRING_LENGTH);
    List *list2 = list_Constructor(STRING_LENGTH);
    
    int passed = ((list1 == NULL) || (list2 == NULL) || (list1 == list2)) ? 0 : 1;
    
    list_Deconstructor(list1);
    list_Deconstructor(list2);
    utr_PrintMessage(utr, passed, "Two constructed lists did not have the same pointer", "Two constructed lists had the same pointer");
    return passed;
}

int RunTest_ListAdd(UTRunner *utr)
{
    // test to see if that add a value to a list is possible
    List *list = list_Constructor(STRING_LENGTH);
    
    int info = list_Add(list, "This is a string");
    int passed = ((list == NULL) || (info == 0) || (info == -1)) ? 0 : 1;
    
    list_Deconstructor(list);
    utr_PrintMessage(utr, passed, "Adding a value to a list worked", "Adding a value to a list did not work");
    return passed;
}

int RunTest_ListMultipleAdd(UTRunner *utr)
{
    // test to see if that adding multiple values to a list is possible
    List *list = list_Constructor(STRING_LENGTH);
    
    char *strings[] =
    {
        "Hello World!",
        "Unit Testing is really boring",
        "Avocado",
        "Dyslexia is fun",
        "Rainbows",
        "Random Word",
        "Need Sleep"
    };
    const int numTests = sizeof(strings) / sizeof(strings[0]);
    
    int info = DEFAULT;
    
    for (int i = 0; i < numTests; i++)
    {
        info = (list_Add(list, strings[i]) == 1) ? info : -1;
    }
    
    int passed = ((list == NULL) || (info != DEFAULT)) ? 0 : 1;
    
    list_Deconstructor(list);
    utr_PrintMessage(utr, passed, "Adding multiple values to a list worked", "Adding multiple values to a list did not work");
    return passed;
}

int RunTest_ListRead(UTRunner *utr)
{
    // test to see if that reading multiple values from a list is possible
    List *list = list_Constructor(STRING_LENGTH);
    
    char *strings[] =
    {
        "Hello World!",
        "Unit Testing is really boring",
        "Avocado",
        "Dyslexia is fun",
        "Rainbows",
        "Random Word",
        "Need Sleep"
    };
    const int numTests = sizeof(strings) / sizeof(strings[0]);
    
    int info = DEFAULT;
    
    // add the values
    for (int i = 0; i < numTests; i++)
    {
        info = (list_Add(list, strings[i]) == 1) ? info : -1;
    }
    
    char *tmp = malloc(STRING_LENGTH * sizeof(char));
    
    // read the values
    for (int i = 0; i < numTests; i++)
    {
        info = (list_Read(list, i, tmp) == 1) ? info : -1;
        info = (strcmp(tmp, strings[i]) == 0) ? info : -1;
    }
    
    // try to read an out of bounds index
    info = (list_Read(list, -1, tmp) == 0) ? info : -1;
    info = (list_Read(list, numTests + 2, tmp) == 0) ? info : -1;
    info = (list_Read(list, numTests + 1, tmp) == 0) ? info : -1;
    info = (list_Read(list, numTests, tmp) == 0) ? info : -1;
    
    // make sure it has validity checks
    info = (list_Read(list, -1, NULL) == 0) ? info : -1;
    info = (list_Read(NULL, numTests - 2, tmp) == -1) ? info : -1;
    
    
    int passed = ((list == NULL) || (info != DEFAULT)) ? 0 : 1;
    
    free(tmp);
    list_Deconstructor(list);
    utr_PrintMessage(utr, passed, "Adding multiple values to a list worked", "Adding multiple values to a list did not work");
    return passed;
}

int RunTest_ListIsEmpty(UTRunner *utr)
{
    // test to see if isEmpty works as expected
    List *list = list_Constructor(STRING_LENGTH);
    int info = DEFAULT;
    
    // check to see if a list isEmpty before we've added anything to it
    info = (list_isEmpty(list) == 1) ? info : -1;
    
    // add a value to the list and make sure its not still empty
    info = (list_Add(list, "hey") == 1) ? info : -1;
    info = (list_isEmpty(list) == 0) ? info : -1;
    
    // add another value to the list and make sure its not still empty
    info = (list_Add(list, "test") == 1) ? info : -1;
    info = (list_isEmpty(list) == 0) ? info : -1;
    
    // add another value to the list and make sure its not still empty
    info = (list_Add(list, "hello") == 1) ? info : -1;
    info = (list_isEmpty(list) == 0) ? info : -1;
    
    // remove one value and make sure that the list is still not empty
    info = (list_Remove(list, 2) == 1) ? info : -1;
    info = (list_isEmpty(list) == 0) ? info : -1;
    
    info = (list_Remove(list, 0) == 1) ? info : -1;
    info = (list_isEmpty(list) == 0) ? info : -1;
    
    // remove the last item and make sure that the list is now empty
    info = (list_Remove(list, 0) == 1) ? info : -1;
    info = (list_isEmpty(list) == 1) ? info : -1;
    
    int passed = ((list == NULL) || (info != DEFAULT)) ? 0 : 1;
    
    list_Deconstructor(list);
    utr_PrintMessage(utr, passed, "list isEmpty worked", "list isEmpty did not work");
    return passed;
}


int RunTest_ListSize(UTRunner *utr)
{
    // test to see if isEmpty works as expected
    List *list = list_Constructor(STRING_LENGTH);
    int info = DEFAULT;
    
    // check to see if a list isEmpty before we've added anything to it
    info = (list_Size(list) == 0) ? info : -1;
    
    // add a value to the list and make sure it has the correct size
    info = (list_Add(list, "hey") == 1) ? info : -1;
    info = (list_Size(list) == 1) ? info : -1;
    
    // add another value to the list and make sure its has the correct size
    info = (list_Add(list, "test") == 1) ? info : -1;
    info = (list_Size(list) == 2) ? info : -1;
    
    // add another value to the list and make sure the list has the correct size
    info = (list_Add(list, "hello") == 1) ? info : -1;
    info = (list_Size(list) == 3) ? info : -1;
    
    // remove one value and make list that the stack has the correct size
    info = (list_Remove(list, 2) == 1) ? info : -1;
    info = (list_Size(list) == 2) ? info : -1;
    
    info = (list_Remove(list, 0) == 1) ? info : -1;
    info = (list_Size(list) == 1) ? info : -1;
    
    // remove the last item and list sure that the stack has the correct size
    info = (list_Remove(list, 0) == 1) ? info : -1;
    info = (list_Size(list) == 0) ? info : -1;
    
    // make sure it has validity checks
    info = (list_Size(NULL) == -1) ? info : -1;
    
    int passed = ((list == NULL) || (info != DEFAULT)) ? 0 : 1;
    
    list_Deconstructor(list);
    utr_PrintMessage(utr, passed, "list Size worked", "list Size did not work");
    return passed;
}
