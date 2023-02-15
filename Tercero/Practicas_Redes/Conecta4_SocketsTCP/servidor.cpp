#include "./include/servidor.h"
#include "./include/juego.h"

using namespace std;

#define MSG_SIZE 250
#define MAX_USUARIOS 30

void manejador(int signum);
void salirCliente(int socket, fd_set * readfds, int * numUsuarios, int arrayUsuarios[]);

/*---------------------------------------------------- 
	Descriptor del socket y buffer de datos                
-----------------------------------------------------*/
int sd, new_sd;
struct sockaddr_in sockname, from;
char buffer[MSG_SIZE];
socklen_t from_len;
struct hostent * host;

fd_set readfds, auxfds;
int salida;
int arrayUsuarios[MAX_USUARIOS];
int numUsuarios = 0;
int i,j,k;
int recibidos;
char identificador[MSG_SIZE];

int on, ret;

vector<Usuario> usuariosRegistrados=cargarUsuarios(); //Carga todos los usuarios registrados del sistema
vector<Usuario> usuariosConectados; //Carga todos los usuarios que se encuentren activos
vector<int> cola; //Carga los usuarios que están en cola para jugar
vector<Partida> partidas; //Lista de partidas simultáneas

regex_t regex_;
int result;
   
int main(){

    cout<<"Servidor del juego activo...\n";
    result = regcomp(&regex_, "REGISTRO -u \\w* -p \\w*", REG_EXTENDED);

    /* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
  	sd = socket (AF_INET, SOCK_STREAM, 0);
	if (sd == -1){
		perror("-Err. No se puede abrir el socket cliente.\n");
    		exit (1);	
	}

    on=1;
    ret = setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    sockname.sin_family = AF_INET;
	sockname.sin_port = htons(2060);
	sockname.sin_addr.s_addr =  INADDR_ANY;

    if (bind (sd, (struct sockaddr *) &sockname, sizeof (sockname)) == -1){
		perror("-Err. Error en la operación bind.\n");
		exit(1);
	}

    /*---------------------------------------------------------------------
		De las peticiones que vamos a aceptar sólo necesitamos el 
		tamaño de su estructura, el resto de información (familia, puerto, 
		ip), nos la proporcionará el método que recibe las peticiones.
   	----------------------------------------------------------------------*/
	from_len = sizeof (from);

	if(listen(sd,1) == -1){
		perror("-Err. Error en la operación de listen.\n");
		exit(1);
	}

    //Inicializar los conjuntos fd_set
    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_SET(sd,&readfds);
    FD_SET(0,&readfds);


    //Capturamos la señal SIGINT (Ctrl+c)
    signal(SIGINT,manejador);

    while(1){

        //Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados
        auxfds = readfds;
        salida = select(FD_SETSIZE,&auxfds,NULL,NULL,NULL);

        if(salida > 0){
            for(i=0; i<FD_SETSIZE; i++){
                //Buscamos el socket por el que se ha establecido la comunicación
                if(FD_ISSET(i, &auxfds)) {
                    if( i == sd){
                        if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1){
                            perror("-Err. Error aceptando peticiones.");
                        }
                        else{
                            if(numUsuarios < MAX_USUARIOS){
                                cout<<"+Ok. Usuario conectado\n";
                                strcpy(buffer, "+Ok. Usuario conectado\n");
                                usuariosRegistrados=cargarUsuarios();

                                arrayUsuarios[numUsuarios] = new_sd;
                                numUsuarios++;
                                FD_SET(new_sd,&readfds);
                            
                                send(new_sd,buffer,sizeof(buffer),0);
                            
                            }
                            else{
                                bzero(buffer,sizeof(buffer));
                                strcpy(buffer,"-Err. Demasiados clientes conectados. Inténtelo de nuevo más tarde.\n");
                                send(new_sd,buffer,sizeof(buffer),0);
                                close(new_sd);
                            }          
                        }
                    }
                    else if (i == 0){
                        //Se ha introducido información de teclado
                        bzero(buffer, sizeof(buffer));
                        fgets(buffer, sizeof(buffer),stdin);

                        if(strcmp(buffer,"SALIR\n")==0){
                            manejador(SIGINT);
                        }
                    }
                    else{
                        bzero(buffer,sizeof(buffer));
                        recibidos = recv(i,buffer,sizeof(buffer),0);
                        
                        if(recibidos > 0){
                            result = regexec(&regex_, buffer, 0, NULL, 0);
                            if(strcmp(buffer,"SALIR\n") == 0){
                                salirCliente(i,&readfds,&numUsuarios,arrayUsuarios);
                            }
                                             
                            else if(!result){
                                string option=buffer;
                                option.pop_back();
                                string username=option.substr(option.find(" -u ")+4, option.find("-p"));
                                username=username.substr(0,username.find(" ")); //Almacena el nombre de usuario
                                string password=option.substr(option.find(" -p ")+4, option.length()+1); //Almacena la contraseña

                                if(usuarioRepetido(username, usuariosRegistrados)){
                                    strcpy(buffer, "-Err. El nombre de usuario indicado ya está registrado.\n");
                                    send(i,buffer,sizeof(buffer),0);
                                }

                                else{
                                    Usuario usuario;
                                    usuario.setUsername(username);
                                    usuario.setPassword(password);
                                    usuario.setSd(sd);

                                    registrarUsuario(usuario, usuariosRegistrados);
                                    usuariosRegistrados.push_back(usuario); //Añade el usuario a la base de datos
                                    cout<<"+Ok. Usuario registrado correctamente\n"<<endl;
                                    strcpy(buffer, "+Ok. Usuario registrado correctamente.\n");
                                    send(i,buffer,sizeof(buffer),0);
                                }
                            }
                            
                            else if(strncmp(buffer, "USUARIO ", strlen("USUARIO "))==0){

                                if(strncmp(buffer, "USUARIO \n", strlen("USUARIO \n"))==0){
                                    strcpy(buffer, "-Err. No se ha podido iniciar sesión\n");
                                    send(i, buffer, sizeof(buffer), 0);
                                }

                                else{
                                    string option=buffer;
                                    option.pop_back();
                                    int aux=option.find(" ");
                                    string usuario=option.substr(aux+1,option.length()+1);

                                    if(usuarioRepetido(usuario,usuariosRegistrados)){ //El usuario ya está en el sistema
                                        if(usuarioRegistrado(usuario,usuariosConectados)){
                                            strcpy(buffer,"-Err. El usuario ya se encuentra activo en el sistema.\n");
                                            send(i,buffer,sizeof(buffer),0);
                                        }
                                        
                                        else{
                                            for(int i=0;i<usuariosRegistrados.size();i++){
                                                if(usuariosRegistrados[i].getUsername()==usuario){
                                                    usuariosRegistrados[i].setSd(sd);
                                                }
                                            }
                                            strcpy(buffer,"+Ok. Usuario correcto. Introduzca su contraseña (PASSWORD <contraseña>): \n");
                                            send(i,buffer,sizeof(buffer),0);
                                        }
                                    }

                                    else{
                                        strcpy(buffer, "-Err. Usuario incorrecto.\n");
                                        send(i,buffer,sizeof(buffer),0);
                                    }
                                }
                            }

                            else if(strncmp(buffer, "PASSWORD ", strlen("PASSWORD "))==0){
                                if (strncmp(buffer, "PASSWORD \n", strlen("PASSWORD \n"))==0){
                                    strcpy(buffer, "–Err. Error en la validación.\n");
                                    send(i, buffer, sizeof(buffer), 0);
                                }

                                else{ //Validar usuario activo
                                    bool isLogged=false;
                                    string passwdOption=buffer;
                                    passwdOption.pop_back();
                                    int aux=passwdOption.find(" ");
                                    string password=passwdOption.substr(aux+1, passwdOption.length()+1);

                                    for(int pos=0;pos<usuariosRegistrados.size();pos++){
                                        if((usuariosRegistrados[pos].getPassword()==password) && (usuariosRegistrados[pos].getSd()==sd)){
                                            cout<<"+Ok. Usuario validado en la base de datos.\n";
                                            strcpy(buffer, "+Ok. Usuario validado.\n");
                                            send(i, buffer, sizeof(buffer),0);

                                            Usuario nuevoUsuario=usuariosRegistrados[pos];
                                            nuevoUsuario.setSd(i);
                                            usuariosConectados.push_back(nuevoUsuario);
                                            isLogged=true;
                                            break;
                                        }
                                    }

                                    if(!isLogged){
                                        strcpy(buffer, "–Err. Error de validación.\n");
                                        send(i, buffer, sizeof(buffer), 0);
                                    }
                                }
                            }

                            else if(strncmp(buffer, "INICIAR-PARTIDA",strlen("INICIAR-PARTIDA"))==0){ //Petición para comenzar partida
                                cola.push_back(i);
                                if(cola.size()==2){
                                    Partida p(cola[0],cola[1]);
                                    limpiarTablero(p.tablero);
                                    partidas.push_back(p);

                                    sprintf(buffer, "+Ok. Empieza la partida: %s\n",p.tableroToString(p.tablero).c_str());

                                    if(partidas.size()>9){
                                        strcpy(buffer,"-Err. Demasiadas partidas en curso. Esperando su finalización.\n");
                                        send(i,buffer,sizeof(buffer),0);
                                    }

                                    send(cola[0],buffer,sizeof(buffer),0);
                                    send(cola[1],buffer,sizeof(buffer),0);

                                    strcpy(buffer,"+Ok. Turno de partida.\n");
                                    send(cola[0],buffer,sizeof(buffer),0);
                                    strcpy(buffer,"+Ok. Turno del otro jugador.\n");
                                    send(cola[1],buffer,sizeof(buffer),0);
                                    cola.clear();
                                }

                                else{
                                    strcpy(buffer,"+Ok. Esperando jugadores.\n");
                                    send(i,buffer,sizeof(buffer),0);
                                }
                            }

                            //Implementación del juego
                            else if(strncmp(buffer,"COLOCAR-FICHA ",strlen("COLOCAR-FICHA "))==0){
                                int partidaActual=partida(i,partidas);
                                
                                string option=buffer;
                                option.pop_back();
                                int pos=option.find(" ");
                                string c=option.substr(pos+1,option.length()+1);
                                int columna=stoi(c);
                                columna-=1;

                                if(partidas[partidaActual].getSdJugador1()==i && partidas[partidaActual].getTurn()==true){ //Turno del jugador 1
                                    string winner;
                                    for(int j=0;j<usuariosConectados.size();j++){
                                        if(usuariosConectados[j].getSd()==i){
                                            winner=usuariosConectados[j].getUsername();
                                        }
                                    }

                                    char jugadorActual=partidas[partidaActual].getJugador1();
                                    int estado=partidas[partidaActual].colocarFicha(jugadorActual,columna);

                                    if(estado!=CORRECT && estado==COLUMNA_LLENA){
                                        strcpy(buffer,"-Err. Debe seleccionar otra columna que tenga alguna casilla disponible\n");
                                        send(i,buffer,sizeof(buffer),0);
                                    }

                                    if(estado!=CORRECT && estado==COLUMNA_INVALIDA){
                                        strcpy(buffer,"-Err. Debe seleccionar una columna válida\n");
                                        send(i,buffer,sizeof(buffer),0);
                                    }

                                    if(estado==CORRECT){
                                        string newTab=partidas[partidaActual].tableroToString(partidas[partidaActual].tablero);
                                        sprintf(buffer,"+Ok. Nuevo tablero: %s\n",newTab.c_str());
                                        send(i,buffer,sizeof(buffer),0);
                                        send(partidas[partidaActual].oponente(i),buffer,sizeof(buffer),0);

                                        int win=partidas[partidaActual].ganador(jugadorActual,partidas[partidaActual].tablero);

                                        if(win!=NO_CONECTA){
                                            sprintf(buffer,"+Ok. Victoria del jugador %s\n",winner.c_str());
                                            send(i,buffer,sizeof(buffer),0);
                                            send(partidas[partidaActual].oponente(i),buffer,sizeof(buffer),0);

                                            partidas.erase(partidas.begin()+partidaActual);
                                        }

                                        if(win==NO_CONECTA){
                                            strcpy(buffer,"+Ok. Turno de partida.\n");
                                            send(partidas[partidaActual].oponente(i),buffer,sizeof(buffer),0);
                                            strcpy(buffer,"+Ok. Turno del otro jugador.\n");
                                            send(i,buffer,sizeof(buffer),0);
                                            partidas[partidaActual].setTurn(false);
                                        }

                                        else if(partidas[partidaActual].empate(partidas[partidaActual].tablero)){
                                            strcpy(buffer,"+Ok. Se ha producido un empate en la partida\n");
                                            send(i,buffer,sizeof(buffer),0);
                                            send(partidas[partidaActual].oponente(i),buffer,sizeof(buffer),0);

                                            partidas.erase(partidas.begin()+partidaActual);
                                        }
                                    }
                                }
                                    
                                else if(partidas[partidaActual].getSdJugador2()==i && partidas[partidaActual].getTurn()==false){ //Turno del jugador 2
                                    string winner;
                                    for(int j=0;j<usuariosConectados.size();j++){
                                        if(usuariosConectados[j].getSd()==i){
                                            winner=usuariosConectados[j].getUsername();
                                        }
                                    }

                                    char jugadorActual=partidas[partidaActual].getJugador2();
                                    int estado=partidas[partidaActual].colocarFicha(jugadorActual,columna);

                                    if(estado!=CORRECT && estado==COLUMNA_LLENA){
                                        strcpy(buffer,"-Err. Debe seleccionar otra columna que tenga alguna casilla disponible\n");
                                        send(i,buffer,sizeof(buffer),0);
                                    }

                                    if(estado!=CORRECT && estado==COLUMNA_INVALIDA){
                                        strcpy(buffer,"-Err. Debe seleccionar una columna válida\n");
                                        send(i,buffer,sizeof(buffer),0);
                                    }

                                    if(estado==CORRECT){
                                        string newTab=partidas[partidaActual].tableroToString(partidas[partidaActual].tablero);
                                        sprintf(buffer,"+Ok. Nuevo tablero: %s\n",newTab.c_str());
                                        send(i,buffer,sizeof(buffer),0);
                                        send(partidas[partidaActual].oponente(i),buffer,sizeof(buffer),0);

                                        int win=partidas[partidaActual].ganador(jugadorActual,partidas[partidaActual].tablero);

                                        if(win!=NO_CONECTA){
                                            sprintf(buffer,"+Ok. El jugador %s ha ganado la partida.\n",winner.c_str());
                                            send(i,buffer,sizeof(buffer),0);
                                            send(partidas[partidaActual].oponente(i),buffer,sizeof(buffer),0);

                                            partidas.erase(partidas.begin()+partidaActual);
                                        }

                                        if(win==NO_CONECTA){
                                            strcpy(buffer,"+Ok. Turno de partida.\n");
                                            send(partidas[partidaActual].oponente(i),buffer,sizeof(buffer),0);
                                            strcpy(buffer,"+Ok. Turno del otro jugador.\n");
                                            send(i,buffer,sizeof(buffer),0);
                                            partidas[partidaActual].setTurn(true);
                                        }

                                        else if(partidas[partidaActual].empate(partidas[partidaActual].tablero)){
                                            strcpy(buffer,"+Ok. Se ha producido un empate en la partida\n");
                                            send(i,buffer,sizeof(buffer),0);
                                            send(partidas[partidaActual].oponente(i),buffer,sizeof(buffer),0);

                                            partidas.erase(partidas.begin()+partidaActual);
                                        }
                                    }
                                }

                                else{ //El turno no coincide con el jugador que realiza la petición
                                    strcpy(buffer,"-Err. Debe esperar su turno.\n");
                                    send(i,buffer,sizeof(buffer),0);
                                }
                            }

                            else{ //Comando no aceptado por el servidor                           
                                strcpy(buffer,"-Err. Comando no válido.\n");
                                send(i,buffer,sizeof(buffer),0);
                            }
                        }
                        //Si el cliente introdujo ctrl+c
                        if(recibidos== 0){
                            printf("El socket %d ha introducido ctrl+c\n", i);
                            //Eliminar ese socket
                            salirCliente(i,&readfds,&numUsuarios,arrayUsuarios);
                        }
                    }
                }
            }
        }
    }
    close(sd);
    return 0;
}

//El servidor se desconecta
void manejador(int signum){
    printf("\nApagando el servidor...\n");
    signal(SIGINT,manejador);

    for(j=0;j<numUsuarios;j++){
        bzero(buffer, sizeof(buffer));
        strcpy(buffer, "-Err. Servidor desconectado.\n");
        send(arrayUsuarios[j], buffer, sizeof(buffer), 0);
        close(arrayUsuarios[j]);
        FD_CLR(arrayUsuarios[j], &readfds);
    }

    close(sd);
    exit(-1);
}

//El cliente se desconecta
void salirCliente(int socket, fd_set * readfds, int * numUsuarios, int arrayUsuarios[]){
    char buffer[250];
    int j;

    int partidaActual=partida(i,partidas);
    bzero(buffer,sizeof(buffer));
    printf("Desconexión del cliente: %d\n",socket);
    strcpy(buffer,"+Ok. Usuario desconectado.\n");
    send(i,buffer,sizeof(buffer),0);

    if(partidaActual!=-1){
        strcpy(buffer,"+Ok. Tu oponente ha salido de la partida.\n");
        send(partidas[partidaActual].oponente(i),buffer,sizeof(buffer),0);
    }
    
    close(socket);
    FD_CLR(socket,readfds);
    
    //Re-estructurar el array de usuarios
    for (j = 0; j < (*numUsuarios) - 1; j++){
        if(arrayUsuarios[j] == socket){
            break;
        }
    }
    for(; j < (*numUsuarios) - 1; j++){
        (arrayUsuarios[j] = arrayUsuarios[j+1]);
    }
    (*numUsuarios)--;
    
    for(int j=0;j<usuariosRegistrados.size();j++){
        if(usuariosRegistrados[i].getSd()==sd){
            usuariosRegistrados[i].setSd(-1);
        }
    }

    for(int j=0;j<usuariosConectados.size();j++){
        if(usuariosConectados[i].getSd()==sd){
            usuariosConectados.erase(usuariosConectados.begin()+i);
        }
    }
}