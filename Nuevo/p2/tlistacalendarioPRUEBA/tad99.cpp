#include <iostream>

using namespace std;

#include "tcalendario.h"
#include "tvectorcalendario.h"
#include "tlistacalendario.h"

int
main(void)
{
    TCalendario a(10,10,2006, (char*) "mensaje 1");
    TCalendario b(11,10,2006, (char*) "mensaje 2");
    TCalendario c(12,10,2006, (char*) "mensaje 3");
    TCalendario d(13,10,2006, (char*) "mensaje 4");
    TCalendario e(14,10,2006, (char*) "mensaje 5");

    TListaCalendario lista;
    TListaCalendario lista2;

    lista.Insertar(a);
    lista.Insertar(b);
    lista.Insertar(c);

    //Probamos el destructor
    cout << lista << endl;
    lista.~TListaCalendario();
    cout << lista << endl;
    cout << lista.Primera().EsVacia() << endl;
    cout << lista.Ultima().EsVacia() << endl;
    

    cout<< lista2 << endl;
    lista2.~TListaCalendario();
    cout << lista2 << endl;




    //Probamos el operador ==
    if(lista == lista2)
        cout << "OK.Las listas vacías coinciden" << endl;
    else cout << "Fallo en la la linea 38 de tad99.cpp" << endl;

    lista.Insertar(a);
    lista.Insertar(b);
    lista.Insertar(c);

    if(lista == lista2)
        cout << "Fallo en la la linea 46 de tad99.cpp" << endl;
    else cout << "OK.Las listas no coinciden" << endl;


    lista2 = lista;
    if(lista == lista2)
        cout << "OK.Las listas coinciden" << endl;
    else cout << "Fallo en la la lainea 52 de tad99.cpp" << endl;

    TListaCalendario *lista3 = new TListaCalendario(lista2);
    if((*lista3) == lista2)
        cout << "OK.Las listas coinciden" << endl;
    else cout << "Fallo en la la linea 57 de tad99.cpp" << endl;

    

    //Probamos el operador+
    TListaCalendario lista4;
    lista4.Insertar(d);
    lista4.Insertar(e);
    cout << lista4 << endl;

    TListaCalendario lista5;
    lista5 = lista + lista4;
    cout << lista5 << endl;
    cout << lista << endl;
    cout << lista4 << endl;



    //Probamos el operador-
    TListaCalendario lista6;
    lista6 = lista - lista4;   
    cout << lista6 << endl; //Como no contienen elementos iguales la lista6 debe ser igual a lista
    cout << lista << endl;
    cout << lista4 << endl;

    lista6 = lista - lista5;
    cout << lista6 << endl; //Como lista5 tiene todos los elementos de lista,e sta se quedará vacia
    cout << lista << endl;
    cout << lista5 << endl;




    //Probamos ExtraerRango()
    lista5 = lista;
    lista6 = lista5.ExtraerRango(1, 10); //Sobrepasa la longitud
    cout << lista6 << endl;
    
    lista5 = lista;
    lista6 = lista5.ExtraerRango(-1, 3); //n1 Por debajo de 0 el rango
    cout << lista6 << endl;

    lista5 = lista;
    lista6 = lista5.ExtraerRango(-3, -1); //n2 Por debajo de 0 el rango
    cout << lista6 << endl;

    lista5 = lista;
    lista6 = lista5.ExtraerRango(2,2); //n1==n2
    cout << lista6 << endl;

    lista5 = lista;
    lista6 = lista5.ExtraerRango(2, 1); //n1>n2
    cout << lista6 << endl;
    
    return 0;
}
