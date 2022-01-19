#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "instruction.h"
#include <simple.h>

void IF(char * buffer){
	if(IF_flag){
		create_CPU_instruction(if_to_id.current_instruction,buffer);
		if_to_id.clockcycle += 1;
		if_to_id.has_executed = 1;
		
	}
	else
		if_to_id.has_exected = 0;
}

void ID(bool ID_flag){
	if(if_to_id.has_exected){
		id_to_exa.opcode = if_to_id.current_instruction->opcode;
		id_to_exa.rd = if_to_id.current_instruction->rd;
		id_to_exa.rs1 = if_to_id.current_instruction->rs1;
		id_to_exa.rs2 = if_to_id.current_instruction->rs2;
		id_to_exa.imm = if_to_id.current_instruction->imm;
		id_to_exa.is_imm = if_to_id.current_instruction->is_imm;
		id_to_exa.trace= if_to_id.current_instruction->trace;
		if (id_to_exa.rs1>=0&&id_to_exa.rs2>=0){
			if(register_status.at(rs1)=="Writing"||register_status.at(rs2)=="Writing"){
				
			}
		}
		
		
		if(id_to_exa.opcode == "set"){
			id_to_exa.control.checkbranch = 0;
			id_to_exa.control.Register_write = 1;
			id_to_exa.control.Register_read = 0;
			id_to_exa.control.Mem_read = 0;
			id_to_exa.control.Mem_write = 0;
		}
		else if (id_to_exa.opcode == "ld" && id_to_exa.is_imm ){
			id_to_exa.control.checkbranch = 0;
			id_to_exa.control.Register_write = 1;
			id_to_exa.control.Register_read = 0;
			id_to_exa.control.Mem_read = 1;
			id_to_exa.control.Mem_write = 0;
		}
		else if (id_to_exa.opcode == "ld" && !id_to_exa.is_imm ){
			id_to_exa.control.checkbranch = 0;
			id_to_exa.control.Register_write = 1;
			id_to_exa.control.Register_read = 1;
			id_to_exa.control.Mem_read = 0;
			id_to_exa.control.Mem_write = 0;
		}
		else if (id_to_exa.opcode == "st" && id_to_exa.is_imm ){
			id_to_exa.control.checkbranch = 0;
			id_to_exa.control.Register_write = 0;
			id_to_exa.control.Register_read = 1;
			id_to_exa.control.Mem_read = 0;
			id_to_exa.control.Mem_write = 1;
		}
		else if (id_to_exa.opcode == "st" && !id_to_exa.is_imm ){
			id_to_exa.control.checkbranch = 0;
			id_to_exa.control.Register_write = 1;
			id_to_exa.control.Register_read = 1;
			id_to_exa.control.Mem_read = 0;
			id_to_exa.control.Mem_write = 0;
		}
		else if (id_to_exa.opcode == "add" && id_to_exa.is_imm ){
			id_to_exa.control.checkbranch = 0;
			id_to_exa.control.Register_write = 1;
			id_to_exa.control.Register_read = 1;
			id_to_exa.control.Mem_read = 0;
			id_to_exa.control.Mem_write = 0;
		}
		else if (id_to_exa.opcode == "add" && !id_to_exa.is_imm ){
			id_to_exa.control.checkbranch = 0;
			id_to_exa.control.Register_write = 1;
			id_to_exa.control.Register_read = 1;
			id_to_exa.control.Mem_read = 0;
			id_to_exa.control.Mem_write = 0;
			id_to_exa.control.two_register = 1;
		}
		else if (id_to_exa.opcode == "sub" && id_to_exa.is_imm ){
			id_to_exa.control.checkbranch = 0;
			id_to_exa.control.Register_write = 1;
			id_to_exa.control.Register_read = 1;
			id_to_exa.control.Mem_read = 0;
			id_to_exa.control.Mem_write = 0;
		}
		else if (id_to_exa.opcode == "sub" && !id_to_exa.is_imm ){
			id_to_exa.control.checkbranch = 0;
			id_to_exa.control.Register_write = 1;
			id_to_exa.control.Register_read = 1;
			id_to_exa.control.Mem_read = 0;
			id_to_exa.control.Mem_write = 0;
			id_to_exa.control.two_register = 1;
		}
		else if (id_to_exa.opcode == "mul" && id_to_exa.is_imm ){
			id_to_exa.control.checkbranch = 0;
			id_to_exa.control.Register_write = 1;
			id_to_exa.control.Register_read = 1;
			id_to_exa.control.Mem_read = 0;
			id_to_exa.control.Mem_write = 0;
		}
		else if (id_to_exa.opcode == "mul" && !id_to_exa.is_imm ){
			id_to_exa.control.checkbranch = 0;
			id_to_exa.control.Register_write = 1;
			id_to_exa.control.Register_read = 0;
			id_to_exa.control.Mem_read = 1;
			id_to_exa.control.Mem_write = 0;
			id_to_exa.control.two_register = 1;
		}
		else if (id_to_exa.opcode == "div" && id_to_exa.is_imm ){
			id_to_exa.control.checkbranch = 0;
			id_to_exa.control.Register_write = 1;
			id_to_exa.control.Register_read = 0;
			id_to_exa.control.Mem_read = 1;
			id_to_exa.control.Mem_write = 0;
		}
		else if (id_to_exa.opcode == "div" && !id_to_exa.is_imm ){
			id_to_exa.control.checkbranch = 0;
			id_to_exa.control.Register_write = ;
			id_to_exa.control.Register_read = 0;
			id_to_exa.control.Mem_read = 1;
			id_to_exa.control.Mem_write = 0;
			id_to_exa.control.two_register = 1;
		}
		else if (id_to_exa.opcode == "bgez"){
			id_to_exa.control.checkbranch = 1;
			id_to_exa.control.Register_write = 0;
			id_to_exa.control.Register_read = 0;
			id_to_exa.control.Mem_read = 0;
			id_to_exa.control.Mem_write = 0;
		}
		else if (id_to_exa.opcode == "blez"){
			id_to_exa.control.checkbranch = 1;
			id_to_exa.control.Register_write = 1;
			id_to_exa.control.Register_read = 0;
			id_to_exa.control.Mem_read = 1;
			id_to_exa.control.Mem_write = 0;
		}
		else if (id_to_exa.opcode == "bez"){
			id_to_exa.control.checkbranch = 1;
			id_to_exa.control.Register_write = 1;
			id_to_exa.control.Register_read = 0;
			id_to_exa.control.Mem_read = 1;
			id_to_exa.control.Mem_write = 0;
		}
		else if (id_to_exa.opcode == "bgtz"){
			id_to_exa.control.checkbranch = 1;
			id_to_exa.control.Register_write = 1;
			id_to_exa.control.Register_read = 0;
			id_to_exa.control.Mem_read = 1;
			id_to_exa.control.Mem_write = 0;
		}
		else if (id_to_exa.opcode == "bltz"){
			id_to_exa.control.checkbranch = 1;
			id_to_exa.control.Register_write = 1;
			id_to_exa.control.Register_read = 0;
			id_to_exa.control.Mem_read = 1;
			id_to_exa.control.Mem_write = 0;
		}
		else if (id_to_exa.opcode == "ret"){
			id_to_exa.control.checkbranch = 1;
			id_to_exa.control.Register_write = 0;
			id_to_exa.control.Register_read = 0;
			id_to_exa.control.Mem_read = 0;
			id_to_exa.control.Mem_write = 0;
		}
		
	}
	
	
	
	
}
