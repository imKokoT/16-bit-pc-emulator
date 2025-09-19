#include "config.h"
#include "cpu.h"
#include "ram.h"
#include "instructions/instructions.h"
#include <iostream>
#include <fstream>

void run(CPU_16x* cpu, RAM* ram) {
    bool run = true;

    while (run)
    {
        switch ((Instruction)ram->getByte(cpu->PC))
        {
        case Instruction::IDL: cpu->PC++; break;
        case Instruction::MOV: instructions::mov(cpu, ram); break;
        case Instruction::TRAP: instructions::trap(cpu, ram); break;
        // ALU
        case Instruction::INC: instructions::inc(cpu, ram); break;
        case Instruction::DEC: instructions::dec(cpu, ram); break;
        case Instruction::ADD: instructions::add(cpu, ram); break;
        case Instruction::STP:
            run = false;
            break;
        default:
            throw std::invalid_argument(
                "CPU error: wrong instruction " + std::to_string(ram->getByte(cpu->PC))
            );
        }

        // if D flag checked call TRAP every instruction
        if (cpu->getFlag(Flag::D)) 
            instructions::trap(cpu, ram, true, false);
    }
}


int main() {
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcout.imbue(std::locale("en_US.UTF-8"));
    printf("starting emulator...\n");

    CPU_16x cpu;
    RAM ram(256);
    ram.data[0x00] = (uint8)Instruction::MOV;
    ram.data[0x01] = 0x00;
    ram.data[0x02] = 0x4;
    ram.data[0x03] = (uint8)Instruction::MOV;
    ram.data[0x04] = 0x80;
    ram.data[0x05] = 0xff;
    ram.data[0x06] = 0x00;
    ram.data[0x07] = (uint8)Instruction::ADD; // immediate R
    ram.data[0x08] = 0x00;
    ram.data[0x09] = 0x00;
    ram.data[0x0a] = 0x4;
    ram.data[0x0b] = (uint8)Instruction::ADD; // immediate WR long + carry
    ram.data[0x0c] = 0x22;
    ram.data[0x0d] = 0x00;
    ram.data[0x0e] = 0x0f;
    ram.data[0x0f] = 0x18;
    ram.data[0x10] = (uint8)Instruction::ADD; // WR0 + R0
    ram.data[0x11] = 0b00010010;
    ram.data[0x12] = 0x00;
    ram.data[0x13] = (uint8)Instruction::ADD; // mem 0xf0 + R0
    ram.data[0x14] = 0b00010001;
    ram.data[0x16] = 0xf0;
    ram.data[0x17] = 0x00;
    
    ram.data[0xf0] = 0xfe;
    ram.data[0xf1] = 0xff;
    cpu.flags = 0x8000; // debug enabled
    try {
        run(&cpu, &ram);
    }
    catch (std::exception e){
        std::cerr << "emulation stops with error: " << e.what() << "\n\n";
        
        instructions::trap(&cpu, &ram, false);
    }
    
    printf("exit emulator\n");
    return 0;
}
