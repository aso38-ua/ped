#ifndef TLISTACALENDARIO_H 
#define TLISTACALENDARIO_H

#include <iostream>
#include <cstring>
using namespace std;

#include "tcalendario.h"
#include "tvectorcalendario.h"

class TNodoCalendario{
    friend class TListaPos;
    friend class TListaCalendario;

    private:
        //Uso de LAYERING sobre la clase
        TCalendario c;
        TNodoCalendario *siguiente;

    public:
        TNodoCalendario();
        TNodoCalendario(const TNodoCalendario &);
        ~TNodoCalendario();

        TNodoCalendario & operator=(const TNodoCalendario &);
};

class TListaPos{
    friend class TNodoCalendario;
    friend class TListaCalendario;

    private:
        //Para implementar la posicion a nodo de la lista de TCalendario
        TNodoCalendario *pos;

    public:
        TListaPos();
        TListaPos(const TListaPos &);
        ~TListaPos();
        
        TListaPos & operator=(const TListaPos &);
        bool operator==(const TListaPos &) const;
        bool operator!=(const TListaPos &) const;

        TListaPos Siguiente() const;
        bool EsVacia() const;
};

class TListaCalendario{
    friend class TNodoCalendario;
    friend class TListaPos;
    friend ostream & operator<< (ostream &, const TListaCalendario &);

    private:
        TNodoCalendario *primero;

    public:
        TListaCalendario();
        TListaCalendario(const TListaCalendario &);
        ~TListaCalendario();

        TListaCalendario & operator=(const TListaCalendario &);

        bool operator== (TListaCalendario &);
        TListaCalendario operator+ (TListaCalendario &);
        TListaCalendario operator- (TListaCalendario &);
        
        bool Insertar (const TCalendario &);
        bool Borrar(const TCalendario &);
        bool Borrar(const TListaPos &);
        bool Borrar(int,int,int);
        bool EsVacia() const;

        TCalendario Obtener(const TListaPos &) const;
        bool Buscar(const TCalendario &) const;
        
        int Longitud() const;

        TListaPos Primera() const;
        TListaPos Ultima() const;

        //Suma de dos sublistas en una nueva lista
        TListaCalendario SumarSubl (int, int , TListaCalendario &, int, int);
        
        TListaCalendario ExtraerRango (int, int);
};
#endif