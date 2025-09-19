#pragma once
#include "../../cpu.h"
#include "../../ram.h"
#include<iostream>
#include<stdexcept>
#include<fstream>

namespace instructions {
    
// T is unsigned
template<typename T1, typename T2>
void _add(CPU_16x* cpu, T1& x, T2 y) {
    cpu->flags &= ~51;   // clear C,O,Z,N
    
    auto old = x;
    x += y; 
    
    cpu->flags |= x < old;                                 // C
    cpu->flags |= ((~(old ^ y) & (old ^ (T1)x)) < 0) << 1; // O
    cpu->flags |= (x == 0) << 4;                           // Z
    cpu->flags |= ((T1)x < 0) << 5;                        // N
}

/// @brief returns Y value by command from XY-type command; 
/// increments PC by Y type
int16 getY(CPU_16x* cpu, RAM* ram, int command) {
    int16 currentPC = cpu->PC;
    switch (command & 0b01111000)
    {
    case 0b00000000: // immediate short
        cpu->PC += 4;
        return ram->getByte(currentPC+3);
    case 0b00100000: // immediate long
        cpu->PC += 5;
        return ram->get2Bytes(currentPC+3);
    case 0b00001000: // from mem address
        cpu->PC += 5;
        return ram->get2Bytes(ram->get2Bytes(currentPC+3));
    case 0b00010000: // from R
        cpu->PC += 3;
        return cpu->R[ram->getByte(currentPC+2) >> 4];
    case 0b00110000: // from WR
        cpu->PC += 3;
        return cpu->WR[ram->getByte(currentPC+2) >> 4];
    case 0b01010000: // from Special
        cpu->PC += 3;
        return cpu->getSpecialRegister(ram->getByte(currentPC+2) >> 4);
    default:
        throw std::exception("wrong Y");
    }
}

void add(CPU_16x* cpu, RAM* ram) {
    int c = ram->get2Bytes(cpu->PC);
    
    if (c & 0x1) { // memory
        int a = ram->get2Bytes(cpu->PC+2);
        cpu->PC += 2; // shift PC via 2-bytes address
        if (c & 0x2) {
            int16 tmp = ram->get2Bytes(a);
            _add(cpu, tmp, getY(cpu, ram, c));
            ram->set2Bytes(a, tmp);
        }
        else 
            _add(cpu, ram->getByteRef(a), getY(cpu, ram, c));
    }
    else { // register
        int r = ram->getByte(cpu->PC+2); // possibly two registers
        switch (c & 0x6)
        {
        case 0b000: // R
            _add(cpu, cpu->R[r & 0xf], getY(cpu, ram, c));
            break;
        case 0b010: // WR
            _add(cpu, cpu->WR[r & 0xf], getY(cpu, ram, c));
            break;
        case 0b100: // special
            _add(cpu, cpu->getSpecialRegisterRef(r & 0xf), getY(cpu, ram, c));
            break;
        default:
            break;
        }
    }
}

} // !namespace instructions
