// =====================================================
// <summary>
//  This file provides a public interface for the file
//  "Trie.c".
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================

#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED


/// ====
/// Defines
/// ====
#define MAXWORDLENGTH 64

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

// Adds the item(word) to the trie data structure
// Returns 1 if addition was succesful
// Returns 0 if unsuccesful
int trie_Add(Trie *trie, char *item);

// adds the items(words) to the trie data structure
// returns 1 if additions were succesful
int trie_AddMultiple(Trie *trie, char **items, int num);

// Prints out the words in the trie in alphabetical order
// returns 1 if successful
// return -1 if unsuccessful
int trie_Print(Trie *trie);

// Tests to see if a word is in the trie
// Returns 1 if item is in the trie and starred (its considered a word)
// Returns 0 if the item is in the trie but not starred (its a partial word)
// Returns -1 if its not in the trie
int trie_Contains(Trie *trie, char *item);

// searches the trie for words prefixed by partial word.
// Returns a value > 0 and < numPredictions if words were found.
// Returns -1 if no words where found.
int trie_searchByPrefix(Trie *trie, char *item, char **result, int num);

#endif // TRIE_H_INCLUDED

