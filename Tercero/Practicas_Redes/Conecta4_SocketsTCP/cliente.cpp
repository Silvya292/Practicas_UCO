#include "./include/cliente.h"
#include "./include/juego.h"

//Cliente que contiene las interfaces de juego y la traducción de los mensajes del servidor
int main(){
    /*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int sd;
	struct sockaddr_in sockname;
	char buffer[250];
	socklen_t len_sockname;
	fd_set readfds, auxfds;
	int salida;
	int fin=0;
	
	/* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
  	sd = socket (AF_INET, SOCK_STREAM, 0);
	if (sd == -1){
		perror("-Err. No se puede abrir el socket cliente.\n");
    		exit (1);	
	}

    /* ------------------------------------------------------------------
		Se rellenan los campos de la estructura con la IP del 
		servidor y el puerto del servicio que solicitamos
	-------------------------------------------------------------------*/
	sockname.sin_family = AF_INET;
	sockname.sin_port = htons(2060);
	sockname.sin_addr.s_addr =  inet_addr("127.0.0.1");

	/* ------------------------------------------------------------------
		Se solicita la conexión con el servidor
	-------------------------------------------------------------------*/
	len_sockname = sizeof(sockname);
	
	if (connect(sd, (struct sockaddr *)&sockname, len_sockname) == -1){
		perror ("-Err. Error de conexión.\n");
		exit(1);
	}

    /* ------------------------------------------------------------------
		Inicializamos las estructuras
	-------------------------------------------------------------------*/
    FD_ZERO(&auxfds);
    FD_ZERO(&readfds);
    
    FD_SET(0,&readfds);
    FD_SET(sd,&readfds);

    start(); //Se imprime la interfaz de comienzo
	do{
		auxfds=readfds;
		salida=select(sd+1,&auxfds, NULL, NULL, NULL);

		if(FD_ISSET(sd,&auxfds)){ //El servidor envía un mensaje
			bzero(buffer,sizeof(buffer));
            recv(sd,buffer,sizeof(buffer),0);

			if(strcmp(buffer, "-Err. Demasiados clientes conectados. Inténtelo de nuevo más tarde.\n")==0 || strcmp(buffer,"-Err. Servidor desconectado.\n")==0){
				fin=1;
			}

			if(strcmp(buffer, "+Ok. Tu oponente ha salido de la partida.\n")==0){
				fin=1;
			}

			if(strcmp(buffer, "+Ok. Usuario validado.\n")==0){
				system("clear");
				gameOptions();
			}

			if(strncmp(buffer, "+Ok. Empieza la partida: -,-,-,-,-,-,-;-,-,-,-,-,-,-;-,-,-,-,-,-,-;-,-,-,-,-,-,-;-,-,-,-,-,-,-;-,-,-,-,-,-,-;\n",strlen("+Ok. Empieza la partida: -,-,-,-,-,-,-;-,-,-,-,-,-,-;-,-,-,-,-,-,-;-,-,-,-,-,-,-;-,-,-,-,-,-,-;-,-,-,-,-,-,-;\n"))==0){
				system("clear");
				gameInterface();
				stringToMatrix(buffer);
			}

			else if(strncmp(buffer, "+Ok. Nuevo tablero: ", strlen("+Ok. Nuevo tablero: "))==0){
				system("clear");
				gameInterface();
				stringToMatrix(buffer);
			}

			else if(strncmp(buffer, "+Ok. Victoria del jugador ",strlen("+Ok. Victoria del jugador "))==0){
				printf("%s",buffer);
				fin=1;
			}

			else if(strncmp(buffer, "+Ok. Se ha producido un empate en la partida\n",strlen("+Ok. Se ha producido un empate en la partida\n"))==0){
				printf("%s",buffer);
				fin=1;
			}

			else{
				printf("%s",buffer);
			}

		}

		else{
			if(FD_ISSET(0,&auxfds)){
				bzero(buffer,sizeof(buffer));
				fgets(buffer,sizeof(buffer),stdin);

                if(strcmp(buffer,"SALIR\n")==0){
                    fin = 1;
                }

				send(sd,buffer,sizeof(buffer),0);
				
			}
		}

	}while(fin==0);
		
	close(sd);
	return 0;
}