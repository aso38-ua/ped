#include <iostream>
#include "tabbcom.h"
#include <queue>

using namespace std;

// Constructor por defecto
TNodoABB::TNodoABB()
{
}
// Constructor de copia
TNodoABB::TNodoABB(TNodoABB &nodo)
{
    this->item = nodo.item;
    this->de = nodo.de;
    this->iz = nodo.iz;
}
// Destructor
TNodoABB::~TNodoABB()
{
}
// Sobrecarga del operador asignación
TNodoABB &TNodoABB::operator=(const TNodoABB &nodo)
{
    this->~TNodoABB();
    this->item = nodo.item;
    this->de = nodo.de;
    this->iz = nodo.iz;

    return *this;
}

// AUXILIAR : Devuelve el recorrido en inorden
void TABBCom::InordenAux(TVectorCom &vector, int &a) const
{
    if (!this->EsVacio())
    {
        // Recorrer el subárbol izquierdo en inorden
        this->nodo->iz.InordenAux(vector, a);
        // Almacenar el elemento en el vector en la posición actual
        vector[a] = this->nodo->item;
        // Incrementar la posición para el siguiente elemento en el vector
        a++;
        // Recorrer el subárbol derecho en inorden
        this->nodo->de.InordenAux(vector, a);
    }
}
// AUXILIAR : Devuelve el recorrido en preorden
void TABBCom::PreordenAux(TVectorCom &v, int &a) const
{
    if (!this->EsVacio())
    {
        // Almacenar el elemento en el vector en la posición actual
        v[a] = this->nodo->item;
        // Incrementar la posición para el siguiente elemento en el vector
        a++;
        // Recorrer el subárbol izquierdo en preorden
        this->nodo->iz.PreordenAux(v, a);
        // Recorrer el subárbol derecho en preorden
        this->nodo->de.PreordenAux(v, a);
    }
}
// AUXILIAR : Devuelve el recorrido en postorden
void TABBCom::PostordenAux(TVectorCom &vector, int &a) const
{
    if (!this->EsVacio())
    {
        // Recorrer el subárbol izquierdo en postorden
        this->nodo->iz.PostordenAux(vector, a);
        // Recorrer el subárbol derecho en postorden
        this->nodo->de.PostordenAux(vector, a);
        // Almacenar el elemento en el vector en la posición actual
        vector[a] = this->nodo->item;
        // Incrementar la posición para el siguiente elemento en el vector
        a++;
    }
}

// Constructor por defecto
TABBCom::TABBCom()
{
    this->nodo = NULL;
}
// Constructor de copia
TABBCom::TABBCom(const TABBCom &arbol)
{
    Copiar(arbol);
}
// Destructor
TABBCom::~TABBCom()
{
    if (nodo != NULL)
    {
        delete this->nodo;
        this->nodo = NULL;
    }
}
// Sobrecarga del operador asignación
TABBCom &TABBCom::operator=(const TABBCom &arbol)
{
    (*this).~TABBCom();
    Copiar(arbol);
    return *this;
}
// Sobrecarga del operador igualdad
bool TABBCom::operator==(const TABBCom &arbol) const
{
    if (Inorden()==arbol.Inorden())
    {
        return true;
    }

    else
    {
        return false;
    }
}
// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool TABBCom::EsVacio() const
{
    if (this->nodo == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Inserta el elemento en el árbol
bool TABBCom::Insertar(TComplejo &complejo)
{
    if (this->EsVacio())
    {
        nodo = new TNodoABB();
        this->nodo->item = complejo;
        return true;
    }

    else if (this->Buscar(complejo))
    {
        return false;
    }

    else if (this->nodo->de.EsVacio() && this->nodo->iz.EsVacio())
    {

        if (this->nodo->item.Mod() > complejo.Mod())
        {
            this->nodo->iz.nodo = new TNodoABB();
            this->nodo->iz.nodo->item = complejo;
            return true;
        }
        else if (this->nodo->item.Mod() < complejo.Mod())
        {
            this->nodo->de.nodo = new TNodoABB();
            this->nodo->de.nodo->item = complejo;
            return true;
        }
        else
        {
            if (this->nodo->item.Re() > complejo.Re())
            {
                this->nodo->iz.nodo = new TNodoABB();
                this->nodo->iz.nodo->item = complejo;
                return true;
            }
            else if (this->nodo->item.Re() < complejo.Re())
            {
                this->nodo->de.nodo = new TNodoABB();
                this->nodo->de.nodo->item = complejo;
                return true;
            }
            else
            {
                if (this->nodo->item.Im() > complejo.Im())
                {
                    this->nodo->iz.nodo = new TNodoABB();
                    this->nodo->iz.nodo->item = complejo;
                    return true;
                }
                else
                {
                    this->nodo->de.nodo = new TNodoABB();
                    this->nodo->de.nodo->item = complejo;
                    return true;
                }
            }
        }
    }

    else
    {
        if (this->nodo->item.Mod() > complejo.Mod())
        {
            this->nodo->iz.Insertar(complejo);
        }
        else if (this->nodo->item.Mod() < complejo.Mod())
        {
            this->nodo->de.Insertar(complejo);
        }
        else
        {
            if (this->nodo->item.Re() > complejo.Re())
            {
                this->nodo->iz.Insertar(complejo);
            }
            else if (this->nodo->item.Re() < complejo.Re())
            {
                this->nodo->de.Insertar(complejo);
            }
            else
            {
                if (this->nodo->item.Im() > complejo.Im())
                {
                    this->nodo->iz.Insertar(complejo);
                }
                else
                {
                    this->nodo->de.Insertar(complejo);
                }
            }
        }
    }
    return true;
}
// Borra el elemento en el árbol
bool TABBCom::Borrar(TComplejo &complejo)
{
    if (this->EsVacio())
    {
        return false;
    }

    else if (this->Buscar(complejo) == false)
    {
        return false;
    }

    else if (this->nodo->item == complejo)
    {
        if (this->nodo->iz.EsVacio() && this->nodo->de.EsVacio())
        {
            delete this->nodo;
            this->nodo = NULL;
            return true;
        }

        else if (this->nodo->iz.EsVacio() && !this->nodo->de.EsVacio())
        {
            TNodoABB *tmp = this->nodo;
            this->nodo = this->nodo->de.nodo;
            tmp->de.nodo = NULL;
            delete tmp;
            return true;
        }

        else if (!this->nodo->iz.EsVacio() && this->nodo->de.EsVacio())
        {
            TNodoABB *tmp = this->nodo;
            this->nodo = this->nodo->iz.nodo;
            tmp->iz.nodo = NULL;
            delete tmp;
            return true;
        }

        else
        {
            TComplejo minimo = this->nodo->de.BuscarMinimo();
            this->nodo->item = minimo;
            return this->nodo->de.Borrar(minimo);
        }
    }
    else
    {
        if (this->nodo->item.Mod() > complejo.Mod())
        {
            this->nodo->iz.Borrar(complejo);
        }
        else if (this->nodo->item.Mod() < complejo.Mod())
        {
            this->nodo->de.Borrar(complejo);
        }
        else
        {
            if (this->nodo->item.Re() > complejo.Re())
            {
                this->nodo->iz.Borrar(complejo);
            }
            else if (this->nodo->item.Re() < complejo.Re())
            {
                this->nodo->de.Borrar(complejo);
            }
            else
            {
                if (this->nodo->item.Im() > complejo.Im())
                {
                    this->nodo->iz.Borrar(complejo);
                }
                else
                {
                    this->nodo->de.Borrar(complejo);
                }
            }
        }
    }
}
// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
bool TABBCom::Buscar(TComplejo &complejo)
{
    if (this->EsVacio())
    {
        return false;
    }
    else if (this->nodo->item == complejo)
    {
        return true;
    }
    else
    {
        if (this->nodo->item.Mod() > complejo.Mod())
        {
            this->nodo->iz.Buscar(complejo);
        }
        else if (this->nodo->item.Mod() < complejo.Mod())
        {
            this->nodo->de.Buscar(complejo);
        }
        else
        {
            if (this->nodo->item.Re() > complejo.Re())
            {
                this->nodo->iz.Buscar(complejo);
            }
            else if (this->nodo->item.Re() < complejo.Re())
            {
                this->nodo->de.Buscar(complejo);
            }
            else
            {
                if (this->nodo->item.Im() > complejo.Im())
                {
                    this->nodo->iz.Buscar(complejo);
                }
                else
                {
                    this->nodo->de.Buscar(complejo);
                }
            }
        }
    }
}
// Devuelve el elemento en la raíz del árbol
TComplejo TABBCom::Raiz() const
{
    if (this->EsVacio())
    {
        return TComplejo();
    }
    else
    {
        return this->nodo->item;
    }
}
// Devuelve la altura del árbol (la altura de un árbol vacío es 0)
int TABBCom::Altura() const
{
    if (this->EsVacio())
    {
        return 0;
    }
    else
    {
        return 1 + max(nodo->iz.Nodos(), nodo->de.Nodos());
    }
}
// Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
int TABBCom::Nodos() const
{
    if (this->EsVacio())
    {
        return 0;
    }
    else
    {
        return 1 + nodo->iz.Nodos() + nodo->de.Nodos();
    }
}
// Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
int TABBCom::NodosHoja() const
{
    if (this->EsVacio())
    {
        return 0;
    }
    else
    {
        if (nodo->iz.EsVacio() && nodo->de.EsVacio())
        {
            return 1; // Si el nodo actual no tiene hijos, es una hoja
        }
        else
        {
            // Si el nodo actual tiene hijos, sumar el número de nodos hoja en sus subárboles izquierdo y derecho
            return nodo->iz.NodosHoja() + nodo->de.NodosHoja();
        }
    }
}
// Devuelve el recorrido en inorden
TVectorCom TABBCom::Inorden() const
{
    // Posición en el vector que almacena el recorrido
    int posicion = 1;
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorCom v(Nodos());
    InordenAux(v, posicion);
    return v;
}
// Devuelve el recorrido en preorden
TVectorCom TABBCom::Preorden() const
{
    // Posición en el vector que almacena el recorrido
    int posicion = 1;
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorCom v(Nodos());
    PreordenAux(v, posicion);
    return v;
}
// Devuelve el recorrido en postorden
TVectorCom TABBCom::Postorden() const
{
    // Posición en el vector que almacena el recorrido
    int posicion = 1;
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorCom v(Nodos());
    PostordenAux(v, posicion);
    return v;
}
// Devuelve el recorrido en niveles
TVectorCom TABBCom::Niveles() const
{
    TVectorCom v;

    if (this->EsVacio())
    {
        return v;
    }

    queue<TABBCom> cola;
    TABBCom subarbol = *this;

    cola.push(subarbol);

    while (!cola.empty())
    {
        subarbol = cola.front();
        cola.pop();

        if (!subarbol.EsVacio())
        {
            v.Redimensionar(v.Tamano() + 1);
            v[v.Tamano() - 1] = subarbol.nodo->item;

            cola.push(subarbol.nodo->iz);
            cola.push(subarbol.nodo->de);
        }
    }

    return v;
}
// Sobrecarga del operador salida
ostream &operator<<(ostream &os, const TABBCom &complejo)
{
    os << complejo.Niveles();
    return os;
}

TComplejo TABBCom::BuscarMinimo() const
{
    if (this->EsVacio())
    {
        // Devolvemos un complejo con valor nulo
        return TComplejo();
    }

    if (this->nodo->iz.EsVacio())
    {
        // Si no hay nodo izquierdo, el mínimo es el nodo actual
        return this->nodo->item;
    }

    // Buscamos el mínimo en el subárbol izquierdo
    return this->nodo->iz.BuscarMinimo();
}

void TABBCom::Copiar (const TABBCom &arbol)
{
    if (arbol.nodo != NULL)
    {
        TNodoABB *aux = new TNodoABB();
        aux->item = arbol.nodo->item;
        nodo = aux;
        nodo->iz.Copiar(arbol.nodo->iz);
        nodo->de.Copiar(arbol.nodo->de);
    }
        else nodo = NULL;   
}