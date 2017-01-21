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
#include "..\Libarys\PredictiveTextEngine.h"

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
int RunTest_6(UTRunner *utr);

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

	int passed = (trie == NULL) ? 0 : 1;

	trie_Deconstructor(trie);
	free(tooLongWord);
	utr_PrintMessage(utr, passed, "Adding values to a trie worked", "Adding values to a trie di not work");
	return passed;
}