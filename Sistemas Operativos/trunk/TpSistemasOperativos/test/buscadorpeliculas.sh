#/bin/bash
clear
echo "Buscador Peliculas"
echo "Criterio de busqueda"
echo "1)Bucar por titulo"
echo "2)Buscar por director"
echo "3)Buscar por año"
read criterio
case $criterio in
1)
echo "Ingrese el titulo"

read titulo
echo $titulo
grep $titulo /home/oscar/workspace/Test/src/peliculas.txt
read pausa
;;
2) 
echo "Ingrese el director"
read director
grep $director /home/oscar/workspace/Test/src/peliculas.txt
read pausa
;;
3)
echo "Ingrese el año"
read anio
grep $anio /home/oscar/workspace/Test/src/peliculas.txt
read pausa
;;
esac
