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

    // Metodo para obtener indice de memoria desde un operando
    int getMemoryIndex(string operand) {
        if (!operand.empty() && operand[0] == 'D') {
            // Extrae el numero despues de 'D'
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
    
    // Metodo para cargar un valor en memoria
    void SET(vector<string> args) {
        int address = getMemoryIndex(args[1]);
        int value = stoi(args[2]);
        if (address != -1) {
            memory->write(address, value);
        }
    }
    
    // Metodo para cargar un valor de memoria a ACC
    void LDR(vector<string> args) {
        int address = getMemoryIndex(args[1]);
        if (address != -1) {
            MAR = address;
            MDR = memory->read(address);
            ACC = MDR;
            ICR++;
        }
    }
    
    // Metodo para sumar valores de memoria
    void ADD(vector<string> args) {
        // Primera forma: ADD D1 NULL NULL
        if (args.size() >= 2 && args[2] == "NULL") {
            int address = getMemoryIndex(args[1]);
            if (address != -1) {
                MAR = address;
                MDR = memory->read(address);
                ACC += MDR;
            }
        }
        // Segunda forma: ADD D1 D3 NULL
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
        // Tercera forma: ADD D1 D3 D4
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
    
    // Metodo para 
    void STR(vector<string> args) {
        int address = getMemoryIndex(args[1]);
        if (address != -1) {
            MAR = address;
            MDR = ACC;
            memory->write(address, MDR);
            ICR++;
        }
    }
    
    // Metodo para mostrar valores de acuerdo a una direccion de memoria
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
            cout << "UC = " << (controlUnit ? "Activo" : "Pausado") << endl;
        } else {
            int address = getMemoryIndex(args[1]);
            if (address != -1) {
                memory->show(address);
            }
        }
        ICR++;
    }
    
    // Memoria de instrucciones para incrementar un valor en 1
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
    
    // Memoria de instrucciones para decrementar un valor en 1
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
    
    // Metodo para pausar la ejecucion
    void PAUSE() {
        controlUnit = false;
        cout << "Simulacion Pausada. Presiona ENTER para continuar..." << endl;
        cin.get();
        controlUnit = true;
        ICR++;
    }
    
    // Metodo para finalizar la ejecucion
    void END() {
        cout << "Ejecucion Finalizada." << endl;
    }

    // Metodo para ejecutar una instruccion
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
            cout << "Instruccion Desconocida: " << opcode << endl;
        }
    }
};

#endif // CPU_H
