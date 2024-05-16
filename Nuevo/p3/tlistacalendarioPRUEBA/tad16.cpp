#include <iostream>
#include "tcalendario.h"
#include "tlistacalendario.h"

using namespace std;

int main() {
    // Crear elementos de calendario
    TCalendario cal1(1, 1, 2022, (char*)"Mensaje 1");
    TCalendario cal2(2, 1, 2022, (char*)"Mensaje 2");
    TCalendario cal3(3, 1, 2022, (char*)"Mensaje 3");
    TCalendario cal4(4, 1, 2022, (char*)"Mensaje 4");

    // Crear lista y añadir elementos
    TListaCalendario lista;
    lista.Insertar(cal1);
    lista.Insertar(cal2);
    lista.Insertar(cal3);
    lista.Insertar(cal4);

    // Mostrar lista inicial
    cout << "Lista inicial:" << endl;
    cout << lista << endl;

    // Borrar elemento en posición 2
    TListaPos pos = lista.Primera().Siguiente();
    lista.Borrar(pos);

    // Mostrar lista tras borrar elemento en posición 2
    cout << "Lista tras borrar elemento en posición 2:" << endl;
    cout << lista << endl;

    // Verificar si se borró el elemento en posición 2
    cout << "Elemento en posición 2 borrado: ";
    if (lista.Buscar(cal2))
        cout << "No";
    else
        cout << "Sí";
    cout << endl;

    return 0;
}

