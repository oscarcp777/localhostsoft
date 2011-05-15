#!/bin/bash
# Comando de Inicialización del ambiente
# Inicializa todas las variables de ambiente necesarias para la ejecución
# de la aplicación y valida la existencia de los archivos maestros de 
# Beneficios y Agencias

# Salida
# Devuelve 0 si se inicializa correctamente
# Devuelve 1 si hubo algún error

# Variable de instalación (se llena desde el INSTULA cuando se copie a BINDIR)
GRUPO=
#GRUPO="LLENAR EN INSTALACION"

# Comandos
GRALOG="./gralog.sh"
POSTONIO="./postonio.sh"

# Mensaje de error
errorMsj="Inicialización de Ambiente No fue exitosa. Error en"

# Archivo de configuración
CONFIGFILE=$GRUPO"/conf/instula.conf"

# Esta función recibe un número de linea y devuelve el valor de la variable
# correpondiente del archivo de configuración
function obtenerValor(){
	head -n $1 $CONFIGFILE | tail -1 | sed -e 's/.*=//'
}

# Esta función muestra las variables seteadas y su correpondiente valor
function mostrarVariables(){
	$GRALOG postini I  "CONFDIR = $CONFDIR" 1
	$GRALOG postini I  "ARRIDIR = $ARRIDIR" 1
	$GRALOG postini I  "BINDIR = $BINDIR" 1
	$GRALOG postini I  "DATASIZE = $DATASIZE" 1
	$GRALOG postini I  "LOGDIR = $LOGDIR" 1
	$GRALOG postini I  "LOGEXT = $LOGEXT" 1
	$GRALOG postini I  "INSTDIR = $INSTDIR" 1
	$GRALOG postini I  "LOGSIZE = $LOGSIZE" 1
	$GRALOG postini I  "USERID = $USERID" 1
	$GRALOG postini I  "DATADIR = $DATADIR" 1
	$GRALOG postini I  "PROCESSED=$PROCESSED" 1
	$GRALOG postini I  "REJECTED=$REJECTED" 1
	$GRALOG postini I  "RECEIVED=$RECEIVED" 1
}

# Esta función termina la ejecución del script
function terminar(){
	echo "Pulse una tecla para finalizar POSTINI..."
	read end
}



# Validar que este seteada la variable GRUPO
if [ -z "$GRUPO" ]
then
	echo "Ejecute este comando desde el directorio de ejecutables"
	return 1
fi		

# Seteo de Variables de Ambiente
if [ -z $ARRIDIR  ] 
then
	export CURRDIR=`obtenerValor 1`
	export CONFDIR=`obtenerValor 2`
	export ARRIDIR=`obtenerValor 3`
	export BINDIR=`obtenerValor 4`
	export DATASIZE=`obtenerValor 5`
	export LOGDIR=`obtenerValor 6`
	export LOGEXT=`obtenerValor 7`
	export LOGSIZE=`obtenerValor 8`
	export USERID=`obtenerValor 9`
	export DATADIR=`obtenerValor 21`
	export INSTDIR=`obtenerValor 22`
	export PROCESSED=`obtenerValor 23`
	export REJECTED=`obtenerValor 24`
	export RECEIVED=`obtenerValor 25`
	$GRALOG postini I "Las variables han sido inicializadas con éxito" 1
else
	$GRALOG postini I "Las variables fueron inicializadas previamente" 1
fi

# Validar que existan directorios y archivos necesarios para la ejecución
if [ ! -e "$DATADIR/agencias.mae" ]
then
	$GRALOG postini E "$errorMsj archivo maestro de agencias (\"$DATADIR/agencias.mae\" no existe)" 1
	$GRALOG postini I "El comando POSTINI termino con errores"
	$GRALOG postini I ""
	terminar
	return 1
fi
if [ ! -e "$DATADIR/beneficios.mae" ]
then
	$GRALOG postini E "$errorMsj archivo maestro de beneficios (\"$DATADIR/beneficios.mae\" no existe)" 1
	$GRALOG postini I "El comando POSTINI termino con errores"
	$GRALOG postini I ""
	terminar
	return 1
fi
if [ ! -e "$BINDIR" ]
then
	$GRALOG postini E "$errorMsj directorio de Ejecutables (\"$BINDIR\" no existe)" 1
	$GRALOG postini I "El comando POSTINI termino con errores"
	$GRALOG postini I ""
	terminar
	return 1
fi
if [ ! -e "$ARRIDIR" ]
then
	$GRALOG postini E "$errorMsj directorio de Recibidos (\"$ARRIDIR\" no existe)" 1
	$GRALOG postini I "El comando POSTINI termino con errores"
	$GRALOG postini I ""
	terminar
	return 1
fi

if [ ! -e "$PROCESSED" ]
then
	$GRALOG postini E "$errorMsj directorio de Procesados (\"$PROCESSED\" no existe)" 1
	$GRALOG postini I "El comando POSTINI termino con errores"
	$GRALOG postini I ""
	terminar
	return 1
fi

if [ ! -e "$REJECTED" ]
then
	$GRALOG postini E "$errorMsj directorio de Rechazados (\"$REJECTED\" no existe)" 1
	$GRALOG postini I "El comando POSTINI termino con errores"
	$GRALOG postini I ""
	terminar
	return 1
fi

if [ ! -e "$RECEIVED" ]
then
	$GRALOG postini E "$errorMsj directorio de Recibidos (\"$RECEIVED\" no existe)" 1
	$GRALOG postini I "El comando POSTINI termino con errores"
	$GRALOG postini I ""
	terminar
	return 1
fi

if [ ! -e "$LOGDIR" ]
then
	$GRALOG postini E "$errorMsj directorio de Log (\"$LOGDIR\" no existe)" 1
	$GRALOG postini I "El comando POSTINI termino con errores"
	$GRALOG postini I ""		
	terminar
	return 1
fi
if [ ! -e "$BINDIR/postonio.sh" ]
then
	$GRALOG postini E "$errorMsj comando POSTONIO (\"$BINDIR/postonio.sh\" no existe)" 1
	$GRALOG postini I "El comando POSTINI termino con errores"
	$GRALOG postini I ""		
	terminar
	return 1
fi
if [ ! -e "$BINDIR/postular.sh" ]
then
	$GRALOG postini E "$errorMsj comando POSTULAR (\"$BINDIR/postula.sh\" no existe)" 1
	$GRALOG postini I "El comando POSTINI termino con errores"
	$GRALOG postini I ""
	terminar
	return 1
fi


#PID de postonio.sh
pid=$(ps -A | grep -v $0 | grep "postonio.sh" | grep -v "grep" | head -n1 | head -c5) 

# Verificar que no haya un POSTONIO corriendo
if [ -z $pid ]
then
	$POSTONIO &
	pid=$(ps -A | grep -v $0 | grep "postonio.sh" | grep -v "grep" | head -n1 | head -c5) 
	$GRALOG postini I  "Se inicia el demonio postonio. Se encuentra corriendo bajo el no. $pid" 1
else
	$GRALOG postini I  "postonio.sh ya se encuentra corriendo bajo nro. $pid" 1
fi

$GRALOG postini I "Inicialización de Ambiente Concluida" 1
$GRALOG postini I  "Ambiente:" 1
$GRALOG postini I  "Las variables seteadas fueron: " 1
mostrarVariables
$GRALOG postini I "Demonio corriendo bajo el Nro.: $pid" 1
$GRALOG postini I "El comando POSTINI finalizo correctamente"
$GRALOG postini I ""

