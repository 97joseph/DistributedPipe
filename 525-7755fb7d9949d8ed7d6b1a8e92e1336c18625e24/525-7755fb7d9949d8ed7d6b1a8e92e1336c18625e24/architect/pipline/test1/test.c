#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE* in_file = fopen("memory.map","r");
	int memory[16384];
	int i = 0;
	
	while(i<16384){
		int number;
		if(fscanf(in_file,"%d",&number)!=1)
			break;
		memory[i]= number;
		i++;	
	}
	
	fclose(in_file);
	printf("%d ",memory[1002]);
}
