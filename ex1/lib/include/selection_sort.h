#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

/**
 * @brief Classic Selection Sort
 * @param array An array
 * @param len Lenght of the array
 * @param size Size of the elements
 * @param compar Function used for comparison
 * The function orders the array using the given comparison function with selection sort.
*/
void selection_sort(void* array, size_t len, size_t size, int (*compar)(const void*, const void*)); 

#endif /* SELECTION_SORT_H */
