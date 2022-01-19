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
	if (argc!=2){
		printf("please enter the file name!\n");
		exit(1);
	}
	FILE* fp = fopen(argv[1], "r");
	char a[100][100];
	char* line = NULL;
	size_t len = 0;
	ssize_t nread;
	int i= 0;
	while((nread = getline(&line,&len,fp)) != -1){
		strcpy(a[i] , line);
		i++;
	}
    int k = 0;
    printf("%s\n",a[3]);
	//CPU_Instruction* ins = malloc(sizeof(ins));
	//create_CPU_instruction(ins, a[9]);
	//print_Instruction(ins);
	
    /*strcpy(buffer, "0020 st R2, #0028\n");
    CPU_Instruction* ins2 = malloc(sizeof(ins));
    create_CPU_instruction(ins2, buffer);
    print_Instruction(ins2);*/
    
    
    return 0;
}
