#!/bin/bash

# Comando "gralog"

# Output
# 	Archivo de log
#
# Opciones y Parámetros
#	Parámetro 1 (obligatorio): comando
#	Parámetro 2 (opcional): tipo de mensaje 
#	Parámetro 3 (obligatorio): mensaje

# No pueden ser más de 3 ni menos de 2 parámetros

#TODO HAY Q VER LO DE LAS EXTENSIONES PQ SON POR DEFECTO .LOG PERO EL USUARIO PUEDE CAMBIARLO EN UNA VARIABLE LOGEXT

if [ $# -gt 4 -o $# -lt 2 ]
then
	./gralog.sh gralog E "$1: Cantidad de parámetros inválida."
	exit 1
fi

# Si es del instalador va en otro lado (TODO si el comando es instula el archivo de Log llamado instula.log que se graba en el directorio $grupo/conf) VER ESTO
if [ -z $LOGDIR ]
then
	logdir="$GRUPO/conf"
else
	logdir="$GRUPO/$LOGDIR"
fi

# Que la dirección no sea un archivo
if [ -f $logdir ]
then
	./gralog.sh gralog E "$1: La dirección del directorio de destino es un archivo."
	exit 1
fi

# Si no existe lo crea.
if [ ! -d $logdir ]
then
	mkdir $logdir
fi

log=$logdir/$1.log

# Si el archivo no existe lo crea
touch $log  

tipoMensaje="  "
mensaje=""

# Si hay dos parámetros no tengo tipo de mensaje

if [ $# -eq 2 ]
then
	mensaje=$2
fi

# Si hay tres parámetros tengo tipo

if [ $# -eq 3 ]
then
	tipoMensaje=$(echo $2 | tr "[:lower:]" "[:upper:]")
	mensaje=$3

	#I = INFORMATIVO: mensajes informativos o explicativos sobre el curso de ejecución del comando. Ej: Inicio de Ejecución
	#A = ALERTA: mensajes de advertencia pero que no afectaran la continuidad de ejecución del comando. Ej: Archivo ya procesado
	#E = ERROR: mensajes de error Ej: Archivo Inexistente.
	#SE = ERROR SEVERO: mensajes severos de error que provocaran la cancelación del comando: Ej: Archivo Maestro no encontrado

	# Si el tipo de mensaje es inválido lo pone en el log del gralog
	if [ $tipoMensaje != I -a $tipoMensaje != A -a $tipoMensaje != E -a $tipoMensaje != SE ]
	then
		tipoMensaje="  "
		./gralog.sh gralog "$1: Tipo de mensaje inválido."
	fi
	
fi

#el 4to parametro sirve para activar la salida standar ademas de escribir en el log
if [ $# -eq 4 ]
then
	tipoMensaje=$(echo $2 | tr "[:lower:]" "[:upper:]")
	mensaje=$3
	
	if [ $tipoMensaje != I -a $tipoMensaje != A -a $tipoMensaje != E -a $tipoMensaje != SE ]
	then
		tipoMensaje="  "
		./gralog.sh gralog "$1: Tipo de mensaje inválido."
	fi
	
	if [ $4 -eq 1 ]
		then
		echo $mensaje
	fi		
fi
unaCadena=$tipoMensaje/

tamanioArchivo=`stat -c%s $log`

# Si el tamaño es menor a $LOGSIZE y no es instalacion puede haber que recortar
if [ $LOGSIZE ]
then
	if [ $tamanioArchivo -eq $LOGSIZE ] || [ $tamanioArchivo -gt $LOGSIZE ]
	then
		# Lo paso a un archivo nuevo, borro el viejo y renombro
		lineas=`wc -l $log | cut -d ' ' -f 1`
		if [ $lineas -gt 50 ]
		then
			logtemp=$log.temp
			touch $logtemp
			tail -q -n 50 $log > $logtemp
			rm $log
			mv $logtemp $log
		fi
	fi
fi
# Escribo el archivo incluyendo nombre de usuario y fecha
usuario=`whoami`
fecha=`date +"%X %x"`
echo "$usuario $fecha $1 $tipoMensaje $mensaje" >> $log

exit 0 
