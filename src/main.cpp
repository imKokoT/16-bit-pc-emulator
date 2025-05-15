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
        case Instruction::STP:
            run = false;
            break;
        default:
            throw std::invalid_argument(
                "CPU error: wrong instruction " + std::to_string(ram->getByte(cpu->PC))
            );
        }
    }
}


int main() {
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcout.imbue(std::locale("en_US.UTF-8"));
    printf("starting emulator...\n");

    CPU_16x cpu;
    RAM ram(256);
    // R
    ram.data[0] = (uint8)Instruction::MOV;
    ram.data[1] = 0;
    ram.data[2] = 0xaa;
    ram.data[3] = (uint8)Instruction::TRAP;
    ram.data[4] = (uint8)Instruction::MOV;
    ram.data[5] = 0b00010001;
    ram.data[7] = 0xf0;
    ram.data[8] = (uint8)Instruction::MOV;
    ram.data[9] = 0b00100010;
    ram.data[10] = 0x00;
    ram.data[11] = (uint8)Instruction::TRAP;
    ram.data[12] = (uint8)Instruction::MOV;
    ram.data[13] = 0b00100011;
    ram.data[14] = 0x08;
    ram.data[15] = (uint8)Instruction::MOV;
    ram.data[16] = 0b00110011;
    ram.data[18] = 0xaa;
    ram.data[19] = (uint8)Instruction::TRAP;

    ram.data[0xf0] = 0x1a;
    ram.data[0xf1] = 0xa1;
    ram.data[255] = 255;

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
