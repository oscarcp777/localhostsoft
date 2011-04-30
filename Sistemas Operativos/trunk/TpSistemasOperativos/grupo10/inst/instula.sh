#!/bin/bash
# Directorios de la instalacion

#Funciones generales
function obtenerValor(){
	head -n $1 $CONFIGFILE | tail -1 | sed -e 's/.*=//'
}

# Inicio Programa
#verifico que la variable $GRUPO se haya seteado

if [ -z "$GRUPO" ]; then
	echo "";
	echo 'No se encuentra seteada la variable $GRUPO.'
	echo 'No se puede iniciar la instalación.';
	echo  'Por favor lea el archivo README.txt y vuelva a realizar la instalación';
	echo "";
	exit 1;
else 
	GRUPO10="$GRUPO/grupo10";
fi

if [ ! -e "$GRUPO10/conf/intula.log"]; then
	./gralog.sh instula.log I "Inicio de Intalacion"
else
	# TODO renombrar archivo de log si es q existe y crear el nuevo
fi

if [ ! -e "$GRUPO10/instula.conf"]; then
	echo "El programa ya se encuentra instalado"
	./gralog.sh instula.log I "El programa ya se encuentra instalado"
	echo "Verificando componentes ya instalados del programa..."
	./gralog.sh instula.log I "Verificando componentes ya instalados del programa..."
	echo obtenerValor 23
else
	# TODO renombrar archivo de log si es q existe y crear el nuevo
fi
 