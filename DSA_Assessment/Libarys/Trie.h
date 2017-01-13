#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED


/// ====
/// Defines
/// ====


/// ====
/// Type Definitions
/// ====
typedef struct Trie Trie;


/// ====
/// Constructors and Destructor
/// ====
Trie *trie_Constructor(void);
void trie_Deconstructor(Trie *trie);


/// ====
/// Functions
/// ====

// adds the item(word) to the trie data structure
// returns 1 if addition was succesful
int trie_Add(Trie* trie, char* item);

// adds the items(words) to the trie data structure
// returns 1 if additions were succesful
int trie_AddMultiple(Trie* trie, char** items);

// prints out the words in the trie in alphabetical order
void trie_Print(Trie* trie);

// tests to see if a word is in the trie
// Returns 1 if item is in the trie
int trie_Contains(Trie* trie, char* item);

#endif // TRIE_H_INCLUDED

