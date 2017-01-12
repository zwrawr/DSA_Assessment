#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WordTree/WordTree.h"

/// ====
/// Defines
/// ====


/// ====
/// Type Definitions
/// ====
typedef struct PredictiveTextEngine PredictiveTextEngine;


/// ====
/// Prototypes
/// ====


/// ====
/// Structures
/// ====
struct PredictiveTextEngine
{
    WordTree *wTree;
};


/// ====
/// Constructors and Destructor
/// ====
PredictiveTextEngine *predictiveTextEngine_Constructor(void)
{
    PredictiveTextEngine *ptEngine;
    ptEngine = malloc(sizeof(PredictiveTextEngine));
    
    ptEngine->wTree = wordTree_Constructor();
    
    return ptEngine;
}

void predictiveTextEngine_Deconstructor(PredictiveTextEngine *ptEngine)
{
    if (ptEngine == NULL)
    {
        printf("WARNING :: \t Attempted to Deconstruct a NULL PredictiveTextEngine");
        return;
    }
    
    wordTree_Deconstructor(ptEngine->wTree);
    free(ptEngine);
    
    return;
}


/// ====
/// Interface Functions
/// ====
char *predictiveTextEngine_predictWord(PredictiveTextEngine *pte, char *partialWord)
{
    // This is probably the most important function
    
    // TODO : improve this function.
    

    int len = strlen(partialWord);
	if (len < 2)
	{
		char buf = malloc(sizeof(char)*strlen(partialWord)+1);
		strcpy_s(buf, sizeof(buf), partialWord);
		return buf;
	}
    
    // we will need to walk the word tree until we find a node that starts with partial word. 
	wordTree_getWordBeginningWith(pte->wTree, partialWord);

}


/// ====
/// Hidden Functions
/// ====
