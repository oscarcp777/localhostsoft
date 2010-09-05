################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ArbolBSharp.cpp \
../src/CampoStream.cpp \
../src/EsquemaBloque.cpp \
../src/EstrategiaAlmacenamiento.cpp \
../src/EstrategiaAlmacenamientoBSharp.cpp \
../src/EstrategiaAlmacenamientoBloques.cpp \
../src/EstrategiaAlmacenamientoBucketHash.cpp \
../src/EstrategiaAlmacenamientoDirectoryHash.cpp \
../src/EstrategiaAlmacenamientoEspacioLibre.cpp \
../src/EstrategiaAlmacenamientoRegistros.cpp \
../src/EstrategiaAlmacenamientoTexto.cpp \
../src/EstrategiaEspacioLibreBloque.cpp \
../src/EstrategiaRecurso.cpp \
../src/EstrategiaRecursoEscrituraDiferida.cpp \
../src/EstrategiaRecursoEscrituraDirecta.cpp \
../src/EstrategiaRecursoUnAlmacenamiento.cpp \
../src/FabricaDeRecursosDeAlmacenamiento.cpp \
../src/RecursoDeAlmacenamiento.cpp \
../src/RegistroLongitudFija.cpp \
../src/RegistroLongitudVariable.cpp \
../src/almacenamiento.cpp \
../src/archivo.cpp \
../src/bloque.cpp \
../src/bloque_b_sharp.cpp \
../src/bloque_externo_b_sharp.cpp \
../src/bloque_interno_b_sharp.cpp \
../src/buffer.cpp \
../src/campo.cpp \
../src/campo_booleano.cpp \
../src/campo_cadena.cpp \
../src/campo_doble.cpp \
../src/campo_entero.cpp \
../src/campo_flotante.cpp \
../src/campo_largo.cpp \
../src/clave.cpp \
../src/comparador_clave.cpp \
../src/componente.cpp \
../src/componentecompuesto.cpp \
../src/contador_referencias.cpp \
../src/esquema.cpp \
../src/estrategia_indice.cpp \
../src/hash_bucket.cpp \
../src/hash_directory.cpp \
../src/indice_b_sharp.cpp \
../src/indice_hash.cpp \
../src/main.cpp \
../src/registro.cpp \
../src/resultado_insercion.cpp 

OBJS += \
./src/ArbolBSharp.o \
./src/CampoStream.o \
./src/EsquemaBloque.o \
./src/EstrategiaAlmacenamiento.o \
./src/EstrategiaAlmacenamientoBSharp.o \
./src/EstrategiaAlmacenamientoBloques.o \
./src/EstrategiaAlmacenamientoBucketHash.o \
./src/EstrategiaAlmacenamientoDirectoryHash.o \
./src/EstrategiaAlmacenamientoEspacioLibre.o \
./src/EstrategiaAlmacenamientoRegistros.o \
./src/EstrategiaAlmacenamientoTexto.o \
./src/EstrategiaEspacioLibreBloque.o \
./src/EstrategiaRecurso.o \
./src/EstrategiaRecursoEscrituraDiferida.o \
./src/EstrategiaRecursoEscrituraDirecta.o \
./src/EstrategiaRecursoUnAlmacenamiento.o \
./src/FabricaDeRecursosDeAlmacenamiento.o \
./src/RecursoDeAlmacenamiento.o \
./src/RegistroLongitudFija.o \
./src/RegistroLongitudVariable.o \
./src/almacenamiento.o \
./src/archivo.o \
./src/bloque.o \
./src/bloque_b_sharp.o \
./src/bloque_externo_b_sharp.o \
./src/bloque_interno_b_sharp.o \
./src/buffer.o \
./src/campo.o \
./src/campo_booleano.o \
./src/campo_cadena.o \
./src/campo_doble.o \
./src/campo_entero.o \
./src/campo_flotante.o \
./src/campo_largo.o \
./src/clave.o \
./src/comparador_clave.o \
./src/componente.o \
./src/componentecompuesto.o \
./src/contador_referencias.o \
./src/esquema.o \
./src/estrategia_indice.o \
./src/hash_bucket.o \
./src/hash_directory.o \
./src/indice_b_sharp.o \
./src/indice_hash.o \
./src/main.o \
./src/registro.o \
./src/resultado_insercion.o 

CPP_DEPS += \
./src/ArbolBSharp.d \
./src/CampoStream.d \
./src/EsquemaBloque.d \
./src/EstrategiaAlmacenamiento.d \
./src/EstrategiaAlmacenamientoBSharp.d \
./src/EstrategiaAlmacenamientoBloques.d \
./src/EstrategiaAlmacenamientoBucketHash.d \
./src/EstrategiaAlmacenamientoDirectoryHash.d \
./src/EstrategiaAlmacenamientoEspacioLibre.d \
./src/EstrategiaAlmacenamientoRegistros.d \
./src/EstrategiaAlmacenamientoTexto.d \
./src/EstrategiaEspacioLibreBloque.d \
./src/EstrategiaRecurso.d \
./src/EstrategiaRecursoEscrituraDiferida.d \
./src/EstrategiaRecursoEscrituraDirecta.d \
./src/EstrategiaRecursoUnAlmacenamiento.d \
./src/FabricaDeRecursosDeAlmacenamiento.d \
./src/RecursoDeAlmacenamiento.d \
./src/RegistroLongitudFija.d \
./src/RegistroLongitudVariable.d \
./src/almacenamiento.d \
./src/archivo.d \
./src/bloque.d \
./src/bloque_b_sharp.d \
./src/bloque_externo_b_sharp.d \
./src/bloque_interno_b_sharp.d \
./src/buffer.d \
./src/campo.d \
./src/campo_booleano.d \
./src/campo_cadena.d \
./src/campo_doble.d \
./src/campo_entero.d \
./src/campo_flotante.d \
./src/campo_largo.d \
./src/clave.d \
./src/comparador_clave.d \
./src/componente.d \
./src/componentecompuesto.d \
./src/contador_referencias.d \
./src/esquema.d \
./src/estrategia_indice.d \
./src/hash_bucket.d \
./src/hash_directory.d \
./src/indice_b_sharp.d \
./src/indice_hash.d \
./src/main.d \
./src/registro.d \
./src/resultado_insercion.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


