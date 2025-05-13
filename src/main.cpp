#include "config.h"
#include "cpu.h"
#include "ram.h"
#include <iostream>


void run(CPU_16x* cpu, RAM* ram) {
    bool run = true;

    while (run)
    {
        switch ((Instruction)ram->getByte(cpu->PC))
        {
        case Instruction::IDL: break;
        case Instruction::STP:
            run = false;
            break;
        default:
            throw std::invalid_argument(
                "CPU error: wrong instruction " + std::to_string(ram->getByte(cpu->PC))
            );
        }

        cpu->PC++;
    }
}


int main() {
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcout.imbue(std::locale("en_US.UTF-8"));
    printf("starting emulator...\n");

    CPU_16x cpu;
    RAM ram(256);

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

        std::cerr << "RAM snapshot dumped to 'ram-dump.bin'\n";
        // TODO: RAM DUMP TO FILE
    }
    
    printf("exit emulator\n");
    return 0;
}
