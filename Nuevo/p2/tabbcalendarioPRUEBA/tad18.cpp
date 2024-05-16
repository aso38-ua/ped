#include <iostream>
#include "../include/tabbcalendario.h"

using namespace std;

int main() {
    // Crear dos árboles de calendario
    TABBCalendario arbol1, arbol2;

    // Insertar eventos en el primer árbol
    arbol1.Insertar(TCalendario(1, 1, 2024, "Evento1"));
    arbol1.Insertar(TCalendario(2, 1, 2024, "Evento2"));
    arbol1.Insertar(TCalendario(3, 1, 2024, "Evento3"));
    arbol1.Insertar(TCalendario(4, 1, 2024, "Evento4"));

    // Insertar eventos en el segundo árbol
    arbol2.Insertar(TCalendario(5, 1, 2024, "Evento5"));
    arbol2.Insertar(TCalendario(6, 1, 2024, "Evento6"));
    arbol2.Insertar(TCalendario(7, 1, 2024, "Evento7"));
    arbol2.Insertar(TCalendario(8, 1, 2024, "Evento8"));

    // Mostrar contenido de los árboles
    cout << "Árbol 1:" << endl << arbol1 << endl;
    cout << "Árbol 2:" << endl << arbol2 << endl;

    // Realizar búsqueda de un evento en el primer árbol
    TCalendario eventoBuscado(3, 1, 2024, "Evento3");
    cout << "Buscar evento en árbol 1: " << (arbol1.Buscar(eventoBuscado) ? "Encontrado" : "No encontrado") << endl;

    // Realizar búsqueda de un evento en el segundo árbol
    TCalendario eventoNoExistente(10, 1, 2024, "EventoNoExistente");
    cout << "Buscar evento en árbol 2: " << (arbol2.Buscar(eventoNoExistente) ? "Encontrado" : "No encontrado") << endl;

    // Borrar un evento en el primer árbol
    arbol1.Borrar(TCalendario(2, 1, 2024, "Evento2"));

    // Borrar un evento en el segundo árbol
    arbol2.Borrar(TCalendario(8, 1, 2024, "Evento8"));

    // Mostrar resultado después de borrar eventos
    cout << "Árbol 1 después del borrado:" << endl << arbol1 << endl;
    cout << "Árbol 2 después del borrado:" << endl << arbol2 << endl;

    // Realizar suma de árboles
    TABBCalendario arbolSuma = arbol1 + arbol2;

    // Realizar resta de árboles
    TABBCalendario arbolResta = arbol1 - arbol2;

    // Mostrar resultado de la suma de árboles
    cout << "Resultado de la suma de árboles:" << endl << arbolSuma << endl;

    // Mostrar resultado de la resta de árboles
    cout << "Resultado de la resta de árboles:" << endl << arbolResta << endl;

    return 0;
}

