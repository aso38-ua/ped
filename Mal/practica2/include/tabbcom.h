#ifndef _INC_TACOM
#define _INC_TACOM

#include <iostream>
#include "tvectorcom.h"
#include "tcomplejo.h"

class TNodoABB;

class TABBCom
{

    // Declaración de amistad con la clase TNodoABB
    friend class TNodoABB;

private:
    // Puntero al nodo
    TNodoABB *nodo;
    // AUXILIAR : Devuelve el recorrido en inorden
    void InordenAux(TVectorCom &, int &) const;
    // AUXILIAR : Devuelve el recorrido en preorden
    void PreordenAux(TVectorCom &, int &) const;
    // AUXILIAR : Devuelve el recorrido en postorden
    void PostordenAux(TVectorCom &, int &) const;

public:
    // Constructor por defecto
    TABBCom();
    // Constructor de copia
    TABBCom(const TABBCom &);
    // Destructor
    ~TABBCom();
    // Sobrecarga del operador asignación
    TABBCom &operator=(const TABBCom &);
    // Sobrecarga del operador igualdad
    bool operator==(const TABBCom &) const;
    // Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
    bool EsVacio() const;
    // Inserta el elemento en el árbol
    bool Insertar(TComplejo &);
    // Borra el elemento en el árbol
    bool Borrar(TComplejo &);
    // Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
    bool Buscar(TComplejo &);
    // Devuelve el elemento en la raíz del árbol
    TComplejo Raiz() const;
    // Devuelve la altura del árbol (la altura de un árbol vacío es 0)
    int Altura() const;
    // Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
    int Nodos() const;
    // Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
    int NodosHoja() const;
    // Devuelve el recorrido en inorden
    TVectorCom Inorden() const;
    // Devuelve el recorrido en preorden
    TVectorCom Preorden() const;
    // Devuelve el recorrido en postorden
    TVectorCom Postorden() const;
    // Devuelve el recorrido en niveles
    TVectorCom Niveles() const;
    // Sobrecarga del operador salida
    friend ostream &operator<<(ostream &, const TABBCom &);
    TComplejo BuscarMinimo() const;
    void Copiar (const TABBCom & );
};

class TNodoABB
{

    friend class TABBCom;

private:
    TComplejo item; // El elemento del nodo
    TABBCom iz, de; // Subárbol izquierdo y derecho

public:
    // Constructor por defecto
    TNodoABB();

    // Constructor de copia
    TNodoABB(TNodoABB &);

    // Destructor
    ~TNodoABB();

    // Sobrecarga del operador asignación
    TNodoABB &operator=(const TNodoABB &);
};

#endif