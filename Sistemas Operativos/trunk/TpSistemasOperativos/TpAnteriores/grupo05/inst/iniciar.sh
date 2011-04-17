#!/bin/bash
#Comando INICIAR
#
#Input
#  Se consultara al llamar al comando los valores de ciertas variables, que se ingresaran directamente en la consola.
#  Variables a consultar:
#     CANLOOP : cantidad de ciclos que sera llamado el comando DETECTAR.
#     TESPERA : tiempo entre ciclos.
#
#Output
#  Devuelve 0 si el programa se pudo iniciar correctamente.
#  Devuelve 1 si el programa no se encontraba instalado correctamente, o fue llamado con la cantidad de parametros incorrecto.
#
#Descripcion
#Este comando debe ser el primero en orden de ejecución. Se dispara manualmente.
#El propósito de este comando es preparar el entorno de ejecución del TP (ambiente). Debe efectuar el seteo
#inicial de las variables de ambiente y debe ofrecer arrancar automáticamente al comando DETECTAR
#siempre que DETECTAR no se esté ejecutando.

export GRUPO=""

#VARIABLE QUE MODIFICA EL INSTALADOR. NO TOCAR.
#GRUPO="ESTA RUTA LA MODIFICA EL INSTALADOR. NO TOCAR!"
CONFIGFILE="$GRUPO/conf/practico.conf";

detectar="detectar.sh"
interpretar="interprete.sh"
reporte="reporte.pl"
logger="glog.sh"

function parsearValor() {
	head -n $1 $CONFIGFILE | tail -n1 | sed -e "s/.*=//" -e "s/^ *//"
}

respVal=""; #respuesta que devuelve la funcion
function pregUsuario(){
	local pregunta=$1;
	local valorDefault=$2;
	local respuesta="";
	
	while [ -z $respuesta ]	#mientras no responda si o no
	do 
		read -p "$pregunta" resp; #leo la respuesta y la guardo en $resp
		echo $resp
		if [ "$resp" = "" ]
		then
			respuesta=$valorDefault;
		else
			respuesta=$(echo $resp | grep '^[1-9]*$');
		fi
	done
	respVal=$respuesta;
}

respSINO=""; #respuesta que devuelve la funcion
function pregUsuarioSINO(){
	local pregunta=$1;
	local respVal="";
	
	while [ -z $respVal ]	#mientras no responda si o no
	do 
		read -p "$pregunta SI - NO: " resp; #leo la respuesta y la guardo en $resp
		respVal=$(echo $resp | grep '^[Ss][Ii]$\|^[Nn][Oo]$'); #valido que la respuesta sea si o no

	done
	#transformo la respuesta a minuscula
	resp=$(echo $respVal | sed 's/^[Ss][Ii]$/si/');
	
	#transformo la respuesta en un numero
	if [ $resp = "si" ]; then
		respSINO=1;
	else
		respSINO=0;
	fi
}

#verificar parametros

if [ $# -gt 0 ] #si hay mas de 0 parametros sale
then
	echo "No pueden existir parametros" >&2
	exit 1
fi

if [ -z $LOGDIR ] #si no se setearon las variables de entorno
then
#tomo variables de archivo de configuracion
	export LOGDIR=`parsearValor 14`
	export MAXLOG=`parsearValor 6`
	export DATADIR=`parsearValor 4`
	export USERID=`parsearValor 12`
	export BINDIR=`parsearValor 11`

#chequear si se encuentra realizado lo indispensable de la instalacion
	if [ -e $CONFIGFILE -a -e "$GRUPO/$BINDIR" -a -e "$GRUPO/$LOGDIR" -a -e "$GRUPO/$BINDIR/$detectar" -a -e "$GRUPO/$BINDIR/$interpretar" -a -e "$GRUPO/$BINDIR/$logger" -a -e "$GRUPO/$BINDIR/$reporte" -a -e "$GRUPO/$DATADIR" ]
	then
		echo "El programa fue instalado correctamente"
	else
		echo "El programa no fue instalado correctamente"
		echo "Reinstale por favor"
		unset LOGDIR
		unset MAXLOG
		unset USERID
		unset BINDIR
		unset DATADIR
		exit 1
	fi
	PATH="$PATH:$GRUPO/$BINDIR"
	glog.sh iniciar I "INICIO Iniciar"
	echo "Se procede a iniciar el programa"
	echo ""
else
	echo "Se procede a iniciar el programa"
	echo "Ya se setearon las variables de ambiente antes. Sus valores son"
	glog.sh iniciar I "INICIO Iniciar"
	glog.sh iniciar I "Ya se setearon las variables de ambiente antes."
	echo "LOGDIR=$LOGDIR"
	echo "MAXLOG=$MAXLOG"
	echo "USERID=$USERID"
	echo "BINDIR=$BINDIR"
	echo ""
fi

#pido el pid de detectar.sh
pid=$(obtpid.sh $detectar)

#chequeo si ya se llamo a iniciar antes
if [ -z $CANLOOP ]
then
	#preguntar al usuario por CANLOOP y TESPERA
	pregUsuario "Cantidad de Ciclos de DETECTAR? (100 ciclos)" 100
	export CANLOOP=$respVal
	pregUsuario "Tiempo de espera entre ciclos? (1 minuto)" 1
	export TESPERA=$respVal

	glog.sh iniciar I "Se setearon variables de entorno TESPERA=$TESPERA y CANLOOP=$CANLOOP"
else
	echo "Ya se llamo a INICIAR anteriormente"
	echo "CANLOOP = $CANLOOP"
	echo "TESPERA = $TESPERA"
	glog.sh iniciar I "Se llamo INICIAR anteriorimente y tenian variables seteadas TESPERA=$TESPERA y CANLOOP=$CANLOOP"
fi

echo ""

if [ -z $pid ]
then
	pregUsuarioSINO "Desea efectuar el inicio de DETECTAR?"
	if [ $respSINO = 1 ]
	then
		$detectar &
		pid=$(obtpid.sh $detectar)
		echo "Se inicia el demonio detectar. Se encuentra corriendo bajo el no. $pid"
		glog.sh iniciar I "Se inicia el demonio Detectar con PID=$pid"
	else
		glog.sh iniciar I "No se ha deseado iniciar Detectar"
		echo "Para iniciar el demonio DETECTAR se debe ir a la consola y llamar a $GRUPO/$BINDIR/$detectar con un & al final para que se inicie como proceso aparte.
Ej: >$detectar & ";
	fi
else
	glog.sh iniciar I "El detectar ya se encontraba corriendo con no. $pid"
	echo "El demonio detectar ya se encuentra corriendo bajo no. $pid"
fi

glog.sh iniciar I "FIN Iniciar"


