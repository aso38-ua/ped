#include <iostream>
#include "../include/tavlcalendario.h"
using namespace std;

TNodoAVL::TNodoAVL() : item(), de(), iz(), fe(){}

TNodoAVL::TNodoAVL(const TNodoAVL &nodo) : item(nodo.item), iz(nodo.iz), de(nodo.de), fe(nodo.fe){}

void TNodoAVL::Copia(const TNodoAVL &nodo) {
    this->item = nodo.item;
    this->iz = nodo.iz;
    this->de = nodo.de;
    this->fe = nodo.fe;
}

TNodoAVL::~TNodoAVL() {
    if (iz.raiz != nullptr) {
        delete iz.raiz;
        iz.raiz = nullptr;
    }
    if (de.raiz != nullptr) {
        delete de.raiz;
        de.raiz = nullptr;
    }
}

TNodoAVL & TNodoAVL::operator=(const TNodoAVL &nodo) {
    if (this != &nodo) {
        this->~TNodoAVL();
        Copia(nodo);
    }
    return *this;
}

TAVLCalendario::TAVLCalendario() {
    this->raiz = nullptr;
}

void TAVLCalendario::Copia(const TAVLCalendario &avl) {
    if (!avl.EsVacio()) {
        this->raiz = new TNodoAVL();
        this->raiz->item = avl.raiz->item;
        this->raiz->iz.Copia(avl.raiz->iz);
        this->raiz->de.Copia(avl.raiz->de);
    } else {
        this->raiz = nullptr;
    }
}

TAVLCalendario::TAVLCalendario(const TAVLCalendario &avl) {
    raiz = nullptr;
    Copia(avl);
}

TAVLCalendario::~TAVLCalendario() {
    if (raiz != nullptr) {
        delete raiz;
        raiz = nullptr;
    }
}

TAVLCalendario & TAVLCalendario::operator=(const TAVLCalendario &avl) {
    if (this != &avl) {
        this->~TAVLCalendario();
        this->Copia(avl);
    }
    return *this;
}

bool TAVLCalendario::operator==(const TAVLCalendario &avl) const {
    return this->Inorden() == avl.Inorden();
}

bool TAVLCalendario::operator!=(const TAVLCalendario &avl) const {
    return !(*this == avl);
}

bool TAVLCalendario::EsVacio() const {
    return (this->raiz == nullptr);
}

bool TAVLCalendario::Insertar(const TCalendario &cal) {
    bool crece = false;
    return InsertarAux(cal, raiz, crece);
}

bool TAVLCalendario::InsertarAux(const TCalendario &cal, TNodoAVL *&nodo, bool &crece) {
    bool insertado = false;

    if (nodo == nullptr) {
        nodo = new TNodoAVL();
        nodo->item = cal;
        crece = true;
        insertado = true;
    } else if (cal < nodo->item) {
        insertado = InsertarAux(cal, nodo->iz.raiz, crece);
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
    } else if (cal > nodo->item) {
        insertado = InsertarAux(cal, nodo->de.raiz, crece);
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
    }
    return insertado;
}

void TAVLCalendario::RotarIzquierda(TNodoAVL *&nodo) {
    TNodoAVL *nuevo = nodo->de.raiz;
    nodo->de.raiz = nuevo->iz.raiz;
    nuevo->iz.raiz = nodo;
    nodo = nuevo;

    nodo->iz.raiz->fe = nodo->iz.raiz->fe - 1 - max(0, nodo->fe);
    nodo->fe = nodo->fe - 1 + min(0, nodo->iz.raiz->fe);
}

void TAVLCalendario::RotarDerecha(TNodoAVL *&nodo) {
    TNodoAVL *nuevo = nodo->iz.raiz;
    nodo->iz.raiz = nuevo->de.raiz;
    nuevo->de.raiz = nodo;
    nodo = nuevo;

    nodo->de.raiz->fe = nodo->de.raiz->fe + 1 - min(0, nodo->fe);
    nodo->fe = nodo->fe + 1 + max(0, nodo->de.raiz->fe);
}

bool TAVLCalendario::Borrar(const TCalendario &cal) {
    bool borrado = false;
    bool decrece = false;
    return BorrarEnAVL(cal, raiz, borrado, decrece);
}

bool TAVLCalendario::BorrarEnAVL(const TCalendario &cal, TNodoAVL *&nodo, bool &borrado, bool &decrece) {
    if (nodo == nullptr) {
        return false;
    }

    if (cal < nodo->item) {
        borrado = BorrarEnAVL(cal, nodo->iz.raiz, borrado, decrece);
        if (decrece) {
            nodo->fe++;
            if (nodo->fe == 2) {
                Equilibrar(nodo);
            } else if (nodo->fe == 1) {
                decrece = false;
            }
        }
    } else if (cal > nodo->item) {
        borrado = BorrarEnAVL(cal, nodo->de.raiz, borrado, decrece);
        if (decrece) {
            nodo->fe--;
            if (nodo->fe == -2) {
                Equilibrar(nodo);
            } else if (nodo->fe == -1) {
                decrece = false;
            }
        }
    } else {
        borrado = true;
        if (nodo->iz.raiz == nullptr || nodo->de.raiz == nullptr) {
            TNodoAVL *aux = nodo->iz.raiz ? nodo->iz.raiz : nodo->de.raiz;
            delete nodo;
            nodo = aux;
            decrece = true;
        } else {
            TCalendario mayorIz = Mayor(nodo->iz.raiz);
            nodo->item = mayorIz;
            borrado = BorrarEnAVL(mayorIz, nodo->iz.raiz, borrado, decrece);
            if (decrece) {
                nodo->fe++;
                if (nodo->fe == 2) {
                    Equilibrar(nodo);
                } else if (nodo->fe == 1) {
                    decrece = false;
                }
            }
        }
    }

    return borrado;
}

void TAVLCalendario::Equilibrar(TNodoAVL *&nodo) {
    if (nodo->fe == -2) {
        if (nodo->iz.raiz->fe <= 0) {
            RotarDerecha(nodo);
        } else {
            RotarIzquierda(nodo->iz.raiz);
            RotarDerecha(nodo);
        }
    } else if (nodo->fe == 2) {
        if (nodo->de.raiz->fe >= 0) {
            RotarIzquierda(nodo);
        } else {
            RotarDerecha(nodo->de.raiz);
            RotarIzquierda(nodo);
        }
    }
}

TCalendario TAVLCalendario::Mayor(TNodoAVL *nodo) const {
    while (nodo->de.raiz != nullptr) {
        nodo = nodo->de.raiz;
    }
    return nodo->item;
}

bool TAVLCalendario::Buscar(const TCalendario &cal) const {
    if (!this->EsVacio()) {
        if (this->raiz->item == cal)
            return true;
        else
            return this->raiz->de.Buscar(cal) || this->raiz->iz.Buscar(cal);
    }
    return false;
}

int TAVLCalendario::Altura() const {
    return EsVacio() ? 0 : 1 + max(this->raiz->iz.Altura(), this->raiz->de.Altura());
}

int TAVLCalendario::Nodos() const {
    return EsVacio() ? 0 : 1 + this->raiz->iz.Nodos() + this->raiz->de.Nodos();
}

TCalendario TAVLCalendario::Raiz() const {
    return EsVacio() ? TCalendario() : this->raiz->item;
}

int TAVLCalendario::NodosHoja() const {
    if (!this->EsVacio()) {
        if (!this->raiz->iz.EsVacio() || !this->raiz->de.EsVacio())
            return this->raiz->iz.NodosHoja() + this->raiz->de.NodosHoja();
        else
            return 1;
    } else {
        return 0;
    }
}

void TAVLCalendario::InordenAux(TVectorCalendario &v, int &pos) const {
    if (!this->EsVacio()) {
        this->raiz->iz.InordenAux(v, pos);
        v[pos++] = this->Raiz();
        this->raiz->de.InordenAux(v, pos);
    }
}

TVectorCalendario TAVLCalendario::Inorden() const {
    int pos = 1;
    TVectorCalendario v(this->Nodos());
    this->InordenAux(v, pos);
    return v;
}

void TAVLCalendario::PreordenAux(TVectorCalendario &v, int &pos) const {
    if (!this->EsVacio()) {
        v[pos++] = this->Raiz();
        this->raiz->iz.PreordenAux(v, pos);
        this->raiz->de.PreordenAux(v, pos);
    }
}

TVectorCalendario TAVLCalendario::Preorden() const {
    int pos = 1;
    TVectorCalendario v(this->Nodos());
    this->PreordenAux(v, pos);
    return v;
}

void TAVLCalendario::PostordenAux(TVectorCalendario &v, int &pos) const {
    if (!this->EsVacio()) {
        this->raiz->iz.PostordenAux(v, pos);
        this->raiz->de.PostordenAux(v, pos);
        v[pos++] = this->Raiz();
    }
}

TVectorCalendario TAVLCalendario::Postorden() const {
    int pos = 1;
    TVectorCalendario v(this->Nodos());
    this->PostordenAux(v, pos);
    return v;
}

// Definición del operador <<
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
