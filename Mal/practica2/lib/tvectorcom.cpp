#include <iostream>
#include <math.h>
#include "tvectorcom.h"
#include "tcomplejo.h"

using namespace std;

// Constructor por defecto
TVectorCom::TVectorCom()
{
    this->tamano = 0;
    this->c = NULL;
}
// Constructor a partir de un tamaño
TVectorCom::TVectorCom(int tamanyo)
{
    if (tamanyo <= 0)
    {
        this->tamano = 0;
        this->c = nullptr;
    }

    else
    {
        this->tamano = tamanyo;
        this->c = new TComplejo[tamanyo];
    }
}
// Constructor de copia
TVectorCom::TVectorCom(TVectorCom &vector)
{
    this->tamano = vector.tamano;
    this->c = vector.c;
}
// Destructor
TVectorCom::~TVectorCom()
{
    this->tamano = 0;
    this->c = nullptr;
}
// Sobrecarga del operador asignación
TVectorCom &TVectorCom::operator=(const TVectorCom &vector)
{
    this->~TVectorCom();
    this->tamano = vector.tamano;
    this->c = vector.c;

    return *this;
}

// MÉTODOS

// Sobrecarga del operador igualdad
bool TVectorCom::operator==(const TVectorCom &vector)
{
    bool devolver = true;
    if (this->tamano != vector.tamano)
    {
        devolver = false;
    }
    else
    {
        for (unsigned i = 0; i < vector.tamano; i++)
        {
            if (this->c[i] != vector.c[i])
            {
                devolver = false;
            }
        }
    }

    return devolver;
}
// Sobrecarga del operador desigualdad
bool TVectorCom::operator!=(const TVectorCom &vector)
{
    bool devolver = true;
    if (this->tamano == vector.tamano)
    {
        devolver = false;
    }
    else
    {
        for (unsigned i = 0; i < vector.tamano; i++)
        {
            if (this->c[i] == vector.c[i])
            {
                devolver = false;
            }
        }
    }

    return devolver;
}
// Sobrecarga del operador corchete (parte IZQUIERDA)
TComplejo &TVectorCom::operator[](int i)
{
    if (i <= tamano && i >= 1)
    {
        return (c[i - 1]);
    }
    return error;
}
// Sobrecarga del operador corchete (parte DERECHA)
TComplejo TVectorCom::operator[](int i) const
{
    if (i <= tamano && i >= 1)
        return (c[i - 1]);

    return error;
}
// Tamaño del vector (posiciones TOTALES)
int TVectorCom::Tamano()
{
    return this->tamano;
}
// Cantidad de posiciones OCUPADAS (TComplejo NO VACIO) en el vector
int TVectorCom::Ocupadas()
{
    int ocupadas = 0;
    for (int i = 0; i < tamano; i++)
    {
        if (c[i].Im() != 0 || c[i].Re() != 0)
        {
            ocupadas++;
        }
    }
    return ocupadas;
}
// Devuelve TRUE si existe el TComplejo en el vector
bool TVectorCom::ExisteCom(const TComplejo &vector)
{
    bool existe = false;
    for (int i = 0; i < this->tamano; i++)
    {
        if (vector.Im() == this->c[i].Im() && vector.Re() == this->c[i].Re())
        {
            existe = true;
        }
    }
    return existe;
}
// Mostrar por pantalla los elementos TComplejo del vector con PARTE REAL IGUAL
// O POSTERIOR al argumento
void TVectorCom::MostrarComplejos(double re)
{

    int Ntam = 0;
    for (int i = 0; i < tamano; i++)
    {
        if (this->c[i].Re() >= re)
        {
            Ntam++;
        }
    }

    int pos = -1;

    TComplejo *nuevoVector = new TComplejo[Ntam];

    for (int i = 0; i < tamano; i++)
    {
        if (this->c[i].Re() >= re)
        {
            pos++;
            nuevoVector[pos] = c[i].Re();
        }
    }

    cout << "[";
    for (int i = 0; i < Ntam; i++)
    {

        if (i != Ntam - 1)
        {
            cout << "(" << nuevoVector[i].Re() << " " << nuevoVector[i].Im() << ")"
                 << ", ";
        }
        else
        {
            cout << "(" << nuevoVector[i].Re() << " " << nuevoVector[i].Im() << ")";
        }
    }
    cout << "]";
}
// REDIMENSIONAR el vector de TComplejo
bool TVectorCom::Redimensionar(int n)
{
    bool redimensionado = false;

    if (n < 0)
    {
        redimensionado = false;
        return redimensionado;
    }

    else if (tamano == n)
    {
        redimensionado = false;
        return redimensionado;
    }

    else if (n > 0 && n > tamano)
    {
        TComplejo *nuevoVector = new TComplejo[n]; // Nuevo vector de TComplejos

        for (int i = 0; i < tamano; i++)
        {
            nuevoVector[i] = this->c[i];
        }

        for (int i = tamano; i < n; i++)
        {
            nuevoVector[i] = TComplejo();
        }

        delete[] this->c;      // Liberar memoria del vector original
        this->c = nuevoVector; // se asigna el nuevo vector al atributo c del objeto

        tamano = n;

        redimensionado = true;
        return redimensionado;
    }

    else if (n > 0 && n < tamano)
    {
        for (int i = n; i < tamano; i++)
        {
            this->c[i] = TComplejo(); // se asigna un complejo vacío (0,0) a las posiciones que se van a eliminar
        }
        tamano = n; // se actualiza el tamaño del vector

        redimensionado = true;
        return redimensionado;
    }

    else
    {
        return redimensionado;
    }
}

// FUNCIONES AMIGAS
//  Sobrecarga del operador salida
ostream &operator<<(ostream &os, const TVectorCom &vec)
{

    os << "[";
    if (vec.tamano != 0)
    {
        for (int i = 0; i < vec.tamano; i++)
        {
            if (i == vec.tamano - 1)
            {
                os << "(" << i + 1 << ") " << vec.c[i];
            }
            else
            {

                os << "(" << i + 1 << ") " << vec.c[i] << ", ";
            }
        }
    }
    os << "]";
    return os;

}
