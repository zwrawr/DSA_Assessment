// =====================================================
// <summary>
//  This file is responsible for unit testing the file "Trie.c"
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "..\UnitTests\UnitTestRunner.h"

// Under test
#include "..\Libarys\Trie.h"

/// ====
/// Defines
/// ====


/// ====
/// Prototypes
/// ====

// These are all of our tests
// They all retrun 1 if they passed

int RunTest_0(UTRunner *utr);
int RunTest_1(UTRunner *utr);
int RunTest_2(UTRunner *utr);
int RunTest_3(UTRunner *utr);
int RunTest_4(UTRunner *utr);
int RunTest_5(UTRunner *utr);

char *getTooLongWord();


/// ====
/// Public Functions
/// ====

// Returns 1 if all tests passed
int trie_UT_RunTests(FILE *log)
{
    int(*TestFunctions[])(UTRunner * utr) =
    {
        RunTest_0,
        RunTest_1,
        RunTest_2,
        RunTest_3,
        RunTest_4,
        RunTest_5
    };
    
    int numTestFunctions = sizeof(TestFunctions) / sizeof(TestFunctions[0]);
    
    UTRunner *utr = utr_Constructor(numTestFunctions, TestFunctions, "Trie", log);
    int result = utr_RunTests(utr);
    utr_Deconstructor(utr);
    
    return result;
}



/// ====
/// Hidden Functions
/// ====

int RunTest_0(UTRunner *utr)
{
    // test to see if that a constructed trie isnt null
    Trie *trie = trie_Constructor();
    
    int passed = (trie == NULL) ? 0 : 1;
    
    trie_Deconstructor(trie);
    utr_PrintMessage(utr, passed, "Constructed trie pointer was not null", "Constructed trie pointer was null");
    return passed;
}

int RunTest_1(UTRunner *utr)
{
    // test to see if that we can add values to a trie
    char *tooLongWord = getTooLongWord();
    
    Trie *trie = trie_Constructor();
    
    int info = 0;
    
    // we should be able to add values now
    info = (trie_Add(trie, "test") == 1) ? info : -1;
    
    // shouldnt be able to add nothing
    info = (trie_Add(trie, "") == 0) ? info : -1;
    
    // should be able to add this
    info = (trie_Add(trie, "tests") == 1) ? info : -1;
    
    // should not be able to add a word thats too long
    info = (trie_Add(trie, tooLongWord) == 0) ? info : -1;
    
    // should be able to add the same word twice
    info = (trie_Add(trie, "testing") == 1) ? info : -1;
    info = (trie_Add(trie, "testing") == 1) ? info : -1;
    
    int passed = ((trie == NULL)) ? 0 : 1;
    
    trie_Deconstructor(trie);
    free(tooLongWord);
    utr_PrintMessage(utr, passed, "Adding values to a trie worked", "Adding values to a trie di not work");
    return passed;
}

int RunTest_2(UTRunner *utr)
{
    // test to see if that contains is working
    char *tooLongWord = getTooLongWord();
    
    int info = 0;
    // make sure we check a null trie
    info = (trie_Add(NULL, "test") == -1) ? info : -1;
    info = (trie_Add(NULL, NULL) == -1) ? info : -1;
    
    Trie *trie = trie_Constructor();
    
    // make sure we cannot check if null is in a trie
    info = (trie_Add(trie, NULL) == -1) ? info : -1;
    
    // make sure we cannot check to see if a tool long word is in the trie
    info = (trie_Add(trie, tooLongWord) == -1) ? info : -1;
    
    // add a bunch of words
    info = (trie_Add(trie, "test") == 1) ? info : -1;
    info = (trie_Add(trie, "tests") == 1) ? info : -1;
    info = (trie_Add(trie, "testing") == 1) ? info : -1;
    info = (trie_Add(trie, "hi") == 1) ? info : -1;
    info = (trie_Add(trie, "hello") == 1) ? info : -1;
    info = (trie_Add(trie, "help") == 1) ? info : -1;
    
    // see if the trie contains the word we added
    info = (trie_Contains(trie, "test") == 1) ? info : -1;
    info = (trie_Contains(trie, "tests") == 1) ? info : -1;
    info = (trie_Contains(trie, "testing") == 1) ? info : -1;
    info = (trie_Contains(trie, "hi") == 1) ? info : -1;
    info = (trie_Contains(trie, "hello") == 1) ? info : -1;
    info = (trie_Contains(trie, "help") == 1) ? info : -1;
    
    // see if the trie contains words we didnt add
    info = (trie_Contains(trie, "avacardo") == -1) ? info : -1;
    info = (trie_Contains(trie, "testEquipment") == -1) ? info : -1;
    info = (trie_Contains(trie, "z") == -1) ? info : -1;
    info = (trie_Contains(trie, "v") == -1) ? info : -1;
    
    // see if the trie contains prefixes of words we added
    info = (trie_Contains(trie, "t") == 0) ? info : -1;
    info = (trie_Contains(trie, "tes") == 0) ? info : -1;
    info = (trie_Contains(trie, "tesin") == 0) ? info : -1;
    info = (trie_Contains(trie, "h") == 0) ? info : -1;
    info = (trie_Contains(trie, "he") == 0) ? info : -1;
    info = (trie_Contains(trie, "hell") == 0) ? info : -1;
    
    
    int passed = (trie == NULL) ? 0 : 1;
    
    trie_Deconstructor(trie);
    free(tooLongWord);
    utr_PrintMessage(utr, passed, "Contains worked", "Contains did not work");
    return passed;
}


int RunTest_3(UTRunner *utr)
{
    // test to see if that we can add multiple values to a trie
    
    char *words1[] =
    {
        "hey",
        "hello",
        "hell",
        "help",
        "havoc",
        "death",
        "unit",
        "testing",
        "is",
        "really",
        "boring",
        "born",
        "border",
        "units",
        "avacado"
    };
    
    char *words2[] =
    {
        "pineapple",
        "horseracing",
        "dyslexia",
        "makes",
        "spelling",
        "words",
        "hard"
    };
    
    int numWords1 = sizeof(words1) / sizeof(words1[0]);
    int numWords2 = sizeof(words2) / sizeof(words2[0]);
    
    
    Trie *trie = trie_Constructor();
    
    int info = 0;
    
    // we should be able to add values now
    info = (trie_AddMultiple(trie, words1, numWords1) == 1) ? info : -1;
    
    // lets check there in there
    info = (trie_Contains(trie, words1[2]) == 1) ? info : -1;
    info = (trie_Contains(trie, words1[7]) == 1) ? info : -1;
    
    // lets use a normal add along side add multiple
    char newWord[] = "new";
    info = (trie_Add(trie, newWord) == 1) ? info : -1;
    
    // lets see if we can add more.
    info = (trie_AddMultiple(trie, words2, numWords2) == 1) ? info : -1;
    
    // lets check there in there
    info = (trie_Contains(trie, words2[2]) == 1) ? info : -1;
    info = (trie_Contains(trie, words2[4]) == 1) ? info : -1;
    info = (trie_Contains(trie, newWord) == 1) ? info : -1;
    
    
    
    
    int passed = (trie == NULL) ? 0 : 1;
    
    trie_Deconstructor(trie);
    utr_PrintMessage(utr, passed, "Adding Multiple values to a trie worked", "Adding Multiple values to a trie di not work");
    return passed;
}

int RunTest_4(UTRunner *utr)
{
    // test to see if trie print is working
    
    // I cannot think of a way to check if what is being printed out is correct appart from grabbing the screen buffer
    // (which isnt ISO C) or mocking printf ( No idea how you'd go about mocking stuff in C )
    
    int info = 0;
    char *words[] =
    {
        "hey",
        "hello",
        "hell",
        "help",
        "havoc",
        "death",
        "unit",
        "testing",
        "is",
        "really",
        "boring",
        "born",
        "border",
        "units",
        "avacado"
    };
    int numWords = sizeof(words) / sizeof(words[0]);
    
    info = (trie_Print(NULL) == -1) ? info : -1;
    
    Trie *trie = trie_Constructor();
    info = (trie_Print(trie) == 0) ? info : -1;
    
    
    // add some words to the trie
    info = (trie_AddMultiple(trie, words, numWords) == 1) ? info : -1;
    info = (trie_Print(trie) == 1) ? info : -1;
    
    int passed = (trie == NULL) ? 0 : 1;
    
    trie_Deconstructor(trie);
    utr_PrintMessage(utr, passed, "Printing a trie worked", "Printing a trie did not work");
    return passed;
}

int RunTest_5(UTRunner *utr)
{
    // test to see if trie searchByPrefix works
    
    int info = 0;
    
    // make sure we cannot look up words in a null trie
    info = (trie_searchByPrefix(NULL, "test", NULL, 0) == -1) ? info : -1;
    
    char *words[] =
    {
        "he",
        "hey",
        "hello",
        "hell",
        "help",
        "havoc",
        "helipad",
        "helicopter",
        "death",
        "dead",
        "deadly",
        "bead",
        "cread",
        "fell",
        "helicopters",
        "heliocentric",
        "units",
        "avacado"
    };
    int numWords = sizeof(words) / sizeof(words[0]);
    
    int numResults = 4;
    char **results = malloc(numResults * sizeof(char *));
    
    for (int i = 0; i < numResults; i++)
    {
        results[i] = malloc(MAXWORDLENGTH * sizeof(char));
    }
    
    Trie *trie = trie_Constructor();
    
    // make sure we cannot look up word if we have no weare to put them
    info = (trie_searchByPrefix(trie, "test", NULL, 0) == -1) ? info : -1;
    info = (trie_searchByPrefix(trie, "test", NULL, 2) == -1) ? info : -1;
    info = (trie_searchByPrefix(trie, NULL, results, 2) == -1) ? info : -1;
    info = (trie_searchByPrefix(trie, "test", results, 0) == -1) ? info : -1;
    info = (trie_searchByPrefix(trie, "test", results, -1) == -1) ? info : -1;
    
    // add the words to the trie
    info = (trie_AddMultiple(trie, words, numWords) == 1) ? info : -1;
    
    // lets look words prexifed by a word thats not in the trie, this should return -1
    info = (trie_searchByPrefix(trie, "test", results, numResults) == -1) ? info : -1;
    
    // lets look words prexifed by a word thats not in the trie,but the trie dose contain words prexied by it this should return 2 (helicopter and helicopters)
    info = (trie_searchByPrefix(trie, "helico", results, numResults) == 2) ? info : -1;
    info = (strcmp(results[0], "helicopter"), 0) ? info : -1;
    info = (strcmp(results[1], "helicopters"), 0) ? info : -1;
    
    // lets look words prexifed by heli (in trie but not starred),should return 4 (helipad, helicopter, helicopters,heliocentric)
    info = (trie_searchByPrefix(trie, "heli", results, numResults) == 4) ? info : -1;
    info = (strcmp(results[0], "helipad"), 0) ? info : -1;
    info = (strcmp(results[1], "helicopter"), 0) ? info : -1;
    info = (strcmp(results[2], "helicopters"), 0) ? info : -1;
    info = (strcmp(results[3], "heliocentric"), 0) ? info : -1;
    
    // lets look only 2 words prexifed by heli (in trie but not starred),should return 4 (helipad, helicopter, helicopters,heliocentric)
    info = (trie_searchByPrefix(trie, "heli", results, 2) == 2) ? info : -1;
    info = (strcmp(results[0], "helipad"), 0) ? info : -1;
    info = (strcmp(results[1], "helicopter"), 0) ? info : -1;
    
    // lets try to find words prefixed by a word in the trie
    info = (trie_searchByPrefix(trie, "de", results, numResults) == 3) ? info : -1;
    info = (strcmp(results[0], "dead"), 0) ? info : -1;
    info = (strcmp(results[1], "death"), 0) ? info : -1;
    info = (strcmp(results[2], "deadly"), 0) ? info : -1;
    
    // lets look for a
    info = (trie_searchByPrefix(trie, "test", results, numResults) == -1) ? info : -1;
    
    int passed = (trie == NULL) ? 0 : 1;
    
    trie_Deconstructor(trie);
    
    for (int i = 0; i < numResults; i++)
    {
        free(results[i]);
    }
    
    free(results);
    utr_PrintMessage(utr, passed, "Prefix based searches work", "Prefix based searches did not work");
    return passed;
}


char *getTooLongWord()
{
    char *tooLongWord = malloc(sizeof(char) * (MAXWORDLENGTH + 1));
    tooLongWord[MAXWORDLENGTH] = '\0';
    
    for (int i = 0; i < MAXWORDLENGTH; i++)
    {
        tooLongWord[i] = (64 + (i % 26));
    }
    
    return tooLongWord;
}