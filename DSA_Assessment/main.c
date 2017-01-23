// =====================================================
// <summary>
//  This is the entry point for the predictive text program
//  it is responsible for the UI and user interactions with the
//  system.
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PredictiveTextEngine/PredictiveTextEngine.h"

/// ====
/// Defines
/// ====
//#define UTEST //force unit testing in non unit test build

#ifdef UTEST
#include "UnitTests\UnitTester.h"
#endif // UTEST

/// ====
/// Prototypes
/// ====
void waitForInput(char *message);
void textEntryLoop();
void doPrediction(char *partial);

/// ====
/// Global
/// ====
PredictiveTextEngine *ptEngine;


/// ====
/// Main
/// ====

// Entry point
#ifdef UTEST

int main(void)
{
    if (UnitTester_RunTestSets() == 1)
    {
        exit(0);
    }
    else
    {
        exit(1);
    }
}
#else

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

#endif // UTEST

void textEntryLoop()
{
    int maxWordLength = predictiveTextEngine_MaxWordLength();
    char *inputBuffer = malloc(256 * sizeof(char));
    inputBuffer[0] = '\0';// strings have to end
    
    while (1)
    {
        fputc(' ', stdin);
        
        // TODO improve this
        
        // a buffer of out word. Auto resizing array list implementation would be better
        // and then read the new text in char by char and add it to the array
        char *info = fgets(inputBuffer, 256, stdin);
        
        //TODO :: Check info
        printf("\n=>\t %s \n", inputBuffer);
        
        // process to find just the last word.
        char *lastWord = malloc(maxWordLength * sizeof(char));
        lastWord[0] = '\0';
        
        int len = (int)strlen(inputBuffer);
        int i = 0;
        
        // walk backwards from the end of the string till we hit a space
        while (inputBuffer[len - i] != ' ')
        {
            i++;
        }
        
        //TODO:: other possible word separators '-' '_'
        // scan the buffer starting at the end looking for a space.
        char *lastSpace = strrchr(inputBuffer, ' ');
        
        // if we didn't find a space then assume that the entire buffer is one string
        if (lastSpace == NULL)
        {
            lastSpace = inputBuffer;
        }
        
        // the last word is between len and len-i
        int result = strcpy_s(lastWord, maxWordLength, lastSpace);
        
        // TODO:: check result
        printf("=>\t %s \n\n", lastWord);
        
        // try to predict a word based on the users input.
        doPrediction(lastWord);
    }
    
    free(inputBuffer);
}

void doPrediction(char *partial)
{
    int numGuesses = 8, maxWordLength = predictiveTextEngine_MaxWordLength();
    char **guesses = malloc(numGuesses * sizeof(char *));
    
    for (int k = 0; k < numGuesses; k++)
    {
        guesses[k] = malloc(maxWordLength * sizeof(char));
        guesses[k][0] = '\0';
    }
    
    int info = predictiveTextEngine_predictWords(ptEngine, partial, guesses, 8);
    
    // TODO:: clean input string before printing
    // TODO:: switch statement and expose some defines that make this more maintainable
    if (info == 1)
    {
        printf("=>\t  %s is a word!\n", partial);
    }
    else if (info == 0)
    {
        for (int i = 0; i < numGuesses; i++)
        {
            printf("=>\t  %s is probably %s\n", partial, guesses[i]);
        }
    }
    else if (info == -1)
    {
        printf("=>\t  %s wasn't found in the dictionary :'(", partial);
    }
    else
    {
        printf("[WARN] \t attempted to predict a word but got an unexpected value back !");
    }
    
    for (int j = 0; j < numGuesses; j++)
    {
        free(guesses[j]);
    }
    
    free(guesses);
}

// Block execution till the user presses enter
void waitForInput(char *message)
{
    printf("\n%s\n=> ", message);
    int result = getchar();
    printf("\n");
    return;
}