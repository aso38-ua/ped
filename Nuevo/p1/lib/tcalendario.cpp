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

TCalendario::TCalendario(int dia, int mes, int anyo, char* mensaje){
    if (!EsFechaValida(dia, mes, anyo))
    {
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        this->mensaje = nullptr;
    }
    else{
        this->dia=dia;
        this->mes=mes;
        this->anyo=anyo;
        this->mensaje = new char[strlen(mensaje) + 1];
        strcpy(this->mensaje, mensaje);
    }
    
}

TCalendario::TCalendario (const TCalendario& calendario){
    this->dia=calendario.dia;
}

TCalendario::~TCalendario() {
    this->dia=1;
    this->mes=1;
    this->anyo=1900;
    this->mensaje=nullptr;
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
    TCalendario resultado(*this);

    // Sumamos los días
    int diasActuales = Dia();
    int mesesActuales = Mes();
    int anyosActuales = Anyo();

    while (dias > 0) {
        // Determinamos el máximo de días para el mes actual y año actual
        int maxDiasMes = 31;
        if (mesesActuales == 2) {
            maxDiasMes = ((anyosActuales % 4 == 0 && anyosActuales % 100 != 0) || (anyosActuales % 400 == 0)) ? 29 : 28;
        } else if (mesesActuales == 4 || mesesActuales == 6 || mesesActuales == 9 || mesesActuales == 11) {
            maxDiasMes = 30;
        }

        int diasRestantesEnMes = maxDiasMes - diasActuales;
        if (diasRestantesEnMes >= dias) {
            // Si los días restantes en el mes son suficientes para completar la suma, simplemente sumamos y salimos del bucle
            diasActuales += dias;
            break;
        } 
        else {
            // Si no, avanzamos al siguiente mes
            dias -= diasRestantesEnMes + 1; // Restamos los días que ya hemos sumado más el día actual
            diasActuales = 1; // Reiniciamos el contador de días al principio del mes
            mesesActuales++;
            if (mesesActuales > 12) {
                // Si nos pasamos de diciembre, avanzamos al siguiente año y reiniciamos el contador de meses
                mesesActuales = 1;
                anyosActuales++;
            }
        }
    }

    // Modificamos el objeto resultado con los nuevos valores de día, mes y año
    resultado.ModFecha(diasActuales, mesesActuales, anyosActuales);

    return resultado;
}

TCalendario TCalendario::operator-(int dias){
    TCalendario resultado(*this); // Creamos una copia del objeto actual

    // Restamos los días
    int diasActuales = Dia(); // Obtenemos el día actual
    int mesesActuales = Mes(); // Obtenemos el mes actual
    int anyosActuales = Anyo(); // Obtenemos el año actual

    while (dias > 0) {
        // Si los días a restar son menores o iguales que los días actuales
        if (dias <= diasActuales) {
            diasActuales -= dias;
            break;
        } else {
            // Si no, restamos los días actuales y avanzamos al mes anterior
            dias -= diasActuales + 1; // Restamos los días que ya hemos restado más el día actual
            mesesActuales--;
            if (mesesActuales < 1) {
                // Si nos pasamos de enero, retrocedemos al año anterior y reiniciamos el contador de meses
                mesesActuales = 12;
                anyosActuales--;
            }
            // Determinamos el máximo de días para el mes anterior
            int maxDiasMesAnterior = 31;
            if (mesesActuales == 2) {
                maxDiasMesAnterior = ((anyosActuales % 4 == 0 && anyosActuales % 100 != 0) || (anyosActuales % 400 == 0)) ? 29 : 28;
            } else if (mesesActuales == 4 || mesesActuales == 6 || mesesActuales == 9 || mesesActuales == 11) {
                maxDiasMesAnterior = 30;
            }
            diasActuales = maxDiasMesAnterior;
        }
    }

    // Modificamos el objeto resultado con los nuevos valores de día, mes y año
    resultado.ModFecha(diasActuales, mesesActuales, anyosActuales);

    return resultado;
}

// Sobrecarga del operador de incremento (postincremento)
TCalendario TCalendario::operator++(int) {
    TCalendario copia(*this); // Hacemos una copia del objeto actual
    *this = *this + 1; // Utilizamos el operador de suma para incrementar la fecha en un día
    return copia; // Devolvemos la copia del objeto antes de incrementarlo
}

// Sobrecarga del operador de incremento (preincremento)
TCalendario& TCalendario::operator++() {
    *this = *this + 1; // Utilizamos el operador de suma para incrementar la fecha en un día
    return *this; // Devolvemos una referencia al objeto actual
}

// Sobrecarga del operador de decremento (postdecremento)
TCalendario TCalendario::operator--(int) {
    TCalendario copia(*this); // Hacemos una copia del objeto actual
    *this = *this - 1; // Utilizamos el operador de resta para decrementar la fecha en un día
    return copia; // Devolvemos la copia del objeto antes de decrementarlo
}

// Sobrecarga del operador de decremento (predecremento)
TCalendario& TCalendario::operator--() {
    *this = *this - 1; // Utilizamos el operador de resta para decrementar la fecha en un día
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




bool TCalendario::EsFechaValida(int d, int m, int a) {
    if (a < 1900)
        return false;

    if (m < 1 || m > 12)
        return false;

    int max_dias;
    switch (m) {
        case 2:
            // Comprobar si el año es bisiesto
            max_dias = ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) ? 29 : 28;
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