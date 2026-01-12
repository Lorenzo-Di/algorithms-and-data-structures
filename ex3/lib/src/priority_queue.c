#define INITIAL_CAPACITY 1024

#include "priority_queue.h"
#include "hash_table.h"
#include <stdlib.h>

struct priorityQueue {
    void **heap;
    size_t capacity;
    size_t size;
    HashTable *table;
    int (*compar)(const void*, const void*);
};

PriorityQueue* priority_queue_create(int (*compar)(const void*,const void*), unsigned long (*hash_func)(const void*)) {
    if(!(compar && hash_func)) { return NULL; }
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    if(!pq) { return NULL; }
    pq->capacity = INITIAL_CAPACITY;
    if(!(pq->heap = malloc(sizeof(void*) * pq->capacity))) {
        free(pq);
        return NULL;
    }
    if(!(pq->table = hash_table_create(compar, hash_func))) {
        free(pq->heap);
        free(pq);
        return NULL;
    }
    pq->size = 0;
    pq->compar = compar;
    
    return pq;
}

int priority_queue_push(PriorityQueue *pq, void *element) {
    if(!(pq && element)) { return -1; }
    if(priority_queue_contains(pq, element) == 1) { return 0;}
    if(pq->size == pq->capacity) {
        void **new_heap;
        if(!(new_heap = realloc(pq->heap, pq->capacity * 2 *sizeof(void *)))) { return 0; }
        pq->heap = new_heap;
        pq->capacity *= 2;
    }
    size_t *index = malloc(sizeof(size_t)); //could be improved?
    if(!index) { return 0; }
    *index = pq->size;
    hash_table_put(pq->table, element, index);
    pq->heap[*index] = element;
    pq->size++;

    move_up(pq, *index);
    return 1;
}
