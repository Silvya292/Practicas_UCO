//crupier.h
//Definition of class crupier

#ifndef CRUPIER_H
#define CRUPIER_H

#include <string>
#include "persona.h"

using namespace std;

class Crupier: public Persona{ //La clase Crupier hereda la parte public de la clase Persona
    private:
        string codigo_; //Código alfanumérico del crupier
    public:
        Crupier(string dni,string codigo,string nombre="",string apellidos="",int edad=0,string direccion="",string localidad="",string provincia="",string pais=""):Persona(dni,nombre,apellidos,edad,direccion,localidad,provincia,pais){codigo_=codigo;} //Constructor de la clase
        inline string getCodigo() const{return codigo_;} //Función que devuelve el cógido del crupier
        inline void setCodigo(string const &codigo){codigo_=codigo;} //Función que asocia el valor insertado con el código del crupier
};

#endif