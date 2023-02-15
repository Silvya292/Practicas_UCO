#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <regex>

using namespace std;

void start(); //Interfaz principal del cliente
void gameOptions(); //Interfaz para el comienzo de la partida
void gameInterface(); //Interfaz con las opciones de juego

#endif