#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

void printUser(struct passwd *pw){
    printf("USUARIO:\n");
    printf("→ Nombre: %s\n", pw->pw_gecos);
    printf("→ Login: %s\n", pw->pw_name);
    printf("→ Password: %s\n", pw->pw_passwd);
    printf("→ UID: %d\n", pw->pw_uid);
    printf("→ Home: %s\n", pw->pw_dir);
    printf("→ Shell: %s\n", pw->pw_shell);
    printf("→ Número de grupo principal: %d\n\n", pw->pw_gid);
}

void printGroup(struct group *gr){
    printf("GRUPO:\n");
    printf("→ Nombre del grupo principal: %s\n", gr->gr_name);
    printf("→ GID: %d\n", gr->gr_gid);
    printf("→ Miembros secundarios: %s\n", *gr->gr_mem);   
}

void printHelp(){
    printf("Ejecución del programa: ej1 [opciones]\n");
    printf("OPCIONES:\n");
    printf("→ -u/--user (<nombre>|<uid>) : Información correspondiente a la estructura passwd del usuario indicado. Si el argumento es un número, se interpretará como UID, de lo contrario será el nombre del usuario.\n");
    printf("→ -g/--group (<nombre>|<gid>) : Información correspondiente a la estructura group indicada. Si el argumento es un número, se interpretará como GID, de lo contario será el nombre del grupo.\n");
    printf("→ -a/--active : Equivalente a especificar --user con el usuario actual.\n");
    printf("→ -m/--maingroup : Modifica a --user o a --active, imprimiendo la información de su grupo principal (mismo formato que --group).\n");
    printf("→ -s/--allgroups : Muestra la información de todos los grupos del sistema junto con su identificador.\n");
    printf("→ -h/--help : Mostrar información sobre cada uno de los usos del programa.\n");
}

int main(int argc, char **argv){
    opterr=0;
    int c;
    // Declaracion de las estructuras que almacenarán la informarción de un usuario y de un grupo
    char *lgn;
    int uid;
    char *gname;
    int gid;
    char *name;
    struct passwd *pw;
    struct group *gr;

    /* Estructura a utilizar por getoptlong */
    static struct option long_options[] = {/* Opciones que no van a actuar sobre un flag */
    //  {<nombre largo>, <recibe/no recibe argumento>, NULL, <nombre corto>}
        {"user", required_argument, NULL, 'u'},
        {"group", required_argument, NULL, 'g'},
        {"active", no_argument, NULL, 'a'},
        {"maingroup", no_argument, NULL, 'm'},
        {"allgroups", no_argument, NULL, 's'},
        {"help", no_argument, NULL, 'h'},
        /* Necesario para indicar el final de las opciones */
        {0, 0, 0, 0}
	};

    /* Estas variables servirán para almacenar el resultado de procesar la línea
     * de comandos */
    char *uvalue = NULL;
    char *gvalue = NULL;
    bool aflag = false;
    bool mflag = false;
    bool sflag=false;
    bool hflag=false;

    while ( (c= getopt_long(argc, argv, "u:g:amsh", long_options, NULL)) != -1) {
        switch (c) {
            case 'u':
                uvalue=optarg;
                break;
            case 'g':
                gvalue=optarg;
                break;
            case 'a':
                aflag=true;
                break;
            case 'm':
                mflag=true;
                break;
            case 's':
                sflag=true;
                break;
            case 'h':
                hflag=true;
                break;
        }
    }

    if (argc==1) {
        //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
        if ((lgn = getenv("USER")) == NULL || (pw = getpwnam(lgn)) == NULL) {
            fprintf(stderr, "Fallo al obtener información de usuario.\n");
            exit(-1);
        }
        if((gr=getgrgid(pw->pw_gid))==NULL){
            fprintf(stderr, "Fallo al obtener información del grupo.\n");
            exit(-1);
        }

        printUser(pw);
        printGroup(gr);
        exit(0);
    }

    else{
        if((uvalue != NULL) && (gvalue == NULL) && (!aflag) && (!mflag) && (!sflag) && (!hflag)){ //-u:
            if(isdigit(*uvalue)){
                uid=atoi(uvalue);
                if((pw=getpwuid(uid))==NULL){
                    fprintf(stderr, "Fallo al obtener información de usuario.\n");
                    exit(-1);
                }
            }
            else{
                lgn=uvalue;
                if ((pw = getpwnam(lgn)) == NULL){ //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
                    fprintf(stderr, "Fallo al obtener información de usuario.\n");
                    exit(-1);
                }
            }
            printUser(pw);
            exit(0);
        }

        else if((uvalue == NULL) && (gvalue != NULL) && (!aflag) && (!mflag) && (!sflag) && (!hflag)){ //-g:
            if(isdigit(*gvalue)){
                gid=atoi(gvalue);
                if((gr=getgrgid(gid))==NULL){
                    fprintf(stderr, "Fallo al obtener información de usuario.\n");
                    exit(-1);
                }
            }
            else{
                gname=gvalue;
                if ((gr = getgrnam(gname)) == NULL){ //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
                    fprintf(stderr, "Fallo al obtener información de usuario.\n");
                    exit(-1);
                }
            }
            printGroup(gr);
            exit(0);
        }

        else if((uvalue == NULL) && (gvalue == NULL) && (aflag) && (!mflag) && (!sflag) && (!hflag)){ //-a
            if ((lgn = getenv("USER"))==NULL || (pw = getpwnam(lgn))==NULL){ //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
                fprintf(stderr, "Fallo al obtener información de usuario.\n");
                exit(-1);
            }
            printUser(pw);
            exit(0);
        }

        else if((uvalue != NULL) && (gvalue == NULL) && (!aflag) && (mflag) && (!sflag) && (!hflag)){ //-u: -m
            if(isdigit(*uvalue)){
                uid=atoi(uvalue);
                if((pw=getpwuid(uid))==NULL){
                    fprintf(stderr, "Fallo al obtener información de usuario.\n");
                    exit(-1);
                }
            }
            else{
                lgn=uvalue;
                if ((pw = getpwnam(lgn)) == NULL){ //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
                    fprintf(stderr, "Fallo al obtener información de usuario.\n");
                    exit(-1);
                }
            }
            printUser(pw);
            
            if ((gr = getgrgid(pw->pw_gid)) == NULL){
                fprintf(stderr, "Fallo al obtener información de grupo. Probablemente el grupo que ha introducido no exista\n");
                exit(-1);
            }
            printGroup(gr);
            exit(0);
        }

        else if((uvalue == NULL) && (gvalue == NULL) && (aflag) && (mflag) && (!sflag) && (!hflag)){ //-a -m
            if ((lgn = getenv("USER"))==NULL || (pw = getpwnam(lgn))==NULL){ //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
                fprintf(stderr, "Fallo al obtener información de usuario.\n");
                exit(-1);
            }
            printUser(pw);

            if ((gr = getgrgid(pw->pw_gid)) == NULL){
                fprintf(stderr, "Fallo al obtener información de grupo. Probablemente el grupo que ha introducido no exista\n");
                exit(-1);
            }
            printGroup(gr);
            exit(0);
        }

        else if((uvalue == NULL) && (gvalue == NULL) && (!aflag) && (!mflag) && (sflag) && (!hflag)){ //-s
            int num;
            FILE *f;
            f = fopen("/etc/group", "r");

            if (f == NULL){
                printf("Error al abrir el fichero /etc/group");
                exit(-1);
            }

            char buffer[256];
            char *groupname;
            char *password;
            char *groupid;
            char *groupmembers;
            printf("GRUPOS:\n");
            while (fgets(buffer, 256, f) != NULL){
                groupname = strtok(buffer, ":");
                password = strtok(NULL, ":");
                groupid = strtok(NULL, ":");
                strtok(NULL, ":");
                groupmembers = strtok(NULL, ":");
                printf("→ Nombre del grupo principal: %s\n", groupname);
                printf("→ Contraseña: %s\n", password);
                printf("→ GID: %s\n", groupid);
                printf("→ Miembros secundarios: %s\n\n", groupmembers);
            }
            exit(0);
        }

        else if(hflag){
            printHelp();
            exit(0);
        }

        else{
            printf("ERROR en la llamada al programa.\n");
            printHelp();
            exit(-1);
        }
    }
    exit(0);
}
    
