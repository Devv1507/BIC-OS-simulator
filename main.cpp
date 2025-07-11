/**
 * Program to simulate the operation of the Basic Instructions Cycle (BIC) of a processor.
 * 
 * Authors:
 *  - David Esteban Valencia Valencia 
 *  - Jeremy Astaiza
 *  - Juan Pablo Escamilla            
 *  - Nicolle Andrea Paz              
 *  - Santiago David Guerrero         
 * 
 * Tecnologia en Desarrollo de Software
 * Universidad del Valle
 */

#include <iostream>
#include "simulator.h"

using namespace std;

int main() {
    Simulator simulator;
    string filename;
    
    do {
        cout << "Type the program name (or 'exit' to quit): ";
        cin >> filename;
        cin.ignore();

        switch (filename[0]) {
            case 'e':
            case 'E':
                if (filename == "exit" || filename == "EXIT") {
                    cout << "Exiting the program." << endl;
                    return 0;
                }
                break;
        }

        if (simulator.loadProgram(filename)) {
            simulator.executeProgram();
        } else {
            cout << "The program could not be loaded. Try again." << endl;
        }
    } while (true);
    
}
