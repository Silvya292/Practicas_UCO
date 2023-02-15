//persona.cc
//Body of class Persona's functions

#include "persona.h"

Persona::Persona(string dni,string nombre,string apellidos,int edad,string direccion,string localidad,string provincia,string pais){ //Constructor
    dni_=dni;
    nombre_=nombre;
    apellidos_=apellidos;
    edad_=edad;
    direccion_=direccion;
    localidad_=localidad;
    provincia_=provincia;
    pais_=pais;
}

bool Persona::setEdad(int const &edad){ //Asociación de la edad insertada con la edad de la persona
    if(edad>=0){ //Se comprueba que sea un valor válido y se asocia
        edad_=edad;
        return true;
    }
    return false;
}

bool Persona::mayor() const{ //Comprobación para ver si la persona es mayor de edad
    if(edad_>=18){ //Se comprueba que sea un valor válido
        return true;
    }
    return false;
}