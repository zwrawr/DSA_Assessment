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
#include <stdbool.h>

#include "../Libarys/Trie.h"
#include "../Libarys/Stack.h"
#include "../Libarys/Queue.h"
#include "../Libarys/List.h"

/// ====
/// Defines
/// ====
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
int recursivePrint(TrieElement *curr, Stack *charStack, int depth);
int charToIndex(char c);
char indexToChar(int index);
char *indicesToString(int *array, int length);
int insert(Trie *trie, char *string);
TrieElement *findElement(Trie *trie, char *item);

int findWordsAtDepthBelow(TrieElement *curr, int depth, char **results, int bufferSize, Stack *wordStack, int *foundOnLayer);



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
    
    bool starred; // if 1 this node represents a compleate word. All leaf elements are starred elements.
};

/// ====
/// Constructors and Destructor
/// ====

Trie *trie_Constructor()
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
    
    trieElement->starred = false;
    
    // Don't create the child elements till we need them
    trieElement->children = NULL;
    ///trieElement->children = malloc(ALPHABETSIZE * sizeof(TrieElement *));
    
    ///if (trieElement->children == NULL)
    ///{
    ///    printf("[ERR!] \tUnable to assign memory for trieElement->children\n");
    ///    return NULL;
    ///}
    
    ///for (int i = 0; i < ALPHABETSIZE; i++)
    ///{
    ///    trieElement->children[i] = NULL;
    ///}
    
    return trieElement;
}

void trieElement_Deconstructor(TrieElement *trieElement)
{
    if (trieElement == NULL)
    {
        printf("[WARN] \tAttempted to free a NULL trieElement\n");
        return;
    }
    
    // if we have children then deconstruct them
    if (trieElement->children != NULL)
    {
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
    }
    
    free(trieElement);
    return;
}
/// ====
/// Interface Functions
/// ====

// Adds the item(word) to the trie data structure
// Returns 1 if addition was succesful
// Returns 0 if word could not be added
// Returns -1 if params are NULL
int trie_Add(Trie *trie, char *item)
{
    if (trie == NULL || trie->root == NULL || item == NULL)
    {
        return -1; // NULL or broken trie so dont attempt to add to it
    }
    else if ( ( strlen(item) < 1 ) || ( strlen(item) > (MAXWORDLENGTH - 1) ) )
    {
        return 0; // cannot add a word with less than 1 letter or more than MAXWORDLENGTH -1
    }
    
    // insert this element into the trie
    int err = insert(trie, item);
    // TODO :: check that value ^
    
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

// Prints out the words in the trie in alphabetical order
// returns 1 if successful
// returns 0 if no items where printed
// return -1 if trie is null
int trie_Print(Trie *trie)
{
    if (trie == NULL)
    {
        return -1;
    }
    
    TrieElement *curr = trie->root;
    
    // were going to construct the word on a stack,
    // pushing a char every time we go down into a node and
    // poping a char every time we exit a node
    Stack *charStack = stack_Constructor();
    
    // traverse the trie in pre-order and print the node if its starred
    int info = recursivePrint(curr, charStack, 0);
    stack_Deconstructor(charStack);
    
    if (info == 0 )
    {
        // no prints
        return 0;
    }
    else if (info > 0)
    {
        // we printed stuff
        return 1;
    }
    else
    {
        return -1;
    }
}

// Tests to see if a word is in the trie
// Returns 1 if item is in the trie and starred (its considered a word)
// Returns 0 if the item is in the trie but not starred (its a partial word)
// Returns -1 if its not in the trie, trie is NULL, item is NULL, item has no characters in it
int trie_Contains(Trie *trie, char *item)
{
    if (trie == NULL || item == NULL || strlen(item) < 1)
    {
        return -1;
    }
    
    TrieElement *found = findElement(trie, item);
    
    // if we get here then curr is the node in the trie that represents item
    // return value depends on curr is starred (curr is a word or partial word)
    if (found == NULL)
    {
        return -1;
    }
    else if (found->starred == true)
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

// Searches the trie for words prefixed by partial word.
// Returns a value > 0 and < numPredictions if words were found.
// Retuns 0 if no words are found.
// Returns -1 if trie is NULL, item is NULL, result is NULL, item has no characters in it, item isnt in trie.
int trie_searchByPrefix(Trie *trie, char *item, char **results, int numToFind)
{
    // ideally we want to find the results with the minimum extra letters
    // e.g. for input "hel" , we want "help" or "helm" before we want "hello" before we want "helicopter"
    // this means we want to proform level order traversal (Breath first)
    // until we find enough results or hit the bottom of the tree. we visit each layer and see if it has any words.
    
    
    if (trie == NULL || item == NULL || results == NULL || numToFind < 1 || strlen(item) < 1)
    {
        return -1;
    }
    
    if (trie_Contains(trie, item ) == -1)
    {
        //printf("[WARN] item isn't in the trie so its impossible for any word to be prefixed by it.");
        return -1;
    }
    
    // creating a queue of elements to proccess
    Queue *elements = queue_Constructor(sizeof(TrieElement *));
    TrieElement *curr = findElement(trie, item);
    
    // make a stack to keep our word in, and add the partial word.
    Stack *wordStack = stack_Constructor();
    
    // make a list to store the words we find
    List *foundWords = list_Constructor(MAXWORDLENGTH * sizeof(char));
    
    // and the partial word to it
    for (int i = 0; i < (int)strlen(item); i++)
    {
        stack_Push(wordStack, charToIndex(item[i]));
    }
    
    
    // whilst we have still have elemenets to process
    while (curr != NULL)
    {
        for (int i = 0; i < ALPHABETSIZE; i++)
        {
            if (curr->children != NULL && curr->children[i] != NULL)
            {
                if (curr->starred == true)
                {
                    // this is a word so we want to add it to our list
                    int *tmpArray = stack_ToArray(wordStack);
                    char *tmpString = indicesToString(tmpArray, stack_GetHeight(wordStack));
                    
                    // add it to our list of found words
                    list_Add(foundWords, tmpString);
                    
                    free(tmpArray);
                    free(tmpString);
                    
                    // if we have enough values then break the loop
                    if (list_Size(foundWords) >= numToFind)
                    {
                        break;
                    }
                }
            }
            
            queue_Enqueue(elements, &(curr->children[i]));
        }
        
        queue_Dequeue(elements, &curr);
    }
    
    stack_Deconstructor(wordStack);
    queue_Deconstructor(elements);
    
    // move values from list into results
    int found = list_Size(foundWords);
    
    for (int i = 0; i < found; i++)
    {
        char *tmp = malloc(MAXWORDLENGTH * sizeof(char));
        list_Read(foundWords, i, tmp);
        
        strcpy_s(results[i], MAXWORDLENGTH, tmp);
        
        free(tmp);
    }
    
    list_Destructor(foundWords);
    return found;
}


/// ====
/// Hidden Functions
/// ====

// Finds an Element that represents item.
// Returns a Non-NULL TrieElement if item is in the trie.
// Returns NULL if item isn't in the trie.
TrieElement *findElement(Trie *trie, char *item)
{
    if (trie == NULL || item == NULL)
    {
        return NULL;
    }
    
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
            if (curr->children != NULL && curr->children[index] != NULL)
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

// Recurively prints the trie
// Returns number of items printed if successful
// Returns -1 if unsuccessful
int recursivePrint(TrieElement *curr, Stack *charStack, int depth)
{
    if (curr == NULL || charStack == NULL || depth < 0)
    {
        return -1;
    }
    
    int printed = 0;
    
    // if this node is starred then it is a compleate word, so print it out
    if (curr->starred == true)
    {
        char *string = indicesToString(stack_ToArray(charStack), stack_GetHeight(charStack));
        printf("> %s\n", string);
        free(string);
        printed++;
    }
    
    // recurse into every existing child node
    for (int i = 0; i < ALPHABETSIZE; i++)
    {
        if (curr->children != NULL && curr->children[i] != NULL)
        {
            // remember to add the letter of the node were going to onto the stack
            stack_Push(charStack, i);
            printed += recursivePrint(curr->children[i], charStack, depth + 1); // TODO:// this can return -1 and mess up our value does it?
            // and then remove it
            stack_Pop_nv(charStack);
        }
    }
    
    return printed;
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
// Returns '#' if index is out side range
char indexToChar(int index)
{
    if (index < 0 || index > ALPHABETSIZE)
    {
        return '#';
    }
    else if ( index >= 0 && index < 26)
    {
        // letters
        return 97 + index;
    }
    else if (index >= 26 && index < 36)
    {
        //numbers
        return 48 + index - 26;
    }
    
    // if we got here then alphabet size is wrong
    printf("[WARN] \tAn index value [%d] within the correct range(0 to ALPHABETSIZE) could not be mapped back to a char \n", index);
    return ' ';
}

// Maps an array of indices back to a string
// Returns a string representing the mapped version of the array
// Returns NULL if input array was NULL or has langth < 1
char *indicesToString(int *array, int length)
{
    if (array == NULL || length < 1)
    {
        return NULL;
    }
    
    char *word = malloc((length + 1) * sizeof(char));
    int k;
    
    for (k = 0; k < length; k++)
    {
        word[k] = indexToChar(array[k]);
    }
    
    word[k] = '\0'; // remember the null terminator char
    return word;
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
        else if (curr->children != NULL && curr->children[index] != NULL)
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
        index = charToIndex(string[i]);
        
        if (index == -1)
        {
            // if charToIndex return -1 then we dont care about this char so skip it e.g. fullstops
            i++;
        }
        else
        {
            // this element might not have it children set up yet so we need to check that
            if (curr->children == NULL)
            {
                curr->children = malloc(ALPHABETSIZE * sizeof(TrieElement *));
                
                if (curr->children == NULL)
                {
                    printf("[ERR!] \tUnable to assign memory for trieElement->children\n");
                    return 0;
                }
                
                for (int i = 0; i < ALPHABETSIZE; i++)
                {
                    curr->children[i] = NULL;
                }
            }
            
            curr->children[index] = trieElement_Constructor();
            curr->children[index]->parent = curr;
            curr = curr->children[index];
            i++;
        }
    }
    
    curr->starred = true;
    
    return 1;
}