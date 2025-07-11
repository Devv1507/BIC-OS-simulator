#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <vector>
#include "memory.h"
#include "alu.h"

using namespace std;

class CPU {
private:
    int ACC;
    int ICR;
    int MAR;
    int MDR;
    bool controlUnit; // UC
    Memory* memory;
    ALU* alu;

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
        this->ACC = 0;
        this->ICR = 0;
        this->MAR = 0;
        this->MDR = 0;
        this->controlUnit = true;
        this->alu = new ALU();
    }
    
    // Method to load a value into memory
    void SET(vector<string> args) {
        int address = this->getMemoryIndex(args[1]);
        int value = stoi(args[2]);
        if (address != -1) {
            this->memory->write(address, value);
        }
    }
    
    // Method to load a value from memory to ACC
    void LDR(vector<string> args) {
        int address = this->getMemoryIndex(args[1]);
        if (address != -1) {
            this->MAR = address;
            this->MDR = this->memory->read(address);
            this->ACC = this->MDR;
            this->ICR++;
        }
    }
    
    // Method to sum memory values using ALU
    void ADD(vector<string> args) {
        int validArgs = 0;
        for (int i = 1; i < args.size(); i++) {
            if (args[i] != "NULL") {
                validArgs++;
            }
        }
        
        switch (validArgs) {
            case 1: {
                // First way: ADD D1 NULL NULL (Suma el valor de D1 al Acumulador)
                if (args.size() >= 2 && args[2] == "NULL") {
                    int address = this->getMemoryIndex(args[1]);
                    if (address != -1) {
                        this->MAR = address;
                        this->MDR = this->memory->read(address);
                        // CPU delegates the addition to ALU
                        this->ACC = this->alu->add(this->ACC, this->MDR);
                    }
                }
                break;
            }
            case 2: {
                // Second way: ADD D1 D3 NULL (Suma D1 y D3, guarda en Acumulador)
                if (args.size() >= 3 && args[3] == "NULL") {
                    int address1 = this->getMemoryIndex(args[1]);
                    int address2 = this->getMemoryIndex(args[2]);
                    if (address1 != -1 && address2 != -1) {
                        // Leer primer operando
                        this->MAR = address1;
                        int operand1 = this->memory->read(address1);
                        
                        // Leer segundo operando
                        this->MAR = address2;
                        int operand2 = this->memory->read(address2);

                        // La CPU delega la suma a la ALU
                        this->ACC = this->alu->add(operand1, operand2);
                    }
                }
                break;
            }
            case 3: { // Third way: ADD D1 D3 D4 (Suma D1 y D3, guarda en D4 y Acumulador)
                if (args.size() >= 4) {
                    int address1 = this->getMemoryIndex(args[1]);
                    int address2 = this->getMemoryIndex(args[2]);
                    int address3 = this->getMemoryIndex(args[3]);
                    if (address1 != -1 && address2 != -1 && address3 != -1) {
                        this->MAR = address1;
                        int operand1 = this->memory->read(address1);
                        
                        this->MAR = address2;
                        int operand2 = this->memory->read(address2);
                        
                        // CPU delegates the addition of operands to ALU
                        int result = this->alu->add(operand1, operand2);
                        
                        this->ACC = result;
                        this->MAR = address3;
                        this->MDR = this->ACC;
                        this->memory->write(address3, this->MDR);
                    }
                }
                break;
            }
        }
        this->ICR++;
    }
    
    // Method to store the contents of the ACC into memory
    void STR(vector<string> args) {
        int address = this->getMemoryIndex(args[1]);
        if (address != -1) {
            this->MAR = address;
            this->MDR = this->ACC;
            this->memory->write(address, this->MDR);
            this->ICR++;
        }
    }
    
    // Method to display values according to a memory address
    void SHW(vector<string> args) {
        switch (args[1][0]) {
            case 'A':
                if (args[1] == "ACC") {
                    cout << "ACC = " << this->ACC << endl;
                }
                break;
            case 'I':
                if (args[1] == "ICR") {
                    cout << "ICR = " << this->ICR << endl;
                }
                break;
            case 'M':
                if (args[1] == "MAR") {
                    cout << "MAR = " << this->MAR << endl;
                } else if (args[1] == "MDR") {
                    cout << "MDR = " << this->MDR << endl;
                }
                break;
            case 'U':
                if (args[1] == "UC") {
                    cout << "UC = " << (this->controlUnit ? "Active" : "Paused") << endl;
                }
                break;
            default:
                int address = this->getMemoryIndex(args[1]);
                if (address != -1) {
                    this->memory->show(address);
                }
                break;
        }
        this->ICR++;
    }
    
    // Instruction memory for incrementing a value by 1 using ALU
    void INC(vector<string> args) {
        int address = this->getMemoryIndex(args[1]);
        if (address != -1) {
            this->MAR = address;
            this->MDR = this->memory->read(address);
            
            // CPU delegates the increment to ALU
            int result = this->alu->increment(this->MDR);
            
            this->memory->write(address, result);
            this->ICR++;
        }
    }
    
    // MODIFICADO: Instruction memory for decrementing a value by 1 using ALU
    void DEC(vector<string> args) {
        int address = this->getMemoryIndex(args[1]);
        if (address != -1) {
            this->MAR = address;
            this->MDR = this->memory->read(address);

            // La CPU delega el decremento a la ALU
            int result = this->alu->decrement(this->MDR);

            this->memory->write(address, result);
            this->ICR++;
        }
    }
    
    // Method to pause the execution
    void PAUSE() {
        this->controlUnit = false;
        cout << "Simulation paused. Press ENTER to continue..." << endl;
        cin.get();
        this->controlUnit = true;
        this->ICR++;
    }
    
    // Method to end the execution
    void END() {
        cout << "Execution completed." << endl;
    }

    // Method to execute an instruction
    void executeInstruction(vector<string> instruction) {
        string opcode = instruction[0];
        
        switch (opcode[0]) {
            case 'S':
                if (opcode == "SET") {
                    SET(instruction);
                } else if (opcode == "SHW") {
                    SHW(instruction);
                } else if (opcode == "STR") {
                    STR(instruction);
                }
                break;
            case 'L':
                if (opcode == "LDR") {
                    LDR(instruction);
                }
                break;
            case 'A':
                if (opcode == "ADD") {
                    ADD(instruction);
                }
                break;
            case 'I':
                if (opcode == "INC") {
                    INC(instruction);
                }
                break;
            case 'D':
                if (opcode == "DEC") {
                    DEC(instruction);
                }
                break;
            case 'P':
                if (opcode == "PAUSE") {
                    PAUSE();
                }
                break;
            case 'E':
                if (opcode == "END") {
                    END();
                }
                break;
            default:
                cout << "Unknown instruction: " << opcode << endl;
                break;
        }
    }
};

#endif // CPU_H
