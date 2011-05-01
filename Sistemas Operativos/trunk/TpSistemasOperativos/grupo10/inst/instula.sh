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

	#comparo las cadenas	
	contador=0;
	#while [ $contador -lt ${#COMANDOS} ]; do
		#var1= echo $1 | cut -d ',' -f `expr $contador + 1`
	#	echo ${COMANDOS[$contador]}
	#contador=`expr $contador + 1`
	#done
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
if [ ! -e "$GRUPO/instula.conf" ]; then
	echo "El programa ya se encuentra instalado"
	$GRALOG instula.log I "El programa ya se encuentra instalado"
	echo "Verificando componentes ya instalados del programa..."
	$GRALOG instula.log I "Verificando componentes ya instalados del programa..."
		
	# Verifica cuales componentes estan instalados y cuales no
	comandosInstalados=`obtenerValor 23`
	mostrarEstadoInstalacion $comandosInstalados
	$GRALOG instula.log I "Borrar los componentes instalados y ejecutar el comando nuevamente"
	echo "Borrar los componentes instalados y ejecutar el comando nuevamente"
else
	echo "TODO" # TODO renombrar archivo de log si es q existe y crear el nuevo
fi



#---------ZONA RICHY---------------
	# Consulta al usuario si esta de acuerdo con los terminos y condiciones de la instalacion
	$GRALOG instula.log I "Mostrando mensaje de Aceptacion de terminos y condiciones...";

	respVal="";
	while [ -z $respVal ]	# mientras no responda si o no
	do
		clear;
		
echo '**************************************************************
* Proceso de Instalación del sistema Postulantes             *
*          Copyright TPSistemasOp (c)2011                    *
**************************************************************
* Al instalar POSTULA UD. expresa estar en un todo de acuerdo* 
* con los términos y condiciones del "ACUERDO DE LICENCIA DE *
* SOFTWARE" incluido en este paquete.                        *
**************************************************************';

		read -p "Acepta? SI - NO: " resp; #leo la respuesta y la guardo en $resp

		respVal=$(echo $resp | grep '^[Ss][Ii]$\|^[Nn][Oo]$'); #valido la respuesta 

	done

	# transformo la respuesta a minuscula
	respVal=$(echo $respVal | sed 's/^[Nn][Oo]$/no/');

	# si el usuario no acepta finalizo el script
	if [ $respVal = "no" ]; then
		$GRALOG instula.log I  "Usuario NO acepto ACUERDO DE LICENCIA DE SOFTWARE";
		exit 2;
	fi
	
	# Usuario Acepto los terminos
	$GRALOG instula.log I  "Usuario acepto ACUERDO DE LICENCIA DE SOFTWARE";

	# Verifica la instalacion de perl
	$GRALOG instula.log I "Verificando versión de Perl instalada....";
	echo "Verificando versión de Perl instalada....";
    PERLV=$(perl -v | grep 'v[0-9]\.[0-9]\+\.[0-9]*' -o); # obtengo la version de perl
	numPERLV=$(echo $PERLV | cut -d"." -f1 | sed 's/^v\([0-9]\)$/\1/'); #obtengo el primer numero

	#si perlv no existe o es menor a 5 mando error
	if [ -z "$numPERLV" ] || [ $numPERLV -lt 5 ] ; then
		msgPerl="**************************************************************
				 * Para instalar POSTULA es necesario contar previamente con  *
				 * Perl 5 o superior instalado.                               *
				 * Efectúe su instalación e inténtelo nuevamente              *
				 **************************************************************
				 Proceso de Instalación Cancelado"
		echo -e $msgPerl;
		$GRALOG instula.log E $msgPerl;
		exit 3;
	else
		echo "PERL instalado. Version:$PERLV";
		$GRALOG instula.log I "PERL instalado. Version:$PERLV";
	fi
	

echo "Todos los directorios del sistema de postulantes serán subdirectorios de:" 
echo $GRUPO

echo "Todos los componentes de la instalación se obtendrán del repositorio:" 
echo $GRUPO"/inst"
echo "Contenido del directorio:"
ls $GRUPO/inst 

echo "El archivo de configuración y el log de la instalación se registrarán en:" 
echo $GRUPO"/conf"


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
 