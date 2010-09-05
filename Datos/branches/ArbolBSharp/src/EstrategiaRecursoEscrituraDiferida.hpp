#ifndef ESTRATEGIARECURSOESCRITURADIFERIDA_HPP
#define ESTRATEGIARECURSOESCRITURADIFERIDA_HPP

#include "puntero_intrusivo.hpp"
#include "EstrategiaRecurso.hpp"


class EstrategiaRecursoEscrituraDiferida : public EstrategiaRecurso
{
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<EstrategiaRecursoEscrituraDiferida> puntero;
        /**
         * Constructor de la clase EstrategiaRecursoEscrituraDiferida
         */
        EstrategiaRecursoEscrituraDiferida( );
        /**
         * Destructor virtual de la clase EstrategiaRecursoEscrituraDiferida
         */
        virtual ~EstrategiaRecursoEscrituraDiferida() throw();
          /**
         * Agrega un registro en el recurso.
         */
         virtual bool agregar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento  ) throw()  ;
         /**
          * Borra un registro del recurso.
          */
         virtual bool borrar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento  ) throw() ;
         /**
          * Obtiene la posicion en almacenamiento del registro.
          */
         virtual Registro::puntero  buscar_registro(  Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento   ) throw() ;
    protected:

    private:
};

#endif // ESTRATEGIARECURSOESCRITURADIFERIDA_HPP
