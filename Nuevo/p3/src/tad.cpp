#include <iostream>
#include "tavlcalendario.h"
#include "tlistacalendario.h"

int main() {
    TAVLCalendario avl;
    TListaCalendario lista;

    // Insertar elementos en el AVL y en la lista
    TCalendario cal1(1, 1, 2020, nullptr);
    TCalendario cal2(2, 1, 2020, nullptr);
    TCalendario cal3(3, 1, 2020, nullptr);

    avl.Insertar(cal1);
    avl.Insertar(cal2);
    avl.Insertar(cal3);

    lista.Insertar(cal1);
    lista.Insertar(cal2);
    lista.Insertar(cal3);

    int *resultados = avl.BuscaAVL(lista);

    for (int i = 0; i < lista.Longitud(); ++i) {
        std::cout << "Posición " << i + 1 << ": " << resultados[i] << std::endl;
    }

    delete[] resultados;
    return 0;
}
