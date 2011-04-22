#!/bin/bash
# Comando de Inicialización del ambiente
# Inicializa todas las variables de ambientes necesarias para la ejecución
# de la aplicación y valida la existencia de los archivos maestros de 
# Beneficios y Agencias

# Salida
# Devuelve 0 si se inicializa correctamente
# Devuelve 1 si hubo algún error

# Variable de instalación (se tiene que pisar desde el INSTULA)
GRUPO="/home/Santiago/Documentos/Materias/Sistemas_Operativos/scripts/comandoPostini"

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
	echo "MAXLOGSIZE = $MAXLOGSIZE"
	echo "USERID = $USERID"
	echo "DATADIR = $DATADIR"
}

# Seteo de Variables de Ambiente
if [ -z $ARRIDIR  ] 
then
	export CONFDIR=`obtenerValor 2`
	export ARRIDIR=`obtenerValor 3`
	export BINDIR=`obtenerValor 4`
	export DATASIZE=`obtenerValor 5`
	export LOGDIR=`obtenerValor 6`
	export LOGEXT=`obtenerValor 7`
	export INSTDIR=`obtenerValor 8`
	export MAXLOGSIZE=`obtenerValor 9`
	export USERID=`obtenerValor 10`
	export DATADIR=`obtenerValor 21`
	echo "Las variables han sido inicializadas con éxito"
else
	echo "Las variables fueron inicializadas previamente"
	echo "`mostrarVariables`"
fi

# Validar que existan directorios y archivos necesarios para la ejecución
if [ ! -e "$GRUPO$DATADIR/agencias.mae" ]
then
	echo "$errorMsj archivo maestro de agencias (\"$GRUPO$DATADIR/agencias.mae\" no existe)"
	read pause
	exit 1
fi
if [ ! -e "$GRUPO$DATADIR/beneficios.mae" ]
then
	echo "$errorMsj archivo maestro de beneficios (\"$GRUPO$DATADIR/beneficios.mae\" no existe)"
	read pause
	exit 1
fi
if [ ! -e "$GRUPO$BINDIR" ]
then
	echo "$errorMsj directorio de Ejecutables (\"$GRUPO$BINDIR\" no existe)"
	read pause
	exit 1
fi
if [ ! -e "$GRUPO$ARRIDIR" ]
then
	echo "$errorMsj directorio de Recibidos (\"$GRUPO$ARRIDIR\" no existe)"
	read pause
	exit 1
fi
if [ ! -e "$GRUPO$LOGDIR" ]
then
	echo "$errorMsj directorio de Log (\"$GRUPO$LOGDIR\" no existe)"
	read pause
	exit 1
fi


echo "Inicialización de Ambiente Concluida"
echo "Ambiente:"
echo "`mostrarVariables`"
echo "Demonio corriendo bajo el Nro.: 1111"


