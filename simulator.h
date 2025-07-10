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
    
    // Method to read instructions from a file
    vector<vector<string>> readInstructions(const string &filename) {
        ifstream file(filename);
        vector<vector<string>> instructions;
        
        if (!file.is_open()) {
            cout << "Error: File could not be opened " << filename << endl;
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
                // Ensure each instruction has at least 5 elements
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
    
    // Method to load a program from a file
    bool loadProgram(string filename) {
        instructions = readInstructions(filename);
        return !instructions.empty();
    }
    
    // Method to execute the loaded progam
    void executeProgram() {
        for (const auto &instruction : instructions) {
            cpu->executeInstruction(instruction);
        }
    }
};

#endif // SIMULATOR_H
