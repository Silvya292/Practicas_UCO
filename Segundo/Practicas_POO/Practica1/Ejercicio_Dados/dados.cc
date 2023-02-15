//dados.cc
//Cuerpo de los métodos de la clase Dados

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "dados.h"

Dados::Dados(){ //Constructor
   srand(time(NULL)); //Inicialización de nº aleatorios
   d1_=d2_=1; //Se inician ambos dados con valor 1
   lanzamientos1_=lanzamientos2_=0; //Se inicia el nº de lanzamientos a 0
   sum1_=sum2_=0; //Se inicia la suma de ambos dados a 0
   v1_.resize(5); //Se redimensiona el vector del dado 1 con 5 elementos
   v2_.resize(5); //Se redimensiona el vector del dado 2 con 5 elementos
   v1_[0]=d1_; //Se pone el primer valor del vector del dado 1 con el valor del dado
   v2_[0]=d2_; //Se pone el primer valor del vector del dado 2 con el valor del dado
   for(int i=1;i<5;i++){ //Se ponen a 0 todos los demás elementos de ambos vectores
       v1_[i]=0;
       v2_[i]=0;
   }
}

void Dados::lanzamiento(){ //Lanzamiento de ambos dados
    setDado1((rand()%6)+1); //Nº pseudoaleatorio entre 1 y 6
    setDado2((rand()%6)+1); //Nº pseudoaleatorio entre 1 y 6
}

bool Dados::setDado1(const int &n){ //Asociación del valor insertado al dado 1
    if((0<n)&&(n<7)){ //Se comprueba que sea un valor válido y se asocia
        d1_=n;
        lanzamientos1_++; //Se aumenta el nº de lanzamientos
        sum1_+=d1_; //Se aumenta la suma de los valores del dado
        ordenaDado1(d1_); //Se añade el valor al vector que los ordena
        return true;
    }
    else{ //En caso contrario devuelve error
        return false;
    }
}

bool Dados::setDado2(const int &n){ //Asociación del valor insertado al dado 2
    if((0<n)&&(n<7)){ //Se comprueba que sea un valor válido y se asocia
        d2_=n;
        lanzamientos2_++; //Se aumenta el nº de lanzamientos
        sum2_+=d2_; //Se aumenta la suma de los valores del dado
        ordenaDado2(d2_); //Se añade el valor al vector que los ordena
        return true;
    }
    else{ //En caso contrario devuelve error
        return false;
    }
}

float Dados::getMedia1() const{ //Media de los valores obtenidos en el dado 1
    if(lanzamientos1_==0){ //Si el dado no se ha lanzado devuelve 0
        return 0;
    }
    return sum1_/lanzamientos1_; //En caso contrario se devuelve la media
}

float Dados::getMedia2() const{ //Media de los valores obtenidos en el dado 2
    if(lanzamientos2_==0){ //Si el dado no se ha lanzado devuelve 0
        return 0;
    }
    return sum2_/lanzamientos2_; //En caso contrario se devuelve la media
}

void Dados::ordenaDado1(int n){ //Ordenación del vector del dado 1
    for(int i=4;i>0;i--){
        v1_[i]=v1_[i-1]; //Se trasladan los valores previos del vector
    }
    v1_[0]=n; //Se le asocia al primer elemento el último valor obtenido
}

void Dados::ordenaDado2(int n){ //Ordenación del vector del dado 2
    for(int i=4;i>0;i--){
        v2_[i]=v2_[i-1]; //Se trasladan los valores previos del vector
    }
    v2_[0]=n; //Se le asocia al primer elemento el último valor obtenido
}

void Dados::getUltimos1(int ultimosD1[]) const{ //Se imprime el vector del dado 1
    for(int i=0;i<5;i++){
        ultimosD1[i]=v1_[i]; //Se asocian al vector auxiliar los valores del vector de la clase
    }
    std::cout << "Los últimos valores obtenidos en el dado 1 han sido:\n";
    for(int i=0;i<5;i++){
        std::cout << "v[" << i << "]=" << ultimosD1[i] << "\n"; //Se imprime el vector
    }
}

void Dados::getUltimos2(int ultimosD2[]) const{ //Se imprime el vector del dado 2
    for(int i=0;i<5;i++){
        ultimosD2[i]=v2_[i]; //Se asocian al vector auxiliar los valores del vector de la clase
    }
    std::cout << "Los últimos valores obtenidos en el dado 2 han sido:\n";
    for(int i=0;i<5;i++){
        std::cout << "v[" << i << "]=" << ultimosD2[i] << "\n"; //Se imprime el vector
    }
}
