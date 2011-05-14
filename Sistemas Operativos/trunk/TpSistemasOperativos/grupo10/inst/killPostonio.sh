#!/bin/bash
#Comando que sirve para matar el proceso postonio

pidPostonio=$(ps | grep "postonio.sh" | head -5c)
kill $pidPostonio