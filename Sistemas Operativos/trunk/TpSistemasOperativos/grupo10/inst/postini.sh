#!/bin/bash
# Comando de Inicialización del ambiente
# Inicializa todas las variables de ambiente necesarias para la ejecución
# de la aplicación y valida la existencia de los archivos maestros de 
# Beneficios y Agencias

# Salida
# Devuelve 0 si se inicializa correctamente
# Devuelve 1 si hubo algún error

# Variable de instalación (se tiene que pisar -o borrar esta linea y setear - desde el INSTULA cuando se copie a BINDIR)
GRUPO="LLENAR EN INSTALACION"

# Mensaje de error
errorMsj="Inicialización de Ambiente No fue exitosa. Error en"

# Archivo de configuración
CONFIGFILE="$GRUPO/conf/instula.conf"

# Esta función recibe un número de linea y devuelve el valor de la variable
# correpondiente del archivo de configuración
function obtenerValor(){
	head -n $1 $CONFIGFILE | tail -1 | sed -e 's/.*=//'
}

# Esta función muestra las variables seteadas y su correpondiente valor
function mostrarVariables(){
	echo "Las variables seteadas fueron: "
	echo "CONFDIR = $CONFDIR"
	echo "ARRIDIR = $ARRIDIR"
	echo "BINDIR = $BINDIR"
	echo "DATASIZE = $DATASIZE"
	echo "LOGDIR = $LOGDIR"
	echo "LOGEXT = $LOGEXT"
	echo "INSTDIR = $INSTDIR"
	echo "LOGSIZE = $LOGSIZE"
	echo "USERID = $USERID"
	echo "DATADIR = $DATADIR"
}

# Esta función termina la ejecución del script
function terminar(){
	echo "Pulse una tecla para finalizar POSTINI..."
	read end
	return 1	
}

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
	echo "Las variables han sido inicializadas con éxito"
else
	echo "Las variables fueron inicializadas previamente"
	echo "`mostrarVariables`"
fi

# Validar que existan directorios y archivos necesarios para la ejecución
if [ ! -e "$DATADIR/agencias.mae" ]
then
	echo "$errorMsj archivo maestro de agencias (\"$DATADIR/agencias.mae\" no existe)"
	terminar
fi
if [ ! -e "$DATADIR/beneficios.mae" ]
then
	echo "$errorMsj archivo maestro de beneficios (\"$DATADIR/beneficios.mae\" no existe)"
	terminar
fi
if [ ! -e "$BINDIR" ]
then
	echo "$errorMsj directorio de Ejecutables (\"$BINDIR\" no existe)"
	terminar
fi
if [ ! -e "$ARRIDIR" ]
then
	echo "$errorMsj directorio de Recibidos (\"$ARRIDIR\" no existe)"
	terminar
fi
if [ ! -e "$LOGDIR" ]
then
	echo "$errorMsj directorio de Log (\"$LOGDIR\" no existe)"
	terminar
fi
if [ ! -e "$BINDIR/postonio.sh" ]
then
	echo "$errorMsj comando POSTONIO (\"$BINDIR/postonio.sh\" no existe)"
	terminar
fi
if [ ! -e "$BINDIR/postular.sh" ]
then
	echo "$errorMsj comando POSTULAR (\"$BINDIR/postula.sh\" no existe)"
	terminar
fi


# PID de postonio.sh
#pid=$(obtpid.sh "postonio.sh")

# Verificar que no haya un POSTONIO corriendo
#if [ -z $pid ]
#then
#	$postonio &
#	pid=$(obtpid.sh $postonio)
#	echo "Se inicia el demonio postonio. Se encuentra corriendo bajo el no. $pid"
#else
#	echo "postonio.sh ya se encuentra corriendo bajo nro. $pid"
#fi


echo "Inicialización de Ambiente Concluida"
echo "Ambiente:"
echo "`mostrarVariables`"
echo "Demonio corriendo bajo el Nro.: $pid"


