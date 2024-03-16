#include <iostream>
#include <math.h>
#include <cstring>
#include "tcalendario.h"

using namespace std;

TCalendario::TCalendario(){
    this->dia=1;
    this->mes=1;
    this->anyo=1900;
    this->mensaje=NULL;
}

TCalendario::TCalendario(int dia, int mes, int anyo, char * m){
    if(EsFechaValida(dia, mes, anyo)){
        this->dia = dia;
        this->mes = mes;
        this->anyo = anyo;

        if(m != NULL){
            this->mensaje = new char[strlen(m)+1];
            strcpy(this->mensaje, m);
        }
        else this->mensaje = NULL;
    }
    else{
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        this->mensaje = NULL;
    }
}

TCalendario::TCalendario (const TCalendario& calendario){
    if (EsFechaValida(calendario.dia,calendario.mes,calendario.anyo))
    {
        this->dia = calendario.dia;
        this->mes = calendario.mes;
        this->anyo = calendario.anyo;

        if(calendario.mensaje != NULL){
            this->mensaje = new char[strlen(calendario.mensaje)+1];
            strcpy(this->mensaje, calendario.mensaje);
        }
        else this->mensaje = NULL;
    }

    else{
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        this->mensaje = NULL;
    }
    
}

TCalendario::~TCalendario() {
    this->dia=1;
    this->mes=1;
    this->anyo=1900;
    if (this->mensaje!=NULL)
    {
        delete [] this->mensaje;
    }
    
    this->mensaje=NULL;
}

TCalendario& TCalendario::operator=(const TCalendario& calendario){
    this->~TCalendario();
    this->dia=calendario.dia;
    this->mes=calendario.mes;
    this->anyo=calendario.anyo;
    this->mensaje=calendario.mensaje;

    return *this;
}

// Sobrecarga del operador: SUMA de fecha + un número de dias;
TCalendario TCalendario::operator+(int dias){
    TCalendario tcalendario(*this);

    for(int i = 0; i < dias; i++){
        tcalendario++; 
    }

    return tcalendario;  
}

TCalendario TCalendario::operator-(int dias){
    TCalendario tcalendario(*this);
    
    for(int i = 0; i < dias; i++){
        tcalendario--;
    }

    if(!EsFechaValida(tcalendario.dia, tcalendario.mes, tcalendario.anyo)){
        tcalendario.~TCalendario();
    }

    return tcalendario; 
}

// Sobrecarga del operador de incremento (postincremento)
TCalendario TCalendario::operator++(int dias) {
    TCalendario tcalendario(*this);
    if(mes == 2){
        if(dia ==29 && EsBisiesto(anyo)){
            dia = 1;
            mes ++;             
        }
        else if(dia==28 && !EsBisiesto(anyo)){
            dia = 1;
            mes++;
        }
        else{
            dia++;
        }        
    }
    else if(mes == 12 ){
        if (dia == 31){
            dia = 1;
            anyo++;
            mes = 1;
            
        }
        else{
            dia++;
        }
    }
    else if(mes ==4|| mes ==6 || mes==9 || mes==11){
        if(dia==30){
            mes ++;
            dia=1;
        }
        else{
            dia ++;
        }
    }
    else if(mes ==1|| mes ==3 || mes==5 || mes==7 ||mes ==8 ||mes ==10 ){
        if(dia==31){
            dia=1;
            mes ++;
            
        }
        else{
            dia ++;
        }
    }
    return tcalendario;
}

// Sobrecarga del operador de incremento (preincremento)
TCalendario& TCalendario::operator++() {
    *this = *this + 1; // Utilizamos el operador de suma para incrementar la fecha en un día

    // Verificar si la fecha resultante sigue siendo válida
    if (!EsFechaValida(dia, mes, anyo)) {
        *this = TCalendario(); // Restauramos el valor original si la fecha no es válida
    }

    return *this; // Devolvemos una referencia al objeto actual
}

// Sobrecarga del operador de decremento (postdecremento)
TCalendario TCalendario::operator--(int dias) {
    TCalendario tcalendario(*this);
    dia--;
    if(dia == 0){
        mes--;
        if(mes == 0){
            mes = 12;
            anyo--;
        }
        if(mes == 2 && !EsBisiesto(this->anyo))
            dia = 28;
        else if(mes == 2 && EsBisiesto(this->anyo))
            dia = 29;
        else if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 ||
                mes == 10 || mes == 12)
            dia = 31;
        else dia = 30;
    }

    if(!EsFechaValida(this->dia, this->mes, this->anyo)){
        this->~TCalendario();
    }

    return tcalendario;
}

// Sobrecarga del operador de decremento (predecremento)
TCalendario& TCalendario::operator--() {
    *this = *this - 1; // Utilizamos el operador de resta para decrementar la fecha en un día

    // Verificar si la fecha resultante sigue siendo válida
    if (!EsFechaValida(dia, mes, anyo)) {
        *this = TCalendario(); // Restauramos el valor original si la fecha no es válida
    }

    return *this; // Devolvemos una referencia al objeto actual
}

bool TCalendario::ModFecha (int dia, int mes, int anyo){
    if (!EsFechaValida(dia, mes, anyo)) {
        // Si la fecha no es válida, no realizamos ninguna modificación
        return false;
    }

    this->dia = dia;
    this->mes = mes;
    this->anyo = anyo;

    return true;
}

bool TCalendario::ModMensaje(char* mensaje){
    if (mensaje == nullptr) {
        // Si el mensaje es nulo, liberamos la memoria asignada previamente
        delete[] this->mensaje;
        this->mensaje = nullptr;
        return true;
    } 
    else {
        // Calculamos la longitud de la cadena de mensaje
        int longitud = strlen(mensaje);

        // Reservamos memoria para la nueva cadena de mensaje
        char* nuevoMensaje = new char[longitud + 1];

        // Copiamos el mensaje proporcionado al nuevo espacio de memoria
        strcpy(nuevoMensaje, mensaje);

        // Liberamos la memoria asignada previamente al mensaje antiguo
        delete[] this->mensaje;

        // Actualizamos el puntero mensaje para que apunte al nuevo mensaje
        this->mensaje = nuevoMensaje;

        return true;
    }
}

// Sobrecarga del operador igualdad;
bool TCalendario::operator ==(const TCalendario& otro) const{
    return (dia == otro.dia && mes == otro.mes && anyo == otro.anyo &&
            ((mensaje == nullptr && otro.mensaje == nullptr) ||
             (mensaje != nullptr && otro.mensaje != nullptr && strcmp(mensaje, otro.mensaje) == 0)));
}

// Sobrecarga del operador desigualdad;
bool TCalendario::operator !=(const TCalendario& otro) const{
    return !(*this == otro);
}

// Sobrecarga del operador >; (ver ACLARACIÓN sobre ORDENACIÓN)
bool TCalendario::operator>(const TCalendario& otro) const {
    // Comparamos las fechas primero
    if (anyo > otro.anyo || (anyo == otro.anyo && mes > otro.mes) || (anyo == otro.anyo && mes == otro.mes && dia > otro.dia)) {
        return true; // La fecha de T1 es posterior a la de T2
    } else if (anyo == otro.anyo && mes == otro.mes && dia == otro.dia) {
        // Si las fechas son iguales, comparamos los mensajes
        if (mensaje == nullptr && otro.mensaje != nullptr) {
            return false; // T1 tiene mensaje NULL y T2 tiene mensaje no NULL
        } else if (mensaje != nullptr && otro.mensaje == nullptr) {
            return true; // T1 tiene mensaje no NULL y T2 tiene mensaje NULL
        } else if (mensaje != nullptr && otro.mensaje != nullptr) {
            return strcmp(mensaje, otro.mensaje) > 0; // Comparamos los mensajes usando strcmp
        }
    }
    return false; // Si ninguna condición se cumple, T1 no es mayor que T2
}

// Sobrecarga del operador <; (ver ACLARACIÓN sobre ORDENACIÓN)
bool TCalendario::operator<(const TCalendario& otro) const {
    // La comparación de < es inversa a la de >
    return otro > *this; // Simplemente utilizamos el operador > y lo invertimos
}

//TCalendario vacío
bool TCalendario::EsVacio(){
    return (this->dia == 1 && this->mes == 1 && this->anyo == 1900 && this->mensaje == nullptr);
}

// Devuelve el día del calendario;
int TCalendario::Dia(){
    return this->dia;
}

// Devuelve el mes del calendario;
int TCalendario::Mes(){
    return this->mes;
}

// Devuelve el año del calendario;
int TCalendario::Anyo(){
    return this->anyo;
}

// Devuelve el mensaje del calendario;
char *TCalendario::Mensaje(){
    return this->mensaje;
}

ostream& operator<<(ostream &s, const TCalendario &obj){

    if(obj.dia < 10)
        s << "0" << obj.dia;
    else s << obj.dia;

    s << "/";

    if(obj.mes < 10)
        s << "0" << obj.mes;
    else s << obj.mes;

    s << "/";
    s << obj.anyo << " ";
    s << "\"";
    
    if(obj.mensaje != NULL)
        s << obj.mensaje;
    
    s << "\"";
    
    return s;
}

bool TCalendario::EsFechaValida(int d, int m, int a) {
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

bool TCalendario::EsBisiesto(int a) {
    return ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0));
}