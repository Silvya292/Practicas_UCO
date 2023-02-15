//ruleta-ppal.cc
//Programa principal para probar la clase Ruleta

#include "ruleta.h"
#include <iostream>
#include <vector>

using namespace std;

void menu(){ //Menú con las funciones del programa
    cout << "   ----------------------------------JUEGO DE LA RULETA----------------------------------------\n\n";
    cout << "   |   Seleccione qué desea hacer:                                                            |\n";
    cout << "   |   1. Cargar los jugadores del fichero jugadores.txt                                      |\n";
    cout << "   |   2. Guardar los jugadores en el fichero jugadores.txt                                   |\n";
    cout << "   |   3. Mostrar el estado de la ruleta, el dinero de la banca y el de los jugadores         |\n";
    cout << "   |   4. Girar la ruleta y conocer los premios obtenidos                                     |\n";
    cout << "   |   5. Eliminar un jugador de la mesa                                                      |\n";
    cout << "   |   6. Añadir un jugador a la mesa                                                         |\n";
    cout << "   |   7. Salir del programa                                                                  |\n\n";
    cout << "   --------------------------------------------------------------------------------------------\n";
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
    system("clear");
    cout << "   ----------------------------------DATOS DEL CRUPIER-----------------------------------------\n\n";    
    Crupier c("x","x"); //Objeto auxiliar de la clase Crupier
    string cadena; //Cadena para leer los datos
    cout << "Introduzca su DNI: ";
    getline(cin,cadena,'\n');
    c.setDNI(cadena);
    cout << "Introduzca ahora su código de crupier: ";
    getline(cin,cadena,'\n');
    c.setCodigo(cadena);
    cout << "Introduzca su nombre: ";
    getline(cin,cadena,'\n');
    c.setNombre(cadena);
    cout << "Introduzca sus apellidos: ";
    getline(cin,cadena,'\n');
    c.setApellidos(cadena);
    cout << "Introduzca su edad: ";
    getline(cin,cadena,'\n');
    c.setEdad(stoi(cadena));
    cout << "Introduzca su dirección: ";
    getline(cin,cadena,'\n');
    c.setDireccion(cadena);
    cout << "Introduzca su localidad: ";
    getline(cin,cadena,'\n');
    c.setLocalidad(cadena);
    cout << "Introduzca su provincia: ";
    getline(cin,cadena,'\n');
    c.setProvincia(cadena);
    cout << "Introduzca su país: ";
    getline(cin,cadena,'\n');
    c.setPais(cadena);
    
    Ruleta r(c);
    list <Jugador> listAux;
    list <Jugador>::iterator j;
    vector <int> beneficioJugadores((int) listAux.size());
    Jugador jAux("x","x"); //Objeto auxiliar de la clase Jugador
    int Njugadores,sumaDinero,Nlanzamientos,beneficioBanca;

    int select;
    menu(); //Se imprime el menú
    do{
        system("clear"); //Se limpia la terminal
        menu();
        cout << "\nSu elección: ";
        cin >> select; //El usuario selecciona una opción

        switch(select){
            case 1: //Cargar los jugadores del fichero jugadores.txt
            r.leeJugadores();
            cout << "Fichero leido correctamente\n";
            break;

            case 2: //Guardar los jugadores en el fichero jugadores.txt
            r.escribeJugadores();
            cout << "Fichero actualizado correctamente\n";
            break;

            case 3: //Mostrar el estado de la ruleta, el dinero de la banca y el de los jugadores
            r.getEstadoRuleta(Njugadores,sumaDinero,Nlanzamientos,beneficioBanca);
            cout << "\nESTADO ACTUAL DE LA RULETA:\n";
            cout << "En la ruleta hay " << Njugadores << " jugadores.\n";
            cout << "La suma de dinero existente en la mesa es de " << sumaDinero << "€\n";
            cout << "La bola se ha lanzado "<< Nlanzamientos << " veces.\n";
            cout << "El beneficio actual de la banca es de " << beneficioBanca << "€\n";

            cout << "\nDINERO DE LA BANCA:\n";
            cout << "El dinero actual de la banca es de " << r.getBanca() << "€\n";
            
            cout << "\nDINERO DE LOS JUGADORES:\n";
            listAux.clear();
            listAux=r.getJugadores();
            j=listAux.begin();
            for(int i=0;i<(int) listAux.size();i++){
                cout << "El dinero del jugador con DNI " << (*j).getDNI() << " y nombre " << (*j).getNombre() << " es: " << (*j).getDinero() <<"€\n";
                j++;
            }
            break;
//TODO correción violación de segmento
            case 4: //Girar la ruleta y conocer los premios obtenidos
            listAux.clear();
            listAux=r.getJugadores();
            j=listAux.begin();
            beneficioBanca=r.getBanca();
            for(int i=0;i< (int) listAux.size();i++){
                beneficioJugadores[i]=(*j).getDinero();
                j++;
            }
            cout << "La bola ha caído en " << r.getBola() << "\n";
            r.getPremios();
            beneficioBanca=r.getBanca()-beneficioBanca; 
            cout << "El beneficio de la banca ha sido de " << beneficioBanca << "€\n\n";
            listAux=r.getJugadores();           
            j=listAux.begin();
            for(int i=0;i< (int) listAux.size();i++){
                beneficioJugadores[i]=(*j).getDinero()-beneficioJugadores[i];
                cout << "El beneficio del jugador con DNI " << (*j).getDNI() << " es de " << beneficioJugadores[i] << "€\n\n";
                j++;
            }
            break;

            case 5: //Eliminar un jugador de la mesa
            cout << "Introduzca el DNI del jugador que desea eliminar: ";
            getline(cin,cadena,'\n');
            if(r.deleteJugador(cadena)==1){
                cout << "Jugador eliminado correctamente\n";
            }
            else if(r.deleteJugador(cadena)==-1){
                cout << "\nERROR: No es posible eliminar el jugador indicado porque la lista está vacía\n";
            }
            else if(r.deleteJugador(cadena)==-2){
                cout << "\nERROR: No es posible eliminar el jugador indicado porque no se encuentra en la lista\n";
            }
            break;
//TODO No deja escribir el DNI
            case 6: //Añadir un jugador a la mesa
            system("clear");
            cout << "   ----------------------------------DATOS DEL JUGADOR-----------------------------------------\n\n";    
            cout << "Introduzca su DNI: ";
            getline(cin,cadena,'\n');
            jAux.setDNI(cadena);
            cout << "Introduzca ahora su código de jugador: ";
            getline(cin,cadena,'\n');
            jAux.setCodigo(cadena);
            cout << "Introduzca su nombre: ";
            getline(cin,cadena,'\n');
            jAux.setNombre(cadena);
            cout << "Introduzca sus apellidos: ";
            getline(cin,cadena,'\n');
            jAux.setApellidos(cadena);
            cout << "Introduzca su edad: ";
            getline(cin,cadena,'\n');
            jAux.setEdad(stoi(cadena));
            cout << "Introduzca su dirección: ";
            getline(cin,cadena,'\n');
            jAux.setDireccion(cadena);
            cout << "Introduzca su localidad: ";
            getline(cin,cadena,'\n');
            jAux.setLocalidad(cadena);
            cout << "Introduzca su provincia: ";
            getline(cin,cadena,'\n');
            jAux.setProvincia(cadena);
            cout << "Introduzca su país: ";
            getline(cin,cadena,'\n');
            jAux.setPais(cadena);
            system("clear");
            if(r.addJugador(jAux)){
                cout << "Jugador añadido correctamente\n";
            }
            else{
                cout << "ERROR:No se ha podido añadir el jugador porque ya se encontraba en la lista\n";
            }
            break;

            case 7: //Salir del programa
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