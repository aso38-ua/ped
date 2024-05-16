#include <iostream>
#include "tabbcalendario.h"

using namespace std;

int main() {
    TABBCalendario arbol1, arbol2;

    // Insertamos algunos elementos en el primer árbol
    arbol1.Insertar(TCalendario(1, 1, 2024, "Evento1"));
    arbol1.Insertar(TCalendario(2, 1, 2024, "Evento2"));
    arbol1.Insertar(TCalendario(3, 1, 2024, "Evento3"));
    arbol1.Insertar(TCalendario(4, 1, 2024, "Evento4"));

    // Insertamos algunos elementos en el segundo árbol
    arbol2.Insertar(TCalendario(5, 1, 2024, "Evento5"));
    arbol2.Insertar(TCalendario(6, 1, 2024, "Evento6"));
    arbol2.Insertar(TCalendario(7, 1, 2024, "Evento7"));
    arbol2.Insertar(TCalendario(8, 1, 2024, "Evento8"));

    // Imprimimos los árboles
    cout << "Árbol 1:" << endl << arbol1 << endl;
    cout << "Árbol 2:" << endl << arbol2 << endl;

    // Realizamos la suma de los árboles
    TABBCalendario arbolSuma = arbol1 + arbol2;
    cout << "Resultado de la suma de árboles:" << endl << arbolSuma << endl;

    // Realizamos la resta de los árboles
    TABBCalendario arbolResta = arbol1 - arbol2;
    cout << "Resultado de la resta de árboles:" << endl << arbolResta << endl;

    return 0;
}

