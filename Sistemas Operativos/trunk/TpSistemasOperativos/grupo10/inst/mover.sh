#!/bin/bash
#Input 
#-->Parametro1 : Archivo Origen
#-->Parametro2 : Archivo Destino
#-->Parametro3 (opcional) : Comando que lo invoca
#
#Output 
#-->Archivo definido en el parametro 2
#-->Archivo de log

archivoOrigen=${1##*/}
archvioDestino=${2##*/}
directorioOrigen=${1%/*}
directorioDestino=${2%/*}

# --------------Comandos--------------------
GRALOG=./gralog.sh

#validamos que la cantidad de parametros sea menor o igual a 3 y mayor o igual a 2
if [ $# -gt 3 -o $# -lt 2 ]
then
	$GRALOG mover E "Error en la cantidad de parametros/n"
	exit 1
fi

#validamos que los directorios origen y destino existan
if [ ! -d "$directorioOrigen" -o ! -e "$directorioOrigen/$archivoOrigen" ]
then
	$GRALOG mover E "El directorio o archivo origen no existe"	
	exit 0
fi
#validamos que el directorio origen axista
if [ ! -d "$directorioDestino" ]
then
	$GRALOG mover E "El directorio destino no existe"
	exit 0
fi
	
#Validamos que en la directorio destino no haya un archivo con el mismo nombre

if [ "$directorioDestino" == "$directorioOrigen" ]
then
	$GRALOG mover A "(Movimiento como Duplicado)Directorio origen y destino son iguales"
fi

if [ -e $directorioDestino/$archvioDestino ]
then
	if [ ! -d $directorioDestino/dup ]
	then 		
		mkdir $directorioDestino/dup
	        $GRALOG mover A "(Movimiento como Duplicado)Se ha creado el directorio$directorioDestino/dup"
	fi		
 		 secuencia=$(ls "$directorioDestino/dup" | grep ".*$archvioDestino.[1-9]*$" | sort -r | sed s/$archvioDestino.// | head -n 1)
		#Verificamos el numero de secuencia de los archivos 			duplicados
		if [ "$secuencia" == "" ]
		then
			secuencia=1
		else
			secuencia=$(echo $secuencia+1 | bc -l)	
		fi		
	
	destinoFinal=$directorioDestino/dup/$archvioDestino.$secuencia
else	
	destinoFinal=$directorioDestino/$archvioDestino
fi
	
mv "$directorioOrigen/$archivoOrigen" "$destinoFinal"
$GRALOG mover I "Archivo movido de $directorioOrigen/$archivoOrigen a $destinoFinal"

exit 1


