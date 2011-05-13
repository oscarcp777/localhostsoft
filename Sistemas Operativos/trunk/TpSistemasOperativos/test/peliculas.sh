#/bin/bash
clear 
echo "PELICULAS"
echo "========="
echo "Nueva Pelicula"
echo "Ingrese nombre de la pelicula"
function sumaMes(){ 
	        year=$(echo "$1" | awk -F- '{print $1}')
	        mes=$(echo "$1" | awk -F- '{print $2}')
	        dia=$(echo "$1" | awk -F- '{print $3}')
	        numMeses=$2
           for ((i = 0; i<numMeses; i++))
           do
          if [ $mes -eq 12 ] ; then 
              mes=1 
              year=`expr $year + 1` 
          else
          mes=`expr $mes + 1` 
          fi
          done
          cant=$(echo $mes | wc -c)
         if [ $cant -eq 2 ] ; then
            mes="0$mes"
         fi	
       echo "$year-$mes-$dia"
} 
function cuadrado()
{

	return=`expr $1 \* $1`
	echo $return
}
ver=`cuadrado 96`
fecha=`sumaMes "2011-01-12" 18`
echo $fecha
echo $ver