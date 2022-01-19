#ifndef SIMULATOR_H_
#define SIMULATOR_H_
#include<iostream>


#define I_len 128
extern "C"
{
	#include"instruction.h"
}
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

typedef struct stage_a{
	CPU_Instruction ins;
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
	int not_advance
}stage_a;

class ST
{
	private:
		stage_a stage;
	public:
		void fetch_ins(char *buffer);
		stage_a get_stage_a();
		void trans_stage(stage_a st);
		void show_st();
		void if_st(simulator sim);
};

void ST::fetch_ins(char *buffer){
	using std::cout;
	char a[I_len];
	strcpy(a,buffer);
	CPU_Instruction * ins_p = (CPU_Instruction*)malloc(sizeof(ins_p));
	create_CPU_instruction(ins_p,a);
	strcpy(stage.ins.opcode,ins_p->opcode);
	stage.ins.rd = ins_p->rd;
	stage.ins.rs1 = ins_p->rs1;
	stage.ins.rs2 = ins_p->rs2;
	stage.ins.imm = ins_p->imm;
	stage.ins.is_imm = ins_p->is_imm;
	strcpy(stage.ins.trace,ins_p->trace);
	free(ins_p);
}

stage_a ST::get_stage_a(){
	return stage;
}

void ST::trans_stage(stage_a st){
	stage = st;
}

void ST::show_st(){
	using std::cout;
	using std::endl;
	cout<<"opcode: "<<stage.ins.opcode<<endl;
	cout<<"rd: "<<stage.ins.rd<<endl;
	cout<<"rs1: "<<stage.ins.rs1<<endl;
	cout<<"rs2: "<<stage.ins.rs2<<endl;
	cout<<"imm: "<<stage.ins.imm<<endl;
	cout<<"is_imm: "<<stage.ins.is_imm<<endl;
	cout<<"trace: "<<stage.ins.trace<<endl;
}

void ST::if_st(simulator* sim){
	
}















#endif
