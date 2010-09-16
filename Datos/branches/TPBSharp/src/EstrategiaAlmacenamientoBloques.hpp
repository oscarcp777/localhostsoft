#ifndef ESTRATEGIAALMACENAMIENTOBLOQUES_HPP_INCLUDED
#define ESTRATEGIAALMACENAMIENTOBLOQUES_HPP_INCLUDED

#include "EstrategiaAlmacenamiento.hpp"
#include "bloque.hpp"
#include "clave.hpp"
#include "comparador_clave.hpp"
#include <list>

/**
 * Clase EstrategiaAlmacenamientoBloques que administra el almacenamiento por bloques
 */
class EstrategiaAlmacenamientoBloques: public EstrategiaAlmacenamiento
{
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<EstrategiaAlmacenamientoBloques> puntero;
        /**
		 * Iterador para lista campos clave
		 */
        typedef std::list<Campo::puntero>::iterator it;
        /**
		 * Constructor
		 */
        EstrategiaAlmacenamientoBloques(ComparadorClave::puntero comparadorClave);
        /**
		 * Destructor
		 */
        ~EstrategiaAlmacenamientoBloques() throw();
        /**
		 * Escribe un registro en el bloque indicado usando el almacenamiento enviado
		 */
        bool Escribir(int posicion, Componente::puntero componente, Almacenamiento::puntero almacenamiento);
        /**
		 * Lee un registro del bloque indicado en el almacenamiento enviado
		 */
        Componente::puntero Leer(int posicion, Almacenamiento::puntero almacenamiento, Clave::puntero clave);
        /**
		 * Escribe un registro al final usando el almacenamiento indicado
		 */
        int AgregarAlFinal(Componente::puntero componente, Almacenamiento::puntero almacenamiento);
        /**
         * Setea el registro con datos de la clave que se usara cuando sea necesario para buscar un registro
         */
        void SetRegistroConDatosClave(Registro::puntero registroAuxiliar);
        /**
         * Devuelve el esquema del bloque actualizado
         */
        EsquemaBloque::puntero GetEsquemaBloque();
        /**
         * Elimina el espacio ocupado en la posicion indicada en el almacenamiento
         */
        bool Eliminar(int posicion, Almacenamiento::puntero almacenamiento);
        /**
         * Devuelve el tamanio
         */
        int TamanioAOcupar( Componente::puntero componente );

        ComparadorClave::puntero GetComparador();

    private:
        /**
         * Comparador para buscar un registro por clave
         */
        ComparadorClave::puntero comparadorClave;
        /**
         * Registro auxiliar para leer por clave un registro en el bloque
         */
        Registro::puntero registroAuxiliar;
        /**
		 * Almacena el esquema de bloques de los datos guardados en el almacenamiento
		 */
		EsquemaBloque::puntero esquemaBloque;
};

#endif // ESTRATEGIAALMACENAMIENTOBLOQUES_HPP_INCLUDED
