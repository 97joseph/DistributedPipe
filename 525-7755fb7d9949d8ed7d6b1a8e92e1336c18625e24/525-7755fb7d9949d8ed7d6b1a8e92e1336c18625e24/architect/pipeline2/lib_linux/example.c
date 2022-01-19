//
//  main.c
//  Project1
//
//  Created by Xiang on 2020/1/28.
//  Copyright © 2020年 Xiang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instruction.h"


int main(int argc, const char * argv[]) {
    
    char *buffer = malloc(100);
    strcpy(buffer, "0016 sub R2, R0, R1");
    CPU_Instruction* ins = malloc(sizeof(ins));
    create_CPU_instruction(ins, buffer);
    print_Instruction(ins);
    
    
    strcpy(buffer, "0020 bgez R2, #0028\n");
    CPU_Instruction* ins2 = malloc(sizeof(ins));
    create_CPU_instruction(ins2, buffer);
    print_Instruction(ins2);
    
    
    return 0;
}
