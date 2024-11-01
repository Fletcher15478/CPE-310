/*
Author: Fletcher Hartsock
Group Gabe Turak, John Ferrell, Chad Wangolo
*/
#include "Instruction.h"

void beq_immd_assm(void) {
	// Checking that the opcode matches
	if (strcmp(OP_CODE, "BEQ") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// The first parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Param 2 needs to be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Param 3 needs to be an immediate
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// Rs should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rt should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// The immediate value is limited to 16 bits, which is -32768 to 32767 for signed values
	if (PARAM3.value > 32767 || PARAM3.value < -32768) {
		state = INVALID_IMMED;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode for BEQ 4 in binary is 000100
	setBits_str(31, "000100");

	// Set Rs
	setBits_num(25, PARAM1.value, 5);

	// Set Rt
	setBits_num(20, PARAM2.value, 5);

	// Set Immediate
	setBits_num(15, PARAM3.value, 16);

	// Tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void beq_immd_bin(void) {
	// Check if the opcode bits match for BEQ 000100
	if (checkBits(31, "000100") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values in the binary
	*/
	
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	int16_t Imm = (int16_t)getBits(15, 16); // Cast to signed 16-bit for immediate

	/*
		Setting Instruction values
	*/

	setOp("BEQ");
	setParam(1, REGISTER, Rs); // First source register operand
	setParam(2, REGISTER, Rt); // Second source register operand
	setParam(3, IMMEDIATE, Imm); // Immediate value

	// Tell the system the decoding is done
	state = COMPLETE_DECODE;
}
