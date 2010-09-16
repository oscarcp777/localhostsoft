#ifndef ESTRATEGIAALMACENAMIENTOCOMPUESTOCOMPRIMIDO_HPP_INCLUDED
#define ESTRATEGIAALMACENAMIENTOCOMPUESTOCOMPRIMIDO_HPP_INCLUDED

#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"
#include "BloqueCompresor.hpp"
#include "EstrategiaAlmacenamiento.hpp"
#include "bloque.hpp"
#include "clave.hpp"
#include "comparador_clave.hpp"
#include "archivo.hpp"

/**
* Clase EstrategiaAlmacenamientoCompuestoComprimido que define un almacenamiento para registros comprimidos
*/
class EstrategiaAlmacenamientoCompuestoComprimido: public EstrategiaAlmacenamiento
{
    public:
        /**
        * Define el tipo de dato puntero.
        */
        typedef PunteroIntrusivo<EstrategiaAlmacenamientoCompuestoComprimido> puntero;
        /**
        * Constructor
        */
        EstrategiaAlmacenamientoCompuestoComprimido(ComparadorClave::puntero comparadorClave);
        /**
        * Destructor
        */
        ~EstrategiaAlmacenamientoCompuestoComprimido() throw();
        /**
        * Escribe un registro y lo almacena comprimido
        */
        bool Escribir(int posicion, Componente::puntero componente, Almacenamiento::puntero almacenamiento);
        /**
        * Lee el registro del almacenamiento y lo devuelve. Sino lo encuentra devuelve NULL
        */
        Componente::puntero Leer(int posicion, Almacenamiento::puntero almacenamiento, Clave::puntero clave);
        /**
        * Agrega en el primer bloque disponible al registro
        */
        int AgregarAlFinal(Componente::puntero componente, Almacenamiento::puntero almacenamiento);
         /**
         * Devuelve el esquema del bloque actualizado
         */
        EsquemaBloque::puntero GetEsquemaBloque();
        /**
         * Setea el registro con datos de la clave que se usara cuando sea necesario para buscar un registro
         */
        void SetRegistroConDatosClave(Registro::puntero registroAuxiliar);

        ComparadorClave::puntero GetComparador();
    private:
        /**
		 * Almacena el esquema de bloques de los datos guardados en el almacenamiento
		 */
		EsquemaBloque::puntero esquemaBloque;
		/**
         * Registro auxiliar para leer por clave un registro en el bloque
         */
        Registro::puntero registroAuxiliar;
        /**
         * Comparador para buscar un registro por clave
         */
		ComparadorClave::puntero comparadorClave;
};

#endif // ESTRATEGIAALMACENAMIENTOCOMPUESTOCOMPRIMIDO_HPP_INCLUDED
