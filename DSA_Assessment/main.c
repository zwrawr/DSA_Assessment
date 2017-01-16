#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PredictiveTextEngine/PredictiveTextEngine.h"


/// ====
/// Prototypes
/// ====
void waitForInput(char *message);
void textEntryLoop();
void doPrediction(char* partial);

/// ====
/// Global
/// ====
PredictiveTextEngine *ptEngine;


/// ====
/// Main
/// ====
// Entry point
int main(void)
{
    ptEngine = predictiveTextEngine_Constructor();
    
	if (ptEngine == NULL)
	{
		printf("[ERR!] \t Couldn't create the predictive text engine, Exiting\n\n");
		exit(-1);
	}

	textEntryLoop();

    waitForInput("Press Enter to exit.");
    predictiveTextEngine_Deconstructor(ptEngine);
    
    return 0;
}

void textEntryLoop()
{
	char* inputBuffer = malloc(256 * sizeof(char));

	while (1)
	{
		fputc(' ', stdin);

		// TODO improve this
		// a buffer of out word. Auto resizing array list implimentation would be better
		// and then read the new text in nchar by char and add it to the array
		char* info = fgets(inputBuffer, 256, stdin);
		//TODO :: Check info

		// proccess to find just the last word.

		//TODO:: expose MAXWORDLENGTH in interface then use that here
		char lastWord[64];

		int len = (int)strlen(inputBuffer);

		int i = 0;
		// walk backwards from the end of the string till we hit a space
		while (inputBuffer[len - i] != ' ') i++;

		//TODO:: theres an error condition if theres no spaces in the word.

		// the last word is between len and len-i
		char* result = strncpy_s(lastWord,64 ,inputBuffer + len - i, i);
		// TODO:: check result

		doPrediction(lastWord);
	}

	free(inputBuffer);
}

void doPrediction(char* partial)
{
	//TODO:: expose MAXWORDLENGTH
	char guess[64];
	int info = predictiveTextEngine_predictWord(ptEngine, partial, guess);

	// TODO:: switch statement and expose some defines that make this more maintainable
	if (info == 1)
	{
		printf("=>\t  %s is a word!\n", partial);
	}
	else if (info == 0)
	{
		printf("=>\t  %s is probably %s\n", partial, guess);
	}
	else if (info == -1)
	{
		printf("=>\t  %s wasn't found in the dictionary :'(", partial);
	}
	else
	{
		printf("[WARN] \t attempted to predict a word but got an unexpected value back !");
	}

}

// Block execution till theres an input.
void waitForInput(char *message)
{
    printf("\n%s\n=> ", message);
    int result = getchar();
    printf("\n");
    
    return;
}