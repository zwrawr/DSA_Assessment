#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// ====
/// Defines
/// ====
#define MAXWORDLENGTH 64
/// ====
/// Type Definitions
/// ====
typedef struct Trie Trie;
typedef struct TrieElement TrieElement;


/// ====
/// Prototypes
/// ====
TrieElement* trieElement_Constructor();
void trieElement_Deconstructor(TrieElement* trieElement);
void recursivePrint(TrieElement* curr, char* string, int depth);
int charToIndex(char c);
char indexToChar(int index);
int insert(Trie* trie, char* string);



/// ====
/// Structures
/// ====
struct Trie
{
	int size; //number of TrieElements currently in this trie
	TrieElement *root; //the root element of the trie is always " " <- a space
};

struct TrieElement
{
	TrieElement** children;//26 pointers one for each letter of the alphabet
	TrieElement* parent;

	//TODO:: if C99 is allowed then use bools for the memory reduction
	int starred; // if 1 this node represents a compleate word. All leaf elements are starred elements.
};

/// ====
/// Constructors and Destructor
/// ====

Trie* trie_Constructor(void)
{
	Trie* trie;
	trie = malloc(sizeof(Trie));

	trie->root = trieElement_Constructor();
	trie->root->parent = trie->root; // the first element in the trie is it's own parent
	trie->size = 1;

	return trie;
}

void trie_Deconstructor(Trie* trie)
{
	if (trie == NULL)
	{
		// cannot free a NULL trie
		return;
	}

	// clean up any elements accociated with this trie
	trieElement_Deconstructor(trie->root);

	free(trie);

	return;
}

TrieElement* trieElement_Constructor()
{
	TrieElement* trieElement;

	trieElement = malloc(sizeof(TrieElement));
	trieElement->parent = NULL;

	trieElement->starred = 0;

	trieElement->children = malloc(26*sizeof(TrieElement*)); // 26 pointers to TrieElements one for each letter
	for (int i = 0; i < 26; i++)
	{
		trieElement->children[i] = NULL;
	}

	return trieElement;
}

void trieElement_Deconstructor(TrieElement* trieElement)
{
	// deconstruct the children
	for (int i = 0; i < 26; i++)
	{
		if (trieElement->children[i] != NULL)
		{
			trieElement_Deconstructor(trieElement->children[i]);
		}
	}
	// free 'this'
	free(trieElement);

	return;
}
/// ====
/// Interface Functions
/// ====

// Adds the item(word) to the trie data structure
// Returns 1 if addition was succesful
// Returns 0 if unsuccesful
int trie_Add(Trie* trie, char* item)
{
	if (trie == NULL || trie->root == NULL )
	{
		return 0; // NULL or broken trie so dont attempt to add to it
	}
	else if( ( strlen(item) < 1 ) || ( strlen(item) > (MAXWORDLENGTH - 1) ) )
	{
		return 0; // cannot add a word with less than 1 letter or more than MAXWORDLENGTH -1
	}

	// insert this element into the trie
	int err = insert(trie, item);

	trie->size++;
	return 1;
}

// Adds the items(words) to the trie data structure
// Returns 1 if additions were succesful
// Returns 0 if unsuccesful
int trie_AddMultiple(Trie* trie, char** items, int num)
{
	if (items == NULL)
	{
		return 0;
	}

	int errs = 0;

	for (int i = 0; i < num; i++)
	{
		if (trie_Add(trie, items[i]) != 1)
		{
			errs++; // if and addtion was unsuccesful increment the number of errors
		}
	}

	if (errs == 0)
	{
		return 1; 
	}
	else
	{
		return 0;
	}
}

// prints out the words in the trie in alphabetical order
void trie_Print(Trie* trie)
{
	// traverse the trie in pre-order and print the node if its starred

	TrieElement* curr = trie->root;
	char string[MAXWORDLENGTH];
	int depth = 0;

	recursivePrint(curr, &string, depth);

}

// Tests to see if a word is in the trie
// Returns 1 if item is in the trie and starred (its considered a word)
// Returns 0 if the item is in the trie but not starred (its a partial word)
// Returns -1 if its not in the trie
int trie_Contains(Trie* trie, char* item)
{
	//TODO:: VALIDITY CHECKS

	int len = (int)strlen(item);
	TrieElement* curr = trie->root;

	// for each letter in the string
	for (int i = 0; i < len; i++)
	{
		// if this element has a child element in the position that matchs the letter in the string
		// then move to that element or return -1 (item isnt in the trie)
		if (curr->children[charToIndex(item[i])] != NULL) 
		{
			curr = curr->children[charToIndex(item[i])];
		}
		else
		{
			return -1;
		}
	}

	// if we get here then curr is the node in the trie that represents item
	// return value depends on curr is starred (curr is a word or partial word)
	if (curr->starred == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/// ====
/// Hidden Functions
/// ====

// recurively prints the trie
void recursivePrint(TrieElement* curr, char* string, int depth)
{
	if (curr->starred == 1)
	{
		printf("> %s\n", string);
	}

	for (int i = 0; i < 26; i++)
	{
		if (curr->children[i] != NULL) {
			string[depth] = indexToChar(i + 1);
			string[depth+1] = '\0';

			recursivePrint(curr->children[i], string, depth + 1);
		}
	}
	return;
}

// returns the index of a char in the alphabet regardless of case or 0 if it is not alphabetic
// a=1, A=1, b=2, B=2, ... , z=26, Z=26 
int charToIndex(char c)
{
	if (c > 64 && c < 91)
	{
		// uppercase letter
		return c - 64;
	}
	else if (c > 96 && c < 123)
	{
		// uppercase letter
		return c - 96;
	}

	return 0;
}

///TODO:: Do we want this function to be so permisive? why not return ' ' if 1 > index or index > 26 ??

// turns an index to a char
// 1=a, 2=b, ... , 26=z
char indexToChar(int index)
{
	return 96 + index % 26;
}

// inserts a trieElement into a trie
// returns 1 if the insertion was successful
int insert(Trie* trie, char* string)
{
	if (trie == NULL || trie->root == NULL || string==NULL || strlen(string) < 1)
	{
		return 0; // NULL or broken trie or NULL or empty string so dont attempt to add to it
	}

	TrieElement* curr = trie->root;

	int valueLength = strlen(string);

	int i = 0, index = 0;
	while ( i < valueLength)
	{
		index = charToIndex(string[i]) - 1; // gives a=0, A=0, b=1, B=1, ...
		if (curr->children[ index ] != NULL)
		{
			curr = curr->children[index];
			i++;
		}
		else
		{
			break;
		}
	}

	while (i < valueLength)
	{
		index = charToIndex(string[i]) - 1; // gives a=0, A=0, b=1, B=1, ...
		curr->children[index] = trieElement_Constructor();
		curr = curr->children[index];
		i++;
	}

	curr->starred = 1;
}