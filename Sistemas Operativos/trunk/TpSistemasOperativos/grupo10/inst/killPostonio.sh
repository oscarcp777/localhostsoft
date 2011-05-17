#!/bin/bash
#Comando que sirve para matar el proceso postonio
#1.- VEO SI SE INICIALIZO EL AMBIENTE

if [ -z $LOGDIR ] || [ -z $CONFDIR ] || [ -z $DATADIR ] || [ -z $ARRIDIR ] || [ -z $BINDIR ] || [ -z $DATASIZE ] || [ -z $LOGEXT ] || [ -z $INSTDIR ] || [ -z $LOGSIZE ] || [ -z $USERID ] || [ -z $PROCESSED ] || [ -z $REJECTED ] || [ -z $RECEIVED ] ; then
     echo "ERROR: Las variables de ambiente no se encuentran inicalizadas"
   # $GRALOG postonio SE "Las variables de ambiente no se encuentran inicalizadas"
    exit 1
fi
GRALOG=./gralog.sh
pidPostonio=$(ps | grep "postonio.sh" | head -5c)

if [ -z $pidPostonio ]; then
			$GRALOG postonio I "Postonio no se encuentra iniciado, no se ha detenido nada." 1	
		else
			kill $pidPostonio
			$GRALOG postonio SE "El proceso postonio.sh se ha parado" 1	
			
fi

