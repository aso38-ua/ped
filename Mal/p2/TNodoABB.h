#ifndef TNODOABB_H
#define TNODOABB_H

#include "tcomplejo.h"
#include "TABBCom.h" // Se incluye la clase TABBCom para establecer la amistad


class TNodoABB {

    friend class TABBCom;

private:
    TComplejo item; // El elemento del nodo
    TABBCom iz, de; // Subárbol izquierdo y derecho

public:
    // Constructor por defecto
    TNodoABB();

    // Constructor de copia
    TNodoABB(TNodoABB&);

    // Destructor
    ~TNodoABB();

    // Sobrecarga del operador asignación
    TNodoABB& operator=(const TNodoABB&);

};

#endif