#ifndef WORDTREE_H_INCLUDED
#define WORDTREE_H_INCLUDED


/// ====
/// Defines
/// ====


/// ====
/// Type Definitions
/// ====
typedef struct WordTree WordTree;


/// ====
/// Constructors and Destructor
/// ====
WordTree *wordTree_Constructor(void);
void wordTree_Deconstructor(WordTree *wordTree);


/// ====
/// Functions
/// ====
char* wordTree_getWordBeginningWith(WordTree* wordTree, char* partialWord);




#endif // WORDTREE_H_INCLUDED
