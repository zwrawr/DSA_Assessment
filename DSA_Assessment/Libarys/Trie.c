#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// ====
/// Defines
/// ====
#define MAXWORDLENGTH 64
#define ALPHABETSIZE 36

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
	TrieElement** children;//ALPHABETSIZE number of pointers one for each letter of the alphabet and one for each number
	TrieElement* parent;

	//TODO:: if C99 is allowed then use bools for the memory reduction
	short starred; // if 1 this node represents a compleate word. All leaf elements are starred elements. 
};

/// ====
/// Constructors and Destructor
/// ====

Trie* trie_Constructor(void)
{
	Trie* trie;
	trie = malloc(sizeof(Trie));

	if (trie == NULL)
	{
		printf("[ERR!] \tUnable to assign memory for trie\n");
		return NULL;
	}

	trie->root = trieElement_Constructor();
	trie->root->parent = trie->root; // the first element in the trie is it's own parent
	trie->size = 1;

	return trie;
}

void trie_Deconstructor(Trie* trie)
{
	if (trie == NULL)
	{
		printf("[WARN] \tAttempted to free a NULL trie\n");
		return; // cannot free a NULL trie
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
	if (trieElement == NULL)
	{
		printf("[ERR!] \tUnable to assign memory for trieElement\n");
		return NULL;
	}

	trieElement->parent = NULL;

	trieElement->starred = 0;

	trieElement->children = malloc(ALPHABETSIZE *sizeof(TrieElement*));
	if (trieElement->children == NULL)
	{
		printf("[ERR!] \tUnable to assign memory for trieElement->children\n");
		return NULL;
	}

	for (int i = 0; i < ALPHABETSIZE; i++)
	{
		trieElement->children[i] = NULL;
	}

	return trieElement;
}

void trieElement_Deconstructor(TrieElement* trieElement)
{
	if (trieElement == NULL)
	{
		printf("[WARN] \tAttempted to free a NULL trieElement\n");
		return;
	}

	// deconstruct the children
	for (int i = 0; i < ALPHABETSIZE; i++)
	{
		if (trieElement->children[i] != NULL)
		{
			trieElement_Deconstructor(trieElement->children[i]);
			//free(trieElement->children[i]);
		}
	}
	free(trieElement->children);
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
		printf("[WARN] \tAttempted to add a word to a NULL or broken trie\n");
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
// Returns 0 if any additions were unsuccesful
int trie_AddMultiple(Trie* trie, char** items, int num)
{
	if (items == NULL || num < 1)
	{
		printf("[WARN] \tAttempted to add items or NULL items to a trie\n");
		return 0;
	}
	if (trie == NULL || trie->root == NULL)
	{
		printf("[WARN] \tAttempted to add multiple words to a NULL or broken trie\n");
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
	//TODO:: validty checks

	// traverse the trie in pre-order and print the node if its starred

	TrieElement* curr = trie->root;
	char string[MAXWORDLENGTH];
	int depth = 0;

	recursivePrint(curr, string, depth);

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
	for(int i = 0; i < len; i++)
	{
		int index = charToIndex(item[i]);

		// if index is -1 then we dont care about this char in the string so we should skip it
		// but if its not -1 then we have to try and walk the string
		if (index != -1)
		{
			// if this element has a child element in the position that matchs the letter in the string
			// then move to that element or return -1 (item isnt in the trie)
			if (curr->children[index] != NULL)
			{
				curr = curr->children[index];
			}
			else
			{
				// we cannot walk the trie any deeper so it cannot contain the string were looking for 
				return -1;
			}
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
	//TODO:: validity checks

	if (curr->starred == 1)
	{
		printf("> %s\n", string);
	}

	for (int i = 0; i < 26; i++)
	{
		if (curr->children[i] != NULL) {
			string[depth] = indexToChar(i);
			string[depth+1] = '\0';

			recursivePrint(curr->children[i], string, depth + 1);
		}
	}
	return;
}

// Maps a Char to an index value
// Returns a number between 0 and ALPHABETSIZE - 1 if successful else returns -1 
int charToIndex(char c)
{
	// This function is linked to ALPHABETSIZE if the result from the function fall out size of 0 to ALPHABETSIZE - 1
	// THINGS WILL BREAK

	int index = -1;

	if (c > 64 && c < 91)
	{
		// uppercase letter
		index = c - 65;
	}
	else if (c > 96 && c < 123)
	{
		// lowercase letter
		index = c - 97;
	}
	else if (c > 47 && c < 58)
	{
		// number
		index = 26 + c - 48;
	}

	if (index >= ALPHABETSIZE || index < -1)
	{
		printf("[WARN] \tA char [%c] was mapped out side of the permitted range [%d]\n",c,index);
		return -1;
	}

	return index ;
}

// Maps an index value back to a char
// Returns ' ' if index is out side range
char indexToChar(int index)
{
	if (index < 0 || index > ALPHABETSIZE)
	{
		return ' ';
	}
	else if ( index >=0 && index <26)
	{
		// letters
		return 97 + index;
	}
	else if (index >= 26 && index < 26)
	{
		//numbers
		return 48 + index;
	}

	// if we got here then alphabet size is wrong
	printf("[WARN] \tAn index value within the correct range(0 to ALPHABETSIZE) could not be mapped back to a char \n");
	return ' ';

}

// Inserts a string into a trie
// Returns 1 if the insertion was successful
// Returns 0 if unsuccessful
int insert(Trie* trie, char* string)
{
	if (trie == NULL || trie->root == NULL || string==NULL || strlen(string) < 1)
	{
		printf("[WARN] \tAttempted to insert a word to a NULL or broken trie\n");
		return 0; // NULL or broken trie or NULL or empty string so dont attempt to add to it
	}

	TrieElement* curr = trie->root;

	int valueLength = (int)strlen(string);

	int i = 0, index = 0;
	while ( i < valueLength)
	{
		index = charToIndex(string[i]);

		// if this char is not alphabeticnumeric skip it else try to walk further
		if (index == -1)
		{
			i++;
		}
		else
		{

			if (curr->children[index] != NULL)
			{
				curr = curr->children[index];
				i++;
			}
			else
			{
				break;
			}
		}
	}

	while (i < valueLength)
	{
		index = charToIndex(string[i]);

		if (index == -1)
		{	
			// if charToIndex return -1 then we dont care about this char so skip it e.g. fullstops
			i++;
		}
		else
		{
			curr->children[index] = trieElement_Constructor();
			curr->children[index]->parent = curr;
			curr = curr->children[index];
			i++;
		}
	}

	curr->starred = 1;

	return 1;
}