#/bin/bash
clear 
echo "PELICULAS"
echo "========="
echo "Nueva Pelicula"
echo "Ingrese nombre de la pelicula"
function cuadrado()
{

	return=`expr $1 \* $1`
	echo $return
}
ver=`cuadrado 96`
echo $ver