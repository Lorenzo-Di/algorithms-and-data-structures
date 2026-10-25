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

static void partition(void* base,
                size_t p,
                size_t r,
                size_t size,
                int (*compar)(const void *, const void *),
                size_t *low,
                size_t *high){
                    
    char* b = (char*)base;
    char pivot[size];
    void *C = (char*)b + (p + (size_t)rand() % (r - p + 1)) * size;
    memcpy(pivot, C, size);

    // [p..l-1] < pivot, [l..i-1] == pivot, [h+1..r] > pivot
    size_t l = p;
    size_t i = p;
    size_t h = r;
    
    while(i<=h){
        int res = compar(b + i * size, pivot);
        if(res < 0){
            swap_bytes(b + l * size, b + i * size, size);
            l++;
            i++;
        }
        else if(res > 0){
            swap_bytes(b + i * size, b + h * size, size);
            h--;
        }
        else{ i++; }
    }

    *low = l;
    *high = h;
}

static void hybridsort_rec(void *base,
                size_t p,
                size_t r,
                size_t size,
                size_t k,
                int (*compar)(const void *, const void *)){

    if(p>=r){ return; }
    
    if(r - p + 1 < k){
        selection_sort((char*)base + p * size, r - p + 1, size, compar);
        return;
    }

    size_t low, high;
    partition(base, p, r, size, compar, &low, &high);
    if(low > p) { hybridsort_rec(base, p, low - 1, size, k, compar); }
    if(high < r) { hybridsort_rec(base, high + 1, r, size, k, compar); }
}

void hybridsort(void *base,
                size_t nitems,
                size_t size,
                size_t k,
                int (*compar)(const void *, const void *)){
    
    if(nitems == 0) { return; }
    hybridsort_rec(base, 0, nitems - 1, size, k, compar);
}