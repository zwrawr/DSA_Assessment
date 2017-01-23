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
#include <conio.h>
#include "./Libarys/Stack.h"
#include "./Libarys/List.h"
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
List *doPrediction(char *partial);
char *addStackToListAndClear(Stack *stack, List *list);
char *stackToString(Stack *stack);
void printTextSoFar(List *list);

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
    
    Stack *letterStack = stack_Constructor();
    List *wordList = list_Constructor(maxWordLength * sizeof(char));
    
    char *inputBuffer = malloc(maxWordLength * sizeof(char));
    inputBuffer[0] = '\0';// strings have to end
    
    List *Suggestions = NULL;
    
    while (1)
    {
    
        // TODO improve this
        
        char letter = _getch();
        
        if (((letter >= 48) && (letter < 58)) || ((letter >= 65) && (letter < 91)) || ((letter >= 97) && (letter < 123)))
        {
            // the input is alphanumeric
            stack_Push(letterStack, (int)letter);
        }
        else if ( letter == 13)
        {
            // the input is an enter so add a new line to the terminal and finish the current word
            printf("\n");
            char *word = addStackToListAndClear(letterStack, wordList);
            free(word);
        }
        else if (letter == 8 || letter == 127)
        {
            // the input is delete or back space
            
            // if this word is not empty
            if (stack_GetHeight(letterStack) > 0)
            {
                stack_Pop_nv(letterStack);
            }
        }
        else if (letter == 32)
        {
            // the input is a space
            char *word = addStackToListAndClear(letterStack, wordList);
            free(word);
            
        }
        else if (letter == 0)
        {
            letter = _getch();
            
            // F1 - 6
            if (letter > 58 && letter < 66)
            {
            
                if (Suggestions != NULL &&  list_Size(Suggestions) > ((int)letter - 59))
                {
                    // clear the stack and add the chosen suggestion to the list
                    int stackHeight = stack_GetHeight(letterStack);
                    
                    for (int i = 0; i < stackHeight; i++)
                    {
                        stack_Pop_nv(letterStack);
                    }
                    
                    char *tmp = malloc(maxWordLength * sizeof(char));
                    list_Read(Suggestions, ((int)letter - 59), tmp);
                    
                    list_Add(wordList, tmp);
                    free(tmp);
                    
                }
            }
            
        }
        
        // grab the current partial word.
        char *lastWord = stackToString(letterStack);
        
        int len = (int)strlen(inputBuffer);
        
        // we need at least two char to make a prediction
        if (strlen(lastWord) > 1)
        {
        
        
            if (Suggestions != NULL)
            {
                list_Deconstructor(Suggestions);
            }
            
            Suggestions = doPrediction(lastWord);
        }
        
        printTextSoFar(wordList);
        
        printf("\r%s\t\t\t\t\t|", lastWord);
        
        free(lastWord);
    }
    
    free(inputBuffer);
}

List *doPrediction(char *partial)
{
    int numGuesses = 8, maxWordLength = predictiveTextEngine_MaxWordLength();
    char **guesses = malloc(numGuesses * sizeof(char *));
    
    // enough new lines to clear the screen
    printf("\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n");
    
    
    for (int k = 0; k < numGuesses; k++)
    {
        guesses[k] = malloc(maxWordLength * sizeof(char));
        guesses[k][0] = '\0';
    }
    
    int info = predictiveTextEngine_predictWords(ptEngine, partial, guesses, numGuesses);
    
    // TODO:: clean input string before printing
    // TODO:: switch statement and expose some defines that make this more maintainable
    if (info == 1)
    {
        printf("[F1]\t %s\n", partial);
    }
    else if (info > 0)
    {
        for (int i = 0; i < numGuesses; i++)
        {
            printf("[F%d]\t %s\n", i + 1 , guesses[i]);
        }
    }
    
    List *suggestions = list_Constructor(maxWordLength * sizeof(char));
    
    for (int j = 0; j < numGuesses; j++)
    {
        list_Add(suggestions, guesses[j]);
        free(guesses[j]);
    }
    
    free(guesses);
    
    return suggestions;
}

// Block execution till the user presses enter
void waitForInput(char *message)
{
    printf("\n%s\n=> ", message);
    int result = getchar();
    printf("\n");
    return;
}

// turns a stack into a string and adds it to the list
char *addStackToListAndClear(Stack *stack, List *list)
{
    int height = stack_GetHeight(stack);
    char *tmpString = malloc(predictiveTextEngine_MaxWordLength() * sizeof(char));
    
    for (int i = 0; i < height; i++)
    {
        int popped = 'a';
        stack_Pop(stack, &popped);
        tmpString[height - i - 1] = (char)popped; // remember stacks are backwards. A queue may be better for this but that means adding more code
    }
    
    tmpString[height] = '\0';
    
    list_Add(list, tmpString);
    
    return tmpString;
}

char *stackToString(Stack *stack)
{
    int height = stack_GetHeight(stack);
    char *tmpString = malloc(predictiveTextEngine_MaxWordLength() * sizeof(char));
    
    for (int i = 0; i < height; i++)
    {
        int peeked = 'a';
        stack_Peek(stack, i, &peeked);
        tmpString[i] = (char)peeked;
    }
    
    tmpString[height] = '\0';
    
    return tmpString;
}

void printTextSoFar(List *list)
{
    int length = list_Size(list);
    char *tmpString = malloc(predictiveTextEngine_MaxWordLength() * sizeof(char));
    tmpString[0] = '\0';
    
    for (int i = 0; i < length; i++)
    {
        list_Read(list, i, tmpString);
        printf("%s ", tmpString);
    }
    
    free(tmpString);
}