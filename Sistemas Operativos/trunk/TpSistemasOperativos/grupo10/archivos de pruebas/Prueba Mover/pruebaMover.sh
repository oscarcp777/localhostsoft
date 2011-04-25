#Directorios de prueba
directorioDestino='./destino'
directorioOrigen='./origen'

#validamos si existe los directorios origen y destino
if [ ! -d $directorioDestino ]
then 
	mkdir $directorioDestino
fi

if [ ! -d $directorioOrigen ]
then
	mkdir $directorioOrigen
fi

#creamos archivo(arch.txt) de prueba
archivo='arch.txt'
echo "archivo de prueba" >> $directorioOrigen/$archivo

#comando mover
alias move='./mover.sh'

#Movemos archivo con mismo nombre a  directorios

/home/hlovey/mover.sh "$directorioOrigen/$archivo" "$directorioDestino/$archivo"


