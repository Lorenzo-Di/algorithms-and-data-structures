/**
 * Test suite for the hybridsort algorithm.
 */

#include "hybridsort.h"
#include "unity.h"

static int compar(const void* a_p, const void* b_p){
    int* inta_p = (int*)a_p;
    int* intb_p = (int*)b_p;
    if(*inta_p < *intb_p) { return -1; }
    else if (*inta_p > *intb_p) { return 1; }
    return 0;
}

static size_t size = sizeof(int);

void test_quicksort_empty_array(void){
    int* array = NULL;
    hybridsort(array, 0, size, 0, compar);
    TEST_PASS();
}

void test_selection_sort_empty_array(void){
    int* array = NULL;
    hybridsort(array, 0, size, 1, compar);
    TEST_PASS();
}

void test_quicksort_one_element_array(void){
    int array[1] = {5};
    int expected[1] = {5};
    hybridsort(array, 1, size, 0, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 1);
}

void test_selection_sort_one_element_array(void){
    int array[1] = {5};
    int expected[1] = {5};
    hybridsort(array, 1, size, 2, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 1);
}

void test_quicksort_already_ordered_array(void){
    int array[2] = {1, 5};
    int expected[2] = {1, 5};
    hybridsort(array, 2, size, 0, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 2);
}

void test_selection_sort_already_ordered_array(void){
    int array[2] = {1, 5};
    int expected[2] = {1, 5};
    hybridsort(array, 2, size, 3, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 2);
}

void test_quicksort_two_elements_array(void){
    int array[2] = {4, -1};
    int expected[2] = {-1, 4};
    hybridsort(array, 2, size, 0, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 2);
}

void test_selection_sort_two_elements_array(void){
    int array[2] = {4, -1};
    int expected[2] = {-1, 4};
    hybridsort(array, 2, size, 3, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 2);
}

void test_quicksort_generic_array(void){
    int array[5] = {2, 4, 0, -3, -2};
    int expected[5] = {-3, -2, 0, 2, 4};
    hybridsort(array, 5, size, 0, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 5);
}

void test_selection_sort_generic_array(void){
    int array[5] = {2, 4, 0, -3, -2};
    int expected[5] = {-3, -2, 0, 2, 4};
    hybridsort(array, 5, size, 6, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 5);
}

void test_hybridsort_even_k_generic_array(void){
    int array[5] = {2, 4, 0, -3, -2};
    int expected[5] = {-3, -2, 0, 2, 4};
    hybridsort(array, 5, size, 4, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 5);
}

void test_sort_uneven_k_generic_array(void){
    int array[5] = {2, 4, 0, -3, -2};
    int expected[5] = {-3, -2, 0, 2, 4};
    hybridsort(array, 5, size, 3, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 5);
}

void test_hybridsort_array_with_repeated_elements(void){
    int array[10] = {2, 4, 7, -1, 0, 3, 0, 2, 2, -1};
    int expected[10] = {-1, -1, 0, 0, 2, 2, 2, 3, 4, 7};
    hybridsort(array, 10, size, 5, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 10);
}

void test_hybridsort_array_with_same_element(void){
    int array[10] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    int expected[10] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    hybridsort(array, 10, size, 5, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 10);
}

void test_hybridsort_reversed_ordered_array(void){
    int array[10] = {12, 8, 7, 3, 2, 1, 0, 0, -2, -9};
    int expected[10] = {-9, -2, 0, 0, 1, 2, 3, 7, 8, 12};
    hybridsort(array, 10, size, 5, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 10);
}