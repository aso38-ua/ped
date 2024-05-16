#ifndef _tavlcalendario_ 
#define _tavlcalendario_ 

#include <iostream>
#include "tcalendario.h"
#include "tvectorcalendario.h"

using namespace std;

class TNodoAVL
{
    private:
        // El elemento (etiqueta) del nodo
        TCalendario item;
        // Subárbol izquierdo y derecho
        TAVLCalendario iz, de;
        // Factor de equilibrio
        int fe;

    public:
        //Constructor por defecto
        TNodoAVL();
        //Constructor copia
        TNodoAVL (const TNodoAVL &);
        //Destructor
        ~TNodoAVL();
        // Sobrecarga del operador asignación
        TNodoAVL & operator=( TNodoAVL &);


};

class TAVLCalendario
{
    friend class TNodoAVL;

    private:
        // Puntero al nodo raíz
        TNodoAVL *raiz;

        // AUXILIAR: devuelve el recorrido en INORDEN
        void InordenAux(TVectorCalendario &, int &);
        // AUXILIAR: devuelve el recorrido en PREORDEN
        void PreordenAux(TVectorCalendario &, int &);
        // AUXILIAR: devuelve el recorrido en POSTORDEN
        void PostordenAux(TVectorCalendario &, int &);

    public:

        // Constructor por defecto
        TAVLCalendario ();
        // Constructor de copia
        TAVLCalendario (const TAVLCalendario &);
        // Destructor
        ~TAVLCalendario ();
        // Sobrecarga del operador asignación
        TAVLCalendario & operator=(const TAVLCalendario &);

        // Sobrecarga del operador igualdad
        bool operator==(const TAVLCalendario &);
        // Sobrecarga del operador desigualdad
        bool operator!=(const TAVLCalendario &);
        // Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
        bool EsVacio();
        // Inserta el elemento en el árbol
        bool Insertar(TCalendario &);
        // Devuelve TRUE si el elemento está en el árbol, false en caso contrario
        bool Buscar(TCalendario &);
        // Devuelve la altura del árbol (la altura de un árbol vacío es 0)
        int Altura();
        // Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
        int Nodos();
        // Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
        int NodosHoja();
        // Devuelve el recorrido en INORDEN sobre un vector
        TVectorCalendario Inorden();
        // Devuelve el recorrido en PREORDEN sobre un vector
        TVectorCalendario Preorden();
        // Devuelve el recorrido en POSTORDEN sobre un vector
        TVectorCalendario Postorden();
        // Borra un TCalendario del árbol AVL
        bool Borrar(TCalendario &);
        // Devuelve el elemento TCalendario raíz del árbol AVL
        TCalendario Raiz();
        // Sobrecarga del operador salida
        friend ostream & operator<<(ostream &, TAVLCalendario &);
};


#endif