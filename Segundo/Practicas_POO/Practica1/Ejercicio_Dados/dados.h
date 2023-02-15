//dados.h
//La clase dados representa el lanzamiento de dos dados

#ifndef DADOS_H
#define DADOS_H

#include <iostream>
#include <vector>

class Dados{
    private:
        int d1_; //Valor del dado 1
        int d2_; //Valor del dado 2
        int lanzamientos1_; //Nº de lanzamientos del dado 1
        int lanzamientos2_; //Nº de lanzamientos del dado 2
        float sum1_; //Suma de los valores del dado 1
        float sum2_; //Suma de los valores del dado 2
        std::vector <int> v1_; //Vector que almacena los valores del dado 1
        std::vector <int> v2_; //Vector que almacena los valores del dado 2
        void ordenaDado1(int valor); //Función que ordena los valores del dado 1
        void ordenaDado2(int valor); //Función que ordena los valores del dado 2

    public:
        Dados(); //Constructor de la clase
        void lanzamiento(); //Función que simula el lanzamiento de dos dados
        inline int getDado1() const{return d1_;} //Función que devuelve el valor del dado 1
        inline int getDado2() const{return d2_;} //Función que devuelve el valor del dado 2
        bool setDado1(const int &n); //Función que asocia el valor insertado con el dado 1
        bool setDado2(const int &n); //Función que asocia el valor insertado con el dado 2
        inline int getSuma()const{return d1_+d2_;} //Función que devuelve la suma de los valores de ambos dados
        inline int getDiferencia()const{return (abs(d1_-d2_));} //Función que devuelve la diferencia de los valores de ambos dados
        inline int getLanzamientos1() const{return lanzamientos1_;} //Función que devuelve el nº de lanzamientos del dado 1
        inline int getLanzamientos2()const{return lanzamientos2_;} //Función que devuelve el nº de lanzamientos del dado 2
        float getMedia1()const; //Función que devuelve la media de los valores del dado 1
        float getMedia2() const; //Función que devuelve la media de los valores del dado 2
        void getUltimos1(int ultimosD1[]) const; //Función que devuelve los últimos valores obtenidos en el dado 1
        void getUltimos2(int ultimosD2[]) const; //Función que devuelve los últimos valores obtenidos en el dado 2
};

#endif