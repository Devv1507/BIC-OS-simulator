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
    
    // Metodos para acceder y modificar la memoria
    int read(int address) {
        if (address >= 0 && address < memorySize) {
            return memoryArray[address];
        }
        cout << "Error: Direccion de memoria fuera de limites: " << address << endl;
        return 0;
    }
    
    // Metodo para escribir en memoria
    void write(int address, int value) {
        if (address >= 0 && address < memorySize) {
            memoryArray[address] = value;
        } else {
            cout << "Error: Direccion de memoria fuera de limites: " << address << endl;
        }
    }
    
    // Metodo para mostrar un valor especifico de la memoria
    void show(int address) {
        if (address >= 0 && address < memorySize) {
            cout << "Valor en memoria de D" << address <<" = " << memoryArray[address] << endl;
        } else {
            cout << "Error: Direccion de memoria fuera de limites: " << address << endl;
        }
    }
};

#endif // MEMORY_H
