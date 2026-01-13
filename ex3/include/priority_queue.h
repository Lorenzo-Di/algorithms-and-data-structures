#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h>

/**
 * @file priority_queue.h
 * @brief Generic priority queue API.
 * 
 * This library implements a priority queue using a ternary heap instead of binary, the
 * heap has the same proprieties as a binary one but instead of 2 children it has 3.
 * Memory ownerhip of the elements stays with the user. The queue stores them but never
 * frees them.
 */

/**
 * @brief Opaque structure representing a Priority Queue
 */
typedef struct priorityQueue PriorityQueue;

/**
 * @brief Create a new priority queue.
 *
 * @param compar Comparison function used to determine equality between elements.
 * The function returns 0 when the two keys are equal, and non‑zero
 * otherwise.
 * @param hash_func Hash function for hash table used as support to esnure less than linear complexity.
 * It must return a 64‑bit hash value and must be consistent: equal keys must produce
 * identical hashes.
 *
 * @return Pointer to the newly allocated priority queue, or NULL on failure.
 */
PriorityQueue* priority_queue_create(int (*compar)(const void*,const void*), unsigned long (*hash_func)(const void*));

/**
 * @brief Insert a value in the heap.
 *
 * Values are not copied; only their pointers are stored.
 *
 * @param pq The Queue.
 * @param element Pointer to the element to insert.
 * 
 * @return 1 on success, -1 invalid arguments, 0 on failure.
 */
int priority_queue_push(PriorityQueue *pq, void *element);

/**
 * @brief Check whether the queue contains the given element.
 *
 * @param pq The Queue.
 * @param element The element to check.
 *
 * @return 1 if the element is present, -1 invalid arguments, 0 if the element is not found.
 */
int priority_queue_contains(const PriorityQueue *pq, const void *element);

/**
 * @brief Retrieve the first element of the queue without removing it.
 * 
 * @param pq The Queue.
 * 
 * @return The pointer to the element, NULL on failure.
 */
void* priority_queue_top(const PriorityQueue *pq);

/**
 * @brief Remove the first element of the queue.
 * 
 * @param pq The Queue.
 */
void priority_queue_pop(PriorityQueue *pq);

/**
 * @brief Remove an element from the queue.
 * 
 * @param pq The Queue.
 * @param element The element to be removed.
 * 
 * @return 1 on success, -1 invalid arguments, 0 if the element is not present
 */
int priority_queue_remove(PriorityQueue *pq, const void *element);

/**
 * @brief Get the number of entries currently stored.
 *
 * @param pq The Queue.
 * 
 * @return Number of stored elements. -1 if the queue is invalid
 *         or if the size exceeds INT_MAX.
 */
int priority_queue_size(const PriorityQueue *pq);

/**
 * @brief Get the number of entries currently stored.
 * 
 * @param pq The Queue.
 * 
 * @return Number of stored elements. 0 if the queue is invalid.
 */
size_t priority_queue_size_size_t(const PriorityQueue *pq);

/**
 * @brief Free the priority queue structure.
 *
 * This frees the queue and the supporting hash table but does **not** free the elements.
 * The user must free them separately if needed.
 *
 * @param pq The Queue.
 */
void priority_queue_free(PriorityQueue *pq);

#endif /* PRIORITY_QUEUE_H */