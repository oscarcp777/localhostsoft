#!/bin/bash

# --------------Variables--------------------
# Lista de todos los comandos del paquete
COMANDOS=("postini.sh" "postonio.sh" "postular.sh" "plist.pl" "mover.sh" "gralog.sh")
# --------------Fin Variables--------------------

# --------------Comandos--------------------
GRALOG=./gralog.sh
# --------------Fin Comandos--------------------

# --------------Funciones Generales--------------------

# Esta función recibe un número de linea y devuelve el valor de la variable
# correpondiente del archivo de configuración
function obtenerValor(){
	head -n $1 "$GRUPO/conf/instula.conf" | tail -1 | sed -e 's/.*=//'
}

# Esta función recibe la lista de comandos instalados y los muestra junto con los no instalados
function mostrarEstadoInstalacion(){
	echo "INSTALADOS: " $1
	#echo "NO INSTALADOS: "
	echo "TODOS: " $2
}

# Esta función recibe un comando y una ubicación y instala el mismo
function instalarComando(){
	# Valida que los archivos no esten en el directorio destino
	if [ -e "$2/$1" ]; then
		$GRALOG instula A "	El componente $1 ya se encuentra instalado, el mismo no fue actualizado" 
		echo "	El componente $1 ya se encuentra instalado, el mismo no fue actualizado"
	else
		cp $1 $2
		$GRALOG instula I "	Instalación del componente  $1 completada" 
		echo "	Instalación del componente  $1 completada"
	fi	
}

# --------------Fin Funciones Generales--------------------



# --------------Inicio Programa--------------

# Verifica que la variable $GRUPO se haya seteado
if [ -z "$GRUPO" ]; then
	echo "";
	echo 'No se encuentra seteada la variable $GRUPO.'
	echo 'No se puede iniciar la instalación.';
	echo  'Por favor lea el archivo README.txt y vuelva a realizar la instalación';
	echo "";
	exit 1;
else
	# Si esta seteada le agrega la ruta del grupo 10 
	GRUPO="$GRUPO/grupo10"
fi

# Valida que exista un archivo previo de log de instalación 
if [ -e "$GRUPO/conf/instula.log" ]; then
	# Hay instalación previa
	# Renombra el archivo anterior y crea el nuevo
	echo "TODO - renombrar archivo de log si es q existe y crear el nuevo"
fi

$GRALOG instula I "Inicio de Instalación"
echo "Inicio de Instalación"

# Valida si existe una instalación previa
#if [ ! -e "$GRUPO/instula.conf" ]; then
#	echo "El programa ya se encuentra instalado"
#	$GRALOG instula I "El programa ya se encuentra instalado"
#	echo "Verificando componentes ya instalados del programa..."
#	$GRALOG instula I "Verificando componentes ya instalados del programa..."
#		
#	# Verifica cuales componentes estan instalados y cuales no
#	comandosInstalados=`obtenerValor 23`
#	`mostrarEstadoInstalacion $comandosInstalados $COMANDOS` 
#	$GRALOG instula I "Borrar los componentes instalados y ejecutar el comando nuevamente"
#	echo "Borrar los componentes instalados y ejecutar el comando nuevamente"
#else
#	echo "TODO" # TODO renombrar archivo de log si es q existe y crear el nuevo
#fi


#---------ZONA RICHY---------------




#---------FIN ZONA RICHY---------------


#---------ZONA TIAGO---------------
# Instalación
	# Variable que chequea si estan todos los componentes
	estaCompleto=true
	# Valida que todos los componentes esten disponibles en el directorio de instalación
	for i in ${COMANDOS[*]}; do
		if [ ! -e $GRUPO/inst/$i ]; then
		 	estaCompleto=false
			$GRALOG instula E "El componente $i no se encuentra o está corrupto, no se puede continuar la instalación" 
			echo "El componente $i no se encuentra o está corrupto, no se puede continuar la instalación"
		fi
	done
	if [ $estaCompleto == "true" ]; then
		$GRALOG instula I "Moviendo Archivos..."
		echo "Moviendo Archivos..."
		# Instalando COMANDOS
		for i in ${COMANDOS[*]}; do
			instalarComando $i $GRUPO/bin  #TODO debe estar BINDIR
		done
	fi
	
		


#---------FIN ZONA TIAGO---------------



# --------------Fin Programa--------------
 