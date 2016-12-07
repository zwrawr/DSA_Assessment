#include <stdio.h>
#include <stdlib.h>
#include "PredictiveTextEngine/PredictiveTextEngine.h"

/// ====
///	Prototypes
/// ====
void init(PredictiveTextEngine* ptEngine);
void deinit(PredictiveTextEngine* ptEngine);

/// ====
///	Main
/// ====
// Entry point
int main(void)
{
	PredictiveTextEngine* ptEngine;
	init(ptEngine);



	waitForInput("Press any key to exit.");
	deinit(ptEngine);

	return 0;
}


/// ====
///	Functions
/// ====
// Sets up datastructres.
void init(PredictiveTextEngine* ptEngine)
{
	ptEngine = predictiveTextEngine_Constructor();

	return;
}

// Tears down datastructres.
void deinit(PredictiveTextEngine* ptEngine)
{
	predictiveTextEngine_Deconstructor(ptEngine);

	return;
}

// Block exicution till theres an input.
void waitForInput(char* message)
{
	printf("\n%s\n=> ",message);
	getchar();
	printf("\n");
	
	return;
}