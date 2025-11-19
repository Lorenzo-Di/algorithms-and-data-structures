#ifndef RECORD_H
#define RECORD_H 
#include <stddef.h>
#include <stdint.h>

/**
 * @struct Record
 * @brief Represents a fixed-size data record (36 bytes total).
 */
 typedef struct record
{
    uint64_t id;
    float field1;
    int64_t field2;
    char field3[16];
} Record;

#endif /* RECORD_H */