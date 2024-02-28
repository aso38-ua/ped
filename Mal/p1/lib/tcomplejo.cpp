#include <iostream>
#include <math.h>
#include "tcomplejo.h"

using namespace std;

TComplejo::TComplejo(){
    this->re=0;
    this->im=0;
}
//Constructor a partir de la PARTE REAL
TComplejo::TComplejo (double real){
    this->re=real;
    this->im=0;

}
//Constructor a partir de la PARTE REAL e IMAGINARIA
TComplejo::TComplejo (double real, double imag){
    this->re=real;
    this->im=imag;
}
//Constructor copia
TComplejo::TComplejo (const TComplejo& complejo){
    this->re=complejo.re;
    this->im=complejo.im;
}
//Destructor
TComplejo::~TComplejo(){
    this->re=0;
    this->im=0;
}
// Sobrecarga del operador asignación
TComplejo& TComplejo::operator= (const TComplejo& otro){
    this->~TComplejo(); // evita asignación a sí mismo
    this->re = otro.re;
    this->im = otro.im;
  
  return *this;
}

// SOBRECARGA DE OPERADORES ARITMÉTICOS;
TComplejo TComplejo::operator+ (const TComplejo& sum){
    TComplejo total;

    total.re=this->re+sum.re;
    total.im=this->im+sum.im;

    return total;
}
TComplejo TComplejo::operator- (const TComplejo& res){
    TComplejo total;

    total.re=this->re-res.re;
    total.im=this->im-res.im;

    return total;
}
TComplejo TComplejo::operator* (const TComplejo& mult){
    TComplejo total;

    total.re=this->re*mult.re;
    total.im=this->im*mult.im;

    return total;
}
TComplejo TComplejo::operator+ (double suma){
    TComplejo total;

    total.re=this->re+suma;
    total.im=this->im;

    return total;
    
}
TComplejo TComplejo::operator- (double rest){
    TComplejo total;

    total.re=this->re-rest;
    total.im=this->im;

    return total;
}
TComplejo TComplejo::operator* (double mult){
    TComplejo total;

    total.re=this->re*mult;
    total.im=this->im;

    return total;
}
// OTROS OPERADORES

bool TComplejo::operator== (const TComplejo& complejo)const{
    if (complejo.re==this->re && complejo.im==this->im)
    {
        return true;
    }

    else{
        return false;
    }
    

} // IGUALDAD de números complejos

bool TComplejo::operator!= (const TComplejo& complejo) const{
    if (complejo.re!=this->re || complejo.im!=this->im)
        {
            return true;
        }

        else{
            return false;
        }
}// DESIGUALDAD de números complejos

double TComplejo::Re(){
    return this->re;
} // Devuelve PARTE REAL

double TComplejo::Im(){
    return this->im;

} // Devuelve PARTE IMAGINARIA

void TComplejo::Re(double real){
    this->re=real;
} // Modifica PARTE REAL

void TComplejo::Im(double imag){
    this->im=imag;
} // Modifica PARTE IMAGINARIA

double TComplejo::Arg(void){
    double a=atan2(im,re);
    return a;
} // Calcula el Argumento (en Radianes)

double TComplejo::Mod(void){
    double a=sqrt(pow(re,2) + pow(im,2));
    return a;
} // Calcula el Módulo

// Sobrecarga del operador SALIDA
ostream & operator<<(ostream &os, TComplejo &complejo){
    os<<"("<<complejo.re<<" "<<complejo.im<<")";
    return os;
}
TComplejo operator+ (double sum, const TComplejo& com){
    TComplejo complejo;

    complejo.re=sum+com.re;
    complejo.im=com.im;
    return complejo;
}
TComplejo operator- (double rest,const TComplejo& com){
    TComplejo complejo;

    complejo.re=com.re-rest;
    complejo.im=com.im;
    return complejo;
}
TComplejo operator* (double mult,const TComplejo& com){
    TComplejo complejo;

    complejo.re=com.re*mult;
    complejo.im=com.im;
    return complejo;
}