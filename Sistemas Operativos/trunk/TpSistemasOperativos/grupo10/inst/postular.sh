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
# ------------------------------------------Comandos------------------------------------------
GRALOG=./gralog.sh
#NOMBRE DEL COMANDO
nombre="postular"
#Motivos
errorCampo1="Campo"
errorCampo2="no informado"
motivoErrorFormato="Formato de registro erroneo"
#obtengo el processId
processId=$(echo "$$")
usuario="usuario loqueado"
# 1.-VEO SI EXISTE OTRO POSTULAR CORRIENDO
proceso=$(ps x)
cantProcess=$(echo "$proceso" | grep -v "grep" | grep -v "obtpid" | grep -v "vi" | grep -v "gedit" | grep -c "$nombre.sh")

if [ $cantProcess -ge 2 ]; then
   # gragarloh.sh 
   echo "El proceso postular.sh ya se está ejecutando!"
   $GRALOG postular SE "El proceso postular.sh ya se está ejecutando!" 1
   exit 1
fi

#2.- VEO SI SE INICIALIZO EL AMBIENTE

#isInicializado=$(verificarvar.sh)
isInicializado=1
if [ $isInicializado -eq 0 ]; then
	# gragarloh.sh 
    $GRALOG postular SE "Las variables de ambiente no se encuentran inicalizadas" 1
    exit 1
fi
#inicializo los path de los archivos
GRUPO="/home/oscar/workspace/TpSistemasOperativos/grupo10"
pathdata="$GRUPO/data"
pathRecibidos="$GRUPO/recibidos"
pathProcesados="$GRUPO/procesados"
pathBeneficiarios="$GRUPO/data/beneficios.mae"
ESTADO_RECHAZADO=rechazado
ESTADO_PENDIENTE=pendiente
ESTADO_APROBADO=aprobado	
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

#validar fecha
#retorna 0 si no hay error y 1 si lo hay
function validarFecha(){
    cantCampos=$(echo "$1" | awk -F- '{print NF}')
	    if [  $cantCampos -ne 3 ];then
	       return=1
	    else
	        year=$(echo "$1" | awk -F- '{print $1}')
	        mes=$(echo "$1" | awk -F- '{print $2}')
	        dia=$(echo "$1" | awk -F- '{print $3}')
	        isyear=$(echo $year | grep "^[0-9]*$")
	        ismes=$(echo $mes | grep "^[0-9]*$")
	        isdia=$(echo $dia | grep "^[0-9]*$")
	        if [ -n $isyear ] && [ -n $isyear ] && [ -n $isyear ]; then
	           if [ $dia -lt 1 ] || [ $dia -gt 31 ] || [ $mes -lt 1 ] || [ $mes -gt 12 ] || [ $year -lt 0 ] ; then
	        	return=1
	           else
	            return=0
	           fi	
	        fi
	    fi

	echo $return
}
function compararFechas(){
        year1=$(echo "$1" | awk -F- '{print $1}')
	    mes1=$(echo "$1" | awk -F- '{print $2}')
	    dia1=$(echo "$1" | awk -F- '{print $3}')
	    year2=$(echo "$2" | awk -F- '{print $1}')
	    mes2=$(echo "$2" | awk -F- '{print $2}')
	    dia2=$(echo "$2" | awk -F- '{print $3}')
        if [ $dia1 -ge $dia2 ] && [ $mes1 -ge $mes2 ] && [ $year1 -ge $year2 ] ; then
	       	return=1
	    else
	        return=0
	    fi
        if [ $dia1 -eq $dia2 ] && [ $mes1 -eq $mes2 ] && [ $year1 -eq $year2 ] ; then
	       	return=0
        fi   	
  echo $return
}
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
function calcularFechaEfectiva(){
	  fechaEfectiva=`date +%Y-%m-%d`
	  esFechMayor=`compararFechas $1 $2`
      if [ $esFechMayor -eq 1 ] ; then
         fechaEfectiva=$1
      else
         fechaEfectiva=$2
      fi
      esFechMayor=`compararFechas $3 $fechaEfectiva`
      if [ $esMayor -eq 1 ] ; then
         fechaEfectiva=$3
      fi
      echo $fechaEfectiva
}
function escribirError(){
var=`verificarExisteArch "$pathdata/benerro.$processId"`
$GRALOG postular E "ERROR : $2" 1
echo $1 >> $pathdata/benerro.$processId
}
function escribirBeneficiario(){
var=`verificarExisteArch "$pathdata/benef.$processId"`
echo $1 >> $pathdata/benef.$processId
}
function calcularFechaFinalizacion(){
	  FEA=$1
	  duracion=$2
	  FFB=$3
      fechaEfectivaAltaMAsDuracion=`sumaMes "$FEA" "$duracion"`
      esMayor=`compararFechas $fechaEfectivaAltaMAsDuracion $FFB`
      if [ $esMayor -eq 1 ];then
       fechaFinalizacion=$FFB
      else
      fechaFinalizacion=$fechaEfectivaAltaMAsDuracion
      fi
      echo $fechaFinalizacion
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
  $GRALOG postular I "Inicio postular <Cantidad de Archivos > : $cantArchivos" 1
  
for arch in ${vector[@]}
do
	
	
	
	
#	echo " :::::::::::::   Proceso el Archivo : ${arch} :::::::::::::::::::::::::::::::::::"
#4.- PROCESO EL PRIMER ARCHIVO
  
    $GRALOG postular I "Archivo a procesar: ${arch}" 1
       contador=0
       contadorError=0
       contadorNuevos=0
       beneficio=""
       duracionMaxBeneficio=0
       fechaFinBeneficio=""
       fechaInicioBeneficio=""
       fechaCorriente=`date +%Y-%m-%d`
       fechaPedidaAlta=`date +%Y-%m-%d`
       estado=$ESTADO_APROBADO
       motivoEstado="Registro con campos validos"
       while read line
       do
       	contador=`expr $contador + 1`
       		
     #   echo  "linea $contador"
        cantidadCampos=$(echo "$line" | awk -F, '{print NF }')
        agencia=$(echo "$arch" | awk -F. '{print $1 }')
        secuencia=$(echo "$arch" | awk -F. '{print $2 }')
        
        #4.1 VALIDAR A NIVEL REGISTRO #############################################
        if [ $cantidadCampos -lt 9 ] || [ $cantidadCampos -gt 11 ];then
        	contadorError=`expr $contadorError + 1`
        	registroNuevo="$agencia,$secuencia,$contador,$motivoErrorFormato,$line"
        	escribirError "$registroNuevo" "$motivoErrorFormato"
        	continue
        fi
        if [ $cantidadCampos -le 11 ] && [ $cantidadCampos -ge 9 ];then
               #valido cuil
               cuil=$(echo "$line" | awk -F, '{print $1}')
               cantCaracteres=`expr length "$cuil"`
               if [ $cantCaracteres -ne 11 ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Cuil $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Cuil $errorCampo2"
        	      continue
               fi
               #valido Tipo doc
               tipoDoc=$(echo "$line" | awk -F, '{print $2}')
               if [ "$tipoDoc" != "DU" -a "$tipoDoc" != "LC" -a "$tipoDoc" != "LE" -a "$tipoDoc" != "PA" ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Tipo doc $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Tipo doc $errorCampo2"
        	      continue
               fi
               #valido Numero de documento
               numeroDoc=$(echo "$line" | awk -F, '{print $3}')
               cantCaracteres=`expr length "$numeroDoc"`
               if [ $cantCaracteres -ne 9 ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Numero doc $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Numero doc $errorCampo2"
        	      continue
               fi
                #valido Apellido
                apellido=$(echo "$line" | awk -F, '{print $4}')
               if [ -z "$apellido" ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Apellido $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Apellido $errorCampo2"
        	      continue
               fi
               #valido Nombre
               Nombre=$(echo "$line" | awk -F, '{print $5}')
               if [ -z "$Nombre" ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Nombre $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Nombre $errorCampo2"
        	      continue
               fi
               #valido Domicilio
               Domicilio=$(echo "$line" | awk -F, '{print $6}')
               if [ -z "$Domicilio" ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Domicilio $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Domicilio $errorCampo2"
        	      continue
               fi
               #valido Localidad
               Localidad=$(echo "$line" | awk -F, '{print $7}')
               if [ -z "$Localidad" ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Localidad $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Localidad $errorCampo2"
        	      continue
               fi
               #valido Provincia
               Provincia=$(echo "$line" | awk -F, '{print $8}')
               if [ -z "$Provincia" ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Provincia $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Provincia $errorCampo2"
        	      continue
               fi
               #valido Codigo de beneficio
               codBeneficio=$(echo "$line" | awk -F, '{print $9}')
               cantCaracteres=`expr length "$codBeneficio"`
               if [ $cantCaracteres -ne 5 ];then
               	  contadorError=`expr $contadorError + 1`
            	  registroNuevo="$agencia,$secuencia,$contador,$errorCampo1 Codigo de beneficio $errorCampo2,$line"
        	      escribirError "$registroNuevo" "$errorCampo1 Codigo de beneficio $errorCampo2"
        	      continue
               fi
                if [ $cantCaracteres -eq 5 ];then
                   codigos=$(cut -d ',' -f2 $pathBeneficiarios)
                   existe=$(echo "$codigos" | grep -c "$codBeneficio")
                   beneficio=$(grep "$codBeneficio" $pathBeneficiarios)
                   duracionMaxBeneficio=$(echo "$beneficio" | awk -F, '{print $6}')
                   fechaFinBeneficio=$(echo "$beneficio" | awk -F, '{print $5}')
                   fechaInicioBeneficio=$(echo "$beneficio" | awk -F, '{print $4}')
                   if [ $existe -ne 1 ];then
                   	contadorError=`expr $contadorError + 1`
                    estado=$ESTADO_RECHAZADO
        	        motivoEstado="No existe el beneficio: $codBeneficio"
        	        fechaEfectivaAlta=`calcularFechaEfectiva $fechaInicioBeneficio $fechaCorriente $fechaCorriente`
                    fechaFinalizacion=`calcularFechaFinalizacion $fechaEfectivaAlta $duracionMaxBeneficio $fechaFinBeneficio`
                    reg1="$agencia,$secuencia,$cuil,$tipoDoc,$apellido,$Nombre,$Domicilio,$Localidad,$Provincia,$codBeneficio,$fechaCorriente,"
                    reg2="$fechaEfectivaAlta,$estado,$duracionMaxBeneficio,$fechaFinalizacion,$motivoEstado,$usuario,$fechaCorriente"
                    beneficiarioNuevo="$reg1$reg2"
                    escribirBeneficiario "$beneficiarioNuevo"
                    continue
                   fi

                   
                fi
              
               if [ $cantidadCampos -eq 10 ];then
                  campo10=$(echo "$line" | awk -F, '{print $10}')
                  cantCaracteres=`expr length "$campo10"`
                    #valido fecha pedida de alta
                  if [ $cantCaracteres -eq 10 ];then
                  	 fechaValida=`validarFecha $campo10`
                     if [ $fechaValida -eq 1 ];then
               	     contadorError=`expr $contadorError + 1`
        	         estado=$ESTADO_RECHAZADO
        	         motivoEstado="Fecha Pedida de Alta Invalido"
        	         fechaEfectivaAlta=`calcularFechaEfectiva $fechaInicioBeneficio $fechaCorriente $campo10`
                     fechaFinalizacion=`calcularFechaFinalizacion $fechaEfectivaAlta $duracionMaxBeneficio $fechaFinBeneficio`
                     reg1="$agencia,$secuencia,$cuil,$tipoDoc,$apellido,$Nombre,$Domicilio,$Localidad,$Provincia,$codBeneficio,$campo10,"
                     reg2="$fechaEfectivaAlta,$estado,$duracionMaxBeneficio,$fechaFinalizacion,$motivoEstado,$usuario,$fechaCorriente"
                     beneficiarioNuevo="$reg1$reg2"
                     escribirBeneficiario "$beneficiarioNuevo"
        	         continue
                     else
                        esMayor=`compararFechas $campo10 $fechaFinBeneficio`
                       if [ $esMayor -eq 1 ];then
                       	  contadorError=`expr $contadorError + 1`
        	              estado=$ESTADO_RECHAZADO
        	              motivoEstado="Fecha Pedida de Alta mayor a Fecha Fin Beneficio"
        	              fechaEfectivaAlta=`calcularFechaEfectiva $fechaInicioBeneficio $fechaCorriente $campo10`
                          fechaFinalizacion=`calcularFechaFinalizacion $fechaEfectivaAlta $duracionMaxBeneficio $fechaFinBeneficio`
                          reg1="$agencia,$secuencia,$cuil,$tipoDoc,$apellido,$Nombre,$Domicilio,$Localidad,$Provincia,$codBeneficio,$campo10,"
                          reg2="$fechaEfectivaAlta,$estado,$duracionMaxBeneficio,$fechaFinalizacion,$motivoEstado,$usuario,$fechaCorriente"
                          beneficiarioNuevo="$reg1$reg2"
                          escribirBeneficiario "$beneficiarioNuevo"
        	              continue
                       fi
                       fechaPedidaAlta=$campo10
        	         fi
        	      else
        	       #valido Duracion pedida
        	            esDuracion=$(echo $campo10 | grep "^[0-9]*$")
            	      if [ -z $esDuracion  ];then
            	      	 contadorError=`expr $contadorError + 1`
            	      	 estado=$ESTADO_RECHAZADO
        	             motivoEstado="Duracion pedida invalida"
        	              fechaEfectivaAlta=`calcularFechaEfectiva $fechaInicioBeneficio $fechaCorriente $fechaCorriente`
                          fechaFinalizacion=`calcularFechaFinalizacion $fechaEfectivaAlta $duracionMaxBeneficio $fechaFinBeneficio`
                          reg1="$agencia,$secuencia,$cuil,$tipoDoc,$apellido,$Nombre,$Domicilio,$Localidad,$Provincia,$codBeneficio,$fechaCorriente,"
                          reg2="$fechaEfectivaAlta,$estado,$duracionMaxBeneficio,$fechaFinalizacion,$motivoEstado,$usuario,$fechaCorriente"
                          beneficiarioNuevo="$reg1$reg2"
                          escribirBeneficiario "$beneficiarioNuevo"
        	              continue
            	      else
            	          if [ $campo10 -gt $duracionMaxBeneficio ];then
            	             contadorError=`expr $contadorError + 1`
            	              estado=$ESTADO_RECHAZADO
        	                  motivoEstado="Duracion pedida mayor a duracion Maxima Beneficio"
        	                 fechaEfectivaAlta=`calcularFechaEfectiva $fechaInicioBeneficio $fechaCorriente $fechaCorriente`
                             fechaFinalizacion=`calcularFechaFinalizacion $fechaEfectivaAlta $duracionMaxBeneficio $fechaFinBeneficio`
                             reg1="$agencia,$secuencia,$cuil,$tipoDoc,$apellido,$Nombre,$Domicilio,$Localidad,$Provincia,$codBeneficio,$fechaCorriente,"
                             reg2="$fechaEfectivaAlta,$estado,$duracionMaxBeneficio,$fechaFinalizacion,$motivoEstado,$usuario,$fechaCorriente"
                             beneficiarioNuevo="$reg1$reg2"
                             escribirBeneficiario "$beneficiarioNuevo"
        	                 continue
        	                  
            	          fi	
            	      fi
                  fi        	        
        	   fi
               if [ $cantidadCampos -eq 11 ];then
        	            fechaPedida=$(echo "$line" | awk -F, '{print $10}')
                        cantCaracteres=`expr length "$fechaPedida"`
                       #valido fecha pedida de alta
                      if [ $cantCaracteres -eq 10 ];then
                  	     fechaValida=`validarFecha $fechaPedida`
                         if [ $fechaValida -eq 1 ];then
               	            contadorError=`expr $contadorError + 1`
            	            estado=$ESTADO_RECHAZADO
        	                motivoEstado="Fecha Pedida de Alta Invalido"
        	                fechaEfectivaAlta=`calcularFechaEfectiva $fechaInicioBeneficio $fechaCorriente $fechaPedida`
                            fechaFinalizacion=`calcularFechaFinalizacion $fechaEfectivaAlta $duracionMaxBeneficio $fechaFinBeneficio`
                            reg1="$agencia,$secuencia,$cuil,$tipoDoc,$apellido,$Nombre,$Domicilio,$Localidad,$Provincia,$codBeneficio,$fechaPedida,"
                            reg2="$fechaEfectivaAlta,$estado,$duracionMaxBeneficio,$fechaFinalizacion,$motivoEstado,$usuario,$fechaCorriente"
                            beneficiarioNuevo="$reg1$reg2"
                            escribirBeneficiario "$beneficiarioNuevo"
        	                continue
        	                
                         else
                             esMayor=`compararFechas $fechaPedida $fechaFinBeneficio`
                             if [ $esMayor -eq 1 ];then
                       	        contadorError=`expr $contadorError + 1`
        	                    estado=$ESTADO_RECHAZADO
        	                    motivoEstado="Fecha Pedida de Alta mayor a Fecha Fin Beneficio"
        	                    fechaEfectivaAlta=`calcularFechaEfectiva $fechaInicioBeneficio $fechaCorriente $fechaPedida`
                                fechaFinalizacion=`calcularFechaFinalizacion $fechaEfectivaAlta $duracionMaxBeneficio $fechaFinBeneficio`
                                reg1="$agencia,$secuencia,$cuil,$tipoDoc,$apellido,$Nombre,$Domicilio,$Localidad,$Provincia,$codBeneficio,$fechaPedida,"
                                reg2="$fechaEfectivaAlta,$estado,$duracionMaxBeneficio,$fechaFinalizacion,$motivoEstado,$usuario,$fechaCorriente"
                                beneficiarioNuevo="$reg1$reg2"
                                escribirBeneficiario "$beneficiarioNuevo"
        	                    continue
                             fi
                         fi
                      fechaPedidaAlta=$fechaPedida
        	          fi
        	   
        	       #valido Duracion pedida
                        duracionPedida=$(echo "$line" | awk -F, '{print $11}')
        	            esDuracion=$(echo $duracionPedida | grep "^[0-9]*$")
            	      if [ -z $esDuracion  ];then
            	      	 contadorError=`expr $contadorError + 1`
            	      	 estado=$ESTADO_RECHAZADO
        	             motivoEstado="Duracion pedida invalida"
        	              fechaEfectivaAlta=`calcularFechaEfectiva $fechaInicioBeneficio $fechaCorriente $fechaPedidaAlta`
                          fechaFinalizacion=`calcularFechaFinalizacion $fechaEfectivaAlta $duracionMaxBeneficio $fechaFinBeneficio`
                          reg1="$agencia,$secuencia,$cuil,$tipoDoc,$apellido,$Nombre,$Domicilio,$Localidad,$Provincia,$codBeneficio,$fechaPedidaAlta,"
                          reg2="$fechaEfectivaAlta,$estado,$duracionMaxBeneficio,$fechaFinalizacion,$motivoEstado,$usuario,$fechaCorriente"
                          beneficiarioNuevo="$reg1$reg2"
                          escribirBeneficiario "$beneficiarioNuevo"
        	              continue
            	      else
            	           if [ $duracionPedida -ge $duracionMaxBeneficio ];then
            	             contadorError=`expr $contadorError + 1`
            	              estado=$ESTADO_RECHAZADO
        	                  motivoEstado="Duracion pedida mayor a duracion Maxima Beneficio"
        	                 fechaEfectivaAlta=`calcularFechaEfectiva $fechaInicioBeneficio $fechaCorriente $fechaPedidaAlta`
                             fechaFinalizacion=`calcularFechaFinalizacion $fechaEfectivaAlta $duracionMaxBeneficio $fechaFinBeneficio`
                             reg1="$agencia,$secuencia,$cuil,$tipoDoc,$apellido,$Nombre,$Domicilio,$Localidad,$Provincia,$codBeneficio,$fechaPedidaAlta,"
                             reg2="$fechaEfectivaAlta,$estado,$duracionMaxBeneficio,$fechaFinalizacion,$motivoEstado,$usuario,$fechaCorriente"
                             beneficiarioNuevo="$reg1$reg2"
                             escribirBeneficiario "$beneficiarioNuevo"
        	                 continue
            	          fi
            	      fi
                    
               fi
       fi
        
        
        ##########################################################################
        #termino las validaciones escribo el registro de beneficiarios nuevos        
        estado=$ESTADO_APROBADO
        motivoEstado="Postulante valido"
        fechaEfectivaAlta=`calcularFechaEfectiva $fechaInicioBeneficio $fechaCorriente $fechaPedidaAlta`
         esMayor=`compararFechas $fechaEfectivaAlta $fechaCorriente`
         if [ $esMayor -eq 1 ];then
         estado=$ESTADO_PENDIENTE
         fi
         fechaFinalizacion=`calcularFechaFinalizacion $fechaEfectivaAlta $duracionMaxBeneficio $fechaFinBeneficio`
         reg1="$agencia,$secuencia,$cuil,$tipoDoc,$apellido,$Nombre,$Domicilio,$Localidad,$Provincia,$codBeneficio,$fechaPedidaAlta,"
         reg2="$fechaEfectivaAlta,$estado,$duracionMaxBeneficio,$fechaFinalizacion,$motivoEstado,$usuario,$fechaCorriente"
         beneficiarioNuevo="$reg1$reg2"
         contadorNuevos=`expr $contadorNuevos + 1`
         escribirBeneficiario "$beneficiarioNuevo"
  
        #4.1.1 VALIDAR A NIVEL CAMPO
       done < "$pathRecibidos/$arch"
         
  
#FIN DE ARCHIVO
#MUEVO AL DIRECTORIO DE $GRUPO/PROCESADOS PARA EVITAR REPROCESAMIENTO
# MOVER.SH

#GRABARLOG.SH
 $GRALOG postular I "Cantidad Total de registros : $contador" 1
 $GRALOG postular I "Cantidad de registros con error : $contadorError" 1
 $GRALOG postular I "Cantidad de beneficiarios nuevos :$contadorNuevos" 1



#echo " :::::::::::::   Fin del Archivo : :::::::::::::::::::::::::::::::::::"
done
# ------------------------------------------------ X -------------------------------------------------------
#CERRAR Y GRABAR LOG
#grabarlog.sh 
echo "Fin de Intérprete"
