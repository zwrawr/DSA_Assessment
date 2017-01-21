// =====================================================
// <summary>
//  This file creates and manages a generic list data structure.
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================

// =====================================================
// This file was created when following the University of York,
// Dept. of Electronics Data Structures and Algorithms Lab Scripts.
// http://www.elec.york.ac.uk/internal_web/meng/yr2/modules/DSA/DSA/Labs/Scripts/Lab4-LinkedLists.pdf
// Some of the code below may be from the source above.
// =====================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Libarys/List.h"

/// ====
/// Defines
/// ====

/// ====
/// TypeDefs
/// ====
typedef struct ListNode ListNode;


/// ====
/// Prototypes
/// ====
ListNode *listNode_Constructor(size_t itemSize, void *data);
void listNode_Destructor(ListNode *);

ListNode *getNode(List *list, int index);

/// ====
/// Structures
/// ====
struct ListNode
{
    void *data;
    ListNode *next;
    ListNode *prev;
};
struct List
{
    int size;
    size_t itemSize;
    ListNode *head;
    ListNode *tail;
};


/// ====
/// Constructors and Destructor
/// ====
struct List *list_Constructor(size_t itemSize)
{
    struct List *list;
    
    list = malloc(sizeof(List));
    
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    
    list->itemSize = itemSize;
    
    return list;
}

void list_Destructor(List *list)
{
    ListNode *currentRecord;
    ListNode *nextRecord = list->head;
    
    while (nextRecord != NULL)
    {
        currentRecord = nextRecord;
        nextRecord = currentRecord->next;
        
        listNode_Destructor(currentRecord);
    }
    
    free(list);
}

ListNode *listNode_Constructor(size_t size, void *data)
{
    ListNode *node;
    
    node = malloc(sizeof(ListNode));
    memcpy(node->data, data, size);
    node->next = NULL;
    node->prev = NULL;
    
    return node;
}

void listNode_Destructor(ListNode *node)
{
    free(node->data);
    free(node);
}


/// ====
/// Functions
/// ====

// Reads the value form a item in the list
// Returns 1 if succesful
// Returns -1 if list is NULL
int list_Add(List *list, void *data)
{
    if (list == NULL)
    {
        return -1;
    }
    
    ListNode *node = listNode_Constructor(list->itemSize, data);
    
    if (list->size == 0) // create new list
    {
        list->head = node;
        list->tail = node;
        node->next = NULL;
        node->prev = NULL;
    }
    else // add to tail
    {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
        node->next = NULL;
    }
    
    list->size++;
    
    return 1;
}

// Reads the value form a item in the list
// Returns 1 if succesful
// Returns 0 if unsuccessful
// Returns -1 if list is NULL
int list_Read( List *list, int index, void *data)
{
    if (list == NULL)
    {
        return -1;
    }
    
    if ((index <= 0) || (index > list->size))
    {
        printf("\nWARNING :attempted to read from an index outside the bounds of an list\n");
        return 0;
    }
    
    ListNode *node = list->head;
    
    int i;
    
    for (i = 0; i < index; i++)
    {
        node = node->next;
    }
    
    memcpy(data, node->data, list->itemSize);
    
    return 1;
}

// Removes an item from a list
// Returns 1 if succesful
// Returns 0 if unsuccessful
// Returns -1 if list is NULL
int list_Remove(List *list, int index)
{
    if (list == NULL)
    {
        return -1;
    }
    
    if ((index <= 0) || (index > list->size))
    {
        printf("\nWARNING :attempted to remove a node from an index outside the bounds of an list\n");
        return 0;
    }
    
    ListNode *node = getNode(list, index);
    
    if (node == NULL)
    {
        printf("\nWARNING :couldn't get node \n");
        return 0;
    }
    
    node->prev->next = node->next;
    node->next->prev = node->prev;
    
    if (node->next == NULL)
    {
        list->tail = node->prev;
    }
    
    if (node->prev == NULL)
    {
        list->head = node->next;
    }
    
    listNode_Destructor(node);
    list->size--;
    return 1;
}

// Gets the number of items in a list
// Returns (>=0) the number of items in the list
// Returns -1 if list is NULL
int list_Size(List *list)
{
    if (list == NULL)
    {
        return -1;
    }
    
    return list->size;
}

// Checks weather a list isempty
// Return 0 if the list is not empty
// Returns 1 if the array list is empty
// Returns -1 if list is null
int list_isEmpty(List *list)
{
    if (list == NULL)
    {
        return -1;
    }
    
    if (list->size > 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


/// ====
/// helpers
/// ====

// gets a node at a specified index
ListNode *getNode(List *list, int index)
{

    if ((index <= 0) || (index > list->size))
    {
        printf("\nWARNING :attempted to get a node from an index outside the bounds of an list\n");
        return NULL;
    }
    
    ListNode *node = list->head;
    
    int i;
    
    for (i = 0; i < index; i++)
    {
        printf("looking at node : ");
        node = node->next;
    }
    
    printf("\n");
    return node;
}
