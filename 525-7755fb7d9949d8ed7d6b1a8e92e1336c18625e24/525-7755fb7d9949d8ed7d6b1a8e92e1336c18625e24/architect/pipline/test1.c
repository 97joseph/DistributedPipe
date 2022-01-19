#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct CPU_Instruction
{
	char opcode[128];
	int rd;
	int rs1;
	int rs2;
	int imm;
	bool is_imm;
	char trace[128];
}CPU_Instruction;
int main(int argc, const char * argv[]){
	char *buffer = malloc(100);
	strcpy(buffer, "0016 sub R2, R0, R1");
	printf("buffer is : %s\n",buffer);
	strcpy(buffer, "0020 bgez R2, #0028\n");
	printf("buffer is : %s\n",buffer);
}
