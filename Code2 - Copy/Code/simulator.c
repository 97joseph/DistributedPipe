
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define NUM_MEMS (2048)
#define NUM_PROC (64)
#define C (1000000)

struct Processor {
    int memory;
    int access_time;
    int granted_access;
    int mu;
};

struct Processor* processors[NUM_PROC];
int Memory[NUM_MEMS] = {0};
int W[NUM_MEMS] = {0};


int uniformly_random(int maximum) {
    return rand() % maximum;
}

int normally_random(int maximum, double mean, double stdev) {
    double v1 = ((double)(rand()) + 1.)/((double)(RAND_MAX) + 1.);
    double v2 = ((double)(rand()) + 1.)/((double)(RAND_MAX) + 1.);
    
    int v0 = round(cos(2 * 3.141593 * v2) * sqrt(-2. * log(v1)) * stdev + mean);
    v0 %= maximum;

    if(v0 >= maximum) v0 -= maximum;
    if(v0 < 0) v0 += maximum;

    return v0;
}

void initial_uniform_assignment(int processor_count, int memory_count) {
    int p;
    for(p = 0; p < processor_count; p++) {
        processors[p]->mu = uniformly_random(memory_count);
    }
}

void initialize(int processor_count) {
    srand(time(NULL));
    
    int p;
    for(p = 0; p < processor_count; p++) {
        processors[p] = malloc(sizeof(struct Processor));
        processors[p]->memory = -1;
        processors[p]->access_time = 0;
        processors[p]->granted_access = 0;
    }
}

void deinitialize(int processor_count) {
    int p;
    for(p = 0; p < processor_count; p++) {
        processors[p]->memory = -1;
        processors[p]->access_time = 0;
        processors[p]->granted_access = 0;
    }
}

void assign_memory_to_processor_uniformly(int processor_count, int memory_count) {
    int p, assigned_memory;
    for(p = 0; p < processor_count; p++) {
        assigned_memory = uniformly_random(memory_count);
        if(Memory[assigned_memory] == 1) {
            processors[p]->access_time += 1;
        } else {
            processors[p]->granted_access += 1;
            processors[p]->memory = assigned_memory;
            Memory[assigned_memory] = 1;
        }
    }
}

void assign_memory_to_processor_normally(int processor_count, int memory_count) {
    int p, assigned_memory;
    for(p = 0; p < processor_count; p++) {
        assigned_memory = normally_random(memory_count, (double)processors[p]->mu, (double)memory_count / 6.0);
        if(Memory[assigned_memory] == 1) {
            processors[p]->access_time += 1;
        } else {
            processors[p]->granted_access += 1;
            processors[p]->memory = assigned_memory;
            Memory[assigned_memory] = 1;
        }
    }
}

int find_next_assigned_processor(int from, int processor_count) {
    int p;
    for(p = from + 1; p < processor_count; p++) {
        if(processors[p]->memory >= 0) break;
    }
    
    return p;
}

void prioritize_unassigned_processor(int processor_count) {
    struct Processor* temp;
    int assigned = 0, p;
    for(p = 0; p < processor_count; p++) {
        if(processors[p]->memory == -1) {
            temp = processors[p];
            processors[p] = processors[assigned];
            processors[assigned] = temp;
            assigned = find_next_assigned_processor(assigned, processor_count);
        }
    }
}

void update_W(double *avg_wait, int processor_count, int memory_count) {
    int p;
    double sum = 0.0;
    
    for(p = 0; p < processor_count; p++) {
        if(processors[p]->granted_access > 0) {
            sum += (double)processors[p]->access_time / (double)processors[p]->granted_access;
        }
    }
    
    avg_wait[memory_count] = sum / processor_count;
}

void reconfigure(int processor_count, int memory_count) {
    int p, m;
    for(p = 0; p < processor_count; p++) {
        processors[p]->memory = -1;
    }
    
    for(m = 0; m < memory_count; m++) {
        Memory[m] = 0;
    }
}

void simulate(double *avg_wait, int avg_wait_l, int procs, char dist){

    // YOUR CODE GOES HERE
    int i, m;
    initialize(procs);
    
    switch (dist) {
        case 'u':
            for(m = 1; m <= NUM_MEMS; m++) {
                printf("%d\n", m);
                for(i = 0; i < C; i++) {
                    assign_memory_to_processor_uniformly(procs, m);
                    prioritize_unassigned_processor(procs);
                    reconfigure(procs, m);
                    update_W(avg_wait, procs, m);
                }
                deinitialize(procs);
            }
            break;
        case 'n':
            for(m = 1; m <= NUM_MEMS; m++) {
                printf("%d\n", m);

                initial_uniform_assignment(procs, m);
                for(i = 0; i < C; i++) {
                    assign_memory_to_processor_normally(procs, m);
                    prioritize_unassigned_processor(procs);
                    reconfigure(procs, m);
                    update_W(avg_wait, procs, m);
                }
                deinitialize(procs);
            }
            break;
        default:
            break;
    }


    printf("procs: %d\ndist: %c\n", procs, dist);
   
}
