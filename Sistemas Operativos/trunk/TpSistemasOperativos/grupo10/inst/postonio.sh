
#while read line
#do 
#  agencia=$(echo $line | cut -d , -f 2)
#  echo -e "$agencia".000000
#  echo -e "$agencia".000000 >> ultimasSecuencias.txt
#done < agencias.mae
#-------------viejo

PATH="/home/shadow/workspace/postonio/recibidos"
		archivos=$(ls -1p "$PATH" )
		echo $archivos
# Esta función recibe una secuencia y agencia
# Devuelve 1 si la respuesta es afirmativa y 0 si es negativa
resp=""; # Respuesta que devuelve la funcion
function validarSecuencia(){
	resp="";
	local secuencia=$1;
	local agencia=$2;

	primerAgenciaSecuencia=$(ls -x | grep $agencia ultimasSecuencias.txt | cut -f 1) #busco la primer agencia con menor secuencia
	echo $primerAgenciaSecuencia--------------------------
	secuenciaUltima=$(echo $primerAgenciaSecuencia | cut -d \. -f 2) 
	echo $secuenciaUltima--------------------
 
    aux=`expr $secuenciaUltima + 1 `
	if [ $aux -eq $secuencia ]; then
		resp=1;
		#modificar la linea
	    n=`printf '%06d' "$aux"`
		echo -e sed "s/$primerAgenciaSecuencia/$agencia.$n/" ultimasSecuencias.txt > ultimasSecuencias.txt
		echo secuencia bien
	else
		resp=0;
	fi
}
agenciaMae=agencias.mae
# Esta función recibe una secuencia y agencia
# Devuelve 1 si la respuesta es afirmativa y 0 si es negativa
resp=""; # Respuesta que devuelve la funcion
function validarSecuencia2(){
	resp="";
	local secuencia=$1;
	local agencia=$2;
	encontroAgencia=$(grep $agencia $agenciaMae -c)
	echo $encontroAgencia
	echo validarSec2

	if [ $encontroAgencia -eq 0 ] ;then
		resp=1;
		echo secuencia bien, primera
	else
		aux=`expr $secuencia - 1 `
		n=`printf '%06d' "$aux"`
		echo $agencia.$n----------
		PATH="/home/shadow/workspace/postonio/recibidos"
		archivos=$(ls -1p $PATH | grep -c "$agencia.$n")
		#encontroAnterior=$(grep -c "$agencia.$n" "$PATH") #busco la primer agencia con menor secuencia
		echo $archivos
		echo $encontroAnterior---------------------.--------,,,,
		if [ $encontroAnterior -eq 1 ]; then
			resp=1;
			echo secuencia bien
		else
			resp=0;
			echo secuencia mal
		fi
	fi
}
recibidos=/recibidos;
sec=000001
agencia=AGENC1
validarSecuencia2 $sec $agencia

	if [ $resp = 0 ]; then
		echo secuencia mal validacion2
	else
		echo secuencia ok validacion2
	fi


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
	tempPreexistente=false
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
		AUX=`echo $nombre | grep "\b......\.......\b"` #valida formato
		if [ -n "$AUX" ]; then
			nomAgencia=$(echo $nombre | cut -d \. -f 1)
			echo $nomAgencia
			aparece=$(grep $nomAgencia $agenciaMae -c)
			echo $aparece ---aparece
			if [ 0 -ne $aparece ];then	
				echo ---val1
				secuencia=$(echo $nombre | cut -d \. -f 2)
				#validar secuencia
				echo $secuencia
				if [ 0 -le 1 ]; then #validar secuencia 
					#mover a recibidos, corroborar que se movio
					echo arridir/$nombre
					mv ./arridir/$nombre ./recibidos
					$GRALOG postonio I "	El archivo $AUX se ha movido a la carpeta de recibidos" 1 
				else
					$GRALOG postonio A "	El archivo $AUX se ha movido a la carpeta de rechazados, por secuencia no permitida" 1 
					mv ./arridir/$nombre ./rechazados
				fi	
			else
				$GRALOG postonio A "	El archivo $AUX se ha movido a la carpeta de rechazados, por codigo de agencia inexistente" 1 
				mv ./arridir/$nombre ./rechazados
			fi
		
		else
			$GRALOG postonio A "	El archivo $AUX se ha movido a la carpeta de rechazados, por nombre incorrecto" 1 	
			mv ./arridir/$nombre ./rechazados		
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

if [ ! -d ./temp ]; then
	mkdir temp #creo un directorio para archivos temporales si no existe
	tempPreexistente=false
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
		AUX=`echo $nombre | grep "\b......\.......\b"` #valida formato
		if [ -n "$AUX" ]; then
			nomAgencia=$(echo $nombre | cut -d \. -f 1)
				echo ---val1
				secuencia=$(echo $nombre | cut -d \. -f 2)
				#validar secuencia
				echo $secuencia
				if [ 0 -le 1 ]; then #validar secuencia 
					#mover a recibidos, corroborar que se movio
					echo arridir/$nombre
					mv ./arridir/$nombre ./recibidos
					$GRALOG postonio I "	El archivo $AUX se ha movido a la carpeta de recibidos" 1 
				else
					$GRALOG postonio A "	El archivo $AUX se ha movido a la carpeta de rechazados, por secuencia no permitida" 1 
					mv ./arridir/$nombre ./rechazados
				fi	
		
		else
			$GRALOG postonio A "	El archivo $AUX se ha movido a la carpeta de rechazados, por nombre incorrecto" 1 	
			mv ./arridir/$nombre ./rechazados		
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
