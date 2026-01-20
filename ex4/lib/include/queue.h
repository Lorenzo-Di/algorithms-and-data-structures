#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

/**
 * @file queue.h
 * @brief Interface for a generic queue (FIFO) based on a Linked List.
 */

/**
 * @brief Opaque structure representing the queue.
 * 
 * The user manipulates only the pointer, without accessing internal fields.
 */
typedef struct queue *Queue;

/**
 * @brief Creates a new empty queue.
 * 
 * @return Pointer to the newly allocated queue, or NULL in case of memory allocation failure.
 */
Queue queue_create();

/**
 * @brief Destroys the queue and frees structural memory.
 * 
 * This function does NOT free the data pointed to by void*,
 * but only the nodes of the internal linked list.
 * Memory management of the actual data is the user's responsibility.
 * @param q The queue to destroy.
 */
void queue_free(Queue q);

/**
 * @brief Inserts an element at the end of the queue.
 * 
 * @param q The queue.
 * @param data Generic pointer to the data to insert.
 * @return true if insertion is successful, false if it fails.
 */
bool queue_enqueue(Queue q, void *data);

/**
 * @brief Removes the element at the front of the queue and returns it.
 * 
 * @param q The queue.
 * @param res Pointer to a void pointer where the address of the extracted data will be stored.
 * @return true if an element was extracted, false if the queue was empty or q is NULL.
 */
bool queue_dequeue(Queue q, void **res);

/**
 * @brief Checks if the queue is empty.
 * 
 * @param q The queue.
 * @return true if the queue is empty or NULL, false if it contains elements.
 */
bool queue_is_empty(Queue q);

/**
 * @brief Returns the number of elements currently in the queue.
 *
 * @param q The queue.
 * @return The number of elements.
 */
int queue_size(Queue q);

#endif /* QUEUE_H */