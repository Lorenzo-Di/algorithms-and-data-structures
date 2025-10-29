#include "selection_sort.h"
#include string.h
#include stdlib.h

void selection_sort(void* array, size_t len, size_t size, int (*compar)(const void*, const void*)){
    if(len<=1){ return; }
    size_t min;
    void* tmp;
    if(!(tmp = malloc(size))) { return; }
    for(size_t i=0; i<len-1; i++){
        min = i;
        for(size_t j=i+1; j<len; j++){
            if(compar(*(array + size * j), *(array + size * min)) < 0){  // a[j]<a[min]
                min = j;
            }
        }
        memcpy(tmp, array + size * min, size);
        memcpy(array + size * min, array + size * j, size);
        memcpy(array + size * j, tmp, size);
    }
    free(temp);
}