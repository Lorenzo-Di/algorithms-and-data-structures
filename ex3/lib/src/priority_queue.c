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

static inline size_t father(size_t i) {
    if(i<=3) { return 0; }
    return (i-1)/3;
}

static inline size_t left_child(size_t i) { return 3 * i + 1; }
static inline size_t middle_child(size_t i) { return 3 * i + 2; }
static inline size_t right_child(size_t i) { return 3 * i + 3; }

static inline size_t max_of_four(PriorityQueue *pq, size_t a, size_t b, size_t c, size_t d) {
    size_t index_max = a;
    void *max_elem = pq->heap[a];

    if(b < pq->size) {
        if(pq->compar(max_elem, pq->heap[b]) < 0) { max_elem = pq->heap[b]; index_max = b; }
    }

    if(c < pq->size) {
        if(pq->compar(max_elem, pq->heap[c]) < 0) { max_elem = pq->heap[c]; index_max = c; }
    }

    if(d < pq->size) {
        if(pq->compar(max_elem, pq->heap[d]) < 0) { max_elem = pq->heap[d]; index_max =d; }
    }

    return index_max;
}

static void swap_elements(PriorityQueue *pq, size_t i, size_t j) {
    void *elem_i = pq->heap[i];
    void *elem_j = pq->heap[j];

    pq->heap[i] = elem_j;
    pq->heap[j] = elem_i;

    size_t *idx_i_p = hash_table_get(pq->table, elem_i);
    size_t *idx_j_p = hash_table_get(pq->table, elem_j);

    if(idx_i_p) { *idx_i_p = j; }
    if(idx_j_p) { *idx_j_p = i; }
}

void move_up(PriorityQueue *pq, size_t index) {
    while(index > 0 && pq->compar(pq->heap[index], pq->heap[father(index)]) > 0) {
        swap_elements(pq, index, father(index));
        index = father(index);
    }
}

void resize_pq_down(PriorityQueue *pq) {
    if(pq->capacity > INITIAL_CAPACITY && (pq->size < (pq->capacity / 4))) {
        void **new_heap = realloc(pq->heap, pq->capacity * sizeof(void *) / 2);
        if(new_heap) { pq->heap = new_heap; pq->capacity /= 2; }
    }
}

static void heapify(PriorityQueue *pq, size_t i) {
    size_t max = max_of_four(pq, i, left_child(i), middle_child(i), right_child(i));
    if(max == i) { return; }

    swap_elements(pq, i, max);

    heapify(pq, max);
}

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

int priority_queue_contains(const PriorityQueue *pq, const void *element) {
    if(!(pq && element)) { return -1; }
    if(hash_table_get(pq->table, element)) { return 1; }
    return 0;
}

void* priority_queue_top(const PriorityQueue *pq) {
    if(!(pq && pq->size)) { return NULL; }
    return pq->heap[0];
}

void priority_queue_pop(PriorityQueue *pq) {
    if(!(pq && pq->size)) { return; }
    size_t *value = hash_table_get(pq->table, pq->heap[0]);
    if(!value) { return; }
    hash_table_remove(pq->table, pq->heap[0]);
    free(value);
    if(pq->size > 1) {
        pq->heap[0] = pq->heap[pq->size-1];
        value = hash_table_get(pq->table, pq->heap[0]);
        if(value) { *value = 0; }
    }
    pq->size--;

    resize_pq_down(pq);

    heapify(pq, 0);
}

int priority_queue_remove(PriorityQueue *pq, const void *element) {
    if(!(pq && element)) { return -1; }
    size_t *index_to_remove = hash_table_get(pq->table, element);
    if(!index_to_remove) { return 0; }
    hash_table_remove(pq->table, element);

    if(*index_to_remove != pq->size-1) {
        pq->heap[*index_to_remove] = pq->heap[pq->size-1]; //put the last element in place of the removed one
        size_t *value = hash_table_get(pq->table, pq->heap[*index_to_remove]);
        *value = *index_to_remove;

        heapify(pq, *value); //check if it should go down
        move_up(pq, *value); //check if it should go up
    }

    free(index_to_remove);
    pq->size--;

    resize_pq_down(pq);

    return 1;
}