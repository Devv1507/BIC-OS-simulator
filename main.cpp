/**
 * Programa para simular el funcionamiento del Ciclo Básico de Instrucciones (CBI) de un procesador.
 * 
 * Autores:
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
        cout << "Ingresa el nombre del programa (o 'exit' para salir): ";
        cin >> filename;
        cin.ignore();

        if (filename == "exit" || filename == "EXIT") {
            cout << "Saliendo del programa." << endl;
            break;
        }

        if (simulator.loadProgram(filename)) {
            simulator.executeProgram();
        } else {
            cout << "No se pudo cargar el programa. Intenta de nuevo." << endl;
        }
    } while (true);
    
}
