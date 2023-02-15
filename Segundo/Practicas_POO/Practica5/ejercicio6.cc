#include <iostream>
using namespace std;

template <class T> //Declaramos la clase abstracta T

void imprimeVector(T vector[], int nEle){
    for(int i=0;i<nEle;i++){
        cout << vector[i] << " "; //Se imprimirán todos los elementos del vector pasado como argumento sin importar el tipo de sus variables
    }
    cout << "\n";
}

int main(){
    int vInt[5]={1,3,5,7,9}; //Se declara un vector de enteros
    float vFloat[5]={1.1,3.1,5.1,7.1,9.1}; //Se declara un vector de flotantes
    char vChar[7]="Silvia"; //Se declara un vector de caracteres

    cout << "Vector de enteros: ";
    imprimeVector(vInt,5); //Se llama a la función pasándole un vector de enteros
    cout << "Vector de flotantes: ";
    imprimeVector(vFloat,5); //Se llama a la función pasándole un vector de flotantes
    cout << "Vector de caracteres: ";
    imprimeVector(vChar,7); //Se llama a la función pasándole un vector de caracteres
}