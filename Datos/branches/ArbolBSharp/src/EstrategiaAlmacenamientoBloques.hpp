#ifndef ESTRATEGIAALMACENAMIENTOBLOQUES_HPP_INCLUDED
#define ESTRATEGIAALMACENAMIENTOBLOQUES_HPP_INCLUDED

#include "EstrategiaAlmacenamiento.hpp"
#include "bloque.hpp"
#include "clave.hpp"
#include "comparador_clave.hpp"
#include <list>

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
		 * Escribe un registro en el bloque usando el almacenamiento indicado
		 */
        bool Escribir(int posicion, Componente::puntero componente, Almacenamiento::puntero almacenamiento);
        /**
		 * Lee un registro del bloque en el almacenamiento indicado
		 */
        Componente::puntero Leer(int posicion, Almacenamiento::puntero almacenamiento, Clave::puntero clave);
        /**
		 * Escribe un registro al final usando el almacenamiento indicado
		 */
        int AgregarAlFinal(Componente::puntero componente, Almacenamiento::puntero almacenamiento);
        /**
		 * Setea los campos en la clave que se usaran para leer el registro
		 */
        void SetCamposClave(std::list<Campo::puntero> listaCamposClave);

        void SetRegistroConDatosClave(Registro::puntero registroAuxiliar);

        EsquemaBloque::puntero GetEsquemaBloque();
    private:
        Clave::puntero clave;
        ComparadorClave::puntero comparadorClave;
        std::list<Campo::puntero> listaCamposClave;
        Registro::puntero registroAuxiliar;
        /**
		 * Almacena el esquema de bloques de los datos guardados en el almacenamiento
		 */
		EsquemaBloque::puntero esquemaBloque;
};

#endif // ESTRATEGIAALMACENAMIENTOBLOQUES_HPP_INCLUDED
