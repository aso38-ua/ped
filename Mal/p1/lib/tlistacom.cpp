#include <iostream>
#include <math.h>
#include "tlistacom.h"

using namespace std;

    // Constructor por defecto
    TListaNodo::TListaNodo (){
        this->e=0;
        this->anterior=nullptr;
        this->siguiente=nullptr;
    }

    // Constructor de copia
    TListaNodo::TListaNodo (const TListaNodo &a){
        this->e=a.e;
        this->anterior=a.anterior;
        this->siguiente=a.siguiente;
    }

    // Destructor
    TListaNodo::~TListaNodo(){
        this->e=0;
        this->anterior=nullptr;
        this->siguiente=nullptr;
    }
    // Sobrecarga del operador asignación
    TListaNodo& TListaNodo::operator=(const TListaNodo &a){
        this->~TListaNodo();
        this->e=a.e;
        this->anterior=a.anterior;
        this->siguiente=a.siguiente;

        return *this;
    }


    TListaPos::TListaPos(){
        this->pos=nullptr;
    }
    // Constructor de copia
    TListaPos::TListaPos (TListaPos &a){
        this->pos=a.pos;
    }
    // Destructor
    TListaPos::~TListaPos (){
        this->pos=nullptr;
    }
    // Sobrecarga del operador asignación
    TListaPos& TListaPos::operator=(const TListaPos &a){
        
    if(!(this == &a))
    {
        (*this).~TListaPos();
        pos=a.pos;

    }
    
    return *this;
    }
    

    // Sobrecarga del operador igualdad
    bool TListaPos::operator==(const TListaPos &a){
        bool devolver;
        if (this->pos==a.pos)
        {
            devolver=true;
        }
        else{
            devolver=false;
        }

        return devolver;
        
    }

    // Sobrecarga del operador desigualdad
    bool TListaPos::operator!=(const TListaPos &a){
        bool devolver;
        if (this->pos!=a.pos)
        {
            devolver=true;
        }
        else{
            devolver=false;
        }

        return devolver;
    }

    // Devuelve la posición anterior
    TListaPos TListaPos::Anterior()const{
        TListaPos lista;

        if (this->pos->anterior==nullptr)
        {
            lista.pos=nullptr;
        }
        else{
            lista.pos=pos->anterior;
        }
        
        return lista;

    }
    // Devuelve la posición siguiente
    TListaPos TListaPos::Siguiente() const{
        TListaPos lista;

        if (this->pos->siguiente==nullptr)
        {
            lista.pos=nullptr;
        }
        else{
            lista.pos=pos->siguiente;
        }
        
        return lista;
    }
    // Devuelve TRUE si la posición no apunta a una lista, FALSE en caso contrario
    bool TListaPos::EsVacia()const{
        if (this->pos==nullptr)
        {
            return true;
        }
        else{
            return false;
        }
        
    }

    // Constructor por defecto
    TListaCom::TListaCom (){
        this->primero=nullptr;
        this->ultimo=nullptr;
    }
    // Constructor de copia
    TListaCom::TListaCom (const TListaCom &a){
        this->primero=a.primero;
        this->ultimo=a.ultimo;

        TListaPos pos = a.Ultima();
        while (!pos.EsVacia()) {
            InsCabeza(pos.pos->e);
            pos=pos.Anterior();
        }

    }

    // Destructor
    TListaCom::~TListaCom (){
        this->primero=nullptr;
        this->ultimo=nullptr;
    }

    // Sobrecarga del operador asignación
    TListaCom& TListaCom::operator=(const TListaCom &a){
    if (this != &a) 
    {
        this->~TListaCom();

        for (TListaPos pos = a.Ultima(); !pos.EsVacia(); pos = pos.Anterior()) 
        {
            InsCabeza(pos.pos->e);
        }
    }

    return *this;
    }
    

    // Sobrecarga del operador igualdad
    bool TListaCom::operator==(const TListaCom &a)const{
    TListaNodo *nodo_actual = this->primero;
    TListaNodo *nodo_otro = a.primero;

    while (nodo_actual != NULL && nodo_otro != NULL) {
        if (nodo_actual->e != nodo_otro->e) {
            return false;
        }

        nodo_actual = nodo_actual->siguiente;
        nodo_otro = nodo_otro->siguiente;
    }

    if (nodo_actual != NULL || nodo_otro != NULL) {
        return false;
    }

    return true;
    }

    // Sobrecarga del operador desigualdad
    bool TListaCom::operator!=(const TListaCom &a)const{
        if (*this==a)
        {
            return false;
        }
        else{
            return true;
        }
        
        
    }

    // Sobrecarga del operador suma
    TListaCom TListaCom::operator+(const TListaCom &a)const{
        TListaCom *resultado=new TListaCom();

        for (TListaPos ac = a.Primera(); !ac.EsVacia(); ac = ac.Siguiente()) {
            resultado->InsCabeza(ac.pos->e);
        }

        return *resultado;
    }

    // Sobrecarga del operador resta
    TListaCom TListaCom::operator-(const TListaCom &a)const{
        TListaCom resultado;

        for (TListaPos ac = Primera(); !ac.EsVacia(); ac = ac.Siguiente()) {
            if (!a.Buscar(ac.pos->e)) 
            {
                resultado.InsCabeza(ac.pos->e);
            }
        }

        return resultado;
    }

    // Devuelve true si la lista está vacía, false en caso contrario
    bool TListaCom::EsVacia() const{
        return (primero == NULL);
    }

    // Inserta el elemento en la cabeza de la lista
    bool TListaCom::InsCabeza(const TComplejo &a){

        TListaNodo *nuevo = new TListaNodo();
        nuevo->e = a;
        
        if (EsVacia()) {
            primero = nuevo;
            ultimo = nuevo;
        } else {
            nuevo->siguiente = primero;
            primero->anterior = nuevo;
            primero = nuevo;
        }
        
        return true;

    }

    // Inserta el elemento a la izquierda de la posición indicada
    bool TListaCom::InsertarI(const TComplejo &a,const TListaPos &b){

        if (b.EsVacia()) {
        return false;
        }
    
        TListaNodo *nodo = primero;
        while (nodo != NULL) {
            if (nodo == b.pos) {
                
                TListaNodo *nuevo = new TListaNodo();
                nuevo->e = a;

                nuevo->siguiente = nodo;
                nuevo->anterior = nodo->anterior;
                if (nodo->anterior != NULL) {
                    nodo->anterior->siguiente = nuevo;
                }
                else {
                    primero = nuevo;
                }
                nodo->anterior = nuevo;
                
                return true;
            }
            nodo = nodo->siguiente;
        }
        
        return false;
    }

    // Inserta el elemento a la derecha de la posición indicada
    bool TListaCom::InsertarD(const TComplejo &a,const TListaPos &b){
        TListaNodo *nodo = primero;

    while (nodo != NULL && nodo != b.pos) {
        nodo = nodo->siguiente;
    }

    if (nodo != NULL) {
        TListaNodo *nuevo = new TListaNodo();
        nuevo->e = a;

        nuevo->siguiente = nodo->siguiente;
        nuevo->anterior = nodo;
        if (nodo->siguiente != NULL) {
            nodo->siguiente->anterior = nuevo;
        }
        nodo->siguiente = nuevo;
        if (ultimo == nodo) {
            ultimo = nuevo;
        }
        return true;
    }

    return false;
    }

    // Busca y borra la primera ocurrencia del elemento
    bool TListaCom::Borrar(const TComplejo &a){
        TListaNodo *nodo = primero;
        TListaNodo *nodoAnterior = NULL;

    while (nodo != NULL) {
        if (nodo->e == a) {
            // Si el nodo es el primero de la lista, ajustar el puntero al primer nodo
            if (nodoAnterior == NULL) {
                primero = nodo->siguiente;
            }
            // Si no es el primer nodo, ajustar el enlace del nodo anterior al siguiente
            else {
                nodoAnterior->siguiente = nodo->siguiente;
            }
            // Si el nodo es el último de la lista, ajustar el puntero al último nodo
            if (nodo == ultimo) {
                ultimo = nodoAnterior;
            }
            delete nodo;
            return true;
        }
        nodoAnterior = nodo;
        nodo = nodo->siguiente;
    }

    return false;
    }

    // Busca y borra todas las ocurrencias del elemento
    bool TListaCom::BorrarTodos(const TComplejo &a){
        bool encontrado = false;
        TListaNodo *nodo = primero;
        TListaNodo *anterior = NULL;

        while (nodo != NULL) {
            if (nodo->e == a) {
                encontrado = true;

                if (anterior == NULL) { // nodo a borrar es el primero de la lista
                    primero = nodo->siguiente;
                } else {
                    anterior->siguiente = nodo->siguiente;
                }

                if (nodo->siguiente == NULL) { // nodo a borrar es el último de la lista
                    ultimo = anterior;
                }

                TListaNodo *aux = nodo;
                nodo = nodo->siguiente;
                delete aux;
            } else {
                anterior = nodo;
                nodo = nodo->siguiente;
            }
        }

        return encontrado;
    }

    // Borra el elemento que ocupa la posición indicada
    bool TListaCom::Borrar(TListaPos &pos){

        if (pos.EsVacia()) {
            return false;
        }

        TListaNodo *nodo = pos.pos;
        TListaNodo *anterior = nodo->anterior;
        TListaNodo *siguiente = nodo->siguiente;

        if (anterior == NULL) {
            primero = siguiente;
        } else {
            anterior->siguiente = siguiente;
        }

        if (siguiente == NULL) {
            ultimo = anterior;
        } else {
            siguiente->anterior = anterior;
        }

        delete nodo;
        pos.pos = NULL;

        return true;

    }
    // Obtiene el elemento que ocupa la posición indicada
    TComplejo TListaCom::Obtener(const TListaPos &pos)const{
        if (pos.EsVacia()) {
        return TComplejo();
    }

        TListaNodo *nodo = pos.pos;
        return nodo->e;
    }

    // Devuelve true si el elemento está en la lista, false en caso contrario
    bool TListaCom::Buscar(const TComplejo &a)const{
        TListaNodo *nodo = primero;

    while (nodo != NULL) {
        if (nodo->e == a) {
            return true;
        }
        nodo = nodo->siguiente;
    }

    return false;

        

    }
    // Devuelve la longitud de la lista
    int TListaCom::Longitud()const{
        int longitud = 0;
        TListaNodo *nodo = primero;

        while (nodo != NULL) {
            longitud++;
            nodo = nodo->siguiente;
        }

        return longitud;
    }
    // Devuelve la primera posición en la lista
    TListaPos TListaCom::Primera() const{
        TListaPos posi;
        posi.pos=this->primero;
        return posi;
    }
    // Devuelve la última posición en la lista
    TListaPos TListaCom::Ultima() const{
        TListaPos posi;
        posi.pos=this->ultimo;
        return posi;
    }

    // Sobrecarga del operador salida
    ostream & operator<<(ostream &, TListaCom &){
        
    }