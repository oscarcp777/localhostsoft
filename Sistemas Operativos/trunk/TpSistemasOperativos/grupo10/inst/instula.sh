#!/bin/bash

# --------------Variables--------------------
# Lista de todos los comandos del paquete
COMANDOS=("postini.sh" "postonio.sh" "postular.sh" "plist" "mover.sh" "gralog.sh")
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

# Esta función recibe un comando y la ubicación donde quiere instalarse el mismo
function instalarComando(){
	 
	$GRALOG instula.log I "		Instalación del componente  $1 completada" 
	echo "		Instalación del componente  $1 completada"
		
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
if [ ! -e "$GRUPO/conf/instula.log" ]; then
	# No hay instalación previa
	$GRALOG instula I "Inicio de Intalacion"
	echo "Inicio de Intalacion"
else
	# Renombra el archivo anterior y crea el nuevo
	echo "TODO - renombrar archivo de log si es q existe y crear el nuevo" 
fi

# Valida si existe una instalación previa
if [ ! -e "$GRUPO/instula.conf" ]; then
	echo "El programa ya se encuentra instalado"
	$GRALOG instula.log I "El programa ya se encuentra instalado"
	echo "Verificando componentes ya instalados del programa..."
	$GRALOG instula.log I "Verificando componentes ya instalados del programa..."
		
	# Verifica cuales componentes estan instalados y cuales no
	comandosInstalados=`obtenerValor 23`
	`mostrarEstadoInstalacion $comandosInstalados $COMANDOS` 
	$GRALOG instula.log I "Borrar los componentes instalados y ejecutar el comando nuevamente"
	echo "Borrar los componentes instalados y ejecutar el comando nuevamente"
else
	echo "TODO" # TODO renombrar archivo de log si es q existe y crear el nuevo
fi


#---------ZONA RICHY---------------




#---------FIN ZONA RICHY---------------


#---------ZONA TIAGO---------------
# Instalación
$GRALOG instula.log I "Moviendo Archivos..."
echo "Moviendo Archivos..."
	# Instalando POSTINI
	instalarComando "postini.sh" $BINDIR	


#---------FIN ZONA TIAGO---------------



# --------------Fin Programa--------------
 