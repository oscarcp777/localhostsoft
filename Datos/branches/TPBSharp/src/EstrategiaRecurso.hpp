#ifndef ESTRATEGIARECURSO_HPP
#define ESTRATEGIARECURSO_HPP
#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"
#include "registro.hpp"
#include "EstrategiaAlmacenamiento.hpp"
#include "almacenamiento.hpp"
#include "indice_secuencial.hpp"

/**
 * Clase abstracta que define una estrategia de Recurso.
  * Define metodos comunes a todas las estrategias de recursos.
  */
class EstrategiaRecurso: public ContadorReferencias {
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<EstrategiaRecurso> puntero;
        /**
         * Destructor virtual de la clase EstrategiaRecurso.
         */
        virtual ~EstrategiaRecurso() throw();

        /**
         * Agrega un registro en el recurso.
         */
         virtual bool agregar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer   ) throw()  = 0;
         /**
          * Borra un registro del recurso.
          */
         virtual bool borrar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer  ) throw() = 0;
         /**
          * Obtiene la posicion en almacenamiento del registro.
          */
         virtual Registro::puntero  buscar_registro(  Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer , IndiceSecuencial::puntero indice_secuencial  ) throw() = 0;
    protected:
        /**
         * Constructor de la clase EstrategiaRecurso.
         */
         EstrategiaRecurso( );

};

#endif // ESTRATEGIARECURSO_HPP
