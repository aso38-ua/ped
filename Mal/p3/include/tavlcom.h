#ifndef _INC_TAVL
#define _INC_TAVL

#include <iostream>
#include "tcomplejo.h"
#include "tvectorcom.h"

using namespace std;

class TNodoAVL;

class TAVLCom
{

    friend class TNodoAVL;

private:
    TNodoAVL *raiz;

    void InordenAux(TVectorCom &vec, int &pos) const;
    void PreordenAux(TVectorCom &vec, int &pos) const;
    void PostordenAux(TVectorCom &vec, int &pos) const;

public:
    TAVLCom();
    TAVLCom(const TAVLCom &avl);
    ~TAVLCom();
    TAVLCom &operator=(const TAVLCom &avl);

    bool operator==(const TAVLCom &avl) const;
    bool operator!=(const TAVLCom &avl) const;
    bool EsVacio() const;
    bool Insertar(TComplejo &complejo);
    bool Buscar(TComplejo &complejo);
    bool Borrar(TComplejo &complejo);
    int Altura() const;
    TComplejo Raiz() const;
    int NodosAux(int total) const;
    int Nodos() const;
    int NodosHoja();
    TVectorCom Inorden() const;
    TVectorCom Preorden() const;
    TVectorCom Postorden() const;

    TNodoAVL *Copiar(TNodoAVL *nodo);

    friend ostream &operator<<(ostream &os, TAVLCom &avl);

    void RotacionII();
    void RotacionDD();
    void RotacionID();
    void RotacionDI();
    void Balancear();
    TNodoAVL *BuscarMin();
    void ActualizarAltura();

    
};

class TNodoAVL
{

    friend class TAVLCom;

private:
    TComplejo item;
    TAVLCom iz, de;
    int fe;

public:
    TNodoAVL();
    TNodoAVL(const TNodoAVL &avl);
    ~TNodoAVL();
    TNodoAVL &operator=(const TNodoAVL &avl);

    
};



#endif