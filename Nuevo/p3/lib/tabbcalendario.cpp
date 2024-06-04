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

TVectorCalendario TABBCalendario::ABBCamino(TListaCalendario &l){
    TVectorCalendario v;

    if(!l.EsVacia() && !this->EsVacio()){

        for(TListaPos i = l.Primera(); !i.EsVacia(); i = i.Siguiente()){ 
            //Si encontramos el elemento que toca en la lista no hacemos nada, si no existe ...
            if(!this->Buscar(l.Obtener(i))){

                //Lo insertamos en el árbol
                this->Insertar(l.Obtener(i)); 

                //Nos guardamos el elemento insertado en el ABB 
                TCalendario buscado =  l.Obtener(i);         

                //Pasamos el elemento a buscar, así como el vector
                //El vector se ampliará ya que está pasado por referencia
                this->ElegirSubarbol(buscado, v);
            }
        }

        return v;
    }
    else{
        return v;
    }
}

void TABBCalendario::ElegirSubarbol(TCalendario &buscado, TVectorCalendario &v){
        
        //Si el elemento que buscamos es menor que la raiz...
        if(!this->EsVacio() && buscado < this->raiz->item){
            //Añadimos un hueco en el vector, y en él añadimos la raiz, que formará parte del camino
            v.Redimensionar(v.Tamano() + 1);
            v[v.Tamano()] = this->raiz->item;

            //Escogemos el subarbol izquierda ya que así encontraremos el elemento en el ABB
            this->raiz->iz.ElegirSubarbol(buscado, v);
        }

        else if(!this->EsVacio()){
            v.Redimensionar(v.Tamano() + 1);
            v[v.Tamano()] = this->raiz->item;

            this->raiz->de.ElegirSubarbol(buscado, v);
        }  
}

TCalendario TABBCalendario::Maximo() const {
    if (EsVacio()) {
        return TCalendario(); // Devuelve un calendario vacío si el árbol está vacío
    } else if (raiz->de.EsVacio()) {
        return raiz->item; // Si no hay subárbol derecho, la raíz es el máximo
    } else {
        return raiz->de.Maximo(); // Continúa buscando en el subárbol derecho
    }
}

TCalendario TABBCalendario::Minimo() const {
    if (EsVacio()) {
        return TCalendario(); // Devuelve un calendario vacío si el árbol está vacío
    } else if (raiz->iz.EsVacio()) {
        return raiz->item; // Si no hay subárbol izquierdo, la raíz es el mínimo
    } else {
        return raiz->iz.Minimo(); // Continúa buscando en el subárbol izquierdo
    }
}

int TABBCalendario::ContarNodos() const {
    if (EsVacio()) {
        return 0; // Si el árbol está vacío, el conteo es 0
    } else {
        return 1 + raiz->iz.ContarNodos() + raiz->de.ContarNodos();
    }
}

bool TABBCalendario::Iguales(const TABBCalendario &abb) const {
    if (EsVacio() && abb.EsVacio()) {
        return true; // Ambos árboles están vacíos
    } else if (!EsVacio() && !abb.EsVacio()) {
        return raiz->item == abb.raiz->item &&
               raiz->iz.Iguales(abb.raiz->iz) &&
               raiz->de.Iguales(abb.raiz->de);
    } else {
        return false; // Uno está vacío y el otro no
    }
}

TCalendario TABBCalendario::AncestroComun(const TCalendario &cal1, const TCalendario &cal2) const {
    if (EsVacio()) {
        return TCalendario(); // Devuelve un calendario vacío si el árbol está vacío
    }

    if (raiz->item > cal1 && raiz->item > cal2) {
        return raiz->iz.AncestroComun(cal1, cal2); // Busca en el subárbol izquierdo
    }

    if (raiz->item < cal1 && raiz->item < cal2) {
        return raiz->de.AncestroComun(cal1, cal2); // Busca en el subárbol derecho
    }

    return raiz->item; // Si uno de los valores es igual a la raíz o están en diferentes subárboles, la raíz es el ancestro común
}

int TABBCalendario::NivelNodo(const TCalendario &cal) const {
    if (EsVacio()) {
        return -1; // Devuelve -1 si el nodo no se encuentra
    }

    if (raiz->item == cal) {
        return 0; // El nivel de la raíz es 0
    }

    if (raiz->item > cal) {
        int nivel = raiz->iz.NivelNodo(cal);
        return (nivel == -1) ? -1 : 1 + nivel; // Añade 1 al nivel del subárbol izquierdo
    } else {
        int nivel = raiz->de.NivelNodo(cal);
        return (nivel == -1) ? -1 : 1 + nivel; // Añade 1 al nivel del subárbol derecho
    }
}

bool TABBCalendario::EsSubconjunto(const TABBCalendario &abb) const {
    if (abb.EsVacio()) {
        return true; // Un árbol vacío es subconjunto de cualquier árbol
    }

    if (EsVacio()) {
        return false; // Un árbol no vacío no puede ser subconjunto de un árbol vacío
    }

    if (!Buscar(abb.raiz->item)) {
        return false; // Si la raíz del segundo árbol no está en el primero, no es subconjunto
    }

    return raiz->iz.EsSubconjunto(abb.raiz->iz) && raiz->de.EsSubconjunto(abb.raiz->de);
}




ostream & operator<<(ostream &os, const TABBCalendario &a){
    os << a.Inorden();
    return os;
}