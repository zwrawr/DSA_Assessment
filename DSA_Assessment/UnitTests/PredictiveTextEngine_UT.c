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
// They all return 1 if they passed

int RunTest_ConstructedPTENotNull(UTRunner *utr);
int RunTest_CanPredictWords(UTRunner *utr);


/// ====
/// Public Functions
/// ====

// Returns 1 if all tests passed
int PredictiveTextEngine_UT_RunTests(FILE *log)
{
    int(*TestFunctions[])(UTRunner * utr) =
    {
        RunTest_ConstructedPTENotNull,
        RunTest_CanPredictWords
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

int RunTest_ConstructedPTENotNull(UTRunner *utr)
{
    // test to see if that a constructed pte isn't null
    PredictiveTextEngine *pte = predictiveTextEngine_Constructor();
    
    int passed = (pte == NULL) ? 0 : 1;
    
    predictiveTextEngine_Deconstructor(pte);
    utr_PrintMessage(utr, passed, "Constructed pte pointer was not null", "Constructed pte pointer was null");
    return passed;
}

int RunTest_CanPredictWords(UTRunner *utr)
{
    // test to see if that we can predict words
    
    PredictiveTextEngine *pte = predictiveTextEngine_Constructor();
    
    int info = 0;
    
    int numResults = 8;
    char **results = malloc(numResults * sizeof(char *));
    
    for (int i = 0; i < numResults; i++)
    {
        results[i] = malloc(predictiveTextEngine_MaxWordLength() * sizeof(char));
        results[i][0] = '\0';
    }
    
    //lets try to do some predictions for words that are in the list
    info = (predictiveTextEngine_predictWords(pte, "hello", results, 2) == 1) ? info : -1;
    info = (strcmp("hello", results[0]) == 0) ? info : -1;
    
    info = (predictiveTextEngine_predictWords(pte, "hel", results, 4) == 4) ? info : -1;
    info = (strcmp("held", results[0]) == 0) ? info : -1;
    info = (strcmp("helen", results[1]) == 0) ? info : -1;
    info = (strcmp("helena", results[2]) == 0) ? info : -1;
    info = (strcmp("helene", results[3]) == 0) ? info : -1;
    
    // NOTE :: The words are weird, where did you even get this list
    info = (predictiveTextEngine_predictWords(pte, "ze", results, 8) == 8) ? info : -1;
    info = (strcmp("zeal", results[0]) == 0) ? info : -1;
    info = (strcmp("zealand", results[1]) == 0) ? info : -1;
    info = (strcmp("zealot", results[2]) == 0) ? info : -1;
    info = (strcmp("zealous", results[3]) == 0) ? info : -1;
    info = (strcmp("zebra", results[4]) == 0) ? info : -1;
    info = (strcmp("zeiss", results[5]) == 0) ? info : -1;
    info = (strcmp("zellerbach", results[6]) == 0) ? info : -1;
    info = (strcmp("zen", results[7]) == 0) ? info : -1;
    
    // Do a prediction for words that are not in the list
    info = (predictiveTextEngine_predictWords(pte, "supercalifra", results, 3) == 0) ? info : -1;
    info = (predictiveTextEngine_predictWords(pte, "zzzzzzzzzzzzzzz", results, 8) == 0) ? info : -1;
    
    // Make sure input validation is working
    info = (predictiveTextEngine_predictWords(pte, "supercalifra", results, 0) == -1) ? info : -1;
    info = (predictiveTextEngine_predictWords(pte, "zzzzzzzzzzzzzzz", NULL, 8) == -1) ? info : -1;
    info = (predictiveTextEngine_predictWords(pte, "z", results, 8) == -1) ? info : -1;
    info = (predictiveTextEngine_predictWords(pte, "", results, 8) == -1) ? info : -1;
    info = (predictiveTextEngine_predictWords(pte, NULL, results, 8) == -1) ? info : -1;
    info = (predictiveTextEngine_predictWords(NULL, NULL, results, 8) == -1) ? info : -1;
    
    int passed = (info != 0) ? 0 : 1;
    
    predictiveTextEngine_Deconstructor(pte);
    utr_PrintMessage(utr, passed, "Predicting words worked", "Predicting words did not work");
    return passed;
}