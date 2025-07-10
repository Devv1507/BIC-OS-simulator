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
        if (address >= 0 && address < memorySize) {
            return memoryArray[address];
        }
        cout << "Error: Memory address out of limits: " << address << endl;
        return 0;
    }
    
    // Method to write to memory
    void write(int address, int value) {
        if (address >= 0 && address < memorySize) {
            memoryArray[address] = value;
        } else {
            cout << "Error: Memory address out of limits: " << address << endl;
        }
    }
    
    // Method to display a specific value from the memory
    void show(int address) {
        if (address >= 0 && address < memorySize) {
            cout << "Memory value of D" << address <<" = " << memoryArray[address] << endl;
        } else {
            cout << "Error: Memory address out of limits: " << address << endl;
        }
    }
};

#endif // MEMORY_H
