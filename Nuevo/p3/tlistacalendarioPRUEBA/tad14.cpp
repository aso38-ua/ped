#include <iostream>
#include "tcalendario.h"
#include "tlistacalendario.h"

using namespace std;

int main() {
    TCalendario a(1,1,2022, (char*) "a");
    TCalendario b(2,1,2022, (char*) "b");
    TCalendario c(3,1,2022, (char*) "c");
    TCalendario d(4,1,2022, (char*) "d");
    TCalendario e(5,1,2022, (char*) "e");
    TCalendario f(6,1,2022, (char*) "f");
    TCalendario g(7,1,2022, (char*) "g");
    TCalendario h(8,1,2022, (char*) "h");
    TCalendario i(9,1,2022, (char*) "i");

    TListaCalendario L1;
    L1.Insertar(a);
    L1.Insertar(c);
    L1.Insertar(d);
    L1.Insertar(e);
    L1.Insertar(f);

    TListaCalendario L2;
    L2.Insertar(b);
    L2.Insertar(c);
    L2.Insertar(d);
    L2.Insertar(g);
    L2.Insertar(h);
    L2.Insertar(i);

    TListaCalendario L3 = L1.SumarSubl(2, 4, L2, 0, 6);

    cout << "L3 = " << L3 << endl;

    return 0;
}

