#!/bin/bash

#Desarrollar un script que reciba 3 argumentos: ruta, número de subdirectorios y longitud de los nombres de los ficheros
#Se creará un directorio principal en la ruta indicada, el nº indicado de subdirectorios con ficheros: .sh .html .key .txt
#Todo con nombres aleatorios
#En el caso de que se indique el nombre de una carpeta que ya existe, se deberá pedir confirmación para eliminarla antes de crear la nueva carpeta.

function getRandomName() {
    tr -dc A-Za-z0-9 < /dev/urandom | head -c $1    #Accede al fichero /dev/urandom, que proporciona caracteres aleatorios de manera infinita, y elimina todos aquellos que no coincidan
                                                    #con A-Za-z0-9. Con head, indicamos que sólo se obtenga el número de caracteres que deseamos.
}

if [ $# != 3 ] #Si el nº de argumentos es distinto de 3 devolverá error
then
    echo "ERROR, número de argumentos incorrecto."
elif [ -d $1 ] #Comprobar si es un directorio
then
    echo "El directorio ya existe. ¿Desea eliminarlo? (s/n)"
    read response #Lee lo insertado por teclado
    if [ $response == "s" ]
    then
        rm -r $1 #Borra el directorio y todo lo que este contenga
        echo "Directorio eliminado."
        echo "Creando nuevo directorio..."
        sleep 1 #Simula la espera de creación
        ./ejercicio1.sh $1 $2 $3 #Vuelve a llamar al ejercicio con los mismos parámetros, asegurándose que ya no existe un directorio con ese nombre
    fi
else
    mkdir $1 #Si no existe, se crea la carpeta con el nombre indicado
    for i in $(seq $2) #se recorren todos los números en secuencia hasta el nº de subdirectorios que hay que crear
    do
        subName="$(getRandomName "$3")" #Se obtiene un nombre aleatorio de subdirectorio
        mkdir $1/$subName #Se crea una carpeta con este nombre dentro de la anterior
        for i in .sh .html .key .txt #Para cada una de las extensiones indicadas se crea un fichero con nombre aleatorio
        do
            fileName="$(getRandomName "$3")"
            touch $1/$subName/$fileName$i #Se crea un fichero vacío con nombre aleatorio
        done
    done
    echo "Directorio creado correctamente"
fi

#$* indica todos los argumentos
#Para el if: -n=(>0)  -z=(==0)  -lt=(<)  -gt=(>)  -le=(<=)  -ge=(>=)  -eq=(==)  -ne=(!=)