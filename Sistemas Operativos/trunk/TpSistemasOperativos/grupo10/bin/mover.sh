archivoOrigen=${1##*/}
archvioDestino=${2##*/}
directorioOrigen=${1%/*}
directorioDestino=${2%/*}


#Ver con el grupo el path del archivo log 	
log='/home/hlovey/log.txt'

#validamos que la cantidad de parametros sea menor o igual a 3 y mayor o igual a 2
if [ $# -gt 3 -o $# -lt 2 ]
then
	echo "Error en la cantidad de parametros/n" >> $log
	exit 1
fi

#validamos que los directorios origen y destino existan
if [ ! -d "$directorioOrigen" -o ! -e "$archivoOrigen" ]
then
	echo "El directorio o archivo origen no existe" >> $log	
	exit 2
fi
#validamos que el directorio origen axista
if [ ! -d "$directorioDestino" ]
then
	echo "El directorio destino no existe" >> $log
	exit 3
fi
	
#Validamos que en la directorio destino no haya un archivo con el mismo nombre

if [ "$directorioDestino" == "$directorioOrigen" ]
then
	echo "(Movimiento como Duplicado)Directorio origen y destino son iguales" >> $log
fi

if [ -e $directorioDestino/$archvioDestino ]
then
	if [ ! -d $directorioDestino/dup ]
	then
 		mkdir $directorioDestino/dup
	else		
 		 secuencia=$(ls "$directorioDestino/dup" | grep ".*$archvioDestino.[1-9]$" | sort -r | sed s/$archvioDestino.// | head -n 1)
		#Verificamos el numero de secuencia de los archivos 			duplicados
		if [ "$secuencia" == "" ]
		then
			secuencia=1
		else
			secuencia=$(echo $secuencia+1 | bc -l)	
		fi
	fi		
	
	destinoFinal=$directorioDestino/dup/$archvioDestino.$secuencia
else	
	destinoFinal=$directorioDestino/$archvioDestino
fi

echo "Archivo movido de $directorioOrigen/$archivoOrigen a $destinoFinal" >> $log	

echo "----------------------------------------------------------------" >> $log

mv "$directorioOrigen/$archivoOrigen" "$destinoFinal"


