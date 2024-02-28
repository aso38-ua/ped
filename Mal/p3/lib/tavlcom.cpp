#include <iostream>
#include "tavlcom.h"

using namespace std;

// Implementación de TNodoAVL

TNodoAVL::TNodoAVL()
{
    fe = 0;
}

TNodoAVL::TNodoAVL(const TNodoAVL &avl)
{
    item = avl.item;
    this->iz = avl.iz;
    de = avl.de;
    fe = avl.fe;
}

TNodoAVL::~TNodoAVL()
{
    // Destructor implicito
}

TNodoAVL &TNodoAVL::operator=(const TNodoAVL &avl)
{
    if (this != &avl)
    {
        this->item = avl.item;
        this->iz = avl.iz;
        this->de = avl.de;
        this->fe = avl.fe;
    }
    return *this;
}

// Implementación de TAVLCom

void TAVLCom::InordenAux(TVectorCom &vec, int &pos) const
{
    if (raiz != NULL)
    {
        raiz->iz.InordenAux(vec, pos);
        vec[pos++] = raiz->item;
        raiz->de.InordenAux(vec, pos);
    }
}

// Implementación del método PreordenAux
void TAVLCom::PreordenAux(TVectorCom &vec, int &pos) const
{
    if (raiz != NULL)
    {
        vec[pos++] = raiz->item;
        raiz->iz.PreordenAux(vec, pos);
        raiz->de.PreordenAux(vec, pos);
    }
}

// Implementación del método PostordenAux
void TAVLCom::PostordenAux(TVectorCom &vec, int &pos) const
{
    if (raiz != NULL)
    {
        raiz->iz.PostordenAux(vec, pos);
        raiz->de.PostordenAux(vec, pos);
        vec[pos++] = raiz->item;
    }
}

TAVLCom::TAVLCom()
{
    this->raiz = NULL;
}

TAVLCom::TAVLCom(const TAVLCom &avl)
{
    this->raiz=NULL;
    Copiar(avl.raiz);
}

TAVLCom::~TAVLCom()
{
    TNodoAVL *aux = new TNodoAVL();
    
    while(!EsVacio()){
        aux = this->raiz;   
        raiz->iz.~TAVLCom();
        raiz->de.~TAVLCom();

        delete this->raiz;
        this->raiz = NULL;
    }
}

TAVLCom &TAVLCom::operator=(const TAVLCom &avl)
{
    if (this != &avl)
    {
        if (avl.raiz != nullptr)
        {
            raiz = new TNodoAVL(*avl.raiz);
        }
        else
        {
            raiz = nullptr;
        }
    }
    return *this;
}

bool TAVLCom::operator==(const TAVLCom &avl) const
{

    TVectorCom vec1 = this->Inorden();
    TVectorCom vec2 = avl.Inorden();

    if (vec1 == vec2)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool TAVLCom::operator!=(const TAVLCom &avl) const
{

    TVectorCom vec1 = this->Inorden();
    TVectorCom vec2 = avl.Inorden();

    if (vec1 != vec2)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool TAVLCom::EsVacio() const
{
    if (this->raiz == NULL)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool TAVLCom::Insertar(TComplejo& complejo)
{
    TNodoAVL* nuevo = new TNodoAVL();
    nuevo->item = complejo;

    if (EsVacio()) {
        raiz = nuevo;
        return true;
    }

    TNodoAVL* nodoActual = raiz;
    TNodoAVL* nodoPadre = nullptr;

    while (nodoActual != nullptr) {
        nodoPadre = nodoActual;

        if (complejo.Mod() < nodoActual->item.Mod()) {
            nodoActual = nodoActual->iz.raiz;
        } else if (complejo.Mod() > nodoActual->item.Mod()) {
            nodoActual = nodoActual->de.raiz;
        } else {
            // El elemento ya existe en el árbol, no se permite la inserción duplicada
            delete nuevo;
            return false;
        }
    }

    // En este punto, nodoPadre es el nodo donde se debe insertar el nuevo nodo

    if (complejo.Mod() < nodoPadre->item.Mod()) {
        nodoPadre->iz.raiz = nuevo;
    } else {
        nodoPadre->de.raiz = nuevo;
    }

    Balancear();
    return true;
}


bool TAVLCom::Buscar(TComplejo &complejo)
{
    if (EsVacio())
    {
        return false; // El árbol está vacío, el elemento no se encuentra
    }

    if (raiz->item == complejo)
    {
        return true; // Se encontró el elemento en la raíz del árbol
    }

    TNodoAVL *nodoActual = raiz;

    while (nodoActual != nullptr)
    {
        if (nodoActual->item == complejo)
        {
            return true; // Elemento encontrado
        }

        else if (nodoActual->item.Mod() < complejo.Mod())
        {
            nodoActual = nodoActual->de.raiz; // Continuar la búsqueda por el subárbol derecho
        }

        else if (nodoActual->item.Mod() > complejo.Mod())
        {
            nodoActual = nodoActual->iz.raiz; // Continuar la búsqueda por el subárbol izquierdo
        }

        else
        {
            // Si los módulos son iguales, se compara la parte real y la parte imaginaria del complejo
            if (nodoActual->item.Re() == complejo.Re() && nodoActual->item.Im() == complejo.Im())
            {
                return true; // Elemento encontrado
            }

            else if (nodoActual->item.Re() < complejo.Re() || (nodoActual->item.Re() == complejo.Re() && nodoActual->item.Im() < complejo.Im()))
            {
                nodoActual = nodoActual->de.raiz; // Continuar la búsqueda por el subárbol derecho
            }

            else
            {
                nodoActual = nodoActual->iz.raiz; // Continuar la búsqueda por el subárbol izquierdo
            }
        }
    }

    return false; // El elemento no se encuentra en el árbol
}

// BUSCAR RECURSVIO
/*bool TAVLCom::Buscar(TComplejo& complejo) const {
    if (raiz == nullptr) {
        return false;  // El árbol está vacío, el elemento no se encuentra
    }

    if (raiz->item == complejo) {
        return true;  // Se encontró el elemento en la raíz del árbol
    }

    if (raiz->item.Mod() < complejo.Mod()) {
        return raiz->de.Buscar(complejo);  // Continuar la búsqueda por el subárbol derecho
    }

    if (raiz->item.Mod() > complejo.Mod()) {
        return raiz->iz.Buscar(complejo);  // Continuar la búsqueda por el subárbol izquierdo
    }

    // Si los módulos son iguales, se compara la parte real y la parte imaginaria del complejo
    if (raiz->item.Re() == complejo.Re() && raiz->item.Im() == complejo.Im()) {
        return true;  // Elemento encontrado
    }

    if (raiz->item.Re() < complejo.Re() || (raiz->item.Re() == complejo.Re() && raiz->item.Im() < complejo.Im())) {
        return raiz->de.Buscar(complejo);  // Continuar la búsqueda por el subárbol derecho
    }

    return raiz->iz.Buscar(complejo);  // Continuar la búsqueda por el subárbol izquierdo
}*/

bool TAVLCom::Borrar(TComplejo &complejo)
{
    if (EsVacio())
    {
        return false; // El árbol está vacío, el elemento no se encuentra
    }
    else if (complejo.Mod() < raiz->item.Mod())
    {
        if (raiz->iz.Borrar(complejo))
        {
            // Se eliminó el elemento del subárbol izquierdo
            Balancear();
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (complejo.Mod() > raiz->item.Mod())
    {
        if (raiz->de.Borrar(complejo))
        {
            // Se eliminó el elemento del subárbol derecho
            Balancear();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        // El elemento se encuentra en la raíz
        if (raiz->iz.EsVacio() && raiz->de.EsVacio())
        {
            // Caso 1: El nodo a eliminar es una hoja
            delete raiz;
            raiz = nullptr;
        }
        else if (raiz->iz.EsVacio())
        {
            // Caso 2: El nodo a eliminar tiene solo un hijo derecho
            TNodoAVL *temp = raiz;
            raiz = raiz->de.raiz;
            temp->de.raiz = nullptr;
            delete temp;
        }
        else if (raiz->de.EsVacio())
        {
            // Caso 2: El nodo a eliminar tiene solo un hijo izquierdo
            TNodoAVL *temp = raiz;
            raiz = raiz->iz.raiz;
            temp->iz.raiz = nullptr;
            delete temp;
        }
        else
        {
            // Caso 3: El nodo a eliminar tiene ambos hijos
            TNodoAVL *sucesor = raiz->de.BuscarMin();
            raiz->item = sucesor->item;
            raiz->de.Borrar(sucesor->item);
            Balancear();
        }

        return true;
    }
}

int TAVLCom::Altura() const
{
    if (EsVacio()) {
        return 0;
    } else {
        int alturaIzq = raiz->iz.Altura();
        int alturaDer = raiz->de.Altura();
        return 1 + max(alturaIzq, alturaDer);
    }
}

TComplejo TAVLCom::Raiz() const
{
    if (this->EsVacio())
    {
        return TComplejo();
    }

    else
    {
        return this->raiz->item;
    }
}

int TAVLCom::Nodos() const
{
    if (this->EsVacio())
    {
        return 0;
    }
    else
    {
        return 1 + this->raiz->iz.Nodos() + this->raiz->de.Nodos();
    }
}

int TAVLCom::NodosHoja()
{
    if (this->EsVacio())
    {
        return 0;
    }
    else if (this->raiz->iz.EsVacio() && this->raiz->de.EsVacio())
    {
        // El nodo actual es una hoja
        return 1;
    }
    else
    {
        // Sumar los nodos hoja de los subárboles izquierdo y derecho
        return this->raiz->iz.NodosHoja() + this->raiz->de.NodosHoja();
    }
}

TVectorCom TAVLCom::Inorden() const
{
    int posicion = 1;
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorCom v(Nodos());
    InordenAux(v, posicion);
    return v;
}

TVectorCom TAVLCom::Preorden() const
{
    int posicion = 1;
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorCom v(Nodos());
    PreordenAux(v, posicion);
    return v;
}

TVectorCom TAVLCom::Postorden() const
{
    int posicion = 1;
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorCom v(Nodos());
    PostordenAux(v, posicion);
    return v;
}

ostream &operator<<(ostream &os, TAVLCom &avl)
{
    TVectorCom v = avl.Inorden();
    os << v;
    return os;
}

// Función auxiliar para realizar la copia recursiva de los nodos
TNodoAVL *TAVLCom::Copiar(TNodoAVL *nodo)
{
    if (nodo == nullptr)
    {
        return nullptr;
    }

    TNodoAVL *nuevoNodo = new TNodoAVL;
    nuevoNodo->item = nodo->item;
    nuevoNodo->iz.Copiar(nodo->iz.raiz);
    nuevoNodo->de.Copiar(nodo->de.raiz);
    nuevoNodo->fe = nodo->fe;

    return nuevoNodo;
}

void TAVLCom::RotacionII()
{
    TNodoAVL *d = raiz;
	TNodoAVL *b = raiz->iz.raiz;
	TNodoAVL *c = b->de.raiz;
	raiz = raiz->iz.raiz;
	raiz->de.raiz = d;
	raiz->de.raiz->iz.raiz = c;

}

void TAVLCom::RotacionDD()
{
    TNodoAVL *b = raiz;
	TNodoAVL *d = raiz->de.raiz;
	TNodoAVL *c = raiz->de.raiz->iz.raiz;
	raiz = d;
	b->de.raiz = c;
	raiz->iz.raiz = b;
}

void TAVLCom::RotacionID()
{
    raiz->iz.RotacionDD();
    RotacionII();
}

void TAVLCom::RotacionDI()
{
    raiz->de.RotacionII();
    RotacionDD();
}

void TAVLCom::Balancear()
{
    if (!EsVacio()) {
        raiz->iz.Balancear();
        raiz->de.Balancear();

        int alturaIzquierda = raiz->iz.Altura();
        int alturaDerecha = raiz->de.Altura();
        raiz->fe = alturaDerecha - alturaIzquierda;

        if (raiz->fe != -1 && raiz->fe != 0 && raiz->fe != 1) {
            // Rotación DD (+2, +1)
            if (raiz->fe == 2 && (raiz->de.raiz->fe == 1 || raiz->de.raiz->fe == 0))
                RotacionDD();
            else if (raiz->fe == -2 && (raiz->iz.raiz->fe == -1 || raiz->iz.raiz->fe == 0))
                RotacionII();
            else if (raiz->fe == -2 && raiz->iz.raiz->fe == 1)
                RotacionID();
            else if (raiz->fe == 2 && raiz->de.raiz->fe == -1)
                RotacionDI();
        }
    }
}


TNodoAVL *TAVLCom::BuscarMin()
{
    if (raiz->iz.EsVacio())
    {
        return raiz;
    }
    else
    {
        return raiz->iz.BuscarMin();
    }
}

void TAVLCom::ActualizarAltura()
{
    raiz->fe = raiz->de.Altura() - raiz->iz.Altura();
}
