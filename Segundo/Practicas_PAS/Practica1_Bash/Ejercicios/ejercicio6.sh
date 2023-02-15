#!/bin/bash

#Desarrolla un script que simule la creación de nuevos usuarios.
#El sistema constará de un fichero (por ejemplo users.txt) que almacenará los usuarios existentes. Por otro lado, cada usuario tendrá su home 
#dentro de un directorio (por ejemplo dentro de ./homes). Además, habrá un directorio que contendrá los ficheros por defecto que se añaden
#al home de un usuario al crearlo (por ejemplo ./skel).
#Dentro de nuestro script deberemos implementar una función crear usuario que se encargue de añadir un nuevo usuario al sistema con el nombre indicado 
#en su primer argumento. Al crearlo, lo añadirá al fichero de texto, le creará su home y meterá los archivos por defecto que se encuentren en el 
#directorio skel. Si se intenta crear un usuario que ya existe, no deberá volver a crearlo.
#Una vez creada dicha función, el script deberá llamarla utilizando como nombre el primer argumento con el que se invoque el script.

function crear_usuario() { #Función para crear usuarios
    while IFS= read -r user #Variable de entorno que determina la separación entre los campos internos, en este caso con un =
                            #Mientras haya usuarios los lee
    do
        if [[ "$user" == $1 ]] #Si el usuario ya existe sale
        then
            echo "El usuario indicado ya existe en el sistema"
            exit
        fi
    done < users.txt #Esto lo hace en el fichero users.txt
    echo "$1" >> users.txt #Imprime sin sobreescribir en el fichero users.txt si no existe
    mkdir homes/$1 #Crea una carpeta con el nombre del usuario en el directorio homes
    cp skel/* homes/$1 #Copia todo lo del directorio skel en la carpeta creada
    echo "Se ha creado el usuario $1"
}

if [ $# != 1 ]
then
    echo "ERROR, número de argumentos incorrecto."
else
    crear_usuario "$1" #Se llama a la función con la primera variable insertada por línea de comandos
fi