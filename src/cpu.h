#pragma once
#ifndef __CPU_H__
#define __CPU_H__
#include "config.h"

enum class ALUFlag;


struct CPU_16x
{
    uint8 R[16]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    uint16 WR[16]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    uint16 PC;
    uint16 SP;
    uint16 flags;

    bool getFlag(ALUFlag flag) {
        return flags & (uint16)flag;
    }

    // returns special register value
    // 0 = PC
    // 1 = SP
    uint16 getSpecialRegister(int index) {
        switch (index)
        {
        case 0: return PC;
        case 1: return SP;
        default:
            return 0;
        }
    }

    // sets special register to value
    // 0 = PC
    // 1 = SP
    void setSpecialRegister(int index, int value) {
        switch (index)
        {
        case 0: PC = value;
        case 1: SP = value;
        }
    }
};

enum class ALUFlag {
    C = 0x01,
    O = 0x02,
    E = 0x04,
    B = 0x08,
    Z = 0x0f,
    N = 0x10
};

enum class Instruction {
    IDL = 0x00,
    STP = 0x0c,
    MOV = 0x01,

    // ALU
    INC = 0x02,
    DEC = 0x03,
    ADD = 0x04,
    SUB = 0x05,
    XOR = 0x06,
     OR = 0x07,
    AND = 0x08,
    NOT = 0x09,
    SHR = 0x0a,
    SHL = 0x0b,

    // Branch
    CMP,
    JMP,
};

#endif // !__CPU_H__
