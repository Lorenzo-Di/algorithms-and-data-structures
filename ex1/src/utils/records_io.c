#include "records_io.h"
#include <stdlib.h>

#define RECORD_DISK_SIZE 36

int read_record(FILE *file, Record *record){
    if (fread(&record->id, 8, 1, file) != 1) return -1;
    if (fread(&record->field1, 4, 1, file) != 1) return -1;
    if (fread(&record->field2, 8, 1, file) != 1) return -1;
    if (fread(&record->field3, 16, 1, file) != 1) return -1;
    return 1;
}

int write_record(FILE *file, const Record *record){
    if (fwrite(&record->id, 8, 1, file) != 1) return -1;
    if (fwrite(&record->field1, 4, 1, file) != 1) return -1;
    if (fwrite(&record->field2, 8, 1, file) != 1) return -1;
    if (fwrite(&record->field3, 16, 1, file) != 1) return -1;
    return 1;
}

int load_records_from_file(FILE *file, Record **records, size_t *count){
    if(fseek(file, 0, SEEK_END) != 0) { return -1; }
    long size = ftell(file);
    rewind(file);

    if(size <= 0) { return -1; }
    
    *count = (size_t)size / RECORD_DISK_SIZE;
    *records = malloc(*count * sizeof(Record));
    if(!*records) { return -1; }

    for(size_t i=0; i < *count; i++){
        if(read_record(file, &(*records)[i]) != 1) return -1;
    }
    
    return 1;
}

int save_records_to_file(FILE *file, const Record *records, size_t count){
     for(size_t i = 0; i < count; i++){
        if(write_record(file, &records[i]) != 1) { return -1; }
    }
    return 1;
}

void print_record(const Record *record){
    printf("id: %lu\nfield1: %.2f\nField2: %ld\nField3: %s\n",
           record->id, record->field1, record->field2, record->field3);
}
