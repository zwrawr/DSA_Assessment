// =====================================================
// <summary>
//  This file creates and manages a trie data structure for the storage
//  and management of words. It allows for fast look ups and fast
//  searches by prefix.
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Libarys/Stack.h"
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
TrieElement *trieElement_Constructor();
void trieElement_Deconstructor(TrieElement *trieElement);
void recursivePrint(TrieElement *curr, char *string, int depth);
int charToIndex(char c);
char indexToChar(int index);
int insert(Trie *trie, char *string);
TrieElement *findElement(Trie *trie, char *item);

int findWordsAtDepth(TrieElement *start, int depth, char *partialWord, char **words, int maxWords, int *foundWords);
int recursive_findWordsAtDepth(TrieElement *curr, Stack *word, int currDepth, int depth,
                               char **words, int *foundWords, int maxWords);


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
    TrieElement **children;//ALPHABETSIZE number of pointers one for each letter of the alphabet and one for each number
    TrieElement *parent;
    
    //TODO:: if C99 is allowed then use bools for the memory reduction
    short starred; // if 1 this node represents a compleate word. All leaf elements are starred elements.
};

/// ====
/// Constructors and Destructor
/// ====

Trie *trie_Constructor(void)
{
    Trie *trie;
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

void trie_Deconstructor(Trie *trie)
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

TrieElement *trieElement_Constructor()
{
    TrieElement *trieElement;
    
    trieElement = malloc(sizeof(TrieElement));
    
    if (trieElement == NULL)
    {
        printf("[ERR!] \tUnable to assign memory for trieElement\n");
        return NULL;
    }
    
    trieElement->parent = NULL;
    
    trieElement->starred = 0;
    
    trieElement->children = malloc(ALPHABETSIZE * sizeof(TrieElement *));
    
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

void trieElement_Deconstructor(TrieElement *trieElement)
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
int trie_Add(Trie *trie, char *item)
{
    if (trie == NULL || trie->root == NULL )
    {
        printf("[WARN] \tAttempted to add a word to a NULL or broken trie\n");
        return 0; // NULL or broken trie so dont attempt to add to it
    }
    else if ( ( strlen(item) < 1 ) || ( strlen(item) > (MAXWORDLENGTH - 1) ) )
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
int trie_AddMultiple(Trie *trie, char **items, int num)
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
void trie_Print(Trie *trie)
{
    //TODO:: validty checks
    //TODO:: use a stack to deal with the string.
    // traverse the trie in pre-order and print the node if its starred
    
    TrieElement *curr = trie->root;
    char string[MAXWORDLENGTH];
    int depth = 0;
    
    recursivePrint(curr, string, depth);
    
}

// Tests to see if a word is in the trie
// Returns 1 if item is in the trie and starred (its considered a word)
// Returns 0 if the item is in the trie but not starred (its a partial word)
// Returns -1 if its not in the trie
int trie_Contains(Trie *trie, char *item)
{
    //TODO:: VALIDITY CHECKS
    
    TrieElement *found = findElement(trie, item);
    
    // if we get here then curr is the node in the trie that represents item
    // return value depends on curr is starred (curr is a word or partial word)
    if (found == NULL)
    {
        return -1;
    }
    else if (found->starred == 1)
    {
        // if the found node was starred then it was a compleate word.
        return 1;
    }
    else
    {
        // wasn't a compleate word.
        return 0;
    }
}

// searches the trie for words prefixed by partial word.
// Returns a value > 0 and < numPredictions if words were found.
// Returns -1 if no words where found.
int trie_searchPrefixedBy(Trie *trie, char *item, char **result, int num)
{

    int info = trie_Contains(trie, item);
    
    if (info == -1)
    {
        printf("[WARN] item isn't in the trie so its impossible for any word to be prefixed by it.");
        return -1;
    }
    
    // ideally we want to find the results with the minimum extra letters
    // e.g. for input "hel" , we want "help" or "helm" before we want "hello" before we want "helicopter"
    // this means we want to proform level order traversal (Breath first)
    
    // until we find enough results or hit the bottom of the tree. we visit each layer and see if it has any words.
    
    int depth = 0, found = 0, isMoreLayers = 1;
    TrieElement *curr = findElement(trie, item);
    
    
    // Until we hit the bottom or get enough results
    while ((found < num) && (isMoreLayers == 1))
    {
        // find all nodes at the current depth and see if there words.
        // do this by running a depth limited search
        
        int bufferSize = (num - found);
        char **buffer = malloc(bufferSize * sizeof(char *));
        
        for (int k = 0; k < bufferSize; k++)
        {
            buffer[k] = malloc(MAXWORDLENGTH * sizeof(char));
        }
        
        int info = findWordsAtDepth(curr, depth, item, buffer, bufferSize, &found);
        
        isMoreLayers = (info == 2 || info == 0) ? 1 : 0;
        
        //move words from buffer into results
        for (int i = 0; i < found; i++)
        {
            strcpy_s(result[i], 64, buffer[i]);
        }
        
        
        for (int j = 0; j < bufferSize; j++)
        {
            free(buffer[j]);
        }
        
        free(buffer);
        depth++;
    }
    
    return found;
}

// Proforms a depth first search with limited depth starting a node curr
// Returns 2 if words were found and there are children on layer depth
// Returns 1 if words were found but there are no more children
// Returns 0 if no words were found but there are children
// Returns -1 if now words were found and there are no child nodes at this depth (bottom of tree).
int findWordsAtDepth(TrieElement *start, int depth, char *partialWord, char **words, int maxWords, int *foundWords)
{
    if (start == NULL || start->children == NULL || maxWords == 0)
    {
        // either we have been passed null by accident or we've hit the bottom of the tree.
        return -1;
    }
    
    TrieElement *curr = start;
    
    Stack *word = stack_Constructor();
    
    // Add the partial word to the stack
    int pwLength = strlen(partialWord);
    
    for (int i = 0; i < pwLength; i++)
    {
        int index = charToIndex(partialWord[i]);
        
        if (index != -1)
        {
            stack_Push(word, index);
        }
    }
    
    int children = recursive_findWordsAtDepth(curr, word, 0, depth, words, foundWords, maxWords);
    
    stack_Deconstructor(word);
    
    if (children > 0 && foundWords == 0)
    {
        return 0;
    }
    
    if (children == 0 && foundWords > 0)
    {
        return 1;
    }
    
    if (children > 0 && foundWords > 0)
    {
        return 2;
    }
    
    return -1;
}


// Recurively finds starred children at a depth from curr
// Returns the number of children found on the layer indicated by depth
//
int recursive_findWordsAtDepth(TrieElement *curr, Stack *word,
                               int currDepth, int depth,
                               char **words, int *foundWords, int maxWords )
{

    int children = 0;
    
    // we have to check every child node.
    for (int i = 0; i < ALPHABETSIZE; i++)
    {
        if (curr->children[i] != NULL)
        {
            curr = curr->children[i];
            
            if (currDepth == depth)
            {
                // we want to keep track of children so we can see if there a layer below this.
                if (curr->children != NULL)
                {
                    children++;
                }
            }
            
            stack_Push(word, i);
            
            if (currDepth == depth && curr->starred == 1)
            {
                // were at a node thats starred and at the right depth.
                
                // turn stack into array
                int height = stack_GetHeight(word);
                int *indexs = stack_ToArray(word);
                
                // map array from indexs to real chars and add the to one of the words were returning
                int k;
                
                for (k = 0; k < height; k++)
                {
                    words[*foundWords][k] = indexToChar(indexs[k]);
                }
                
                words[*foundWords][k] = '\0'; // remember the null terminator char
                
                free(indexs);
                
                (*foundWords)++;
                
                // we have the amount of words we need so get outta here
                if (*foundWords >= maxWords)
                {
                    return children;
                }
                
            }
            else
            {
                // not deep enough yet so we need to go deeper
                children = recursive_findWordsAtDepth(curr, word, currDepth, depth, words, foundWords, maxWords);
                
                if (*foundWords >= maxWords)
                {
                    return children;
                }
            }
            
            curr = curr->parent;
            stack_Pop_nv(word);
        }
    }
    
    return children;
}



/// ====
/// Hidden Functions
/// ====

// Finds an Element that represents item.
// Returns a Non-NULL TrieElement if item is in the trie.
// Returns NULL if item isn't in the trie.
TrieElement *findElement(Trie *trie, char *item)
{
    int len = (int)strlen(item);
    TrieElement *curr = trie->root;
    
    // for each letter in the string
    for (int i = 0; i < len; i++)
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
                return NULL;
            }
        }
    }
    
    return curr;
}

// recurively prints the trie
void recursivePrint(TrieElement *curr, char *string, int depth)
{
    //TODO:: validity checks
    
    if (curr->starred == 1)
    {
        printf("> %s\n", string);
    }
    
    for (int i = 0; i < 26; i++)
    {
        if (curr->children[i] != NULL)
        {
            string[depth] = indexToChar(i);
            string[depth + 1] = '\0';
            
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
        printf("[WARN] \tA char [%c] was mapped out side of the permitted range [%d]\n", c, index);
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
    else if ( index >= 0 && index < 26)
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
int insert(Trie *trie, char *string)
{
    if (trie == NULL || trie->root == NULL || string == NULL || strlen(string) < 1)
    {
        printf("[WARN] \tAttempted to insert a word to a NULL or broken trie\n");
        return 0; // NULL or broken trie or NULL or empty string so dont attempt to add to it
    }
    
    TrieElement *curr = trie->root;
    
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