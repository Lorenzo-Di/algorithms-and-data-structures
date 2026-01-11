#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H
#include <stddef.h>

/**
 * @file selection_sort.h
 * @brief Standard selection sort function.
 */

/**
 * @brief Classic Selection Sort
 * @param array The array to be sorted
 * @param len Length of the array
 * @param size Size of the elements in the array
 * @param compar Function used for sorting the array.
 * The function orders the array using the given comparison function with selection sort.
*/
void selection_sort(void* array, size_t len, size_t size, int (*compar)(const void*, const void*)); 

#endif /* SELECTION_SORT_H */
