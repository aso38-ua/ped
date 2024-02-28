#include <iostream>
#include <TABBCom.h>
#include <TNodoABB.h>
#include "tcomplejo.h"

using namespace std;

// AUXILIAR : Devuelve el recorrido en inorden
void TABBCom::InordenAux(TVectorCom & vector, int & a) const{
    if (!this->EsVacio()) {
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
void TABBCom::PreordenAux(TVectorCom & v, int & posicion) const{
    if (!this->EsVacio()) {
        // Almacenar el elemento en el vector en la posición actual
        v[posicion] = this->nodo->item;
        // Incrementar la posición para el siguiente elemento en el vector
        posicion++;
        // Recorrer el subárbol izquierdo en preorden
        this->nodo->iz.PreordenAux(v, posicion);
        // Recorrer el subárbol derecho en preorden
        this->nodo->de.PreordenAux(v, posicion);
    }
}
// AUXILIAR : Devuelve el recorrido en postorden
void TABBCom::PostordenAux(TVectorCom & vector, int & a) const{
    
}

// Constructor por defecto
TABBCom::TABBCom (){
    this->nodo=NULL;
}
// Constructor de copia
TABBCom::TABBCom (const TABBCom & arbol){
    this->nodo->~TNodoABB();
    this->nodo=new TNodoABB(*arbol.nodo);
}
// Destructor
TABBCom::~TABBCom (){
    delete this->nodo;
}
// Sobrecarga del operador asignación
TABBCom & TABBCom::operator=(const TABBCom & arbol){
    this->nodo->~TNodoABB();
    this->nodo=new TNodoABB(*arbol.nodo);

    return *this;

}
// Sobrecarga del operador igualdad
bool TABBCom::operator==(const TABBCom & arbol) const{
    if (this->nodo==arbol.nodo)
    {
        return true;
    }

    else{
        return false;
    }
    
}
// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool TABBCom::EsVacio() const{
    if (this->nodo==NULL)
    {
        return true;
    }
    else{
        return false;
    }
    
}
// Inserta el elemento en el árbol
bool TABBCom::Insertar(const TComplejo &complejo){
    if (this->EsVacio())
    {
        nodo = new TNodoABB();
        nodo->item = complejo;
        return true;
    }
    else if (complejo == nodo->item){
        return false;
    }
    else{
        return nodo->de.Insertar(complejo);
    }
}
// Borra el elemento en el árbol
bool TABBCom::Borrar(const TComplejo &complejo){
    
}
// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
bool TABBCom::Buscar(const TComplejo &){

}
// Devuelve el elemento en la raíz del árbol
TComplejo TABBCom::Raiz() const{
    if (this->EsVacio()) {
        return TComplejo();
    }
    else {
        return this->nodo->item;
    }
}
// Devuelve la altura del árbol (la altura de un árbol vacío es 0)
int TABBCom::Altura() const{
    if (this->EsVacio())
    {
        return 0;
    }
    else{
        return 1 + max(nodo->iz.Nodos(),nodo->de.Nodos());
    }
}
// Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
int TABBCom::Nodos() const{
    if (this->EsVacio())
    {
        return 0;
    }
    else{
        return 1 + nodo->iz.Nodos() + nodo->de.Nodos();
    }
    
}
// Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
int TABBCom::NodosHoja() const{
    if (this->EsVacio())
    {
        return 0;
    }
    else{
        if (nodo->iz.EsVacio() && nodo->de.EsVacio()){
            return 1; // Si el nodo actual no tiene hijos, es una hoja
        }
        else{
            // Si el nodo actual tiene hijos, sumar el número de nodos hoja en sus subárboles izquierdo y derecho
            return nodo->iz.NodosHoja() + nodo->de.NodosHoja();
        }
    }
}
// Devuelve el recorrido en inorden
TVectorCom TABBCom::Inorden() const{
    // Posición en el vector que almacena el recorrido
    int posicion = 1;
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorCom v(Nodos());
    InordenAux(v, posicion);
    return v;
}
// Devuelve el recorrido en preorden
TVectorCom TABBCom::Preorden() const{
    // Posición en el vector que almacena el recorrido
    int posicion = 1;
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorCom v(Nodos());
    PreordenAux(v, posicion);
    return v;
}
// Devuelve el recorrido en postorden
TVectorCom TABBCom::Postorden() const{

}
// Devuelve el recorrido en niveles
TVectorCom TABBCom::Niveles() const{

}
// Sobrecarga del operador salida
ostream & operator<<(ostream &,const TABBCom &){

}