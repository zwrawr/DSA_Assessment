// =====================================================
// <summary>
//  This file is responsible for running all unit tests
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================
#include <stdlib.h>
#include <stdio.h>

#include "..\UnitTests\Stack_UT.h"

/// ====
/// Defines
/// ====


/// ====
/// Prototypes
/// ====


/// ====
/// Public Functions
/// ====

// Returns 1 if all tests passed
int UnitTester_RunTests(void)
{
    printf("\n====#====#====#====#====#====#====#====#====#==== \n");
    printf("====                                         ==== \n");
    printf("====                UNIT TESTING             ==== \n");
    printf("====                                         ==== \n");
    printf("====#====#====#====#====#====#====#====#====#==== \n\n");
    
    int failed = 0, info = 0;
    
    // if the test has passed we keep failed the same, if not we add one to failed
    
    info = stack_UT_RunTests();
    failed += (( info == 1) ? 0 : 1);
    
    
    
    printf("\n\n====#====#====#====#====#====#====#====#====#==== \n");
    
    if (failed == 0)
    {
        printf(" [PASS] \t All Unit Tests passed ! \n");
    }
    else
    {
        printf("*[FAIL]*\t %d Sets of Unit Tests failed ! \n", failed);
    }
    
    getchar();
    
    
    if (failed == 0)
    {
        return 1;
    }
    
    return 0;
}