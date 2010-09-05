#ifndef ESQUEMABLOQUE_HPP_INCLUDED
#define ESQUEMABLOQUE_HPP_INCLUDED

#include<map>

#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"

class EsquemaBloque: public ContadorReferencias
{
    public:
	/**
	 * Define el tipo de dato puntero.
	 */
	typedef PunteroIntrusivo<EsquemaBloque> puntero;
        /**
	 * Iterador para lista Bloques-Espacio
	 */
        typedef std::map<int, int>::iterator iterador;
        /**
		 * Primer campo de lista Bloques-Espacio
		 */
        EsquemaBloque::iterador primerCampo();
        /**
		 * Ultimo campo de lista Bloques-Espacio
		 */
        EsquemaBloque::iterador ultimoCampo();
        /**
		 * Obtiene el espacio ocupado en el numero de bloque indicado
		 */
        int GetEspacioOcupado(int numeroDeBloque);
        /**
		 * Obtiene la cantidad de bloques totales
		 */
        int GetCantidadDeBloques();
        /**
		 * Setea el espacio ocupado en el bloque
		 */
        void SetEspacioOcupado(int numeroDeBloque, int espacio);
        /**
		 * Constructor de EsquemaBloque
		 */
        EsquemaBloque(int cantidadDeBloques);
        /**
		 * Destructor de EsquemaBloque
		 */
        ~EsquemaBloque() throw();
    private:
        /**
		 * Almacena la lista de espacios ocupados segun numero de bloque
		 */
        std::map<int, int> listaBloquesEspacio;
        /**
		 * Almacena la cantidad de bloques
		 */
        int cantidadDeBloques;
};
#endif // ESQUEMABLOQUE_HPP_INCLUDED
