#ifndef _tabbcalendario_ 
#define _tabbcalendario_

#include <iostream>
#include <queue>
#include "tcalendario.h"
#include "tvectorcalendario.h"
#include "tlistacalendario.h"
using namespace std;

class TNodoABB;

class TABBCalendario{
    friend class TNodoABB;
    friend ostream & operator<<(ostream &, const TABBCalendario &);

    private:
        TNodoABB *raiz;

        void InordenAux(TVectorCalendario &, int &) const;
        void PreordenAux(TVectorCalendario &, int &) const;
        void PostordenAux(TVectorCalendario &, int &) const;
        void TABBCalendario::ElegirSubarbol(TCalendario &buscado, TVectorCalendario &v);

    public:
        TABBCalendario();
        TABBCalendario(const TABBCalendario &);
        ~TABBCalendario();
        TABBCalendario & operator=(const TABBCalendario &);

        bool operator==(const TABBCalendario &) const;

        bool EsVacio() const;
        bool Insertar(const TCalendario &);
        bool Borrar(const TCalendario &);
        bool Buscar(const TCalendario &) const;
        TCalendario Raiz() const;
        int Altura() const;
        int Nodos() const;
        int NodosHoja() const;

        TVectorCalendario Inorden() const;
        TVectorCalendario Preorden() const;
        TVectorCalendario Postorden() const;
        TVectorCalendario Niveles() const;

        TABBCalendario operator+(TABBCalendario &);
        TABBCalendario operator-(TABBCalendario &);

        //Examen
        TVectorCalendario ABBCamino(TListaCalendario &l);
        TCalendario Maximo() const;
        TCalendario Minimo() const;
        int ContarNodos() const;
        bool Iguales(const TABBCalendario &abb) const;
        TCalendario AncestroComun(const TCalendario &cal1, const TCalendario &cal2) const;
        int TABBCalendario::NivelNodo(const TCalendario &cal) const;
        bool TABBCalendario::EsSubconjunto(const TABBCalendario &abb) const;
};

class TNodoABB{
    friend class TABBCalendario;

    private:
        TCalendario item;
        TABBCalendario iz, de;

    public:
        TNodoABB();
        TNodoABB(const TNodoABB &);
        ~TNodoABB();

        TNodoABB & operator=(const TNodoABB &);
};

#endif