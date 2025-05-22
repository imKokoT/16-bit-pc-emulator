#pragma once
#ifndef __INSTUCTION_DEC_CPP__
#define __INSTUCTION_DEC_CPP__
#include "../../cpu.h"
#include "../../ram.h"
#include<iostream>
#include<fstream>

namespace instructions {

    // increment x with setting ALU flags
    void _dec(CPU_16x* cpu, uint8& x) {
        cpu->flags &= ~51;                  // clear O,Z,N
        cpu->flags |= (x == INT8_MIN) << 1; // O
        x--;                                // compute result
        cpu->flags |= (x == 0) << 4;        // Z
        cpu->flags |= ((int8)x < 0) << 5;   // N
    }

    // increment x with setting ALU flags
    void _dec(CPU_16x* cpu, uint16& x) {
        cpu->flags &= ~51;                   // clear O,Z,N
        cpu->flags |= (x == INT16_MIN) << 1; // O
        x--;                                 // compute result
        cpu->flags |= (x == 0) << 4;         // Z
        cpu->flags |= ((int16)x < 0) << 5;   // N
    }

    void dec(CPU_16x* cpu, RAM* ram){
        int c = ram->get2Bytes(cpu->PC);
        int r = c & 0b1111;

        if (c & 0x10) { // memory
            int pos = ram->get2Bytes(cpu->PC+2);
            if (c & 0x80) {
                uint16 tmp = ram->get2Bytes(pos);
                _dec(cpu, tmp);
                ram->set2Bytes(pos, tmp);
            }
            else 
                _dec(cpu, ram->getByteRef(pos));

            cpu->PC += 4;
        } 
        else { // register
            switch (c >> 6 & 0x3)
            {
            case 0b00: // R register
                _dec(cpu, cpu->R[r]);
                break;
            case 0b01: // WR register
                _dec(cpu, cpu->WR[r]);
                break;
            case 0b10: // special
            case 0b11:
                _dec(cpu, cpu->getSpecialRegisterRef(r));
                break;
            }
            cpu->PC += 2;
        }
    }
}

#endif // !__INSTRUCTION_DEC_CPP__
