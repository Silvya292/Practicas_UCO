#!/bin/bash

#Desarrolla un script que, utilizando el comando df, muestre la siguiente información:
#1. Sistemas de ficheros cuyo número de bloques tenga al menos N cifras, donde N es el primer argumento de lı́nea de comandos.
#2. Sistemas de ficheros cuyo porcentaje de uso sea inferior al 10 %.
#3. Sistemas de ficheros cuyo porcentaje de uso sea de al menos el 90 %.

if [ $# != 1 ] #Si el nº de argumentos es distinto de 1 devolverá error
then
    echo "Número de argumentos incorrecto."
else
    echo "1) Sistema de ficheros cuyo número de bloques tenga al menos "$1" cifras:"
    df | grep -Eo "^[^ ]+[ ]+[0-9]{$1}.*" | sort #Fuerza a que se repitan los nºs N veces
    echo -e "\n2) Sistemas de ficheros cuyo porcentaje de uso sea inferior al 10%:"
    df | grep -Eo "^[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+[0-9]{1}%+.*" | sort #Solo del 0% al 9%
    echo -e "\n3) Sistema de ficheros cuyo porcentaje de uso sea de al menos el 90%:"
    df | grep  -Eo "^[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+(9[0-9]{1}%|100%)+.*" | sort #Al menos un 90% o 100%
fi