#pragma once
#ifndef __CPU_H__
#define __CPU_H__
#include "config.h"


struct CPU_16x
{
    uint8 R[16];
    uint16 WR[16];

    uint16 PC;
    uint16 SP;
    uint16 flags;
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
    MOV = 0x01,

    // ALU
    INC = 0x02,
    DEC = 0x03,
    ADD = 0x04,
    SUB = 0x05,
    XOR = 0x06,
     OR = 0x07,
    AND = 0x08,
    NOT = 0x07,
    SHR = 0x08,
    SHL = 0x09,

    // Branch
    CMP,
    JMP,
};

#endif // !__CPU_H__
