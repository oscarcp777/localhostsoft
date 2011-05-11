# Esta función recibe una secuencia y agencia
# Devuelve 1 si la respuesta es afirmativa y 0 si es negativa
resp=""; # Respuesta que devuelve la funcion
function validarSecuencia(){
	resp="";
	local agencia=$1;
	local secuencia=$2;
	ls $RECIBIDOS >./temp/DET/archivosValidos.txt
	ls $PROCESADOS >>./temp/DET/archivosValidos.txt
	
	encontroAgencia=$(grep -c "$agencia" ./temp/DET/archivosValidos.txt )	
	echo $encontroAgencia

	if [ $encontroAgencia -eq 0 ] ;then
		resp=1;
		rm temp/DET/archivosValidos.txt
	else
		aux=`expr $secuencia - 1 `
		n=`printf '%06d' "$aux"`
		encontroAnterior=$(grep -c "$agencia.$n" ./temp/DET/archivosvalidos.txt )	
		echo $encontroAnterior		
		if [ $encontroAnterior -eq 1 ]; then
			resp=1;
			rm temp/DET/archivosValidos.txt
		else
			resp=0;
			rm temp/DET/archivosValidos.txt
		fi
	fi
}

#------------

#seteo variables 
agenciaMae=agencias.mae
ARRIDIR=./arridir
RECIBIDOS=./recibidos
RECHAZADOS=./rechazados
TESPERA=4000
# --------------Comandos--------------------
GRALOG=./gralog.sh

#creo los directorios 
if [ ! -d $ARRIDIR ]; then
	mkdir $ARRIDIR
fi
if [ ! -d $RECIBIDOS ]; then
	mkdir $RECIBIDOS
fi
if [ ! -d $RECHAZADOS ]; then
	mkdir $RECHAZADOS
fi



if [ ! -d ./temp ]; then
	mkdir temp #creo un directorio para archivos temporales si no existe
fi
if [ ! -d ./temp/DET ]; then
	mkdir ./temp/DET
fi

while [ 0 -le 1 ] 

do #principio del loop

#verifico que haya archivos en ARRIDIR
ls $ARRIDIR >./temp/DET/archivos.txt
cantidad=$(wc -l <./temp/DET/archivos.txt)
if [ $cantidad -eq 0 ]; then 
	echo "No hay archivos en la carpeta x"
else
	for  i in $(seq 1 $cantidad);
	do
		valido=true
		nombre=$(head -n $i ./temp/DET/archivos.txt | tail -n 1) 
		AUX=`echo $nombre | grep "\b......\.......\b"` #valido formato
		if [ -n "$AUX" ]; then
			nomAgencia=$(echo $nombre | cut -d \. -f 1)
			aparece=$(grep $nomAgencia $agenciaMae -c)
			if [ 0 -ne $aparece ];then	#valido que exista la agencia
				secuencia=$(echo $nombre | cut -d \. -f 2)
				validarSecuencia  $nomAgencia $secuencia
				if [ $resp -eq 1 ]; then #valido secuencia 
					echo $ARRIDIR/$nombre
					mv $ARRIDIR/$nombre $RECIBIDOS
					$GRALOG postonio I "	El archivo $AUX se ha movido a la carpeta de recibidos" 1 
				else
					$GRALOG postonio A "	El archivo $AUX se ha movido a la carpeta de rechazados, por secuencia no permitida" 1 
					mv $ARRIDIR/$nombre $RECHAZADOS
				fi	
			else
				$GRALOG postonio A "	El archivo $AUX se ha movido a la carpeta de rechazados, por codigo de agencia inexistente" 1 
				mv $ARRIDIR/$nombre $RECHAZADOS
			fi
		
		else
			$GRALOG postonio A "	El archivo $AUX se ha movido a la carpeta de rechazados, por nombre incorrecto" 1 	
			mv $ARRIDIR/$nombre $RECHAZADOS		
		fi
	done
fi

#verifico que haya archivos en RECIBIDOS
ls $RECIBIDOS >./temp/DET/recibidos.txt
cantidad=$(wc -l <./temp/DET/recibidos.txt)
if [ $cantidad -eq 0 ]; then 
	echo "No hay archivos en la carpeta x"
else

pid=$(obtpid.sh "postular.sh")
	if [ -n "$pid" ];then
		echo "POSTULAR se encuentra corriendo con PID: $pid"
		$GRALOG postonio A "Se llamo a POSTULAR, y ya se encuentra corriendo con PID: $pid"
	else
		postular.sh & 
		pid=$(obtpid.sh "postular.sh")
		if [ -n $(obtpid.sh "postular.sh") ]; then
			echo "El pid de POSTULAR es: $pid"
			$GRALOG postonio A "Se llamo a POSTULAR, PID: $pid"
			
		else
			echo "ERROR: No se pudo ejecutar postular.sh"
			$GRALOG postonio A "ERROR: No se pudo ejecutar postular."
		fi
	fi

fi

rm temp/DET/recibidos.txt
rm temp/DET/archivos.txt
rmdir temp/DET
rmdir temp


sleep "$TESPERA"s

done #termina el loop
