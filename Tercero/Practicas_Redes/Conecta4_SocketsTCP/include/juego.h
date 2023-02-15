#ifndef JUEGO_H
#define JUEGO_H

#include <iostream>
#include <stdio.h>

//DEFINE con los distintos valores posibles que se obtendrán

#define FILAS 6
#define COLUMNAS 7

#define JUGADOR_1 'o'
#define JUGADOR_2 'x'
#define VACIO ' '

#define NO_VALID -1
#define CORRECT 3
#define COLUMNA_LLENA 2
#define COLUMNA_INVALIDA 4

#define CONECTA_VERTICAL 1
#define CONECTA_HORIZONTAL 2
#define CONECTA_DIAGONAL_ASCENDENTE 3
#define CONECTA_DIAGONAL_DESCENDENTE 4
#define NO_CONECTA 0

using namespace std;

//Clase con las variables de una partida entre dos jugadores
class Partida{
    private:
        int sdJugador1;
        int sdJugador2;
        char jugador1=JUGADOR_1;
        char jugador2=JUGADOR_2;
        bool turn=true;

    public:  
        char tablero[FILAS][COLUMNAS];

        Partida(){
            this->sdJugador1=-1;
            this->sdJugador2=-1;
        }

        Partida(int sd1, int sd2){
            this->sdJugador1=sd1;
            this->sdJugador2=sd2;
        }

        inline char getJugador1(){
            return this->jugador1;
        }

        inline char getJugador2(){
            return this->jugador2;
        }

        inline int getSdJugador1(){ 
            return this->sdJugador1;
        }

        inline int getSdJugador2(){ 
            return this->sdJugador2;
        }

        inline bool getTurn(){
            return this->turn;
        }

        void setSdJugador1(int sd1){ 
            this->sdJugador1=sd1; 
        }
        void setSdJugador2(int sd2){ 
            this->sdJugador2=sd2; 
        }

        inline void setTurn(bool turno){
            this->turn=turno;
        }

        int conectaVertical(int fila, int columna, char jugador,char tablero[FILAS][COLUMNAS]);
        int conectaHorizontal(int fila, int columna, char jugador,char tablero[FILAS][COLUMNAS]);
        int conectaDiagonalAscendente(int fila, int columna, char jugador,char tablero[FILAS][COLUMNAS]);
        int conectaDiagonalDescendente(int fila, int columna, char jugador,char tablero[FILAS][COLUMNAS]);

        int ganador(char jugador,char tablero[FILAS][COLUMNAS]);
        int empate(char tablero[FILAS][COLUMNAS]);

        int colocarFicha(char jugador, int columna);
        int obtenerFilaDesocupada(int columna);

        int oponente(int sd);

        string tableroToString(char tablero[FILAS][COLUMNAS]);
};

void limpiarTablero(char tablero[FILAS][COLUMNAS]); //Vaciar tablero
int dibujarTablero(char tablero[FILAS][COLUMNAS]); //Imprimir tablero
void stringToMatrix(string tablero); //Pasar el string del servidor a un tablero legible para el cliente

#endif
