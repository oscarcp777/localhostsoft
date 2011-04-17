#!/bin/bash
#Comando DETECTAR
#
#Input
#	Archivos (cualqesquiera) que arriban al directorio $DATADIR
#	Tabla de Paisas y Sistemas $grupo/conf/p-s.tab
#
#Output
#	Archivos de Practico REcibidos $grupo/$DATADIR/ok/<pais>-<sistema>-<año>-<mes>
#	Archivos (cualesquiera) Rechazados $grupo/$DATADIR/nok/<nombre del archivo>
#	Log $LOGDIR/detectar.log
#
#El comando no recibe parámetros ni tiene opciones
#

#verificar la incializacion del ambiente

#seteo variables 
OKDIR=$GRUPO$DATADIR/ok
NOKDIR=$GRUPO$DATADIR/nok
CONFDIR="/conf/"
#creo los directorios ok y nok si no estan creados
if [ ! -d $OKDIR ]; then
	mkdir $OKDIR
fi
if [ ! -d $NOKDIR ]; then
	mkdir $NOKDIR
fi


# for que controla la cantidad de veces que se va a ejecutar el demonio

for nroLoop in $(seq 1 $CANLOOP) 
do #principio del loop

#inicializo el log
glog.sh "detectar" I "--------------------------Ciclo Nro $nroLoop--------------------------"

#tomo los achivos del directorio DATADIR y verifico su validez

if [ ! -d ./temp ]; then
	mkdir temp #creo un directorio para archivos temporales si no existe
	tempPreexistente=false
fi
if [ ! -d ./temp/DET ]; then
	mkdir ./temp/DET
fi

ls -1p $GRUPO$DATADIR | grep -v /\$ >./temp/DET/archivos.txt #guardo en archivos.txt todos los nombres de archivos que se encuentrean en DATADIR

#hago un primer filtro, todos los archivos que no cumplan con el formato <texto>-<texto>-<texto>-<texto> son mandados a NOKDIR
grep -v "^.\{1,3\}-[0-9]\{1,2\}-[0-9]\{4\}-[0-9]\{1,2\}$" ./temp/DET/archivos.txt >./temp/DET/primerFiltro.txt

#mando a NOKDIR todos los archivos de primerFiltro.txt

cantidad=$(wc -l <./temp/DET/primerFiltro.txt) #cuento cuantos archivos tengo en primerFiltro.txt
for  j in $(seq 1 $cantidad);
do
	nombre=$(head -n $j ./temp/DET/primerFiltro.txt | tail -n 1)
	# deb echo "RECHAZADO: $nombre"
	glog.sh "detectar" E "RECHAZADO: $nombre"
	mover.sh "$GRUPO$DATADIR/$nombre" "$NOKDIR" "detectar"
done

ls -1p $GRUPO$DATADIR | grep -v /\$ >./temp/DET/archivos.txt #con el primer filtro aplicado vuelvo a leer los archivos de DATADIR
cantidad=$(wc -l <./temp/DET/archivos.txt) #cuento cuantos archivos tengo en DATADIR
pstab=$GRUPO$CONFDIR/"p-s.tab" #tomo el p-s.tab

for  i in $(seq 1 $cantidad);
do
	valido=true
	nombre=$(head -n $i ./temp/DET/archivos.txt | tail -n 1) # tomo un nombre de archivo de archivos.txt
	nuevoNombre=$(echo $nombre | tr "[:lower:]" "[:upper:]")
	if [ "$nombre" != "$nuevoNombre" ]; then
		mv "$GRUPO$DATADIR/$nombre" "$GRUPO$DATADIR/$nuevoNombre" # paso los nombres a lower case
	fi
	nombre=$nuevoNombre
	#separo los 4 campos del nombre

	pais=$(echo $nombre | cut -d \- -f 1)
	sistema=$(echo $nombre | cut -d \- -f 2)
	anio=$(echo $nombre | cut -d \- -f 3)
	mes=$(echo $nombre | cut -d \- -f 4)

	#comienzo la validacion	

	if [ $anio -lt 2000 -o $anio -gt $(date +%Y) ]; then # invalido si el año no va de 2000 al actual
		valido=false
	elif [ $mes -lt 1 -o $mes -gt 12 ]; then # invaildo si el mes no esta entre los numeros 1 y 12
		valido=false
	elif [ $anio -eq $(date +%Y) -a $mes -gt $(date +%m) ]; then # invalido si el mes no es menor o igual al actual si el año es el actual
		valido=false
	elif [ $(grep "^$pais-[a-zA-Z]*-$sistema-" $pstab -c -i) -eq 0 ]; then # invalido si el pais y el sistema no se encuentran en p-s.tab (may o min)
		valido=false
	fi

	#si es invalido lo rechazo y lo mando a NOKDIR, de lo contrario lo recibo en OKDIR	

	if [ "$valido" == "false" ]; then
		# deb echo "RECHAZADO: $nombre"
		glog.sh "detectar" E "RECHAZADO: $nombre"
		mover.sh "$GRUPO$DATADIR/$nombre" "$NOKDIR" "detectar"	#inicializo el log
	else
		# deb echo "RECIBIDO: $nombre"
		glog.sh "detectar" I "RECIBIDO: $nombre"
		mover.sh "$GRUPO$DATADIR/$nombre" "$OKDIR" "detectar"			
	fi
done

#verifico que haya archivos en OKDIR
ls $OKDIR >./temp/DET/archivos.txt
cantidad=$(wc -l <./temp/DET/archivos.txt)
if [ $cantidad -eq 0 ]; then #si no hay ningun archivo que mandar al inteprete pasa al siguiente ciclo despues de TESPERA minutos
	echo "No hay archivos que mandar al interprete."
	glog.sh "detectar" I "No hay archivos que mandar al interprete."
else
	pid=$(obtpid.sh "interprete.sh")
	if [ -n "$pid" ];then
		echo "INTERPRETE esta corriendo"
		glog.sh "detectar" I "INTERPRETE esta corriendo"
	else
		interprete.sh & #llamo al interprete para que corra separado del detectar.sh
		pid=$(obtpid.sh "interprete.sh")
		if [ -n $(obtpid.sh "interprete.sh") ]; then
			echo "El process id del interprete es: $pid"
			glog.sh "detectar" I "Se llamo al INTERPRETE. Su process id es: $pid"
		else
			echo "Error al ejecutar interprete.sh"
			glog.sh "detectar" E "Error al ejecutar interprete.sh"
		fi
	fi
fi

# elimino archivos y directorios temporales

rm ./temp/DET/primerFiltro.txt
rm ./temp/DET/archivos.txt
rmdir ./temp/DET
if [ "$tempPreexistente" == "false" ]; then
	rmdir ./temp
fi

#finalizo el log

glog.sh "detectar" I "--------------------------Fin del ciclo $nroLoop--------------------------"

#duermo a detectar.sh TESPERA minutos

sleep "$TESPERA"m

done #fin del loop

