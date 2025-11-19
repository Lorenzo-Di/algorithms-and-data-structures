#include "unity.h"

void test_compare_id_greater(void);
void test_compare_id_greater_zero(void);
void test_compare_id_lesser(void);
void test_compare_id_lesser_zero(void);
void test_compare_id_equal(void);
void test_compare_id_equal_zero(void);

void test_compare_field1_greater(void);
void test_compare_field1_greater_zero(void);
void test_compare_field1_lesser(void);
void test_compare_field1_lesser_zero(void);
void test_compare_field1_equal(void);
void test_compare_field1_equal_zero(void);

void test_compare_field2_greater(void);
void test_compare_field2_greater_zero(void);
void test_compare_field2_lesser(void);
void test_compare_field2_lesser_zero(void);
void test_compare_field2_equal(void);
void test_compare_field2_equal_zero(void);

void test_compare_field3_greater(void);
void test_compare_field3_greater_zero(void);
void test_compare_field3_lesser(void);
void test_compare_field3_lesser_zero(void);
void test_compare_field3_equal(void);
void test_compare_field3_equal_zero(void);

void test_quicksort_empty_array(void);
void test_selection_sort_empty_array(void);
void test_quicksort_one_element_array(void);
void test_selection_sort_one_element_array(void);
void test_quicksort_already_ordered_array(void);
void test_selection_sort_already_ordered_array(void);
void test_quicksort_two_elements_array(void);
void test_selection_sort_two_elements_array(void);
void test_quicksort_generic_array(void);
void test_selection_sort_generic_array(void);
void test_hybridsort_even_k_generic_array(void);
void test_sort_uneven_k_generic_array(void);
void test_hybridsort_array_with_repeated_elements(void);
void test_hybridsort_array_with_same_element(void);
void test_hybridsort_reversed_ordered_array(void);

void test_hybridsort_float_array(void);
void test_hybridsort_struct_array(void);
void test_hybridsort_string(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_compare_id_greater);
    RUN_TEST(test_compare_id_greater_zero);
    RUN_TEST(test_compare_id_lesser);
    RUN_TEST(test_compare_id_lesser_zero);
    RUN_TEST(test_compare_id_equal);
    RUN_TEST(test_compare_id_equal_zero);

    RUN_TEST(test_compare_field1_greater);
    RUN_TEST(test_compare_field1_greater_zero);
    RUN_TEST(test_compare_field1_lesser);
    RUN_TEST(test_compare_field1_lesser_zero);
    RUN_TEST(test_compare_field1_equal);
    RUN_TEST(test_compare_field1_equal_zero);

    RUN_TEST(test_compare_field2_greater);
    RUN_TEST(test_compare_field2_greater_zero);
    RUN_TEST(test_compare_field2_lesser);
    RUN_TEST(test_compare_field2_lesser_zero);
    RUN_TEST(test_compare_field2_equal);
    RUN_TEST(test_compare_field2_equal_zero);

    RUN_TEST(test_compare_field3_greater);
    RUN_TEST(test_compare_field3_greater_zero);
    RUN_TEST(test_compare_field3_lesser);
    RUN_TEST(test_compare_field3_lesser_zero);
    RUN_TEST(test_compare_field3_equal);
    RUN_TEST(test_compare_field3_equal_zero);
    
    RUN_TEST(test_quicksort_empty_array);
    RUN_TEST(test_selection_sort_empty_array);
    RUN_TEST(test_quicksort_one_element_array);
    RUN_TEST(test_selection_sort_one_element_array);
    RUN_TEST(test_quicksort_already_ordered_array);
    RUN_TEST(test_selection_sort_already_ordered_array);
    RUN_TEST(test_quicksort_two_elements_array);
    RUN_TEST(test_selection_sort_two_elements_array);
    RUN_TEST(test_quicksort_generic_array);
    RUN_TEST(test_selection_sort_generic_array);
    RUN_TEST(test_hybridsort_even_k_generic_array);
    RUN_TEST(test_sort_uneven_k_generic_array);
    RUN_TEST(test_hybridsort_array_with_repeated_elements);
    RUN_TEST(test_hybridsort_array_with_same_element);
    RUN_TEST(test_hybridsort_reversed_ordered_array);

    RUN_TEST(test_hybridsort_float_array);
    RUN_TEST(test_hybridsort_struct_array);
    RUN_TEST(test_hybridsort_string);
    
    return UNITY_END();
}