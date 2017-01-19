// =====================================================
// <summary> 
//	This file creates and manages predictive text engines that 
//	can taje partial words and make suggestions of complete words
//	that appear in a word list.
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Libarys/Trie.h"

/// ====
/// Defines
/// ====
#define WORDSFILE "Data/words.txt"// "Data/words.txt" or "Data/100words.txt"

/// ====
/// Type Definitions
/// ====
typedef struct PredictiveTextEngine PredictiveTextEngine;


/// ====
/// Prototypes
/// ====
FILE *loadFile(char* path);
void closeFile(FILE* file);
int countLinesInFile(FILE *file);

char **getWordsArray(FILE *file, int *lines);
void freeWordsArray(char **words, int length);

/// ====
/// Structures
/// ====
struct PredictiveTextEngine
{
    Trie *trie;
};


/// ====
/// Constructors and Destructor
/// ====
PredictiveTextEngine *predictiveTextEngine_Constructor(void)
{
    PredictiveTextEngine *ptEngine;
    ptEngine = malloc(sizeof(PredictiveTextEngine));
	if (ptEngine == NULL)
	{
		printf("[ERR!] \tUnable to assign memory for ptEngine\n");
		return NULL;
	}

    ptEngine->trie = trie_Constructor();

	// get the words for the trie
	FILE* wordsfile = loadFile(WORDSFILE);
	int len = 0;
	char** words = getWordsArray(wordsfile,&len);
	closeFile(wordsfile);

	//populate the trie
	trie_AddMultiple(ptEngine->trie, words, len);
	freeWordsArray(words,len);

    return ptEngine;
}

void predictiveTextEngine_Deconstructor(PredictiveTextEngine *ptEngine)
{
    if (ptEngine == NULL)
    {
        printf("[WARN]\t Attempted to Deconstruct a NULL PredictiveTextEngine\n");
        return;
    }
    
    trie_Deconstructor(ptEngine->trie);
    free(ptEngine);
    
    return;
}


/// ====
/// Interface Functions
/// ====

// Predicts a set of words from a partialWord
// Returns 1 if the partial word is a word
// Returns 0 if possible words are found
// Returns -1 if no word is found
int predictiveTextEngine_predictWords(PredictiveTextEngine *pte, char *partialWord, char** predictions, int numPredictions)
{
    // This is probably the most important function
    // TODO : improve this function.
    
	// TODO:: validity checks


	int numPosSoFar = 0; // how many possible words we have found so far

    int len = (int)strlen(partialWord);

	if (numPredictions > 1)
	{
		strcpy_s(predictions[0], 64, partialWord);
		numPosSoFar++;
	}

	// dont make guesses for words less than 2 letters long just return the input
	if (len < 2)
	{
		printf("[MESG] \t Partial word is too short to make any guesses, must be at least 2 letters long.\n");
		return -1;
	}

	// 1st prediction is always just the partial word so numPredictions must be one to make sense
	if (numPredictions < 2)
	{
		printf("[MESG] \t numPredictions is too small must be at least 2.\n");
		return -1;
	}

	//TODO:: switch/case statemnet
	//TODO:: have some defines in stead of checking against 0 , 1, -1
    
	// check to see if the partial word is in the trie
	int info = trie_Contains(pte->trie, partialWord);

	// The partial word is considered a word
	if (info == 1)
	{
		// word is in the trie so 
		strcpy_s(predictions[numPosSoFar], 64, partialWord);
		numPosSoFar++;
	}

	// There is a word in the trie that is prefixed by this partial word
	if ( info == 0 && numPosSoFar <= numPredictions)
	{
		int numberOfPredictionsToMake = (numPredictions - numPosSoFar);
		char** words = malloc(numberOfPredictionsToMake *sizeof(char*));
		for (int i = 0; i < numberOfPredictionsToMake; i++) words[i] = malloc(64 , sizeof(char));
		

		// find if there are any words in the trie that are prefixed by our partial word
		int numFound = trie_searchPrefixedBy(pte->trie, partialWord, words, numberOfPredictionsToMake);

		if (numFound > 0)
		{
			// we found some word prefixed by our partial word put them in our predictions array.
			for (int i = 0; i < numFound; i++)
			{
				strcpy_s(predictions[numPosSoFar+i],64,words[i]);
			}
		}
		numPosSoFar += numFound;

		for (int i = 0; i < numberOfPredictionsToMake; i++) words[i] = malloc(64 * sizeof(char));
		free(words);
	}

	// There is not a word in the the trie is directly prefixed by this trie
	if ( info == 0 && numPosSoFar <= numPredictions)
	{

	}

	// check too see if there are words prefixed with partial word

	// if we have found more than just the partial word the return 0
	return (numPosSoFar > 1) ? 0 : -1;
}


/// ====
/// Hidden Functions
/// ====

// Opens the file at *path for reading. 
// Returns a pointer to the opened file or a NULL pointer if file couldnt be opened
FILE *loadFile(char* path)
{
	FILE *file;
	errno_t err = fopen_s(&file, path, "r");

	if (err == 0)
	{
		printf("[DONE] Opened file '%s' \n", path);
	}
	else
	{
		printf("[WARN]\t Unable to open file '%s' \n", path);
		return NULL;
	}

	return file;
}

// Closes the file pointed to by *file
void closeFile(FILE* file)
{
	int err = fclose(file);
	if (err == 0)
	{
		printf("[DONE] Closing file \n");
	}
	else
	{
		printf("[WARN]\t Unable to close file \n");
	}
}

// Parses the file at *file and counts the number of lines
// Returns the number of line in *file
int countLinesInFile(FILE *file)
{
	printf("[    ] Counting lines in file");
	//make sure were at the begging of the file
	fseek(file, 0, SEEK_SET);

	int count = 0;
	char buf[64];

	while (fgets(buf, sizeof(buf), file) != NULL)
	{
		count++;
		printf("\r[....] Counted %d lines in file", count);
	}

	printf("\r[DONE]\t\t\t\t\n");

	return count;
}

// Reads in *file one line at a time to obtain an array of lines
// Returns a char** of all the lines in the file
char **getWordsArray(FILE *file, int *lines)
{

	*lines = countLinesInFile(file);
	if (*lines < 1)
	{
		printf("[ERR!] there wasn't any lines in the dictionary file, Exiting\n");
		exit(-1);
	}

	char **words = malloc(*lines * sizeof(char *));

	//make sure were at the begging of the file
	fseek(file, 0, SEEK_SET);

	printf("[    ] Getting Words from file");

	for (int i = 0; i < *lines; i++)
	{
		words[i] = malloc(sizeof(char) * 64);

		if (fgets(words[i], 64, file) != NULL)
		{
			// this removes the trailing \n from a word
			words[i][strcspn(words[i], "\n")] = 0;
			if (i % 100 == 0) printf("\r[....]Reading word 0-%d from file : %s \t\t\t\t", i, words[i]);
		}
		else
		{
			printf("\n[WARN]\t Unable to read line %d form file\t\t\n", i);
		}
	}

	printf("\r[DONE] Got Words from file \t\t\t\t\n");
	return words;
}

// Frees a char** of length length
void freeWordsArray(char **words, int length)
{
	printf("[    ] Freeing array");

	for (int i = 0; i < length; i++)
	{
		free(words[i]);
		if (i%100==0) printf("\r[....] Freeing array, word %d of %d", i, length);
	}

	free(words);

	printf("\r[DONE] Freed array\t\t\t\t\n");

	return;
}