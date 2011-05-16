
#Salida por pantalla una lista, de todos los archivos benef.<id>, todas las agencias y todas los beneficios y solo los pendientes, y una matriz de beneficiarios. 
clear;
echo "-------------------------TEST1--------------------------------------------"
echo "--------LISTA,MATRIZ,TODAS LAS AGENCIAS Y BENEFICIOS, PENDIENTES----------"	
./plist.pl benef.* '.*' '.*' -t -c -ep
#idem solo los aprobados
echo "-------------------------TEST2--------------------------------------------"
echo "--------LISTA,MATRIZ,TODAS LAS AGENCIAS Y BENEFICIOS, APROBADOS-----------"
./plist.pl benef.* '.*' '.*' -t -c -ea
#idem solo los rechazados
echo "-------------------------TEST3--------------------------------------------"
echo "--------LISTA,MATRIZ,TODAS LAS AGENCIAS Y BENEFICIOS, RECHAZADOS----------"
./plist.pl benef.* '.*' '.*' -t -c -er
#Idem pendientes, rechazados y aprobados
echo "-------------------------TEST4--------------------------------------------"
echo "--------LISTA,MATRIZ,TODAS LAS AGENCIAS Y BENEFICIOS, TODOS LOS ESTADOS---"
./plist.pl benef.* '.*' '.*' -t -c
#Idem pero salida por archivo y pantallad con la opcion -td
echo "-------------------------TEST5--------------------------------------------"
echo "--------LISTA,MATRIZ,TODAS LAS AGENCIAS Y BENEFICIOS, PENDIENTES----------"
./plist.pl benef.* '.*' '.*' -td -c


