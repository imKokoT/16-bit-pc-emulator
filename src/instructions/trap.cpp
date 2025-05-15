#pragma once
#ifndef __INSTUCTION_TRAP_CPP__
#define __INSTUCTION_TRAP_CPP__
#include "../cpu.h"
#include "../ram.h"
#include<iostream>
#include<fstream>

namespace instructions {
    void trap(CPU_16x* cpu, RAM* ram, bool pause = true, bool incPC = true) {
        std::cerr << "TRAPPED at " << cpu->PC << "\n\n";

        std::cerr << "CPU snapshot:\n";
        std::cerr << "\tPC: " << std::hex << cpu->PC << "\tSP: " << std::hex << cpu->SP << '\n';
        std::cerr << "\tALU flags:" << 
            "\tC=" << cpu->getFlag(Flag::C) << 
            "\tO=" << cpu->getFlag(Flag::O) <<
            "\tE=" << cpu->getFlag(Flag::E) <<
            "\tB=" << cpu->getFlag(Flag::B) <<
            "\tZ=" << cpu->getFlag(Flag::Z) <<
            "\tN=" << cpu->getFlag(Flag::N) << "\n\n";
        std::cerr << "Registers:\n";
        for(int i = 0; i < 16; i++)
            std::cerr << "\tR" << std::dec << i << "=" << std::hex << (int)cpu->R[i];
        std::cerr << '\n';
        for(int i = 0; i < 16; i++)
            std::cerr << "\tWR" << std::dec << i << "=" << std::hex << (int)cpu->WR[i];
        std::cerr << "\n\n";

        std::cerr << "RAM snapshot dumped to 'ram-dump.bin'\n";
        std::ofstream of("ram-dump.bin", std::ios::binary);
        for (int i = 0; i < ram->getSize(); i++)
            of << (char)ram->getByte(i);
        of.close();

        if (pause)
            std::system("pause");
        if (incPC)
            cpu->PC++;
    }
}

#endif // !__INSTUCTION_TRAP_CPP__
