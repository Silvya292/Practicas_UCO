#!/bin/bash

#Desarrolla un script que permita listar todos los ficheros de un directorio sin mostrar los sub-directorios pero incluyendo 
#los ficheros que estos puedan contener. El nombre del fichero deberá mostrar sin su ruta, solo incluyendo el nombre. 
#Además, se deberá añadir un número que indicará el orden de cada fichero y también otro número que indicará el número de caracteres del mismo

if [ $# != 1 ] #Si el nº de argumentos es distinto de 1 devolverá error
then
    echo "ERROR, número de argumentos incorrecto."
elif [ -d $1 ] #Comprobar si es un directorio
then
    for i in $(ls $1) #Se lista el directorio
    do
        for j in $(ls $1$i) #Se listan los subdirectorios
        do
            echo -e "$j  \t ${#j}"  #Se listan cada uno de los ficheros y se escribe la longitud de su nombre, de la variable.
                                    #Para saber el número de caracteres de un fichero sería con wc
        done
    done | nl #Se enumeran todos los ficheros
else
    echo "El directorio insertado no existe"
fi

#Forma alternativa
#for i in $(find ${1} -type f(o también d) -printf "%f\n")
#do
#    echo -e "$i  \t ${#i}"
#done | sort -k2 -n | nl #Ordena por la columna k=2 y -n es para indicar que son nºs