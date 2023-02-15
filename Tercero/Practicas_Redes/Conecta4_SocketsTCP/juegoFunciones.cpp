#include "./include/juego.h"

//FUNCIONES PARA LA COMPROBACIÓN DE ALINEACIÓN GANADORA

int Partida::conectaVertical(int columna, int fila, char jugador,char tablero[FILAS][COLUMNAS]){
    int filaInicio; //Fila comienzo de la comprobación
    if(fila-3>0){
        filaInicio=fila-3;
    }
    else{
        filaInicio=0;
    }

    int contador=0;
    for(;filaInicio<=fila;filaInicio++){
        if(tablero[filaInicio][columna]==jugador){
            contador++;
        }
        else{
            contador=0;
        }
    }
    return contador;
}

int Partida::conectaHorizontal(int columna, int fila, char jugador,char tablero[FILAS][COLUMNAS]){
    int columnaFinal; //Columna final de la comprobación
    if(columna+4<COLUMNAS){
        columnaFinal=columna+3;
    }
    else{
        columnaFinal=COLUMNAS-1;
    }

    int contador=0;
    for(;columna<=columnaFinal;columna++){
        if(tablero[fila][columna]==jugador){
            contador++;
        }
        else{
            contador=0;
        }
    }
    return contador;
}

int Partida::conectaDiagonalAscendente(int columna, int fila, char jugador,char tablero[FILAS][COLUMNAS]){
    int filaInicio;
    if(fila-3>0){
        filaInicio=fila-3;
    }
    else{
        filaInicio=0;
    }

    int columnaFinal;
    if(columna+4<COLUMNAS){
        columnaFinal=columna+3;
    }
    else{
        columnaFinal=COLUMNAS-1;
    }

    int contador=0;
    while(columna<=columnaFinal && filaInicio<=fila){
        if(tablero[fila][columna]==jugador){
            contador++;
        }
        else{
            contador=0;
        }
        fila--;
        columna++;
    }
    return contador;
}

int Partida::conectaDiagonalDescendente(int columna, int fila, char jugador,char tablero[FILAS][COLUMNAS]){
    int columnaFinal;
    if(columna+4<COLUMNAS){
        columnaFinal=columna+3;
    }
    else{
        columnaFinal=COLUMNAS-1;
    }

    int filaFinal;
    if(fila+4<FILAS){
        filaFinal=fila+3;
    }
    else{
        filaFinal=FILAS-1;
    }

    int contador=0;
    while(columna<=columnaFinal && fila<=filaFinal){
        if(tablero[fila][columna]==jugador){
            contador++;
        }
        else{
            contador=0;
        }
        fila++;
        columna++;
    }
    return contador;
}

//FUNCIÓN PARA LA DETERMINACIÓN DE GANADOR O EMPATE

int Partida::ganador(char jugador,char tablero[FILAS][COLUMNAS]){
    for(int fila=0;fila<FILAS;fila++){
        for(int columna=0;columna<COLUMNAS;columna++){
            if(conectaVertical(columna,fila,jugador,tablero)>=4){
                return CONECTA_VERTICAL;
            }
            if(conectaHorizontal(columna,fila,jugador,tablero)>=4){
                return CONECTA_HORIZONTAL;
            }
            if(conectaDiagonalAscendente(columna,fila,jugador,tablero)>=4){
                return CONECTA_DIAGONAL_ASCENDENTE;
            }
            if(conectaDiagonalDescendente(columna,fila,jugador,tablero)>=4){
                return CONECTA_DIAGONAL_DESCENDENTE;
            }
        }
    }
    return NO_CONECTA;
}

int Partida::empate(char tablero[FILAS][COLUMNAS]){
    for(int i=0;i<COLUMNAS;i++){
        int resultado=obtenerFilaDesocupada(i);
        if(resultado!=NO_VALID){
            return 0;
        }
    }
    return 1;
}

int Partida::obtenerFilaDesocupada(int columna){
    for(int i=FILAS-1;i>=0;i--){
        if(tablero[i][columna]==VACIO){
            return i;
        }
    }
    return NO_VALID;
}

//FUNCIONES PARA EL TABLERO

void limpiarTablero(char tablero[FILAS][COLUMNAS]){
    for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLUMNAS;j++){
            tablero[i][j]=VACIO;
        }
    }
}

int dibujarTablero(char tablero[FILAS][COLUMNAS]){
    for(int i=0;i<COLUMNAS;i++){
        cout<<"|"<<i+1;
        if(i+1>=COLUMNAS){
            cout<<"|";
        }
    }
    cout<<endl;
    for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLUMNAS;j++){
            cout<<"|"<<tablero[i][j];
            if(j+1>=COLUMNAS){
                cout<<"|";
            }
        }
        cout<<endl;
    }
    cout<<endl;
    return 0;
}

//FUNCIÓN PARA COLOCAR LA FICHA EN EL TABLERO

int Partida::colocarFicha(char jugador, int columna){
    if(columna<0 || columna>=COLUMNAS){
        return COLUMNA_INVALIDA;
    }
    int fila=obtenerFilaDesocupada(columna);
    if(fila==NO_VALID){
        return COLUMNA_LLENA;
    }
    tablero[fila][columna]=jugador;
    return CORRECT;
}

//FUNCIONES PARA LOS JUGADORES

int Partida::oponente(int sd){
    if(this->getSdJugador1()==sd){
        return getSdJugador2();
    }
    else if(this->getSdJugador2()==sd){
        return getSdJugador1();
    }
    else{
        return -1;
    }
}

//FUNCIÓN PARA PASAR EL TABLERO A UN STRING

string Partida::tableroToString(char tablero[FILAS][COLUMNAS]){
    string tablero_str="";

    for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLUMNAS;j++){
            if(tablero[i][j]==VACIO){
                tablero_str.append("-,");
            }
            else if(tablero[i][j]==JUGADOR_1){
                tablero_str.append("o,");
            }
            else if(tablero[i][j]==JUGADOR_2){
                tablero_str.append("x,");
            }

            if(j==COLUMNAS-1){
                tablero_str.pop_back();
                tablero_str.append(";");
            }
        }
    }

    return tablero_str;
}

//FUNCIÓN PARA PASAR EL TABLERO A UN FORMATO LEGIBLE PARA EL CLIENTE

void stringToMatrix(string tablero){
    tablero.pop_back();
    int aux=tablero.find(":");
    string newTab=tablero.substr(aux+2, tablero.length()+1);

    for(int i=0;i<COLUMNAS;i++){
        cout<<"|"<<i+1;
        if(i+1>=COLUMNAS){
            cout<<"|";
        }
    }
    cout<<endl;

    cout<<"|";
    for(int i=0;i<newTab.size();i++){
        if(newTab[i]=='-'){
            cout<<VACIO;
        }
        else if(newTab[i]=='o'){
            cout<<JUGADOR_1;
        }
        else if(newTab[i]=='x'){
            cout<<JUGADOR_2;
        }
        else if(newTab[i]==','){
            cout<<"|";
        }
        if(newTab[i]==';' && (i!=newTab.size()-1)){
            cout<<"|";
            cout<<endl;
            cout<<"|";
        }
        if(newTab[i]==';' && (i==newTab.size()-1)){
            cout<<"|";
            cout<<endl;
        }
        
    }
    cout<<endl;
}