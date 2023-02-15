//guess.cc
//A program that generates a random number and test the user to guess it

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(void){
    srand(time(NULL)); //Inicializador de nº aleatorios
    int n=(rand()%10)+1; //Se le asigna a n un nº aleatorio entre 1-10

    cout << "Este programa genera un nº pseudoaleatorio entre 1 y 10. Trate de adivinarlo\n";
    cout << "Escriba un nº: ";

    int guess;
    cin >> guess; //El usuario inserta por teclado un nº

    do{
        if(guess>n){ //Si el nº insertado es mayor a n se imprime este mensaje
            cout << "El nº buscado es menor\nEscriba un nº: ";
            cin >> guess; //Se pide insertar de nuevo otro nº
        }
        else if(guess<n){ //Si el nº insertado es menor a n se imprime este mensaje
            cout << "El nº buscado es mayor\nEscriba un nº: ";
            cin >> guess; //Se pide insertar de nuevo otro nº
        }
        else{ //Se imprime este mensaje si se acertó el nº
        cout << "Ha acertado el nº buscado\n";
        } 
    }while(guess!=n); //Esto se repetirá hasta que el usuario acierte el número generado    
}