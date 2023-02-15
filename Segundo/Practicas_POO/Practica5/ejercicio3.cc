#include <iostream>
#include <vector>    // Necesario para el contenedor vector
#include <algorithm> //Necesario para la función sort()

using namespace std;

int main(){
    cout << "ORDENACIÓN DE VECTORES" << endl;
    cout << "Introduzca el número de elementos del vector: ";
    int nEle; //Número de elementos del vector
    cin >> nEle;

    vector <int> v(nEle); //Se crea un vector de nEle elementos

    for(int i=0;i<v.size();i++){
        cout << "Introduzca elemento para el vector: ";
        cin >> v[i]; //Se introducen todos los elementos del vector
    }

    cout << endl;
    cout << "Vector insertado:" << endl;
    for(int i=0;i<v.size();i++){
        cout << v[i] << " "; //Se imprime el vector insertado
    }
    cout << endl << endl;

    sort(v.begin(),v.end()); //Se ordena el vector
    cout << "Vector ordenado:" << endl;
    for(int i=0;i<v.size();i++){
        cout << v[i] << " "; //Se imprime el vector ordenado
    }
    cout << endl;
    return 0;
}