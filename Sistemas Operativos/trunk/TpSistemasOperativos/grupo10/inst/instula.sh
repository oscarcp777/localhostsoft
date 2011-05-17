#!/bin/bash
#Valores de retorno
#	0 Finalizado con exito
#	1 No se seteo la variable $GRUPO o se seteo en un directorio incorrecto
#	2 Archivo de configuracion corrupto 
#   3 Elimine los componentes instalados e inténtelo nuevamente #TODO q pasa si estan todos borrados pero el archivo de conf no esta borrado  
# 	4 Usuario no acepto acuerdo de licencia de sowftware
#	5 Perl no esta instalado o su version es menor a la 5.0
#	6 Usuario no acepto continuar con la intalacion

# ------------------------------------------Variables------------------------------------------
# Directorio base de POSTULA
BASEDIR=$GRUPO"grupo10"
# Directorio de Archivos Maestros
DATADIR=$BASEDIR/data
# Directorio de Instalación
INSTDIR=$BASEDIR/inst
# Directorio de Configuración
CONFDIR=$BASEDIR/conf
# Archivo de Configuración
CONFFILE="instula.conf"
# Lista de todos los comandos del paquete
COMANDOS=("postini.sh" "postonio.sh" "postular.sh" "plist.pl" "mover.sh" "gralog.sh" "killPostonio.sh" "startPostonio.sh")
# Subdirectorio de ejecutables
BINDIR=""
ARRIDIR=""
DATASIZE=""
LOGDIR=""
LOGEXT=""
LOGSIZE=""
PROCESSED=$BASEDIR"/procesados"
REJECTED=$BASEDIR"/rechazados"
RECEIVED=$BASEDIR"/recibidos"
# ------------------------------------------Fin Variables------------------------------------------

# ------------------------------------------Comandos------------------------------------------
GRALOG=./gralog.sh
# ------------------------------------------Fin Comandos------------------------------------------

# ------------------------------------------Funciones Generales-----------------------------------------------------

# Esta función recibe un número de linea y devuelve el valor de la variable
# correpondiente del archivo de configuración
function obtenerValor(){
	head -n $1 "$CONFDIR/$CONFFILE" | tail -1 | sed -e 's/.*=//'
}
#obtiene valor de la linea pasada
function parsearValor() {
	head -n$1 "$CONFDIR/$CONFFILE" | tail -n1 | sed -e "s/.*=//" -e "s/^ *//"
}

# Esta función recibe un comando y una ubicación e instala el mismo
function instalarComando(){
	# Valida que los archivos no esten en el directorio destino
	if [ -e "$2/$1" ]; then
		$GRALOG instula A "	El componente $1 ya se encuentra instalado, el mismo no fue actualizado" 1 
	else
		cp $1 $2
		if [ "$1" = "postini.sh" ]; then
			#escribo $GRUPO 
    		sed -e "s:#GRUPO=\\\"LLENAR EN INSTALACION\\\":export GRUPO=\\\"$BASEDIR\\\":" "postini.sh" > "$BINDIR/postini.sh"
		fi
		#asigno permisos al script
		chmod u+x "$2/$1"
		$GRALOG instula I "	Permisos de ejecución asignados al archivo $1" 1
		
	$GRALOG instula I "	Instalación del componente  $1 completada" 1	
	fi	
}
	
# Esta función crea el archivo de configuración de la instalación
function crearConfiguracion(){
	$GRALOG instula I "Generando Archivo de Configuración..." 1
	echo "CURRDIR=$BASEDIR" >> "$CONFDIR/$CONFFILE"              	      	#1
	echo "CONFDIR=$CONFDIR" >> "$CONFDIR/$CONFFILE" 
	echo "ARRIDIR=$ARRIDIR" >> "$CONFDIR/$CONFFILE" 
	echo "BINDIR=$BINDIR" >> "$CONFDIR/$CONFFILE" 
	echo "DATASIZE=$DATASIZE" >> "$CONFDIR/$CONFFILE"
	echo "LOGDIR=$LOGDIR" >> "$CONFDIR/$CONFFILE"
	echo "LOGEXT=$LOGEXT" >> "$CONFDIR/$CONFFILE" 
	LOGSIZE=$(echo "$LOGSIZE*1024" | bc)
	echo "LOGSIZE=$LOGSIZE" >> "$CONFDIR/$CONFFILE" 
	echo "USERID= `whoami`" >> "$CONFDIR/$CONFFILE"
	echo "FECINS= `date +%D`" >> "$CONFDIR/$CONFFILE" 
	for ((i=0;i<10;i++)); do
		echo " " >> "$CONFDIR/$CONFFILE"
	done
	echo "DATADIR=$DATADIR" >> "$CONFDIR/$CONFFILE"
	echo "INSTDIR=$INSTDIR" >> "$CONFDIR/$CONFFILE"
	echo "PROCESSED=$PROCESSED" >> "$CONFDIR/$CONFFILE"
	echo "REJECTED=$REJECTED" >> "$CONFDIR/$CONFFILE"
	echo "RECEIVED=$RECEIVED" >> "$CONFDIR/$CONFFILE"

	for ((i=0;i<${#COMANDOS[*]};i++)); do
	    echo "COMAND = ${COMANDOS[$i]}" >> "$CONFDIR/$CONFFILE"
	    echo "USERID = `whoami`" >> "$CONFDIR/$CONFFILE"
	    echo "FECINS = `date +%D`" >> "$CONFDIR/$CONFFILE"
	    echo " " >> "$CONFDIR/$CONFFILE" 
	done
	$GRALOG instula I "Archivo de Configuración $CONFFILE generado con éxito" 1
}

# Esta función recibe una pregunta y valida su respuesta, siendo los valores posibles SI y NO
# Devuelve 1 si la respuesta es afirmativa y 0 si es negativa
respSINO=""; # Respuesta que devuelve la funcion
function pregSINO(){
	respSINO="";
	local pregunta=$1;
	local respVal="";
	
	while [ -z $respVal ]	# Mientras no responda si o no
	do 
		read -p "$pregunta SI - NO: " resp; # Lee la respuesta y la guarda en $resp
		respVal=$(echo $resp | grep '^[Ss][Ii]$\|^[Nn][Oo]$'); # Valido que la respuesta sea si o no

	done
	# Transforma la respuesta a minuscula
	resp=$(echo $respVal | sed 's/^[Ss][Ii]$/si/');
	
	# Transforma la respuesta en un numero
	if [ $resp = "si" ]; then
		respSINO=1;
	else
		respSINO=0;
	fi
}

# Esta función recibe un mensaje de pregunta para seleccionar un determinado directorio y en el segundo parametro el directorio por defecto
# Devuelve una cadena con el directorio seleccionado por el usuario
dirSeleccionado=""; # directorio que devuelve la funcion
function preguntarDirectorio(){
 dirSeleccionado=""
 local pregunta=$1
 local resp="";
 local posibleDir=""
	
	
	while [ -z $dirSeleccionado ]; do
		read -p "$pregunta" posibleDir;
		if [ -z $posibleDir ] ; then
			dirSeleccionado=$2
		else 
			resp=$(echo $posibleDir | grep "^[A-Za-z0-9%@_=:.]\{1,\}$");
						
			if [ -z $resp ]; then 
				echo "";
				echo "El nombre de directorio $posibleDir es invalido";
			else
				dirSeleccionado="$BASEDIR/$resp"
			fi
		fi	
	done
	
}

# Esta función recibe un mensaje de pregunta para seleccionar tamaño y en el segundo parametro es el tamaño por defecto
# Devuelve el tamaño definido por el usuario 
tamanio=0; # directorio que devuelve la funcion
function preguntarTamanio(){
 tamanio=0
 local pregunta=$1
 local resp="";
 local posibleTam=""
	
	
	while [ $tamanio -eq 0 ]; do
		read -p "$pregunta " posibleTam;
		if [ -z $posibleTam ] ; then
			tamanio=$2 #   $2 es el valor por dafault 
		else 
			resp=$(echo $posibleTam | grep "^[0-9]*$");			
			if [ -z $resp ]; then 
				echo "";
				echo "El valor $posibleTam es invalido";
			else
				tamanio=$resp
			fi
		fi	
	done
	
}

# Esta función recibe un mensaje de pregunta para seleccionar una extension de archivo y en el segundo parametro el valor por defecto
# Devuelve una cadena con la extension seleccionado por el usuario
extSeleccionada=""; # extension que devuelve la funcion
function preguntarExtension(){
 extSeleccionada=""
 local pregunta=$1
 local resp="";
 local posibleExt=""
	
	
	while [ -z $extSeleccionada ]; do
		read -p "$pregunta" posibleExt;
		if [ -z $posibleExt ] ; then
			extSeleccionada=$2
		else 
			resp=$(echo $posibleExt | grep "^[A-Za-z.]\{1,\}$");
						
			if [ -z $resp ]; then 
				echo "";
				echo "El nombre de de la extension $posibleExt es invalido";
			else
				extSeleccionada=$resp
			fi
		fi	
	done
	
}


# ------------------------------------------Fin Funciones Generales------------------------------------------



# --------------Inicio Programa--------------

# Verifica que la variable $GRUPO se haya seteado
if [ -z "$GRUPO" ]; then
	echo "";
	echo 'No se encuentra seteada la variable $GRUPO.'
	echo 'No se puede iniciar la instalación.';
	echo  'Por favor lea el archivo README.txt y vuelva a realizar la instalación';
	echo "";
	exit 1; 
else
	# Si esta seteada le agrega la ruta del grupo 10
	GRUPO="$GRUPO/grupo10"
fi

# Valida que exista un archivo previo de log de instalación 
if [ -e "$CONFDIR/instula.log" ]; then
	# Hay instalación previa
	# Renombra el archivo anterior 
	mv "$CONFDIR/instula.log" "$CONFDIR/instulaOLD.log"	
fi

$GRALOG instula I "Inicio de Instalación" 1

# Valida si existe una instalación previa
if [ -e "$CONFDIR/$CONFFILE" ]
then
	$GRALOG instula I "El programa ya se encuentra instalado" 1
	$GRALOG instula I "Verificando componentes ya instalados del programa..." 1
		
	# Verifica cuales componentes estan instalados y cuales no
	
	#array con el nombre de los comandos que faltan
	declare -a COMANDOS_INSTALADOS;
	declare -a COMANDOS_FALTANTES;
	indice=0; #indice del array
	indiceInstalados=0; #indice del array instalados

	#recupero el path de la carpeta de ejecutables que fue guardada en el archivo de configuracion
	directorioTempBin=`obtenerValor 4`

	#obtengo todos los comandos que hay y los guardo en comandos.temp
	cat "$CONFDIR/$CONFFILE" | grep "COMAND = " -n | sed "s/COMAND = //" > "$CONFDIR/comandos.temp";
	
	#recorro todo el archivo comandos.temp
	for linea in $(cat "$CONFDIR/comandos.temp"); do	
		#obtengo el numero de linea donde arranco a leer el comando y el nombre del comando
		numLinea=$(echo $linea | cut -f1 -d":");
		comando=$(echo $linea | cut -f2 -d":");
		
		#Las demas caracteristicas de los comandos deben estar si o si contiguas
		u=$(echo "scale=0;$numLinea+1" | bc -l); #USERID
		f=$(echo "scale=0;$numLinea+2" | bc -l); #FECHA
		
		#Obtengo todos los parametros del comando
		userComando=$(parsearValor $u);
		fecComando=$(parsearValor $f); 
		
		#sino estan contiguas el archivo esta corrupto	
		if [ -z "$userComando" -o -z "$fecComando" ]; then
			mensError="El archivo de configuracion se encuentra corrupto cercano a la linea $numLinea
					   Las descripciones de los comandos deben estar contiguas"
			$GRALOG instula E "$mensError" 1			
			exit 2;
		fi
		
		#si el archivo del comando existe
		if [ -e "$directorioTempBin/$comando" ]; then 
			#guardo el nombre del comando intalado en un vector
			varTemp=$comando"-"$fecComando"-"$userComando
			COMANDOS_INSTALADOS=( ${COMANDOS_INSTALADOS[*]} [$indiceInstalados]=$varTemp );
			indiceInstalados=$(($indiceInstalados+1));
			
		else
			#guardo el nombre del comando que falta en un vector
			COMANDOS_FALTANTES=( ${COMANDOS_FALTANTES[*]} [$indice]=$comando );
			indice=$(($indice+1));	
		fi
	done
	rm "$CONFDIR/comandos.temp";
	#Si no hay ningun comando faltante indicar al usuario que el programa esta correctamente instalado
	if [ -z $COMANDOS_FALTANTES ]; then
			echo "	********************************************************"
			echo "	*   Proceso de Instalación del sistema de Postulantes  *"
			echo "	*            Copyright TPSistemasOp (c)2011            *"
			echo "	********************************************************"
			echo "	 Se encuentran instalados los siguientes componentes: "
			for i in "${COMANDOS_INSTALADOS[@]}"; do 
			echo "         $i  ";
			 done
			echo "        ********************************************************"
			echo "	Proceso de Instalación Cancelado"
		exit 0;	

	else
			echo "  **************************************************************"
			echo "  * Proceso de Instalación del sistema Postulantes             *"
			echo "  *          Copyright TPSistemasOp (c)2011                    *"
			echo "  **************************************************************"
			echo "  * Se encuentran instalados los siguientes componentes:       *"
			for i in "${COMANDOS_INSTALADOS[@]}"; do 
			echo "         $i  ";
			done                                  
			echo "  * Falta instalar los siguientes componentes:                 *"
			for i in "${COMANDOS_FALTANTES[@]}"; do 
			echo "         $i  ";
			done
			echo "  * Elimine los componentes instalados e inténtelo nuevamente. *"
			echo "  *                                                            *"
			echo "  **************************************************************"
			exit 3;
	fi

fi

	# Consulta al usuario si esta de acuerdo con los terminos y condiciones de la instalacion
	$GRALOG instula I "Mostrando mensaje de Aceptación de términos y condiciones...";

			
echo '**************************************************************
* Proceso de Instalación del sistema Postulantes             *
*          Copyright TPSistemasOp (c)2011                    *
**************************************************************
* Al instalar POSTULA UD. expresa estar en un todo de acuerdo* 
* con los términos y condiciones del "ACUERDO DE LICENCIA DE *
* SOFTWARE" incluido en este paquete.                        *
**************************************************************';

	pregSINO "Acepta?"
	# Si el usuario no acepta finaliza el script
	if [ $respSINO = 0 ]; then
		$GRALOG instula I  "Usuario NO acepto ACUERDO DE LICENCIA DE SOFTWARE: Instalación Cancelada";
		exit 4;
	fi
	
	# Usuario Acepto los terminos
	$GRALOG instula I  "Usuario acepto ACUERDO DE LICENCIA DE SOFTWARE";

	# Verifica la instalacion de perl
	$GRALOG instula I "Verificando versión de Perl instalada...." 1
	PERLV=$(perl -v | grep 'v[0-9]\.[0-9]\+\.[0-9]*' -o); # obtengo la version de perl
	numPERLV=$(echo $PERLV | cut -d"." -f1 | sed 's/^v\([0-9]\)$/\1/'); #obtengo el primer numero

	#si perlv no existe o es menor a 5 mando error
	if [ -z "$numPERLV" ] || [ $numPERLV -lt 5 ] ; then
		msgPerl="**************************************************************
				 * Para instalar POSTULA es necesario contar previamente con  *
				 * Perl 5 o superior instalado.                               *
				 * Efectúe su instalación e inténtelo nuevamente              *
				 **************************************************************
				 Proceso de Instalación Cancelado"
		echo -e $msgPerl;
		$GRALOG instula E $msgPerl;
		exit 5;
	else
		$GRALOG instula I "PERL instalado. Version:$PERLV" 1
	fi
	
algo="seguir";
while [ ! -z $algo ]; do
	echo "Todos los directorios del sistema de postulantes serán subdirectorios de:" 
	echo $BASEDIR
	echo ""

	echo "Todos los componentes de la instalación se obtendrán del repositorio:" 
	echo $INSTDIR
	echo ""
	echo "Contenido del directorio:"
	ls $INSTDIR
	echo "" 

	echo "El archivo de configuración y el log de la instalación se registrarán en:" 
	echo $CONFDIR
	echo ""
	
# se almacena en la variable BINDIR el directorio q el usuario escriba y sino por defecto $BASEDIR/bin
	preguntarDirectorio "Ingrese el nombre del subdirectorio de ejecutables: (presione ENTER para dejar el subdirectorio por defecto /bin)" "$BASEDIR/bin"
	BINDIR=$dirSeleccionado
	echo $BINDIR
	
# se almacena en la variable ARRIDIR el directorio q el usuario escriba y sino por defecto $BASEDIR/arribos
	preguntarDirectorio "Ingrese el nombre del directorio que permite el arribo de archivos externos (presione ENTER para dejar el subdirectorio por defecto /arribos)" "$BASEDIR/arribos"
	ARRIDIR=$dirSeleccionado
	echo $ARRIDIR
	
		continuar=0;
		while [ $continuar -eq 0 ]; do
			# se almacena en la variable DATASIZE el espacio mínimo reservado para datos q el usuario ingrese y sino 200 Mb por defecto
			preguntarTamanio "Ingrese el espacio mínimo requerido para datos externos (en Mbytes): 200 Mb" 200
			DATASIZE=$tamanio
			echo $DATASIZE
	
			# calculo espacio libre en ARRIDIR
			$GRALOG instula I "Calculando espacio disponible..." 1
			#obtengo el espacio libre en el directorio(df -B). corto la unica linea que me devuelve,
			#reemplazo los espacios en blanco por ';' (sed) y hago un cut del tercer campo (cut)
			espacioLibre=$(df -B1024 "$BASEDIR" | tail -n1 | sed -e"s/\s\{1,\}/;/g" | cut -f4 -d';');
			espacioLibre=$(echo "scale=0 ; $espacioLibre/1024" | bc -l); #lo paso a Mb
			$GRALOG instula I "Espacio disponible en $ARRIDIR $espacioLibre Mb" 1 
			
			#si el espacio disponible en ARRIDIR es menor que el espacio minimo reservado para datos se informa el error y se vuelve al punto anterior	
			if [ $DATASIZE -gt $espacioLibre ] ; then
				 msgError="ERROR !:
	         	Insuficiente espacio en disco.
	         	Espacio disponible en $ARRIDIR $espacioLibre Mb. 
	         	Espacio requerido $DATASIZE Mb" 	
			 	$GRALOG instula E "$msgError" 1         	
	         
	         else
	         	continuar=1
			fi
		done	
	
	# se almcacena en la variable LOGDIR el directorio q el usuario escriba para los archivos de log de los comandos y sino $BASEDIR/log por defecto
	preguntarDirectorio "Ingrese el nombre del directorio de log: (presione ENTER para dejar el subdirectorio por defecto /log)" "$BASEDIR/log"
	LOGDIR=$dirSeleccionado
	echo $LOGDIR
	
	# se almacena en la variable LOGEXT la extension q el usuario escriba para los archivos de log y sino (.log) por defecto
	preguntarExtension "Ingrese la extensión para los archivos de log: (.log)" ".log"
	LOGEXT=$extSeleccionada
	echo $LOGEXT
	
	# se almacena en la variable LOGSIZE el tamaño maximo reservado para los archivos de log q el usuario ingrese y sino 500 KB por defecto
	preguntarTamanio "Ingrese el tamaño máximo para los archivos <LOGEXT> (en Kbytes): 500 KB" 500
	LOGSIZE=$tamanio
	echo $LOGSIZE
	
	# Mostrar estructura de directorios y parámetros configurados
		$GRALOG instula I "Mostrando estructura de directorios configurada";
		clear
	echo "****************************************************
* Parámetros de Instalación del paquete POSTULA		     *	
**********************************************************
 Directorio de trabajo: $BASEDIR
 Directorio de instalación: $INSTDIR
 Directorio de configuración: $CONFDIR
 Directorio de datos: $DATADIR
 Librería de ejecutables: $BINDIR
 Directorio de arribos: $ARRIDIR
 Espacio mínimo reservado en $ARRIDIR: $DATASIZE Mb
 Directorio para los archivos de Log: $LOGDIR
 Extensión para los archivos de Log: $LOGEXT
 Tamaño máximo para cada archivo de Log: $LOGSIZE Kb
 Log de la instalación: $CONFDIR/instula.log
	
 Si los datos ingresados son correctos oprima sólo ENTER para iniciar la instalación.
 Si desea modificar alguno de ellos oprima cualquier tecla.
**********************************************************"
	
		read -n1 algo
		if [ ! -z $algo ]; then
			$GRALOG instula I "El usuario decide modificar estructura de directorios configurada";
			
		else
			$GRALOG instula I "El usuario acepta estructura de directorios configurada";
						
		fi


done


# Confirmación Inicio Instalación
	$GRALOG instula I "Mostrando mensaje de Confirmación de la Instalación"
	pregSINO "Iniciando Instalación... Está UD. seguro?"
	# Si el usuario no acepta finaliza el script
	if [ $respSINO = 0 ]; then
		$GRALOG instula I  "Usuario No Confirma la Instalación: Instalación Cancelada";
		exit 6;
	fi
	
	# Usuario Acepto los terminos
	$GRALOG instula I  "Usuario acepto Confirmación de Instalación";
 
# Creación estructura de Directorios definida
	$GRALOG instula I "Creando Estructuras de Directorio......" 1
	
	DIRECTORIOS=( $BINDIR $ARRIDIR $LOGDIR $PROCESSED $REJECTED $RECEIVED);
	for i in ${DIRECTORIOS[*]}; do
		# Crea los directorios
		if [ ! -e $i -a ! -z $i ] 
		then
			mkdir -p -m u+x "$i" 
			$GRALOG instula I "	Se creo el directorio $i" 1 
		else
			if [ -z $i ];then
				$GRALOG instula I "	El directorio $i no está definido" 1
			else
				$GRALOG instula I "	El directorio $i ya existe" 1
			fi
		fi
	done

# Instalación
	# Variable que chequea si estan todos los componentes
	estaCompleto=true
	# Valida que todos los componentes esten disponibles en el directorio de instalación
	for i in ${COMANDOS[*]}; do
		if [ ! -e $INSTDIR/$i ]; then
		 	estaCompleto=false
			$GRALOG instula E "El componente $i no se encuentra o está corrupto, no se puede continuar la instalación" 1 
		fi
	done
	if [ $estaCompleto == "true" ]; then
		$GRALOG instula I "Moviendo Archivos..." 1
		# Instalando COMANDOS
		for i in ${COMANDOS[*]}; do
			instalarComando $i $BINDIR
		done
	fi
	
# Creación archivo de configuración
	crearConfiguracion

# Si existe elimino archivo comandos.temp
	if [ -e "$CONFDIR/comandos.temp" ]; then
		rm "$CONFDIR/comandos.temp";			
	fi


mensFinal="***************************************************************
* Se encuentran instalados los siguientes componentes:       *
* postini.sh  `date +%D`    `whoami`          			       
* postonio.sh  `date +%D`    `whoami`                  		   
* plist.pl `date +%D`    `whoami`                  		   
* postular.sh `date +%D`    `whoami`
* gralog.sh `date +%D`    `whoami`
* mover.sh `date +%D`    `whoami`
* killPostonio.sh `date +%D`    `whoami`
* startPostonio.sh `date +%D`    `whoami`                            
**************************************************************
* FIN del Proceso de Instalación de Postulantes			   *			
*          Copyright TPSistemasOp (c)2011                    *
**************************************************************";

	echo "$mensFinal"
	$GRALOG instula I "$mensFinal"

	exit 0;
# ------------------------------------------Fin Programa------------------------------------------
 
