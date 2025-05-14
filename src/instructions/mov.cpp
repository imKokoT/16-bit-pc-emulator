#pragma once
#ifndef __INSTUCTION_MOV_H__
#define __INSTUCTION_MOV_H__
#include "../cpu.h"
#include "../ram.h"

namespace instructions {

    void mov(CPU_16x* cpu, RAM* ram){
        int c = ram->get2Bytes(cpu->PC);
        int r = c & 0b1111;
        int tmp;
        
        switch (c >> 4 & 0b1111)
        {
        // --- 1 byte register (R) ---
        case 0b0000: // immediate
            cpu->R[r] = ram->getByte(cpu->PC+2);
            cpu->PC += 3;
            break;
        case 0b0001: // from RAM address
            cpu->R[r] = ram->getByte(ram->get2Bytes(cpu->PC+2));
            cpu->PC += 4;
            break;
        case 0b0010: // from register
            tmp = ram->getByte(cpu->PC+2); // get other register data

            // check other register
            switch (tmp >> 2 & 0b11) { 
            case 0b00:  
                cpu->R[r] = cpu->R[tmp >> 4];
                break;
            case 0b01:
                cpu->R[r] = cpu->WR[tmp >> 4];
                break;
            case 0b10:
            case 0b11:
                cpu->R[r] = cpu->getSpecialRegister(tmp >> 4);
                break;
            }
            cpu->PC += 3;
            break;
        case 0b0011: // to address
            ram->setByte(
                ram->get2Bytes(cpu->PC+2),
                cpu->R[r]
            );
            cpu->PC += 4;
            break;

        // --- 2 bytes register (WR) ---
        case 0b1000: // immediate
            cpu->WR[r] = ram->get2Bytes(cpu->PC+2);
            cpu->PC += 4;
            break;
        case 0b1001: // from RAM address
            cpu->WR[r] = ram->get2Bytes(ram->get2Bytes(cpu->PC+2));
            cpu->PC += 4;
            break;
        case 0b1010: // from register
            tmp = ram->getByte(cpu->PC+2); // get other register data

            // check other register
            switch (tmp >> 2 & 0b11) { 
            case 0b00:  
                cpu->WR[r] = cpu->R[tmp >> 4];
                break;
            case 0b01:
                cpu->WR[r] = cpu->WR[tmp >> 4];
                break;
            case 0b10:
            case 0b11:
                cpu->WR[r] = cpu->getSpecialRegister(tmp >> 4);
                break;
            }

            cpu->PC += 3;
            break;
        case 0b1011: // to address
            ram->set2Bytes(
                ram->get2Bytes(cpu->PC+2),
                cpu->WR[r]
            );
            cpu->PC += 4;
            break;

        // --- reserved ---
        case 0b1100: // immediate
        case 0b0100:
            cpu->setSpecialRegister(r, ram->get2Bytes(cpu->PC+2));
            cpu->PC += 4;
            break;
        case 0b0101: // from RAM address
        case 0b1101:
            cpu->setSpecialRegister(r, ram->get2Bytes(ram->get2Bytes(cpu->PC+2)));
            cpu->PC += 4;
            break;
        case 0b0110: // from register
        case 0b1110:
            tmp = ram->getByte(cpu->PC+2); // get other register data

            // check other register
            switch (tmp >> 2 & 0b11) { 
            case 0b00:  
                cpu->setSpecialRegister(r, cpu->R[tmp >> 4]);
                break;
            case 0b01:
                cpu->setSpecialRegister(r, cpu->WR[tmp >> 4]);
                break;
            case 0b10:
            case 0b11:
                cpu->setSpecialRegister(r, cpu->getSpecialRegister(tmp >> 4));
                break;
            }

            cpu->PC += 3;
            break;
        case 0b1111: // to RAM address
        case 0b0111:
            ram->set2Bytes(
                ram->get2Bytes(cpu->PC+2),
                cpu->getSpecialRegister(r)
            );
            cpu->PC += 4;
            break;
        default:
            cpu->PC += 2;
            break;
        }
    }
}

#endif // !__INSTUCTION_MOV_H__
