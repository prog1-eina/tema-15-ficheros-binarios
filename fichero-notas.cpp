﻿/******************************************************************************\
 * Curso de Programación 1. Tema 15 (Ficheros binarios)
 * Autores: Miguel Ángel Latre
 * Última revisión: 2 de diciembre de 2021
 * Resumen: Funciones que trabajan con un fichero binario de pares NIP-nota.
 * Nota: El programa completo está contenido en este fichero, por lo que puede 
 *       compilarse y ejecutarse con la extensión Code Runner de Visual Studio 
 *       Code.
 *       También puede compilarse desde la terminal través de la orden
 *           g++ -Wall -Wextra fichero-notas.cpp -o fichero-notas
 *       y ejecutarse en Windows a través de la orden
 *           .\fichero-notas.exe
 *       o en Linux y macOS
 *           ./fichero-notas
\******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

const string NOMBRE_FICHERO = "prog1.dat";


/*
 * Pre:  ---
 * Post: Crea un fichero binario de nombre «nombreFichero» compuesto por
 *       una secuencia de pares (NIP, nota) solicitados interactivamente al
 *       usuario.
 */
void crearFicheroNotas(const string nombreFichero) {
    ofstream f;
    f.open(nombreFichero, ios::binary);
    if (f.is_open()) {
        cout << "Introduzca un NIP (0 para acabar): ";
        unsigned nip;
        cin >> nip;
        while (nip != 0) {
            cout << "Introduzca una nota: ";
            double nota;
            cin >> nota;

            f.write(reinterpret_cast<const char*>(&nip), sizeof(nip));
            f.write(reinterpret_cast<const char*>(&nota), sizeof(nota));

            cout << "Introduzca un NIP (0 para acabar): ";
            cin >> nip;
        }
        f.close();
    } else {
        cerr << "No se ha podido escribir en el fichero \"" << nombreFichero
             << "\"" << endl;
    }
}


/*
 * Pre:  «nombreFichero» es el nombre de un fichero existente binario cuya
 *       estructura consiste en una secuencia de pares (NIP, nota), de tipos
 *       int y double, respectivamente.
 * Post: Muestra en la pantalla del contenido del fichero de nombre
 *       «nombreFichero», de acuerdo con el siguiente formato de ejemplo:
 *         NIP   Nota
 *       ------------
 *       487524   7.9
 *       454844  10.0
 *       567896   6.3
 */
void mostrarFicheroNotas(const string nombreFichero) {
    ifstream f;
    f.open(nombreFichero, ios::binary);
    if (f.is_open()) {
        cout << "  NIP   Nota" << endl;
        cout << "------------" << endl;
        cout << fixed << setprecision(1);
        unsigned nip;
        while(f.read(reinterpret_cast<char*>(&nip), sizeof(nip))) {
            double nota;
            f.read(reinterpret_cast<char*>(&nota), sizeof(nota));
            cout << setw(6) << nip << " " << setw(5) << nota << endl;
        }
        f.close();
    } else {
        cerr << "No se ha podido leer el fichero \"" << nombreFichero
             << "\"" << endl;
    }
}


/*
 * Programa que crea un fichero binario de nombre «NOMBRE_FICHERO» compuesto por
 * una secuencia de pares (NIP, nota) solicitados interactivamente al usuario y,
 * tras ello, muestra en la pantalla del contenido del fichero recién creado, de
 * acuerdo con el siguiente formato de ejemplo:
 *         NIP   Nota
 *       ------------
 *       487524   7.9
 *       454844  10.0
 *       567896   6.3
 */
int main() {
    crearFicheroNotas(NOMBRE_FICHERO);
    mostrarFicheroNotas(NOMBRE_FICHERO);
    return 0;
}
