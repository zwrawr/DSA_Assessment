// =====================================================
// <summary>
//  This file is responsible for unit testing the file "Stack.c"
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================
#include <stdlib.h>
#include <stdio.h>

/// ====
/// Defines
/// ====

/// ====
/// TypeDefs
/// ====
typedef struct UTRunner UTRunner;


/// ====
/// Structures
/// ====

struct UTRunner
{
    int(**TestFunctions)(void);
    int numTestFunctions;
    char *TestSetName;
};

/// ====
/// Prototypes
/// ====
void utr_PrintMessage(int passed, char *success, char *failure);


/// ====
/// Constructors and DeConstrutors
/// ====
UTRunner *utr_Constructor(int num, int (**funcs)(void), char *name )
{
    UTRunner *utr;
    utr = malloc(sizeof(UTRunner));
    utr->numTestFunctions = num;
    utr->TestFunctions = funcs;
    utr->TestSetName = name;
}

void utr_Deconstructor(UTRunner *utr)
{
    free(utr);
}


/// ====
/// Public Functions
/// ====

// Returns 1 if all tests passed
int utr_RunTests(UTRunner *utr)
{
    printf("\n\n==== ==== ==== ==== ==== ==== ==== ==== ==== ==== \n");
    printf("====           UNIT TESTING %s \n", utr->TestSetName);
    printf("==== ==== ==== ==== ==== ==== ==== ==== ==== ==== \n");
    int totalFailed = 0;
    
    // run all unit tests
    for (int i = 0; i < utr->numTestFunctions; i++)
    {
        // run the unit test and get the result, info will be 1 if test passed
        int info = utr->TestFunctions[i]();
        // if the test didn't pass incriment the the fails counter
        totalFailed += (info == 1) ? 0 : 1;
    }
    
    printf("==== ==== ==== ==== ==== ==== ==== ==== ==== ==== \n");
    
    if (totalFailed == 0)
    {
        printf(" [PASS] \tAll Unit Tests for %s passed ! \n\n", utr->TestSetName);
    }
    else
    {
        printf("*[FAIL]*\t%d Unit Tests for %s failed ! \n\n", totalFailed, utr->TestSetName);
    }
    
    return (totalFailed == 0) ? 1 : 0;
}

void utr_PrintMessage(int passed, char *success, char *failure)
{
    if (passed == 1)
    {
        printf(" [PASS] \t %s\n", success);
    }
    else
    {
        printf("*[FAIL]*\t %s\n", failure);
    }
}

/// ====
/// Hidden Functions
/// ====


