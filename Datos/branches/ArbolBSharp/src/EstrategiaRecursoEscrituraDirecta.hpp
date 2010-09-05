#ifndef ESTRATEGIARECURSOESCRITURADIRECTA_HPP
#define ESTRATEGIARECURSOESCRITURADIRECTA_HPP

#include "EstrategiaRecurso.hpp"


class EstrategiaRecursoEscrituraDirecta : public EstrategiaRecurso
{
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<EstrategiaRecursoEscrituraDirecta> puntero;
        /**
         * Constructor de la clase EstrategiaRecursoEscrituraDirecta
         */
        EstrategiaRecursoEscrituraDirecta();
        /**
         * Destructor virtual de la clase EstrategiaRecursoEscrituraDirecta
         */
        virtual ~EstrategiaRecursoEscrituraDirecta() throw();
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
         virtual Registro::puntero  buscar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento   ) throw() ;

    protected:

    private:
        int posicion_en_almacenamiento;
};

#endif // ESTRATEGIARECURSOESCRITURADIRECTA_HPP
