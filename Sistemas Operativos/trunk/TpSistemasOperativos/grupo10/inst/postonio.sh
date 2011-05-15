#!/bin/bash
#!/bin/bash
# Comando "postonio"
# Demonio que verifica la existencia de archivos en la carpeta de arribos, 
# verifica que los codigos de agencia sean validos y que las secuencias sean permitidas,
# si estan correctos, se mueven a la carpeta de recibidos, de lo contrario a la carpeta de rechazados.
# Tambien verifica  que hayan archivos en la carpeta de recibidos y de ser asi, se invoca al comando postular.
# El tiempo de los ciclos se determina en la variable TESPERA
#------------

#seteo variables 
nroCiclo=0
agenciaMae=$DATADIR"/agencias.mae"
TESPERA=30
# --------------Comandos--------------------
GRALOG=./gralog.sh


# Esta función recibe una secuencia y agencia
# Devuelve 1 si la secuencia es correcta y 0 si es incorrecta
resp=""; # Respuesta que devuelve la funcion
function validarSecuencia(){
	resp="";
	local agencia=$1;
	local secuencia=$2;
	ls $RECEIVED >./temp/DET/archivosValidos.txt
	ls $PROCESSED >>./temp/DET/archivosValidos.txt
	
	encontroAgencia=$(grep -c "$agencia" ./temp/DET/archivosValidos.txt )	
	
	if [ $encontroAgencia -eq 0 ] ;then
		if [ $secuencia -ge 1 ]; then 
			resp=1;
			rm temp/DET/archivosValidos.txt
		else
			resp=0;
		fi	
	else
		aux=`expr $secuencia - 1 `
		
		if [ $secuencia -ge 1 ]; then 
			n=`printf '%06d' "$aux"`
			encontroAnterior=$(grep -c "$agencia.$n" ./temp/DET/archivosValidos.txt )	
			encontroActual=$(grep -c "$agencia.$secuencia" ./temp/DET/archivosValidos.txt )
			if [ $encontroAnterior -eq 1 -a $encontroActual -eq 0 ]; then
				resp=1;
				rm temp/DET/archivosValidos.txt
			else
				resp=0;
				rm temp/DET/archivosValidos.txt
			fi
		else
			resp=0;
			rm temp/DET/archivosValidos.txt
		fi
	fi
}

while [ 0 -le 1 ] 

do #principio del loop

$GRALOG postonio I "---------------Comienzo de ciclo: $nroCiclo ---------------" 


if [ ! -d /temp ]; then
	mkdir temp #creo un directorio para archivos temporales si no existe
fi
if [ ! -d ./temp/DET ]; then
	mkdir ./temp/DET
fi


#verifico que haya archivos en ARRIDIR
ls $ARRIDIR > ./temp/DET/archivos.txt
cantidad=$(wc -l < ./temp/DET/archivos.txt)

if [ $cantidad -eq 0 ]; then 
		$GRALOG postonio A "No hay archivos en la carpeta $ARRIDIR" 

else
	for  i in $(seq 1 $cantidad);
	do
		valido=true
		nombre=$(head -n $i ./temp/DET/archivos.txt | tail -n 1) 
		AUX=`echo $nombre | grep "\b......\.[0-9][0-9][0-9][0-9][0-9][0-9]\b"` #valido formato
						
		if [ -n "$AUX" ]; then
			nomAgencia=$(echo $nombre | cut -d \. -f 1)
			aparece=$(grep $nomAgencia $agenciaMae -c)
			if [ 0 -ne $aparece ];then	#valido que exista la agencia
				secuencia=$(echo $nombre | cut -d \. -f 2)
						
				validarSecuencia  $nomAgencia $secuencia
				if [ $resp -eq 1 ]; then #valido secuencia 
					
					./mover.sh "$ARRIDIR/$nombre" "$RECEIVED/$nombre"
					$GRALOG postonio I "	El archivo $nombre se ha movido a la carpeta de recibidos"
				else
					$GRALOG postonio A "	El archivo $nombre se ha movido a la carpeta de rechazados, por secuencia no permitida" 
					./mover.sh "$ARRIDIR/$nombre" "$REJECTED/$nombre"
				fi	
			else
				$GRALOG postonio A "	El archivo $nombre se ha movido a la carpeta de rechazados, por codigo de agencia inexistente" 
				./mover.sh "$ARRIDIR/$nombre" "$REJECTED/$nombre"
			fi
		
		else
			$GRALOG postonio A "	El archivo $nombre se ha movido a la carpeta de rechazados, por nombre incorrecto"
			./mover.sh "$ARRIDIR/$nombre" "$REJECTED/$nombre"		
		fi
	done
fi

#verifico que haya archivos en RECIBIDOS
ls $RECEIVED > ./temp/DET/recibidos.txt
cantidad=$(wc -l < ./temp/DET/recibidos.txt)
if [ $cantidad -eq 0 ]; then 
	$GRALOG postonio A "No hay archivos en la carpeta $RECEIVED"

else


pid=$(ps -A | grep -v $0 | grep "postular.sh" | grep -v "grep" | head -n1 | head -c5)
	if [ -n "$pid" ];then

		$GRALOG postonio A "Se llamo a POSTULAR, y ya se encuentra corriendo con PID: $pid"
	else
		./postular.sh & 
		pid=$(ps -A | grep -v $0 | grep "postular.sh" | grep -v "grep" | head -n1 | head -c5)
		if [ -n $pid ]; then
			$GRALOG postonio A "Se llamo a POSTULAR, PID: $pid"
			
		else
			$GRALOG postonio A "ERROR: No se pudo ejecutar postular."
		fi
	fi

fi


rm ./temp/DET/recibidos.txt
rm ./temp/DET/archivos.txt
rmdir ./temp/DET
rmdir ./temp

$GRALOG postonio I "---------------Fin de ciclo: $nroCiclo ---------------" 
nroCiclo=`expr $nroCiclo + 1 `
sleep "$TESPERA"s

done #termina el loop
