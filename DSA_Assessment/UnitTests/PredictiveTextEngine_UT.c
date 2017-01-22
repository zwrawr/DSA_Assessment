// =====================================================
// <summary>
//  This file is responsible for unit testing the file "PredictiveTextEngine.c"
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "..\UnitTests\UnitTestRunner.h"

// Under test
#include "..\PredictiveTextEngine\PredictiveTextEngine.h"

/// ====
/// Defines
/// ====


/// ====
/// Prototypes
/// ====

// These are all of our tests
// They all retrun 1 if they passed

int RunTest_0(UTRunner *utr);
int RunTest_1(UTRunner *utr);
int RunTest_2(UTRunner *utr);
int RunTest_3(UTRunner *utr);
int RunTest_4(UTRunner *utr);
int RunTest_5(UTRunner *utr);
int RunTest_6(UTRunner *utr);


/// ====
/// Public Functions
/// ====

// Returns 1 if all tests passed
int PredictiveTextEngine_UT_RunTests(FILE *log)
{
    int(*TestFunctions[])(UTRunner * utr) =
    {
        RunTest_0,
        RunTest_1
    };
    
    int numTestFunctions = sizeof(TestFunctions) / sizeof(TestFunctions[0]);
    
    UTRunner *utr = utr_Constructor(numTestFunctions, TestFunctions, "PTE", log);
    int result = utr_RunTests(utr);
    utr_Deconstructor(utr);
    
    return result;
}



/// ====
/// Hidden Functions
/// ====

int RunTest_0(UTRunner *utr)
{
    // test to see if that a constructed pte isnt null
    PredictiveTextEngine *pte = predictiveTextEngine_Constructor();
    
    int passed = (pte == NULL) ? 0 : 1;
    
    predictiveTextEngine_Deconstructor(pte);
    utr_PrintMessage(utr, passed, "Constructed pte pointer was not null", "Constructed pte pointer was null");
    return passed;
}

int RunTest_1(UTRunner *utr)
{
    // test to see if that we can predict words
    
    PredictiveTextEngine *pte = predictiveTextEngine_Constructor();
    
    int info = 0;
    
    int numResults = 4;
    char **results = malloc(numResults * sizeof(char *));
    
    for (int i = 0; i < numResults; i++)
    {
        results[i] = malloc(predictiveTextEngine_MaxWordLength() * sizeof(char));
        results[i][0] = '\0';
    }
    
    //lets try to do some preictions
    info = (predictiveTextEngine_predictWords(pte, "hello", results, 1) == 1) ? info : -1;
    
    
    
    int passed = (info != 0) ? 0 : 1;
    
    predictiveTextEngine_Deconstructor(pte);
    utr_PrintMessage(utr, passed, "Predicting words worked", "Predicting words did not work");
    return passed;
}