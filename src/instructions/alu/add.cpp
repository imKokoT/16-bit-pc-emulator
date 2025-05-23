#pragma once
#ifndef __INSTUCTION_ADD_CPP__
#define __INSTUCTION_ADD_CPP__
#include "../../cpu.h"
#include "../../ram.h"
#include<iostream>
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

}

#endif // !__INSTUCTION_ADD_CPP__
