#include "unity.h"
#include "hash_table.h"
#include <stdlib.h>

/* --- SETUP & HELPERS --- */

static HashTable* table;

/* Comparison function for integers */
static int compare_ints(const void* a, const void* b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return ia - ib;
}

/* Identity hash function for integers (predictable for bucket testing) */
static unsigned long hash_int(const void* k) {
    return (unsigned long)(*(const int*)k);
}

/* Runs BEFORE every test */
void setUp(void) {
    table = hash_table_create(compare_ints, hash_int);
}

/* Runs AFTER every test */
void tearDown(void) {
    hash_table_free(table);
}

/* --- STANDARD TEST CASES --- */

void test_create_table(void) {
    TEST_ASSERT_NOT_NULL(table);
    TEST_ASSERT_EQUAL_INT(0, hash_table_size(table));
}

void test_put_get_simple(void) {
    int key = 42;
    int value = 100;

    hash_table_put(table, &key, &value);
    
    TEST_ASSERT_EQUAL_INT(1, hash_table_size(table));
    TEST_ASSERT_TRUE(hash_table_contains_key(table, &key));
    
    int* retrieved = (int*)hash_table_get(table, &key);
    TEST_ASSERT_NOT_NULL(retrieved);
    TEST_ASSERT_EQUAL_INT(100, *retrieved);
}

void test_put_overwrite_value(void) {
    int key = 10;
    int val1 = 500;
    int val2 = 600;

    hash_table_put(table, &key, &val1);
    hash_table_put(table, &key, &val2); /* Overwrite */

    TEST_ASSERT_EQUAL_INT(1, hash_table_size(table));
    
    int* retrieved = (int*)hash_table_get(table, &key);
    TEST_ASSERT_EQUAL_INT(600, *retrieved);
}

void test_remove_existing(void) {
    int key = 5;
    int val = 5;

    hash_table_put(table, &key, &val);
    hash_table_remove(table, &key);

    TEST_ASSERT_EQUAL_INT(0, hash_table_size(table));
    TEST_ASSERT_FALSE(hash_table_contains_key(table, &key));
    TEST_ASSERT_NULL(hash_table_get(table, &key));
}

void test_remove_non_existing(void) {
    int key = 99;
    /* Removing a non-existent key should not crash */
    hash_table_remove(table, &key); 
    TEST_ASSERT_EQUAL_INT(0, hash_table_size(table));
}

void test_collision_handling(void) {
    /* With initial capacity 1024 and identity hash:
     * 1 % 1024 = 1
     * 1025 % 1024 = 1
     * Keys 1 and 1025 map to the same bucket.
     */
    int k1 = 1, v1 = 10;
    int k2 = 1025, v2 = 20;

    hash_table_put(table, &k1, &v1);
    hash_table_put(table, &k2, &v2);

    TEST_ASSERT_EQUAL_INT(2, hash_table_size(table));
    TEST_ASSERT_EQUAL_INT(10, *(int*)hash_table_get(table, &k1));
    TEST_ASSERT_EQUAL_INT(20, *(int*)hash_table_get(table, &k2));
}

void test_resize_trigger(void) {
    /* Initial capacity = 1024. Load factor 0.75 -> threshold 768.
     * Insert 800 elements to force resize.
     */
    int keys[800];
    int values[800];

    for (int i = 0; i < 800; i++) {
        keys[i] = i;
        values[i] = i * 2;
        hash_table_put(table, &keys[i], &values[i]);
    }

    TEST_ASSERT_EQUAL_INT(800, hash_table_size(table));

    /* Verify data integrity after resize */
    for (int i = 0; i < 800; i++) {
        int* res = (int*)hash_table_get(table, &keys[i]);
        TEST_ASSERT_NOT_NULL(res);
        TEST_ASSERT_EQUAL_INT(i * 2, *res);
    }
}

void test_keyset(void) {
    int k1 = 10, v1 = 1;
    int k2 = 20, v2 = 2;
    int k3 = 30, v3 = 3;

    hash_table_put(table, &k1, &v1);
    hash_table_put(table, &k2, &v2);
    hash_table_put(table, &k3, &v3);

    void** keys = hash_table_keyset(table);
    TEST_ASSERT_NOT_NULL(keys);

    /* Verify keys presence (order not guaranteed) */
    int count = 0;
    for (int i = 0; i < 3; i++) {
        int val = *(int*)keys[i];
        if (val == 10 || val == 20 || val == 30) count++;
    }
    TEST_ASSERT_EQUAL_INT(3, count);

    free(keys); /* User must free the array */
}

void test_keyset_empty(void) {
    void** keys = hash_table_keyset(table);
    TEST_ASSERT_NOT_NULL(keys); /* Should return valid pointer (malloc(0)) */
    free(keys);
}

/* --- ADVANCED / ROBUSTNESS TEST CASES --- */

void test_null_safety(void) {
    int key = 1;
    int val = 1;

    /* Should not crash if NULL is passed */
    hash_table_put(NULL, &key, &val);
    hash_table_put(table, NULL, &val);
    
    TEST_ASSERT_NULL(hash_table_get(NULL, &key));
    TEST_ASSERT_NULL(hash_table_get(table, NULL));
    
    TEST_ASSERT_FALSE(hash_table_contains_key(NULL, &key));
    TEST_ASSERT_FALSE(hash_table_contains_key(table, NULL));
    
    hash_table_remove(NULL, &key);
    hash_table_remove(table, NULL);
    
    TEST_ASSERT_EQUAL_INT(-1, hash_table_size(NULL));
    TEST_ASSERT_NULL(hash_table_keyset(NULL));
}

void test_interleaved_operations(void) {
    int k1=1, v1=10;
    int k2=2, v2=20;
    int k3=3, v3=30;

    /* Add 3 elements */
    hash_table_put(table, &k1, &v1);
    hash_table_put(table, &k2, &v2);
    hash_table_put(table, &k3, &v3);
    TEST_ASSERT_EQUAL_INT(3, hash_table_size(table));

    /* Remove the middle one */
    hash_table_remove(table, &k2);
    TEST_ASSERT_EQUAL_INT(2, hash_table_size(table));
    TEST_ASSERT_FALSE(hash_table_contains_key(table, &k2));
    TEST_ASSERT_TRUE(hash_table_contains_key(table, &k3)); /* k3 must still exist */

    /* Re-add the removed one */
    hash_table_put(table, &k2, &v2);
    TEST_ASSERT_EQUAL_INT(3, hash_table_size(table));
    TEST_ASSERT_TRUE(hash_table_contains_key(table, &k2));
}

void test_heavy_load_resize(void) {
    /* Initial capacity 1024. 
     * Target: exceed 2048 elements to force at least two resizes.
     */
    const int LIMIT = 2500;
    int *keys = malloc(sizeof(int) * (size_t)LIMIT);
    int *values = malloc(sizeof(int) * (size_t)LIMIT);

    if (!keys || !values) {
        free(keys);
        free(values);
        TEST_FAIL_MESSAGE("Memory allocation failed in test");
    }

    for(int i=0; i<LIMIT; i++) {
        keys[i] = i;
        values[i] = i;
        hash_table_put(table, &keys[i], &values[i]);
    }

    TEST_ASSERT_EQUAL_INT(LIMIT, hash_table_size(table));

    /* Spot check */
    int check_idx = 2000;
    int *val = (int*)hash_table_get(table, &keys[check_idx]);
    TEST_ASSERT_NOT_NULL(val);
    TEST_ASSERT_EQUAL_INT(2000, *val);

    free(keys);
    free(values);
}

/* --- MAIN --- */
int main(void) {
    UNITY_BEGIN();
    
    /* Basic Tests */
    RUN_TEST(test_create_table);
    RUN_TEST(test_put_get_simple);
    RUN_TEST(test_put_overwrite_value);
    RUN_TEST(test_remove_existing);
    RUN_TEST(test_remove_non_existing);
    RUN_TEST(test_collision_handling);
    RUN_TEST(test_resize_trigger);
    RUN_TEST(test_keyset);
    RUN_TEST(test_keyset_empty);
    
    /* Robustness Tests */
    RUN_TEST(test_null_safety);
    RUN_TEST(test_interleaved_operations);
    RUN_TEST(test_heavy_load_resize);

    return UNITY_END();
}