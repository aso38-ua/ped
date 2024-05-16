#include <iostream>
#include "tcalendario.h"
#include "tlistacalendario.h"

using namespace std;

int main() {
    TCalendario a(1, 1, 1977, (char*) "uno");
    TCalendario b(1, 1, 1980, (char*) "dos");
    TListaCalendario l1;
  
    l1.Insertar(a);   
    l1.Insertar(b);
    l1.Insertar(a + 3);

    cout << "Prueba de función Buscar:" << endl;
    cout << "Elemento a buscar: " << b << endl;
    if (l1.Buscar(b)) {
        cout << "El elemento " << b << " se encontró en la lista." << endl;
    } else {
        cout << "El elemento " << b << " no se encontró en la lista." << endl;
    }

    cout << "Elemento a buscar: " << TCalendario(1, 1, 1990, (char*)"tres") << endl;
    if (l1.Buscar(TCalendario(1, 1, 1990, (char*)"tres"))) {
        cout << "El elemento " << TCalendario(1, 1, 1990, (char*)"tres") << " se encontró en la lista." << endl;
    } else {
        cout << "El elemento " << TCalendario(1, 1, 1990, (char*)"tres") << " no se encontró en la lista." << endl;
    }

    return 0;
}

