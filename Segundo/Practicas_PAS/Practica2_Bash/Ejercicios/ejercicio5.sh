#!/bin/bash

#Crea un script que muestre la siguiente información obtenida a partir del fichero /etc/group:
#1. Grupos que contengan al menos 1 usuario además del usuario principal del grupo.
#2. Grupos cuyo nombre empiece por u y acabe en s.
#3. Grupos que no contengan ningún usuario adicional.
#4. Grupos con GID menor que 100.

echo "1) Grupos que contengan al menos 1 usuario además del usuario principal del grupo:"
cat /etc/group | grep -E '^[^ ]+:[^ ]+:[^ ]+:[^ ]+:.*$' | sort #Fuerza a que haya más de uno y solo muestras el grupo

echo -e "\n2) Grupos cuyo nombre empiece por u y acabe en s:"
cat /etc/group | grep -E '^u.*s:[^_]:.*$' #Fuerza el primer y el último carácter

echo -e "\n3) Grupos que no contengan ningún usuario adicional:"
cat /etc/group | grep -E '^[^ ]+:[^ ]+:[^ ]+:$' | sort #Fuerza a que no haya más un usuario

echo -e "\n4) Grupos con GID menos que 100:"
cat /etc/group | grep -E '^[^ ]+:[^ ]+:[0-9]{2}:.*$' | sort #Fuerza a que el GID sea menor a 100

#Para que sea de 90 a 100 sería (9[0-9]|100)
