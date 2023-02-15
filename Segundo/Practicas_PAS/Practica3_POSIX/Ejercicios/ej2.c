/* Implemente un programa en C usando tuberías similar a los existentes en los ficheros
pipe.c y pipe2.c, pero en este caso que un proceso genere dos números aleatorios flotantes
y envie la suma de ellos al otro proceso para que éste muestre su resultado.
*/

#include <errno.h> //Control de errores
#include <stdio.h>
#include <stdlib.h> //exit, rand, srand
#include <string.h> //strerror
#include <sys/wait.h> //wait
#include <time.h> //Para la semilla del generador de aleatorios
#include <unistd.h> //pipe, close, fork, usleep, read, write, getpid, getppid

int main(){
    pid_t flag;
    int status;
    float n1, n2, suma, resultado;
    int fildes[2];
    const int BSIZE = 100;
    char buf[BSIZE];
    ssize_t nbytes;

    status = pipe(fildes);
    if (status == -1) {
        perror("Error en pipe");
        exit(EXIT_FAILURE);
    }

    switch(fork()){
        case -1: // Ocurrió un error al hacer fork()
            perror("No se ha podido crear el proceso hijo...");
            exit(EXIT_FAILURE);
        
        case 0:
            close(fildes[1]);

            resultado = read(fildes[0], &suma, sizeof(float));
            if (resultado != sizeof(float)) {
                printf("\n[HIJO]: ERROR al leer de la tubería...\n");
                exit(EXIT_FAILURE);
            }

            // Imprimimos el campo que viene en la tubería
            printf("[HIJO]: Leo la suma aleatoria %f de la tubería.\n", suma);

            // Cerrar el extremo que he usado
            printf("[HIJO]: Tubería cerrada ...\n");
            close(fildes[0]);
            break;
        
        default: // El padre escribe en la tubería
            close(fildes[0]);

            srand(time(NULL)); // Semilla de los números aleatorios establecida a la hora actual
            n1=rand()%5000; // Número aleatorio entre 0 y 4999
            n2=rand()%5000; // Número aleatorio entre 0 y 4999
            suma=n1+n2;
            printf("[PADRE]: Número aleatorio %f generado\n", n1);
            printf("[PADRE]: Número aleatorio %f generado.\n", n2);

            // Mandamos el mensaje
            resultado = write(fildes[1], &suma, sizeof(float));
            if (resultado != sizeof(float)) {
                printf("\n[PADRE]: ERROR al escribir en la tubería...\n");
                exit(EXIT_FAILURE);
            }

            // Cerrar el extremo que he usado
            close(fildes[1]);
            printf("[PADRE]: Tubería cerrada...\n");

            //Espera del padre a los hijos
            while ((flag = waitpid(-1, &status, WUNTRACED | WCONTINUED)) > 0) {
                if (WIFEXITED(status)) {
                    printf("Proceso Padre %d, hijo con PID %ld finalizado, status = %d\n", getpid(), (long int)flag, WEXITSTATUS(status));
                } else if (WIFSIGNALED(status)) {
                    printf("Proceso Padre %d, hijo con PID %ld finalizado al recibir la señal %d\n", getpid(), (long int)flag, WTERMSIG(status));
                } else if (WIFSTOPPED(status)) // Para cuando se para un proceso. Con wait() no nos serviria.
                {
                    printf("Proceso Padre %d, hijo con PID %ld parado al recibir la señal %d\n", getpid(), (long int)flag, WSTOPSIG(status));
                } else if (WIFCONTINUED(status)) // Para cuando se reanuda un proceso parado. Con wait() no nos serviria.
                {
                    printf("Proceso Padre %d, hijo con PID %ld reanudado\n", getpid(), (long int)flag);
                }
            }

            if (flag == (pid_t)-1 && errno == ECHILD) {
                printf("Proceso Padre %d, no hay más hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
            } else {
                printf("Error en la invocación de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
                exit(EXIT_FAILURE);
            }
    }       
}