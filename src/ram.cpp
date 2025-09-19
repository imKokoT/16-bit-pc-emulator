#pragma once
#include "config.hpp"
#include <iostream>
#include <string>


struct RAM
{
    uint32 _size; 
    uint8* data;

    uint8 getByte(int pos) { 
        if (pos + 1 > _size) {
            throw std::out_of_range(
                "RAM ERROR: failed to get byte from position "+std::to_string(pos)+"; RAM size " + std::to_string(_size)
            ); 
        }
        return data[pos];
    }

    uint16 get2Bytes(int pos) {
        if (pos + 2 > _size) {
            throw std::out_of_range(
                "RAM ERROR: failed to get 2 bytes from position "+std::to_string(pos)+"; RAM size " + std::to_string(_size)
            ); 
        }
        return (uint16)(data)[pos] << 8 | data[pos+1]; 
    }

    uint8& getByteRef(int pos) {
        if (pos + 1 > _size) {
            throw std::out_of_range(
                "RAM ERROR: failed to get byte ref from position "+std::to_string(pos)+"; RAM size " + std::to_string(_size)
            ); 
        }
        return data[pos];
    }

    // so sad but this doesn't work 
    //
    // uint16& get2BytesRef(int pos) {
    //     if (pos + 2 > _size) {
    //         throw std::out_of_range(
    //             "RAM ERROR: failed to get 2 ref bytes from position "+std::to_string(pos)+"; RAM size " + std::to_string(_size)
    //         ); 
    //     }
    //     return *(uint16*)(data + pos);
    // }

    void setByte(int pos, uint8 value) {
        if (pos + 1 > _size) {
            throw std::out_of_range(
                "RAM ERROR: failed to set byte to position "+std::to_string(pos)+"; RAM size " + std::to_string(_size)
            ); 
        }
        data[pos] = value;
    }

    void set2Bytes(int pos, uint16 value) {
        if (pos + 2 > _size) {
            throw std::out_of_range(
                "RAM ERROR: failed to set 2 bytes to position "+std::to_string(pos)+"; RAM size " + std::to_string(_size)
            ); 
        }
        data[pos] = value >> 8;
        data[pos+1] = value; 
    }

    int getSize() { return _size; }

    RAM(int size){
        _size = size;
        data = new uint8[size];
        for (int i = 0; i < size; i++)
            data[i] = 0;
    }

    ~RAM() {
        delete[] data;
    }
};
