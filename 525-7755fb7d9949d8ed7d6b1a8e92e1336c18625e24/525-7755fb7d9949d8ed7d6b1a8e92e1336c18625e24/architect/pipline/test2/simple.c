#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "simulator.h"

void memory_out_0(simulator* sim){
	FILE* fp;
	fp =fopen("memory0_map.txt","w");
	for (int i; i<16384; i++){
		fprintf(fp,"%d ",sim->memory[i]);
	}
	fclose(fp);
}

void memory_out_1(simulator* sim){
	FILE* fp;
	fp =fopen("memory1_map.txt","w");
	for (int i; i<16384; i++){
		fprintf(fp,"%d ",sim->memory[i]);
	}
	fclose(fp);
}
void memory_out_2(simulator* sim){
	FILE* fp;
	fp =fopen("memory2_map.txt","w");
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
	printf("\n\n>Simple pipeline<\n\n\n");
	sim->branch_ha = (sim->bez_num+sim->bgez_num+sim->blez_num+sim->bltz_num+sim->bgtz_num)*10;
	printf("Data hazard :    %d\n",sim->data_ha);
	printf("Structual hazard :    %d\n",sim->struct_ha);
	printf("Control hazard :    %d\n",sim->branch_ha);
	int sum = sim->data_ha+sim->struct_ha+sim->branch_ha;
	printf("(A+B+C)Total pipeline stalls:   %d\n\n\n\n",sum);
	printf("Total cycles:	%d\n",sim->cc-1);
	printf("IPC:	%f\n",(float)sim->ins_sum/(sim->cc-1));
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
 	memset(sim->stages, 0, sizeof(stage) * 10);
  	memset(sim->memory, 0, sizeof(int) * 16384);
  	
  	sim->tot_ins = a_size;
  	for (int k = 0;k<a_size;++k){
  		strcpy(sim->instructions[k],a[k]);
  	}
  	for (int i = 1; i < 10; ++i) {
    	sim->stages[i].execute_flag = 1;
  	}
  	return sim;
}

void IF(simulator* sim){

	stage* st = &sim->stages[0];
	st->wb_reg = 17;
	if(st->ret_flag){
		st->branch_flag = 1;
		sim->stages[1]=sim->stages[0];
	}
	if((sim->pc)/4 == sim->tot_ins){
		if(st->depen_flag||st->struct_flag||st->branch_flag){
			if(st->depen_flag){
    			//printf("Fetch          :%s\n",st->trace);
    		}
    		else if(st->struct_flag){
    			sim->struct_ha += 1;
    			//printf("Fetch          :%s\n",st->trace);
    		}
    		else{
    			//sim->branch_ha += 1;
    			sim->stages[1].stall_flag=1;
    			//printf("Fetch          :%s\n",st->trace);
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
  
    		}
    		else if(st->struct_flag){
    			sim->struct_ha += 1;
    		}
    		else{
    			//sim->branch_ha += 1;
    			sim->stages[1].stall_flag=1;
    		}
    	}
    	else if(st->depen_fin){
    		st->depen_fin = 0;
    		//sim->data_ha += 1;
    		
    	}
    	else{
			sim->stages[1]=sim->stages[0];
			sim->pc += 4;
    	}
	}
}


void ID(simulator* sim){
	stage* st = &sim->stages[1];
	//printf("imm = %d\n",st->imm);
	if(st->branch_flag){
		sim->stages[2]=sim->stages[1];
	}

	
	
	if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
	}
	
	if(!st->execute_flag&&!st->stall_flag){
		if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
		}
		if(strcmp(st->opcode,"set")==0){
			st->set = 1;
			sim->register_status[st->rd] = 1;
			st->result = st->imm;
			sim->write_re += 1;
			sim->stages[2] = sim->stages[1];
		}
		if(strcmp(st->opcode,"add")==0 || strcmp(st->opcode,"sub")==0){
			st->adsub = 1;
			check_depen(sim,st);
			if(st->depen_flag){
				sim->data_ha += 1;
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	if(sim->wb_re[st->rs1]||sim->wb_re[st->rs2]){
	        			
	        			sim->data_ha +=1;
	        		}
	        	if(sim->stages[0].depen_flag){
	        		//sim->data_ha-=1;
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		st->struct_fin = 1;
	        		//st->struct_flag = 0;
	        		//st->stall_flag=0;
	        		//sim->stages[2]=sim->stages[1];
	        	}
	        	else if(!st->is_imm&&!st->struct_fin){
	        		if(st->struct_flag){
	        			sim->stages[0].struct_flag=0;
	        			st->struct_flag = 0;
	        			st->struct_fin = 1;
	        			st->data2 = sim->registers[st->rs2];
	        			sim->read_re += 1;
	        			sim->write_re += 1;
	        			sim->stages[2]=sim->stages[1];
	        		}
	        		else{
	        		
	        			sim->stages[0].struct_flag = 1;
	        			//sim->stages[0].stall_flag = 1;
	        			st->struct_flag = 1;
	        			st->stall_flag=1;
	        			st->data1=sim->registers[st->rs1];
	        			sim->read_re += 1;
						sim->stages[2]=sim->stages[1];
						st->stall_flag=0;
	        		}
	        	}
	        	else {	  	        		
	        		if(st->is_imm){
			    		sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers[st->rs1];
			    		st->data2 = st->imm;
			    		sim->read_re += 1;
			    		sim->write_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    		
			    	}
			    	else{
			    		sim->register_status[st->rd]=1;
			    		st->struct_fin = 0;
			    		st->data1 = sim->registers[st->rs1];
			    		st->data2 = sim->registers[st->rs2];
			    		sim->read_re += 2;
			    		sim->write_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
	        	}
	        }
		}
		if(strcmp(st->opcode,"mul")==0 || strcmp(st->opcode,"div")==0){
			st->mudi = 1;
			check_depen(sim,st);
			if(st->depen_flag){
				sim->data_ha += 1;
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				//sim->write_re += 1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	if(sim->wb_re[st->rs1]||sim->wb_re[st->rs2]){
	        			
	        			sim->data_ha +=1;
	        		}
	        	if(sim->stages[0].depen_flag){
	        		
	        	
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		//sim->data_ha += 1;
	        		//st->stall_flag =0;
	        		//st->depen_flag = 0;
	        		st->struct_fin = 1;
	        		//st->struct_flag = 0;
	        		//st->stall_flag=0;
	        		//sim->stages[2]=sim->stages[1];
	        	}
	        	/*else if(st->rs1==st->wb_reg||st->rs2==st->wb_reg){
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		sim->data_ha += 1;
	        		sim->ha_test+=1;
	        		//st->stall_flag =0;
	        		//st->depen_flag = 0;
	        		st->struct_fin = 1;
	        	}*/
	        	else if(!st->is_imm&&!st->struct_fin){
	        		if(st->struct_flag){
	        			sim->stages[0].struct_flag=0;
	        			st->struct_flag = 0;
	        			st->struct_fin = 1;
	        			st->data2 = sim->registers[st->rs2];
	        			sim->read_re += 1;
	        			sim->write_re += 1;
	        			sim->stages[2]=sim->stages[1];
	        		}
	        		else{
	        			sim->stages[0].struct_flag = 1;
	        			//sim->stages[0].stall_flag = 1;
	        			st->struct_flag = 1;
	        			st->stall_flag=1;
	        			st->data1=sim->registers[st->rs1];
	        			sim->read_re += 1;
						sim->stages[2]=sim->stages[1];
						st->stall_flag=0;
	        		}
	        	}
	        	else{	  	        		
	        		if(st->is_imm){
			    		sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers[st->rs1];
			    		st->data2 = st->imm;
			    		sim->read_re += 1;
			    		sim->write_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
			    	else{
			    		sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers[st->rs1];
			    		st->data2 = sim->registers[st->rs2];
			    		sim->read_re += 2;
			    		sim->write_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
	        	}
	        }
		}
		if(strcmp(st->opcode,"bez")==0 || strcmp(st->opcode,"bgez")==0||strcmp(st->opcode,"blez")==0||strcmp(st->opcode,"bgtz")==0||strcmp(st->opcode,"bez")==0){
		
			st->branch_flag = 1;
			check_depen(sim,st);
			if(st->depen_flag){
				//sim->branch_ha+=1;
			    //sim->data_ha+=1;
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        	if(sim->stages[0].depen_flag){
	        		//sim->data_ha-=1;
	        		//sim->branch_ha+=1;
	        		/*if(sim->wb_re[st->rd]){
	        			sim->data_ha += 1;
	        			sim->ha_test+=1;
	        		}*/
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		st->stall_flag = 1;
	        		sim->stages[2]=sim->stages[1];
	        		st->stall_flag = 0;
	        	}
	        	/*else if(st->rd==st->wb_reg){
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		sim->data_ha += 1;
	        		sim->ha_test+=1;
	        		//st->depen_flag = 0;
	        		st->stall_flag = 1;
	        		sim->stages[2]=sim->stages[1];
	        		st->stall_flag = 0;
	        	}*/
				else{
	        		sim->stages[0].branch_flag = 1;
	        		st->data1 = sim->registers[st->rd];
	        		
	        		st->data2 = st->imm;
	        		//printf("data2= %d\n",st->data2);
	        		sim->read_re +=1;
	        		sim->stages[2] = sim->stages[1];
				}
			}
		
		}
		if(strcmp(st->opcode,"st")==0){
			st->ldst = 1;
			check_depen(sim,st);
			if(st->depen_flag){
				sim->data_ha+=1;
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	if(sim->wb_re[st->rd]||sim->wb_re[st->rs1]){
	        			
	        			sim->data_ha +=1;
	        		}
	        	if(sim->stages[0].depen_flag){
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		//sim->data_ha-=1;
	        		st->struct_fin = 1;
	        		//st->struct_flag = 0;
	        		//st->stall_flag=0;
	        		//sim->stages[2]=sim->stages[1];
	        	}
	        	/*else if(st->rd==st->wb_reg||st->rs1==st->wb_reg){
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		sim->data_ha += 1;
	        		sim->ha_test+=1;
	        		//st->stall_flag =0;
	        		//st->depen_flag = 0;
	        		st->struct_fin = 1;
	        	}*/
	        	else if(!st->is_imm&&!st->struct_fin){
	        		if(st->struct_flag){
	        			sim->stages[0].struct_flag=0;
	        			st->struct_flag = 0;
	        			st->struct_fin = 1;
	        			//st->data2 = sim->registers[st->rs2];
	        			sim->read_re += 1;
	        			st->result=sim->registers[st->rs1];
	        			sim->stages[2]=sim->stages[1];
	        		}
	        		else{
	        			sim->stages[0].struct_flag = 1;
	        			//sim->stages[0].stall_flag = 1;
	        			st->struct_flag = 1;
	        			st->stall_flag=1;
	        			st->data1=sim->registers[st->rd];
	        			sim->read_re += 1;
						sim->stages[2]=sim->stages[1];
						st->stall_flag=0;
	        		}
	        	}
	        	else{	  	        		
	        		if(st->is_imm){
			    		//sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers[st->rd];
			    		st->result = st->imm;
			    		sim->read_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
			    	else{
			    		//sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers[st->rd];
						st->result=sim->registers[st->rs1];
			    		sim->read_re += 2;
			    		//sim->write_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
	        	}
	        }
		
		}
		if(strcmp(st->opcode,"ld")==0){
			st->ldst = 1;
			check_depen(sim,st);
			if(st->depen_flag){
				sim->data_ha+=1;
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	if(sim->wb_re[st->rs1]){
	        			
	        			sim->data_ha +=1;
	        		}
	        	if(sim->stages[0].depen_flag){
	        		//sim->data_ha-=1;
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		st->stall_flag = 1;
	        		sim->stages[2]=sim->stages[1];
	        		st->stall_flag = 0;
	        	}
				else{
	        		if(st->rs1>=0){
	        			st->result = sim->registers[st->rs1];
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
		
		}
		
		
		if(strcmp(st->opcode,"ret")==0){
			st->ret_flag = 1;
			sim->stages[0].ret_flag = 1;
			sim->stages[0].stall_flag = 1;
			sim->stages[2] = sim->stages[1];
		}
		st->wb_reg =17;
		set_wb_z(sim);
	}
}

void EXa(simulator* sim){
	stage* st = &sim->stages[2];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
		sim->stages[3]=sim->stages[2];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		add_ins_num(sim,st);
		if(!st->adsub){
			sim->stages[3]=sim->stages[2];
		}
		else{
			if(strcmp(st->opcode,"add")==0){
				st->result = st->data1 + st->data2;
			}
			if(strcmp(st->opcode,"sub")==0){
				st->result = st->data1 - st->data2;
			}
			sim->stages[3]=sim->stages[2];
		}
		//printf("EXa              :%s\n",st->trace);
	}
}


void EXb1(simulator* sim){
	stage*st = &sim->stages[3];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
		sim->stages[4]=sim->stages[3];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		if(!st->branch_flag){
			sim->stages[4]=sim->stages[3];
			//printf("EXb1              :%s\n",st->trace);
		}
		else{
			int a;
			a = check_branch(st);
			if(a){
				sim->pc = st->data2;
				sim->stages[0].branch_flag = 0;
				sim->stages[0].stall_flag = 0;
			}
			else {
				sim->stages[0].branch_flag = 0;
			}
			sim->stages[4]=sim->stages[3];
			//printf("EXb1              :%s\n",st->trace);
		}
	}
}
void EXb2(simulator* sim){
	stage* st = &sim->stages[4];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
		sim->stages[5]=sim->stages[4];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
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
			sim->stages[5]=sim->stages[4];
		}
	}
}


void Mem1(simulator* sim){
	stage* st = &sim->stages[5];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
		sim->stages[6]=sim->stages[5];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		sim->stages[6]=sim->stages[5];
		
	}
}
void Mem2(simulator* sim){
	stage* st = &sim->stages[6];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
		sim->stages[7]=sim->stages[6];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		sim->stages[7]=sim->stages[6];
	}
}
void Mem3(simulator* sim){
	stage* st = &sim->stages[7];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
		sim->stages[8]=sim->stages[7];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		sim->stages[8]=sim->stages[7];
	}
}

void Mem4(simulator* sim){
	stage* st = &sim->stages[8];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
		sim->stages[9]=sim->stages[8];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		if(!st->ldst){
			sim->stages[9]=sim->stages[8];
		}
		else{
			
			if(strcmp(st->opcode,"ld")==0){
				st->result=sim->memory[(st->result)/4];
			}
			
			else if(strcmp(st->opcode,"st")==0){
				sim->memory[(st->result)/4]=st->data1;
			}
			sim->stages[9]=sim->stages[8];
		}
	}
}
void WB(simulator* sim){
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

void ID_v1(simulator* sim){
	stage* st = &sim->stages[1];
	if(st->branch_flag){
		sim->stages[2]=sim->stages[1];
	}
	
	
	if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
	}
	
	if(!st->execute_flag&&!st->stall_flag){
		if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
		}
		if(strcmp(st->opcode,"set")==0){
			st->set = 1;
			sim->register_status[st->rd] = 1;
			st->result = st->imm;
			sim->write_re += 1;
			sim->stages[2] = sim->stages[1];
		}
		if(strcmp(st->opcode,"add")==0 || strcmp(st->opcode,"sub")==0){
			st->adsub = 1;
			check_depen(sim,st);
			//printf("depend =    %d\n",st->depen_flag);
			if(st->depen_flag){
				sim->data_ha += 1;
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	if(!st->is_imm&&!sim->stages[0].depen_flag){
	        		if(st->struct_flag){
	        			sim->stages[0].struct_flag=0;
	        			st->struct_flag = 0;
	        			st->struct_fin = 1;
	        			st->data2 = sim->registers[st->rs2];
	        			sim->read_re += 1;
	        			sim->write_re += 1;
	        			sim->stages[2]=sim->stages[1];
	        		}
	        		else{
	        		
	        			sim->stages[0].struct_flag = 1;
	        			//sim->stages[0].stall_flag = 1;
	        			st->struct_flag = 1;
	        			st->stall_flag=1;
	        			st->data1=sim->registers[st->rs1];
	        			sim->read_re += 1;
						sim->stages[2]=sim->stages[1];
						st->stall_flag=0;
	        		}
	        	}
	        	else {	
	        		sim->stages[0].depen_flag = 0;  	        		
	        		if(st->is_imm){
			    		sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers[st->rs1];
			    		st->data2 = st->imm;
			    		sim->read_re += 1;
			    		sim->write_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
			    	else{
			    		sim->register_status[st->rd]=1;
			    		st->struct_fin = 0;
			    		st->data1 = sim->registers[st->rs1];
			    		st->data2 = sim->registers[st->rs2];
			    		sim->read_re += 2;
			    		sim->write_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
	        	}
	        }
		}
		if(strcmp(st->opcode,"mul")==0 || strcmp(st->opcode,"div")==0){
			st->mudi = 1;
			check_depen(sim,st);
			//printf("depend =    %d\n",st->depen_flag);
			if(st->depen_flag){
				sim->data_ha += 1;
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				//sim->write_re += 1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        	if(!st->is_imm&&!sim->stages[0].depen_flag){
	        		if(st->struct_flag){
	        			sim->stages[0].struct_flag=0;
	        			st->struct_flag = 0;
	        			st->struct_fin = 1;
	        			st->data2 = sim->registers[st->rs2];
	        			sim->read_re += 1;
	        			sim->write_re += 1;
	        			sim->stages[2]=sim->stages[1];
	        		}
	        		else{
	        			sim->stages[0].struct_flag = 1;
	        			//sim->stages[0].stall_flag = 1;
	        			st->struct_flag = 1;
	        			st->stall_flag=1;
	        			st->data1=sim->registers[st->rs1];
	        			sim->read_re += 1;
						sim->stages[2]=sim->stages[1];
						st->stall_flag=0;
	        		}
	        	}
	        	else{
	        		sim->stages[0].depen_flag = 0;	  	        		
	        		if(st->is_imm){
			    		sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers[st->rs1];
			    		st->data2 = st->imm;
			    		sim->read_re += 1;
			    		sim->write_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
			    	else{
			    		sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers[st->rs1];
			    		st->data2 = sim->registers[st->rs2];
			    		sim->read_re += 2;
			    		sim->write_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
	        	}
	        }
		}
		if(strcmp(st->opcode,"bez")==0 || strcmp(st->opcode,"bgez")==0||strcmp(st->opcode,"blez")==0||strcmp(st->opcode,"bgtz")==0||strcmp(st->opcode,"bez")==0){
		
			st->branch_flag = 1;
			check_depen(sim,st);
			if(st->depen_flag){
				//sim->branch_ha+=1;
			    //sim->data_ha+=1;
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        	sim->stages[0].depen_flag = 0;
	        	sim->stages[0].branch_flag = 1;
	        	st->data1 = sim->registers[st->rd];
	        		
	        	st->data2 = st->imm;
	        	//printf("data2= %d\n",st->data2);
	        	sim->read_re +=1;
	        	sim->stages[2] = sim->stages[1];
				
			}
		
		}
		
		if(strcmp(st->opcode,"st")==0){
			st->ldst = 1;
			check_depen(sim,st);
			if(st->depen_flag){
				sim->data_ha+=1;
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        	if(!st->is_imm&&!sim->stages[0].depen_flag){
	        		if(st->struct_flag){
	        			sim->stages[0].struct_flag=0;
	        			st->struct_flag = 0;
	        			st->struct_fin = 1;
	        			//st->data2 = sim->registers[st->rs2];
	        			sim->read_re += 1;
	        			st->result=sim->registers[st->rs1];
	        			sim->stages[2]=sim->stages[1];
	        		}
	        		else{
	        			sim->stages[0].struct_flag = 1;
	        			//sim->stages[0].stall_flag = 1;
	        			st->struct_flag = 1;
	        			st->stall_flag=1;
	        			st->data1=sim->registers[st->rd];
	        			sim->read_re += 1;
						sim->stages[2]=sim->stages[1];
						st->stall_flag=0;
	        		}
	        	}
	        	else{
	        		sim->stages[0].depen_flag = 0;	  	        		
	        		if(st->is_imm){
			    		//sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers[st->rd];
			    		st->result = st->imm;
			    		sim->read_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
			    	else{
			    		//sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers[st->rd];
						st->result=sim->registers[st->rs1];
			    		sim->read_re += 2;
			    		//sim->write_re += 1;
			    		sim->stages[2]=sim->stages[1];
			    	}
	        	}
	        }
		
		}
		if(strcmp(st->opcode,"ld")==0){
			st->ldst = 1;
			check_depen(sim,st);
			if(st->depen_flag){
				sim->data_ha+=1;
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        	sim->stages[0].depen_flag=0;
	        	/*else if(st->rd==st->wb_reg||st->rs1==st->wb_reg){
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		sim->data_ha += 1;
	        		sim->ha_test+=1;
	        		//st->stall_flag =0;
	        		//st->depen_flag = 0;
	        		st->struct_fin = 1;
	        	}*/
				
	        	if(st->rs1>=0){
	        		st->result = sim->registers[st->rs1];
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
			sim->stages[0].stall_flag = 1;
			sim->stages[2] = sim->stages[1];
		}
		st->wb_reg =17;
		set_wb_z(sim);
	}
}

void EXa_v1(simulator* sim){
	stage* st = &sim->stages[2];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
		sim->stages[3]=sim->stages[2];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		add_ins_num(sim,st);
		if(st->adsub){
			if(strcmp(st->opcode,"add")==0){
				st->result = st->data1 + st->data2;
			}
			if(strcmp(st->opcode,"sub")==0){
				st->result = st->data1 - st->data2;
			}
			sim->stages[3]=sim->stages[2];
		}
		else if(st->branch_flag){
			int a;
			a = check_branch(st);
			if(a){
				sim->pc = st->data2;
				sim->stages[0].branch_flag = 0;
				sim->stages[0].stall_flag = 0;
			}
			else {
				sim->stages[0].branch_flag = 0;
			}
			sim->stages[3]=sim->stages[2];
		} 
		else sim->stages[3]=sim->stages[2];
	}
}


void EXb1_v1(simulator* sim){
	stage*st = &sim->stages[3];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
		sim->stages[4]=sim->stages[3];
	}
	if(!st->execute_flag&&!st->stall_flag){
		
		sim->stages[4]=sim->stages[3];
	}
}

void print_3_v1(simulator* sim){
	sim->branch_ha = (sim->bez_num+sim->bgez_num+sim->blez_num+sim->bltz_num+sim->bgtz_num)*8;
	printf("Data hazard :    %d\n",sim->data_ha);
	printf("Structual hazard :    %d\n",sim->struct_ha);
	printf("Control hazard :    %d\n",sim->branch_ha);
	int sum = sim->data_ha+sim->struct_ha+sim->branch_ha;
	printf("(A+B+C)Total pipeline stalls:   %d\n\n\n\n",sum);
	printf("Total cycles:	%d\n",sim->cc-1);
	printf("IPC:	%f\n",(float)sim->ins_sum/(sim->cc-1));
	printf("Ha_test    %d\n",sim->ha_test);
}


void ID_v2(simulator* sim){
	stage* st = &sim->stages[1];
	//printf("imm = %d\n",st->imm);
	if(st->branch_flag){
		sim->stages[2]=sim->stages[1];
	}
	
	
	if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
	}
	
	if(!st->execute_flag&&!st->stall_flag){
		if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
		}
		if(strcmp(st->opcode,"set")==0){
			st->set = 1;
			sim->register_status[st->rd] = 1;
			st->result = st->imm;
			sim->write_re += 1;
			sim->stages[2] = sim->stages[1];
		}
		if(strcmp(st->opcode,"add")==0 || strcmp(st->opcode,"sub")==0){
			st->adsub = 1;
			check_depen_v2(sim,st);
			if(st->depen_flag){
				sim->data_ha += 1;
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				//sim->write_re += 1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        		
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
				//sim->stages[0].stall_flag=1;
				//sim->write_re += 1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        		
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
		if(strcmp(st->opcode,"bez")==0 || strcmp(st->opcode,"bgez")==0||strcmp(st->opcode,"blez")==0||strcmp(st->opcode,"bgtz")==0||strcmp(st->opcode,"bez")==0){
			
				st->branch_flag = 1;
				check_depen_v2(sim,st);
				if(st->depen_flag){
					//sim->branch_ha+=1;
					//sim->data_ha+=1;
					sim->stages[0].depen_flag = 1;
					//sim->stages[0].stall_flag=1;
					st->stall_flag=1;
					sim->stages[2]=sim->stages[1];
					st->stall_flag=0;
				}
			    else{
			    	
			    	sim->stages[0].depen_flag = 0;
			    	sim->stages[0].branch_flag = 1;
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
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        		
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
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        	sim->stages[0].depen_flag=0;
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
			sim->stages[0].stall_flag = 1;
			sim->stages[2] = sim->stages[1];
		}
		st->wb_reg =17;
		set_wb_z(sim);
		//printf("imm = %d\n",st->imm);
		//printf("rd = %d\n",st->rd);
	}
}

void EXa_v2(simulator* sim){
	stage* st = &sim->stages[2];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
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
				sim->pc = st->data2;
				sim->stages[0].branch_flag = 0;
				sim->stages[0].stall_flag = 0;
			}
			else {
				sim->stages[0].branch_flag = 0;
			}
			sim->stages[3]=sim->stages[2];
		} 
		else sim->stages[3]=sim->stages[2];
	}
}


void EXb1_v2(simulator* sim){
	stage*st = &sim->stages[3];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
		sim->stages[4]=sim->stages[3];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status_v2_mudi(sim,st);
		keep_status_v2_ld(sim,st);
		sim->stages[4]=sim->stages[3];
		//printf("EXb1              :%s\n",st->trace);
	}
}
void EXb2_v2(simulator* sim){
	stage* st = &sim->stages[4];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
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
		//printf("EXb2              :%s\n",st->trace);
	}
}
void Mem1_v2(simulator* sim){
	stage* st = &sim->stages[5];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
		sim->stages[6]=sim->stages[5];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		sim->stages[6]=sim->stages[5];
		//printf("Memory 1          :%s\n",st->trace);
	}
}
void Mem2_v2(simulator* sim){
	stage* st = &sim->stages[6];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
		sim->stages[7]=sim->stages[6];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		sim->stages[7]=sim->stages[6];
		//printf("Memory 2          :%s\n",st->trace);
	}
}
void Mem3_v2(simulator* sim){
	stage* st = &sim->stages[7];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
		sim->stages[8]=sim->stages[7];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		sim->stages[8]=sim->stages[7];
		//printf("Memory 3          :%s\n",st->trace);
	}
}

void Mem4_v2(simulator* sim){
	stage* st = &sim->stages[8];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
		sim->stages[9]=sim->stages[8];
	}
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		if(!st->ldst){
			sim->stages[9]=sim->stages[8];
			//printf("Memory 4          :%s\n",st->trace);
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
			//printf("Memory 4          :%s\n",st->trace);
		}
		
	}
}

void ID_v3(simulator* sim){
	stage* st = &sim->stages[1];
	//printf("imm = %d\n",st->imm);
	if(st->branch_flag){
		sim->stages[2]=sim->stages[1];
	}
	
	
	if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
	}
	
	if(!st->execute_flag&&!st->stall_flag){
		if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
		}
		if(strcmp(st->opcode,"set")==0){
			st->set = 1;
			sim->register_status[st->rd] = 1;
			st->result = st->imm;
			sim->write_re += 1;
			sim->stages[2] = sim->stages[1];
		}
		if(strcmp(st->opcode,"add")==0 || strcmp(st->opcode,"sub")==0){
			st->adsub = 1;
			check_depen_v2(sim,st);
			if(st->depen_flag){
				sim->data_ha += 1;
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				//sim->write_re += 1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        		
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
				//sim->stages[0].stall_flag=1;
				//sim->write_re += 1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        		
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
		if(strcmp(st->opcode,"bez")==0 || strcmp(st->opcode,"bgez")==0||strcmp(st->opcode,"blez")==0||strcmp(st->opcode,"bgtz")==0||strcmp(st->opcode,"bez")==0){
				
				check_depen_v2(sim,st);
				if(st->depen_flag){
					sim->stages[0].depen_flag = 1;
					st->stall_flag=1;
					sim->stages[2]=sim->stages[1];
					st->stall_flag=0;
				}
			    else{
			    	if(sim->branch_prediction<=8){
						sim->branch_prediction+=1;
						sim->read_re +=1;
						st->data1 = sim->registers_v2[st->rd];
						st->data2 = st->imm;
						int a;
						a = check_branch(st);
						if(a){
							sim->pc = st->data2;
							sim->stages[0].branch_flag = 0;
						}
						sim->stages[2] = sim->stages[1];
					}
					else{
						
						sim->branch_prediction = 0;
						st->branch_flag = 1;
						sim->stages[0].depen_flag = 0;
						sim->stages[0].branch_flag = 1;
						st->data1 = sim->registers_v2[st->rd];
						
						st->data2 = st->imm;
						sim->read_re +=1;
						sim->stages[2] = sim->stages[1];
						
					}
				}
			}
			
		
		if(strcmp(st->opcode,"st")==0){
			st->ldst = 1;
			check_depen_v2(sim,st);
			if(st->depen_flag){
				sim->data_ha+=1;
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        		
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
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	
	        	sim->stages[0].depen_flag=0;
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
			sim->stages[0].stall_flag = 1;
			sim->stages[2] = sim->stages[1];
		}
		st->wb_reg =17;
		set_wb_z(sim);
		//printf("Decode          :%s\n",st->trace);
	}
}



