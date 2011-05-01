#!/bin/bash

#Comando "POSTULAR"
#
#   ARCHIVOS DE INPUT
#       Busca los archivos recibidos de este path:
#       $grupo/recibidos/
#       Archivo de postulantes <codigo de agencia>.<secuencia>
#
#       Busca el archivo maestro de beneficios de este path:
#        $grupo/data/
#       Archivo de beneficios  beneficios.mae
#       
#
#   ARCHIVOs DE OUTPUT
#      Los archivos una vez procesado se mueve a 
#       $grupo/procesados/
#
#      Los Beneficiarios se guardan en este path :
#       $grupo/data/
#      registros exitosos      benef.<process id>
#      registros con errores   benerro.<process id>

#NOMBRE DEL COMANDO
nombre="postular"
#Motivos
errorCampo1="Campo"
errorCampo2="no informado"
motivoErrorFormato="Formato de registro erroneo"
#obtengo el processId
processId=$(echo "$$")

# 1.-VEO SI EXISTE OTRO POSTULAR CORRIENDO
proceso=$(ps x)
cantProcess=$(echo "$proceso" | grep -v "grep" | grep -v "obtpid" | grep -v "vi" | grep -v "gedit" | grep -c "$nombre.sh")

if [ $cantProcess -ge 2 ]; then
   # gragarloh.sh 
   echo "El proceso postular.sh ya se está ejecutando!"
   exit 1
fi

#2.- VEO SI SE INICIALIZO EL AMBIENTE

#isInicializado=$(verificarvar.sh)
isInicializado=1
if [ $isInicializado -eq 0 ]; then
	# gragarloh.sh 
    echo "Las variables de ambiente no se encuentran inicalizadas"
    exit 1
fi
#inicializo los path de los archivos
GRUPO="/home/oscar/workspace/TpSistemasOperativos/grupo10"
pathdata="$GRUPO/data"
pathRecibidos="$GRUPO/recibidos"
pathProcesados="$GRUPO/procesados"
pathBeneficiarios="$GRUPO/data/beneficios.mae"

#creo el pathProcesados si no estaban creados
if [ ! -e $pathProcesados ]; then
    mkdir $pathProcesados
fi

#si no existe el archivo lo crea
function verificarExisteArch(){
	if [ -f $1 ];
	then
	echo "$1"	
	else
	> $1
	fi	
}
function escribirError(){
var=`verificarExisteArch "$pathdata/benerro.$processId"`
echo " ERROR : $2"
echo $1 >> $pathdata/benerro.$processId
}
#3.- ----------------------------        PROCESO ARCHIVOS   -------------------------------------------------
# lo listo como columna los archivos y filtro lo que terminan en barra
archivos=$(ls -1p $pathRecibidos | grep -v /\$ )

#IFS=Separador de elementos de una lista. Normalmente espacio, tabulador y salto de carro

OldIFS=$IFS #guardo el IFS actual
IFS=$'\n' #pongo como IFS sólo el salto de linea
vector=($archivos) #creo el vector separando sólo con el IFS
IFS=$OldIFS #restauro el IFS anterior
cantArchivos=${#vector[@]}

  # gragarloh.sh  
  echo "Inicio postular <Cantidad de Archivos > : $cantArchivos"

for arch in ${vector[@]}
do
	
	
	
	
	echo " :::::::::::::   Proceso el Archivo : ${arch} :::::::::::::::::::::::::::::::::::"
#4.- PROCESO EL PRIMER ARCHIVO
  echo "Archivo a procesar: ${arch}"
  
       contador=0;
       contadorError=0;
       contadorNuevos=0;
       while read line
       do
       	contador=`expr $contador + 1`
        echo  "linea $contador"
        cantidadCampos=$(echo "$line" | awk -F, '{print NF }')
        agencia=$(echo "$arch" | awk -F. '{print $1 }')
        secuencia=$(echo "$arch" | awk -F. '{print $2 }')
        
        #4.1 VALIDAR A NIVEL REGISTRO #############################################

        if [ $cantidadCampos -lt 9 ] || [ $cantidadCampos -gt 11 ];then
        	contadorError=`expr $contadorError + 1`
        	registroNuevo="$agencia,$secuencia,$contador,$motivoErrorFormato,$line"
        	escribirError "$registroNuevo" "$motivoErrorFormato"
        fi
        if [ $cantidadCampos -le 11 ] && [ $cantidadCampos -ge 9 ];then
               #valido cuil
               cuil=$(echo "$line" | awk -F, '{print $1}')
               cantCaracteres=`expr length "$cuil"`
               if [ $cantCaracteres -ne 11 ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Cuil $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Cuil $errorCampo2"
               fi
               #valido Tipo doc
               tipoDoc=$(echo "$line" | awk -F, '{print $2}')
               if [ "$tipoDoc" != "DU" -a "$tipoDoc" != "LC" -a "$tipoDoc" != "LE" -a "$tipoDoc" != "PA" ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Tipo doc $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Tipo doc $errorCampo2"
               fi
               #valido Numero de documento
               numeroDoc=$(echo "$line" | awk -F, '{print $3}')
               cantCaracteres=`expr length "$numeroDoc"`
               if [ $cantCaracteres -ne 9 ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Numero doc $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Numero doc $errorCampo2"
               fi
                #valido Apellido
                apellido=$(echo "$line" | awk -F, '{print $4}')
               if [ -n "$apellido" ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Apellido $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Apellido $errorCampo2"
               fi
               #valido Nombre
               Nombre=$(echo "$line" | awk -F, '{print $5}')
               if [ -n "$Nombre" ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Nombre $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Nombre $errorCampo2"
               fi
               #valido Domicilio
               Domicilio=$(echo "$line" | awk -F, '{print $6}')
               if [ -n "$Domicilio" ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Domicilio $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Domicilio $errorCampo2"
               fi
               #valido Localidad
               Localidad=$(echo "$line" | awk -F, '{print $7}')
               if [ -n "$Localidad" ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Localidad $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Localidad $errorCampo2"
               fi
               #valido Provincia
               Provincia=$(echo "$line" | awk -F, '{print $8}')
               if [ -n "$Provincia" ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Provincia $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Provincia $errorCampo2"
               fi
               #valido Codigo de beneficio
               codBeneficio=$(echo "$line" | awk -F, '{print $9}')
               cantCaracteres=`expr length "$codBeneficio"`
               if [ $cantCaracteres -ne 5 ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Codigo de beneficio $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Codigo de beneficio $errorCampo2"
               fi
               
               #valido Apellido
               apellido=$(echo "$line" | awk -F, '{print $10}')
               if [ -n "$apellido" ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Apellido $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Apellido $errorCampo2"
               fi
               
       fi
        
        
        ##########################################################################
        var=$(echo "$line" | awk -F, '{print $1 "," $3}')
        #4.1.1 VALIDAR A NIVEL CAMPO
       done < "$pathRecibidos/$arch"
         
  
#FIN DE ARCHIVO
#MUEVO AL DIRECTORIO DE $GRUPO/PROCESADOS PARA EVITAR REPROCESAMIENTO
# MOVER.SH

#GRABARLOG.SH
echo "Cantidad Total de registros : $contador"
echo "Cantidad de registros con error : $contadorError"
echo "Cantidad de beneficiarios nuevos :$contadorNuevos"

echo " :::::::::::::   Fin del Archivo : :::::::::::::::::::::::::::::::::::"
done
# ------------------------------------------------ X -------------------------------------------------------
#CERRAR Y GRABAR LOG
#grabarlog.sh 
echo "Fin de Intérprete"
