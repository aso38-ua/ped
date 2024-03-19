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

TListaCalendario & TListaCalendario::operator=(const TListaCalendario &obj){
    if(this != &obj){
        this->~TListaCalendario();
        for(TListaPos i = obj.Primera(); !i.EsVacia(); i = i.Siguiente()){ 
            this->Insertar(i.pos->c);
        }   
    }
    return (*this);
}

bool TListaCalendario::operator==(TListaCalendario &obj){
    TListaPos actual = this->Primera();
    TListaPos otra = obj.Primera();

    if(this->Longitud() == obj.Longitud()){
        do{
            if(!actual.EsVacia() && !otra.EsVacia()){
                if(actual.pos->c != otra.pos->c)
                    return false;
                actual = actual.Siguiente();
                otra = otra.Siguiente();
            }
        }while(!actual.EsVacia());

        return true;
    }
    return false;
}

TListaCalendario TListaCalendario::operator+ (TListaCalendario &obj){
    TListaCalendario *resultado = new TListaCalendario(*this);
    for(TListaPos i = obj.Primera(); !i.EsVacia(); i = i.Siguiente())
        resultado->Insertar(i.pos->c);
    return (*resultado);
}

TListaCalendario TListaCalendario::operator- (TListaCalendario &obj){
    TListaCalendario *resultado = new TListaCalendario(*this);
    for(TListaPos i = obj.Primera(); !i.EsVacia(); i = i.Siguiente())
        resultado->Borrar(i.pos->c);
    return (*resultado);
}

bool TListaCalendario::Insertar(const TCalendario &obj){
    TNodoCalendario * nuevoNodo = new TNodoCalendario();
    nuevoNodo->c = obj;

    if(this->EsVacia()){  
        nuevoNodo->siguiente = NULL;    //No hay siguiente nodo
        this->primero = nuevoNodo;
        return true;
    }
    else if(!this->Buscar(obj)){

        TNodoCalendario *explorado = new TNodoCalendario();
        explorado = this->primero;

        do{
            if(explorado == this->primero && nuevoNodo->c < explorado->c){

                nuevoNodo->siguiente = explorado;
                this->primero = nuevoNodo;
                return true;
            }

            else if(explorado->siguiente != NULL && explorado->siguiente->c > nuevoNodo->c){
                nuevoNodo->siguiente = explorado->siguiente;
                explorado->siguiente = nuevoNodo;
                return true;
            }

            //Inserción al final de la lista
            else if(explorado->siguiente == NULL) {
                nuevoNodo->siguiente = NULL;
                explorado->siguiente = nuevoNodo;
                return true;
            }

            explorado = explorado->siguiente;
        }while(explorado != NULL);

        return false;
    }
    else return false;
}

//Busca y borra el elemento
bool TListaCalendario::Borrar(const TCalendario &obj){
    TNodoCalendario *aux = this->primero;
    TNodoCalendario *aEliminar;

    while(aux != NULL){  //Mientras apuntamos a un nodo..
        //Eliminar primer nodo
        if(this->primero->c == obj){
            aEliminar = this->primero;
            this->primero = this->primero->siguiente; //, si el siguiente es null la lista se queda vacia
            delete aEliminar;
            return true;  //Solo puede haber una ocurrencia
        }

        else{
            //Eliminar nodo intermedio
            if(aux->siguiente != NULL && aux->siguiente->c == obj){
                aEliminar = aux->siguiente;
                aux->siguiente = aux->siguiente->siguiente; //Salteamos el nodo intermedio
                delete aEliminar;
                return true;
            }

            else aux = aux->siguiente;
        }  
    }
    return false;
}

//Borra el elemento que ocupa la posición indicada
bool TListaCalendario::Borrar(const TListaPos &obj){
    if(!obj.EsVacia()){
        TCalendario c = obj.pos->c;
        if(Borrar(c))
            return true;
        else return false;
    }
    else return false;    
}

//Borra todos los Calendarios que ocupa la posición indicada
bool TListaCalendario::Borrar(int dia, int mes,int anyo){
    TNodoCalendario *aux = this->primero;
    TNodoCalendario *aEliminar;
    bool borrado = false;


    TCalendario *limite = new TCalendario(dia,mes,anyo, NULL);
    while(aux != NULL){  //Mientras apuntamos a un nodo..

        /*  Hay que tener en cuenta que para usar el operador < se valora
            el contenido del char, por lo que le asignaremos el mensaje de 
            cada una de las fechas de forma que cuando coincidan las fechas
            lo haga el objeto en su totalidad
        */
        limite->ModMensaje(aux->c.Mensaje());   

        //Eliminar primer nodo
        if(this->primero->c < (*limite)){   //Desreferenciamos el puntero
            aEliminar = this->primero;
            this->primero = this->primero->siguiente; //, si el siguiente es null la lista se queda vacia
            aux = aux->siguiente;

            delete aEliminar;
            borrado = true;            
        }

        else{
            //Eliminar nodo intermedio
            if(aux->siguiente != NULL && aux->siguiente->c < (*limite)){
                aEliminar = aux->siguiente;
                aux->siguiente = aux->siguiente->siguiente; //Salteamos el nodo intermedio

                delete aEliminar;
                borrado = true;
            }

            else if(aux->c == (*limite))
                break;
            
            else aux = aux->siguiente;
        }  
    }
    return borrado;
}

bool TListaCalendario::EsVacia() const{
    if(this->primero == NULL)
        return true;
    return false;
}

TCalendario TListaCalendario::Obtener(const TListaPos &obj) const{
    for(TListaPos i = this->Primera(); !i.EsVacia(); i = i.Siguiente())
        if(i == obj)
            return i.pos->c;

    return TCalendario();
}

bool TListaCalendario::Buscar(const TCalendario &obj) const{
    for(TListaPos i = this->Primera(); !i.EsVacia(); i = i.Siguiente())
        if(i.pos->c == obj) //Únicamente puede haber un TCalendario (fecha+mensaje) en la lista
            return true;
    return false;
}

int TListaCalendario::Longitud() const{
    int longitud = 0;
    for(TListaPos i = this->Primera(); !i.EsVacia(); i = i.Siguiente() )
        longitud++;
    return longitud;
}

TListaPos TListaCalendario::Primera() const{
    TListaPos tpos;
    if(this->EsVacia())
        return tpos;
    else{
        tpos.pos = this->primero;
        return tpos; 
    }
}

TListaPos TListaCalendario::Ultima() const{
    TListaPos ultima = this->Primera();
    for(int i = 1; i < this->Longitud(); i++) // Es necesario inicializar el for a 1 ya que sino siempre cogerá la ultima posición que es NULL
        ultima = ultima.Siguiente();
    return ultima;
}

TListaCalendario TListaCalendario::SumarSubl(int I_L1, int F_L1, TListaCalendario & L2, int I_L2, int F_L2){
    TListaCalendario *L1copia = new TListaCalendario(*this);
    TListaCalendario *L2copia = new TListaCalendario(L2);
    TListaCalendario resultado;

    *L1copia = L1copia->ExtraerRango(I_L1, F_L1);
    *L2copia = L2copia->ExtraerRango(I_L2, F_L2);

    resultado = *L1copia + *L2copia;
    return resultado;
}

TListaCalendario TListaCalendario::ExtraerRango(int n1, int n2){
    TListaCalendario * nuevaLista = new TListaCalendario(*this);
    TListaCalendario listaExtraida;

    if(n1 > n2)
        return listaExtraida;

    if(n1 <= 0)
        n1 = 1;

    if(n2 > this->Longitud())
        n2 = this->Longitud();
    

    int contador = 1;
    for(TListaPos pos = nuevaLista->Primera(); !pos.EsVacia(); pos = pos.Siguiente() ){
        if(contador >= n1 && contador <= n2){
            this->Borrar(pos);
            listaExtraida.Insertar(pos.pos->c);
        }
        contador ++;
    }
    nuevaLista->~TListaCalendario();

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