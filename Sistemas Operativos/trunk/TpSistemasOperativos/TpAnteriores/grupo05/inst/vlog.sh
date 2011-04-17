#!/bin/bash

# Comando "vglog"

# Output
# 	Archivo de log
#
# Opciones y Parámetros
#	Parámetro 1 (obligatorio): comando
#	Parámetro 2 (deseable): algún tipo de filtro (-h para hora, -d para dia, -m para mes, -a para año, -t para tipo) 
#	Parámetro 3 (obligatorio si hay tipo de filtro): filtro

# No pueden ser más de 2 ni menos de 1 parámetros

if [ $# -gt 11 -o $# -lt 1 ]
then
	./glog.sh vglog es "Cantidad de parámetros inválida."
	exit 1
fi


logdir="$GRUPO/$LOGDIR"

# Si es del instalador va en otro lado
if [ $1 = instalar -o -z $logdir ]
then
	logdir="../log"
fi

archivo=$logdir/$1.log

if [ ! -f $archivo ]; then
  	./glog.sh vglog es "No existe el archivo."
  	exit 2
   elif [ ! -r $archivo ]; then
  	./glog.sh vglog es "No se puede leer el archivo."
  	exit 3
   fi



tipo=""	
dia=""
mes=""
anio=""
hora=""
anterior=""

for var in "$@"
do	
case $anterior in
"-t") tipo=$(echo $var | tr "[:lower:]" "[:upper:]") ;;
"-h") hora=$var ;;
"-d") dia=$var ;;
"-m") mes=$var ;;
"-a") anio=$var ;;
esac
	anterior=$var
done

# Encabezados

	printf "%-*s" 21 "Fecha"
	printf "%-*s" 12 "Fución"
	printf "%-*s" 9 "Tipo"
	printf "%-s\n" "Mensaje"	


	#lineas=`wc -l $archivo | cut -d ' ' -f 1`
	#lineas=$(echo "$lineas+1" | bc)

	contLineas=1

	while read linea #[ $contLineas != $lineas ]
		
	do
		lineaFiltrada=$linea

		if [ -n "$lineaFiltrada" -a -n "$tipo" ]
		then
			lineaFiltrada=`echo "$lineaFiltrada" | sed -n "s/\([0-2][0-9]:[0-6][0-9]:[0-6][0-9] [0-3][0-9]\/[0-1][0-9]\/[0-9][0-9] \)\(${1} \)\(${tipo} \).*/&/gp"`
		fi

		if [ -n "$lineaFiltrada" -a -n "$hora" ]
		then
			lineaFiltrada=`echo "$lineaFiltrada" | sed -n "s/\(${hora}:[0-6][0-9]:[0-6][0-9] \)\([0-3][0-9]\/[0-1][0-9]\/[0-9][0-9] \).*/&/p"`
		fi

		if [ -n "$lineaFiltrada" -a -n "$dia" ]
		then
			lineaFiltrada=`echo "$lineaFiltrada" | sed -n "s/\([0-2][0-9]:[0-6][0-9]:[0-6][0-9] \)\(${dia}\/[0-1][0-9]\/[0-9][0-9] \).*/&/p"`
		fi

		if [ -n "$lineaFiltrada" -a -n "$mes" ]
		then
			lineaFiltrada=`echo "$lineaFiltrada" | sed -n "s/\([0-2][0-9]:[0-6][0-9]:[0-6][0-9] \)\([0-3][0-9]\/${mes}\/[0-9][0-9] \).*/&/p"`
		fi

		if [ -n "$lineaFiltrada" -a -n "$anio" ]
		then
			lineaFiltrada=`echo "$lineaFiltrada" | sed -n "s/\([0-2][0-9]:[0-6][0-9]:[0-6][0-9] \)\([0-3][0-9]\/[0-1][0-9]\/${anio} \).*/&/p"`
		fi

		if [ -n "$lineaFiltrada" ]
		then
	
			printf "%-20s %s" "`echo "$lineaFiltrada" | sed -n "s/\([0-2][0-9]:[0-6][0-9]:[0-6][0-9] [0-3][0-9]\/[0-1][0-9]\/[0-9][0-9] \).*/\1/gp"`"
			printf "%-10s %s" "$1"
			printf "%-8s %s" "`echo "$lineaFiltrada" | sed -n "s/\([0-2][0-9]:[0-6][0-9]:[0-6][0-9] [0-3][0-9]\/[0-1][0-9]\/[0-9][0-9] \)\(${1} \)\(.. \).*/\3/gp"`"
			printf "%s\n" "`echo "$lineaFiltrada" | sed -n "s/\([0-2][0-9]:[0-6][0-9]:[0-6][0-9] [0-3][0-9]\/[0-1][0-9]\/[0-9][0-9] \)\(${1} \)\(.. \)\(.*\)/\4/gp"`"
			#echo $lineaFiltrada
		fi
	done < $archivo
exit 0
