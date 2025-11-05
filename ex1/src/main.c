#include "selection_sort.h"

void hybridsort(void *base,
                size_t nitems,
                size_t size,
                size_t k,
                int (*compar)(const void *, const void *)){

    if(nitems < k){ selection_sort(nitems, size, compar); }
    //quicksort
}