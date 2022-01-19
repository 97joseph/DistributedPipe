#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include"instruction.h"
#include"simulator.h"


int main(int argc, char const* argv[]){
	if (argc!=3){
		printf("please enter the two arguments, first one is 0-3, second one is input file!\n");
		exit(1);
	}
	FILE* fp = fopen(argv[2], "r");
	char a[100][100];
	char* line = NULL;
	size_t len = 0;
	ssize_t nread;
	int i= 0;
	long sw;
	while((nread = getline(&line,&len,fp)) != -1){
		strcpy(a[i] , line);
		i++;
	}
	simulator* sim = sim_build(a,i);
	FILE* in_file = fopen("memory_map.txt","r");
	int k = 0;
	
	while(i<16384){
		int number;
		if(fscanf(in_file,"%d",&number)!=1)
			break;
		sim->memory[k]= number;
		k++;	
	}
	
	fclose(in_file);
	/*for(int x = 0;x<16384;x++){
		printf("%d ",sim->memory[x]);
	}*/
	
	sw = strtol(argv[1],NULL,10);
	if(sw == 0){
		while(!sim->end_flag){
			WB(sim);
			Mem4(sim);
			Mem3(sim);
			Mem2(sim);
			Mem1(sim);
			EXb2(sim);
			EXb1(sim);
			EXa(sim);
			ID(sim);
			IF(sim);
			sim->cc += 1;
		}
		memory_out_0(sim);
		sim->ins_sum = sim->set_num+sim->add_num+sim->sub_num+sim->mul_num+sim->div_num+sim->ld_num+sim->st_num+sim->bez_num+sim->bgez_num+sim->blez_num+sim->bgtz_num+sim->bltz_num+sim->ret_num;
		print_1(sim,argv[2]);
		print_2(sim);
		print_3(sim);
	}
	else if(sw== 1){
		while(!sim->end_flag){
			printf("===============================\n");
			printf("Clock Cycle #: %d\n",sim->cc);
			printf("-------------------------------\n");
			WB(sim);
			Mem4(sim);
			Mem3(sim);
			Mem2(sim);
			Mem1(sim);
			EXb2(sim);
			EXb1_v1(sim);
			EXa_v1(sim);
			ID_v1(sim);
			IF(sim);
			sim->cc += 1;
		}
		memory_out_1(sim);
		sim->ins_sum = sim->set_num+sim->add_num+sim->sub_num+sim->mul_num+sim->div_num+sim->ld_num+sim->st_num+sim->bez_num+sim->bgez_num+sim->blez_num+sim->bgtz_num+sim->bltz_num+sim->ret_num;
		printf("\n\n>Pipeline update#2<\n\n");
		print_2(sim);
		print_3_v1(sim);
	}
	else if(sw==2){
		while(!sim->end_flag){
			WB(sim);
			Mem4_v2(sim);
			Mem3_v2(sim);
			Mem2_v2(sim);
			Mem1_v2(sim);
			EXb2_v2(sim);
			EXb1_v2(sim);
			EXa_v2(sim);
			ID_v2(sim);
			IF(sim);
			sim->cc += 1;
		}
		memory_out_2(sim);
		sim->ins_sum = sim->set_num+sim->add_num+sim->sub_num+sim->mul_num+sim->div_num+sim->ld_num+sim->st_num+sim->bez_num+sim->bgez_num+sim->blez_num+sim->bgtz_num+sim->bltz_num+sim->ret_num;
		printf("\n\n>Pipeline update#2<\n\n\n");
		print_1(sim,argv[2]);
		print_2(sim);
		print_3_v2(sim);
	}
	else if(sw==3){
		while(!sim->end_flag){
			printf("===============================\n");
			printf("Clock Cycle #: %d\n",sim->cc);
			printf("-------------------------------\n");
			WB(sim);
			Mem4_v2(sim);
			Mem3_v2(sim);
			Mem2_v2(sim);
			Mem1_v2(sim);
			EXb2_v2(sim);
			EXb1_v2(sim);
			EXa_v2(sim);
			ID_v3(sim);
			IF(sim);
			sim->cc += 1;
			
		}
		memory_out_3(sim);
		sim->ins_sum = sim->set_num+sim->add_num+sim->sub_num+sim->mul_num+sim->div_num+sim->ld_num+sim->st_num+sim->bez_num+sim->bgez_num+sim->blez_num+sim->bgtz_num+sim->bltz_num+sim->ret_num;
		printf("\n\n>Pipeline update#3<\n\n\n");
		print_2(sim);
		print_3_v3(sim);
	}
}



