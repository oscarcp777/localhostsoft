#!/bin/bash
#Comando que sirve para matar el proceso postonio

GRALOG=./gralog.sh
pidPostonio=$(ps | grep "postonio.sh" | head -5c)

if [ -z $pidPostonio ]; then
			$GRALOG postonio I "Postonio no se encuentra iniciado, no se ha detenido nada." 1	
		else
			kill $pidPostonio
			$GRALOG postonio SE "El proceso postonio.sh se ha parado" 1	
			
fi

