#pragma once
#ifndef __INSTUCTION_INC_CPP__
#define __INSTUCTION_INC_CPP__
#include "../../cpu.h"
#include "../../ram.h"
#include<iostream>
#include<fstream>

namespace instructions {
    void inc(CPU_16x* cpu, RAM* ram){
        int c = ram->get2Bytes(cpu->PC);
        int r = c & 0b1111;

        if (c & 0x10) { // memory
            int pos = ram->get2Bytes(cpu->PC+2);
            if (c & 0x80)
                ram->set2Bytes(pos, ram->get2Bytes(pos)+1);
            else 
                ram->setByte(pos, ram->getByte(pos)+1);

            cpu->PC += 4;
        } 
        else { // register
            switch (c >> 6 & 0x3)
            {
            case 0b00: // R register
                cpu->R[r]++;
                break;
            case 0b01: // WR register
                cpu->WR[r]++;
                break;
            case 0b10: // special
            case 0b11:
                cpu->setSpecialRegister(r, cpu->getSpecialRegister(r)+1);
                break;
            }
            cpu->PC += 2;
        }
    }
}

#endif // !__INSTRUCTION_INC_CPP__