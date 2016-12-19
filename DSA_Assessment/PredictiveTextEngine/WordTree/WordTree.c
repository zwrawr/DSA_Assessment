#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// ====
/// Defines
/// ====
#define WORDSFILE "Data/words.txt"
#define WORDTREESIZE 64
#define MAXWORDLENGTH 128
/// ====
/// TypeDefs
/// ====
typedef struct WordTree WordTree;
typedef struct TreeElement TreeElement;


/// ====
/// Prototypes
/// ====
FILE* getWordsFile();
TreeElement* treeElement_Constructor(char* word);
void treeElement_Deconstructor(TreeElement* treeElement);
int getNumberOfLinesInFile(FILE* file);

/// ====
/// Structures
/// ====
struct WordTree
{
	int size; //number of words currently in this word tree
	TreeElement* root; //the root element of the tree
};

struct TreeElement
{
	char word[MAXWORDLENGTH];
	TreeElement* left;
	TreeElement* right;
};


/// ====
/// Constructors and Destructor
/// ====
WordTree *wordTree_Constructor(void)
{
	WordTree *wordTree;
	wordTree = malloc(sizeof(WordTree));

	FILE* file = getWordsFile();
	char** words =getWordArray(file);

	//sort the array first as it is quicker than do lots of sorted inserts into the tree.
	sortWordArray(words);

	// the root node in the tree is a space
	wordTree->root = treeElement_Constructor(" ");
	// add the words to the word tree


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

TreeElement* treeElement_Constructor(char* word)
{
	TreeElement* treeElement;
	treeElement = malloc(sizeof(TreeElement));

	treeElement->left = NULL;
	treeElement->right = NULL;

	strcpy_s(treeElement->word, MAXWORDLENGTH, word);

	return treeElement;

}

void treeElement_Deconstructor(TreeElement* treeElement)
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
FILE* getWordsFile() 
{
	FILE* file;
	errno_t err = fopen_s(&file, WORDSFILE, "r");

	if (err == 0)
	{
		printf("The file '%s' was opened\n",WORDSFILE);
	}
	else
	{
		printf("ERROR :: \t The file '%s' was not be opened\n Exiting",WORDSFILE);
		exit(1);
	}

	return file;
}

int getNumberOfLinesInFile(FILE* file)
{
	int count = 0;
	char buf[64];
	while (fgets(buf, sizeof(buf) ,file) != NULL)
	{
		count++;
	}

	printf("The file contains %d lines/words",count);

	return count;
}

char** getWordsArray(FILE* file)
{
	int lines = getNumberOfLinesInFile(file);
	char** words = malloc(lines);

	for (int i = 0; i < lines; i++)
	{
		char* buf = malloc(sizeof(char) * 64);
		if (fgets(buf, 64, file) != NULL)
		{
			words[i] = buf;
		}
		else
		{
			words[i] = NULL;
		}
	}

	return words;
}

void sortWordArray(char** words)
{
	//TODO: impliment quick sort
	//TODO: impliment mergesort or selection sort
	//TODO: make merge sort use quicksort if theres less than 256 items to be sorted
	//TODO: benchmark the above
	//TODO: multithread?

	// This is buble sort and should be nuked and replaced with a better sort at some point

}