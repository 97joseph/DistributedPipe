#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "simulator.h"


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
		else{
			if(st->rs1 >= 0 ){
				if(sim->register_status[st->rd]==1||sim->register_status[st->rs1]==1) st->depen_flag=1;
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





void keep_status(simulator* sim, stage* st){
	if(st->mudi||st->adsub||strcmp(st->opcode,"ld")==0){
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
	int sum = sim->set_num+sim->add_num+sim->sub_num+sim->mul_num+sim->div_num+sim->ld_num+sim->st_num+sim->bez_num+sim->bgez_num+sim->blez_num+sim->bgtz_num+sim->bltz_num+sim->ret_num;
	printf("Total instructions counts: %d\n\n\n",sum);
	printf("Register READ  %d\n", sim->read_re);
	printf("Register WRITE %d\n", sim->write_re);
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





simulator* sim_build(char a[][100],int a_size){
	simulator* sim =malloc(sizeof(* sim));
	sim->ins = malloc(sizeof(sim->ins));
	sim->pc = 0;
	sim->cc = 1;
	//sim->wb_reg = 16;
  	memset(sim->registers, 0, sizeof(int) * 16);
  	memset(sim->register_status, 0, sizeof(int) * 16);
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

	printf("pc = %d\n",sim->pc);
	stage* st = &sim->stages[0];
	st->wb_reg = 17;
	if(st->ret_flag){
		st->branch_flag = 1;
		sim->stages[1]=sim->stages[0];
	}
	printf("success\n");
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
    			sim->branch_ha += 1;
    			sim->stages[1].stall_flag=1;
    			//printf("Fetch          :%s\n",st->trace);
    		}
    	}
    	else if(st->depen_fin){
    		st->depen_fin = 0;
    		sim->data_ha += 1;
    		//printf("end hazard!\n");
    		//printf("Fetch          :%s\n",st->trace);
    	}
		st->stall_flag = 1;
	}
	printf("success\n");
	if(!st->execute_flag&&!st->stall_flag){
		st->pc = sim->pc;
		char* buffer = malloc(sizeof(char)*100);
		//printf("%s\n",buffer);
		strcpy(buffer,sim->instructions[(st->pc)/4]);
		//printf("%s\n",buffer);
		printf("buffer= %s\n",buffer);
		
		create_CPU_instruction(sim->ins, buffer);
		printf("success\n");
		strcpy(st->opcode,sim->ins->opcode);
    	st->rd = sim->ins->rd;
    	st->rs1 = sim->ins->rs1;
    	st->rs2 = sim->ins->rs2;
    	st->imm = sim->ins->imm;
    	st->rd = sim->ins->rd;
    	st->is_imm = sim->ins->is_imm;
    	strcpy(st->trace,sim->ins->trace);
    	printf("st->depen_flag = %d\n",st->depen_flag);
    	printf("st->struct_flag  = %d\n",st->struct_flag);
    	printf("st->branch_flag = %d\n",st->branch_flag);
    	//printf("rs2 = %d\n",st->rs2);
  
    	if(st->depen_flag||st->struct_flag||st->branch_flag){
			if(st->depen_flag){
    			printf("Fetch          :%s\n",st->trace);
    		}
    		else if(st->struct_flag){
    			sim->struct_ha += 1;
    			printf("Fetch          :%s\n",st->trace);
    		}
    		else{
    			sim->branch_ha += 1;
    			sim->stages[1].stall_flag=1;
    			printf("Fetch          :%s\n",st->trace);
    		}
    	}
    	else if(st->depen_fin){
    		st->depen_fin = 0;
    		//sim->data_ha += 1;
    		printf("end hazard!\n");
    		printf("Fetch          :%s\n",st->trace);
    	}
    	else{
			sim->stages[1]=sim->stages[0];
			sim->pc += 4;
			printf("Fetch          :%s\n",st->trace);
    	//printf("rd = %d\n",st->rd);
    	}
	}
}


void ID(simulator* sim){
	stage* st = &sim->stages[1];
	//printf("imm = %d\n",st->imm);
	if(st->branch_flag){
		sim->stages[2]=sim->stages[1];
	}
	printf("is_imm = %d\n",st->is_imm);
	
	
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
			sim->write_re+=1;
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
	        	else if(st->rs1==st->wb_reg||st->rs2==st->wb_reg){
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		sim->data_ha += 1;
	        		//st->stall_flag =0;
	        		//st->depen_flag = 0;
	        		st->struct_fin = 1;
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
			    		printf("data1  = %d\n",st->data1);
			    		printf("data2 = %d\n",st->data2);
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
				sim->write_re += 1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
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
	        	else if(st->rs1==st->wb_reg||st->rs2==st->wb_reg){
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		sim->data_ha += 1;
	        		//st->stall_flag =0;
	        		//st->depen_flag = 0;
	        		st->struct_fin = 1;
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
				sim->branch_ha+=1;
				sim->stages[0].depen_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[2]=sim->stages[1];
				st->stall_flag=0;
			}
	        else{
	        	if(sim->stages[0].depen_flag){
	        		sim->branch_ha+=1;
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		st->stall_flag = 1;
	        		sim->stages[2]=sim->stages[1];
	        		st->stall_flag = 0;
	        	}
	        	else if(st->rd==st->wb_reg){
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		sim->data_ha += 1;
					
	        		//st->stall_flag =0;
	        		//st->depen_flag = 0;
	        		st->stall_flag = 1;
	        		sim->stages[2]=sim->stages[1];
	        		st->stall_flag = 0;
	        	}
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
	        	else if(st->rd==st->wb_reg||st->rs1==st->wb_reg){
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		sim->data_ha += 1;
	        		//st->stall_flag =0;
	        		//st->depen_flag = 0;
	        		st->struct_fin = 1;
	        	}
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
			    		//sim->write_re += 1;
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
	        	if(sim->stages[0].depen_flag){
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		st->stall_flag = 1;
	        		sim->stages[2]=sim->stages[1];
	        		st->stall_flag = 0;
	        	}
	        	else if(st->rd==st->wb_reg||st->rs1==st->wb_reg){
	        		sim->stages[0].depen_fin = 1;
	        		sim->stages[0].depen_flag = 0;
	        		sim->data_ha += 1;
	        		//st->stall_flag =0;
	        		//st->depen_flag = 0;
	        		st->struct_fin = 1;
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
		printf("Decode          :%s\n",st->trace);
		//printf("imm = %d\n",st->imm);
		//printf("rd = %d\n",st->rd);
	}
}

void EXa(simulator* sim){
	stage* st = &sim->stages[2];
	if(st->depen_flag||st->struct_flag||st->branch_flag){
		sim->stages[3]=sim->stages[2];
	}
	if(!st->execute_flag&&!st->stall_flag){
		printf("reg 15 = %d\n",sim->registers[15]);
		keep_status(sim, st);
		printf("reg 15 = %d\n",sim->registers[15]);
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
		printf("EXa              :%s\n",st->trace);
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
			printf("EXb1              :%s\n",st->trace);
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
			printf("EXb1              :%s\n",st->trace);
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
		printf("EXb2              :%s\n",st->trace);
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
		printf("Memory 1          :%s\n",st->trace);
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
		printf("Memory 2          :%s\n",st->trace);
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
		printf("Memory 3          :%s\n",st->trace);
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
			printf("Memory 4          :%s\n",st->trace);
		}
		else{
			if(strcmp(st->opcode,"ld")==0){
				sim->registers[st->rd]=sim->memory[(st->result)/4];
			}
			else if(strcmp(st->opcode,"st")==0){
				sim->memory[(st->result)/4]=st->data1;
			}
			sim->stages[9]=sim->stages[8];
			printf("Memory 4          :%s\n",st->trace);
		}
	}
}
void WB(simulator* sim){
	printf("sucess\n");
	stage* st = &sim->stages[9];
	if(!st->execute_flag&&!st->stall_flag){
		if(st->mudi||st->adsub||st->set){
			sim->registers[st->rd]=st->result;
			sim->register_status[st->rd]=0;
			sim->stages[1].wb_reg = st->rd;
			
			printf("Change   rd: %d to   %d\n",st->rd,sim->registers[st->rd]);
		}
		else if(st->ret_flag){
			sim->end_flag = 1;
		}
		//printf("reg 15 = %d\n",sim->registers[15]);
		printf("re_st = %d\n",sim->register_status[st->rd]);
		printf("Writeback          :%s\n",st->trace);
	}
}










