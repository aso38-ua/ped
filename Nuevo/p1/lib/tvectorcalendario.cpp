#include <iostream>
using namespace std;

#include "tcalendario.h"
#include "tvectorcalendario.h"

// Constructor por defecto
TVectorCalendario::TVectorCalendario(){
    this->tamano=0;
    this->c=nullptr;
}

// Constructor a partir de un tamaño
TVectorCalendario::TVectorCalendario(int tam){
    if(tam <= 0){
        this->tamano = 0;
        this->c = nullptr;
    }
    else{
        this->tamano = tam;
        this->c = new TCalendario [tam];
        if(c == nullptr){
            this->tamano = 0;
            return;
        }
    }
}

// Constructor de copia
TVectorCalendario::TVectorCalendario(const TVectorCalendario& vec) {
    if (this != &vec) {
        delete[] c;
        tamano = vec.tamano;
        c = new TCalendario[tamano];
        if (c != nullptr) {
            for (int i = 0; i < tamano; ++i) {
                c[i] = vec.c[i];
            }
        } else {
            tamano = 0;
        }
    }
}

// Destructor
TVectorCalendario::~TVectorCalendario() {
    this->tamano = 0;
    if(this->c != nullptr){
        delete [] c;
        this->c = nullptr;
    }
}

// Sobrecarga del operador de asignación
TVectorCalendario& TVectorCalendario::operator=(const TVectorCalendario& vec) {
    if (this != &vec) {
        // Liberar la memoria ocupada por el vector existente
        delete[] c;
        
        // Asignar el tamaño del vector fuente al vector destino
        tamano = vec.tamano;
        
        // Crear un nuevo arreglo de TCalendario y copiar los elementos del vector fuente al vector destino
        c = new TCalendario[tamano];
        for (int i = 0; i < tamano; i++) {
            c[i] = vec.c[i];
        }
    }
    return *this;
}

// Sobrecarga del operador de igualdad
bool TVectorCalendario::operator==(const TVectorCalendario& vec) const {
    if(this->tamano != vec.tamano)
        return false;
    else{
        for(int i = 0; i < this->tamano; i++){
            if(this->c[i] != vec.c[i])
                return false;
        }
    }
    return true;
}

// Sobrecarga del operador de desigualdad
bool TVectorCalendario::operator!=(const TVectorCalendario& vec) const {
    return !(*this == vec);
}

// Sobrecarga del operador corchete (parte IZQUIERDA)
TCalendario& TVectorCalendario::operator[](int idx) {
    if(idx >= 1 && idx <= this->tamano)
        return this->c[idx-1];
    return error;
}

// Sobrecarga del operador corchete (parte DERECHA)
TCalendario TVectorCalendario::operator[](int idx) const {
    if(idx >= 1 && idx <= this->tamano)
        return this->c[idx-1];
    return error;
}

// Tamaño del vector (posiciones TOTALES)
int TVectorCalendario::Tamano() const {
    return tamano;
}

// Cantidad de posiciones OCUPADAS (no vacías) en el vector
int TVectorCalendario::Ocupadas() {
    int count = 0;
    for (int i = 0; i < this->tamano; i++) {
        if (!c[i].EsVacio()){
            count++;
        }
    }
    return count;
}

// Devuelve TRUE si existe el calendario en el vector
bool TVectorCalendario::ExisteCal(const TCalendario& cal) const {
    for (int i = 0; i <= tamano; i++) {
        if (c[i] == cal) return true;
    }
    return false;
}

bool TVectorCalendario::EsFechaValida(int d, int m, int a) {
    if (a < 1900)
        return false;

    if (m < 1 || m > 12)
        return false;

    int max_dias;
    switch (m) {
        case 2:
            // Comprobar si el año es bisiesto
            max_dias = (EsBisiesto(a)) ? 29 : 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            max_dias = 30;
            break;
        default:
            max_dias = 31;
            break;
    }

    if (d < 1 || d > max_dias) // Si el día está fuera del rango [1, max_dias], no es válido
        return false;

    return true;
}

bool TVectorCalendario::EsBisiesto(int a) {
    return ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0));
}

// Mostrar por pantalla mensajes de TCalendario en el vector, de fecha IGUAL O POSTERIOR a la pasada
void TVectorCalendario::MostrarMensajes(int dia, int mes, int anyo){
    if (EsFechaValida(dia, mes, anyo)) {
        stringstream out;
        out << "[";
        
        if((dia,mes,anyo)){

            for(int i = 0; i<this->tamano; i++){

                if(c[i].Anyo() < anyo){
                    continue;
                }
                
                else if(c[i].Anyo() == anyo && c[i].Mes() < mes){
                    continue;
                }
                
                else if(c[i].Anyo() == anyo && c[i].Mes() == mes && c[i].Dia() < dia){
                    continue;
                }
                    
                else{
                    out << c[i];
                    if(i != this->tamano - 1)
                        out << ", ";
                }
            }
        }
        out << "]";
        cout << out.str();
    }
}

// REDIMENSIONAR el vector de TCalendario
bool TVectorCalendario::Redimensionar(int tam) {
    if (tam <= 0 || tam == this->tamano) {
        return false;
    }

    TCalendario *aux = new TCalendario[tam];

    // Copiar elementos del vector actual al nuevo vector
    int minSize = tam < this->tamano ? tam : this->tamano;
    for (int i = 0; i < minSize; i++) {
        aux[i] = this->c[i];
    }

    // Inicializar el resto de elementos del nuevo vector si es más grande
    if (tam > this->tamano) {
        for (int i = this->tamano; i < tam; i++) {
            aux[i] = TCalendario();
        }
    }

    // Liberar memoria del antiguo vector y actualizar miembros de la clase
    delete[] this->c;
    this->c = aux;
    this->tamano = tam;

    return true;
}

// Sobrecarga del operador de inserción
ostream& operator<<(ostream& os, const TVectorCalendario& vec) {
    os << "[";
    for(int i = 1; i <= vec.tamano; i++){
        os << "(" << i <<") " << vec[i];
        if(i!= vec.tamano)
            os << ", "; 
    }
    os<< "]";

    return os;
}
