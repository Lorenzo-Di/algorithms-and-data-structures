#ifndef HYBRIDSORT_H
#define HYBRIDSORT_H
#include <stddef.h>

/**
 * @mainpage Algorithm project Documentation
 *
 * @section intro_sec Introduction
 * This is the documentation for a sorting library.
 * The main algorithm is HybridSort.
 *
 * @section usage_sec How to use
 * Include hybridsort.h and call hybridsort().
 */

/**
 * @file hybridsort.h
 * @brief Public Interface for the hybrid sort algorithm.
 */

/**
 * @brief A sorting algorithm that combines quicksort and selection sort.
 * The algorithm uses quicksort for arrays of lenght >= k, selection sort for < k.
 * @param base The array to be sorted
 * @param nitems Length of the array
 * @param size Size of the elements in the array
 * @param k The threshold for switching between the algorithms
 * @param compar Function used for sorting the array.
 * The function orders the array using the given comparison function with selection sort.
*/
void hybridsort(void *base,
                size_t nitems,
                size_t size,
                size_t k,
                int (*compar)(const void *, const void *));


#endif /* HYBRIDSORT_H */
