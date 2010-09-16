#ifndef ESTRATEGIARECURSOUNALMACENAMIENTO_HPP
#define ESTRATEGIARECURSOUNALMACENAMIENTO_HPP

#include "EstrategiaRecurso.hpp"

/**
 * Define la estrategia de Recurso de Almacenamiento.
 */
class EstrategiaRecursoUnAlmacenamiento : public EstrategiaRecurso
{
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<EstrategiaRecursoUnAlmacenamiento> puntero;
        /**
         * Constructor de la clase EstrategiaRecursoEscrituraDirecta
         */
        EstrategiaRecursoUnAlmacenamiento();
        /**
         * Destructor virtual de la clase EstrategiaRecursoEscrituraDirecta
         */
        virtual ~EstrategiaRecursoUnAlmacenamiento() throw();
          /**
         * Agrega un registro en el recurso.
         */
         virtual bool agregar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer   ) throw()  ;
         /**
          * Borra un registro del recurso.
          */
         virtual bool borrar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer   ) throw() ;
         /**
          * Obtiene la posicion en almacenamiento del registro.
          */
         virtual Registro::puntero  buscar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer, IndiceSecuencial::puntero indice_secuencial   ) throw()  ;

    protected:

    private:
        int posicion_en_almacenamiento;
};

#endif // ESTRATEGIARECURSOUNALMACENAMIENTO_HPP
