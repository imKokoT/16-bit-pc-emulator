#pragma once
#ifndef __INSTRUCTION_SET_H__
#define __INSTRUCTION_SET_H__

// First instruction set Basic Architecture Set V1
enum class Instructions {
    LTR = 0x00, // load to register
    STM = 0x10, // set to memory
    INC = 0x20, // increment
    DEC = 0x30, // decrement
    ADD = 0x40, 
    NOT = 0x50,
    XOR = 0x60,
    OR = 0x70,
    AND = 0x80,
    SHR = 0x90, // shift right
    SHL = 0xA0, // shift left
    JMP = 0xB0, // jump
    IOG = 0xC0, // io get
    IOS = 0xD0, // io set
    CMP = 0xE0, // compare
};


#endif // !__INSTRUCTION_SET_H__
