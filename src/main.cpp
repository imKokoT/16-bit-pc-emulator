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
    ram.data[3] = (uint8)Instruction::MOV;
    ram.data[4] = 0b00010001;
    ram.data[6] = 0xf0;
    ram.data[7] = (uint8)Instruction::MOV;
    ram.data[8] = 0b00100010;
    ram.data[9] = 0x00;
    ram.data[10] = (uint8)Instruction::MOV;
    ram.data[11] = 0b00100011;
    ram.data[12] = 0x08;
    ram.data[13] = (uint8)Instruction::MOV;
    ram.data[14] = 0b00110011;
    ram.data[16] = 0xaa;
    // WR
    ram.data[20] = (uint8)Instruction::MOV;
    ram.data[21] = 0b10000000;
    ram.data[22] = 0xef;
    ram.data[23] = 0xfe;
    ram.data[24] = (uint8)Instruction::MOV;
    ram.data[25] = 0b10010001;
    ram.data[27] = 0xf0;
    ram.data[28] = (uint8)Instruction::MOV;
    ram.data[29] = 0b10100010;
    ram.data[30] = 0x00;
    ram.data[31] = (uint8)Instruction::MOV;
    ram.data[32] = 0b10100011;
    ram.data[33] = 0x08;
    ram.data[34] = (uint8)Instruction::MOV;
    ram.data[35] = 0b10110000;
    ram.data[37] = 0xa0;

    ram.data[0xf0] = 0x1a;
    ram.data[0xf1] = 0xa1;
    ram.data[255] = 255;

    try {
        run(&cpu, &ram);
    }
    catch (std::exception e){
        std::cerr << "emulation stops with error: " << e.what() << "\n\n";
        
        std::cerr << "CPU snapshot:\n";
        std::cerr << "\tPC: " << std::hex << cpu.PC << "\tSP: " << std::hex << cpu.SP << '\n';
        std::cerr << "\tALU flags:" << 
            "\tC=" << cpu.getFlag(ALUFlag::C) << 
            "\tO=" << cpu.getFlag(ALUFlag::O) <<
            "\tE=" << cpu.getFlag(ALUFlag::E) <<
            "\tB=" << cpu.getFlag(ALUFlag::B) <<
            "\tZ=" << cpu.getFlag(ALUFlag::Z) <<
            "\tN=" << cpu.getFlag(ALUFlag::N) << "\n\n";
        std::cerr << "Registers:\n";
        for(int i = 0; i < 16; i++)
            std::cerr << "\tR" << std::dec << i << "=" << std::hex << (int)cpu.R[i];
        std::cerr << '\n';
        for(int i = 0; i < 16; i++)
            std::cerr << "\tWR" << std::dec << i << "=" << std::hex << (int)cpu.WR[i];
        std::cerr << "\n\n";

        std::cerr << "RAM snapshot dumped to 'ram-dump.bin'\n";
        std::ofstream of("ram-dump.bin", std::ios::binary);
        for (int i = 0; i < ram.getSize(); i++)
            of << (char)ram.getByte(i);
        of.close();
    }
    
    printf("exit emulator\n");
    return 0;
}
