/*
Author: Fletcher Hartsock
Group Gabe Turak, John Ferrell, Chad Wangolo
*/
#include "Instruction.h"

void bne_immd_assm(void) {
    // Checking that the opcode matches
    if (strcmp(OP_CODE, "BNE") != 0) {
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

    // The second parameter should be a register
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // The third parameter should be an immediate
    if (PARAM3.type != IMMEDIATE) {
        state = MISSING_REG;
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

    /*
        Putting the binary together
    */

    // Set the opcode for BNE 5 in binary is 000101
    setBits_num(31, 5, 6);

    // Set Rs
    setBits_num(25, PARAM1.value, 5);

    // Set Rt
    setBits_num(20, PARAM2.value, 5);

    // Set Immediate
    setBits_num(15, PARAM3.value, 16);

    // Tell the system the encoding is done
    state = COMPLETE_ENCODE;
}

void bne_immd_bin(void) {
    // Check if the opcode bits match for BNE 000101
    if (checkBits(31, "000101") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Finding values in the binary
    */

    // getBits(start_bit, width)
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);
    int16_t Imm = (int16_t)getBits(15, 16); // Cast to signed 16-bit for immediate

    /*
        Setting Instruction values
    */

    setOp("BNE");
    setParam(1, REGISTER, Rs); // First source register operand
    setParam(2, REGISTER, Rt); // Second source register operand
    setParam(3, IMMEDIATE, Imm); // Immediate value

    // Tell the system the decoding is done
    state = COMPLETE_DECODE;
}
