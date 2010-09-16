#ifndef ESTRATEGIARECURSOESCRITURADIRECTA_HPP
#define ESTRATEGIARECURSOESCRITURADIRECTA_HPP

#include "EstrategiaRecurso.hpp"


/**
 * Define la estrategia de Recurso de Almacenamiento.
 */
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
         virtual bool agregar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer   ) throw()  ;
         /**
          * Borra un registro del recurso.
          */
         virtual bool borrar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer   ) throw()  ;
         /**
          * Obtiene la posicion en almacenamiento del registro.
          */
         virtual Registro::puntero  buscar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer, IndiceSecuencial::puntero indice_secuencial   ) throw()  ;

    protected:

    private:
        int posicion_en_almacenamiento;
        int * actualmente_en_buffer;
        int total_en_buffer;
        int posicion_en_buffer;
        int proximo_en_buffer( int pos );
        int si_esta_en_buffer( int pos );
};

#endif // ESTRATEGIARECURSOESCRITURADIRECTA_HPP
