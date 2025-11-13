#ifndef RECORDS_IO_H
#define RECORDS_IO_H
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @struct Record
 * @brief Represents a fixed-size data record (36 bytes total).
 */

 typedef struct record
{
    uint64_t id;
    _Float32 field1;
    int64_t field2;
    char field3[16];
} Record;


int read_record(FILE *file, Record *record);

int write_record(FILE *file, const Record *record);

int load_records_from_file(FILE *file, Record **records, size_t *count);

int save_records_to_file(FILE *file, const Record *records, size_t count);

void print_record(const Record *record);

#endif /* RECORDS_IO_H */