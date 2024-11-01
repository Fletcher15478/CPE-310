/*
Author: Fletcher Hartsock
Group Gabe Turak, John Ferrell, Chad Wangolo, Fletcher Hartsock
*/
#include "Instruction.h"


void sw_immd_assm(void) {
    // Checking that the opcode matches
    if (strcmp(OP_CODE, "SW") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Checking the type of parameters
    */

    // The first parameter should be a register (data register)
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // The second parameter should be an immediate (offset)
    if (PARAM2.type != IMMEDIATE) {
        state = MISSING_REG;
        return;
    }

    // The third parameter should be a register (base address register)
    if (PARAM3.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    /*
        Checking the value of parameters
    */

    // Rt (data register) should be 31 or less
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    // Base register should be 31 or less
    if (PARAM3.value > 31) {
        state = INVALID_REG;
        return;
    }

    /*
        Putting the binary together
    */

    // Set the opcode for SW 101011
    setBits_num(31, 43, 6);

    // Set Base register
    setBits_num(25, PARAM3.value, 5);

    // Set Rt (data register)
    setBits_num(20, PARAM1.value, 5);

    // Set Offset
    setBits_num(15, PARAM2.value, 16);

    // Tell the system the encoding is done
    state = COMPLETE_ENCODE;
}

void sw_immd_bin(void) {
    // Check if the opcode bits match for SW 101011
    if (checkBits(31, "101011") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Finding values in the binary
    */

    // getBits(start_bit, width)
    uint32_t Base = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);
    int16_t Offset = (int16_t)getBits(15, 16); // Cast to signed 16-bit for offset

    /*
        Setting Instruction values
    */

    setOp("SW");
    setParam(1, REGISTER, Rt);      // Data register
    setParam(2, IMMEDIATE, Offset); // Offset
    setParam(3, REGISTER, Base);    // Base address register

    // Tell the system the decoding is done
    state = COMPLETE_DECODE;
}
