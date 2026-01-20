#include "bfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 128
#define MAX_CITY_LENGTH 64

typedef struct {
    char place1[MAX_CITY_LENGTH];
    char place2[MAX_CITY_LENGTH];
    float distance;
} InputRecord;


static int compare_strings(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

static unsigned long hash_string(const void* k) {
    unsigned long hash = 5381;
    int c;
    const char *str = (const char*)k;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + (unsigned long)c;
    }
    return hash;
}

void load_records_from_file(FILE *file, InputRecord **records, size_t *count) {
    char line[MAX_LINE_LENGTH];
    *count = 0;
    while(fgets(line, sizeof(line), file)) { (*count)++; }
    rewind(file);

    if(*count == 0) { return; }
    *records = malloc(*count * sizeof(InputRecord));
    if(!*records) { return; }

    size_t i;
    for(i=0; i < *count; i++) {
        if(fscanf(file, "%[^,],%[^,],%f\n", (*records)[i].place1, (*records)[i].place2, &(*records)[i].distance) != 3) {
            break;
        }
    }
    *count = i;
}

void save_result_to_file(FILE *file, char **result) {
    for(size_t i = 0; result[i]; i++) {
        fprintf(file, "%s\n", result[i]);
    }
}

int main(int argc, char* argv[]) {
    if(argc!=4){
        printf("Usage: $ ./bin/main_ex1 <input_file> <starting_city> <output_file>");
        return EXIT_FAILURE;
    }

    FILE *infile = fopen(argv[1], "r");
    if(!infile) { return EXIT_FAILURE; }

    char *starting_city = argv[2];
    
    FILE *outfile = fopen(argv[3], "w");
    if(!outfile) { fclose(infile); return EXIT_FAILURE; }

    InputRecord *records = NULL;
    size_t count = 0;

    load_records_from_file(infile, &records, &count);
    fclose(infile);
    if(!records) { fclose(outfile); return EXIT_FAILURE; }

    Graph gr = graph_create(1, 0, compare_strings, hash_string);
    if(!gr) { free(records); fclose(outfile); return EXIT_FAILURE; }

    for(size_t i = 0; i < count; i++) {
        graph_add_node(gr, records[i].place1);
        graph_add_node(gr, records[i].place2);
        graph_add_edge(gr, records[i].place1, records[i].place2, &records[i].distance);
    }

    char **result = (char **)breadth_first_visit(gr, starting_city, compare_strings, hash_string);

    save_result_to_file(outfile, result);
    fclose(outfile);

    graph_free(gr);
    free(records);
    records = NULL;
    free(result);
    result = NULL;
    return EXIT_SUCCESS;
}