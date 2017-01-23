// =====================================================
// <summary>
//  This file is responsible for unit testing the file "List.c",
//  The list implementation is generic but it is only used for
//  char* in the code base so that what I'm testing it with.
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "..\UnitTests\UnitTestRunner.h"

// Under test
#include "..\Libarys\Trie.h"

/// ====
/// Defines
/// ====
#define DEFAULT 0

#define WORDS_10 "Data/10words.txt"
#define WORDS_100 "Data/100words.txt"
#define WORDS_1000 "Data/1000words.txt"
#define WORDS_10000 "Data/10000words.txt"
#define WORDS_25000 "Data/words.txt"


/// ====
/// Prototypes
/// ====
clock_t lookups(Trie *trie, char **words, int numWords);
clock_t searchesbyprefix(Trie *trie, char **words, int numWords);

char **_LoadWordsIntoTrie(char *path, Trie *trie, clock_t *timeForInsert, int *num);
FILE *_loadFile(char *path);
void _closeFile(FILE *file);
int _countLinesInFile(FILE *file);

int doSpeedTest(char *path, UTRunner *utr);


char **_getWordsArray(FILE *file, int *lines);
void _freeWordsArray(char **words, int length);
// These are all of our tests
// They all return 1 if they passed

int RunTest_10words(UTRunner *utr);
int RunTest_100words(UTRunner *utr);
int RunTest_1000words(UTRunner *utr);
int RunTest_10000words(UTRunner *utr);
int RunTest_25000words(UTRunner *utr);



/// ====
/// Public Functions
/// ====

// Returns 1 if all tests passed
int complexity_UT_RunTests(FILE *log)
{
    int(*TestFunctions[])(UTRunner * utr) =
    {
        RunTest_10words,
        RunTest_100words,
        RunTest_1000words,
        RunTest_10000words,
        RunTest_25000words
    };
    int numTestFunctions = sizeof(TestFunctions) / sizeof(TestFunctions[0]);
    
    UTRunner *utr = utr_Constructor(numTestFunctions, TestFunctions, "Complexity", log);
    int result = utr_RunTests(utr);
    utr_Deconstructor(utr);
    
    return result;
}



/// ====
/// Hidden Functions
/// ====

int RunTest_10words(UTRunner *utr)
{
    doSpeedTest(WORDS_10, utr);
    return 1;
}

int RunTest_100words(UTRunner *utr)
{
    doSpeedTest(WORDS_100, utr);
    return 1;
}

int RunTest_1000words(UTRunner *utr)
{
    doSpeedTest(WORDS_1000, utr);
    return 1;
}

int RunTest_10000words(UTRunner *utr)
{
    doSpeedTest(WORDS_10000, utr);
    return 1;
}

int RunTest_25000words(UTRunner *utr)
{
    doSpeedTest(WORDS_25000, utr);
    return 1;
}

int doSpeedTest(char *path, UTRunner *utr)
{
    // test to see if that a constructed list isn't null
    Trie *trie = trie_Constructor();
    
    clock_t insertion;
    
    int numTest = 0;
    char **words = _LoadWordsIntoTrie(path, trie, &insertion, &numTest);
    
    
    // test insert speed
    char insertionMessage[256] = "";
    sprintf_s(insertionMessage, 256, " \nTook %f seconds to insert %d items, time per item %f \n",
              (float)insertion / CLOCKS_PER_SEC,
              numTest,
              (float)insertion / (CLOCKS_PER_SEC * 10.0));
              
              
    // test lookup speed
    clock_t lookuptime = lookups(trie, words, numTest);
    char lookupMessage[256] = "";
    sprintf_s(lookupMessage, 256, " Took %f seconds to lookup %d items, time per item %f \n",
              (float)lookuptime / CLOCKS_PER_SEC,
              numTest,
              (float)lookuptime / (CLOCKS_PER_SEC * 10.0)
             );
             
    // test search by prefix speed
    clock_t searchbyprefixtime = searchesbyprefix(trie, words, numTest);
    char searchMessage[256] = "";
    sprintf_s(searchMessage, 256, " Took %f seconds to search by prefix %d items, time per item %f \n",
              (float)searchbyprefixtime / CLOCKS_PER_SEC,
              numTest,
              (float)searchbyprefixtime / (CLOCKS_PER_SEC * 10.0)
             );
             
    // build message
    char message[1024] = "";
    sprintf_s(message, 1024, "%s %s %s \n", insertionMessage, lookupMessage, searchMessage);
    int passed = (trie == NULL) ? 0 : 1;
    
    _freeWordsArray(words, 10);
    trie_Deconstructor(trie);
    utr_PrintMessage(utr, passed, message, " ");
    return passed;
}

clock_t searchesbyprefix(Trie *trie, char **words, int numWords)
{
    int numberOfPredictionsToMake = 4;
    char **results = malloc(numberOfPredictionsToMake * sizeof(char *));
    
    for (int i = 0; i < numberOfPredictionsToMake; i++)
    {
        results[i] = malloc(MAXWORDLENGTH * sizeof(char));
        results[i][0] = '\0';
    }
    
    clock_t start = clock();
    
    for (int i = 0; i < numWords; i++)
    {
    
        trie_searchByPrefix(trie, words[i], results, numberOfPredictionsToMake);
    }
    
    clock_t end = clock();
    
    _freeWordsArray(results, numberOfPredictionsToMake);
    
    return end - start;
}

clock_t lookups(Trie *trie, char **words, int numWords)
{
    clock_t start = clock();
    
    for (int i = 0; i < numWords; i++)
    {
        trie_Contains(trie, words[i]);
    }
    
    clock_t end = clock();
    return end - start;
}

char **_LoadWordsIntoTrie(char *path, Trie *trie, clock_t *timeForInsert, int *num)
{
    // get the words for the trie
    FILE *wordsfile = _loadFile(path);
    char **words = _getWordsArray(wordsfile, num);
    _closeFile(wordsfile);
    
    clock_t start = clock();
    //populate the trie
    trie_AddMultiple(trie, words, *num);
    clock_t end = clock();
    
    *timeForInsert = end - start;
    //freeWordsArray(words, len);
    return words;
}



// Opens the file at *path for reading.
// Returns a pointer to the opened file or a NULL pointer if file couldn't be opened
FILE *_loadFile(char *path)
{
    // Validity checks
    if (path == NULL || strlen(path) < 1)
    {
        return NULL;
    }
    
    FILE *file;
    errno_t err = fopen_s(&file, path, "r");
    
    if (err != 0)
    {
        printf("[WARN]\t Unable to open file '%s' \n", path);
        return NULL;
    }
    
    return file;
}

// Closes the file pointed to by *file
void _closeFile(FILE *file)
{
    if (file == NULL)
    {
        return;
    }
    
    int err = fclose(file);
    
    if (err != 0)
    {
        printf("[WARN]\t Unable to close file \n");
    }
}




int _countLinesInFile(FILE *file)
{
    if (file == NULL)
    {
        return -1;
    }
    
    int count = 0;
    char buf[MAXWORDLENGTH];
    
    //make sure were at the begging of the file
    fseek(file, 0, SEEK_SET);
    
    while (fgets(buf, sizeof(buf), file) != NULL)
    {
        count++;
    }
    
    return count;
}


char **_getWordsArray(FILE *file, int *lines)
{
    if (file == NULL)
    {
        return NULL;
    }
    
    *lines = _countLinesInFile(file);
    
    if (*lines < 1)
    {
        printf("[ERR!] there wasn't any lines in the dictionary file, Exiting\n");
        exit(-1);
    }
    
    //make sure were at the begging of the file
    fseek(file, 0, SEEK_SET);
    
    // allocate an array that can hold a string for each line of the file
    char **words = malloc(*lines * sizeof(char *));
    
    
    
    for (int i = 0; i < *lines; i++)
    {
        words[i] = malloc(sizeof(char) * MAXWORDLENGTH);
        words[i][0] = '\0';
        
        
        if (fgets(words[i], MAXWORDLENGTH, file) != NULL)
        {
            // this removes the trailing \n from a word
            words[i][strcspn(words[i], "\n")] = 0;
            
        }
        else
        {
            printf("\n[WARN]\t Unable to read line %d form file\t\t\n", i);
        }
    }
    
    return words;
}

void _freeWordsArray(char **words, int length)
{
    if (words == NULL)
    {
        return;
    }
    
    // free each element in the array
    for (int i = 0; i < length; i++)
    {
        free(words[i]);
    }
    
    // free the array
    free(words);
    return;
}