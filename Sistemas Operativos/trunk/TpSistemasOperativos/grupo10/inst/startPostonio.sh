#!/bin/bash
#Comando que sirve para inicializar el proceso postonio, se verifica que no este corriendo otro.
GRALOG=./gralog.sh
POSTONIO="./postonio.sh"

#PID de postonio.sh
pid=$(ps -A | grep -v $0 | grep "postonio.sh" | grep -v "grep" | head -n1 | head -c5) 

# Verificar que no haya un POSTONIO corriendo
if [ -z $pid ]
then
	$POSTONIO &
	pid=$(ps -A | grep -v $0 | grep "postonio.sh" | grep -v "grep" | head -n1 | head -c5) 
	$GRALOG postonio I  "Se inicia el demonio postonio. Se encuentra corriendo bajo el no. $pid" 1
else
	$GRALOG postonio I  "postonio.sh ya se encuentra corriendo bajo nro. $pid" 1
fi

