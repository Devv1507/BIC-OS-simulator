#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

using namespace std;

class Memory {
private:
    int* memoryArray;
    int memorySize;

public:
    // Constructor
    Memory(int size = 100) {
        memorySize = size;
        memoryArray = new int[size];
        for (int i = 0; i < size; i++) {
            memoryArray[i] = 0;
        }
    }
    
    // Method to access and modify memory
    int read(int address) {
        switch (address >= 0 && address < memorySize ? 1 : 0) {
            case 1:
                return memoryArray[address];
            case 0:
            default:
                cout << "Error: Memory address out of limits: " << address << endl;
                return 0;
        }
    }
    
    // Method to write to memory
    void write(int address, int value) {
        switch (address >= 0 && address < memorySize ? 1 : 0) {
            case 1:
                memoryArray[address] = value;
                break;
            case 0:
            default:
                cout << "Error: Memory address out of limits: " << address << endl;
                break;
        }
    }
    
    // Method to display a specific value from the memory
    void show(int address) {
        switch (address >= 0 && address < memorySize ? 1 : 0) {
            case 1:
                cout << "Memory value of D" << address <<" = " << memoryArray[address] << endl;
                break;
            case 0:
            default:
                cout << "Error: Memory address out of limits: " << address << endl;
                break;
        }
    }
};

#endif // MEMORY_H
