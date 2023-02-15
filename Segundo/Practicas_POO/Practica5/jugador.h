//jugador.h
//Definition of class Jugador

#ifndef JUGADOR_H
#define JUGADOR_H

#include "persona.h"
#include <string>
#include <list>

using namespace std;

struct Apuesta{ //Declaración de un struct para las apuestas
    int tipo;
    string valor;
    int cantidad;
};

class Jugador: public Persona{ //La clase Jugador hereda la parte public de la clase Persona
    private:
        int dinero_;
        string codigo_;
        list <Apuesta> apuestas_; //Lista de apuestas del jugador
    public:
        Jugador(string dni,string codigo,string nombre="",string apellidos="",int edad=0,string direccion="",string localidad="",string provincia="",string pais=""):Persona(dni,nombre,apellidos,edad,direccion,localidad,provincia,pais){ //Constructor de la clase
            codigo_=codigo;
            dinero_=1000;
        }
        inline string getCodigo() const{return codigo_;} //Función que devuelve el código del jugador
        inline void setCodigo(string const &codigo){codigo_=codigo;} //Función que asocia el valor insertado con el código del jugador
        inline int getDinero() const{return dinero_;} //Función que devuelve el dinero del jugador
        inline void setDinero(int const &dinero){dinero_=dinero;} //Función que asocia el valor insertado con el dinero del jugador
        inline list <Apuesta> getApuestas() const{return apuestas_;} //Función que devuelve la lista de apuestas del jugador
        void setApuestas(); //Función que lee la lista de apuestas del jugador
};

#endif