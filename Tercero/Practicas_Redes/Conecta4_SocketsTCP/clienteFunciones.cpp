#include "./include/cliente.h"

//Interfaz principal del cliente
void start(){
    cout << "\n ------------------------------------------------------------------"  << endl;
    cout << "|                                                                  |" << endl;
    cout << "|                      ¡Bienvenido a ConeCta4!                     |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "| Seleccione una opción:                                           |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "| * Iniciar sesión:                                                |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "| - USUARIO (nombre de usuario)                                    |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "| * Registrarse:                                                   |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "| - REGISTRO -u (nombre de usuario) -p (contraseña)                |" << endl;
    cout << "|                                                                  |" << endl;
    cout << " ------------------------------------------------------------------\n" << endl;
}

//Interfaz para el comienzo de la partida
void gameOptions(){
    cout << "\n ------------------------------------------------------------------"  << endl;
    cout << "|                                                                  |" << endl;
    cout << "|                        ¡Ya estás dentro!                         |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "| Seleccione una opción:                                           |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "| - INICIAR-PARTIDA                                                |" << endl;
    cout << "| - SALIR                                                          |" << endl; 
    cout << "|                                                                  |" << endl;     
    cout << " ------------------------------------------------------------------\n" << endl;
}

//Interfaz con las opciones de juego
void gameInterface(){
    cout << "\n ------------------------------------------------------------------"  << endl;
    cout << "|                                                                  |" << endl;
    cout << "|                       Opciones de juego:                         |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "| Para colocar una ficha indique:                                  |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "| - COLOCAR-FICHA <numero de la columna deseada>                   |" << endl;
    cout << "|                                                                  |" << endl;     
    cout << " ------------------------------------------------------------------\n" << endl;
}