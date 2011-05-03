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

# Esta función recibe un comando y una ubicación e instala el mismo
function instalarComando(){
	# Valida que los archivos no esten en el directorio destino
	if [ -e "$2/$1" ]; then
		$GRALOG instula A "	El componente $1 ya se encuentra instalado, el mismo no fue actualizado" 1 
	else
		cp $1 $2
		$GRALOG instula I "	Instalación del componente  $1 completada" 1	
	fi	
}

# Esta función recibe una pregunta y valida su respuesta, siendo los valores posibles SI y NO
# Devuelve 1 si la respuesta es afirmativa y 0 si es negativa
respSINO=""; # Respuesta que devuelve la funcion
function pregSINO(){
	respSINO="";
	local pregunta=$1;
	local respVal="";
	
	while [ -z $respVal ]	# Mientras no responda si o no
	do 
		read -p "$pregunta SI - NO: " resp; # Lee la respuesta y la guarda en $resp
		respVal=$(echo $resp | grep '^[Ss][Ii]$\|^[Nn][Oo]$'); # Valido que la respuesta sea si o no

	done
	# Transforma la respuesta a minuscula
	resp=$(echo $respVal | sed 's/^[Ss][Ii]$/si/');
	
	# Transforma la respuesta en un numero
	if [ $resp = "si" ]; then
		respSINO=1;
	else
		respSINO=0;
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

$GRALOG instula I "Inicio de Instalación" 1
#echo "Inicio de Instalación"

# Valida si existe una instalación previa
if [ ! -e "$GRUPO/instula.conf" ]; then
	$GRALOG instula I "El programa ya se encuentra instalado" 1
	$GRALOG instula I "Verificando componentes ya instalados del programa..." 1
		
	# Verifica cuales componentes estan instalados y cuales no
	comandosInstalados=`obtenerValor 23`
	mostrarEstadoInstalacion $comandosInstalados
	$GRALOG instula I "Borrar los componentes instalados y ejecutar el comando nuevamente" 1
	#exit 1; TODO Descomentar al finalizar comando
else
	echo "TODO" # TODO renombrar archivo de log si es q existe y crear el nuevo
fi



#---------ZONA RICHY---------------
	# Consulta al usuario si esta de acuerdo con los terminos y condiciones de la instalacion
	$GRALOG instula I "Mostrando mensaje de Aceptacion de terminos y condiciones...";

	
		
echo '**************************************************************
* Proceso de Instalación del sistema Postulantes             *
*          Copyright TPSistemasOp (c)2011                    *
**************************************************************
* Al instalar POSTULA UD. expresa estar en un todo de acuerdo* 
* con los términos y condiciones del "ACUERDO DE LICENCIA DE *
* SOFTWARE" incluido en este paquete.                        *
**************************************************************';

	pregSINO "Acepta?"
	# Si el usuario no acepta finaliza el script
	if [ $respSINO = 0 ]; then
		$GRALOG instula I  "Usuario NO acepto ACUERDO DE LICENCIA DE SOFTWARE: Instalación Cancelada";
		exit 2;
	fi
	
	# Usuario Acepto los terminos
	$GRALOG instula I  "Usuario acepto ACUERDO DE LICENCIA DE SOFTWARE";

	# Verifica la instalacion de perl
	$GRALOG instula I "Verificando versión de Perl instalada...." 1
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
		$GRALOG instula E $msgPerl;
		exit 3;
	else
		#echo "PERL instalado. Version:$PERLV";
		$GRALOG instula I "PERL instalado. Version:$PERLV" 1
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

# Mostrar estructura de directorios y parámetros configurados

	clear
echo "**************************************************************************************************
* Parámetros de Instalación del paquete POSTULA		     *	
**************************************************************************************************
 Directorio de trabajo: $GRUPO
 Directorio de instalación: $GRUPO/inst
 Directorio de configuración: $GRUPO/conf
 Directorio de datos: $GRUPO/data
 Librería de ejecutables: $BINDIR
 Directorio de arribos: $ARRIDIR
 Espacio mínimo reservado en $ARRIDIR: $DATASIZE Mb
 Directorio para los archivos de Log: $LOGDIR
 Extensión para los archivos de Log: $LOGEXT
 Tamaño máximo para cada archivo de Log: $LOGSIZE Kb
 Log de la instalación: $GRUPO/conf/instula.log

 Si los datos ingresados son correctos oprima sólo ENTER para iniciar la instalación.
 Si desea modificar alguno de ellos oprima cualquier tecla.
**************************************************************************************************"

	read -n1 algo
	if [ ! -z $algo ]; then
		echo ""
		echo "Vuelve al paso 2"
	else
		echo "Sigue"
	fi

# Confirmación Inicio Instalación
	$GRALOG instula I "Mostrando mensaje de Confirmación de la Instalación"
	pregSINO "Iniciando Instalación... Está UD. seguro?"
	# Si el usuario no acepta finaliza el script
	if [ $respSINO = 0 ]; then
		$GRALOG instula I  "Usuario No Confirma la Instalación: Instalación Cancelada";
		exit 2;
	fi
	
	# Usuario Acepto los terminos
	$GRALOG instula I  "Usuario acepto Confirmación de Instalación";
	


#######variables de prueba, se borran cuando esten los datos pedidos al usuario#############
BINDIR=/binTest
ARRIDIR=/recibidosTest
LOGDIR=/logTest
PROCESSED=/procesadosTest
NEW=/nuevosTest
LIST=/listaTest

#######fin variables de prueba, se borran cuando esten los datos pedidos al usuario#############
 
# Creación estructura de Directorios definida
	$GRALOG instula I "Creando Estructuras de Directorio......" 1
	
	DIRECTORIOS=( $BINDIR $ARRIDIR $LOGDIR $PROCESSED $NEW $LIST);
	for i in ${DIRECTORIOS[*]}; do
		# Crea los directorios
		if [ ! -e "$GRUPO/$i" ] 
		then
			mkdir  "$GRUPO$i" 
			$GRALOG instula I "	Se creo el directorio $GRUPO$i" 1 
		else
			$GRALOG instula I "	El directorio $GRUPO$i ya existe" 1
		fi
	done

# Instalación
	# Variable que chequea si estan todos los componentes
	estaCompleto=true
	# Valida que todos los componentes esten disponibles en el directorio de instalación
	for i in ${COMANDOS[*]}; do
		if [ ! -e $GRUPO/inst/$i ]; then
		 	estaCompleto=false
			$GRALOG instula E "El componente $i no se encuentra o está corrupto, no se puede continuar la instalación" 1 
		fi
	done
	if [ $estaCompleto == "true" ]; then
		$GRALOG instula I "Moviendo Archivos..." 1
		# Instalando COMANDOS
		for i in ${COMANDOS[*]}; do
			instalarComando $i $GRUPO/bin  #TODO debe estar BINDIR
		done
	fi
	
		


#---------FIN ZONA TIAGO---------------



# --------------Fin Programa--------------
 
