#include <iostream>
#include <math.h>
#include <cstring>
#include "tcalendario.h"

using namespace std;

TCalendario::TCalendario(){
    this->dia=1;
    this->mes=1;
    this->anyo=1900;
    this->mensaje=nullptr;
}

TCalendario::TCalendario(int dia, int mes, int anyo,const char * m){
    if(EsFechaValida(dia, mes, anyo)){
        this->dia = dia;
        this->mes = mes;
        this->anyo = anyo;

        if(m != NULL){
            this->mensaje = new char[strlen(m)+1];
            strcpy(this->mensaje, m);
        }
        else this->mensaje = nullptr;
    }
    else{
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        this->mensaje = nullptr;
    }
}

TCalendario::TCalendario (const TCalendario& calendario){
    if (EsFechaValida(calendario.dia,calendario.mes,calendario.anyo))
    {
        this->dia = calendario.dia;
        this->mes = calendario.mes;
        this->anyo = calendario.anyo;

        if(calendario.mensaje != nullptr){
            this->mensaje = new char[strlen(calendario.mensaje)+1];
            strcpy(this->mensaje, calendario.mensaje);
        }
        else this->mensaje = nullptr;
    }

    else{
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        this->mensaje = nullptr;
    }
    
}

TCalendario::~TCalendario() {
    this->dia=1;
    this->mes=1;
    this->anyo=1900;
    if (this->mensaje!=nullptr)
    {
        delete [] this->mensaje;
    }
    
    this->mensaje=nullptr;
}

TCalendario& TCalendario::operator=(const TCalendario& calendario) {
    // Protección contra autoasignación
    if (this != &calendario) {
        // Copiar los datos del calendario pasado al actual
        this->dia = calendario.dia;
        this->mes = calendario.mes;
        this->anyo = calendario.anyo;

        // Liberar la memoria asignada previamente al mensaje
        delete[] this->mensaje;

        // Copiar el mensaje si el calendario pasado tiene uno
        if (calendario.mensaje != nullptr) {
            this->mensaje = new char[strlen(calendario.mensaje) + 1];
            strcpy(this->mensaje, calendario.mensaje);
        } else {
            // Establecer el mensaje como nullptr si el calendario pasado no tiene uno
            this->mensaje = nullptr;
        }
    }
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

// Función privada para incrementar la fecha
void TCalendario::IncrementarFecha() {
    int diasEnMes[] = {0, 31, 28 + EsBisiesto(anyo), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    dia++;
    if (dia > diasEnMes[mes]) {
        dia = 1;
        mes++;
        if (mes > 12) {
            mes = 1;
            anyo++;
        }
    }
}

// Sobrecarga del operador de incremento (postincremento)
TCalendario TCalendario::operator++(int dias) {
    TCalendario tcalendario(*this);
    IncrementarFecha();
    return tcalendario;
}

// Sobrecarga del operador de incremento (preincremento)
TCalendario& TCalendario::operator++() {
    IncrementarFecha();
    return *this;
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
    if (*this==otro)
    {
        return false;
    }
    
    // La comparación de < es inversa a la de >
    else{
        return otro > *this; // Simplemente utilizamos el operador > y lo invertimos
    }
    
}

//TCalendario vacío
bool TCalendario::EsVacio() const{
    return (this->dia == 1 && this->mes == 1 && this->anyo == 1900 && this->mensaje == NULL);
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