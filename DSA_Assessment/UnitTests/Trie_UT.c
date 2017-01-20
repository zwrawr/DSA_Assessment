// =====================================================
// <summary>
//  This file is responsible for unit testing the file "Trie.c"
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================
#include <stdlib.h>
#include <stdio.h>
#include "..\UnitTests\UnitTestRunner.h"
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
        RunTest_2
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
    info = (trie_Add(trie, "") == 0) ? info : -1;
    info = (trie_Add(trie, "tests") == 1) ? info : -1;
    info = (trie_Add(trie, tooLongWord) == 0) ? info : -1;
    info = (trie_Add(trie, "testing") == 1) ? info : -1;
    
    int passed = (trie == NULL) ? 0 : 1;
    
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
    
    int numWords1 = sizeof(words1) / sizeof(words1[0]);
    
    
    Trie *trie = trie_Constructor();
    
    int info = 0;
    
    // we should be able to add values now
    info = (trie_AddMultiple(trie, words1, numWords1) == 1) ? info : -1;
    
    //info = (trie_AddMultiple(trie, "") == 0) ? info : -1;
    
    
    int passed = (trie == NULL) ? 0 : 1;
    
    trie_Deconstructor(trie);
    utr_PrintMessage(utr, passed, "Adding values to a trie worked", "Adding values to a trie di not work");
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