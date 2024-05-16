#include <iostream>
#include "../include/tabbcalendario.h"
#include <string.h>
#include <string>
#include <cstring>
using namespace std;

TNodoABB::TNodoABB(){
    item = TCalendario();
    de = TABBCalendario();
    iz = TABBCalendario();
}

TNodoABB::TNodoABB(const TNodoABB &n){
    item = n.item;
    de = n.de;
    iz = n.iz;
}

TNodoABB::~TNodoABB(){

}

TNodoABB & TNodoABB::operator=(const TNodoABB &n){
    if(this != &n){
        item = n.item;
        de = n.de;
        iz = n.iz;
    }
    return *this;
}

TABBCalendario::TABBCalendario(){
    raiz = nullptr;
}

TABBCalendario::TABBCalendario(const TABBCalendario &a){
    if(a.raiz != nullptr){
        raiz = new TNodoABB();
        *raiz = *(a.raiz);
    }else{
        raiz = nullptr;
    }
}

TABBCalendario::~TABBCalendario(){
    if(raiz != NULL){
        delete raiz;
        raiz = NULL;
    }
}

TABBCalendario & TABBCalendario::operator=(const TABBCalendario &a){
    if(this != &a){
        if(raiz != NULL){
            delete raiz;
            raiz = NULL;
        }
        if(a.raiz != NULL){
            raiz = new TNodoABB();
            *raiz = *(a.raiz);
        }
    }
    return *this;
}

bool TABBCalendario::operator==(const TABBCalendario &a) const{
    if(this->Inorden() == a.Inorden())
        return true;
    else return false;
}

bool TABBCalendario::EsVacio() const{
    if(raiz == NULL)
        return true;
    else return false;
}

bool TABBCalendario::Insertar(const TCalendario &c){
    if(raiz == NULL){
        raiz = new TNodoABB();
        raiz->item = c;
        return true;
    }else{
        if(raiz->item == c)
            return false;
        else if(raiz->item < c)
            return raiz->de.Insertar(c);
        else return raiz->iz.Insertar(c);
    }
}

bool TABBCalendario::Borrar(const TCalendario &c){
    if(raiz == NULL)
        return false;
    else{
        if(raiz->item == c){
            if(raiz->de.raiz == NULL && raiz->iz.raiz == NULL){
                delete raiz;
                raiz = NULL;
                return true;
            }else if(raiz->de.raiz == NULL){
                TNodoABB *aux = raiz;
                raiz = raiz->iz.raiz;
                aux->iz.raiz = NULL;
                delete aux;
                return true;
            }else if(raiz->iz.raiz == NULL){
                TNodoABB *aux = raiz;
                raiz = raiz->de.raiz;
                aux->de.raiz = NULL;
                delete aux;
                return true;
            }else{
                TCalendario cal = raiz->de.raiz->item;
                raiz->de.Borrar(cal);
                raiz->item = cal;
                return true;
            }
        }else if(raiz->item < c)
            return raiz->de.Borrar(c);
        else return raiz->iz.Borrar(c);
    }
}

bool TABBCalendario::Buscar(const TCalendario &c) const{
    if(raiz == NULL)
        return false;
    else{
        if(raiz->item == c)
            return true;
        else if(raiz->item < c)
            return raiz->de.Buscar(c);
        else return raiz->iz.Buscar(c);
    }
}

TCalendario TABBCalendario::Raiz() const{
    if(raiz != NULL)
        return raiz->item;
    else return TCalendario();
}

int TABBCalendario::Altura() const{
    if(raiz == NULL)
        return 0;
    else{
        int iz = raiz->iz.Altura();
        int de = raiz->de.Altura();
        if(iz > de)
            return iz + 1;
        else return de + 1;
    }
}

int TABBCalendario::Nodos() const{
    if(raiz == NULL)
        return 0;
    else return 1 + raiz->iz.Nodos() + raiz->de.Nodos();
}

int TABBCalendario::NodosHoja() const{
    if(raiz == NULL)
        return 0;
    else if(raiz->iz.raiz == NULL && raiz->de.raiz == NULL)
        return 1;
    else return raiz->iz.NodosHoja() + raiz->de.NodosHoja();
}

void TABBCalendario::InordenAux(TVectorCalendario &v, int &n) const{
    if(!this->EsVacio()){
        this->raiz->iz.InordenAux(v, n);
        v[n++] = this->Raiz();
        this->raiz->de.InordenAux(v, n);
    }
}

TVectorCalendario TABBCalendario::Inorden() const{
    int n = 1;
    TVectorCalendario v(Nodos());
    InordenAux(v, n);
    return v;
}

void TABBCalendario::PreordenAux(TVectorCalendario &v, int &n) const{
    if(!this->EsVacio()){
        v[n++] = this->Raiz();
        this->raiz->iz.PreordenAux(v, n);        
        this->raiz->de.PreordenAux(v, n);
    }
}

TVectorCalendario TABBCalendario::Preorden() const{
    int n = 1;
    TVectorCalendario v(Nodos());
    PreordenAux(v, n);
    return v;
}

void TABBCalendario::PostordenAux(TVectorCalendario &v, int &n) const{
    if(!this->EsVacio()){ 
        this->raiz->iz.PostordenAux(v, n);        
        this->raiz->de.PostordenAux(v, n);
        v[n++] = this->Raiz();
    }
}

TVectorCalendario TABBCalendario::Postorden() const{
    int n = 1;
    TVectorCalendario v(Nodos());
    PostordenAux(v, n);
    return v;
}

TVectorCalendario TABBCalendario::Niveles() const{
    TVectorCalendario v(Nodos());
    queue<TNodoABB*> cola;
    TNodoABB *nodo = raiz;
    int n = 0;
    if(nodo != NULL){
        cola.push(nodo);
        while(!cola.empty()){
            nodo = cola.front();
            cola.pop();
            v[n] = nodo->item;
            n++;
            if(nodo->iz.raiz != NULL)
                cola.push(nodo->iz.raiz);
            if(nodo->de.raiz != NULL)
                cola.push(nodo->de.raiz);
        }
    }
    return v;
}

TABBCalendario TABBCalendario::operator+(TABBCalendario &a){
    TABBCalendario aux(*this);
    TVectorCalendario v = a.Inorden();
    for(int i = 1; i <= v.Tamano(); i++)
        aux.Insertar(v[i]);
    return aux;
}

TABBCalendario TABBCalendario::operator-(TABBCalendario &a){
    TABBCalendario aux(*this);
    TVectorCalendario v = a.Inorden();
    for(int i = 1; i <= v.Tamano(); i++)
        aux.Borrar(v[i]);
    return aux;
}

ostream & operator<<(ostream &os, const TABBCalendario &a){
    os << a.Inorden();
    return os;
}