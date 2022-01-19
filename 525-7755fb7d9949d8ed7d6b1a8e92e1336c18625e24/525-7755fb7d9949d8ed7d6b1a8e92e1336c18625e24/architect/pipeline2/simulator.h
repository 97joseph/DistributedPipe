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
    int advance_flag;
    int p_stall_flag;
    int branch_a_flag;
    int depen_f_flag;
    int ret_a_flag;
    int full;
    int full_wb;
    int d_stall;
    int back_stall;
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
	int dat_ha;
	int branc_ha;
	int struc_a;
	int t_c;
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
	stage stages[20];
	char instructions[100][100]; 
}simulator;



simulator* sim_build(char a[][100],int a_size);
simulator* sim_build_d(char a[][100],int a_size);




void print_1(simulator* sim, const char* a);
void print_2(simulator* sim);
void print_3(simulator* sim);


void IF_p1(simulator* sim);
void ID_p1(simulator* sim);
void EXa_p1(simulator* sim);
void EXb1_p1(simulator* sim);
void EXb2_p1(simulator* sim);
void Mem1_p1(simulator* sim);
void Mem2_p1(simulator* sim);
void Mem3_p1(simulator* sim);
void Mem4_p1(simulator* sim);
void WB_p1(simulator* sim);

void IF_p2(simulator* sim);
void ID_p2(simulator* sim);
void EXa_p2(simulator* sim);
void EXb1_p2(simulator* sim);
void EXb2_p2(simulator* sim);
void Mem1_p2(simulator* sim);
void Mem2_p2(simulator* sim);
void Mem3_p2(simulator* sim);
void Mem4_p2(simulator* sim);
void WB_p2(simulator* sim);
int judege_in(simulator* sim);
void print_3_d(simulator* sim);
void filter_input(simulator* sim,int a);
void IF_p1_d(simulator* sim);
void ID_p1_d(simulator* sim);
void cond_d(simulator* sim);
void EXa_p1_d(simulator* sim);
void EXb1_p1_d(simulator* sim);
void EXb2_p1_d(simulator* sim);
void Mem1_d(simulator* sim);
void Mem2_d(simulator* sim);
void Mem3_d(simulator* sim);
void Mem4_d(simulator* sim);
void WB_p1_d(simulator* sim);

void IF_p2_d(simulator* sim);
void ID_p2_d(simulator* sim);
void EXa_p2_d(simulator* sim);

void WB_p2_d(simulator* sim);

void print_2_v2(simulator* sim);

void print_3_v1(simulator* sim);
void print_3_v2(simulator* sim);
void print_3_v3(simulator* sim);
void get_memory(simulator* sim);
void memory_out_0(simulator* sim);
void memory_out_1(simulator* sim);
void memory_out_2(simulator* sim);
void memory_out_3(simulator* sim);
void set_wb_z(simulator* sim);
int check_branch(stage* st);
void check_depen(simulator* sim, stage* st);
void keep_status(simulator* sim, stage* st);
void add_ins_num(simulator* sim, stage* st);

void check_depen_v2(simulator* sim, stage* st);
void check_waw(simulator*sim, stage* st);
int check_wb_buffer(simulator*sim, stage*st);
int check_stage(simulator*sim, stage*st);
void keep_status_v2_mudi(simulator* sim, stage* st);
void keep_status_v2_ld(simulator* sim, stage* st);

//void print_1();

#endif

