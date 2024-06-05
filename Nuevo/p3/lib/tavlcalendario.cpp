#include <iostream>
#include "../include/tavlcalendario.h"
using namespace std;

// Constructor por defecto
TNodoAVL::TNodoAVL() : item(), iz(), de(), fe(0) {}

// Constructor de copia
TNodoAVL::TNodoAVL(const TNodoAVL &nodo) : item(nodo.item), iz(nodo.iz), de(nodo.de), fe(nodo.fe) {}

// Método Copia
void TNodoAVL::Copia(const TNodoAVL &nodo) {
    item = nodo.item;
    iz = nodo.iz;
    de = nodo.de;
    fe = nodo.fe;
}

// Destructor
TNodoAVL::~TNodoAVL() {}

// Operador de asignación
TNodoAVL& TNodoAVL::operator=(const TNodoAVL &nodo) {
    if (this != &nodo) {
        item = nodo.item;
        iz = nodo.iz;
        de = nodo.de;
        fe = nodo.fe;
    }
    return *this;
}

// Constructor por defecto
TAVLCalendario::TAVLCalendario() : raiz(nullptr) {}

// Método Copia
void TAVLCalendario::Copia(const TAVLCalendario &avl) {
    if (!avl.EsVacio()) {
        raiz = new TNodoAVL();
        raiz->item = avl.raiz->item;
        raiz->iz.Copia(avl.raiz->iz);
        raiz->de.Copia(avl.raiz->de);
        raiz->fe = avl.raiz->fe;
    } else {
        raiz = nullptr;
    }
}

// Constructor de copia
TAVLCalendario::TAVLCalendario(const TAVLCalendario &avl) : raiz(nullptr) {
    Copia(avl);
}

// Destructor
TAVLCalendario::~TAVLCalendario() {
    if (raiz != nullptr) {
        delete raiz;
        raiz = nullptr;
    }
}

// Operador de asignación
TAVLCalendario& TAVLCalendario::operator=(const TAVLCalendario &avl) {
    if (this != &avl) {
        this->~TAVLCalendario();
        Copia(avl);
    }
    return *this;
}

// Operador de igualdad
bool TAVLCalendario::operator==(const TAVLCalendario &avl) const {
    return Inorden() == avl.Inorden();
}

// Operador de desigualdad
bool TAVLCalendario::operator!=(const TAVLCalendario &avl) const {
    return !(*this == avl);
}

// Método para verificar si el árbol está vacío
bool TAVLCalendario::EsVacio() const {
    return (raiz == nullptr);
}

// Método para insertar un calendario
bool TAVLCalendario::Insertar(const TCalendario &cal) {
    bool crece = false;
    return InsertarAux(cal, raiz, crece);
}

// Método auxiliar para la inserción
bool TAVLCalendario::InsertarAux(const TCalendario &cal, TNodoAVL *&nodo, bool &crece) {
    if (nodo == nullptr) {
        nodo = new TNodoAVL();
        nodo->item = cal;
        crece = true;
        return true;
    } else if (cal < nodo->item) {
        bool insertado = InsertarAux(cal, nodo->iz.raiz, crece);
        if (crece) {
            nodo->fe--;
            if (nodo->fe == -2) {
                if (nodo->iz.raiz->fe == 1) {
                    RotarIzquierda(nodo->iz.raiz);
                }
                RotarDerecha(nodo);
                crece = false;
            } else if (nodo->fe == 0) {
                crece = false;
            }
        }
        return insertado;
    } else if (cal > nodo->item) {
        bool insertado = InsertarAux(cal, nodo->de.raiz, crece);
        if (crece) {
            nodo->fe++;
            if (nodo->fe == 2) {
                if (nodo->de.raiz->fe == -1) {
                    RotarDerecha(nodo->de.raiz);
                }
                RotarIzquierda(nodo);
                crece = false;
            } else if (nodo->fe == 0) {
                crece = false;
            }
        }
        return insertado;
    }
    return false;
}

// Rotación a la izquierda
void TAVLCalendario::RotarIzquierda(TNodoAVL *&nodo) {
    TNodoAVL *nuevo = nodo->de.raiz;
    nodo->de.raiz = nuevo->iz.raiz;
    nuevo->iz.raiz = nodo;
    nodo = nuevo;

    nodo->iz.raiz->fe = nodo->iz.raiz->fe - 1 - max(0, nodo->fe);
    nodo->fe = nodo->fe - 1 + min(0, nodo->iz.raiz->fe);
}

// Rotación a la derecha
void TAVLCalendario::RotarDerecha(TNodoAVL *&nodo) {
    TNodoAVL *nuevo = nodo->iz.raiz;
    nodo->iz.raiz = nuevo->de.raiz;
    nuevo->de.raiz = nodo;
    nodo = nuevo;

    nodo->de.raiz->fe = nodo->de.raiz->fe + 1 - min(0, nodo->fe);
    nodo->fe = nodo->fe + 1 + max(0, nodo->de.raiz->fe);
}

// Método para borrar un calendario
bool TAVLCalendario::Borrar(const TCalendario &cal){

    bool borrado = false;

    if (this->EsVacio())
    {
        borrado = false;
    }
    
    if(this->Buscar(cal)){
        
        if(this->raiz->item < cal)
            borrado = this->raiz->de.Borrar(cal);

        else if(this->raiz->item > cal)
            borrado = this->raiz->iz.Borrar(cal);

        else if(this->raiz->iz.EsVacio() && !this->raiz->de.EsVacio()){
            this->raiz = this->raiz->de.raiz;
            borrado = true;
        }

        else if(this->raiz->iz.EsVacio() && this->raiz->de.EsVacio() ){
            this->raiz = nullptr;
            borrado = true;
        }

        else if(!this->raiz->iz.EsVacio() && this->raiz->de.EsVacio()){
            this->raiz = this->raiz->iz.raiz;
            borrado = true;
        }

        else if(!this->raiz->iz.EsVacio() && !this->raiz->de.EsVacio()){
            TCalendario izq = this->raiz->iz.Ordenar();
            this->raiz->item = izq;
            this->raiz->iz.Borrar(izq);
        }

        else borrado = false;

    }

    if (this->raiz != nullptr)
        this->Equilibrar();

    return borrado;
    
}

TCalendario TAVLCalendario::Ordenar() const{
    TCalendario cal;
    if(!this->EsVacio()){
        if(this->raiz->de.EsVacio())
            return this->raiz->item;
        else return this->raiz->de.Ordenar();
    }

    return cal;
}

// Método para equilibrar el árbol
void TAVLCalendario::Equilibrar(){

    this->raiz->fe = CalcularFE();

    if(this->raiz->fe < -1){
        TNodoAVL *izquierdo;

        if(this->raiz->iz.raiz->fe <= 0){
            izquierdo = raiz->iz.raiz;
            raiz->iz.raiz = raiz->iz.raiz->de.raiz;
            izquierdo->de.raiz = raiz;
            raiz = izquierdo;

        } else{

            izquierdo = raiz->iz.raiz;
            raiz->iz.raiz = izquierdo->de.raiz->de.raiz;
            izquierdo->de.raiz->de.raiz = raiz;
            raiz = izquierdo->de.raiz;
            izquierdo->de.raiz = raiz->iz.raiz;
            raiz->iz.raiz = izquierdo;
        }

        this->raiz->fe = CalcularFE();
        this->ActualizarFE();
    }

    else if(this->raiz->fe > 1){
        TNodoAVL *derecho = this->raiz;

        if (raiz->de.raiz->fe >= 0){
            derecho = raiz->de.raiz;
            raiz->de.raiz = raiz->de.raiz->iz.raiz;
            derecho->iz.raiz = raiz;
            raiz = derecho;

        } else{

            derecho = raiz->de.raiz;
            raiz->de.raiz = derecho->iz.raiz->iz.raiz;
            derecho->iz.raiz->iz.raiz = raiz;
            raiz = derecho->iz.raiz;
            derecho->iz.raiz = raiz->de.raiz;
            raiz->de.raiz = derecho;
        }

        this->raiz->fe = CalcularFE();
        this->ActualizarFE();
    }
}

int TAVLCalendario::CalcularFE(){
    int izquierda = this->raiz->iz.Altura(), derecha = this->raiz->de.Altura();    
    return derecha - izquierda;
}

void TAVLCalendario::ActualizarFE(){

    if(this->raiz->iz.raiz != nullptr)
        this->raiz->iz.raiz->fe = this->CalcularFE();

    if(this->raiz->de.raiz != nullptr)
        this->raiz->de.raiz->fe = this->CalcularFE();
}

// Método para buscar un calendario
bool TAVLCalendario::Buscar(const TCalendario &cal) const {
    if (!EsVacio()) {
        if (raiz->item == cal) {
            return true;
        } else {
            return raiz->de.Buscar(cal) || raiz->iz.Buscar(cal);
        }
    }
    return false;
}

// Método para obtener la altura del árbol
int TAVLCalendario::Altura() const {
    return EsVacio() ? 0 : 1 + max(raiz->iz.Altura(), raiz->de.Altura());
}

// Método para contar el número de nodos en el árbol
int TAVLCalendario::Nodos() const {
    return EsVacio() ? 0 : 1 + raiz->iz.Nodos() + raiz->de.Nodos();
}

// Método para obtener la raíz del árbol
TCalendario TAVLCalendario::Raiz() const {
    return EsVacio() ? TCalendario() : raiz->item;
}

// Método para contar el número de nodos hoja en el árbol
int TAVLCalendario::NodosHoja() const {
    if (!EsVacio()) {
        if (!raiz->iz.EsVacio() || !raiz->de.EsVacio()) {
            return raiz->iz.NodosHoja() + raiz->de.NodosHoja();
        } else {
            return 1;
        }
    }
    return 0;
}

// Métodos auxiliares para los recorridos
void TAVLCalendario::InordenAux(TVectorCalendario &v, int &pos) const {
    if (!EsVacio()) {
        raiz->iz.InordenAux(v, pos);
        v[pos++] = Raiz();
        raiz->de.InordenAux(v, pos);
    }
}


void TAVLCalendario::PostordenAux(TVectorCalendario &v, int &pos) const{
    if(!this->EsVacio()){ 
        this->raiz->iz.PostordenAux(v, pos);        
        this->raiz->de.PostordenAux(v, pos);
        v[pos++] = this->Raiz();
    }
}

// Métodos para obtener los recorridos
TVectorCalendario TAVLCalendario::Inorden() const {
    int pos = 1;
    TVectorCalendario v(Nodos());
    InordenAux(v, pos);
    return v;
}

TVectorCalendario TAVLCalendario::Preorden() const{
    int pos = 1;
    TVectorCalendario v (this->Nodos());
    this->PreordenAux(v, pos);
    return v;
}

void TAVLCalendario::PreordenAux(TVectorCalendario &v, int &pos) const{
    if(!this->EsVacio()){
        v[pos++] = this->Raiz();
        this->raiz->iz.PreordenAux(v, pos);        
        this->raiz->de.PreordenAux(v, pos);
    }
}

TVectorCalendario TAVLCalendario::Postorden() const {
    int pos = 1;
    TVectorCalendario v(Nodos());
    PostordenAux(v, pos);
    return v;
}

// Nuevo método para buscar la posición de un nodo en el AVL
int TAVLCalendario::BuscaNodo(const TCalendario &cal) const {
    TNodoAVL *actual = this->raiz;
    TNodoAVL *padre = nullptr;
    bool esHijoIzquierdo = false;

    while (actual != nullptr && actual->item != cal) {
        padre = actual;
        if (cal < actual->item) {
            esHijoIzquierdo = true;
            actual = actual->iz.raiz;
        } else {
            esHijoIzquierdo = false;
            actual = actual->de.raiz;
        }
    }

    if (actual == nullptr) {
        return 0; // Nodo no encontrado
    } else if (actual == raiz) {
        return 3; // Es la raíz
    } else if (esHijoIzquierdo) {
        return 1; // Es hijo izquierdo
    } else {
        return 2; // Es hijo derecho
    }
}

// Función principal para buscar los nodos de la lista en el AVL
int* TAVLCalendario::BuscaAVL(TListaCalendario &lista) {
    int tamanoLista = lista.Longitud();
    
    if (tamanoLista == 0) {
        return nullptr;
    }

    if (this->EsVacio())
    {
        int *resultado = new int[tamanoLista];
        for (int i = 0; i < tamanoLista; i++)
        {
            resultado[i] = 0;
        }
        
        return resultado;
    }
    

    int *resultado = new int[tamanoLista];

    TListaPos pos = lista.Primera();
    for (int i = 0; i < tamanoLista; i++) {
        resultado[i] = BuscaNodo(pos.pos->c); // Aquí accedemos directamente a pos->c
        pos = pos.Siguiente();
    }

    return resultado;
}

// Sobrecarga del operador <<
ostream& operator<<(ostream &s, const TAVLCalendario &obj) {
    TVectorCalendario v = obj.Inorden();
    s << "[";
    for (int i = 1; i <= v.Tamano(); ++i) {
        s << "(" << i << ") " << v[i];
        if (i < v.Tamano()) {
            s << ", ";
        }
    }
    s << "]";
    return s;
}
