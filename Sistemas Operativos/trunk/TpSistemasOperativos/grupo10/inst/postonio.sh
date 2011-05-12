
#------------

#seteo variables 
agenciaMae=$DATADIR"/agencias.mae"
TESPERA=30
# --------------Comandos--------------------
GRALOG=./gralog.sh


# Esta función recibe una secuencia y agencia
# Devuelve 1 si la respuesta es afirmativa y 0 si es negativa
resp=""; # Respuesta que devuelve la funcion
function validarSecuencia(){
	resp="";
	local agencia=$1;
	local secuencia=$2;
	ls $RECEIVED >./temp/DET/archivosValidos.txt
	ls $PROCESSED >>./temp/DET/archivosValidos.txt
	
	encontroAgencia=$(grep -c "$agencia" ./temp/DET/archivosValidos.txt )	
	
	if [ $encontroAgencia -eq 0 ] ;then
		resp=1;
		rm temp/DET/archivosValidos.txt
	else
		aux=`expr $secuencia - 1 `
		n=`printf '%06d' "$aux"`
		encontroAnterior=$(grep -c "$agencia.$n" ./temp/DET/archivosValidos.txt )	
				
		if [ $encontroAnterior -eq 1 ]; then
			resp=1;
			rm temp/DET/archivosValidos.txt
		else
			resp=0;
			rm temp/DET/archivosValidos.txt
		fi
	fi
}

while [ 0 -le 1 ] 

do #principio del loop

if [ ! -d /temp ]; then
	mkdir temp #creo un directorio para archivos temporales si no existe
fi
if [ ! -d ./temp/DET ]; then
	mkdir ./temp/DET
fi


#verifico que haya archivos en ARRIDIR
ls $ARRIDIR > ./temp/DET/archivos.txt
cantidad=$(wc -l < ./temp/DET/archivos.txt)
echo "************************"
echo "cantidad: $cantidad"
echo "************************"
if [ $cantidad -eq 0 ]; then 
	echo "No hay archivos en la carpeta x"
else
	for  i in $(seq 1 $cantidad);
	do
		valido=true
		nombre=$(head -n $i ./temp/DET/archivos.txt | tail -n 1) 
		AUX=`echo $nombre | grep "\b......\.......\b"` #valido formato
		
		echo "***********************************"
		echo "nombre: $nombre"
		echo "aux:  $AUX"
		echo "***********************************"	
				
		if [ -n "$AUX" ]; then
			nomAgencia=$(echo $nombre | cut -d \. -f 1)
			aparece=$(grep $nomAgencia $agenciaMae -c)
			if [ 0 -ne $aparece ];then	#valido que exista la agencia
				secuencia=$(echo $nombre | cut -d \. -f 2)
						
				validarSecuencia  $nomAgencia $secuencia
				if [ $resp -eq 1 ]; then #valido secuencia 
					
					mv "$ARRIDIR/$nombre" $RECEIVED
					$GRALOG postonio I "	El archivo $AUX se ha movido a la carpeta de recibidos" 1 
				else
					$GRALOG postonio A "	El archivo $AUX se ha movido a la carpeta de rechazados, por secuencia no permitida" 1 
					mv "$ARRIDIR/$nombre" $REJECTED
				fi	
			else
				$GRALOG postonio A "	El archivo $AUX se ha movido a la carpeta de rechazados, por codigo de agencia inexistente" 1 
				mv "$ARRIDIR/$nombre" $REJECTED
			fi
		
		else
			$GRALOG postonio A "	El archivo $AUX se ha movido a la carpeta de rechazados, por nombre incorrecto" 1 	
			mv "$ARRIDIR/$nombre" $REJECTED		
		fi
	done
fi

#verifico que haya archivos en RECIBIDOS
ls $RECEIVED > ./temp/DET/recibidos.txt
cantidad=$(wc -l < ./temp/DET/recibidos.txt)
if [ $cantidad -eq 0 ]; then 
	echo "No hay archivos en la carpeta x"
else


pid=$(ps a | grep -v $0 | grep "postular.sh" | grep -v "grep" | head -n1 | head -c5)
	if [ -n "$pid" ];then
		echo "POSTULAR se encuentra corriendo con PID: $pid"
		$GRALOG postonio A "Se llamo a POSTULAR, y ya se encuentra corriendo con PID: $pid"
	else
		./postular.sh & 
		pid=$(ps a | grep -v $0 | grep "postular.sh" | grep -v "grep" | head -n1 | head -c5)
		if [ -n $pid ]; then
			echo "El pid de POSTULAR es: $pid"
			$GRALOG postonio A "Se llamo a POSTULAR, PID: $pid"
			
		else
			echo "ERROR: No se pudo ejecutar postular.sh"
			$GRALOG postonio A "ERROR: No se pudo ejecutar postular."
		fi
	fi

fi


rm ./temp/DET/recibidos.txt
rm ./temp/DET/archivos.txt
rmdir ./temp/DET
rmdir ./temp

#processId=$(echo "$$")
#echo  $proccesId"------------------------------"
sleep "$TESPERA"s

done #termina el loop
