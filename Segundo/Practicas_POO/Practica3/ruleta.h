//ruleta.h
//Definition of class Ruleta

#ifndef RULETA_H
#define RULETA_H

#include "crupier.h"
#include "jugador.h"

class Ruleta{
    private:
        int banca_; //Dinero de la banca
        int bola_; //Número de la ruleta
        list <Jugador> jugadores_; //Lista de jugadores
        Crupier crupier_; //Objeto de la clase Crupier
        bool rojo_negro(string const &color); //Función para comprobar el color de la apuesta
        bool par_impar(string const &parimpar); //Función para comprobar la paridad de la apuesta
        bool alto_bajo(string const &altobajo); //Función para comprobar el número de la apuesta
    public:
        inline Ruleta(Crupier const &crupier):crupier_(crupier.getDNI(), crupier.getCodigo()){ //Constructor de la clase
            srand(time(NULL));
            banca_=1000000;
            bola_=-1;
        };
        inline int getBanca()const{return banca_;} //Función que devuelve el dinero de la banca
        inline int getBola()const{return bola_;} //Función que devuelve la bola obtenida
        bool setBanca(int const &fondo); //Función que asocia el dinero insertado al de la banca
        bool setBola(int const &numero); //Función que asocia el valor de la bola insertado a la de la ruleta
        inline Crupier getCrupier() const{return crupier_;} //Función que devuelve el crupier de la ruleta
        inline void setCrupier(Crupier const &crupier){crupier_=crupier;} //Función que asocia el crupier insertado con el crupier de la ruleta
        inline list <Jugador> getJugadores() const{return jugadores_;} //Función que devuelve una lista con los jugadores de la ruleta
        bool addJugador(Jugador &jugador); //Función que añade un jugador a la ruleta
        int deleteJugador(string const &dni); //Función que elimina un jugador de la ruleta por DNI
        int deleteJugador(Jugador &jugador); //Función que elimina un jugador de la ruleta pasando un objeto de la clase
        void escribeJugadores(); //Función que escribe en un fichero los jugadores de la ruleta
        void leeJugadores(); //Función que lee de un fichero los jugadores de la ruleta
        inline void giraRuleta(){setBola(rand()%37);} //Función que simula el giro de la ruleta
        void getPremios(); //Función que devuelve los premios obtenidos por los jugadores de la ruleta
};

#endif