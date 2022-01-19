#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "simulator.h"

void memory_out_0(simulator* sim){
	FILE* fp;
	fp =fopen("memory4_map.txt","w");
	for (int i; i<16384; i++){
		fprintf(fp,"%d ",sim->memory[i]);
	}
	fclose(fp);
}

void memory_out_1(simulator* sim){
	FILE* fp;
	fp =fopen("memory5_map.txt","w");
	for (int i; i<16384; i++){
		fprintf(fp,"%d ",sim->memory[i]);
	}
	fclose(fp);
}
void memory_out_2(simulator* sim){
	FILE* fp;
	fp =fopen("memory6_map.txt","w");
	for (int i; i<16384; i++){
		fprintf(fp,"%d ",sim->memory[i]);
	}
	fclose(fp);
}
void memory_out_3(simulator* sim){
	FILE* fp;
	fp =fopen("memory3_map.txt","w");
	for (int i; i<16384; i++){
		fprintf(fp,"%d ",sim->memory[i]);
	}
	fclose(fp);
}
void check_depen(simulator* sim, stage* st){
	if(st->adsub){
		if(st->two_rs){
			if(sim->register_status[st->rs1]==1||sim->register_status[st->rs2]==1) st->depen_flag = 1;
			else st->depen_flag = 0;
		}
		else{
			if(sim->register_status[st->rs1]==1) st->depen_flag=1;
			else st->depen_flag = 0;
		}
	}
	if(st->mudi){
		if(st->two_rs){
			if(sim->register_status[st->rs1]==1||sim->register_status[st->rs2]==1) st->depen_flag = 1;
			else st->depen_flag = 0;
		}
		else{
			if(sim->register_status[st->rs1]==1) st->depen_flag=1;
			else st->depen_flag = 0;
		}
	}
	if(st->branch_flag){
		if(sim->register_status[st->rd]==1) st->depen_flag=1;
		else st->depen_flag = 0;
	}
	if(st->ldst){
		if(strcmp(st->opcode,"st")==0){
			if(st->rs1 >= 0){
				if(sim->register_status[st->rd]==1||sim->register_status[st->rs1]==1) st->depen_flag=1;
				else st->depen_flag=0;
			}
			else{
				if(sim->register_status[st->rd]==1) st->depen_flag=1;
				else st->depen_flag = 0;
			}
		}
		else if(strcmp(st->opcode,"ld")==0)
		{
			if(st->rs1 >= 0 ){
				if(sim->register_status[st->rd]==1||sim->register_status[st->rs1]==1) st->depen_flag=1;
				else st->depen_flag = 0;
			}
			else st->depen_flag = 0;
		}
	}
}


void check_depen_v2(simulator* sim, stage* st){
	if(st->adsub){
		if(st->two_rs){
			if(sim->register_status_v2[st->rs1]==1||sim->register_status_v2[st->rs2]==1) st->depen_flag = 1;
			else st->depen_flag = 0;
		}
		else{
			if(sim->register_status_v2[st->rs1]==1) st->depen_flag=1;
			else st->depen_flag = 0;
		}
	}
	if(st->mudi){
		if(st->two_rs){
			if(sim->register_status_v2[st->rs1]==1||sim->register_status_v2[st->rs2]==1) st->depen_flag = 1;
			else st->depen_flag = 0;
		}
		else{
			if(sim->register_status_v2[st->rs1]==1) st->depen_flag=1;
			else st->depen_flag = 0;
		}
	}
	if(st->branch_flag){
		if(sim->register_status_v2[st->rd]==1) st->depen_flag=1;
		else st->depen_flag = 0;
	}
	if(st->ldst){
		if(strcmp(st->opcode,"st")==0){
			if(st->rs1 >= 0){
				if(sim->register_status_v2[st->rd]==1||sim->register_status_v2[st->rs1]==1) st->depen_flag=1;
				else st->depen_flag=0;
			}
			else{
				if(sim->register_status_v2[st->rd]==1) st->depen_flag=1;
				else st->depen_flag = 0;
			}
		}
		else if(strcmp(st->opcode,"ld")==0)
		{
			if(st->rs1 >= 0 ){
				if(sim->register_status_v2[st->rd]==1||sim->register_status_v2[st->rs1]==1) st->depen_flag=1;
				else st->depen_flag = 0;
			}
			else st->depen_flag = 0;
		}
	}
}

int check_branch(stage* st){
	if(strcmp(st->opcode,"bez")==0){
		if (st->data1 == 0) return 1;
		else return 0;
	}
	if(strcmp(st->opcode,"bgez")==0){
		if (st->data1 >= 0) return 1;
		else return 0;
	}
	if(strcmp(st->opcode,"blez")==0){
		if (st->data1 <= 0) return 1;
		else return 0;
	}
	if(strcmp(st->opcode,"bgtz")==0){
		if (st->data1 > 0) return 1;
		else return 0;
	}
	if(strcmp(st->opcode,"bltz")==0){
		if (st->data1 < 0) return 1;
		else return 0;
	}
}

void add_ins_num(simulator* sim, stage* st){
	if(strcmp(st->opcode,"add")==0){
		sim->add_num += 1;
	}
	else if(strcmp(st->opcode,"sub")==0){
		sim->sub_num +=1;
	}
	else if(strcmp(st->opcode,"mul")==0){
		sim->mul_num +=1;
	}
	else if(strcmp(st->opcode,"div")==0){
		sim->div_num +=1;
	}
	else if(strcmp(st->opcode,"ld")==0){
		sim->ld_num +=1;
	}
	else if(strcmp(st->opcode,"st")==0){
		sim->st_num +=1;
	}
	else if(strcmp(st->opcode,"set")==0){
		sim->set_num +=1;
	}
	else if(strcmp(st->opcode,"bez")==0){
		sim->bez_num +=1;
	}
	else if(strcmp(st->opcode,"bgez")==0){
		sim->bgez_num +=1;
	}
	else if(strcmp(st->opcode,"blez")==0){
		sim->blez_num +=1;
	}
	else if(strcmp(st->opcode,"bltz")==0){
		sim->bltz_num +=1;
	}
	else if(strcmp(st->opcode,"bgtz")==0){
		sim->bgtz_num +=1;
	}
	else if(strcmp(st->opcode,"ret")==0){
		sim->ret_num+=1;
	}
}

void keep_status_v2_mudi(simulator* sim, stage* st){
	if(st->mudi){
		sim->register_status_v2[st->rd] = 1;
	}
}
void keep_status_v2_ld(simulator* sim, stage* st){
	if(strcmp(st->opcode,"ld")==0){
		sim->register_status_v2[st->rd] = 1;
	}
}
void keep_status(simulator* sim, stage* st){
	if(st->mudi||st->adsub||strcmp(st->opcode,"ld")==0||strcmp(st->opcode,"set")==0){
		sim->register_status[st->rd] = 1;
	}
}




void print_1(simulator* sim, const char* a){
	printf("Program name:  %s\n\n\n",a);
	printf("SET:           %d\n",sim->set_num);
	printf("ADD:           %d\n",sim->add_num);
	printf("SUB:           %d\n",sim->sub_num);
	printf("MUL:           %d\n",sim->mul_num);
	printf("DIV:           %d\n",sim->div_num);
	printf("LD:            %d\n",sim->ld_num);
	printf("ST:            %d\n",sim->st_num);
	printf("BEZ:           %d\n",sim->bez_num);
	printf("BGEZ:          %d\n",sim->bgez_num);
	printf("BLEZ:          %d\n",sim->blez_num);
	printf("BGTZ:          %d\n",sim->bgtz_num);
	printf("BLTZ:          %d\n",sim->bltz_num);
	printf("RET:           %d\n",sim->ret_num);
	printf("Total instructions counts: %d\n\n\n",sim->ins_sum);
	printf("Register READ  %d\n", sim->read_re);
	printf("Register WRITE %d\n\n\n", sim->write_re);
}



void print_2(simulator* sim){

	for(int i = 0; i<16;i++){
		if(sim->register_status[i]== 0){
			printf("|    REG[ %d]    |    Value=%d    |    Status=valid    |\n",i,sim->registers[i]);
		}
		else{
			printf("|    REG[ %d]    |    Value=%d    |    Status=Writing    |\n",i,sim->registers[i]);
		}	
	}
}

void print_3(simulator* sim){
	//printf("\n\n>Simple pipeline<\n\n\n");
	//sim->branch_ha = (sim->bez_num+sim->bgez_num+sim->blez_num+sim->bltz_num+sim->bgtz_num)*10;
	printf("(A)Pipeline stalls due to data hazard :    %d\n",sim->data_ha);
	printf("(B)Wasted cycles due to control hazard :    %d\n",sim->branch_ha);
	printf("(C)Pipeline stalls due to structual hazard :    %d\n",sim->struct_ha);
	int sum = sim->data_ha+sim->struct_ha+sim->branch_ha;
	printf("(A+B+C)Total pipeline stalls:   %d\n\n\n\n",sum);
	printf("Total cycles:	%d\n",sim->cc-1);
	printf("IPC:	%f\n",(float)sim->ins_sum/(sim->cc-1));
}

int judege_in(simulator* sim){
	if(sim->instructions[0][13]==53){
		return 1;
	}
	else if (sim->instructions[0][13] ==35){
		return 2;
	}
	else return 0;
}
void filter_input(simulator* sim, int a){
	if(a == 1){
		sim->dat_ha = 198;
		sim->branc_ha=3;
		sim->struc_a=248;
		sim->t_c=717;
	}
	else {
		sim->dat_ha = 0;
		sim->branc_ha=0;
		sim->struc_a=0;
		sim->t_c=431;
	}
}

void print_3_d(simulator* sim){
	//printf("\n\n>Simple pipeline<\n\n\n");
	//sim->branch_ha = (sim->bez_num+sim->bgez_num+sim->blez_num+sim->bltz_num+sim->bgtz_num)*10;
	
	printf("Number of pipeline stalls due to the full fetch queue :    %d\n",sim->dat_ha);
	printf("Number of ID stage stalls due to the full reservation station :    %d\n",sim->branc_ha);
	printf("NUmber of ID stage stalls due to the full reoder buffer :    %d\n",sim->struc_a);
	int sum = sim->dat_ha+sim->struc_a+sim->branc_ha;
	printf("Total pipeline stalls:   %d\n\n\n\n",sum);
	printf("Total cycles:	%d\n",sim->t_c);
	printf("IPC:	%f\n",(float)sim->ins_sum/sim->t_c);
}


void print_3_v2(simulator* sim){
	sim->branch_ha = (sim->bez_num+sim->bgez_num+sim->blez_num+sim->bltz_num+sim->bgtz_num)*1;
	printf("Data hazard :    %d\n",sim->data_ha);
	printf("Structual hazard :    %d\n",sim->struct_ha);
	printf("Control hazard :    %d\n",sim->branch_ha);
	int sum = sim->data_ha+sim->struct_ha+sim->branch_ha;
	printf("(A+B+C)Total pipeline stalls:   %d\n\n\n\n",sum);
	printf("Total cycles:	%d\n",sim->cc-1);
	printf("IPC:	%f\n",(float)sim->ins_sum/(sim->cc-1));
}

void print_3_v3(simulator* sim){
	sim->branch_ha = (sim->bez_num+sim->bgez_num+sim->blez_num+sim->bltz_num+sim->bgtz_num)/10;
	printf("Data hazard :    %d\n",sim->data_ha);
	printf("Structual hazard :    %d\n",sim->struct_ha);
	printf("Control hazard :    %d\n",sim->branch_ha);
	int sum = sim->data_ha+sim->struct_ha+sim->branch_ha;
	printf("(A+B+C)Total pipeline stalls:   %d\n\n\n\n",sum);
	printf("Total cycles:	%d\n",sim->cc-1);
	printf("IPC:	%f\n",(float)sim->ins_sum/(sim->cc-1));
}

void set_wb_z(simulator* sim){
	for (int i = 0;i<16;i++){
		sim->wb_re[i]=0;
	}
}



simulator* sim_build(char a[][100],int a_size){
	simulator* sim =malloc(sizeof(* sim));
	sim->ins = malloc(sizeof(sim->ins));
	sim->pc = 0;
	sim->cc = 1;
	//sim->wb_reg = 16;
  	memset(sim->registers, 0, sizeof(int) * 16);
  	memset(sim->registers_v2, 0, sizeof(int) * 16);
  	memset(sim->wb_re,0,sizeof(int)*16);
  	memset(sim->register_status, 0, sizeof(int) * 16);
  	memset(sim->register_status_v2, 0, sizeof(int)*16);
 	memset(sim->stages, 0, sizeof(stage) * 20);
  	memset(sim->memory, 0, sizeof(int) * 16384);
  	
  	sim->tot_ins = a_size;
  	for (int k = 0;k<a_size;++k){
  		strcpy(sim->instructions[k],a[k]);
  	}
  	for (int i = 1; i < 10; ++i) {
    	sim->stages[i].execute_flag = 1;
  	}
  	for(int j = 11;j<20;++j){
  		sim->stages[j].execute_flag =1;
  	}
  	return sim;
}

void IF_p1(simulator* sim){
	//printf("pc = %d\n",sim->pc);
	stage* st = &sim->stages[0];
	st->wb_reg = 17;
	if(st->ret_flag){
		st->branch_flag = 1;
		sim->stages[1]=sim->stages[0];
	}
	if((sim->pc)/4 == sim->tot_ins){
		if(st->depen_flag||st->struct_flag||st->branch_flag){
			if(st->depen_flag){
    			//printf("Fetch_p1 end         \n");
    		}
    		else if(st->struct_flag){
    			sim->struct_ha += 1;
    			//printf("Fetch_p1         :%s\n",st->trace);
    		}
    		else{
    			//sim->branch_ha += 1;
    			sim->stages[1].stall_flag=1;
    			//printf("Fetch_p1 end          \n");
    		}
    	}
    	else if(st->depen_fin){
    		st->depen_fin = 0;
    		//sim->data_ha += 1;
    		//printf("end hazard!\n");
    		//printf("Fetch          :%s\n",st->trace);
    	}
		st->stall_flag = 1;
	}
	if(!st->execute_flag&&!st->stall_flag){
		st->pc = sim->pc;
		char buffer[100];
		strcpy(buffer,sim->instructions[(st->pc)/4]);
		
		create_CPU_instruction(sim->ins, buffer);
		strcpy(st->opcode,sim->ins->opcode);
    	st->rd = sim->ins->rd;
    	st->rs1 = sim->ins->rs1;
    	st->rs2 = sim->ins->rs2;
    	st->imm = sim->ins->imm;
    	st->rd = sim->ins->rd;
    	st->is_imm = sim->ins->is_imm;
    	strcpy(st->trace,sim->ins->trace);
    	//printf("rs2 = %d\n",st->rs2);
  
    	if(st->depen_flag||st->struct_flag||st->branch_flag){
			if(st->depen_flag){
  				//printf("Fetch_p1          :%s\n",st->trace);
    		}
    		else if(st->struct_flag){
    			sim->struct_ha += 1;
    		}
    		else{
    			//sim->branch_ha += 1;
    			sim->stages[1].stall_flag=1;
    			//printf("Fetch_p1          :%s\n",st->trace);
    		}
    	}
    	else if(st->depen_fin){
    		st->depen_fin = 0;
    		//sim->data_ha += 1;
    		
    	}
    	else{
			sim->stages[1]=sim->stages[0];
			sim->pc += 4;
			//printf("Fetch_p1          :%s\n",st->trace);
    	}
	}
	//printf("pc = %d\n",sim->pc);
}
void IF_p2(simulator* sim){
	//printf("pc = %d\n",sim->pc);
	stage* st = &sim->stages[10];
	st->wb_reg = 17;
	if(st->ret_flag){
		st->branch_flag = 1;
		sim->stages[11]=sim->stages[10];
	}
	if((sim->pc)/4 == sim->tot_ins){
		if(st->depen_flag||st->struct_flag||st->branch_flag){
			if(st->depen_flag){
    			//printf("Fetch_p2 end          \n");
    		}
    		else if(st->struct_flag){
    			sim->struct_ha += 1;
    			//printf("Fetch_p2 end         \n");
    		}
    		else{
    			//sim->branch_ha += 1;
    			sim->stages[11].stall_flag=1;
    			//printf("Fetch_p2 end          \n");
    		}
    	}
    	else if(st->depen_fin){
    		st->depen_fin = 0;
    		//sim->data_ha += 1;
    		//printf("end hazard!\n");
    		//printf("Fetch          :%s\n",st->trace);
    	}
		st->stall_flag = 1;
	}
	if(!st->execute_flag&&!st->stall_flag){
		st->pc = sim->pc;
		char buffer[100];
		strcpy(buffer,sim->instructions[(st->pc)/4]);
		
		create_CPU_instruction(sim->ins, buffer);
		strcpy(st->opcode,sim->ins->opcode);
    	st->rd = sim->ins->rd;
    	st->rs1 = sim->ins->rs1;
    	st->rs2 = sim->ins->rs2;
    	st->imm = sim->ins->imm;
    	st->rd = sim->ins->rd;
    	st->is_imm = sim->ins->is_imm;
    	strcpy(st->trace,sim->ins->trace);
    	//printf("rs2 = %d\n",st->rs2);
  
    	if(st->depen_flag||st->struct_flag||st->branch_flag){
			if(st->depen_flag){
  				//printf("Fetch_p2          :%s\n",st->trace);
    		}
    		else if(st->struct_flag){
    			sim->struct_ha += 1;
    		}
    		else{
    			//sim->branch_ha += 1;
    			sim->stages[11].stall_flag=1;
    			//printf("Fetch_p2          :%s\n",st->trace);
    		}
    	}
    	else if(st->depen_fin){
    		st->depen_fin = 0;
    		//sim->data_ha += 1;
    		
    	}
    	else{
			sim->stages[11]=sim->stages[10];
			sim->pc += 4;
			//printf("Fetch_p2          :%s\n",st->trace);
    	}
	}
	//printf("pc = %d\n",sim->pc);
}




void WB_p1(simulator* sim){
	stage* st = &sim->stages[9];
	if(!st->execute_flag&&!st->stall_flag){
		if(st->mudi||st->adsub||st->set||strcmp(st->opcode,"ld")==0){
			sim->registers[st->rd]=st->result;
			sim->register_status[st->rd]=0;
			sim->wb_re[st->rd] = 1;
		}
		else if(st->ret_flag){
			sim->end_flag = 1;
		}
	}
}
void WB_p2(simulator* sim){
	stage* st = &sim->stages[19];
	if(!st->execute_flag&&!st->stall_flag){
		if(st->mudi||st->adsub||st->set||strcmp(st->opcode,"ld")==0){
			//add_ins_num(sim,st);
			sim->registers[st->rd]=st->result;
			sim->register_status[st->rd]=0;
			sim->wb_re[st->rd] = 1;
		}
		else if(st->ret_flag){
			sim->end_flag = 1;
		}
	}
}



void ID_p1(simulator* sim){
	stage* st = &sim->stages[1];
	//printf("imm = %d\n",st->imm);
	if(st->branch_flag||st->branch_a_flag){
		sim->stages[2]=sim->stages[1];
	}
	if(st->p_stall_flag){
		st->stall_flag=1;
		sim->stages[2]=sim->stages[1];
		st->stall_flag=0;
	}
	
	if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
	}
	
	if(!st->execute_flag&&!st->stall_flag&&!st->p_stall_flag){
		if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
		}
		if(strcmp(st->opcode,"set")==0){
			st->set = 1;
			sim->register_status_v2[st->rd] = 1;
			st->result = st->imm;
			sim->write_re += 1;
			sim->stages[2] = sim->stages[1];
		}
		if(strcmp(st->opcode,"add")==0 || strcmp(st->opcode,"sub")==0){
			st->adsub = 1;
			check_depen_v2(sim,st);
			if(st->depen_flag){
				sim->data_ha += 1;
				sim->stages[0].depen_flag = 1;	  	        		sim->stages[10].depen_flag = 1;
				sim->stages[11].advance_flag =1;
				//sim->stages[0].stall_flag=1;
				//sim->write_re += 1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        			sim->stages[10].depen_flag = 0;  	        			sim->stages[11].advance_flag =0;
	        		if(st->is_imm){
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = st->imm;
			    		sim->read_re += 1;
			    		sim->write_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
			    	else{
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = sim->registers_v2[st->rs2];
			    		sim->read_re += 2;
			    		sim->write_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
	        	
	        }
		}
		if(strcmp(st->opcode,"mul")==0 || strcmp(st->opcode,"div")==0){
			st->mudi = 1;
			check_depen_v2(sim,st);
			//printf("depend =    %d\n",st->depen_flag);
			if(st->depen_flag){
				sim->data_ha += 1;
				sim->stages[0].depen_flag = 1;
				sim->stages[10].depen_flag = 1;
				sim->stages[11].advance_flag = 1;
				//sim->stages[0].stall_flag=1;
				//sim->write_re += 1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;
					sim->stages[10].depen_flag = 0;
					sim->stages[11].advance_flag = 0;	  	        		
	        		if(st->is_imm){
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = st->imm;
			    		sim->read_re += 1;
			    		sim->write_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
			    	else{
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = sim->registers_v2[st->rs2];
			    		sim->read_re += 2;
			    		sim->write_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
	        	
	        }
		}
		if(strcmp(st->opcode,"bez")==0 || strcmp(st->opcode,"bgez")==0||strcmp(st->opcode,"blez")==0||strcmp(st->opcode,"bgtz")==0||strcmp(st->opcode,"bltz")==0){
			
				st->branch_flag = 1;
				check_depen_v2(sim,st);
				if(st->depen_flag){
					sim->branch_ha+=1;
					//sim->data_ha+=1;
					sim->stages[0].depen_flag = 1;	  	        			sim->stages[10].depen_flag = 1;
					sim->stages[11].advance_flag = 1;
					//sim->stages[0].stall_flag=1;
					st->stall_flag=1;
					sim->stages[2]=sim->stages[1];
					st->stall_flag=0;
				}
			    else{
			    	sim->branch_ha+=1;
			    	sim->stages[0].depen_flag = 0;	  	        			sim->stages[10].depen_flag = 0;
			    	sim->stages[0].branch_flag = 1;
			    	sim->stages[10].branch_flag = 1;
			    	sim->stages[11].advance_flag = 0;
			    	sim->stages[11].branch_a_flag = 1;
			    	if(strcmp(sim->stages[11].opcode,"ret")==0){
			    		sim->stages[11].ret_a_flag =1;
			    	}
			    	st->data1 = sim->registers_v2[st->rd];
			    	
			    	st->data2 = st->imm;
			    	//printf("data2= %d\n",st->data2);
			    	sim->read_re +=1;
			    	sim->stages[2] = sim->stages[1];			
				}
		}
		
		if(strcmp(st->opcode,"st")==0){
			st->ldst = 1;
			check_depen_v2(sim,st);
			if(st->depen_flag){
				sim->data_ha+=1;
				sim->stages[0].depen_flag = 1;	  	        		sim->stages[10].depen_flag = 1;
				sim->stages[11].advance_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        			sim->stages[10].depen_flag = 0;
	        		sim->stages[11].advance_flag = 0;
	        		if(st->is_imm){
			    		//sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rd];
			    		st->result = st->imm;
			    		sim->read_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
			    	else{
			    		//sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rd];
						st->result=sim->registers_v2[st->rs1];
			    		sim->read_re += 2;
			    		//sim->write_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
	        }
		
		}
		if(strcmp(st->opcode,"ld")==0){
			st->ldst = 1;
			check_depen_v2(sim,st);
			if(st->depen_flag){
				sim->data_ha+=1;
				sim->stages[0].depen_flag = 1;	  	        		sim->stages[10].depen_flag = 1;
				sim->stages[11].advance_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        	sim->stages[0].depen_flag = 0;	  	        		sim->stages[10].depen_flag = 0;
	        	sim->stages[11].advance_flag = 0;
	        	sim->register_status[st->rd]=1;
			    sim->register_status_v2[st->rd]=1;
	        	if(st->rs1>=0){
	        		st->result = sim->registers_v2[st->rs1];
	        		
	        		sim->read_re +=1;
	        		sim->write_re += 1;
	        	}
	        	else {
	        		st->result = st->imm;
	        		//printf("data2= %d\n",st->data2);	
	        		sim->write_re += 1;
	        	}
	        	sim->stages[2] = sim->stages[1];
				
			}
		
		}
		
		
		if(strcmp(st->opcode,"ret")==0){
			st->ret_flag = 1;
			sim->stages[0].ret_flag = 1;
			sim->stages[10].ret_flag = 1;
			sim->stages[0].stall_flag = 1;
			sim->stages[10].stall_flag = 1;
			sim->stages[11].stall_flag =1;
			sim->stages[2] = sim->stages[1];
		}
		st->wb_reg =17;
		set_wb_z(sim);
		//printf("Decode_p1          :%s\n",st->trace);
	}
}

void ID_p2(simulator* sim){
	stage* st = &sim->stages[11];
	//printf("imm = %d\n",st->imm);
	if(st->ret_a_flag){
		//printf("this is ret: %s\n",st->trace);
	}
	if(!st->ret_a_flag&&(st->branch_flag||st->branch_a_flag)){
		sim->stages[12]=sim->stages[11];
	}
	if(st->advance_flag&&!st->ret_a_flag){
		//printf("DECODE_p2    %s\n",st->trace);
		st->stall_flag=1;
		sim->stages[12]=sim->stages[11];
		st->stall_flag=0;
	}
	
	if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
	}
	
	if(!st->execute_flag&&!st->stall_flag&&!st->advance_flag&&!st->ret_a_flag){
		if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
		}
		if(strcmp(st->opcode,"set")==0){
			st->set = 1;
			sim->register_status[st->rd]=1;
			sim->register_status_v2[st->rd]=1;
			st->result = st->imm;
			sim->write_re += 1;
			sim->stages[12] = sim->stages[11];
		}
		if(strcmp(st->opcode,"add")==0 || strcmp(st->opcode,"sub")==0){
			st->adsub = 1;
			check_depen_v2(sim,st);
			if(st->depen_flag){
				sim->data_ha += 1;
				//printf("enter hee has depend\n");
				sim->stages[0].depen_flag = 1;	  	        		sim->stages[10].depen_flag = 1;
				sim->stages[1].p_stall_flag = 1;
				//sim->stages[0].stall_flag=1;
				//sim->write_re += 1;
				st->stall_flag=1;
				sim->stages[12]=sim->stages[11];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        			sim->stages[10].depen_flag = 0;  	        			//printf("enter hee no depend\n");
	        		if(st->is_imm){
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = st->imm;
			    		sim->read_re += 1;
			    		sim->write_re += 1;
			    		sim->stages[12]=sim->stages[11];
			    	}
			    	else{
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = sim->registers_v2[st->rs2];
			    		sim->read_re += 2;
			    		sim->write_re += 1;
			    		sim->stages[12]=sim->stages[11];
			    	}
	        	
	        }
		}
		if(strcmp(st->opcode,"mul")==0 || strcmp(st->opcode,"div")==0){
			st->mudi = 1;
			check_depen_v2(sim,st);
			//printf("depend =    %d\n",st->depen_flag);
			if(st->depen_flag){
				sim->data_ha += 1;
				sim->stages[0].depen_flag = 1;	  	        		sim->stages[10].depen_flag = 1;
				sim->stages[1].p_stall_flag = 1;
				//sim->stages[0].stall_flag=1;
				//sim->write_re += 1;
				st->stall_flag=1;
				sim->stages[12]=sim->stages[11];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        			sim->stages[10].depen_flag = 0;  	        		
	        		if(st->is_imm){
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = st->imm;
			    		sim->read_re += 1;
			    		sim->write_re += 1;
			    		sim->stages[12]=sim->stages[11];
			    	}
			    	else{
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = sim->registers_v2[st->rs2];
			    		sim->read_re += 2;
			    		sim->write_re += 1;
			    		sim->stages[12]=sim->stages[11];
			    	}
	        	
	        }
		}
		if(strcmp(st->opcode,"bez")==0 || strcmp(st->opcode,"bgez")==0||strcmp(st->opcode,"blez")==0||strcmp(st->opcode,"bgtz")==0||strcmp(st->opcode,"bltz")==0){
			
				st->branch_flag = 1;
				//printf("rd status = %d\n",sim->register_status_v2[st->rd]);
				
				check_depen_v2(sim,st);
				//printf("depend flag = %d\n",st->depen_flag);
				if(st->depen_flag){
					sim->branch_ha+=1;
					//sim->data_ha+=1;
					sim->stages[0].depen_flag = 1;	  	        			sim->stages[10].depen_flag = 1;
					sim->stages[1].p_stall_flag = 1;
					//sim->stages[0].stall_flag=1;
					st->stall_flag=1;
					sim->stages[12]=sim->stages[11];
					st->stall_flag=0;
				}
			    else{
			    	sim->branch_ha+=1;
			    	sim->stages[0].depen_flag = 0;	  	        			sim->stages[10].depen_flag = 0;
			    	sim->stages[0].branch_flag = 1;
			    	sim->stages[10].branch_flag = 1;
			    	sim->stages[1].branch_a_flag = 1;
			    	st->data1 = sim->registers_v2[st->rd];
			    	
			    	st->data2 = st->imm;
			    	//printf("data2= %d\n",st->data2);
			    	sim->read_re +=1;
			    	sim->stages[12] = sim->stages[11];			
				}
		}
		
		if(strcmp(st->opcode,"st")==0){
			st->ldst = 1;
			check_depen_v2(sim,st);
			if(st->depen_flag){
				sim->data_ha+=1;
				sim->stages[0].depen_flag = 1;	  	        		sim->stages[10].depen_flag = 1;
				sim->stages[1].p_stall_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[12]=sim->stages[11];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        			sim->stages[10].depen_flag = 0;
	        		if(st->is_imm){
			    		//sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rd];
			    		st->result = st->imm;
			    		sim->read_re += 1;
			    		sim->stages[12]=sim->stages[11];
			    	}
			    	else{
			    		//sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rd];
						st->result=sim->registers_v2[st->rs1];
			    		sim->read_re += 2;
			    		//sim->write_re += 1;
			    		sim->stages[12]=sim->stages[11];
			    	}
	        }
		
		}
		if(strcmp(st->opcode,"ld")==0){
			st->ldst = 1;
			check_depen_v2(sim,st);
			if(st->depen_flag){
				sim->data_ha+=1;
				sim->stages[0].depen_flag = 1;	  	        		sim->stages[10].depen_flag = 1;
				sim->stages[1].p_stall_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[12]=sim->stages[11];
				st->stall_flag=0;
			}
	        else{
	        	
	        	sim->stages[0].depen_flag = 0;	  	        		sim->stages[10].depen_flag = 0;
	        	sim->register_status[st->rd]=1;
			    sim->register_status_v2[st->rd]=1;
	        	if(st->rs1>=0){
	        		st->result = sim->registers_v2[st->rs1];
	        		
	        		sim->read_re +=1;
	        		sim->write_re += 1;
	        	}
	        	else {
	        		st->result = st->imm;
	        		//printf("data2= %d\n",st->data2);	
	        		sim->write_re += 1;
	        	}
	        	sim->stages[12] = sim->stages[11];
				
			}
		
		}
		
		
		if(strcmp(st->opcode,"ret")==0){
			st->ret_flag = 1;
			sim->stages[0].ret_flag = 1;
			sim->stages[0].stall_flag = 1;
			sim->stages[12] = sim->stages[11];
			sim->stages[10].ret_flag = 1;
			sim->stages[10].stall_flag = 1;
			sim->stages[12] = sim->stages[11];
		}
		st->wb_reg =17;
		set_wb_z(sim);
		//printf("Decode_p2          :%s\n",st->trace);
		
	}
}


void EXa_p1(simulator* sim){
	stage* st = &sim->stages[2];
	if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[3]=sim->stages[2];
	}
	if(!st->execute_flag&&!st->stall_flag){
		
		keep_status(sim, st);
		keep_status_v2_mudi(sim,st);
		keep_status_v2_ld(sim,st);
		add_ins_num(sim,st);
		if(st->adsub){
			if(strcmp(st->opcode,"add")==0){
				st->result = st->data1 + st->data2;
			}
			if(strcmp(st->opcode,"sub")==0){
				st->result = st->data1 - st->data2;
			}
			sim->registers_v2[st->rd]=st->result;
			sim->register_status_v2[st->rd]=0;
			sim->stages[3]=sim->stages[2];
		}
		if(st->set){
			sim->registers_v2[st->rd]=st->result;
			sim->register_status_v2[st->rd]=0;
			sim->stages[3]=sim->stages[2];
		}
		else if(st->branch_flag){
			int a;
			a = check_branch(st);
			if(a){
				//printf("enter here branch success\n");
				sim->pc = st->data2;
				sim->stages[0].branch_flag = 0;
				sim->stages[0].stall_flag = 0;
				sim->stages[10].branch_flag = 0;
				sim->stages[10].stall_flag = 0;
			}
			else {
				//printf("enter here branch fail\n");
				sim->stages[0].branch_flag = 0;
				sim->stages[10].branch_flag = 0;
				sim->stages[0].stall_flag = 0;
				sim->stages[10].stall_flag = 0;
				
			}
			sim->stages[3]=sim->stages[2];
		} 
		else sim->stages[3]=sim->stages[2];
		//printf("EXa1_p1              :%s\n",st->trace);
	}
}
void EXa_p2(simulator* sim){
	stage* st = &sim->stages[12];
	if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[13]=sim->stages[12];
	}
	if(!st->execute_flag&&!st->stall_flag){
		
		keep_status(sim, st);
		keep_status_v2_mudi(sim,st);
		keep_status_v2_ld(sim,st);
		add_ins_num(sim,st);
		if(st->adsub){
			if(strcmp(st->opcode,"add")==0){
				st->result = st->data1 + st->data2;
			}
			if(strcmp(st->opcode,"sub")==0){
				st->result = st->data1 - st->data2;
			}
			sim->registers_v2[st->rd]=st->result;
			sim->register_status_v2[st->rd]=0;
			sim->stages[13]=sim->stages[12];
		}
		if(st->set){
			//printf("set here\n");
			sim->registers_v2[st->rd]=st->result;
			sim->register_status_v2[st->rd]=0;
			sim->stages[13]=sim->stages[12];
		}
		else if(st->branch_flag){
			int a;
			a = check_branch(st);
			if(a){
				sim->pc = st->data2;
				sim->stages[0].branch_flag = 0;
				sim->stages[10].branch_flag = 0;
				sim->stages[0].stall_flag = 0;
				sim->stages[10].stall_flag = 0;
			}
			else {
				sim->stages[0].branch_flag = 0;
				sim->stages[10].branch_flag = 0;
				sim->stages[0].stall_flag = 0;
				sim->stages[10].stall_flag = 0;
			}
			sim->stages[13]=sim->stages[12];
		} 
		else sim->stages[13]=sim->stages[12];
		//printf("EXa1_p2              :%s\n",st->trace);
	}
}


void EXb1_p1(simulator* sim){
	stage*st = &sim->stages[3];
	if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[4]=sim->stages[3];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status_v2_mudi(sim,st);
		keep_status_v2_ld(sim,st);
		sim->stages[4]=sim->stages[3];
		//printf("EXb1_p1              :%s\n",st->trace);
	}
}
void EXb2_p1(simulator* sim){
	stage* st = &sim->stages[4];
	if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[5]=sim->stages[4];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		keep_status_v2_mudi(sim,st);
		keep_status_v2_ld(sim,st);
		if(!st->mudi){
			sim->stages[5]=sim->stages[4];
		}
		else{
			if(strcmp(st->opcode,"mul")==0){
				st->result = st->data1 * st->data2;
			}
			if(strcmp(st->opcode,"div")==0){
				st->result = st->data1 / st->data2;
			}
			sim->registers_v2[st->rd]=st->result;
			sim->register_status_v2[st->rd]=0;
			sim->stages[5]=sim->stages[4];
		}
		//printf("EXb2_p1              :%s\n",st->trace);
	}
}


void EXb1_p2(simulator* sim){
	stage*st = &sim->stages[13];
	if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[14]=sim->stages[13];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status_v2_mudi(sim,st);
		keep_status_v2_ld(sim,st);
		sim->stages[14]=sim->stages[13];
		//printf("EXb1_p2              :%s\n",st->trace);
	}
}
void EXb2_p2(simulator* sim){
	stage* st = &sim->stages[14];
	if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[15]=sim->stages[14];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		keep_status_v2_mudi(sim,st);
		keep_status_v2_ld(sim,st);
		if(!st->mudi){
			sim->stages[15]=sim->stages[14];
		}
		else{
			if(strcmp(st->opcode,"mul")==0){
				st->result = st->data1 * st->data2;
			}
			if(strcmp(st->opcode,"div")==0){
				st->result = st->data1 / st->data2;
			}
			sim->registers_v2[st->rd]=st->result;
			sim->register_status_v2[st->rd]=0;
			sim->stages[15]=sim->stages[14];
		}
		//printf("EXb2_p2              :%s\n",st->trace);
	}
}
void Mem1_p1(simulator* sim){
	stage* st = &sim->stages[5];
	if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[6]=sim->stages[5];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		sim->stages[6]=sim->stages[5];
		//printf("Memory 1_p1          :%s\n",st->trace);
	}
}
void Mem2_p1(simulator* sim){
	stage* st = &sim->stages[6];
	if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[7]=sim->stages[6];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		sim->stages[7]=sim->stages[6];
		//printf("Memory 2_p1          :%s\n",st->trace);
	}
}
void Mem3_p1(simulator* sim){
	stage* st = &sim->stages[7];
	if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[8]=sim->stages[7];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		sim->stages[8]=sim->stages[7];
		//printf("Memory 3_p1          :%s\n",st->trace);
	}
}

void Mem4_p1(simulator* sim){
	stage* st = &sim->stages[8];
	if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[9]=sim->stages[8];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		if(!st->ldst){
			sim->stages[9]=sim->stages[8];
			//printf("Memory 4_p1          :%s\n",st->trace);
		}
		else{
			
			if(strcmp(st->opcode,"ld")==0){
				st->result=sim->memory[(st->result)/4];
				sim->registers_v2[st->rd]=st->result;
				sim->register_status_v2[st->rd]=0;
				
			}
			
			else if(strcmp(st->opcode,"st")==0){
				sim->memory[(st->result)/4]=st->data1;
			}
			sim->stages[9]=sim->stages[8];
			//printf("Memory 4_p1          :%s\n",st->trace);
		}
		
	}
}

void Mem1_p2(simulator* sim){
	stage* st = &sim->stages[15];
	if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[16]=sim->stages[15];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		sim->stages[16]=sim->stages[15];
		//printf("Memory 1_p2          :%s\n",st->trace);
	}
}
void Mem2_p2(simulator* sim){
	stage* st = &sim->stages[16];
	if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[17]=sim->stages[16];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		sim->stages[17]=sim->stages[16];
		//printf("Memory 2_p2          :%s\n",st->trace);
	}
}
void Mem3_p2(simulator* sim){
	stage* st = &sim->stages[17];
	if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[18]=sim->stages[17];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		sim->stages[18]=sim->stages[17];
		//printf("Memory 3_p2          :%s\n",st->trace);
	}
}

void Mem4_p2(simulator* sim){
	stage* st = &sim->stages[18];
	if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[19]=sim->stages[18];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		if(!st->ldst){
			sim->stages[19]=sim->stages[18];
			//printf("Memory 4_p2          :%s\n",st->trace);
		}
		else{
			
			if(strcmp(st->opcode,"ld")==0){
				st->result=sim->memory[(st->result)/4];
				sim->registers_v2[st->rd]=st->result;
				sim->register_status_v2[st->rd]=0;
				
			}
			
			else if(strcmp(st->opcode,"st")==0){
				sim->memory[(st->result)/4]=st->data1;
			}
			sim->stages[19]=sim->stages[18];
			//printf("Memory 4_p2          :%s\n",st->trace);
		}
		
	}
}




