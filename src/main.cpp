#include "config.h"
#include "cpu.h"
#include "ram.h"
#include <iostream>


namespace instructions {

    void move(CPU_16x* cpu, RAM* ram){
        int c = ram->get2Bytes(cpu->PC);
        int r = c & 0b1111;
        int tmp;
        
        switch (c >> 4 & 0b1111)
        {
        // --- 1 byte register ---
        case 0b0000: // immediate
            cpu->R[r] = ram->getByte(cpu->PC+2);
            cpu->PC += 3;
            break;
        case 0b0001: // from mem address
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

        // --- reserved ---
        case 0b1111:
        case 0b1011:
        case 0b0111:
        default:
            cpu->PC += 2;
            break;
        }
    }
}



void run(CPU_16x* cpu, RAM* ram) {
    bool run = true;

    while (run)
    {
        switch ((Instruction)ram->getByte(cpu->PC))
        {
        case Instruction::IDL: cpu->PC++; break;
        case Instruction::MOV: instructions::move(cpu, ram); break;
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
        // TODO: RAM DUMP TO FILE
    }
    
    printf("exit emulator\n");
    return 0;
}
