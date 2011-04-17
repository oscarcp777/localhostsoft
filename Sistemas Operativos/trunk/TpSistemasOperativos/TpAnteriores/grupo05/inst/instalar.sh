#!/bin/bash
# Comando "instalar"
#Input
#         Archivos de la instalación
#Output
#         Comandos
#         Archivo de Configuración
#         Datos de Prueba
#         Tablas de Parámetros
#         Archivo de Log
#
#Valores de retorno
#	0 Exito
#	1 No se seteo la variable $GRUPO o se seteo en un directorio incorrecto
#	2 Usuario no acepto acuerdo de licencia de sowftware
#	3 Perl no esta instalado o su version es menor a la 5.0
#	4 Usuario no acepto continuar con el espacio disponible que posee
#	5 Faltan archivos necesarios para la instalacion
#	6 El archivo de configuracion se encuentra corrupto
#	7 Usuario no acepto la instalacion automatica de los componentes faltantes
	


#**********************************Funciones generales**********************************************
#pregUsuario: Realiza una pregunta al usuario del tipo (Si - No) y devuelve la respuesta
#Param: $1 = msj
#	$2 = pregunta
#	$3 = borrado de pantalla
#Retorno: Se guarda en la variables $respPregUsuario

respPregUsuario=""; #respuesta que devuelve la funcion
function pregUsuario(){
	local msj=$1;
	local pregunta=$2;
	local borrado=$3;
	local respVal="";
	
	echo "";
	$borrado;
	echo -e "$msj";
	while [ -z $respVal ]	#mientras no responda si o no
	do 
		read -p "$pregunta SI - NO: " resp; #leo la respuesta y la guardo en $resp
		respVal=$(echo $resp | grep '^[Ss][Ii]$\|^[Nn][Oo]$'); #valido que la respuesta sea si o no

	done
	#transformo la respuesta a minuscula
	resp=$(echo $respVal | sed 's/^[Ss][Ii]$/si/');
	
	#transformo la respuesta en un numero
	if [ $resp = "si" ]; then
		respPregUsuario=1;
	else
		respPregUsuario=0;
	fi
}

#crearConfiguracion: Crea el archivo de configurcaion
function crearConfiguracion(){
	echo "INSTDIR=/inst" > "$dirConf/$archConf"              	      	#1
	echo "FILECONF=/conf/$archConf" >> "$dirConf/$archConf" 
	echo "LOGFILE=/log/instalar.log" >> "$dirConf/$archConf" 
	echo "DATADIR=/$DATADIR" >> "$dirConf/$archConf" 
	echo "PERLVER=$PERLV" >> "$dirConf/$archConf" 
	MAXLOG=$(echo "$MAXLOG*1024" | bc)
	echo "MAXLOG=$MAXLOG" >> "$dirConf/$archConf" 
	echo "USIZE=$USIZE" >> "$dirConf/$archConf"				#7 
	echo " " >> "$dirConf/$archConf" 
	echo " " >> "$dirConf/$archConf" 
	declare -a COMANDOS;
	COMANDOS=( "mover.sh" "iniciar.sh" "detectar.sh" "interprete.sh" "reporte.pl" "glog.sh" "vlog.sh" "obtpid.sh" "envcheck.sh");
	for ((i=0;i<${#COMANDOS[*]};i++)); do
	    echo "COMAND = ${COMANDOS[$i]}" >> "$dirConf/$archConf"		      	#10
	    echo "BINDIR = /$BINDIR" >> "$dirConf/$archConf"
	    echo "USERID = `whoami`" >> "$dirConf/$archConf"
	    echo "FECINS = `date +%D`" >> "$dirConf/$archConf"
	    echo "LOGDIR = /$LOGDIR" >> "$dirConf/$archConf"
	    echo " " >> "$dirConf/$archConf" 
	done
}
#parsearValor()
#lee la linea pasada
function parsearValor() {
	head -n$1 $dirConf/$archConf | tail -n1 | sed -e "s/.*=//" -e "s/^ *//"
}

#instalarEjecutable
#copia el script a la carpeta $BINDIR y le asigna permisos
#Parametros: #1 = nombre del script a copiar
#	     #2 = directorio donde se copia el archivo
function instalarEjecutable() {
	local script=$1;
	local directorio=$2;
	#copio el script
	cp "$script" "$dirPrograma$directorio/$script"
	echo "$script movido a $dirPrograma$directorio/";		
	$log I "$script movido a $dirPrograma$directorio/";	

	#asigno permisos al script
	chmod u+x "$dirPrograma$directorio/$script"
	echo "Permisos de ejecución asignados al archivo $script";
	echo "";
	$log I "Permisos de ejecución asignados al archivo $script";

	#si el comando es el iniciar.sh le modifico la variable $GRUPO
	if [ "$script" = "iniciar.sh" ]; then
		#escribo $GRUPO 
    		sed -e "s:#GRUPO=\\\"ESTA RUTA LA MODIFICA EL INSTALADOR. NO TOCAR!\\\":GRUPO=\\\"$dirPrograma\\\":" "iniciar.sh" > "$dirPrograma$directorio/iniciar.sh"
	fi

}

#preguntarDirectorio
#valida que el comando pasado sea un directorio y solo un directorio. A/b/c no se permite
dirValidado="";
function preguntarDirectorio(){
	local resp="";
	while [ -z $resp ]; do
		read -p "Ingrese nueva ubicacion:$dirPrograma/" dirPasado;
		resp=$(echo $dirPasado | grep "^[A-Za-z0-9%@_=:.]\{1,\}$");
		if [ -z $resp ]; then 
			echo "";
			echo "El nombre de directorio $dirPasado es invalido";
		fi
	done
	dirValidado=$resp;
}

#*******************************************FIN - Funciones generales**************************************


#*******************************************Variables generales********************************************
msgError="Proceso de instalación cancelado";

#Variables de configuracion
PERLV="";
BINDIR="bin";
DATADIR="datos";
LOGDIR="log";
USIZE="Mb";
MAXLOG=0;

#****Directorios de la instalacion****
dirPrograma=$GRUPO"grupo05";
dirLogInst="$dirPrograma/log"; #directorio de log de instalacion
dirConf="$dirPrograma/conf"; #directorio de configuraciones

dirInst="$dirPrograma/inst"; #directorio donde se encuentran archivos de la instalacion

#****Archivos y comandos de la instalacion****
declare -a COM_INST; #comandos
declare -a ARCH_INST; #archivos
declare -a ARCH_OBLIGAT #ambos
COM_INST=( "glog.sh" "mover.sh" "detectar.sh" "vlog.sh" "iniciar.sh" "interprete.sh" "obtpid.sh" "reporte.pl" "envcheck.sh");
ARCH_CONF=(  "T1.tab" "T2.tab" );
ARCH_OBLIGAT=( ${COM_INST[*]} ${ARCH_CONF[*]}  );

archConf="practico.conf";

#****Comandos****
log="./glog.sh instalar"; #permite llamar con "log mensaje"

#***********************************************FIN - Variables Generales*************************************




#*****************INICIO PROGRAMA**************************
#verifico que la variable $GRUPO se haya seteado
if [ -z "$GRUPO" ]; then
	echo "";
	echo 'No se encuentra seteada la variable $GRUPO.'
	echo 'No se puede iniciar la instalación.';
	echo  'Por favor lea el archivo README.txt y vuelva a realizar la instalación';
	echo "";
	exit 1;
else
	GRUPO=$dirPrograma;
fi
#verifico que el directorio $dirInst exista
if [ ! -e "$dirInst" ]; then
	echo "";
	echo "El directorio $dirInst no existe"
	echo 'No se puede iniciar la instalación.';
	echo  'Por favor lea el archivo README.txt y vuelva a realizar la instalación';
	echo "";
	exit 1;
fi

#Creo el directorio /log
if [ ! -e $dirLogInst ]; then	
	mkdir $dirLogInst	
fi
#Creo el directorio /conf
if [ ! -e $dirConf ]; then	
	mkdir $dirConf	
fi

#Verifico que existan todos los archivos necesarios para la instalacion 
for ((i=0;i<${#ARCH_OBLIGAT[*]};i++)); do
	if [ ! -e ${ARCH_OBLIGAT[$i]} ] 
	then	
		echo "";
		echo "No se encontro el archivo ${ARCH_OBLIGAT[$i]} necesario para realizar la instalacíon"; 
		echo "";
		echo $msgError;
		echo "Verifique que ${ARCH_OBLIGAT[$i]} exista";
		echo "";
		exit 5;
	fi
done


#inicio ejecucion
$log I "Inicio de Ejecución";

#grabo el archivo de Log
$log I "Log de la instalación: ($dirLogInst/$archivoLog)";
$log I "Nombre del directorio de instalación: ($dirPrograma/inst/)";
$log I "Nombre del directorio de configuración: ($dirPrograma/conf/)";

#***Detecto si hay algun componente ya instalado***
$log I "Verificando versiones anteriores del programa ya instaladas...";
if [ -e "$dirConf/$archConf" ]; then 
#Hay una version instalada
	$log I "El programa ya se encuentra instalado";
	echo ""; echo "El programa ya se encuentra instalado";
	$log I "Verificando componentes ya instalados del programa...";
	echo "Verificando componentes ya instalados del programa...";
	
	#array con el nombre de los comandos que faltan
	declare -a COMANDOS_FALTANTES;
	declare -a DIR_COM_FALTANTES;
	indice=0; #indice del array
	
	#obtengo todos los comandos que hay y los guardo en comandos.temp
	cat "$dirConf/$archConf" | grep "COMAND = " -n | sed "s/COMAND = //" > "comandos.temp";

	
	#recorro todo el archivo comandos.temp
	for linea in $(cat "comandos.temp"); do	
		#obtengo el numero de linea donde arranco a leer el comando y el nombre del comando
		numLinea=$(echo $linea | cut -f1 -d":");
		comando=$(echo $linea | cut -f2 -d":");

		#Las demas caracteristicas de los comandos deben estar si o si contiguas
		j=$(echo "scale=0;$numLinea+1" | bc -l); #BINDIR
		k=$(echo "scale=0;$numLinea+2" | bc -l); #USERID
		l=$(echo "scale=0;$numLinea+3" | bc -l); #FECHA

		#Obtengo todos los parametros del comando
		dirComando=$(parsearValor $j);
		userComando=$(parsearValor $k);
		fecComando=$(parsearValor $l); 
		
		#sino estan contiguas el archivo esta corrupto	
		if [ -z "$dirComando" ] || [ -z "$userComando" ] || [ -z "$fecComando" ]; then
			echo "El archivo de configuracion se encuentra corrupto cercano a la linea $numLinea";
			echo "Las descripciones de los comandos deben estar contiguas";
			echo $msgError;

			$log E "El archivo de configuracion se encuentra corrupto cercano a la linea $numLinea";
			$log E $msgError;
			exit 6;
		fi


		#si el archivo existe
		if [ -e "$dirPrograma/$dirComando/$comando" ]; then 
			echo "Comando $comando instalado el $fecComando por $userComando";
			$log I "Comando $comando instalado el $fecComando por $userComando";
		else
			#guardo el nombre del comando que falta en un vector
			COMANDOS_FALTANTES=( ${COMANDOS_FALTANTES[*]} [$indice]=$comando );
			#guardo el directorio del comando
			DIR_COM_FALTANTES=( ${DIR_COM_FALTANTES[*]} [$indice]=$dirComando );

			indice=$(($indice+1));	
		fi
	done

	#elimino comandos.temp
	rm "comandos.temp";

	#Si no hay ningun comando faltante indicar al usuario que el programa esta correctamente instalado
	if [ -z $COMANDOS_FALTANTES ]; then
		echo "";
		echo "\"Practico\" se encuentra correctamente instalado!";
		$log I "\"Practico\" se encuentra correctamente instalado!";
		echo "Dirijase a la carpeta $dirPrograma/$BINDIR y ejecute el comando \". ./iniciar.sh\"";
		echo "";
		$log I "Fin de Ejecución";
		exit 0;	

	else
		echo "";
		echo  "Faltan instalar los siguientes componentes:"
		$log W "Faltan instalar los siguientes componentes: ${COMANDOS_FALTANTES[*]}";

		for i in "${COMANDOS_FALTANTES[@]}"; do 
			echo $i ;

		 done
		
		pregUsuario " " "Desea que el programa instale automaticamente los componentes que faltan?";
		if [ $respPregUsuario -eq 1 ]; then # acepto
			echo "Instalando componentes faltantes...";	
			$log I "Instalando componentes faltantes...";
			i=0;
			for com in "${COMANDOS_FALTANTES[@]}"; do 
				instalarEjecutable $com ${DIR_COM_FALTANTES[$i]} ;
				i=$(($i+1));
		 	done
			echo "Componentes correctamente instalados"		
			$log I "Componentes correctamente instalados"		
		else
			echo "";
			echo "Usuario cancelo instalación";
			echo $msgError;
			echo "";
			$log E "Usuario cancelo instalación";
			$log E "$msgError";
			exit 7;
		fi		
		
	fi

else #NO HAY NINGUNA INSTALACION ANTERIOR

	$log I "No hay ninguna version anterior instalada";
	$log I "Mostrando mensaje de Aceptacion de terminos y condiciones...";

	respVal="";
	while [ -z $respVal ]	#mientras no responda si o no
	do
		clear;
echo '***************************************************
*       Proceso de Instalación de "Practico"      *
*          Copyright TPSistemasOp (c)2009         *
***************************************************
A T E N C I O N: Al instalar Practico UD. expresa aceptar los términos y
Condiciones del "ACUERDO DE LICENCIA DE SOFTWARE" incluido en este paquete.';

		read -p "Acepta? SI - NO: " resp; #leo la respuesta y la guardo en $resp

		respVal=$(echo $resp | grep '^[Ss][Ii]$\|^[Nn][Oo]$'); #valido la respuesta 

	done

	#transformo la respuesta a minuscula
	respVal=$(echo $respVal | sed 's/^[Nn][Oo]$/no/');

	#si el usuario no acepta finalizo el script
	if [ $respVal = "no" ]; then
		$log I  "Usuario NO acepto ACUERDO DE LICENCIA DE SOFTWARE";
		$log E "$msgError";
		exit 2;
	fi
	
	#Usuario Acepto los terminos
	$log I  "Usuario acepto ACUERDO DE LICENCIA DE SOFTWARE";


	#***Chequeo la instalacion de perl***
	$log I "Verificando versión de Perl instalada....";
	echo "Verificando versión de Perl instalada....";
        PERLV=$(perl -v | grep 'v[0-9]\.[0-9]\+\.[0-9]*' -o); #obtengo la version de perl
	numPERLV=$(echo $PERLV | cut -d"." -f1 | sed 's/^v\([0-9]\)$/\1/'); #obtengo el primer numero

	#si perlv no existe o es menor a 5 mando error
	if [ -z "$numPERLV" ] || [ $numPERLV -lt 5 ] ; then
		msgPerl="ATENCION! Esta instalación solo puede ser ejecutada si Perl 5 o superior esta instalado.\n	Efectúe la instalación de Perl y reinicie el proceso de instalación."
		echo -e $msgPerl;
		$log E $msgPerl;
		exit 3;
	else
		echo "PERL instalado. Version:$PERLV";
		$log I "PERL instalado. Version:$PERLV";
	fi
	
	#ANCLA desde donde vuelvo a arrancar sino esta de acuerdo con la instalacion
	instalar=0;
	while [ $instalar -eq 0 ]; do
		#***Defino directorio de ejecutables***
		$log I "Definiendo directorio de ejecutables....";
		pregUsuario "Nombre del directorio de ejecutables: ($dirPrograma/$BINDIR)" "Desea Modificarlo?";
		if [ $respPregUsuario -eq 1 ]; then # acepto
			preguntarDirectorio;
			BINDIR=$dirValidado;
		
		fi
		$log I "Directorio de ejecutables: $dirPrograma/$BINDIR/";

		#***Defino el directorio de datos***
		$log I "Definiendo directorio de datos....";
		pregUsuario "Nombre del directorio de datos: ($dirPrograma/$DATADIR)" "Desea Modificarlo?";
		if [ $respPregUsuario -eq 1 ]; then # acepto
			preguntarDirectorio;
			DATADIR=$dirValidado;
		fi
		$log I "Directorio de datos: $dirPrograma/$DATADIR/";
	
		#***Espacio libre en DATADIR***
		$log I "Calculando espacio disponible...";
		#obtengo el espacio libre en el directorio(df -B). corto la unica linea que me devuelve,
		#reemplazo los espacios en blanco por ';' (sed) y hago un cut del tercer campo (cut)
		DATASIZE=$(df -B1024 "$dirPrograma" | tail -n1 | sed -e"s/\s\{1,\}/;/g" | cut -f4 -d';');
		DATASIZE=$(echo "scale=0 ; $DATASIZE/1024" | bc -l); #lo paso a Mb
	
		$log I "Espacio disponible en $dirPrograma/$DATADIR/: $DATASIZE $USIZE";
		pregUsuario "Espacio disponible en $dirPrograma/$DATADIR/: $DATASIZE $USIZE" "Desea continuar?"
		if [ $respPregUsuario -eq 0 ]; then # NO acepto
			$log E "Usuario NO acepto continuar con $DATASIZE $USIZE de espacio disponible";
			$log E "$msgError";
			exit 4;
		fi
		$log I "Usuario acepto continuar con el espacio disponible dado";
	
		#***Defino el directorio de logs***
		$log I "Definiendo directorio de logs para los comandos....";
		pregUsuario "Nombre del directorio de log: ($dirPrograma/$LOGDIR)" "Desea Modificarlo?";
		if [ $respPregUsuario -eq 1 ]; then # acepto
			preguntarDirectorio;
			LOGDIR=$dirValidado;
		fi
		$log I "Directorio de logs: $dirPrograma/$LOGDIR/";
	
		#***Defino espacio maximo para archivos de logs ***
		$log I "Definiendo espacio maximo para archivos de logs....";
		if [ $MAXLOG -eq 0 ]; then
			MAXLOG=$(echo "scale=0 ; $DATASIZE/100" | bc -l); #1% DE $DATASIZE
		fi
		fin=0;
		while [ $fin -eq 0 ]; do
			pregUsuario "Espacio máximo para archivos de log? ($MAXLOG $USIZE)" "Desea Modificarlo?"
			if [ $respPregUsuario -eq 1 ]; then # Lo modifica
				read -p "Ingrese nueva valor en $USIZE: " resp;
				#valido que sea un numero
				respVal=$(echo $resp | grep "^[0-9]*$");
				if [ $respVal ]; then
					#tiene que ser menor a $MAXIMO
					MAXIMO=$(echo "scale=0 ; $DATASIZE/100" | bc -l); #1% DE $DATASIZE
					if [ $respVal -gt $MAXIMO ]; then
						echo "Valor Incorrecto. El maximo permitido es $MAXIMO $USIZE";
					else
						fin=1;
						MAXLOG=$respVal;
					fi
				else
					echo "Por favor ingrese un número entero";
				fi
			else
				fin=1;
			fi
		done
		$log I "Espacio para archivos de logs: $MAXLOG $USIZE";

		msjConf="\"PARÁMETROS DE INSTALACION DE PRACTICO\"\nVersión de Perl: $PERLV\nNombre del directorio de instalación: $dirPrograma/inst\nNombre del directorio de configuración: $dirPrograma/conf\nNombre del directorio de ejecutables: $dirPrograma/$BINDIR\nNombre del directorio de datos: $dirPrograma/$DATADIR\nNombre del directorio de logs: $dirPrograma/$LOGDIR\nEspacio máximo para archivos de log: $MAXLOG $USIZE\n";
		pregUsuario "$msjConf" "Continuar instalación?" clear;

		if [ $respPregUsuario -eq 1 ]; then # acepto instalar
			instalar=1;
			$log I "Usuario acepto instalar el programa con los parametros configurados";
		else
			$log W "Usuario NO acepto instalar el programa con los parametros configurados";
			clear;
		fi

	done #FIN de preguntas de la instalacion

	#********COMIENZO A INSTALAR***********

	#***Creo estructura de directorios***
	echo "";
	echo "Creando Estructura de Directorio.......";
	$log I "Creando Estructura de Directorio.......";
	
	#creo un array con todos los directorios a crear
	declare -a DIRECTORIOS;
	DIRECTORIOS=( $BINDIR $DATADIR $LOGDIR);
	for ((i=0;i<3;i++)); do
		#creo los directorios
		if [ ! -e "$dirPrograma/${DIRECTORIOS[$i]}" ] 
		then
			mkdir  "$dirPrograma/${DIRECTORIOS[$i]}";
			echo "Se creo el directorio $dirPrograma/${DIRECTORIOS[$i]}";
			$log I "Se creo el directorio $dirPrograma/${DIRECTORIOS[$i]}";
		else
			$log I "El directorio $dirPrograma/${DIRECTORIOS[$i]} ya existe";
			echo "El directorio $dirPrograma/${DIRECTORIOS[$i]} ya existe";
		fi
	done
	echo "Estructura de Directorio creada.";
	$log I "Estructura de Directorio creada.";
	echo "";
	
	#***Muevo archivos necesarios***
	echo "Moviendo archivos de ejecución y asignando permisos.......";
	$log I "Moviendo archivos de ejecución y asignando permisos.......";
	for((i=0;i<${#COM_INST[*]};i++)); do
		instalarEjecutable ${COM_INST[$i]} "/$BINDIR"
	done

	echo "Archivos de ejecución movidos.";
	$log I "Archivos de ejecución movidos.";
	echo "Permisos asignados.......";
  	$log I "Permisos asignados.......";
	echo "";

	echo "Moviendo archivos de configuración.......";
	$log I "Moviendo archivos de configuración.......";
	#*.tab
	cp *.tab $dirConf;
	
	#PPI.mae (no siempre existe)
	if [ -e "PPI.mae" ]; then
		#creo el directorio y despues guardo el archivo
		if [ ! -e "$dirPrograma/$DATADIR/mae" ]; then	
			mkdir "$dirPrograma/$DATADIR/mae"	
		fi
		cp "PPI.mae" "$dirPrograma/$DATADIR/mae";
	fi

	echo "Archivos de configuración movidos.";
	$log I "Archivos de configuración movidos.";
	echo "";

	#***Guardo informacion de la instalacion***
	echo "Guardando información de la instalación.......";
	$log I "Guardando información de la instalación.......";
	crearConfiguracion;
	echo "Información de la instalación guardada";
	$log I "Información de la instalación guardada";

	#***Borro archivos temporales***

	#***Muestro mensaje con todo lo instalado
	echo "";
	echo "Componentes instalados:"
	echo ${COM_INST[*]};
	echo ${ARCH_CONF[*]}
	$log I "Componentes instalados:"
	$log I "${COM_INST[*]}";
	$log I "${ARCH_CONF[*]}";

fi

echo "";
echo "Instalación de \"Practico\" finalizo correctamente!";
echo "Para empezar a utilizarlo dirijase a la carpeta $dirPrograma/$BINDIR y ejecute el comando \". ./iniciar.sh\"";
echo "";


#***Finalizo instalacion
$log I "Fin de Ejecución";

exit 0;
