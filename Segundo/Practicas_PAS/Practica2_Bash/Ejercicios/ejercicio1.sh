#!/bin/bash

#Desarrolla un script que muestre el porcentaje de uso de CPU de cada uno de los usuarios que haya conectados en el sistema. 
#Para ello, puedes utilizar la salida del comando ps aux. Ten en cuenta que este comando te proporciona el uso de CPU de cada proceso, 
#por lo que deberás calcular la suma de los procesos de cada usuario. La salida deberá estar ordenada por orden alfabético según el nombre de usuario.

for i in $(ps aux | sed -rne '1!s/^([^ ]+).*/\1/p' | sort | uniq) #Se obtienen cada uno de los usuarios
do
    CPU=0 #Se crea una variable para el % total
    for j in $(ps aux | sed -rne '1!s/^'$i'[ ]+[^ ]+[ ]+([^ ]+).*/\1/p' | sort | uniq) #Se cogen cada uno de los % de uso y se van sumando
    do
        CPU=$(echo "$CPU + $j" | bc) #bc permite que se sumen flotantes
    done
    echo "$i está haciendo un uso de CPU del $j %"
done

#Caracteres especiales: ^=Empareja con el principio de línea  $=Empareja con el final de línea  *=Empareja con 0,1 o más ocurrencias del carácter anterior
#.=Selecciona un carácter cualquiera  ?=Selecciona 1 o ninguna vez lo anterior
#() o \(\)=Permiten agrupar caracteres a la hora de aplicar metacaracteres

#Comando sed: -r=Usa EREs y no BREs  -n=Para imprimir tienes que indicarlo con print  -e 'comando'=Ejecuta el comando especificado  
#!=Empareja con todas las direcciones distintas a la indicada  d=Borrar líneas direccionadas  p=Imprimir líneas direccionadas
#s=Sustituir una expresión por otra sobre las líneas seleccionadas (s/patron/reemplazo/[banderas])→ n(reemplaza la enésima vez) g(reemp. todas) p(fuerza a imprimir)