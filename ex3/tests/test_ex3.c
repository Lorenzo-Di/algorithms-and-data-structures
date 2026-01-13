#include "unity.h"
#include "priority_queue.h"
#include <stdlib.h>

static PriorityQueue* pq = NULL;

static int val1 = 10;
static int val2 = 20;
static int val3 = 30;
static int val4 = 5;
static int val5 = 100;

static int compare_ints(const void* a, const void* b) {
    return (*(const int*)a) - (*(const int*)b);
}

static unsigned long hash_int(const void* a) {
    return (unsigned long)(*(const int*)a);
}

void setUp(void) {
    pq = priority_queue_create(compare_ints, hash_int);
}

void tearDown(void) {
    if (pq != NULL) {
        priority_queue_free(pq);
        pq = NULL;
    }
}

void test_PriorityQueue_Create(void) {
    TEST_ASSERT_NOT_NULL(pq);
    TEST_ASSERT_EQUAL_INT(0, priority_queue_size(pq));
}

void test_PriorityQueue_Push(void) {
    TEST_ASSERT_EQUAL_INT(1, priority_queue_push(pq, &val1));
    TEST_ASSERT_EQUAL_INT(1, priority_queue_size(pq));
    TEST_ASSERT_EQUAL_PTR(&val1, priority_queue_top(pq));
}

void test_Heap_Property_Order(void) {
    priority_queue_push(pq, &val2); // 20
    priority_queue_push(pq, &val1); // 10
    priority_queue_push(pq, &val3); // 30
    priority_queue_push(pq, &val4); // 5

    /* Expect Min-Heap order: 5, 10, 20, 30 */
    TEST_ASSERT_EQUAL_PTR(&val4, priority_queue_top(pq));
    priority_queue_pop(pq);

    TEST_ASSERT_EQUAL_PTR(&val1, priority_queue_top(pq));
    priority_queue_pop(pq);

    TEST_ASSERT_EQUAL_PTR(&val2, priority_queue_top(pq));
    priority_queue_pop(pq);

    TEST_ASSERT_EQUAL_PTR(&val3, priority_queue_top(pq));
    priority_queue_pop(pq);
}

void test_PriorityQueue_Contains(void) {
    priority_queue_push(pq, &val1);
    TEST_ASSERT_TRUE(priority_queue_contains(pq, &val1));
    TEST_ASSERT_FALSE(priority_queue_contains(pq, &val2));
}

void test_PriorityQueue_Remove_Arbitrary(void) {
    priority_queue_push(pq, &val1);
    priority_queue_push(pq, &val2);
    priority_queue_push(pq, &val3);

    TEST_ASSERT_EQUAL_INT(1, priority_queue_remove(pq, &val2));
    TEST_ASSERT_EQUAL_INT(2, priority_queue_size(pq));
    TEST_ASSERT_FALSE(priority_queue_contains(pq, &val2));

    /* Verify heap integrity */
    TEST_ASSERT_EQUAL_PTR(&val1, priority_queue_top(pq));
    priority_queue_pop(pq);
    TEST_ASSERT_EQUAL_PTR(&val3, priority_queue_top(pq));
}

void test_PriorityQueue_Remove_Root_Explicitly(void) {
    priority_queue_push(pq, &val1);
    priority_queue_push(pq, &val2);

    /* Remove root (10) via remove() instead of pop() */
    TEST_ASSERT_EQUAL_INT(1, priority_queue_remove(pq, &val1));
    TEST_ASSERT_EQUAL_PTR(&val2, priority_queue_top(pq));
}

void test_PriorityQueue_Remove_Missing(void) {
    priority_queue_push(pq, &val1);
    TEST_ASSERT_EQUAL_INT(0, priority_queue_remove(pq, &val5));
}

void test_Duplicate_Pointer_Insertion(void) {
    priority_queue_push(pq, &val1);
    /* Should return 0 if already present */
    TEST_ASSERT_EQUAL_INT(0, priority_queue_push(pq, &val1));
    TEST_ASSERT_EQUAL_INT(1, priority_queue_size(pq));
}

void test_Equal_Priority_Behavior(void) {
    int a = 10, b = 10;
    priority_queue_push(pq, &a);
    priority_queue_push(pq, &b);

    TEST_ASSERT_EQUAL_INT(2, priority_queue_size(pq));
    
    /* Ensure both are retrieved */
    TEST_ASSERT_NOT_NULL(priority_queue_top(pq));
    priority_queue_pop(pq);
    TEST_ASSERT_NOT_NULL(priority_queue_top(pq));
}

void test_Empty_Queue_Behavior(void) {
    TEST_ASSERT_NULL(priority_queue_top(pq));
    priority_queue_pop(pq); // Should not crash
    TEST_ASSERT_EQUAL_INT(0, priority_queue_size(pq));
}

void test_Stress_Ternary_Structure(void) {
    int data[20];
    for (int i = 0; i < 20; i++) {
        data[i] = 19 - i;
        priority_queue_push(pq, &data[i]);
    }

    TEST_ASSERT_EQUAL_INT(20, priority_queue_size(pq));

    /* Verify sorted output 0..19 */
    for (int i = 0; i < 20; i++) {
        int* top = (int*)priority_queue_top(pq);
        TEST_ASSERT_EQUAL_INT(i, *top);
        priority_queue_pop(pq);
    }
}

void test_PriorityQueue_Sizes(void) {
    TEST_ASSERT_EQUAL_INT(0, priority_queue_size(pq));
    priority_queue_push(pq, &val1);
    TEST_ASSERT_EQUAL_UINT((size_t)1, priority_queue_size_size_t(pq));
}

void test_Invalid_Args(void) {
    TEST_ASSERT_EQUAL_INT(-1, priority_queue_push(NULL, &val1));
    TEST_ASSERT_EQUAL_INT(-1, priority_queue_push(pq, NULL));
    TEST_ASSERT_EQUAL_INT(-1, priority_queue_contains(NULL, &val1));
    TEST_ASSERT_NULL(priority_queue_top(NULL));
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_PriorityQueue_Create);
    RUN_TEST(test_PriorityQueue_Push);
    RUN_TEST(test_Heap_Property_Order);
    RUN_TEST(test_PriorityQueue_Contains);
    RUN_TEST(test_PriorityQueue_Remove_Arbitrary);
    RUN_TEST(test_PriorityQueue_Remove_Root_Explicitly);
    RUN_TEST(test_PriorityQueue_Remove_Missing);
    RUN_TEST(test_Duplicate_Pointer_Insertion);
    RUN_TEST(test_Equal_Priority_Behavior);
    RUN_TEST(test_Empty_Queue_Behavior);
    RUN_TEST(test_Stress_Ternary_Structure);
    RUN_TEST(test_PriorityQueue_Sizes);
    RUN_TEST(test_Invalid_Args);

    return UNITY_END();
}