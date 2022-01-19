#ifndef _SIMPLE_H_
#define _SIMPLE_H_
#include <vector>
#include <stdlib.h>
#include <string>
#include "instruction.h"
using namespace std;

extern vector<int>registers (16);
extern vector<string>register_status (16);
extern vector<int>memory;
extern vector<string>instruction_set;
extern bool IF_flag;
extern bool ID_flag;

extern struct IF_to_ID{
	unsigned int has_executed;
	unsigned int clockcycle;
	CPU_Instruction* current_instruction;
	CPU_Instruction* next_instruction;
}if_to_id;

extern struct ID_to_EXa{
	char opcode;
	int rd;
	int rs1;
	int rs2;
	int imm;
	bool is_imm;
	char trace[128];
	
	
	
	struct {
	    int dependency;
	    int two_register;
		int checkbranch;
		int Register_write;
		int Register_read;
		int Mem_read;
		int Mem_write;
	}control;
	int readdata1;
	int readdata2;

}id_to_exa;

void IF(bool IF_flag, char * buffer);
void ID(bool ID_flag);

#endif
