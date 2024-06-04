#include <iostream>
#include "tcalendario.h"
#include "tlistacalendario.h"

using namespace std;

int main() {
    TCalendario a(1, 1, 2022, (char *)"Mensaje 1");
    TCalendario b(2, 1, 2022, (char *)"Mensaje 2");
    TCalendario c(3, 1, 2022, (char *)"Mensaje 3");
    TCalendario d(4, 1, 2022, (char *)"Mensaje 4");

    TListaCalendario lista;
    lista.Insertar(a);
    lista.Insertar(b);
    lista.Insertar(c);
    lista.Insertar(d);

    cout << "Lista inicial:" << endl;
    cout << lista << endl;

    TCalendario obj(2, 1, 2022, (char *)"Mensaje 2");
    bool borrado = lista.Borrar(obj);

    cout << "Lista tras borrar elemento (2, 1, 2022):" << endl;
    cout << lista << endl;
    cout << "Elemento (2, 1, 2022) borrado: " << (borrado ? "Sí" : "No") << endl;

    return 0;
}

