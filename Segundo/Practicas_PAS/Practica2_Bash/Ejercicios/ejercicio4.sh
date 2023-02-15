#!/bin/bash

#Crea un script que acceda al fichero /etc/passwd y muestre:
#1. Usuarios que pertenezcan al grupo con GID 46.
#2. Usuarios que pertenezcan a los grupos con GID 33, 34 o 38.
#3. Usuarios con UID de 4 dı́gitos.
#4. Usuarios con nombre de 4 caracteres.

echo "1) Usuarios del grupo 46:"
cat /etc/passwd | grep -E "^[^ ]+:[^ ]+:[^ ]+:46" | sort #El grupo es el 4º elemento y solo selecciona los del 46

echo -e "\n2) Usuarios de los grupos 33,34 o 38:"
cat /etc/passwd | grep -E "^[^ ]+:[^ ]+:[^ ]+:(33|34|38)" | sort

echo -e "\n3) Usuarios con un UID de 4 digitos:"
cat /etc/passwd | grep -E "^[^ ]+:[^ ]+:[0-9]{4}:" | sort #Selecciona a todos aquellos que tengan un nº del 0 al 9 cuatro veces

echo -e "\n4) Usuarios con nombres de 4 caracteres:"
cat /etc/passwd | grep -E "^[^ :]{4,4}:" | sort

#Comando grep: Se utiliza con -E o se pone egrep
#-i=Considera igual mayúsculas y minúsculas  -o=Solo muestra el emparejamiento y no las líneas  -v=Muestra las líneas que no cumplen el patrón
#-h=Elimina el prefijo del nombre del archivo -r o -R=Búsquedas recurrentes  -w=Búsqueda de la palabra exacta

#echo "1) Usuarios del grupo 46:"
#while IFS=: read -r f1 f2 f3 f4 f5 f6 f7
#do
#    if [[ $f4 == "46" ]]
#    then
#        echo "$f1:$f2:$f3:$f4:$f5:$f6:$f7"
#    fi
#done < /etc/passwd
#
#echo "2) Usuarios de los grupos 33, 34 o 38:"
#while IFS=: read -r f1 f2 f3 f4 f5 f6 f7
#do
#    if [[ $f4 == "33" ]] || [[ $f4 == "34" ]] || [[ $f4 == "38" ]]
#    then
#        echo "$f1:$f2:$f3:$f4:$f5:$f6:$f7"
#    fi
#done < /etc/passwd