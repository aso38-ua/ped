#include <iostream>
#include <TNodoABB.h>
#include <TABBCom.h>

using namespace std;

// Constructor por defecto
TNodoABB::TNodoABB (){
    this->item=TComplejo();
    this->de=TABBCom();
    this->iz=TABBCom();
}
// Constructor de copia
TNodoABB::TNodoABB (TNodoABB& nodo){ //const?
    this->item=nodo.item;
    this->de=nodo.de;
    this->iz=nodo.iz;
}
// Destructor
TNodoABB::~TNodoABB (){
    this->item.~TComplejo();
    this->de=TABBCom();
    this->iz=TABBCom();
}
// Sobrecarga del operador asignación
TNodoABB& TNodoABB::operator=(const TNodoABB& nodo){
    this->~TNodoABB();
    this->item=nodo.item;
    this->de=nodo.de;
    this->iz=nodo.iz;

    return *this;
    
}
