/**
 * Test suite for the selection sort algorithm.
 */

#include "selection_sort.h"
#include "unity.h"
#include <stdlib.h>

static int compar(const void* a_p, const void* b_p){
    int* inta_p = (int*)a_p;
    int* intb_p = (int*)b_p;
    if(*inta_p < *intb_p) { return -1; }
    else if (*inta_p > *intb_p) { return 1; }
    return 0;
}

static size_t len;
static size_t size = sizeof(int);

static void test_selection_sort_empty_array(void){
    int array[0];
    selection_sort(array, 0, size, compar);
    TEST_PASS();
}

static void test_selection_sort_one_element_array(void){
    int array[1] = {5};
    int expected[1] = {5};
    selection_sort(array, 1, size, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 1);
}

static void test_selection_sort_already_ordered_array(void){
    int array[2] = {1, 5};
    int expected[2] = {1, 5};
    selection_sort(array, 2, size, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 2);
}

static void test_selection_sort_two_elements_array(void){
    int array[2] = {4, -1};
    int expected[2] = {-1, 4};
    selection_sort(array, 2, size, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 2);
}

static void test_selection_sort_generic_array(void){
    int array[5] = {2, 4, 0, -3, -2};
    int expected[5] = {-3, -2, 0, 2, 4};
    selection_sort(array, 5, size, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 5);
}

static void test_selection_sort_array_with_repeated_elements(void){
    int array[5] = {0, 3, 0, 2, -1};
    int expected[5] = {-1, 0, 0, 2, 3};
    selection_sort(array, 5, size, compar);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, array, 5);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_selection_sort_empty_array);
    RUN_TEST(test_selection_sort_one_element_array);
    RUN_TEST(test_selection_sort_already_ordered_array);
    RUN_TEST(test_selection_sort_two_elements_array);
    RUN_TEST(test_selection_sort_generic_array);
    RUN_TEST(test_selection_sort_array_with_repeated_elements);
    
    return UNITY_END();
}
