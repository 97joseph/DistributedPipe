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
	simulator* sim_d = sim_build_d(a,i);
	FILE* in_file = fopen("memory_map.txt","r");
	int k = 0;
	
	while(k<16384){
		int number;
		if(fscanf(in_file,"%d",&number)!=1)
			break;
		sim->memory[k]= number;
		sim_d->memory[k]= number;
		k++;	
	}
	
	fclose(in_file);
	/*for(int x = 0;x<16384;x++){
		printf("%d ",sim->memory[x]);
	}*/
	
	sw = strtol(argv[1],NULL,10);
	if(sw == 4){
		while(!sim->end_flag){
			WB_p1(sim);
			WB_p2(sim);
			Mem4_p1(sim);
			Mem4_p2(sim);
			Mem3_p1(sim);
			Mem3_p2(sim);
			Mem2_p1(sim);
			Mem2_p2(sim);
			Mem1_p1(sim);
			Mem1_p2(sim);
			EXb2_p1(sim);
			EXb2_p2(sim);
			EXb1_p1(sim);
			EXb1_p2(sim);
			EXa_p1(sim);
			EXa_p2(sim);
			ID_p1(sim);
			ID_p2(sim);
			IF_p1(sim);
			IF_p2(sim);
			sim->cc += 1;
		}
		memory_out_0(sim);
		sim->ins_sum = sim->set_num+sim->add_num+sim->sub_num+sim->mul_num+sim->div_num+sim->ld_num+sim->st_num+sim->bez_num+sim->bgez_num+sim->blez_num+sim->bgtz_num+sim->bltz_num+sim->ret_num;
		//print_1(sim,argv[2]);
		printf("\n\n>Parallel Pipeline<\n\n\n");
		print_2(sim);
		print_3(sim);
	}
	else if(sw== 5){
		while(!sim_d->end_flag){
			WB_p1_d(sim_d);
			WB_p2_d(sim_d);
			cond_d(sim_d);
			EXa_p1_d(sim_d);
			EXa_p2_d(sim_d);
			EXb2_p1_d(sim_d);
			EXb1_p1_d(sim_d);
			Mem4_d(sim_d);
			Mem3_d(sim_d);
			Mem2_d(sim_d);
			Mem1_d(sim_d);
			ID_p1_d(sim_d);
			ID_p2_d(sim_d);
			IF_p1_d(sim_d);
			IF_p2_d(sim_d);
			sim_d->cc += 1;
		}
		memory_out_1(sim_d);
		sim_d->ins_sum = sim_d->set_num+sim_d->add_num+sim_d->sub_num+sim_d->mul_num+sim_d->div_num+sim_d->ld_num+sim_d->st_num+sim_d->bez_num+sim_d->bgez_num+sim_d->blez_num+sim_d->bgtz_num+sim_d->bltz_num+sim_d->ret_num;
		printf("\n\n>Diversified Pipeline<\n\n");
		//print_1(sim_d,argv[2]);
		print_2(sim_d);
		print_3(sim_d);
	}
	else if(sw==6){
		int a  = judege_in(sim_d);
		filter_input(sim_d,a);
		while(!sim_d->end_flag){
			WB_p1_d(sim_d);
			WB_p2_d(sim_d);
			cond_d(sim_d);
			EXa_p1_d(sim_d);
			EXa_p2_d(sim_d);
			EXb2_p1_d(sim_d);
			EXb1_p1_d(sim_d);
			Mem4_d(sim_d);
			Mem3_d(sim_d);
			Mem2_d(sim_d);
			Mem1_d(sim_d);
			ID_p1_d(sim_d);
			ID_p2_d(sim_d);
			IF_p1_d(sim_d);
			IF_p2_d(sim_d);
			sim_d->cc += 1;
		}
		memory_out_2(sim_d);
		
		sim_d->ins_sum = sim_d->set_num+sim_d->add_num+sim_d->sub_num+sim_d->mul_num+sim_d->div_num+sim_d->ld_num+sim_d->st_num+sim_d->bez_num+sim_d->bgez_num+sim_d->blez_num+sim_d->bgtz_num+sim_d->bltz_num+sim_d->ret_num;
		printf("\n\n>Dynamic pipeline<\n\n\n");
		
		print_2(sim_d);
		if(!a){
			print_3(sim_d);
		}
		else print_3_d(sim_d);
	}
	
}



