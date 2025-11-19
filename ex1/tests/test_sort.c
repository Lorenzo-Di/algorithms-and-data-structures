/**
 * Test suite for the hybridsort algorithm.
 */

#include "hybridsort.h"
#include "compare_records.h"
#include "unity.h"

static int compar(const void* a_p, const void* b_p){
    int inta = *(const int*)a_p;
    int intb = *(const int*)b_p;
    return (inta > intb) - (inta < intb);
}

static int compar_float(const void* a_p, const void* b_p){
    float da = *(const float*)a_p;
    float db = *(const float*)b_p;
    return (da > db) - (da < db);
}

typedef struct {
    int key;
    char str[3];
} Item;

static int compar_item(const void* a, const void* b) {
    int ka = ((const Item*)a)->key;
    int kb = ((const Item*)b)->key;
    return (ka > kb) - (ka < kb);
}

static int compar_string(const void *a, const void *b) {
    return strcmp((const char*)a, (const char*)b);
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

void test_hybridsort_float_array(void){
    float array[5] = {2.1f, 1.3f, 5.43f, -2.0f, 7.746f};
    float expected[5] = {-2.0f, 1.3f, 2.1f, 5.43f, 7.746f};
    hybridsort(array, 5, sizeof(float), 3, compar_float);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, array, 5);
    (void)expected; //needed to avoid compiler warnings
}

void test_hybridsort_struct_array(void){
    Item array[5] = {{3, {0}}, {1, {0}}, {4, {0}}, {2, {0}}, {1, {0}}};
    Item expected[5] = {{1, {0}}, {1, {0}}, {2, {0}}, {3, {0}}, {4, {0}}};
    hybridsort(array, 5, sizeof(Item), 2, compar_item);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, array, sizeof(Item), 5);
}

void test_hybridsort_string(void) {
    char array[][16] = {
        "these",
        "are",
        "four",
        "strings"
    };
    char expected[][16] = {
        "are",
        "four",
        "strings",
        "these"
    };
    hybridsort(array, 4, sizeof(array[0]), 3, compar_string);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, array, 4, sizeof(array[0]));
}