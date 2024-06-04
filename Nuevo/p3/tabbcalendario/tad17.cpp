#include <iostream>
#include "../include/tabbcalendario.h"
#include <string.h>
#include <string>
#include <cstring>
using namespace std;

int main() {
    TABBCalendario arbol1, arbol2;

    arbol1.Insertar(TCalendario(1, 1, 2024, "Evento1"));
    arbol1.Insertar(TCalendario(2, 1, 2024, "Evento2"));
    arbol1.Insertar(TCalendario(3, 1, 2024, "Evento3"));
    arbol1.Insertar(TCalendario(4, 1, 2024, "Evento4"));

    arbol2.Insertar(TCalendario(5, 1, 2024, "Evento5"));
    arbol2.Insertar(TCalendario(6, 1, 2024, "Evento6"));
    arbol2.Insertar(TCalendario(7, 1, 2024, "Evento7"));
    arbol2.Insertar(TCalendario(8, 1, 2024, "Evento8"));

    cout << "Árbol 1:" << endl;
    TVectorCalendario vec1 = arbol1.Inorden();
    for (int i = 1; i <= vec1.Tamano(); i++) {
        cout << "[" << vec1[i].Dia() << "/" << vec1[i].Mes() << "/" << vec1[i].Anyo() << "] \"" << vec1[i].Mensaje() << "\" ";
    }
    cout << endl;

    cout << "Árbol 2:" << endl;
    TVectorCalendario vec2 = arbol2.Inorden();
    for (int i = 1; i <= vec2.Tamano(); i++) {
        cout << "[" << vec2[i].Dia() << "/" << vec2[i].Mes() << "/" << vec2[i].Anyo() << "] \"" << vec2[i].Mensaje() << "\" ";
    }
    cout << endl;

    TABBCalendario arbolSuma = arbol1 + arbol2;
    cout << "Resultado de la suma de árboles:" << endl;
    TVectorCalendario vecSuma = arbolSuma.Inorden();
    for (int i = 1; i <= vecSuma.Tamano(); i++) {
        cout << "[" << vecSuma[i].Dia() << "/" << vecSuma[i].Mes() << "/" << vecSuma[i].Anyo() << "] \"" << vecSuma[i].Mensaje() << "\" ";
    }
    cout << endl;

    TABBCalendario arbolResta = arbol1 - arbol2;
    cout << "Resultado de la resta de árboles:" << endl;
    TVectorCalendario vecResta = arbolResta.Inorden();
    for (int i = 1; i <= vecResta.Tamano(); i++) {
        cout << "[" << vecResta[i].Dia() << "/" << vecResta[i].Mes() << "/" << vecResta[i].Anyo() << "] \"" << vecResta[i].Mensaje() << "\" ";
    }
    cout << endl;

    return 0;
}

