#!/bin/bash

#Desarrollar un script que reciba como parámetros la ruta de un directorio y un número entero N de horas, y liste todos los ficheros 
#que se encuentren dentro de dicho directorio que hayan sido modificados en las N horas anteriores.

if [ $# != 2 ] #Si el nº de argumentos es distinto de 2 devolverá error
then
    echo "Argumentos incorrectos. Uso: ./ejercicio5.sh <ruta_directorio> <num_horas>"
elif [ -d $1 ] #Comprobar si es un directorio
then
    nMin=$(($2 * 60)) #Se calcula el nº de minutos multiplicando las horas insertadas
    for i in $(find $1 -type f -mmin -$nMin) #Imprime los fichero que hayan sido modificados en los últimos nMin
    do
        echo "$($i)"
    done
else
    echo "El directorio insertado no existe"
fi

#Forma alternativa
#ruta=${1}
#nHoras=${2}
#segundos=$(date +%s)
#for i in $(find $ruta -type f -print "%p\n")
#do
#    horas=$(($segundos - $(date +%s -r $i))/3600)
#    if [ $horas -lt $nHoras ]
#    then
#        echo "$i"
#    fi
#done
