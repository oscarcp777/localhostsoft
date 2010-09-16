#ifndef ESTRATEGIARECURSOESCRITURADIFERIDA_HPP
#define ESTRATEGIARECURSOESCRITURADIFERIDA_HPP
#include "EstrategiaAlmacenamientoCompuestoComprimido.hpp"
#include "EstrategiaRecurso.hpp"

typedef struct Tregbuf{
    int pos_buffer;
    int pos_disco;
    bool endisco;
}Tregbuf;



/**
 * Define la estrategia de Recurso de Almacenamiento.
 */
class EstrategiaRecursoEscrituraDiferida : public EstrategiaRecurso
{
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<EstrategiaRecursoEscrituraDiferida> puntero;
        /**
         * Constructor de la clase EstrategiaRecursoEscrituraDirecta
         */
        EstrategiaRecursoEscrituraDiferida();
        /**
         * Destructor virtual de la clase EstrategiaRecursoEscrituraDirecta
         */
        virtual ~EstrategiaRecursoEscrituraDiferida() throw();
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
        Tregbuf actualmente_en_buffer[16];
        int total_en_buffer;
        int posicion_en_buffer;
        int xreg_ultimo;
        EsquemaBloque::puntero esquema;
        BloqueCompresor::puntero bloque_compresor;
        int agregar_en_buffer( int ppos );
        int si_esta_en_buffer( int pos );
        int si_esta_en_buffer_ademas( int pos, int ultima_pos_encontrada );
};

#endif // ESTRATEGIARECURSOESCRITURADIFERIDA_HPP
