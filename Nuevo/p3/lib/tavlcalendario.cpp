#include <iostream>
#include "../include/tavlcalendario.h"
using namespace std;

TNodoAVL::TNodoAVL() : item(), de(), iz(), fe(){}

TNodoAVL::TNodoAVL(const TNodoAVL &nodo) : item(nodo.item), iz(nodo.iz), de(nodo.de), fe(nodo.fe){}

void TNodoAVL::Copia(const TNodoAVL &nodo){
    //Usando el operador= de la clase TAVLCalendario
    this->item = nodo.item;
    this->iz = nodo.iz;
    this->de = nodo.de;
    this->fe = nodo.fe;
}

TNodoAVL::~TNodoAVL(){}

TNodoAVL & TNodoAVL::operator=(const TNodoAVL &nodo){
    if(this != &nodo){      //Protección contra autoasignación
        this->~TNodoAVL();
        Copia(nodo);
    }
    return *this;
}

// Constructor por defecto
TAVLCalendario::TAVLCalendario(){
    this->raiz = nullptr;
}

void TAVLCalendario::Copia(const TAVLCalendario &avl){
    if(!avl.EsVacio()){
        this->raiz = new TNodoAVL();
        this->raiz->item = avl.raiz->item;
        this->raiz->iz.Copia(avl.raiz->iz);
        this->raiz->de.Copia(avl.raiz->de);
    }
    else this->raiz = NULL;
}

// Constructor de copia
TAVLCalendario::TAVLCalendario(const TAVLCalendario &avl) {
    raiz = nullptr;
    Copia(avl);
}

// Destructor
TAVLCalendario::~TAVLCalendario(){
    TNodoAVL *aux = new TNodoAVL();
    
    while(!EsVacio()){
        aux = this->raiz;   
        raiz->iz.~TAVLCalendario();
        raiz->de.~TAVLCalendario();

        delete this->raiz;
        this->raiz = NULL;
    }
}

// Sobrecarga del operador asignación
TAVLCalendario & TAVLCalendario::operator= (const TAVLCalendario &avl){
    if(this != &avl){
        this->~TAVLCalendario();
        this->Copia(avl);
    }

    return *this;
}
// Sobrecarga del operador igualdad
bool TAVLCalendario::operator==(const TAVLCalendario &avl) const{
    if(this->Inorden() == avl.Inorden())
        return true;
    else return false;
}

// Sobrecarga del operador desigualdad
bool TAVLCalendario::operator!=(const TAVLCalendario &avl) const{
    return !(*this == avl);
}
// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool TAVLCalendario::EsVacio() const{
    return (this->raiz == NULL);
}

bool TAVLCalendario::Insertar(const TCalendario &cal) {
    bool crece = false; // Variable para verificar si el árbol crece
    return InsertarAux(cal,raiz,crece);
}

// Función auxiliar para insertar un elemento en el árbol AVL
bool TAVLCalendario::InsertarAux(const TCalendario &cal, TNodoAVL *&nodo, bool &crece) {
    bool insertado = false;

    if (nodo == nullptr) {
        nodo = new TNodoAVL();
        nodo->item = cal;
        crece = true;
        insertado = true;
    } else if (cal < nodo->item) {
        insertado = InsertarAux(cal, nodo->iz.raiz, crece);
        if (crece) {
            nodo->fe--;
            if (nodo->fe == -2) {
                if (nodo->iz.raiz->fe == 1) {
                    // Rotación doble derecha-izquierda
                    RotarIzquierda(nodo->iz.raiz);
                }
                // Rotación simple derecha
                RotarDerecha(nodo);
                crece = false;
            } else if (nodo->fe == 0) {
                crece = false;
            }
        }
    } else if (cal > nodo->item) {
        insertado = InsertarAux(cal, nodo->de.raiz, crece);
        if (crece) {
            nodo->fe++;
            if (nodo->fe == 2) {
                if (nodo->de.raiz->fe == -1) {
                    // Rotación doble izquierda-derecha
                    RotarDerecha(nodo->de.raiz);
                }
                // Rotación simple izquierda
                RotarIzquierda(nodo);
                crece = false;
            } else if (nodo->fe == 0) {
                crece = false;
            }
        }
    }
    return insertado;
}

// Rotación simple a la izquierda
void TAVLCalendario::RotarIzquierda(TNodoAVL *&nodo) {
    TNodoAVL *nuevo = raiz->de.raiz;
    raiz->de.raiz = nuevo->iz.raiz;
    nuevo->iz.raiz = raiz;
    raiz = nuevo;

    // Actualizar factores de equilibrio
    raiz->iz.raiz->fe = raiz->iz.raiz->fe - 1 - max(0, raiz->fe);
    raiz->fe = raiz->fe - 1 + min(0, raiz->iz.raiz->fe);
}

// Rotación simple a la derecha
void TAVLCalendario::RotarDerecha(TNodoAVL *&nodo) {
    TNodoAVL *nuevo = raiz->iz.raiz;
    raiz->iz.raiz = nuevo->de.raiz;
    nuevo->de.raiz = raiz;
    raiz = nuevo;

    // Actualizar factores de equilibrio
    raiz->de.raiz->fe = raiz->de.raiz->fe + 1 - min(0, raiz->fe);
    raiz->fe = raiz->fe + 1 + max(0, raiz->de.raiz->fe);
}

bool TAVLCalendario::Borrar(const TCalendario &cal) {
    bool borrado = false;
    bool decrece = false;
    return BorrarEnAVL(cal, raiz, borrado, decrece);
}

bool TAVLCalendario::BorrarEnAVL(const TCalendario &cal, TNodoAVL *&nodo, bool &borrado, bool &decrece) {
    if (nodo == nullptr) {
        return false;
    }

    if (cal < nodo->item) {
        borrado = BorrarEnAVL(cal, nodo->iz.raiz, borrado, decrece);
        if (decrece) {
            nodo->fe++;
            if (nodo->fe == 2) {
                Equilibrar(nodo);
            } else if (nodo->fe == 1) {
                decrece = false;
            }
        }
    } else if (cal > nodo->item) {
        borrado = BorrarEnAVL(cal, nodo->de.raiz, borrado, decrece);
        if (decrece) {
            nodo->fe--;
            if (nodo->fe == -2) {
                Equilibrar(nodo);
            } else if (nodo->fe == -1) {
                decrece = false;
            }
        }
    } else {
        borrado = true;
        if (nodo->iz.raiz == nullptr || nodo->de.raiz == nullptr) {
            TNodoAVL *aux = nodo->iz.raiz ? nodo->iz.raiz : nodo->de.raiz;
            delete nodo;
            nodo = aux;
            decrece = true;
        } else {
            TCalendario mayorIz = Mayor(nodo->iz.raiz);
            nodo->item = mayorIz;
            borrado = BorrarEnAVL(mayorIz, nodo->iz.raiz, borrado, decrece);
            if (decrece) {
                nodo->fe++;
                if (nodo->fe == 2) {
                    Equilibrar(nodo);
                } else if (nodo->fe == 1) {
                    decrece = false;
                }
            }
        }
    }

    return borrado;
}

void TAVLCalendario::Equilibrar(TNodoAVL *&nodo) {
    if (nodo->fe == -2) {
        if (nodo->iz.raiz->fe <= 0) {
            RotarDerecha(nodo);
        } else {
            RotarIzquierda(nodo->iz.raiz);
            RotarDerecha(nodo);
        }
    } else if (nodo->fe == 2) {
        if (nodo->de.raiz->fe >= 0) {
            RotarIzquierda(nodo);
        } else {
            RotarIzquierda(nodo->iz.raiz);
            RotarDerecha(nodo);
        }
    }
}

TCalendario TAVLCalendario::Mayor(TNodoAVL *nodo) const {
    while (nodo->de.raiz != nullptr) {
        nodo = nodo->de.raiz;
    }
    return nodo->item;
}

bool TAVLCalendario::Buscar(const TCalendario &cal) const{
    if(!this->EsVacio()){
        if(this->raiz->item == cal)
            return true;
        else{
            if(this->raiz->de.Buscar(cal) || this->raiz->iz.Buscar(cal))
                return true;
            else return false; 
        }
    }
    return false;
}

int TAVLCalendario::Altura() const{
    return EsVacio() ? 0 : 1 + max(this->raiz->iz.Altura(), this->raiz->de.Altura());
}

int TAVLCalendario::Nodos() const{
    return EsVacio() ? 0 : 1 + this->raiz->iz.Nodos() + this->raiz->de.Nodos();
}

TCalendario TAVLCalendario::Raiz() const{
    return EsVacio() ? TCalendario() : this->raiz->item;
}

int TAVLCalendario::NodosHoja() const{
    if (!this->EsVacio()){
        if(!this->raiz->iz.EsVacio() || !this->raiz->iz.EsVacio())
            return this->raiz->iz.NodosHoja() + this->raiz->de.NodosHoja();
        else
            return 1;
    }   
    else return 0;
}

void TAVLCalendario::InordenAux(TVectorCalendario &v, int &pos) const{
    if(!this->EsVacio()){
        this->raiz->iz.InordenAux(v, pos);
        v[pos++] = this->Raiz();
        this->raiz->de.InordenAux(v, pos);
    }
}
               
TVectorCalendario TAVLCalendario::Inorden() const{
    int pos = 1;
    TVectorCalendario v (this->Nodos());
    this->InordenAux(v, pos);
    return v;
}

void TAVLCalendario::PreordenAux(TVectorCalendario &v, int &pos) const{
    if(!this->EsVacio()){
        v[pos++] = this->Raiz();
        this->raiz->iz.PreordenAux(v, pos);        
        this->raiz->de.PreordenAux(v, pos);
    }
}

TVectorCalendario TAVLCalendario::Preorden() const{
    int pos = 1;
    TVectorCalendario v (this->Nodos());
    this->PreordenAux(v, pos);
    return v;
}

void TAVLCalendario::PostordenAux(TVectorCalendario &v, int &pos) const{
    if(!this->EsVacio()){ 
        this->raiz->iz.PostordenAux(v, pos);        
        this->raiz->de.PostordenAux(v, pos);
        v[pos++] = this->Raiz();
    }
}

TVectorCalendario TAVLCalendario::Postorden() const{
    int pos = 1;
    TVectorCalendario v (this->Nodos());
    this->PostordenAux(v, pos);
    return v;
}

ostream& operator<<(ostream &s, const TAVLCalendario &obj){
    s << obj.Inorden();
    return s;
}