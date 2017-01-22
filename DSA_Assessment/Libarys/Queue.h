// =====================================================
// <summary>
//  This file provides a public interface for the file
//  "Queue.c". This is a generic queue implimentation,
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================


#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

/// ====
/// TypeDefs
/// ====
typedef struct Queue Queue;


/// ====
/// Constructors and Destructor
/// ====

Queue *queue_Constructor(size_t itemSize);
void queue_Deconstructor(Queue *queue);


/// ====
/// Functions
/// ====

// test to see weather the queue is empty
// Returns 1 if queue is empty
// Returns 0 if queue isnt empty
// Returns -1 if queue is NULL
int queue_isEmpty(Queue *queue);

// Add an item to the queue
// Returns 1 if enqueue was successful
// Returns -1 if queue is null
int queue_Enqueue(Queue *queue, void *data);

// Remove an item from the queue
// Returns 1 if dequeue was successful
// Returns 0 if it was unsuccessful
// Returns -1 if queue is null
int queue_Dequeue(Queue *queue, void *dequeuedvalue);

// Peek at a value in the queue
// Returns 1 if peek was successful
// Returns 0 if it was unsuccessful
// Returns -1 if queue is null
int queue_Peek(Queue *queue, int index, void *peeked);



#endif // QUEUE_H_INCLUDED