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
    
    ptEngine->trie = trie_Constructor();

	// populate the trie
	FILE* wordsfile = loadFile(WORDSFILE);
	int len = 0;
	char** words = getWordsArray(wordsfile,&len);
	closeFile(wordsfile);

	trie_AddMultiple(ptEngine->trie, words);
	freeWordsArray(words,len);
	trie_Print(ptEngine->trie);

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
char *predictiveTextEngine_predictWord(PredictiveTextEngine *pte, char *partialWord)
{
    // This is probably the most important function
    
    // TODO : improve this function.
    

    int len = (int)strlen(partialWord);

	// dont make guesses for words less than 2 letters long just return the input
	if (len < 2)
	{
		char *buf = malloc(sizeof(char)*strlen(partialWord)+1);
		strcpy_s(buf, sizeof(buf), partialWord);
		return buf;
	}
    
	// check to see if the partial word is in the trie
	if (trie_Contains(pte->trie, partialWord) == 1)
	{
		char *buf = malloc(sizeof(char)*strlen(partialWord) + 1);
		strcpy_s(buf, sizeof(buf), partialWord);
		return buf;
	}

	return NULL;
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

	printf("\r[DONE]\n");

	return count;
}

// Reads in *file one line at a time to obtain an array of lines
// Returns a char** of all the lines in the file
char **getWordsArray(FILE *file, int *lines)
{

	*lines = countLinesInFile(file);
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
			printf("\r[....]Reading word 0-%d from file : %s \t\t\t\t", i, words[i]);
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
		printf("\r[....] Freeing array, word %d of %d", i, length);
	}

	free(words);

	printf("\r[DONE] Freed array\t\t\t\t");
}