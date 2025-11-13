#include "records_io.h"
#include <stdlib.h>

int read_record(FILE *file, Record *record){
    return fread(record, sizeof(Record), 1, file);
}

int write_record(FILE *file, const Record *record){
    return fwrite(record, sizeof(Record), 1, file);
}

int load_records_from_file(FILE *file, Record **records, size_t *count){
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    *count = size / sizeof(Record);
    rewind(file);
    *records = malloc(*count * sizeof(Record));
    if(!*records) { return -1; }
    return read_record(file, *records);
}

int save_records_to_file(FILE *file, const Record *records, size_t count){
    return fwrite(records, sizeof(Record), count, file);
}

void print_record(const Record *record){
    printf("id: %lu\nfield1: %.2f\nField2: %ld\nField3: %s\n",
           record->id, record->field1, record->field2, record->field3);
}
