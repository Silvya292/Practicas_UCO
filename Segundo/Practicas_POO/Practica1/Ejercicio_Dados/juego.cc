//juego.cc
//Programa principal que prueba el funcionamiento de la clase Dados

#include <iostream>
#include "dados.h"

using namespace std;

void menu(){ //Menú con las funciones del programa
    cout << "              -------------------------JUEGO DE LOS DADOS-------------------------\n\n";
    cout << "              |   Seleccione qué desea hacer:                                    |\n";
    cout << "              |   1. Lanzamiento de los dados                                    |\n";
    cout << "              |   2. Mostrar valor del dado 1                                    |\n";
    cout << "              |   3. Mostrar valor del dado 2                                    |\n";
    cout << "              |   4. Editar valor del dado 1                                     |\n";
    cout << "              |   5. Editar valor del dado 2                                     |\n";
    cout << "              |   6. Mostrar la suma de los valores de ambos dados               |\n";
    cout << "              |   7. Mostrar la diferencia de los valores de ambos dados         |\n";
    cout << "              |   8. Mostrar el nº de lanzamientos del dado 1                    |\n";
    cout << "              |   9. Mostrar el nº de lanzamientos del dado 2                    |\n";
    cout << "              |   10. Mostrar la media de los valores adquiridos por el dado 1   |\n";
    cout << "              |   11. Mostrar la media de los valores adquiridos por el dado 2   |\n";
    cout << "              |   12. Mostrar los últimos cinco valores obtenidos en el dado 1   |\n";
    cout << "              |   13. Mostrar los últimos cinco valores obtenidos en el dado 2   |\n";
    cout << "              |   14. Salir del programa                                         |\n\n";
    cout << "              --------------------------------------------------------------------\n";
}

bool continuar(){ //Función bucle para continuar ejecutando el programa
    cout << "\nDesea continuar (Y/N): ";
    char cont;
    cin >> cont;
    if(cont=='Y'||cont=='y'){
        return true;
    }
    else{
        system("clear");
        cout << "                                         Hasta pronto =)\n\n";
        exit(0);
    }
    cout << "\n";
}


int main(){
    Dados d; //Se crea un objeto de la clase Dados

    int select,dado;

    menu(); //Se imprime el menú

    do{
        system("clear"); //Se limpia la terminal
        menu();
        cout << "\nSu elección: ";
        cin >> select; //El usuario selecciona una opción

        switch(select){
            case 1: //Lanzamiento de los dados
                d.lanzamiento();
                cout << "Dados lanzados correctamente\n";
            break;

            case 2: //Obtención del valor del dado 1
                cout << "Dado 1 (d1_) = " << d.getDado1() << "\n";
            break;

            case 3: //Obtención del valor del dado 2
                cout << "Dado 2 (d2_) = " << d.getDado2() << "\n";
            break;

            case 4: //Introducción de un valor para el dado 1
                cout << "Introduzca el valor del dado: ";
                cin >> dado;
                if(d.setDado1(dado)==true){ //Si el valor está en el rango correcto se añade
                    cout << "Valor añadido\n";
                }
                else{
                    cout << "Error. Valor fuera de rango\n";
                }
            break;

            case 5: //Introducción de un valor para el dado 2
                cout << "Introduzca el valor del dado: ";
                cin >> dado;
                if(d.setDado2(dado)==true){ //Si el valor está en el rango correcto se añade
                    cout << "Valor añadido\n";
                }
                else{
                    cout << "Error. Valor fuera de rango\n";
                }
            break;

            case 6: //Suma de ambos dados
                cout << "La suma de ambos dados es: " << d.getSuma() << "\n";
            break;

            case 7: //Diferencia de ambos dados
                cout << "La diferencia de ambos dados es: " << d.getDiferencia() << "\n";
            break;

            case 8: //Nº de lanzamientos del dado 1
                cout << "El dado 1 se ha lanzado " << d.getLanzamientos1() << " veces\n";
            break;

            case 9: //Nº de lanzamientos del dado 2
                cout << "El dado 2 se ha lanzado " << d.getLanzamientos2() << " veces\n";
            break;

            case 10: //Media de los valores del dado 1
                cout << "La media de los valores del dado 1 es: " << d.getMedia1() << "\n";
            break;

            case 11: //Media de los valores del dado 2
                cout << "La media de los valores del dado 2 es: " << d.getMedia2() << "\n";
            break;

            case 12: //Impresión del vector de valores del dado 1
                int v1[5];
                d.getUltimos1(v1);
            break;

            case 13: //Impresión del vector de valores del dado 2
                int v2[5];
                d.getUltimos2(v2);
            break;

            case 14:
                system("clear");
                cout << "                                         Hasta pronto =)\n\n";
                exit(0);

            default: //Si la opción no es válida se imprime un mensaje de error
                cout << "Opción no válida\n";
            break;
        }
    }while(continuar()==true);

    return 0;

}