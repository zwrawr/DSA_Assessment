#include <stdio.h>
#include <stdlib.h>
#include "WordTree/WordTree.h"

/// ====
/// Defines
/// ====


/// ====
/// TypeDefs
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
	WordTree* wTree;
};


/// ====
/// Constructors and Destructor
/// ====
PredictiveTextEngine *predictiveTextEngine_Constructor(void)
{
	PredictiveTextEngine* ptEngine;
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


/// ====
/// Hidden Functions
/// ====
