#/bin/bash
clear 
echo "PELICULAS"
echo "========="
echo "Nueva Pelicula"
echo "Ingrese nombre de la pelicula"
read pelicula
echo "Ingrese director"
read director
echo "Ingrese año"
read anio
hola="222";
echo "$pelicula $director $anio" >> peliculas.txt
