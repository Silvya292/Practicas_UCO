//persona.h
//Definition of class Persona

#ifndef PERSONA_H
#define PERSONA_H

#include <string>

using namespace std;

class Persona{
    private:
        string dni_;
        string nombre_;
        string apellidos_;
        int edad_;
        string direccion_;
        string localidad_;
        string provincia_;
        string pais_;
    public:
        Persona(string dni,string nombre="",string apellidos="",int edad=0,string direccion="",string localidad="",string provincia="",string pais=""); //Constructor de la clase
        inline string getDNI() const{return dni_;} //Función que devuelve el DNI de la persona
        inline void setDNI(string const &dni){dni_=dni;} //Función que asocia el valor insertado con el DNI de la persona
        inline string getNombre() const{return nombre_;} //Función que devuelve el nombre de la persona
        inline void setNombre(string const &nombre){nombre_=nombre;} //Función que asocia el valor insertado con el nombre de la persona
        inline string getApellidos() const{return apellidos_;} //Función que devuelve los apellidos de la persona
        inline void setApellidos(string const &apellidos){apellidos_=apellidos;} //Función que asocia el valor insertado con los apellidos de la persona
        inline int getEdad() const{return edad_;} //Función que devuelve la edad de la persona
        bool setEdad(int const &edad); //Función que asocia el valor insertado con la edad de la persona
        inline string getDireccion() const{return direccion_;} //Función que devuelve la dirección de la persona
        inline void setDireccion(string const &direccion){direccion_=direccion;}; //Función que asocia el valor insertado con la dirección de la persona
        inline string getLocalidad() const{return localidad_;} //Función que devuelve la localidad de la persona
        inline void setLocalidad(string const &localidad){localidad_=localidad;} //Función que asocia el valor insertado con la localidad de la persona
        inline string getProvincia() const{return provincia_;} //Función que devuelve la provincia de la persona
        inline void setProvincia(string const &provincia){provincia_=provincia;} //Función que asocia el valor insertado con la provincia de la persona
        inline string getPais() const{return pais_;} //Función que devuelve el pais de la persona
        inline void setPais(string const &pais){pais_=pais;} //Función que asocia el valor insertado con el pais de la persona
        inline string getApellidosyNombre() const{return apellidos_ + ", " + nombre_;} //Función que devuelve la concatenación del nombre y los apellidos de la persona
        bool mayor() const; //Función que indica si la persona es mayor de edad
};

#endif