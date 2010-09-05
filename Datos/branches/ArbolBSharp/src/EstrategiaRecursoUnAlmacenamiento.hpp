#ifndef ESTRATEGIARECURSOUNALMACENAMIENTO_HPP
#define ESTRATEGIARECURSOUNALMACENAMIENTO_HPP

#include "puntero_intrusivo.hpp"
#include "EstrategiaRecurso.hpp"


class EstrategiaRecursoUnAlmacenamiento : public EstrategiaRecurso
{
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<EstrategiaRecursoUnAlmacenamiento> puntero;
        /**
         * Constructor de la clase EstrategiaRecursoUnAlmacenamiento
         */
        EstrategiaRecursoUnAlmacenamiento();
        /**
         * Destructor virtual de la clase EstrategiaRecursoUnAlmacenamiento
         */
        virtual ~EstrategiaRecursoUnAlmacenamiento() throw();
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
         virtual Registro::puntero  buscar_registro (Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento   ) throw() ;


    protected:

    private:
};

#endif // ESTRATEGIARECURSOUNALMACENAMIENTO_HPP
