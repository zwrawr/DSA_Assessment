// =====================================================
// <summary>
//  This file is responsible for running all unit tests
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "..\UnitTests\UnittestRunner.h"


// all of the unittesting files
#include "..\UnitTests\Stack_UT.h"
#include "..\UnitTests\Trie_UT.h"
#include "..\UnitTests\PredictiveTextEngine_UT.h"
#include "..\UnitTests\List_UT.h"
#include "..\UnitTests\Complexity_UT.h"


/// ====
/// Defines
/// ====
#define LOGFILE "UnitTestLog.txt"
/// ====
/// Prototypes
/// ====


/// ====
/// Public Functions
/// ====

// Returns 1 if all tests passed
int UnitTester_RunTestSets(void)
{
    FILE *log;
    fopen_s(&log, LOGFILE, "w");
    
    // get the time
    time_t now;
    time(&now);
    char *buf = malloc(64 * sizeof(char));
    ctime_s(buf, 64, &now);
    
    fprintf(log, "\n   %s \n", buf );
    
    printf("\n====#====#====#====#====#====#====#====#====#==== \n");
    printf("====                                         ==== \n");
    printf("====                UNIT TESTING             ==== \n");
    printf("====                                         ==== \n");
    printf("====#====#====#====#====#====#====#====#====#==== \n\n\n");
    
    fprintf(log, "====#====#====#====#====#====#====#====#====#==== \n");
    fprintf(log, "====                                         ==== \n");
    fprintf(log, "====                UNIT TESTING             ==== \n");
    fprintf(log, "====                                         ==== \n");
    fprintf(log, "====#====#====#====#====#====#====#====#====#==== \n\n");
    
    int failed = 0, info = 0;
    
    int(*TestFunctions[])(FILE * log) =
    {
        stack_UT_RunTests,
        trie_UT_RunTests,
        PredictiveTextEngine_UT_RunTests,
        list_UT_RunTests,
        complexity_UT_RunTests
    };
    
    int numTestFunctions = sizeof(TestFunctions) / sizeof(TestFunctions[0]);
    
    // Run ALl sets of tests below
    // if the test has passed we keep failed the same, if not we add one to failed
    for (int i = 0; i < numTestFunctions; i++)
    {
        info = TestFunctions[i](log);
        failed += ((info == 1) ? 0 : 1);
    }
    
    
    printf("\n\n\n====#====#====#====#====#====#====#====#====#==== \n");
    fprintf(log, "\n\n\n====#====#====#====#====#====#====#====#====#==== \n");
    
    if (failed == 0)
    {
        printf(" [PASS] \t All Unit Tests passed ! \n");
        fprintf(log, " [PASS] \t All Unit Tests passed ! \n");
    }
    else
    {
        printf("*[FAIL]*\t %d Sets of Unit Tests failed ! \n", failed);
        fprintf(log, "*[FAIL]*\t %d Sets of Unit Tests failed ! \n", failed);
    }
    
    printf("\n\n\n\n\n");
    fclose(log);
    getchar();
    
    if (failed == 0)
    {
        return 1;
    }
    
    return 0;
}