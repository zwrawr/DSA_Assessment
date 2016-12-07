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
	PredictiveTextEngine* ptEngine = malloc(sizeof(PredictiveTextEngine));
	ptEngine->wTree = wordTree_Constructor();

	return;
}

void predictiveTextEngine_Deconstructor(PredictiveTextEngine *ptEngine)
{
	wordTree_Destructor(ptEngine->wTree);
	free(ptEngine);

	return;
}


/// ====
/// Interface Functions
/// ====


/// ====
/// Hidden Functions
/// ====
