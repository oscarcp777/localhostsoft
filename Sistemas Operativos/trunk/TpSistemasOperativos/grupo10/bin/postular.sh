#!/bin/bash

#Comando "POSTULAR"
#
#   ARCHIVOS DE INPUT
#       Busca los archivos recibidos de este path:
#       $grupo/recibidos/
#       Archivo de beneficios  beneficios.mae
#       Archivo de postulantes <codigo de agencia>.<secuencia>
#       separador de campos ","
#
#   ARCHIVO DE OUTPUT
#      El archivo una vez procesado se mueve a 
#       $grupo/procesados/

#########Nombre del comando
nombre="interprete"

#########Checkeo que no haya otro interprete corriendo
procesosCorriendo=$(ps x)
cantidad=$(echo "$procesosCorriendo" | grep -v "grep" | grep -v "obtpid" | grep -v "vi" | grep -v "gedit" |grep -c "$nombre.sh")
if [ $cantidad -gt 2 ]; then
    glog.sh $nombre w "El proceso Interprete ya está en ejecución"
    exit 1
fi

##########Checkeo las variables de ambiente
variablesok=$(envcheck.sh)
if [ $variablesok = 1 ]; then
    echo "Entorno no inicializado"
    exit 2
fi

#########Inicializo las variables de los directorios

directorioOK="$GRUPO/$DATADIR/ok"
directorioNEW="$GRUPO/$DATADIR/new"
directorioOLD="$GRUPO/$DATADIR/old"
directorioNOK="$GRUPO/$DATADIR/nok"

#creo los directorios new y old si no estaban creados
if [ ! -e $directorioNEW ]; then
    mkdir $directorioNEW
fi

if [ ! -e $directorioOLD ]; then
    mkdir $directorioOLD
fi

#########Inicializo el log
glog.sh $nombre i "Inicio de Intérprete"

#########Inicializo variables
sepE=','
tablaDeSeparadores="$GRUPO/conf/T1.tab"
tablaDeCampos="$GRUPO/conf/T2.tab"

#########Proceso los archivos
archivos=$(ls -1p $directorioOK | grep -v /\$ )
OldIFS=$IFS #guardo el IFS actual
IFS=$'\n' #pongo como IFS sólo el new line
vector=($archivos) #creo el vector separando sólo con el IFS
IFS=$OldIFS #restauro el IFS anterior
cantArchivos=${#vector[@]}
glog.sh $nombre i "Cantidad de archivos=$cantArchivos"

for arch in ${vector[@]}
do
    
    #####Chequeo si el archivo está repetido
    #####Elimino los ceros de la izquierda en sistema y mes
    i=${arch//"-0"/"-"}

    if [ -f $directorioOLD/$i ] && [ -f $directorioOLD/$arch ]; then
        mover.sh $directorioOK/$arch $directorioNOK interprete
        glog.sh $nombre i "DUPLICADO: $arch"
    else
    #####Si no está repetido, lo proceso
      ####Inicializo las variables que saco del nombre del archivo
        pais=$(echo "$i" | cut -f1 -d"-")
        pais=$(echo $pais | tr "[:lower:]" "[:upper:]")
        sis_id=$(echo "$i" | cut -f2 -d"-")
        anio_id=$(echo "$i" | cut -f3 -d"-")
        mes_id=$(echo "$i" | cut -f4 -d"-")

      ##Busco en la tabla de separadores los que corresponden al pais y sistema
        formato=$(grep "$pais-$sis_id" $tablaDeSeparadores)
        sepF=$(echo "$formato" | cut -d"-" -f3)
        sepD=$(echo "$formato" | cut -d"-" -f4)

        #buscar en tabla 2 los campos que necesito, su posición y formatos
        camposLeidos=$(grep "$pais-$sis_id-.*-.*-.*-1" $tablaDeCampos)

        posNoContrat=$(echo "$camposLeidos" | grep "NO_CONTRAT" | cut -f4 -d"-" )
        formDtFlux=$(echo "$camposLeidos" | grep "DT_FLUX" | cut -d"-" -f5)
        longFecha=${formDtFlux:6:(${#formDtFlux}-7)}
        formatoFecha=${formDtFlux:0:6}
        posDtFlux=$(echo "$camposLeidos" | grep "DT_FLUX" | cut -d"-" -f4)
        posCdStatctb=$(echo "$camposLeidos" | grep "CD_STATCTB" | cut -d"-" -f4)
        posMtCrd=$(echo "$camposLeidos" | grep "MT_CRD" | cut -d"-" -f4)
        posMtImp=$(echo "$camposLeidos" | grep "MT_IMPAGO" | cut -d"-" -f4)
        posMtInde=$(echo "$camposLeidos" | grep "MT_INDE" | cut -d"-" -f4)
        posMtInnode=$(echo "$camposLeidos" | grep "MT_INNODE" | cut -d"-" -f4)
        posMtOtr=$(echo "$camposLeidos" | grep "MT_OTRSUMDC" | cut -d"-" -f4)

        cantidadRegistrosInput=0
        cantidadRegistrosOutput=0

        while read line
        do
            #analizo el campo de Estado contable para decartar o no el registro
            cantidadRegistrosInput=$(($cantidadRegistrosInput+1))
            campoEstado=$(echo "$line" | cut -d"$sepF" -f$posCdStatctb)
            if [ "$campoEstado" != "CTX" ]; then
                if [ "$campoEstado" = "SNA" -o "$campoEstado" = "SNIM" ]; then
                    nuevoEstado="SANO"
                elif [ "$campoEstado" = "DTCA" -o "$campoEstado" = "DTXA" ]; then
                    nuevoEstado="DUDOSO"
                fi

                #leer montos
                mCrd=$(echo "$line" | cut -d"$sepF" -f"$posMtCrd")
                mImp=$(echo "$line" | cut -d"$sepF" -f"$posMtImp")
                mInde=$(echo "$line" | cut -d"$sepF" -f"$posMtInde")
                mInnode=$(echo "$line" | cut -d"$sepF" -f"$posMtInnode")
                mOtr=$(echo "$line" | cut -d"$sepF" -f"$posMtOtr")

                #analizar monto y convertir a estándar
                #reemplazo el separador decimal del archivo por "." para que lo use bc
                sepBC="."
                mCrd=${mCrd/$sepD/$sepBC}
                mImp=${mImp/$sepD/$sepBC}
                mInde=${mInde/$sepD/$sepBC}
                mInnode=${mInnode/$sepD/$sepBC}
                mOtr=${mOtr/$sepD/$sepBC}

                #corto a 10 digitos de parte entera y 2 de parte decimal
                mCrd=$(echo "scale=2; lenght=12; $mCrd" | bc -l)
                mImp=$(echo "scale=2; lenght=12; $mImp" | bc -l)
                mInde=$(echo "scale=2; lenght=12; $mInde" | bc -l)
                mInnode=$(echo "scale=2; lenght=12; $mInnode" | bc -l)
                mOtr=$(echo "scale=2; lenght=12; $mOtr" | bc -l)

                #calcular monto restante
                mRest=$(echo "scale=2; lenght=12; $mCrd+$mImp+$mInde-$mOtr" | bc -l)

                #tomo el primer caracter del mRest, si es negativo, ignoro ese registro
                mRestPrimero=${mRest:0:1}
                if [ "$mRestPrimero" != "-" ]; then
                    cantidadRegistrosOutput=$(($cantidadRegistrosOutput+1))

                    #analizar fecha y convertir a estándar
                    fecha=$(echo "$line" | cut -d"$sepF" -f"$posDtFlux")
                    if [ "$longFecha" = "8" ]; then
                        if [ "$formatoFecha" = "ddmmyy" ]; then
                            dia=$(echo $fecha | cut -c 1,2)
                            mes=$(echo $fecha | cut -c 3,4)
                            anio=$(echo $fecha | cut -c 5-8)
                        else
                            dia=$(echo $fecha | cut -c 7,8)
                            mes=$(echo $fecha | cut -c 5,6)
                            anio=$(echo $fecha | cut -c 1-4)
                        fi
                    else
                        if [ "$formatoFecha" = "ddmmyy" ]; then
                            dia=$(echo $fecha | cut -c 1,2)
                            mes=$(echo $fecha | cut -c 4,5)
                            anio=$(echo $fecha | cut -c 7-10)
                        else
                            dia=$(echo $fecha | cut -c 9,10)
                            mes=$(echo $fecha | cut -c 6,7)
                            anio=$(echo $fecha | cut -c 1-4)
                        fi
                    fi
                    fechaEstandar="$dia/$mes/$anio"

                    #leo el número de contrato
                    nContrat=$(echo "$line" | cut -d"$sepF" -f"$posNoContrat")

                    #reemplazo "." que usa bc por el separador estándar del sistema
                    mCrd=${mCrd/$sepBC/$sepE}
                    mImp=${mImp/$sepBC/$sepE}
                    mInde=${mInde/$sepBC/$sepE}
                    mInnode=${mInnode/$sepBC/$sepE}
                    mOtr=${mOtr/$sepBC/$sepE}
                    mRest=${mRest/$sepBC/$sepE}

                    #fecha de grabación
                    fechaGrab=$(date +%d/%m/%Y)

                    #armar el nuevo registro
                    registroNuevo="$sis_id-$anio_id-$mes_id-$nContrat-$fechaEstandar-$nuevoEstado-$mCrd-$mImp-$mInde-$mInnode-$mOtr-$mRest-$fechaGrab-$USERID"
                    echo $registroNuevo >> $directorioNEW/CONTRACT.$pais
                fi
            fi
        done < "$directorioOK/$arch"
        mover.sh $directorioOK/$arch $directorioOLD $nombre
        glog.sh $nombre i "Cantidad de registros leidos: $cantidadRegistrosInput"
        glog.sh $nombre i "Cantidad de registros grabados: $cantidadRegistrosOutput"
     fi
done
glog.sh $nombre i "Fin de Intérprete"
exit 0
