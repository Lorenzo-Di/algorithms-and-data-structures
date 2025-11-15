#ifndef COMPARE_RECORDS_H
#define COMPARE_RECORDS_H
#include "record.h"
#include <string.h>

static inline int compare_record_id(const void *a, const void *b){
    const Record *ra = a;
    const Record *rb = b;
    return (ra->id > rb->id) - (ra->id < rb->id);
}

static inline int compare_record_field1(const void *a, const void *b){
    const Record *ra = a;
    const Record *rb = b;
    return (ra->field1 > rb->field1) - (ra->field1 < rb->field1);
}

static inline int compare_record_field2(const void *a, const void *b){
    const Record *ra = a;
    const Record *rb = b;
    return (ra->field2 > rb->field2) - (ra->field2 < rb->field2);
}

static inline int compare_record_field3(const void *a, const void *b){
    const Record *ra = a;
    const Record *rb = b;
    return strcmp(ra->field3, rb->field3);
}

#endif /* COMPARE_RECORDS_H */