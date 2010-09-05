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
#include "EstrategiaRecurso.hpp"

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
        virtual bool agregar_registro(Registro::puntero registro);
        /**
         * Borra en un recurso un registro
         */
        virtual bool remover_registro(Registro::puntero registro);
        /**
         * Leer de un recurso un registro
         */
        virtual Registro::puntero buscar_registro(Registro::puntero registro_busqueda);

        //OJO FABRICA PROTECTED
        /**
         * Constructor protegido de la clase EstrategiaRecurso
         */
        RecursoDeAlmacenamiento(EstrategiaRecurso::puntero estRecur, EstrategiaAlmacenamiento::puntero estAlmac, EstrategiaIndice::puntero estIndice, Almacenamiento::puntero parchivo, Almacenamiento::puntero pbuffer);

    protected:

        /**
        * Almacena la estrategia de almacenamiento.
        */
        EstrategiaAlmacenamiento::puntero estrategia_almacenamiento;
        /**
        * Almacena la estrategia de indice.
        */
        EstrategiaIndice::puntero estrategia_indice;
        /**
        * Almacena el archivo.
        */
        Almacenamiento::puntero archivo;
        /**
        * Almacena el buffer.
        */
        Almacenamiento::puntero buffer;
};

#endif // RECURSODEALMACENAMIENTO_HPP
