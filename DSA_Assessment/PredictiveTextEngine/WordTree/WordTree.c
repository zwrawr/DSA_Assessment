#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// ====
/// Defines
/// ====
#define WORDSFILE "Data/words.txt"// "Data/words.txt" or "Data/100words.txt"
#define WORDTREESIZE 64
#define MAXWORDLENGTH 128
/// ====
/// Type Definitions
/// ====
typedef struct WordTree WordTree;
typedef struct TreeElement TreeElement;


/// ====
/// Prototypes
/// ====
FILE *getWordsFile();
char **getWordsArray(FILE *file, int *lines);
TreeElement *treeElement_Constructor(char *word);
void treeElement_Deconstructor(TreeElement *treeElement);
int getNumberOfLinesInFile(FILE *file);
void sortWordArray(char **words, int length);
void addSortedWordsToTree(WordTree *wordTree, char **words, int length);
TreeElement *addSortedWords(WordTree *wordTree, char **words, int start, int end);
void freeWordsArray(char **words, int length);

/// ====
/// Structures
/// ====
struct WordTree
{
    int size; //number of words currently in this word tree
    TreeElement *root; //the root element of the tree
};

// Should this be a binary tree or should it have a child for each possible letter?
struct TreeElement
{
    char word[MAXWORDLENGTH];
    TreeElement *left;
    TreeElement *right;
};


/// ====
/// Constructors and Destructor
/// ====
WordTree *wordTree_Constructor(void)
{
    WordTree *wordTree;
    wordTree = malloc(sizeof(WordTree));
    
    FILE *file = getWordsFile();
    int lines = 0;
    char **words = getWordsArray(file, &lines);
    
    //sort the array first as it is quicker than do lots of sorted inserts into the tree.
    sortWordArray(words, lines);
    
    // add the words to the word tree
    addSortedWordsToTree(wordTree, words, lines);
    
    // remember to free the temp array we created
    freeWordsArray(words, lines);
    
    return wordTree;
}

void wordTree_Deconstructor(WordTree *wordTree)
{
    if (wordTree == NULL)
    {
        printf("WARNING :: \t Attempted to Deconstruct a NULL WordTree");
        return;
    }
    
    treeElement_Deconstructor(wordTree->root);
    free(wordTree);
}

TreeElement *treeElement_Constructor(char *word)
{
    TreeElement *treeElement;
    treeElement = malloc(sizeof(TreeElement));
    
    treeElement->left = NULL;
    treeElement->right = NULL;
    
    strcpy_s(treeElement->word, MAXWORDLENGTH, word);
    
    return treeElement;
    
}

void treeElement_Deconstructor(TreeElement *treeElement)
{
    if (treeElement == NULL)
    {
        printf("WARNING :: \t Attempted to Deconstruct a NULL TreeElement");
        return;
    }
    
    if (treeElement->left != NULL)
    {
        treeElement_Deconstructor(treeElement->left);
    }
    
    if (treeElement->right != NULL)
    {
        treeElement_Deconstructor(treeElement->right);
    }
    
    free(treeElement);
}

/// ====
/// Interface Functions
/// ====


/// ====
/// Hidden Functions
/// ====
FILE *getWordsFile()
{
    FILE *file;
    errno_t err = fopen_s(&file, WORDSFILE, "r");
    
    if (err == 0)
    {
        printf("[DONE] Opened file '%s' \n", WORDSFILE);
    }
    else
    {
        printf("[ERR!]\t Unable to open file '%s' \n[EXIT] Exiting\n", WORDSFILE);
        exit(1);
    }
    
    return file;
}

int getNumberOfLinesInFile(FILE *file)
{
    printf("[    ] Counting lines in file");
    //make sure were at the begging of the file
    fseek(file, 0, SEEK_SET);
    
    int count = 0;
    char buf[64];
    
    while (fgets(buf, sizeof(buf) , file) != NULL)
    {
        count++;
        printf("\r[....] Counted %d lines in file", count);
    }
    
    printf("\r[DONE]\n");
    
    return count;
}

char **getWordsArray(FILE *file, int *lines)
{

    *lines = getNumberOfLinesInFile(file);
    char **words = malloc(*lines * sizeof(char *));
    
    //make sure were at the begging of the file
    fseek(file, 0, SEEK_SET);
    
    printf("[    ] Getting Words from file");
    
    for (int i = 0; i < *lines; i++)
    {
        words[i] = malloc(sizeof(char) * 64);
        
        if (fgets(words[i], 64, file) != NULL)
        {
            // this removes the trailing \n from a word
            words[i][strcspn(words[i], "\n")] = 0;
            printf("\r[....]Reading word 0-%d from file : %s \t\t\t\t", i, words[i]);
        }
        else
        {
            printf("\n[WARN]\t Unable to read line %d form file\t\t\n", i);
        }
    }
    
    printf("\r[DONE] Got Words from file \t\t\t\t\n");
    return words;
}

void sortWordArray(char **words, int length)
{
    //TODO: implement quick sort
    //TODO: implement merge sort or selection sort
    //TODO: make merge sort use quick sort if theres less than 256 items to be sorted
    //TODO: benchmark the above
    //TODO: multi thread?
    
    // This is bubble sort and should be nuked and replaced with a better sort at some point
    
    printf("[    ] Sorting Words");
    int swaps;
    
    for (int i = 0; i < length; i++)
    {
        swaps = 0;
        
        for (int j = 0; j < (length - i - 1); j++)
        {
            if (strcmp(words[j], words[j + 1]))
            {
                swaps++;
                char *tmp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = tmp;
            }
        }
        
        printf("\r[....] Sorting Words, %d swaps\t\t", swaps);
        
        if (swaps == 0)
        {
            break;
        }
    }
    
    printf("\r[DONE] Sorted Words\t\t\t\t\n");
    
}

void addSortedWordsToTree(WordTree *wordTree, char **words, int length)
{
    printf("[    ] Adding words to tree\r");
    wordTree->root = addSortedWords(wordTree, words, 0, length - 1);
    printf("\r[DONE] Added words to tree\t\t\t\t\n");
}

TreeElement *addSortedWords(WordTree *wordTree, char **words, int start, int end)
{

    // we want to add the center node as a new element and the continue recursively for both sides.
    
    /*  e.g.
    *   if start == 0 and end == 99
    *   we create a new tree element with words[0 + (99 - 0)/2] (words[50])
    *   then we recursively find the left and right
    *   left has start == 0 and end = 49
    *   right has start == 51 and end == 99
    */
    
    /*  e.g.
    *   if start == 51 and end == 99
    *   we create a new tree element with words[51 + (99 - 51)/2] (words[75])
    *   then we recursively find the left and right
    *   left has start == 51 and end = 74
    *   right has start == 76 and end == 99
    */
    
    /*  e.g.
    *   if start == 0 and end == 3
    *   we create a new tree element with words[0 + (3 - 0)/2] (words[1])
    *   then we recursively find the left and right
    *   left has start == 0 and end = 0
    *   right has start == 2 and end == 2
    */
    
    // we only have a single value left
    if (end == start)
    {
        printf("\r[....] Added word 0-%d %s to tree \t\t\t\t", start, words[start]);
        TreeElement *treeElement = treeElement_Constructor(words[start]);
        wordTree->size++;
        return treeElement;
    }
    
    // we only have two values left so we cannot make a midpoint
    if (end == start + 1)
    {
        printf("\r[....] Added words 0-%d %s to tree \t\t\t\t", start, words[start]);
        TreeElement *treeElement = treeElement_Constructor(words[end]);
        wordTree->size++;
        
        treeElement->left = treeElement_Constructor(words[start]);
        wordTree->size++;
        
        return treeElement;
    }
    
    
    int midpoint = start + (end - start) / 2;
    
    printf("\r[....] Added words 0-%d %s to tree \t\t\t\t", midpoint, words[midpoint]);
    TreeElement *treeElement = treeElement_Constructor(words[midpoint]);
    wordTree->size++;
    
    //left half
    treeElement->left = addSortedWords(wordTree, words, start, midpoint - 1);
    //right half
    treeElement->right = addSortedWords(wordTree, words, midpoint + 1, end);
    
    return treeElement;
}

void freeWordsArray(char **words, int length)
{
    printf("[    ] Freeing temporary array");
    
    for (int i = 0; i < length; i++)
    {
        free(words[i]);
        printf("\r[....] Freeing temporary array, word %d of %d", i, length);
    }
    
    free(words);
    
    printf("\r[DONE] Freed temporary array\t\t\t\t");
}