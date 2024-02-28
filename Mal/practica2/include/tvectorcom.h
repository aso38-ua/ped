#ifndef _VEC_TCOM
#define _VEC_TCOM

#include <iostream>
#include "tcomplejo.h"

class TVectorCom
{

private:
    TComplejo *c;
    int tamano;

    TComplejo error;

public:
    // Constructor por defecto
    TVectorCom();
    // Constructor a partir de un tamaño
    TVectorCom(int);
    // Constructor de copia
    TVectorCom(TVectorCom &);
    // Destructor
    ~TVectorCom();
    // Sobrecarga del operador asignación
    TVectorCom &operator=(const TVectorCom &);

    // MÉTODOS

    // Sobrecarga del operador igualdad
    bool operator==(const TVectorCom &);
    // Sobrecarga del operador desigualdad
    bool operator!=(const TVectorCom &);
    // Sobrecarga del operador corchete (parte IZQUIERDA)
    TComplejo &operator[](int);
    // Sobrecarga del operador corchete (parte DERECHA)
    TComplejo operator[](int) const;
    // Tamaño del vector (posiciones TOTALES)
    int Tamano();
    // Cantidad de posiciones OCUPADAS (TComplejo NO VACIO) en el vector
    int Ocupadas();
    // Devuelve TRUE si existe el TComplejo en el vector
    bool ExisteCom(const TComplejo &);
    // Mostrar por pantalla los elementos TComplejo del vector con PARTE REAL IGUAL
    // O POSTERIOR al argumento
    void MostrarComplejos(double);
    // REDIMENSIONAR el vector de TComplejo
    bool Redimensionar(int);

    // FUNCIONES AMIGAS
    //  Sobrecarga del operador salida
    friend ostream &operator<<(ostream &, const TVectorCom &);
};

#endif