#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"
#define NUM_MEMS (2048)

int main(int argc, char **argv){
    if(argc != 3){
        fprintf(stderr, "Usage: %s <processors> <u|n>\n", argv[0]);
        exit(1);
    }
    int procs = atoi(argv[1]);
    if(procs < 1){
        fprintf(stderr, "The number of processors must be a positive "
                "integer.\n");
        exit(1);
    }
    char dist = argv[2][0];
    if(dist != 'u' && dist != 'n'){
        fprintf(stderr, "The distribution must be 'u' or 'n' (uniform or "
                "normal).\n");
        exit(1);
    }
    double avg_wait[NUM_MEMS];
    simulate(avg_wait, NUM_MEMS, procs, dist);
    for(int i=0; i<NUM_MEMS; i++){
        printf("%.4f\n",avg_wait[i]);
    }
    return 0;
}
