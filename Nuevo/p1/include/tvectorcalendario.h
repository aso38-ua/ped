#ifndef TVECTORCALENDARIO_H
#define TVECTORCALENDARIO_H

#include <sstream>
#include "tcalendario.h"

class TVectorCalendario {
private:
    TCalendario *c; // Array de TCalendario
    int tamano; // Tamaño del vector
    TCalendario error; // TCalendario para devolver en caso de error
    bool comprobarFecha(int, int, int);
    bool bisiesto(int);

public:
    // Constructor por defecto
    TVectorCalendario();

    // Constructor a partir de un tamaño
    TVectorCalendario(int);

    // Constructor de copia
    TVectorCalendario(const TVectorCalendario&);

    // Destructor
    ~TVectorCalendario();

    // Sobrecarga del operador de asignación
    TVectorCalendario& operator=(const TVectorCalendario&);

    // Sobrecarga del operador de igualdad
    bool operator==(const TVectorCalendario&) const;

    // Sobrecarga del operador de desigualdad
    bool operator!=(const TVectorCalendario&) const;

    // Sobrecarga del operador corchete (parte IZQUIERDA)
    TCalendario& operator[](int);

    // Sobrecarga del operador corchete (parte DERECHA)
    TCalendario operator[](int) const;

    // Tamaño del vector (posiciones TOTALES)
    int Tamano() const;

    // Cantidad de posiciones OCUPADAS (no vacías) en el vector
    int Ocupadas() const;

    // Devuelve TRUE si existe el calendario en el vector
    bool ExisteCal(const TCalendario&) const;

    // Mostrar por pantalla mensajes de TCalendario en el vector, de fecha IGUAL O POSTERIOR a la pasada
    void MostrarMensajes(int, int, int);

    // REDIMENSIONAR el vector de TCalendario
    bool Redimensionar(int);

    // Sobrecarga del operador de inserción
    friend ostream& operator<<(ostream&, const TVectorCalendario&);
};

#endif
