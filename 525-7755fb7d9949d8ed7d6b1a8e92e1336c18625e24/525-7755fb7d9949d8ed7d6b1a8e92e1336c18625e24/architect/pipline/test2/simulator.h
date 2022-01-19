#ifndef SIMULATOR_H_
#define COORDIN_H_
#include <stdbool.h>
#include "instruction.h"
#define I_len 100

typedef struct stage{
	char opcode[128];
	int rd;		   
	int rs1;		   
	int rs2;		   
	int imm;		   
    bool is_imm; 
    char trace[128];
    int pc;
    char current_ins[I_len];
    int depen_flag;
    int depen_fin;
    int struct_flag;
    int struct_fin;
    int branch_flag;
    int stall_flag;
    int execute_flag;
    int two_rs;
    int set;
    int adsub;
    int ldst;
    int mudi;
	int ret_flag;
	int data1;
	int data2;
	int result;
	int wb_reg;
	
}stage;


typedef struct simulator{
	int registers[16];
	int registers_v2[16];
	int register_status[16];
	int register_status_v2[16];
	int wb_re[16];
	CPU_Instruction* ins;
	int data_ha;
	int struct_ha;
	int branch_ha;
	int ha_test;
	int read_re;
	int write_re;
	int wb_reg;
	int set_num;
	int add_num;
	int sub_num;
	int mul_num;
	int div_num;
	int ld_num;
	int st_num;
	int bez_num;
	int bgez_num;
	int blez_num;
	int bgtz_num;
	int bltz_num;
	int branch_prediction;
	int ret_num;
	int ins_sum;
	int pc;
	int cc;
	int tot_ins;
	int memory[16384];
	int end_flag;
	stage stages[10];
	char instructions[100][100]; 
}simulator;



simulator* sim_build(char a[][100],int a_size);



void IF(simulator* sim);
void ID(simulator* sim);
void EXa(simulator* sim);
void EXb1(simulator* sim);
void EXb2(simulator* sim);
void Mem1(simulator* sim);
void Mem2(simulator* sim);
void Mem3(simulator* sim);
void Mem4(simulator* sim);
void WB(simulator* sim);
void print_1(simulator* sim, const char* a);
void print_2(simulator* sim);
void print_3(simulator* sim);


void ID_v1(simulator* sim);
void EXa_v1(simulator* sim);
void EXb1_v1(simulator* sim);

void ID_v2(simulator* sim);
void EXa_v2(simulator* sim);
void EXb1_v2(simulator* sim);
void EXb2_v2(simulator* sim);
void Mem1_v2(simulator* sim);
void Mem2_v2(simulator* sim);
void Mem3_v2(simulator* sim);
void Mem4_v2(simulator* sim);

void ID_v3(simulator* sim);
void memory_out_0(simulator* sim);
void memory_out_1(simulator* sim);
void memory_out_2(simulator* sim);
void memory_out_3(simulator* sim);

void print_2_v2(simulator* sim);

void print_3_v1(simulator* sim);
void print_3_v2(simulator* sim);
void print_3_v3(simulator* sim);
void get_memory(simulator* sim);

int check_branch(stage* st);
void check_depen(simulator* sim, stage* st);
void keep_status(simulator* sim, stage* st);
void add_ins_num(simulator* sim, stage* st);

void check_depen_v2(simulator* sim, stage* st);
void keep_status_v2_mudi(simulator* sim, stage* st);
void keep_status_v2_ld(simulator* sim, stage* st);

//void print_1();

#endif

