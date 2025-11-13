#include "selection_sort.h"
#include "hybridsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline void swap_bytes(void *a, void *b, size_t size) {
    char tmp[size];
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

static size_t partition(void* base,
                size_t p,
                size_t r,
                size_t size,
                int (*compar)(const void *, const void *)){
    
    char* b = (char*)base;
    char* k = b + (p + (size_t)rand() % (r - p + 1)) * size; //pivot
    swap_bytes(k, b + r * size, size);

    size_t i = p; // i is the index of the first element > pivot or the one to be checked if none so far
    for(size_t j = p; j < r; j++){
        if(compar(b + j * size, b + r * size) <= 0){
            swap_bytes(b + i * size, b + j * size, size);
            i++;
        }
    }
    swap_bytes(b + i * size, b + r * size, size);
    return i;
}

static void hybridsort_rec(void *base,
                size_t p,
                size_t r,
                size_t size,
                size_t k,
                int (*compar)(const void *, const void *)){
    
    if(p>=r){ return; }
    
    if(r-p+1 < k){
        selection_sort((char*)base + p*size, r-p+1, size, compar);
        return;
    }

    size_t q = partition(base, p, r, size, compar);
    if(q>p) { hybridsort_rec(base, p, q-1, size, k, compar); }
    hybridsort_rec(base, q+1, r, size, k, compar);

}

void hybridsort(void *base,
                size_t nitems,
                size_t size,
                size_t k,
                int (*compar)(const void *, const void *)){
    
    if(nitems == 0) { return; }
    hybridsort_rec(base, 0, nitems-1, size, k, compar);
}
