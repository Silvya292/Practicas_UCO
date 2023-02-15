//jugador.cc
////Body of class Jugador's functions

#include "jugador.h"
#include <iostream>
#include <fstream>

using namespace std;

void Jugador::setApuestas(){ //Asociación de la lista de apuestas obtenida con las apuestas del jugador
    apuestas_.clear(); //Se borran todos los elementos previos de la lista de apuestas
    ifstream file(getDNI()+ ".txt"); //Se define un fichero que se abre en modo lectura

    if(!file){ //Si no se puede abrir se devuelve error
        cout << "ERROR: No existe el fichero insertado\n";
        EXIT_FAILURE;
    }

    Apuesta apuesta; //Se crea una apuesta auxiliar para leer el fichero
    string cadena; //Se define un string para los elementos de la lista
    getline(file,cadena,','); //Se lee el primer elemento de la lista

    while (!file.eof()){ //Se leerán sucesivamente todos los elementos de la lista y se asocian a lista de la clase
        apuesta.tipo=stoi(cadena);
        getline(file,cadena,',');
        apuesta.valor=cadena;
        getline(file,cadena,'\n');
        apuesta.cantidad=stoi(cadena);
        apuestas_.push_back(apuesta); //Se añaden todos los elementos de la lista leídos al final de la lista de apuestas del jugador
        getline(file,cadena,',');
    }
    file.close(); //Se cierra el fichero
}