#include "selection_sort.h"
#include <string.h>
#include <stdlib.h>

void selection_sort(void* array, size_t len, size_t size, int (*compar)(const void*, const void*)){
    if(len<=1){ return; }
    char tmp[size];
    size_t min;
    char* a = array;

    for(size_t i=0; i<len-1; i++){
        min = i;
        size_t j;
        for(j=i+1; j<len; j++){
            if(compar(a + size * j, a + size * min) < 0){
                min = j;
            }
        }
        if(min!=i){
            memcpy(tmp, a + size * min, size);
            memcpy(a + size * min, a + size * i, size);
            memcpy(a + size * i, tmp, size);
        }
    }
}