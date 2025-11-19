#include "hybridsort.h"
#include "record.h"
#include "records_io.h"
#include "compare_records.h"
#include <stdlib.h>
#include <stdio.h>

void sort_records(FILE *infile, FILE *outfile, size_t field, size_t k){
    Record *records = NULL;
    size_t count = 0;
    load_records_from_file(infile, &records, &count);

    switch (field){
        case 1:
            hybridsort(records, count, sizeof(Record), k, compare_record_id);
            break;
        case 2:
            hybridsort(records, count, sizeof(Record), k, compare_record_field1);
            break;
        case 3:
            hybridsort(records, count, sizeof(Record), k, compare_record_field2);
            break;
        case 4:
            hybridsort(records, count, sizeof(Record), k, compare_record_field3);
            break;
    }

    save_records_to_file(outfile, records, count);
    free(records);
    records = NULL;
}

int main(int argc, char* argv[]){
    if(argc!=5){
        printf("Usage: $ ./bin/main_ex1 <input_file> <output_file> <field> <k>");
        return EXIT_FAILURE;
    }

    FILE *infile = fopen(argv[1], "rb");
    if(!infile) { return EXIT_FAILURE; }
    
    FILE *outfile = fopen(argv[2], "wb");
    if(!outfile) { return EXIT_FAILURE; }
    
    size_t field = (size_t)(atoi(argv[3]));
    if(field < 1 || field > 4) { return EXIT_FAILURE; }
    
    long tmp = atol(argv[4]);
    if(tmp < 0) { return EXIT_FAILURE; }
    size_t k = (size_t)(tmp);

    sort_records(infile, outfile, field, k);

    fclose(infile);
    fclose(outfile);

    return EXIT_SUCCESS;
}