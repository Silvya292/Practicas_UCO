//jugador-ppal.cc
//Example to prove the class Jugador is working well

#include "jugador.h"
#include <iostream>

using namespace std;

int main(){
    cout << "Comprobación del funcionamiento de la clase Jugador\n\n";
    cout << "   ----------------------------------DATOS DEL JUGADOR-----------------------------------------\n\n";    
    Jugador j("x","x"); //Objeto auxiliar de la clase Jugador
    string cadena; //Cadena para leer los datos
    cout << "Introduzca su DNI: ";
    getline(cin,cadena,'\n');
    j.setDNI(cadena);
    cout << "Introduzca ahora su código de jugador: ";
    getline(cin,cadena,'\n');
    j.setCodigo(cadena);
    cout << "Introduzca su nombre: ";
    getline(cin,cadena,'\n');
    j.setNombre(cadena);
    cout << "Introduzca sus apellidos: ";
    getline(cin,cadena,'\n');
    j.setApellidos(cadena);
    cout << "Introduzca su edad: ";
    getline(cin,cadena,'\n');
    j.setEdad(stoi(cadena));
    cout << "Introduzca su dirección: ";
    getline(cin,cadena,'\n');
    j.setDireccion(cadena);
    cout << "Introduzca su localidad: ";
    getline(cin,cadena,'\n');
    j.setLocalidad(cadena);
    cout << "Introduzca su provincia: ";
    getline(cin,cadena,'\n');
    j.setProvincia(cadena);
    cout << "Introduzca su país: ";
    getline(cin,cadena,'\n');
    j.setPais(cadena);
    system("clear");

    list <Apuesta> apuestas; //Se define una lista auxiliar de apuestas
    j.setApuestas(); //Se leen del fichero las apuestas del jugador
    apuestas=j.getApuestas(); //Se asocian las apuestas del jugador a la lista auxiliar

    list <Apuesta>::iterator i; //Se define un iterador para recorrer la lista
    int n=1; //Contador de apuestas
    cout << "Jugador " << j.getCodigo() << ":\n\n";

    for(i=apuestas.begin();i!=apuestas.end();i++){ //Se imprime la lista de apuestas del jugador
        cout << "Apuesta número " << n << endl;
        cout << "   Tipo: " << i->tipo << endl;
        cout << "   Valor: " << i->valor << endl;
        cout << "   Cantidad: " << i->cantidad << endl << endl;
        n++;
    }

    return 0;
}