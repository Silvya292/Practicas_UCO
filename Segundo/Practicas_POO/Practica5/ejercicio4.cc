#include <iostream>
#include <vector>    // necesario para el contenedor vector
#include <algorithm> //Necesario para la función sort()

using namespace std;

bool desc(int a, int b){ //Se define una función para el orden descendente
    return a>b;
}

bool asc(int a, int b){ //Se define una función para el orden ascedente
    return a<b;
}

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
        cout << v[i] << " "; //Se imprime el vector
    }
    cout << endl << endl;

    cout << "Seleccione qué orden desea :" << endl;
    cout << "1. Orden ascendente" << endl << "2. Orden descendente" << endl;
    cout << "Su elección: ";
    int election;
    cin >> election; //Selección del orden del vector
    cout << endl;

    if(election==1){
        sort(v.begin(),v.end(),asc);
    }
    else{
        sort(v.begin(),v.end(),desc);
    }
    
    cout << "Vector ordenado:" << endl;
    for(int i=0;i<v.size();i++){
        cout << v[i] << " "; //Se imprime el vector ordenado
    }
    cout << endl;
    return 0;
}