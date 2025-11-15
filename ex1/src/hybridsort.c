#include "selection_sort.h"
#include "hybridsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    
    size_t a1 = p;
    size_t b1 = p + (r - p) / 2;
    size_t c1 = r;
    char* A = b + a1 * size;
    char* B = b + b1 * size;
    char* C = b + c1 * size;

    if (compar(A, B) > 0) swap_bytes(A, B, size);
    if (compar(B, C) > 0) swap_bytes(B, C, size);
    if (compar(A, B) > 0) swap_bytes(A, B, size);
    swap_bytes(b + b1 * size, b + r * size, size);

    char pivot[size];
    memcpy(pivot, b + r * size, size);

    // [p..l-1] < pivot, [l..i-1] == pivot, [g+1..r] > pivot
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
    hybridsort_rec(base, high + 1, r, size, k, compar);
}

void hybridsort(void *base,
                size_t nitems,
                size_t size,
                size_t k,
                int (*compar)(const void *, const void *)){
    
    if(nitems == 0) { return; }
    srand((unsigned int)time(NULL));
    hybridsort_rec(base, 0, nitems - 1, size, k, compar);
}