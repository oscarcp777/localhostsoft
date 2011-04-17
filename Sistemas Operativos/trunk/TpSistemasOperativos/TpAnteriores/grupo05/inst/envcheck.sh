#!/bin/bash

#Comando que chequea que las variables de entorno estén inicializadas
#Echo 1 si el ambiente no fue inicializado
#Echo 0 si están inicializadas

if [ -z $LOGDIR ] || [ -z $BINDIR ] || [ -z $DATADIR ] || [ -z $CANLOOP ] || [ -z $TESPERA ] || [ -z $USERID ] || [ -z $MAXLOG ]
then
    echo 1
else
    echo 0
fi

exit 0
