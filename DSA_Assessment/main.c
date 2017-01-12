#include <stdio.h>
#include <stdlib.h>
#include "PredictiveTextEngine/PredictiveTextEngine.h"

/// ====
/// Prototypes
/// ====
void waitForInput(char *message);

/// ====
/// Main
/// ====
// Entry point
int main(void)
{
    PredictiveTextEngine *ptEngine;
    ptEngine = predictiveTextEngine_Constructor();
    
	char* guess = predictiveTextEngine_predictWord("th");
	printf("=>\t guessing that 'th' is %s\n", guess);
    
    waitForInput("Press any key to exit.");
    predictiveTextEngine_Deconstructor(ptEngine);
    
    return 0;
}

// Block execution till theres an input.
void waitForInput(char *message)
{
    printf("\n%s\n=> ", message);
    getchar();
    printf("\n");
    
    return;
}