#include <iostream>
using namespace std;

#include "tlistacalendario.h"

// Constructor por defecto
TNodoCalendario::TNodoCalendario() {
    this->c=TCalendario();
    siguiente = nullptr;
}

// Constructor de copia
TNodoCalendario::TNodoCalendario(const TNodoCalendario &nodo) {
    if (!nodo.c.EsVacio()) { // Verificar si el nodo fuente no está vacío
        this->c = nodo.c;
    } else {
        // Si el nodo fuente está vacío, se crea un nuevo TCalendario vacío
        this->c = TCalendario();
    }
    this->siguiente = nodo.siguiente;
}


// Destructor
TNodoCalendario::~TNodoCalendario() {
    this->c.~TCalendario();
    siguiente = nullptr; // Eliminamos la referencia al siguiente nodo
}

// Sobrecarga del operador asignación
TNodoCalendario &TNodoCalendario::operator=(const TNodoCalendario &nodo) {
    if (this != &nodo) {
        if (!nodo.c.EsVacio()) { // Verificar si el nodo fuente no está vacío
            this->c = nodo.c;
        } else {
            // Si el nodo fuente está vacío, se asigna un TCalendario vacío
            this->c = TCalendario();
        }
        this->siguiente = nodo.siguiente;
    }
    return *this;
}

// Constructor por defecto
TListaPos::TListaPos(){
    this->pos = nullptr;
}

// Constructor de copia
TListaPos::TListaPos(const TListaPos &obj) {
    if (obj.pos == nullptr) {
        this->pos = nullptr;
    } else {
        TNodoCalendario *nodoOriginal = obj.pos;
        TNodoCalendario *nodoNuevo = new TNodoCalendario(*nodoOriginal); // Copia el nodo
        this->pos = nodoNuevo;
        
        // Copiar el resto de la lista
        TNodoCalendario *nodoActual = this->pos;
        nodoOriginal = nodoOriginal->siguiente;
        while (nodoOriginal != nullptr) {
            nodoNuevo = new TNodoCalendario(*nodoOriginal); // Copia el nodo
            nodoActual->siguiente = nodoNuevo;
            nodoActual = nodoActual->siguiente;
            nodoOriginal = nodoOriginal->siguiente;
        }
    }
}

//Destructor
TListaPos::~TListaPos(){
    this->pos = nullptr;
}

// Sobrecarga del operador asignación 
TListaPos &  TListaPos::operator=(const TListaPos &obj){
    if(this != &obj){
        this->pos = obj.pos;
    }
    return *this;
}

// Sobrecarga del operador igualdad
bool TListaPos::operator==(const TListaPos &obj) const{
    if(this->pos == obj.pos)
        return true;
    return false;
}

// Sobrecarga del operador desigualdad 
bool TListaPos::operator!=(const TListaPos &obj) const{ 
    return !(*this == obj);
}

// Devuelve la posición siguiente
TListaPos TListaPos::Siguiente() const{
    TListaPos lp;
    if(this->pos->siguiente != nullptr) // Si la posición actual no es la última, asigna el siguiente nodo
        lp.pos = this->pos->siguiente;
    return lp;
}

// Posición vacía
bool TListaPos::EsVacia() const {
    return (this->pos == nullptr);
}

// Constructor por defecto
TListaCalendario::TListaCalendario(){
    this->primero = nullptr;
}

// Constructor de copia
TListaCalendario::TListaCalendario(const TListaCalendario &lista){
   this->primero = nullptr;
    for(TListaPos i = lista.Primera(); !i.EsVacia(); i = i.Siguiente()){ 
            this->Insertar(i.pos->c);
    }
}

//Destructor
TListaCalendario::~TListaCalendario(){
    TNodoCalendario *aux;

    while (this->primero != nullptr){
        aux = this->primero->siguiente;
        delete this->primero;
        this->primero = aux;
    }
}

// Sobrecarga del operador asignación
TListaCalendario & TListaCalendario::operator=(const TListaCalendario &obj) {
    if (this != &obj) {
        // Limpia la lista actual antes de la asignación
        this->Vaciar();

        // Copia los elementos de la lista obj
        for (TListaPos i = obj.Primera(); !i.EsVacia(); i = i.Siguiente()) { 
            this->Insertar(i.pos->c);
        }   
    }
    return *this;
}

// Función para vaciar la lista
void TListaCalendario::Vaciar() {
    TNodoCalendario *aux;

    while (this->primero != nullptr) {
        aux = this->primero->siguiente;
        delete this->primero;
        this->primero = aux;
    }
}

// Sobrecarga del operador igualdad 
bool TListaCalendario::operator==(const TListaCalendario &obj) const {
    TListaPos actual = this->Primera();
    TListaPos otra = obj.Primera();

    // Itera sobre ambas listas y compara sus elementos
    while (!actual.EsVacia() && !otra.EsVacia()) {
        if (actual.pos->c != otra.pos->c) {
            return false;
        }
        actual = actual.Siguiente();
        otra = otra.Siguiente();
    }

    // Verifica si ambas listas llegaron al final simultáneamente
    return actual.EsVacia() && otra.EsVacia();
}

// Sobrecarga del operador suma
TListaCalendario TListaCalendario::operator+ (TListaCalendario &obj) {
    TListaCalendario resultado(*this); // Crear una copia de la lista actual

    // Insertar los elementos de la lista obj en la lista resultado
    for(TListaPos i = obj.Primera(); !i.EsVacia(); i = i.Siguiente())
        resultado.Insertar(i.pos->c);

    return resultado;
}

// Sobrecarga del operador resta
TListaCalendario TListaCalendario::operator- (TListaCalendario &obj) {
    TListaCalendario resultado(*this); // Crear una copia de la lista actual

    // Borrar los elementos de la lista obj de la lista resultado
    for(TListaPos i = obj.Primera(); !i.EsVacia(); i = i.Siguiente())
        resultado.Borrar(i.pos->c);

    return resultado;
}

// Inserta el elemento en la posición que le corresponda dentro de la lista
bool TListaCalendario::Insertar(const TCalendario &cal) {
    // Verificar si el calendario ya existe en la lista
    if (Buscar(cal)) {
        return false; // Devolver false indicando que no se insertó el duplicado
    }

    TNodoCalendario *nuevoNodo = new TNodoCalendario();
    nuevoNodo->c = cal;

    // Insertar el nuevo nodo al principio de la lista si está vacía
    if (this->EsVacia()) {
        this->primero = nuevoNodo;
        return true;
    }

    // Insertar el nuevo nodo al principio de la lista si es menor que el primer calendario
    if (cal < this->primero->c) {
        nuevoNodo->siguiente = this->primero;
        this->primero = nuevoNodo;
        return true;
    }

    TNodoCalendario *explorado = this->primero;
    while (explorado->siguiente != nullptr && explorado->siguiente->c < cal) {
        explorado = explorado->siguiente;
    }

    // Insertar el nuevo nodo en la posición correcta
    nuevoNodo->siguiente = explorado->siguiente;
    explorado->siguiente = nuevoNodo;
    return true;
}


// Busca y borra el elemento
bool TListaCalendario::Borrar(const TCalendario &obj) {
    if (this->EsVacia()) return false;

    if (this->primero->c == obj) {
        TNodoCalendario *aEliminar = this->primero;
        this->primero = this->primero->siguiente;
        delete aEliminar;
        return true;
    }

    TNodoCalendario *explorado = this->primero;
    while (explorado->siguiente != nullptr && explorado->siguiente->c != obj) {
        explorado = explorado->siguiente;
    }

    if (explorado->siguiente != nullptr) {
        TNodoCalendario *aEliminar = explorado->siguiente;
        explorado->siguiente = explorado->siguiente->siguiente;
        delete aEliminar;
        return true;
    }

    return false;
}

// Borra el elemento que ocupa la posición indicada
bool TListaCalendario::Borrar(const TListaPos &obj) {
    if (!obj.EsVacia()) {
        TCalendario c = obj.pos->c;
        return Borrar(c);
    }
    return false;
}

//Borra todos los Calendarios que ocupa la posición indicada
bool TListaCalendario::Borrar(int dia, int mes, int anyo) {
    TNodoCalendario *aux = this->primero;
    TNodoCalendario *anterior = nullptr;
    bool borrado = false;

    // Calendario límite para comparar
    TCalendario limite(dia, mes, anyo, nullptr);

    while (aux != nullptr) {
        if (aux->c == limite) {
            // Borrar nodo actual
            if (anterior != nullptr) {
                anterior->siguiente = aux->siguiente;
                delete aux;
                aux = anterior->siguiente;
            } else {
                this->primero = aux->siguiente;
                delete aux;
                aux = this->primero;
            }
            borrado = true;
        } else {
            // Avanzar al siguiente nodo
            anterior = aux;
            aux = aux->siguiente;
        }
    }

    return borrado;
}



// Devuelve true si la lista está vacía, false en caso contrario
bool TListaCalendario::EsVacia() const {
    return (this->primero == nullptr);
}

// Obtiene el elemento que ocupa la posición indicada

TCalendario TListaCalendario::Obtener(const TListaPos &obj) const {
    TListaPos i = this->Primera();
    while (!i.EsVacia()) {
        if (i == obj) {
            return i.pos->c;
        }
        i = i.Siguiente();
    }
    return TCalendario(); // Si no se encuentra, se devuelve un calendario vacío
}

// Devuelve true si el Calendario está en la lista.
bool TListaCalendario::Buscar(const TCalendario &obj) const {
    TListaPos i = this->Primera();
    while (!i.EsVacia()) {
        if (i.pos->c == obj) {
            return true;
        }
        i = i.Siguiente();
    }
    return false;
}

// Devuelve la longitud de la lista
int TListaCalendario::Longitud() const {
    int longitud = 0;
    for(TListaPos i = this->Primera(); !i.EsVacia(); i = i.Siguiente() )
        longitud++;
    return longitud;
}

// Devuelve la primera posición en la lista
TListaPos TListaCalendario::Primera() const {
    TListaPos tpos;
    if(this->EsVacia())
        return tpos;
    else{
        tpos.pos = this->primero;
        return tpos; 
    }
}

// Devuelve la última posición en la lista
TListaPos TListaCalendario::Ultima() const {
    TListaPos ultima = this->Primera();
    while (!ultima.EsVacia() && !ultima.Siguiente().EsVacia()) {
        ultima = ultima.Siguiente();
    }
    return ultima;
}

// Suma de dos sublistas en una nueva lista
TListaCalendario TListaCalendario::SumarSubl(int I_L1, int F_L1, TListaCalendario &L2, int I_L2, int F_L2) {
    // Sublista de la lista invocante
    TListaCalendario Sublista1 = this->ExtraerRango(I_L1, F_L1);
    // Sublista de la lista pasada como parámetro
    TListaCalendario Sublista2 = L2.ExtraerRango(I_L2, F_L2);

    // Unión de ambas sublistas
    TListaCalendario resultado;
    resultado = Sublista1 + Sublista2;

    return resultado;
}

// Extraer un rango de nodos de la lista
TListaCalendario TListaCalendario::ExtraerRango(int n1, int n2) {
    TListaCalendario listaExtraida;

    if (n1 <= 0) n1 = 1; // Si n1 es menor o igual a 0
    if (n2 > this->Longitud()) n2 = this->Longitud(); // Si n2 excede la longitud de la lista
    if (n1 > n2) return listaExtraida; // Si n1 es mayor que n2, la sublista resultante es vacía

    int contador = 1;
    TListaPos pos = this->Primera();
    while (!pos.EsVacia() && contador <= n2) {
        if (contador >= n1 && contador <= n2) {
            // Insertar en la lista extraída
            listaExtraida.Insertar(pos.pos->c);
        }
        pos = pos.Siguiente(); // Avanzar al siguiente nodo
        contador++; // Incrementar el contador de posición
    }

    return listaExtraida;
}

ostream& operator<<(ostream &s, const TListaCalendario& obj){
    s << "<";
    for(TListaPos i = obj.Primera(); !i.EsVacia(); i = i.Siguiente() ){
        s << obj.Obtener(i);
        if(i !=  obj.Ultima())
            s << " "; 
    }
       
    s<< ">";

    return s;
}