#include "records_io.h"
#include <stdlib.h>

int read_record(FILE *file, Record *record){
    if(fread(record, sizeof(Record), 1, file) == 1) { return 1; }
    return -1;
}

int write_record(FILE *file, const Record *record){
    if(fwrite(record, sizeof(Record), 1, file) == 1) { return 1; }
    return -1;
}

int load_records_from_file(FILE *file, Record **records, size_t *count){
    if(fseek(file, 0, SEEK_END) != 0) { return -1; }
    long size = ftell(file);
    if(size <= 0) { return -1; }
    *count = (size_t)size / sizeof(Record);
    rewind(file);
    *records = malloc(*count * sizeof(Record));
    if(!*records) { return -1; }
    if(fread(*records, sizeof(Record), *count, file) == *count) { return 1; }
    return -1;
}

int save_records_to_file(FILE *file, const Record *records, size_t count){
    if(fwrite(records, sizeof(Record), count, file) == count) { return 1; }
    return -1;
}

void print_record(const Record *record){
    printf("id: %lu\nfield1: %.2f\nField2: %ld\nField3: %s\n",
           record->id, record->field1, record->field2, record->field3);
}
