#ifndef COMPARE_RECORDS_H
#define COMPARE_RECORDS_H
#include "record.h"
#include <string.h>

static inline int compare_record_id(const Record *a, const Record *b){
    return (a->id > b->id) - (a->id < b->id);
}

static inline int compare_record_field1(const Record *a, const Record *b){
    return (a->field1 > b->field1) - (a->field1 < b->field1);
}

static inline int compare_record_field2(const Record *a, const Record *b){
    return (a->field2 > b->field2) - (a->field2 < b->field2);
}

static inline int compare_record_field3(const Record *a, const Record *b){
    return strcmp(a->field3, b->field3);
}

#endif /* COMPARE_RECORDS_H */