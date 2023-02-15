#!/bin/bash

#Desarrolla un script que permita realizar una copia de seguridad de un determinado directorio y almacenarla en un fichero comprimido. 
#El programa deberá recibir dos argumentos:
##1. Directorio que se va a copiar.
##2. Directorio donde se almacenará la copia comprimida.
#El nombre del fichero de copia resultante deberá seguir el formato: nombredirectoriooriginal_AñoMesDia.tar.gz

if [ $# != 2 ] #Si el nº de argumentos es distinto de 2 devolverá error
then
    echo "Argumentos incorrectos. Uso: ./ejercicio3.sh <directorio_origen> <directorio_destino>."
elif [ -d $1 ] #Comprobar si es un directorio
then
    fecha=$(date +"%Y%m%d") #Se guarda la fecha en una variable de la forma AñoMesDía
    nameZip=$1_$fecha.tar.gz #Se crea el nombre del comprimido
    if [ -d $2 ] #Comprobar si es un directorio el destino
    then
        if [ -f $2/$nameZip ]   #Comprueba si ya existe un fichero con el mismo nombre
        then
            echo "Ya se ha realizado esta copia hoy ($2/$nameZip)"
        else
            tar -czf $nameZip $1/*  #Comprime el directorio y todo su contenido. 
                                    #Comando tar: c=crear un nuevo archivo .tar  v=mostrar descripción del progreso  f=nombre del archivo  z=compresión gzip
            mv $nameZip $2/ #Mueve el comprimido al directorio destino
            echo -e "Copia realizada en $2/$nameZip"
        fi
    else #Si no existe el directorio destino
        echo -e "Creando directorio de destino..."
        mkdir $2 #Se crea el directorio
        tar -czf $nameZip $1/* #Se comprime
        mv $nameZip $2/ #Se mueve el comprimido
        echo "Copia realizada en $2/$nameZip"
    fi
else
    echo "El directorio insertado no existe"
fi

#Eliminar /
#if [ "${arg1: -1}" == '/' ]
#then
#    arg1=${arg1%?}
#fi


