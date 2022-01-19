#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "simulator.h"





void check_waw(simulator* sim, stage* st){
	if(st->adsub){
		if(sim->register_status_v2[st->rd]==1){
			st->depen_flag =1;
		}
	}
	if(st->mudi){
		if(sim->register_status_v2[st->rd]==1){
			st->depen_flag =1;
		}
	}
	if(st->ldst){
		if(strcmp(st->opcode,"ld")==0)
		{
			if(sim->register_status_v2[st->rd]==1){
					st->depen_flag =1;
			}
		}
	}
	if(st->set){
		if(sim->register_status_v2[st->rd]==1){
					st->depen_flag =1;
		}
	}
}



int check_stage(simulator*sim, stage*st){
	if(strcmp(st->opcode,"add")==0){
		st->adsub =1;
	}
	else if(strcmp(st->opcode,"sub")==0){
		st->adsub =1;
	}
	else if(strcmp(st->opcode,"mul")==0){
		st->mudi =1;
	}
	else if(strcmp(st->opcode,"div")==0){
		st->mudi =1;
	}
	else if(strcmp(st->opcode,"ld")==0){
		st->ldst =1;
	}
	else if(strcmp(st->opcode,"st")==0){
		st->ldst=1;
	}
	else if(strcmp(st->opcode,"set")==0){
		st->set =1;
	}
	else if(strcmp(st->opcode,"bez")==0){
		st->branch_flag=1;
	}
	else if(strcmp(st->opcode,"bgez")==0){
		st->branch_flag=1;
	}
	else if(strcmp(st->opcode,"blez")==0){
		st->branch_flag=1;
	}
	else if(strcmp(st->opcode,"bltz")==0){
		st->branch_flag=1;
	}
	else if(strcmp(st->opcode,"bgtz")==0){
		st->branch_flag=1;
	}
	else if(strcmp(st->opcode,"ret")==0){
		st->branch_flag=1;
	}
	if(st->set){
		if(!sim->stages[5].full){
			return 5;
		}
		else if(!sim->stages[6].full){
			return 6;
		}
		else return 100;
	}
	if(st->adsub){
		if(!sim->stages[5].full){
			return 5;
		}
		else if(!sim->stages[6].full){
			return 6;
		}
		else return 100;
	}
	if(st->mudi){
		if(!sim->stages[7].full){
			return 7;
		}
		else return 100;
	}
	if(st->ldst){
		if(!sim->stages[9].full){
			return 9;
		}
		else return 100;
	}
	if(st->branch_flag){
		if(!sim->stages[4].full){
			return 4;
		}
		else return 100;
	}
}

int check_wb_buffer(simulator*sim, stage*st){
	if (!sim->stages[13].full_wb){
		return 13;
	}
	else if(!sim->stages[14].full_wb){
		return 14;
	}
	else return 100;
}






simulator* sim_build_d(char a[][100],int a_size){
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
  	for(int j = 2;j<16;++j){
  		sim->stages[j].execute_flag =1;
  	}
  	return sim;
}

void IF_p1_d(simulator* sim){
	//printf("pc = %d\n",sim->pc);
	
	stage* st = &sim->stages[0];
	st->wb_reg = 17;
	//printf("bf: %d dt: %d sf: %d fl: %d df: %d\n",st->branch_flag,st->d_stall,st->stall_flag,st->full,st->depen_flag);
	if(st->ret_flag){
		st->branch_flag = 1;
		sim->stages[2]=sim->stages[0];
	}
	if((sim->pc)/4 == sim->tot_ins){
		if(st->depen_flag||st->struct_flag||st->branch_flag||st->depen_f_flag){
			if(st->depen_flag||st->depen_f_flag){
    			//printf("Fetch_p1 end         \n");
    		}
    		else if(st->struct_flag){
    			sim->struct_ha += 1;
    			//printf("Fetch_p1         :%s\n",st->trace);
    		}
    		else{
    			//sim->branch_ha += 1;
    			sim->stages[2].stall_flag=1;
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
  
    	if(st->depen_flag||st->struct_flag||st->branch_flag||st->depen_f_flag){
			if(st->depen_flag||st->depen_f_flag){
  				//printf("Fetch_p1          :%s\n",st->trace);
    		}
    		else if(st->struct_flag){
    			sim->struct_ha += 1;
    		}
    		else{
    			//sim->branch_ha += 1;
    			sim->stages[2].stall_flag=1;
    			//printf("Fetch_p1          :%s\n",st->trace);
    		}
    	}
    	else if(st->depen_fin){
    		st->depen_fin = 0;
    		//sim->data_ha += 1;
    		
    	}
    	else{
			sim->stages[2]=sim->stages[0];
			sim->pc += 4;
			//printf("Fetch_p1          :%s\n",st->trace);
    	}
	}
	//printf("pc = %d\n",sim->pc);
}
void IF_p2_d(simulator* sim){
	//printf("pc = %d\n",sim->pc);
	stage* st = &sim->stages[1];
	st->wb_reg = 17;
	if(st->ret_flag){
		st->branch_flag = 1;
		sim->stages[3]=sim->stages[1];
	}
	if((sim->pc)/4 == sim->tot_ins){
		if(st->depen_flag||st->struct_flag||st->branch_flag||st->depen_f_flag){
			if(st->depen_flag||st->depen_f_flag){
    			//printf("Fetch_p2 end          \n");
    		}
    		else if(st->struct_flag){
    			sim->struct_ha += 1;
    			//printf("Fetch_p2 end         \n");
    		}
    		else{
    			//sim->branch_ha += 1;
    			sim->stages[3].stall_flag=1;
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
  
    	if(st->depen_flag||st->struct_flag||st->branch_flag||st->depen_f_flag){
			if(st->depen_flag||st->depen_f_flag){
  				//printf("Fetch_p2          :%s\n",st->trace);
    		}
    		else if(st->struct_flag){
    			sim->struct_ha += 1;
    		}
    		else{
    			//sim->branch_ha += 1;
    			sim->stages[3].stall_flag=1;
    			//printf("Fetch_p2          :%s\n",st->trace);
    		}
    	}
    	else if(st->depen_fin){
    		st->depen_fin = 0;
    		//sim->data_ha += 1;
    		
    	}
    	else{
			sim->stages[3]=sim->stages[1];
			sim->pc += 4;
			//printf("Fetch_p2          :%s\n",st->trace);
    	}
	}
	//printf("pc = %d\n",sim->pc);
}

void ID_p1_d(simulator* sim){
	stage* st = &sim->stages[2];
	//printf("full = %d",sim->stages[7].full);
	int st_n = check_stage(sim,st);
	//printf("st_n = %d\n",st_n);
	//printf("bf: %d dt: %d sf: %d fl: %d af: %d\n",st->branch_flag,st->d_stall,st->stall_flag,st->full,st->advance_flag);
	if(st_n<50){
		st->d_stall = 0;
		sim->stages[0].depen_f_flag = 0;	  	        		sim->stages[1].depen_f_flag = 0;
	}
	else{
		st->d_stall =1;
		sim->struct_ha +=1;
		sim->stages[0].depen_f_flag = 1;	  	        		sim->stages[1].depen_f_flag = 1;
	}
	//printf("imm = %d\n",st->imm);
	if((st->branch_flag||st->branch_a_flag)&&!st->d_stall){
		sim->stages[st_n]=sim->stages[2];
	}
	if(st->p_stall_flag&&!st->d_stall){
		st->stall_flag=1;
		sim->stages[st_n]=sim->stages[2];
		st->stall_flag=0;
	}
	
	if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
	}
	
	if(!st->execute_flag&&!st->stall_flag&&!st->p_stall_flag&&!st->d_stall){
		if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
		}
		if(strcmp(st->opcode,"set")==0){
			check_waw(sim,st);
			if(st->depen_flag){
				sim->data_ha += 1;
			}
			st->set = 1;
			sim->register_status_v2[st->rd] = 1;
			st->result = st->imm;
			sim->write_re += 1;
			sim->stages[st_n] = sim->stages[2];
			sim->stages[st_n].full = 1;
		}
		if(strcmp(st->opcode,"add")==0 || strcmp(st->opcode,"sub")==0){
			st->adsub = 1;
			check_depen_v2(sim,st);
			check_waw(sim,st);
			//printf("dpen: %d",st->depen_flag);
			if(st->depen_flag){
				sim->data_ha += 1;
				sim->stages[0].depen_flag = 1;	  	        		sim->stages[1].depen_flag = 1;
				sim->stages[3].advance_flag =1;
				//sim->stages[0].stall_flag=1;
				//sim->write_re += 1;
				st->stall_flag=1;
				sim->stages[st_n]=sim->stages[2];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        			sim->stages[1].depen_flag = 0;  	        		sim->stages[3].advance_flag =0;
	        		if(st->is_imm){
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = st->imm;
			    		sim->read_re += 1;
			    		sim->write_re += 1;
			    		sim->stages[st_n]=sim->stages[2];
			    		sim->stages[st_n].full = 1;
			    	}
			    	else{
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = sim->registers_v2[st->rs2];
			    		sim->read_re += 2;
			    		sim->write_re += 1;
			    		sim->stages[st_n]=sim->stages[2];
			    		sim->stages[st_n].full = 1;
			    	}
	        	
	        }
		}
		if(strcmp(st->opcode,"mul")==0 || strcmp(st->opcode,"div")==0){
			st->mudi = 1;
			check_depen_v2(sim,st);
			check_waw(sim,st);
			//printf("depend =    %d\n",st->depen_flag);
			if(st->depen_flag){
				sim->data_ha += 1;
				sim->stages[0].depen_flag = 1;
				sim->stages[1].depen_flag = 1;
				sim->stages[3].advance_flag = 1;
				//sim->stages[0].stall_flag=1;
				//sim->write_re += 1;
				st->stall_flag=1;
				sim->stages[st_n]=sim->stages[2];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;
					sim->stages[1].depen_flag = 0;
					sim->stages[3].advance_flag = 0;	  	        		
	        		if(st->is_imm){
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = st->imm;
			    		sim->read_re += 1;
			    		sim->write_re += 1;
			    		sim->stages[st_n]=sim->stages[2];
			    		sim->stages[st_n].full = 1;
			    		
			    	}
			    	else{
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = sim->registers_v2[st->rs2];
			    		sim->read_re += 2;
			    		sim->write_re += 1;
			    		sim->stages[st_n]=sim->stages[2];
			    		sim->stages[st_n].full = 1;
			    	}
	        	
	        }
		}
		if(strcmp(st->opcode,"bez")==0 || strcmp(st->opcode,"bgez")==0||strcmp(st->opcode,"blez")==0||strcmp(st->opcode,"bgtz")==0||strcmp(st->opcode,"bltz")==0){
			
				st->branch_flag = 1;
				check_depen_v2(sim,st);
				check_waw(sim,st);
				if(st->depen_flag){
					sim->branch_ha+=1;
					sim->stages[0].depen_flag = 1;	  	        			sim->stages[1].depen_flag = 1;
					sim->stages[3].advance_flag = 1;
					//sim->stages[0].stall_flag=1;
					st->stall_flag=1;
					sim->stages[st_n]=sim->stages[2];
					st->stall_flag=0;
				}
			    else{
			    	//printf("enter hee no depend\n");
			    	sim->branch_ha+=1;
			    	sim->stages[0].depen_flag = 0;	  	        			sim->stages[1].depen_flag = 0;
			    	sim->stages[0].branch_flag = 1;
			    	sim->stages[1].branch_flag = 1;
			    	sim->stages[3].advance_flag = 0;
			    	sim->stages[3].branch_a_flag = 1;
			    	if(strcmp(sim->stages[3].opcode,"ret")==0){
			    		sim->stages[3].ret_a_flag =1;
			    	}
			    	st->data1 = sim->registers_v2[st->rd];
			    	
			    	st->data2 = st->imm;
			    	//printf("data2= %d\n",st->data2);
			    	sim->read_re +=1;
			    	sim->stages[st_n] = sim->stages[2];			
			    	sim->stages[st_n].full = 1;
				}
		}
		
		if(strcmp(st->opcode,"st")==0){
			st->ldst = 1;
			check_depen_v2(sim,st);
			//check_waw(sim,st);
			if(st->depen_flag){
				sim->data_ha+=1;
				sim->stages[0].depen_flag = 1;	  	        		sim->stages[1].depen_flag = 1;
				sim->stages[3].advance_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[st_n]=sim->stages[2];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        			sim->stages[1].depen_flag = 0;
	        		sim->stages[3].advance_flag = 0;
	        		if(st->is_imm){
			    		//sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rd];
			    		st->result = st->imm;
			    		sim->read_re += 1;
			    		sim->stages[st_n]=sim->stages[2];
			    		sim->stages[st_n].full = 1;
			    	}
			    	else{
			    		//sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rd];
						st->result=sim->registers_v2[st->rs1];
			    		sim->read_re += 2;
			    		//sim->write_re += 1;
			    		sim->stages[st_n]=sim->stages[2];
			    		sim->stages[st_n].full = 1;
			    	}
	        }
		
		}
		if(strcmp(st->opcode,"ld")==0){
			st->ldst = 1;
			check_depen_v2(sim,st);
			check_waw(sim,st);
			if(st->depen_flag){
				sim->data_ha+=1;
				sim->stages[0].depen_flag = 1;	  	        		sim->stages[1].depen_flag = 1;
				sim->stages[3].advance_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[st_n]=sim->stages[2];
				st->stall_flag=0;
			}
	        else{
	        	
	        	sim->stages[0].depen_flag = 0;	  	        		sim->stages[1].depen_flag = 0;
	        	sim->stages[3].advance_flag = 0;
	        	sim->register_status[st->rd]=1;
			    sim->register_status_v2[st->rd]=1;
	        	if(st->rs1>=0){
	        		st->result = sim->registers_v2[st->rs1];
	        		sim->stages[st_n].full = 1;
	        		sim->read_re +=1;
	        		sim->write_re += 1;
	        	}
	        	else {
	        		st->result = st->imm;
	        		//printf("data2= %d\n",st->data2);	
	        		sim->write_re += 1;
	        	}
	        	sim->stages[st_n] = sim->stages[2];
				sim->stages[st_n].full = 1;
			}
		
		}
		
		
		if(strcmp(st->opcode,"ret")==0){
			st->ret_flag = 1;
			sim->stages[0].ret_flag = 1;
			sim->stages[1].ret_flag = 1;
			sim->stages[3].stall_flag = 1;
			sim->stages[1].stall_flag = 1;
			sim->stages[3].stall_flag =1;
			sim->stages[st_n] = sim->stages[2];
			sim->stages[st_n].full = 1;
		}
		st->wb_reg =17;
		set_wb_z(sim);
		//printf("Decode_p1          :%s\n",st->trace);
	}
}

void ID_p2_d(simulator* sim){
	stage* st = &sim->stages[3];
	//rintf("imm = %d\n",st->imm);
	if(st->ret_a_flag){
		//printf("this is ret: %s\n",st->trace);
	}
	int st_n = check_stage(sim,st);
	//printf("st_n = %d\n",st_n);
	//printf("bf: %d dt: %d sf: %d fl: %d af: %d\n",st->branch_flag,st->d_stall,st->stall_flag,st->full,st->advance_flag);
	if(st_n<50){
		st->d_stall = 0;
		sim->stages[0].depen_f_flag = 0;	  	        		sim->stages[1].depen_f_flag = 0;
	}
	else{
		st->d_stall =1;
		check_depen_v2(sim,st);
		check_waw(sim,st);
		if(st->depen_flag){
			st->depen_flag = 0;
			sim->struct_ha -=1;
			sim->data_ha += 1;
		}
		if(!sim->stages[0].branch_flag&&!sim->stages[0].depen_flag){
			sim->struct_ha +=1;
		}
		//printf("DECODE_p2    %s\n",st->trace);
		sim->stages[0].depen_f_flag = 1;	  	        		sim->stages[1].depen_f_flag = 1;
		sim->stages[2].p_stall_flag =1;
	}
	if(!st->d_stall&&!st->ret_a_flag&&(st->branch_flag||st->branch_a_flag)){
		sim->stages[st_n]=sim->stages[3];
	}
	if(st->advance_flag&&!st->ret_a_flag&&!st->d_stall){
		//printf("DECODE_p2    %s\n",st->trace);
		st->stall_flag=1;
		sim->stages[st_n]=sim->stages[3];
		st->stall_flag=0;
	}
	
	if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
	}
	
	if(!st->execute_flag&&!st->stall_flag&&!st->advance_flag&&!st->ret_a_flag&&!st->d_stall){
		if(st->rs1 >=0 && st->rs2>=0 ){
		st->two_rs = 1;
		}
		if(strcmp(st->opcode,"set")==0){
			st->set = 1;
			check_waw(sim,st);
			if(st->depen_flag){
				sim->data_ha += 1;
			}
			sim->register_status[st->rd]=1;
			sim->register_status_v2[st->rd]=1;
			st->result = st->imm;
			sim->write_re += 1;
			sim->stages[st_n] = sim->stages[3];
			sim->stages[st_n].full = 1;
		}
		if(strcmp(st->opcode,"add")==0 || strcmp(st->opcode,"sub")==0){
			st->adsub = 1;
			check_depen_v2(sim,st);
			check_waw(sim,st);
			if(st->depen_flag){
				sim->data_ha += 1;
				//printf("enter hee has depend\n");
				sim->stages[0].depen_flag = 1;	  	        		sim->stages[1].depen_flag = 1;
				sim->stages[2].p_stall_flag = 1;
				//sim->stages[0].stall_flag=1;
				//sim->write_re += 1;
				st->stall_flag=1;
				sim->stages[st_n]=sim->stages[3];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        			sim->stages[1].depen_flag = 0;  	        		//printf("enter hee no depend\n");
	        		if(st->is_imm){
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = st->imm;
			    		sim->read_re += 1;
			    		sim->write_re += 1;
			    		sim->stages[st_n]=sim->stages[3];
			    		sim->stages[st_n].full = 1;
			    	}
			    	else{
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = sim->registers_v2[st->rs2];
			    		sim->read_re += 2;
			    		sim->write_re += 1;
			    		sim->stages[st_n]=sim->stages[3];
			    		sim->stages[st_n].full = 1;
			    	}
	        	
	        }
		}
		if(strcmp(st->opcode,"mul")==0 || strcmp(st->opcode,"div")==0){
			st->mudi = 1;
			check_depen_v2(sim,st);
			check_waw(sim,st);
			//printf("depend =    %d\n",st->depen_flag);
			if(st->depen_flag){
				sim->data_ha += 1;
				sim->stages[0].depen_flag = 1;	  	        		sim->stages[1].depen_flag = 1;
				sim->stages[2].p_stall_flag = 1;
				//sim->stages[0].stall_flag=1;
				//sim->write_re += 1;
				st->stall_flag=1;
				sim->stages[st_n]=sim->stages[3];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        			sim->stages[1].depen_flag = 0;  	        		
	        		if(st->is_imm){
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = st->imm;
			    		sim->read_re += 1;
			    		sim->write_re += 1;
			    		sim->stages[st_n]=sim->stages[3];
			    		sim->stages[st_n].full = 1;
			    	}
			    	else{
			    		sim->register_status[st->rd]=1;
			    		sim->register_status_v2[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rs1];
			    		st->data2 = sim->registers_v2[st->rs2];
			    		sim->read_re += 2;
			    		sim->write_re += 1;
			    		sim->stages[st_n]=sim->stages[3];
			    		sim->stages[st_n].full = 1;
			    	}
	        	
	        }
		}
		if(strcmp(st->opcode,"bez")==0 || strcmp(st->opcode,"bgez")==0||strcmp(st->opcode,"blez")==0||strcmp(st->opcode,"bgtz")==0||strcmp(st->opcode,"bltz")==0){
			
				st->branch_flag = 1;
				//printf("rd status = %d\n",sim->register_status_v2[st->rd]);
				
				check_depen_v2(sim,st);
				check_waw(sim,st);
				//printf("depend flag = %d\n",st->depen_flag);
				if(st->depen_flag){
					sim->branch_ha+=1;
					//sim->data_ha+=1;
					sim->stages[0].depen_flag = 1;	  	        			sim->stages[1].depen_flag = 1;
					sim->stages[2].p_stall_flag = 1;
					//sim->stages[0].stall_flag=1;
					st->stall_flag=1;
					sim->stages[st_n]=sim->stages[3];
					st->stall_flag=0;
				}
			    else{
			    	sim->branch_ha+=1;
			    	sim->stages[0].depen_flag = 0;	  	        			sim->stages[1].depen_flag = 0;
			    	sim->stages[0].branch_flag = 1;
			    	sim->stages[1].branch_flag = 1;
			    	sim->stages[2].branch_a_flag = 1;
			    	st->data1 = sim->registers_v2[st->rd];
			    	
			    	st->data2 = st->imm;
			    	//printf("data2= %d\n",st->data2);
			    	sim->read_re +=1;
			    	sim->stages[st_n] = sim->stages[3];			
			    	sim->stages[st_n].full = 1;
				}
		}
		
		if(strcmp(st->opcode,"st")==0){
			st->ldst = 1;
			check_depen_v2(sim,st);
			check_waw(sim,st);
			if(st->depen_flag){
				sim->data_ha+=1;
				sim->stages[0].depen_flag = 1;	  	        		sim->stages[1].depen_flag = 1;
				sim->stages[2].p_stall_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[st_n]=sim->stages[3];
				st->stall_flag=0;
			}
	        else{
	        	
	        		sim->stages[0].depen_flag = 0;	  	        			sim->stages[1].depen_flag = 0;
	        		if(st->is_imm){
			    		//sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rd];
			    		st->result = st->imm;
			    		sim->read_re += 1;
			    		sim->stages[st_n]=sim->stages[3];
			    		sim->stages[st_n].full = 1;
			    	}
			    	else{
			    		//sim->register_status[st->rd]=1;
			    		st->data1 = sim->registers_v2[st->rd];
						st->result=sim->registers_v2[st->rs1];
			    		sim->read_re += 2;
			    		//sim->write_re += 1;
			    		sim->stages[st_n]=sim->stages[3];
			    		sim->stages[st_n].full = 1;
			    	}
	        }
		
		}
		if(strcmp(st->opcode,"ld")==0){
			st->ldst = 1;
			check_depen_v2(sim,st);
			check_waw(sim,st);
			if(st->depen_flag){
				sim->data_ha+=1;
				sim->stages[0].depen_flag = 1;	  	        		sim->stages[1].depen_flag = 1;
				sim->stages[2].p_stall_flag = 1;
				//sim->stages[0].stall_flag=1;
				st->stall_flag=1;
				sim->stages[st_n]=sim->stages[3];
				st->stall_flag=0;
			}
	        else{
	        	
	        	sim->stages[0].depen_flag = 0;	  	        		sim->stages[1].depen_flag = 0;
	        	sim->register_status[st->rd]=1;
			    sim->register_status_v2[st->rd]=1;
	        	if(st->rs1>=0){
	        		st->result = sim->registers_v2[st->rs1];
	        		sim->stages[st_n].full = 1;
	        		sim->read_re +=1;
	        		sim->write_re += 1;
	        	}
	        	else {
	        		st->result = st->imm;
	        		//printf("data2= %d\n",st->data2);	
	        		sim->write_re += 1;
	        	}
	        	sim->stages[st_n] = sim->stages[3];
	        	sim->stages[st_n].full = 1;
				
			}
		
		}
		
		
		if(strcmp(st->opcode,"ret")==0){
			st->ret_flag = 1;
			sim->stages[0].ret_flag = 1;
			sim->stages[0].stall_flag = 1;
			sim->stages[st_n] = sim->stages[3];
			sim->stages[1].ret_flag = 1;
			sim->stages[1].stall_flag = 1;
			sim->stages[st_n] = sim->stages[3];
			sim->stages[st_n].full = 1;
		}
		st->wb_reg =17;
		set_wb_z(sim);
		//printf("Decode_p2          :%s\n",st->trace);
		
	}
}

void cond_d(simulator* sim){
	stage* st = &sim->stages[4];
	//printf("ef =%d  st =%d\n",st->execute_flag,st->stall_flag);
	if(!st->execute_flag&&!st->stall_flag){
		keep_status(sim, st);
		keep_status_v2_mudi(sim,st);
		keep_status_v2_ld(sim,st);
		add_ins_num(sim,st);
		//printf("enter hee cond  \n");
		if(st->branch_flag){
			int a;
			a = check_branch(st);
			if(a){
				//printf("enter here branch success\n");
				sim->pc = st->data2;
				sim->stages[0].branch_flag = 0;
				sim->stages[0].stall_flag = 0;
				sim->stages[1].branch_flag = 0;
				sim->stages[1].stall_flag = 0;
				sim->stages[2]=sim->stages[15];
				sim->stages[3]=sim->stages[15];
			}
			else {
				//printf("enter here branch fail\n");
				sim->stages[0].branch_flag = 0;
				sim->stages[1].branch_flag = 0;
				sim->stages[0].stall_flag = 0;
				sim->stages[1].stall_flag = 0;
				
			}
			sim->stages[13]=sim->stages[4];
			st->full =0;
			st->execute_flag = 1;
		} 
		else sim->stages[13]=sim->stages[4];
		sim->stages[13].full_wb = 1;
		st->full = 0;
		st->execute_flag =1;
		//printf("Cond_d              :%s\n",st->trace);
	}
}




void EXa_p1_d(simulator* sim){
	stage* st = &sim->stages[5];
	if(!st->execute_flag&&!st->stall_flag){
		int wb_n = check_wb_buffer(sim,st);
		
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
			sim->stages[wb_n]=sim->stages[5];
		}
		else if(st->set){
			sim->registers_v2[st->rd]=st->result;
			sim->register_status_v2[st->rd]=0;
			sim->stages[wb_n]=sim->stages[5];
		}
		else sim->stages[wb_n]=sim->stages[5];
		sim->stages[wb_n].full_wb = 1;
		st->full = 0;
		st->execute_flag =1;
		//printf("EXa1_p1              :%s\n",st->trace);
		
	}
}
void EXa_p2_d(simulator* sim){
	stage* st = &sim->stages[6];
	
	if(!st->execute_flag&&!st->stall_flag){
		int wb_n = check_wb_buffer(sim,st);
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
			sim->stages[wb_n]=sim->stages[6];
		}
		if(st->set){
			sim->registers_v2[st->rd]=st->result;
			sim->register_status_v2[st->rd]=0;
			sim->stages[wb_n]=sim->stages[6];
		}
		else sim->stages[wb_n]=sim->stages[6];
		sim->stages[wb_n].full_wb = 1;
		st->full = 0;
		st->execute_flag =1;
		//printf("EXa1_p2              :%s\n",st->trace);
	}
}

void EXb1_p1_d(simulator* sim){
	stage*st = &sim->stages[7];
	if(st->back_stall){
		sim->struct_ha += 1;
	}
	if(!st->back_stall){
		if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[8]=sim->stages[7];
		}
	}
	if(!st->execute_flag&&!st->stall_flag&&!st->back_stall){
		add_ins_num(sim,st);
		keep_status_v2_mudi(sim,st);
		keep_status_v2_ld(sim,st);
		sim->stages[8]=sim->stages[7];
		st->full = 0;
		st->execute_flag =1;
		//printf("EXb1_d              :%s\n",st->trace);
	}
}
void EXb2_p1_d(simulator* sim){
	stage* st = &sim->stages[8];
	int wb_n = check_wb_buffer(sim,st);
	if(!st->execute_flag&&!st->stall_flag){
		if(wb_n<50){
			st->back_stall =0;
			sim->stages[7].back_stall = 0;
		
		}
		else {
			st->back_stall = 1;
			sim->stages[7].back_stall =1;
		}
		keep_status(sim, st);
		keep_status_v2_mudi(sim,st);
		keep_status_v2_ld(sim,st);
		
		if(strcmp(st->opcode,"mul")==0){
			st->result = st->data1 * st->data2;
		}
		if(strcmp(st->opcode,"div")==0){
			st->result = st->data1 / st->data2;
		}
		sim->registers_v2[st->rd]=st->result;
		sim->register_status_v2[st->rd]=0;
		if(!st->back_stall){
			sim->stages[wb_n]=sim->stages[8];
			sim->stages[wb_n].full_wb = 1;
			st->full = 0;
			st->execute_flag =1;
			//printf("EXb2_d              :%s\n",st->trace);
		}
	}
}
void Mem1_d(simulator* sim){
	stage* st = &sim->stages[9];
	if(st->back_stall){
		sim->struct_ha +=1;
	}
	if(!st->back_stall){
		if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[10]=sim->stages[9];
		}
	}
	if(!st->execute_flag&&!st->stall_flag&&!st->back_stall){
		add_ins_num(sim,st);
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		
		sim->stages[10]=sim->stages[9];
		st->full = 0;
		st->execute_flag =1;
		//printf("Memory 1_p1          :%s\n",st->trace);
	}
}
void Mem2_d(simulator* sim){
	stage* st = &sim->stages[10];
	if(!st->back_stall){
		sim->stages[9].back_stall=0;
		if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[11]=sim->stages[10];
		}
	}
	if(!st->execute_flag&&!st->stall_flag&&!st->back_stall){
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		sim->stages[11]=sim->stages[10];
		st->full = 0;
		st->execute_flag =1;
		//printf("Memory 2_p1          :%s\n",st->trace);
	}
}
void Mem3_d(simulator* sim){
	stage* st = &sim->stages[11];
	if(!st->back_stall){
		sim->stages[10].back_stall=0;
		if(st->depen_flag||st->struct_flag||st->branch_flag||st->p_stall_flag||st->advance_flag){
		sim->stages[12]=sim->stages[11];
		}
	}
	if(!st->execute_flag&&!st->stall_flag&&!st->back_stall){
		
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		sim->stages[12]=sim->stages[11];
		st->full = 0;
		st->execute_flag =1;
		//printf("Memory 3_p1          :%s\n",st->trace);
	}
}

void Mem4_d(simulator* sim){
	stage* st = &sim->stages[12];
	int wb_n = check_wb_buffer(sim,st);
	if(!st->execute_flag&&!st->stall_flag){
		if(wb_n<50){
			st->back_stall =0;
			sim->stages[11].back_stall = 0;
		
		}
		else {
			st->back_stall = 1;
			sim->stages[11].back_stall =1;
		}
		keep_status(sim, st);
		keep_status_v2_ld(sim,st);
		
		//printf("result %d",st->result);
			
		if(strcmp(st->opcode,"ld")==0){
			st->result=sim->memory[(st->result)/4];
			sim->registers_v2[st->rd]=st->result;
			sim->register_status_v2[st->rd]=0;
			
		}
			
		else if(strcmp(st->opcode,"st")==0){
			sim->memory[(st->result)/4]=st->data1;
		}
		if(!st->back_stall){
			sim->stages[wb_n]=sim->stages[12];
			st->full = 0;
			st->execute_flag =1;
			//printf("Memory 4_d          :%s\n",st->trace);
		}
	}
		
}

void WB_p1_d(simulator* sim){
	stage* st = &sim->stages[13];
	if(!st->execute_flag&&!st->stall_flag){
		if(st->mudi||st->adsub||st->set||strcmp(st->opcode,"ld")==0){
			sim->registers[st->rd]=st->result;
			sim->register_status[st->rd]=0;
			sim->wb_re[st->rd] = 1;
		}
		else if(st->ret_flag){
			sim->end_flag = 1;
		}
		st->execute_flag =1;
		st->full_wb =0;
		//printf("WB1_d          :%s\n",st->trace);
	}
}
void WB_p2_d(simulator* sim){
	stage* st = &sim->stages[14];
	if(!st->execute_flag&&!st->stall_flag){
		if(st->mudi||st->adsub||st->set||strcmp(st->opcode,"ld")==0){
			sim->registers[st->rd]=st->result;
			sim->register_status[st->rd]=0;
			sim->wb_re[st->rd] = 1;
		}
		else if(st->ret_flag){
			sim->end_flag = 1;
		}
		st->execute_flag =1;
		st->full_wb =0;
		//printf("WB2_d          :%s\n",st->trace);
	}
}

