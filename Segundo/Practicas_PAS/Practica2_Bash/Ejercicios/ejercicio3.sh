#!/bin/bash

#Desarrollar un script que reciba como argumento el nombre de un fichero de texto y extraiga cada palabra única que aparezca en ese fichero. 
#Cada palabra se deberá mostrar en una lı́nea diferente y deberán estar ordenadas por orden alfabético. Además de la palabra, en cada lı́nea
#se mostrará el número de orden y la longitud de la palabra. Recuerda realizar los controles de errores oportunos.

if [ $# != 1 ] #Si el nº de argumentos es distinto de 1 devolverá error
then
    echo "Número de parámetros incorrecto"
else
    for word in $(cat $1 | tr '.' ',' | sed 's/,//g' | sed 's/[A-Z]/\L&/g') #Sustituye los . por , elimina las , con sed y pasa todas las may. a min.
    do
        echo -e "$word  ${#word}" #Imprime la palabra y su extensión
    done | sort | uniq | nl #Ordena cada palabra distinta y las enumera
fi

#Para pasar de mayúsculas a minúsculas \L& de minúsculas a mayúsculas \U&
#Para encadenar varios sed puede ser también con -e