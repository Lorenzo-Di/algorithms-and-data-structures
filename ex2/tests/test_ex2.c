#include "unity.h"
#include "hash_table.h"
#include <stdlib.h>

static int cmp_int(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

static unsigned long hash_int(const void* a) {
    return (unsigned long)(*(const int*)a);
}

/* Helpers */
static int* make_int(int v) {
    int* p = malloc(sizeof(int));
    *p = v;
    return p;
}

/* =====================
   TESTS
   ===================== */

void test_create_not_null(void) {
    HashTable* t = hash_table_create(cmp_int, hash_int);
    TEST_ASSERT_NOT_NULL(t);
    hash_table_free(t);
}

void test_put_then_get_single(void) {
    HashTable* t = hash_table_create(cmp_int, hash_int);
    int* k = make_int(5);
    int* v = make_int(99);

    hash_table_put(t, k, v);
    void* out = hash_table_get(t, k);

    TEST_ASSERT_EQUAL_PTR(v, out);
    hash_table_free(t);
}

void test_get_nonexistent_returns_null(void) {
    HashTable* t = hash_table_create(cmp_int, hash_int);
    int* k = make_int(42);

    TEST_ASSERT_NULL(hash_table_get(t, k));
    free(k);
    hash_table_free(t);
}

void test_overwrite_value(void) {
    HashTable* t = hash_table_create(cmp_int, hash_int);
    int* k = make_int(10);
    int* v1 = make_int(1);
    int* v2 = make_int(2);

    hash_table_put(t, k, v1);
    hash_table_put(t, k, v2);

    TEST_ASSERT_EQUAL_PTR(v2, hash_table_get(t, k));
    hash_table_free(t);
}

void test_contains_key_found(void) {
    HashTable* t = hash_table_create(cmp_int, hash_int);
    int* k = make_int(3);
    hash_table_put(t, k, make_int(7));

    TEST_ASSERT_TRUE(hash_table_contains_key(t, k));
    hash_table_free(t);
}

void test_contains_key_not_found(void) {
    HashTable* t = hash_table_create(cmp_int, hash_int);
    int* k = make_int(500);

    TEST_ASSERT_FALSE(hash_table_contains_key(t, k));
    free(k);
    hash_table_free(t);
}

void test_remove_key(void) {
    HashTable* t = hash_table_create(cmp_int, hash_int);
    int* k = make_int(8);
    int* v = make_int(123);
    hash_table_put(t, k, v);

    hash_table_remove(t, k);

    TEST_ASSERT_FALSE(hash_table_contains_key(t, k));
    hash_table_free(t);
}

void test_size(void) {
    HashTable* t = hash_table_create(cmp_int, hash_int);
    TEST_ASSERT_EQUAL_INT(0, hash_table_size(t));

    hash_table_put(t, make_int(1), make_int(10));
    hash_table_put(t, make_int(2), make_int(20));

    TEST_ASSERT_EQUAL_INT(2, hash_table_size(t));
    hash_table_free(t);
}

void test_keyset_empty(void) {
    HashTable* t = hash_table_create(cmp_int, hash_int);

    void** ks = hash_table_keyset(t);
    TEST_ASSERT_NOT_NULL(ks);   /* should be 1 element array */
    free(ks);

    hash_table_free(t);
}

void test_keyset_contents(void) {
    HashTable* t = hash_table_create(cmp_int, hash_int);
    int* k1 = make_int(1);
    int* k2 = make_int(2);
    int* k3 = make_int(3);

    hash_table_put(t, k1, make_int(10));
    hash_table_put(t, k2, make_int(20));
    hash_table_put(t, k3, make_int(30));

    void** ks = hash_table_keyset(t);
    TEST_ASSERT_NOT_NULL(ks);

    /* We only test counts, not order */
    int count = 0;
    for (int i = 0; i < 3; i++) {
        if (ks[i] == k1 || ks[i] == k2 || ks[i] == k3)
            count++;
    }

    TEST_ASSERT_EQUAL_INT(3, count);
    free(ks);
    hash_table_free(t);
}
