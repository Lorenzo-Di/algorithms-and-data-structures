#include "compare_records.h"
#include "unity.h"
#include <stdlib.h>

static Record *a,* b;

void setUp(void){
    a = malloc(sizeof(Record));
    b = malloc(sizeof(Record));
    if(!a || !b) { TEST_FAIL_MESSAGE("Failed malloc"); }
}

void tearDown(void){
    free(a);
    a = NULL;
    free(b);
    b=NULL;
}


void test_compare_id_greater(void){
    a->id = 10;
    b->id = 5;
    TEST_ASSERT(compare_record_id(a, b) > 0);
}

void test_compare_id_greater_zero(void){
    a->id = 10;
    b->id = 0;
    TEST_ASSERT(compare_record_id(a, b) > 0);
}

void test_compare_id_lesser(void){
    a->id = 5;
    b->id = 10;
    TEST_ASSERT(compare_record_id(a, b) < 0);
}

void test_compare_id_lesser_zero(void){
    a->id = 0;
    b->id = 10;
    TEST_ASSERT(compare_record_id(a, b) < 0);
}

void test_compare_id_equal(void){
    a->id = 10;
    b->id = 10;
    TEST_ASSERT_EQUAL(0, compare_record_id(a, b));
}

void test_compare_id_equal_zero(void){
    a->id = 0;
    b->id = 0;
    TEST_ASSERT_EQUAL(0, compare_record_id(a, b));
}

///////////////////////////////////////////////

void test_compare_field1_greater(void){
    a->field1 = 10.5f;
    b->field1 = 10.35f;
    TEST_ASSERT(compare_record_field1(a, b) > 0);
}

void test_compare_field1_greater_zero(void){
    a->field1 = 10.5f;
    b->field1 = 0.0f;
    TEST_ASSERT(compare_record_field1(a, b) > 0);
}

void test_compare_field1_lesser(void){
    a->field1 = 10.35f;
    b->field1 = 10.5f;
    TEST_ASSERT(compare_record_field1(a, b) < 0);
}

void test_compare_field1_lesser_zero(void){
    a->field1 = 0.0f;
    b->field1 = 10.5f;
    TEST_ASSERT(compare_record_field1(a, b) < 0);
}

void test_compare_field1_equal(void){
    a->field1 = 10.5f;
    b->field1 = 10.5f;
    TEST_ASSERT_EQUAL(0, compare_record_field1(a, b));
}

void test_compare_field1_equal_zero(void){
    a->field1 = 0.0f;
    b->field1 = 0.0f;
    TEST_ASSERT_EQUAL(0, compare_record_field1(a, b));
}

///////////////////////////////////////////////

void test_compare_field2_greater(void){
    a->field2 = 10;
    b->field2 = 5;
    TEST_ASSERT(compare_record_field2(a, b) > 0);
}

void test_compare_field2_greater_zero(void){
    a->field2 = 10;
    b->field2 = 0;
    TEST_ASSERT(compare_record_field2(a, b) > 0);
}

void test_compare_field2_lesser(void){
    a->field2 = 5;
    b->field2 = 10;
    TEST_ASSERT(compare_record_field2(a, b) < 0);
}

void test_compare_field2_lesser_zero(void){
    a->field2 = 0;
    b->field2 = 10;
    TEST_ASSERT(compare_record_field2(a, b) < 0);
}

void test_compare_field2_equal(void){
    a->field2 = 10;
    b->field2 = 10;
    TEST_ASSERT_EQUAL(0, compare_record_field2(a, b));
}

void test_compare_field2_equal_zero(void){
    a->field2 = 0;
    b->field2 = 0;
    TEST_ASSERT_EQUAL(0, compare_record_field2(a, b));
}

///////////////////////////////////////////////

void test_compare_field3_greater(void){
    strcpy(a->field3, "b");
    strcpy(b->field3, "a"); 
    TEST_ASSERT(compare_record_field3(a, b) > 0);
}

void test_compare_field3_greater_zero(void){
    strcpy(a->field3, "b");
    b->field3[0] = '\0'; 
    TEST_ASSERT(compare_record_field3(a, b) > 0);
}

void test_compare_field3_lesser(void){
    strcpy(a->field3, "a");
    strcpy(b->field3, "b"); 
    TEST_ASSERT(compare_record_field3(a, b) < 0);
}

void test_compare_field3_lesser_zero(void){
    a->field3[0] = '\0'; 
    strcpy(b->field3, "b");
    TEST_ASSERT(compare_record_field3(a, b) < 0);
}

void test_compare_field3_equal(void){
    strcpy(a->field3, "a");
    strcpy(b->field3, "a"); 
    TEST_ASSERT_EQUAL(0, compare_record_field3(a, b));
}

void test_compare_field3_equal_zero(void){
    a->field3[0] = '\0';
    b->field3[0] = '\0';
    TEST_ASSERT_EQUAL(0, compare_record_field3(a, b));
}