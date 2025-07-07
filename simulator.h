#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "cpu.h"
#include "memory.h"

using namespace std;

class Simulator {
private:
    Memory* memory;
    CPU* cpu;
    vector<vector<string>> instructions;
    
    // Metodo para leer instrucciones desde un archivo
    vector<vector<string>> readInstructions(const string &filename) {
        ifstream file(filename);
        vector<vector<string>> instructions;
        
        if (!file.is_open()) {
            cout << "Error: No se pudo abrir el archivo " << filename << endl;
            return instructions;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> tokens;
            string token;
            
            while (ss >> token) {
                tokens.push_back(token);
            }
            
            if (!tokens.empty()) {
                // Asegurar que cada instruccion tenga al menos 5 elementos
                while (tokens.size() < 5) {
                    tokens.push_back("NULL");
                }
                instructions.push_back(tokens);
            }
        }
        
        file.close();
        return instructions;
    }

public:
    // Constructor
    Simulator(int memorySize = 100) {
        memory = new Memory(memorySize);
        cpu = new CPU(memory);
    }
    
    // Metodo para cargar un programa desde un archivo
    bool loadProgram(string filename) {
        instructions = readInstructions(filename);
        return !instructions.empty();
    }
    
    // Metodo para ejecutar el programa cargado
    void executeProgram() {
        for (const auto &instruction : instructions) {
            cpu->executeInstruction(instruction);
        }
    }
};

#endif // SIMULATOR_H
