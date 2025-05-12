#pragma once
#ifndef __INSTRUCTION_SET_H__
#define __INSTRUCTION_SET_H__


enum class Instruction {
    IDL = 0x00,
    MOV = 0x01,

    // ALU
    INC,
    DEC,
    ADD,
    SUB,
    XOR,
    OR,
    AND,
    NOT,
    SHR,
    SHL,

    // Branch
    CMP,
    JMP,
};


#endif // !__INSTRUCTION_SET_H__
