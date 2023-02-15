#include <iostream>
#include <vector>    // Necesario para el contenedor vector
#include <algorithm> //Necesario para la función sort()
#include <fstream>
#include "jugador.h"

using namespace std;

bool desc(Jugador a, Jugador b){ //Se define una función para el orden descendente
    return a.getDNI()>b.getDNI();
}

bool asc(Jugador a, Jugador b){ //Se define una función para el orden ascedente
    return a.getDNI()<b.getDNI();
}

vector <Jugador> leeJugadores(){ //Lectura de los jugadores de la lista
    ifstream file("jugadores.txt"); //Se define un fichero y se abre en modo lectura
    if(!file){ //Si no es posible abrir el fichero devuelve un mensaje de error
        cout << "ERROR al abrir el fichero\n";
        EXIT_FAILURE;
    }

    vector <Jugador> jugadores_; //Se crea un vector de jugadores

    jugadores_.clear(); //Se vacía el vector
    Jugador jugador_aux("x","x"); //Se define un jugador auxiliar
    string dato;
    getline(file,dato,','); //Se lee el primer elemento de la lista
    while(!file.eof()){ //Hasta el final del fichero se van leyendo todos los datos y asociándolos a los atributos del jugador auxiliar
        jugador_aux.setDNI(dato);
        getline(file,dato,',');
        jugador_aux.setCodigo(dato);
        getline(file,dato,',');
        jugador_aux.setNombre(dato);
        getline(file,dato,',');
        jugador_aux.setApellidos(dato);
        getline(file,dato,',');
        jugador_aux.setDireccion(dato);
        getline(file,dato,',');
        jugador_aux.setLocalidad(dato);
        getline(file,dato,',');
        jugador_aux.setProvincia(dato);
        getline(file,dato,',');
        jugador_aux.setPais(dato);
        getline(file,dato,'\n');
        jugador_aux.setDinero(stoi(dato));
        jugadores_.push_back(jugador_aux); //Se añade al final de la lista de jugadores el jugador leido
        getline(file,dato,',');
    }
    file.close(); //Se cierra el fichero
    return jugadores_;
}

int main(){
    vector <Jugador> v; //Se crea un vector de jugadores
    v=leeJugadores(); //Se leen todos los elementos

    cout << "ORDENACIÓN DE VECTORES DE JUGADORES POR DNI" << endl;
    cout << "Vector inicial de DNIs: " << endl;
    for(int i=0;i<(int)v.size();i++){
        cout << v[i].getDNI() << " "; //Se imprime el vector inicial
    }
    cout << "\n\n";

    cout << "Seleccione qué orden desea :" << endl;
    cout << "1. Orden ascendente" << endl << "2. Orden descendente" << endl; 
    cout << "Su elección: ";
    int election;
    cin >> election; //Selección del orden
    cout << endl;

    if(election==1){
        sort(v.begin(),v.end(),asc);
    }
    else{
        sort(v.begin(),v.end(),desc);
    }

    cout << "Vector ordenado:" << endl;
    for(int i=0;i<v.size();i++){
        cout << v[i].getDNI() << " "; //Se imprime el vector ordenado
    }
    cout << endl;
    return 0;
}