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
    this->tamano = vec.tamano;
    this->c = new TCalendario[tamano];

    if(this->c == nullptr){
        this->tamano = 0;
        return;
    }

    for (int i = 0; i <= tamano; ++i) {
        this->c[i] = vec.c[i];
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
    if (this ==&vec)
    {
        return *this;
        
    }else{
        (*this).~TVectorCalendario();
        this->tamano =vec.tamano;
        this->c=new TCalendario[tamano];
        for (int i = 0; i < tamano; i++){
            this->c[i]=vec[i+1];
        }
        return *this;
    }
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
    if (idx < 1 || idx > tamano) return error;
    return c[idx];
}

// Sobrecarga del operador corchete (parte DERECHA)
TCalendario TVectorCalendario::operator[](int idx) const {
    if (idx < 1 || idx > tamano) return error;
    return c[idx];
}

// Tamaño del vector (posiciones TOTALES)
int TVectorCalendario::Tamano() const {
    return tamano;
}

// Cantidad de posiciones OCUPADAS (no vacías) en el vector
int TVectorCalendario::Ocupadas() const {
    int count = 0;
    for (int i = 1; i <= tamano; i++) {
        if (!c[i].EsVacio()) count++;
    }
    return count;
}

// Devuelve TRUE si existe el calendario en el vector
bool TVectorCalendario::ExisteCal(const TCalendario& cal) const {
    for (int i = 1; i <= tamano; ++i) {
        if (c[i] == cal) return true;
    }
    return false;
}

bool TVectorCalendario::bisiesto(int anyo){
    if(anyo % 4 == 0 && (anyo % 100 != 0 || anyo % 400 == 0))
        return true;
    return false; 
}

bool TVectorCalendario::comprobarFecha(int dia, int mes, int anyo){
    //Limites (dias negativos, +12 meses, +31 dias, <1900, mes-dias)
    if(dia > 0 && dia <= 31 && mes > 0 && mes <= 12 && anyo >= 1900){

        //Febrero bisiesto (max 29), sino (max 28)
        if(bisiesto(anyo) && mes==2 && dia > 29)
            return false; 
        
        else if(!bisiesto(anyo) && mes == 2 && dia > 28)
                return false;
        
        //Abril. junio, septiembre y noviembre (=30)
        if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
            if(dia > 30)
                return false;
        }
        return true;
    }
    return false;
}

// Mostrar por pantalla mensajes de TCalendario en el vector, de fecha IGUAL O POSTERIOR a la pasada
void TVectorCalendario::MostrarMensajes(int dia, int mes, int anyo){
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

// REDIMENSIONAR el vector de TCalendario
bool TVectorCalendario::Redimensionar(int t) {
    if (t <= 0 || t == tamano) return false;

    TCalendario *newArray = new TCalendario[t + 1];
    int minSize = t < tamano ? t : tamano;
    for (int i = 1; i <= minSize; ++i) {
        newArray[i] = c[i];
    }
    delete[] c;
    c = newArray;
    tamano = t;
    return true;
}

// Sobrecarga del operador de inserción
ostream& operator<<(ostream& os, const TVectorCalendario& vec) {
    os << "[";
    for (int i = 1; i <= vec.tamano; ++i) {
        if (i > 1) os << ", ";
        os << "(" << i << ") " << vec.c[i];
    }
    os << "]";
    return os;
}
