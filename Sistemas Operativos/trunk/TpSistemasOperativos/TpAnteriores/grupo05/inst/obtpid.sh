#!/bin/bash
#encuentra el process id del primer proceso que coincida con el nombre

#verifico que pasen un y solo un parámetro
if [ $# -gt 1 ]
then
    echo "Demasiados parámetros" >&2
    exit 2
elif [ $# -eq 0 ]
then
    echo "Se debe especificar el nombre de proceso" >&2
    exit 2
fi

resultado=$(ps a | grep -v $0 | grep "$1" | grep -v "grep" | head -n1 | head -c5) 
verif=$(echo $resultado | wc -w)
if [ $verif -eq 0 ]
then #Si no se encontró el process id
    exit 1
else
    echo $resultado
    exit 0
fi
