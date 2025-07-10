#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <vector>
#include "memory.h"

using namespace std;

class CPU {
private:
    int ACC;
    int ICR;
    int MAR;
    int MDR;
    bool controlUnit; // UC
    Memory* memory;

    // Method to obtain memory index from operand
    int getMemoryIndex(string operand) {
        if (!operand.empty() && operand[0] == 'D') {
            // Extracts the number after 'D'
            return stoi(operand.substr(1));
        }
        return -1;
    }

public:
    // Constructor
    CPU(Memory* mem) : memory(mem) {
        ACC = 0;
        ICR = 0;
        MAR = 0;
        MDR = 0;
        controlUnit = true;  
    }
    
    // Method to load a value into memory
    void SET(vector<string> args) {
        int address = getMemoryIndex(args[1]);
        int value = stoi(args[2]);
        if (address != -1) {
            memory->write(address, value);
        }
    }
    
    // Method to load a value from memory to ACC
    void LDR(vector<string> args) {
        int address = getMemoryIndex(args[1]);
        if (address != -1) {
            MAR = address;
            MDR = memory->read(address);
            ACC = MDR;
            ICR++;
        }
    }
    
    // Method to sum memory values
    void ADD(vector<string> args) {
        // First way: ADD D1 NULL NULL
        if (args.size() >= 2 && args[2] == "NULL") {
            int address = getMemoryIndex(args[1]);
            if (address != -1) {
                MAR = address;
                MDR = memory->read(address);
                ACC += MDR;
            }
        }
        // Second way: ADD D1 D3 NULL
        else if (args.size() >= 3 && args[3] == "NULL") {
            int address1 = getMemoryIndex(args[1]);
            int address2 = getMemoryIndex(args[2]);
            if (address1 != -1 && address2 != -1) {
                MAR = address1;
                MDR = memory->read(address1);
                ACC = MDR;
                
                MAR = address2;
                MDR = memory->read(address2);
                ACC += MDR;
            }
        }
        // Third way: ADD D1 D3 D4
        else if (args.size() >= 4) {
            int address1 = getMemoryIndex(args[1]);
            int address2 = getMemoryIndex(args[2]);
            int address3 = getMemoryIndex(args[3]);
            if (address1 != -1 && address2 != -1 && address3 != -1) {
                MAR = address1;
                MDR = memory->read(address1);
                ACC = MDR;
                
                MAR = address2;
                MDR = memory->read(address2);
                ACC += MDR;
                
                MAR = address3;
                MDR = ACC;
                memory->write(address3, MDR);
            }
        }
        ICR++;
    }
    
    // Method to store the contents of the ACC into memory
    void STR(vector<string> args) {
        int address = getMemoryIndex(args[1]);
        if (address != -1) {
            MAR = address;
            MDR = ACC;
            memory->write(address, MDR);
            ICR++;
        }
    }
    
    // Method to display values according to a memory address
    void SHW(vector<string> args) {
        if (args[1] == "ACC") {
            cout << "ACC = " << ACC << endl;
        } else if (args[1] == "ICR") {
            cout << "ICR = " << ICR << endl;
        } else if (args[1] == "MAR") {
            cout << "MAR = " << MAR << endl;
        } else if (args[1] == "MDR") {
            cout << "MDR = " << MDR << endl;
        } else if (args[1] == "UC") {
            cout << "UC = " << (controlUnit ? "Active" : "Paused") << endl;
        } else {
            int address = getMemoryIndex(args[1]);
            if (address != -1) {
                memory->show(address);
            }
        }
        ICR++;
    }
    
    // Instruction memory for incrementing a value by 1
    void INC(vector<string> args) {
        int address = getMemoryIndex(args[1]);
        if (address != -1) {
            MAR = address;
            MDR = memory->read(address);
            MDR++;  
            memory->write(address, MDR);
            ICR++;
        }
    }
    
    // Instruction memory for decrementing a value by 1
    void DEC(vector<string> args) {
        int address = getMemoryIndex(args[1]);
        if (address != -1) {
            MAR = address;
            MDR = memory->read(address);
            MDR--;
            memory->write(address, MDR);
            ICR++;
        }
    }
    
    // Method to pause the execution
    void PAUSE() {
        controlUnit = false;
        cout << "Simulation paused. Press ENTER to continue..." << endl;
        cin.get();
        controlUnit = true;
        ICR++;
    }
    
    // Method to end the execution
    void END() {
        cout << "Execution completed." << endl;
    }

    // Method to execute an instruction
    void executeInstruction(vector<string> instruction) {
        string opcode = instruction[0];
        
        if (opcode == "SET") {
            SET(instruction);
        } else if (opcode == "LDR") {
            LDR(instruction);
        } else if (opcode == "ADD") {
            ADD(instruction);
        } else if (opcode == "STR") {
            STR(instruction);
        } else if (opcode == "SHW") {
            SHW(instruction);
        } else if (opcode == "INC") {
            INC(instruction);
        } else if (opcode == "DEC") {
            DEC(instruction);
        } else if (opcode == "PAUSE") {
            PAUSE();
        } else if (opcode == "END") {
            END();
        } else {
            cout << "Unknown instruction: " << opcode << endl;
        }
    }
};

#endif // CPU_H
