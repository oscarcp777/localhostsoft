#ifndef ESTRATEGIA_ALMACENAMIENTO_ESPACIO_LIBRE_HPP
#define ESTRATEGIA_ALMACENAMIENTO_ESPACIO_LIBRE_HPP

#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"
#include "archivo.hpp"

/**
 * Estrategia para almacenar espacio libre en un almacenamiento dado.
 */
class EstrategiaAlmacenamientoEspacioLibre: public ContadorReferencias {
	public:
		/**
		 * Define el tipo de dato puntero.
		 */
		typedef PunteroIntrusivo<EstrategiaAlmacenamientoEspacioLibre> puntero;
		/**
		 * Constructor de la clase EstrategiaAlmacenamientoEspacioLibre.
		 */
		EstrategiaAlmacenamientoEspacioLibre(const std::string& nombre_archivo) throw();
		/**
		 * Destructor virtual de la clase EstrategiaAlmacenamientoEspacioLibre.
		 */
		virtual ~EstrategiaAlmacenamientoEspacioLibre() throw();
		/**
		 * Escribe la cantidad de espacio ocupado / libre para un numero de elemento dentro de un almacenamiento dado.
		 */
		void escribir_espacio_ocupado(unsigned int posicion, unsigned int espacio_ocupado) throw();
		/**
		 * Lee la cantidad de espacio ocupado / libre para un numero de elemento dentro de un almacenamiento dado.
		 */
		unsigned int leer_espacio_ocupado(unsigned int posicion) throw();
		/**
		 * Busca el numero de elemento dentro de un almacenamiento dado con espacio libre.
		 */
		unsigned int buscar_espacio_libre() throw();
	protected:
		/**
		 * Verifica si el espacio ocupado / libre para un numero de elemento dentro de un almacenamiento dado se considera  no lleno.
		 */
		virtual bool es_espacio_libre(unsigned int espacio_ocupado) throw() = 0;
	private:
		/**
		 * Almacena el archivo de espacios ocupados / libres.
		 */
		Archivo::puntero archivo;
};

#endif /** ESTRATEGIA_ALMACENAMIENTO_ESPACIO_LIBRE_HPP */

