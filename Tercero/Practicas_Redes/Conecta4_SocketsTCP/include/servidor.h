#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <strings.h>
#include <cstring>
#include <regex>
#include <ctype.h>
#include <regex.h>

#include "juego.h"

using namespace std;

//Clase usuario con los distintos valores necesario sen el sistema
class Usuario{
    private:
        string userName;
        string password;
        int sd;

    public:
        Usuario(string username, string password, int sd){
            this->setUsername(username);
            this->setPassword(password);
            this->setSd(sd);
        }

        Usuario(){
            this->userName = "";
            this->password = "";
        }

        inline string getUsername(){
            return this->userName; 
        }

        inline string getPassword(){ 
            return this->password; 
        }

        inline int getSd(){ 
            return this->sd; 
        }

        inline void setUsername(string username){ 
            this->userName = username; 
        }

        inline void setPassword(string password){ 
            this->password = password; 
        }

        inline void setSd(int sd){ 
            this->sd = sd; 
        }
};

vector<Usuario> cargarUsuarios(); //Lista con los usuarios guardados en el fichero
bool registrarUsuario(Usuario usuario, vector<Usuario> usuarios); //Añade un nuevo usuario al fichero

bool comprobarPassword(string password, string usuario, vector<Usuario> usuarios); //Comprueba si la contraseña pertenece al nombre de usuario indicado
bool usuarioRepetido(string usuario, vector<Usuario> usuarios); //Comprueba si ya existe el nombre de usuario indicado
bool usuarioRegistrado(string usuario, vector<Usuario> usuariosIn); //Comprueba si el usuario se ha registrado previamente

int partida(int sd, vector<Partida> partidas); //Comprueba en qué partida está el usuario

#endif