#ifndef RECURSODEALMACENAMIENTO_HPP
#define RECURSODEALMACENAMIENTO_HPP

#include<stdio.h>
#include<cstring>
#include<sstream>
#include<iostream>
#include "campo.hpp"
#include "campo_entero.hpp"
#include "campo_booleano.hpp"
#include "campo_doble.hpp"
#include "campo_flotante.hpp"
#include "campo_largo.hpp"
#include "campo_cadena.hpp"
#include "esquema.hpp"
#include "clave.hpp"
#include "archivo.hpp"
#include "buffer.hpp"
#include "registro.hpp"
#include "RegistroLongitudFija.hpp"
#include "EstrategiaEspacioLibreBloque.hpp"
#include "EstrategiaAlmacenamiento.hpp"
#include "estrategia_indice.hpp"
#include "indice_b_sharp.hpp"
#include "indice_hash.hpp"
#include "estrategia_indice.hpp"
#include "EsquemaBloque.hpp"
#include "EstrategiaAlmacenamientoBloques.hpp"
#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"
#include "indice_secuencial.hpp"
#include "EstrategiaRecurso.hpp"


/**
 * Define el Recurso De Almacenamiento.
 * Clase que se encarga de manejar y controlar las demas Estrategias.
 */
class RecursoDeAlmacenamiento: public ContadorReferencias {
       public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<RecursoDeAlmacenamiento> puntero;

        /**
        * Almacena la estrategia de recurso.
        */
        EstrategiaRecurso::puntero estrategia_recurso;

        /**
         * Destructor virtual de la clase EstrategiaRecurso
         */
        virtual ~RecursoDeAlmacenamiento() throw();
        /**
         * Escribir en un recurso un registro
         */
        virtual bool agregar_registro(Registro::puntero registro, IndiceSecuencial::puntero indice_secuencial );
        /**
         * Borra en un recurso un registro
         */
        virtual bool remover_registro(Registro::puntero registro);
        /**
         * Leer de un recurso un registro
         */
        virtual Registro::puntero buscar_registro(Registro::puntero registro_busqueda, IndiceSecuencial::puntero indice_secuencial);

        //OJO FABRICA PROTECTED
        /**
         * Constructor protegido de la clase EstrategiaRecurso
         */
        RecursoDeAlmacenamiento(EstrategiaRecurso::puntero estRecur, EstrategiaAlmacenamiento::puntero estAlmac,  EstrategiaAlmacenamiento::puntero estAlmacBuffer, EstrategiaIndice::puntero estIndice, Almacenamiento::puntero parchivo, Almacenamiento::puntero pbuffer);

    protected:

        /**
        * Almacena la estrategia de almacenamiento.
        */
        EstrategiaAlmacenamiento::puntero estrategia_almacenamiento;
        EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer;
        /**
        * Almacena la estrategia de indice.
        */
        EstrategiaIndice::puntero estrategia_indice;
        /**
        * Almacena el archivo.
        */
        Archivo::puntero archivo;
        /**
        * Almacena el buffer.
        */
        Buffer::puntero buffer;
};

#endif // RECURSODEALMACENAMIENTO_HPP
