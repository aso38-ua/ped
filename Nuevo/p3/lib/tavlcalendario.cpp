#include <iostream>
#include "tavlcalendario.h"
#include "tcalendario.h"
#include "tvectorcalendario.h"
#include <string.h>
#include <string>
#include <cstring>
using namespace std;

TNodoAVL::TNodoAVL(){
    this->item=TCalendario();
    this->fe=NULL;
    //this->de=TAVLCalendario();
    //this->iz=TAVLCalendario();
}

TNodoAVL::TNodoAVL(const TNodoAVL &nodo){
    this->item = nodo.item;
    this->fe = nodo.fe;
    this->de = TAVLCalendario(nodo.de); // Llamada al constructor de copia de TAVLCalendario
    this->iz = TAVLCalendario(nodo.iz); // Llamada al constructor de copia de TAVLCalendario
}


// Constructor por defecto
TAVLCalendario::TAVLCalendario() : raiz(NULL) {}

// Constructor de copia
TAVLCalendario::TAVLCalendario(const TAVLCalendario &avl) {
    raiz = NULL;
    *this = avl;
}

// Destructor
TAVLCalendario::~TAVLCalendario() {
    if (raiz != NULL) {
        delete raiz;
        raiz = NULL;
    }
}

// Sobrecarga del operador asignación
TAVLCalendario & TAVLCalendario::operator=(const TAVLCalendario &avl) {
    if (this != &avl) {
        // Eliminar el árbol actual
        if (raiz != NULL) {
            delete raiz;
            raiz = NULL;
        }
        // Copiar el árbol avl
        if (avl.raiz != NULL) {
            raiz = new TNodoAVL(*(avl.raiz));
        }
    }
    return *this;
}
// Sobrecarga del operador igualdad
/*bool TAVLCalendario::operator==(const TAVLCalendario &avl) {
    return *raiz == *(avl.raiz);
}*/
// Sobrecarga del operador desigualdad
bool TAVLCalendario::operator!=(const TAVLCalendario &avl) {
    return !(*this == avl);
}
// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool TAVLCalendario::EsVacio() {
    return raiz == nullptr;
}
