// =====================================================
// <summary>
//  This file creates and manages a generic queue data structure.
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================

// =====================================================
// This file was created when following the University of York,
// Dept. of Electronics Data Structures and Algorithms Lab Scripts.
// http://www.elec.york.ac.uk/internal_web/meng/yr2/modules/DSA/DSA/Labs/Scripts/Lab7-StacksAndQueues.pdf
// Some of the code below may be from the source above.
// =====================================================

//TODO:: Make Generic . . . after making queue generic i've decided not to make the stack generic as that took alot of work.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"


/// ====
/// TypeDefs
/// ====

typedef struct Item Item;


/// ====
/// Defines
/// ====


/// ====
/// Prototypes
/// ====

Item *itemConstructor(size_t size, void *data);
void itemDeconstructor(Item *item);


/// ====
/// Structures
/// ====

struct Queue
{
    int length;
    
    // the size of an item to be stored
    size_t itemSize;
    
    Item *front;
    Item *back;
};

struct Item
{
    void *data;
    Item *next;
    Item *prev;
};


/// ====
/// Constructors and Destructor
/// ====

Queue *queue_Constructor(size_t size)
{
    Queue *queue;
    queue = malloc(sizeof(Queue));
    
    queue->length = 0;
    queue->front = NULL;
    queue->back = NULL;
    
    queue->itemSize = size;
    
    return queue;
}

void queue_Deconstructor(Queue *queue)
{
    Item *curr;
    Item *next = queue->front;
    
    while (next != NULL)
    {
        curr = next;
        next = curr->next;
        itemDeconstructor(curr);
    }
    
    free(queue);
    
}

Item *itemConstructor(size_t size, void *data)
{
    Item *item;
    item = malloc(sizeof(Item));
    
    item->data = malloc(size);
    memcpy(item->data, data, size);
    
    item->next = NULL;
    item->prev = NULL;
    
    return item;
}

void itemDeconstructor(Item *item)
{

    free(item->data);
    free(item);
}


/// ====
/// Public Functions
/// ====

// test to see weather the queue is empty
// Returns 1 if queue is empty
// Returns 0 if queue isnt empty
// Returns -1 if queue is NULL
int queue_isEmpty(Queue *queue)
{
    if (queue == NULL)
    {
        return -1;
    }
    
    if (queue->length == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

// Add an item to the queue
// Returns 1 if enqueue was successful
// Returns -1 if queue is null
int queue_Enqueue(Queue *queue, void *data)
{
    if (queue == NULL)
    {
        return -1;
    }
    
    Item *item = itemConstructor(queue->itemSize, data);
    
    if (queue->length == 0)
    {
        queue->front = item;
        queue->back = item;
        item->next = NULL;
        item->prev = NULL;
    }
    else
    {
        queue->front->prev = item;
        item->next = queue->front;
        item->prev = NULL;
        queue->front = item;
    }
    
    queue->length++;
    
    return 1;
    
}

// Remove an item from the queue
// Returns 1 if dequeue was successful
// Returns 0 if it was unsuccessful
// Returns -1 if queue is null
int queue_Dequeue(Queue *queue, void *data)
{
    if (queue == NULL)
    {
        // this queue hasnt been initialized
        return -1;
    }
    
    if (queue->length == 0)
    {
        // nothing to dequeue
        return 0;
    }
    
    Item *last = queue->back;
    memcpy(data, last->data, queue->itemSize);
    
    if (queue->length == 1)
    {
        // queue will be empty once we dequeue this item
        queue->back = NULL;
        queue->front = NULL;
        
        queue->length = 0;
    }
    else
    {
        last->prev->next = NULL;
        queue->back = last->prev;
        
        queue->length--;
    }
    
    itemDeconstructor(last);
    
    return 1;
}

// Peek at a value in the queue
// Returns 1 if peek was successful
// Returns 0 if it was unsuccessful
// Returns -1 if queue is null
int queue_Peek(Queue *queue, int index, void *peeked)
{
    if (queue == NULL)
    {
        return -1;
    }
    
    if (index < 0 || index >= queue->length)
    {
        return 0;
    }
    
    Item *item = queue->back;
    
    for (int j = 0; j < index; j++)
    {
        item = item->prev;
    }
    
    memcpy(peeked, item->data, queue->itemSize);
    
    return 1;
}

/// ====
/// Helper Functions
/// ====