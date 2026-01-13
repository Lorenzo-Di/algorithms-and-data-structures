#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 128

typedef struct {
    int ID;
    int Start;
    int Length;
    int Priority;
} InputTask;

typedef struct {
    int ID;
    int StartTime;
    int EndTime;
} OutputTask;

static int compare_tasks(const void* a, const void* b) {
    const InputTask *task_a = (const InputTask*) a;
    const InputTask *task_b = (const InputTask*) b;
    return task_a->Priority - task_b->Priority;
}

static unsigned long hash_task(const void* a) {
    const InputTask *task_a = (const InputTask*) a;
    return (unsigned long)task_a->ID;
}

void load_tasks_from_file(FILE *file, InputTask **tasks, size_t *count) {
    char line[MAX_LINE_LENGTH];
    *count = 0;
    while(fgets(line, sizeof(line), file)) { (*count)++; }
    rewind(file);

    if(*count == 0) { return; }
    *tasks = malloc(*count * sizeof(InputTask));
    if(!*tasks) { return; }

    for(size_t i=0; i < *count; i++){
        fscanf(file, "%d,%d,%d,%d", &(*tasks)[i].ID, &(*tasks)[i].Start, &(*tasks)[i].Length, &(*tasks)[i].Priority);
    }
}

void save_tasks_to_file(FILE *file, OutputTask *tasks, size_t count) {
    for(size_t i = 0; i < count; i++) {
        fprintf(file, "%d,%d,%d\n", tasks[i].ID, tasks[i].StartTime, tasks[i].EndTime);
    }
}

void simulation(InputTask *input_tasks, OutputTask **output_tasks, size_t count) {
    *output_tasks = malloc(count * sizeof(OutputTask));
    if(!*output_tasks) { return; }

    PriorityQueue *pq = priority_queue_create(compare_tasks, hash_task);
    size_t completed_tasks = 0;
    size_t current_time = 0;
    size_t current_index = 0;
    InputTask *current_task = NULL;

    while(completed_tasks < count) {
        while(current_index < count && current_time >= (size_t)input_tasks[current_index].Start) {
            if(priority_queue_push(pq, &input_tasks[current_index]) != 1) { completed_tasks++; }
            current_index++;
        }
        if((current_task = priority_queue_top(pq))) {
            priority_queue_pop(pq);
            (*output_tasks)[completed_tasks].ID = current_task->ID;
            (*output_tasks)[completed_tasks].StartTime = (int)current_time;
            current_time += (size_t)current_task->Length;
            (*output_tasks)[completed_tasks].EndTime = (int)current_time;
            completed_tasks++;
        }
        else { current_time++; }
    }
}

int main(int argc, char* argv[]) {
    if(argc!=3){
        printf("Usage: $ ./bin/main_ex1 <input_file> <output_file>");
        return EXIT_FAILURE;
    }

    FILE *infile = fopen(argv[1], "r");
    if(!infile) { return EXIT_FAILURE; }
    
    FILE *outfile = fopen(argv[2], "w");
    if(!outfile) { return EXIT_FAILURE; }

    InputTask *input_tasks = NULL;
    OutputTask *output_tasks = NULL;
    size_t count = 0;

    load_tasks_from_file(infile, &input_tasks, &count);
    fclose(infile);

    simulation(input_tasks, &output_tasks, count);

    free(input_tasks);
    input_tasks = NULL;

    save_tasks_to_file(outfile, output_tasks, count);
    fclose(outfile);

    free(output_tasks);
    output_tasks = NULL;
}