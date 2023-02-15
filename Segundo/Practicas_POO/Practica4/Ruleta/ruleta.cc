//ruleta.cc
//Body of class Ruleta's functions

#include "ruleta.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool Ruleta::setBanca(int const &fondo){ //Asociación del valor insertado al dinero de la banca
    if(fondo>0){ //Si es un valor válido se asocia
        banca_=fondo;
        return true;
    }
    return false;
}

bool Ruleta::setBola(int const &numero){ //Asociación del número insertado a la bola de la ruleta
    if((numero>-1)&&(numero<37)){ //Si es un valor válido se asocia
        bola_=numero;
        return true;
    }
    return false;
}

bool Ruleta::addJugador(Jugador &jugador){ //Adición de un jugador a la lista de la ruleta
    list <Jugador>::iterator j; //Se define un iterador para la lista
    for(j=jugadores_.begin();j!=jugadores_.end();j++){
        if(j->getDNI()==jugador.getDNI()){ //Si el jugador ya existe en la lista se devuelve false
            return false;
        }
    }
    jugadores_.push_back(jugador); //Si no existe previamente se añade al final de la lista
    fstream file((jugador.getDNI()+".txt"),fstream::app); //Se define un fichero genérico y se abre para añadir datos al final
    if(!file){ //Si no existe el fichero se devuelve un error
        cout << "ERROR al abrir el fichero\n";
        return false;
    }
    return true;
}

int Ruleta::deleteJugador(string const &dni){ //Eliminación de un jugador por DNI
    if(jugadores_.empty()){ //Si la lista está vacía se devuelve -1
        return -1;
    }
    list <Jugador>::iterator j; //Se define un iterador para la lista
    for(j=jugadores_.begin();j!=jugadores_.end();j++){
        if(j->getDNI()==dni){ //Si el DNI del jugador ya existe en la lista se elimina
            jugadores_.erase(j);
            return 1;
        }
    }
    return -2; //Si no se ha encontrado devuelve -2
}

int Ruleta::deleteJugador(Jugador &jugador){ //Eliminación de un jugador por DNI
    if(jugadores_.empty()){ //Si la lista está vacía se devuelve -1
        return -1;
    }
    list <Jugador>::iterator j; //Se define un iterador para la lista
    for(j=jugadores_.begin();j!=jugadores_.end();j++){
        if(j->getDNI()==jugador.getDNI()){ //Si el DNI del jugador ya existe en la lista se elimina
            jugadores_.erase(j);
            return 1;
        }
    }
    return -2; //Si no se ha encontrado devuelve -2
}

void Ruleta::escribeJugadores(){ //Inscripción de jugadores
    ofstream file("jugadores.txt"); //Se define un fichero y se abre en modo lectura/escritura
    if(!file){ //Si no es posible abrir el fichero devuelve un mensaje de error
        cout << "ERROR al abrir el archivo\n";
        EXIT_FAILURE;
    }

    list <Jugador>::iterator j; //Se define un iterador para la lista
    for(j=jugadores_.begin();j!=jugadores_.end();j++){ 
        file<<j->getDNI()<<','
        <<j->getCodigo()<<','
        <<j->getNombre()<<','
        <<j->getApellidos()<<','
        <<j->getDireccion()<<','
        <<j->getLocalidad()<<','
        <<j->getProvincia()<<','
        <<j->getPais()<<','
        <<j->getDinero()<<'\n';
    }
    file.close(); //Se cierra el fichero
}

void Ruleta::leeJugadores(){ //Lectura de los jugadores de la lista
    ifstream file("jugadores.txt"); //Se define un fichero y se abre en modo lectura
    if(!file){ //Si no es posible abrir el fichero devuelve un mensaje de error
        cout << "ERROR al abrir el fichero\n";
        EXIT_FAILURE;
    }
    jugadores_.clear(); //Se limpia la lista
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
}

bool Ruleta::rojo_negro(string const &color){ //Comprobación del color
    vector <int> rojo={1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36}; //Vector de números rojos
    vector <int> negro={2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35}; //Vector de números negros
    if(bola_==0){ //Si es 0 devuelve falso al no tener ningún color
        return false;
    }
    else if(color=="rojo"){
        for(int i=0;i<(int)rojo.size();i++){
            if(bola_==rojo[i]){
                return true;
            }
        }
    }
    else if(color=="negro"){
        for(int i=0;i<(int)negro.size();i++){
            if(bola_==negro[i]){
                return true;
            }
        }
    }
    return false;
}

bool Ruleta::par_impar(string const &parimpar){ //Comprobación de la paridad
    vector <int> par={2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36}; //Vector de números pares
    vector <int> impar={1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35}; //Vector de números impares
    if(bola_==0){ //Si es 0 se devuelve falso
        return false;
    }
    else if(parimpar=="par"){
        for(int i=0;i<(int)par.size();i++){
            if(bola_==par[i]){
                return true;
            }
        }
    }
    else if(parimpar=="impar"){
        for(int i=0;i<(int)impar.size();i++){
            if(bola_==impar[i]){
                return true;
            }
        }
    }
    return false;
}

bool Ruleta::alto_bajo(string const &altobajo){ //Comprobación del número
    vector <int> bajo={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18}; 
    vector <int> alto={19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
    if(bola_==0){ //Si es 0 se devuelve falso
        return false;
    }
    else if(altobajo=="alto"){
        for(int i=0;i<(int)alto.size();i++){
            if(bola_==alto[i]){
                return true;
            }
        }
    }
    else if(altobajo=="bajo"){
        for(int i=0;i<(int)bajo.size();i++){
            if(bola_==bajo[i]){
                return true;
            }
        }
    }
    return false;
}

void Ruleta::getPremios(){ //Comprobación de los premios obtenidos
    list <Apuesta> apuestas; //Lista auxiliar de apuestas
    list <Jugador>::iterator j; //Se define un iterador para la lista

    for(j=jugadores_.begin();j!=jugadores_.end();j++){//Se asocian las apuestas de todos los jugadores de la lista de la clase
        j->setApuestas();
        apuestas=j->getApuestas(); //Se asocian las apuestas del jugador a la lista de apuestas auxiliar

        for(auto i=apuestas.begin();i!=apuestas.end();i++){
            Apuesta aux=*i;

            switch(aux.tipo){ //Según el tipo de apuesta la ganancia difiere
                case 1://Apuesta sencilla
                    if(stoi(aux.valor)==bola_){
                        j->setDinero(j->getDinero()+(aux.cantidad*35));
                        setBanca(getBanca()-(aux.cantidad*35));
                        break;
                    }
                    else{
                        j->setDinero(j->getDinero()-aux.cantidad);
                        setBanca(getBanca()+aux.cantidad);
                        break;
                    }

                case 2://Apuesta rojo o negro
                    if(rojo_negro(aux.valor)){
                        j->setDinero(j->getDinero()+aux.cantidad);
                        setBanca(getBanca()-aux.cantidad);
                        break;
                    }
                    else{
                        j->setDinero(j->getDinero()-aux.cantidad);
                        setBanca(getBanca()+aux.cantidad);
                        break;
                    }
                
                case 3://Apuesta par o impar
                    if(par_impar(aux.valor)){
                        j->setDinero(j->getDinero()+aux.cantidad);
                        setBanca(getBanca()-aux.cantidad);
                        break;
                    }
                    else{
                        j->setDinero(j->getDinero()-aux.cantidad);
                        setBanca(getBanca()+aux.cantidad);
                        break;
                    }
                
                case 4://Apuesta alto o bajo
                    if(alto_bajo(aux.valor)){
                        j->setDinero(j->getDinero()+aux.cantidad);
                        setBanca(getBanca()-aux.cantidad);
                        break;
                    }
                    else{
                        j->setDinero(j->getDinero()-aux.cantidad);
                        setBanca(getBanca()+aux.cantidad);
                        break;
                    }
            }
        }
    }
}


void Ruleta::getEstadoRuleta(int &Njugadores, int &sumaDinero, int &Nlanzamientos, int &beneficioBanca){ //Información del estado de la ruleta
    Njugadores=(int) jugadores_.size();
    sumaDinero=banca_; //Se asocia en primer lugar el dinero de la banca a la suma de dinero total
    list <Jugador>::iterator j; //Se define un iterador para la lista
    for(j=jugadores_.begin();j!=jugadores_.end();j++){
        sumaDinero += j->getDinero();
    }
    Nlanzamientos=Nlanzamientos_; //Se asocia el número de lanzamientos
    beneficioBanca=beneficioBanca_; //Se asocia el beneficio de la banca
}
