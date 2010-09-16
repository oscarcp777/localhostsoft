#ifndef ESTRATEGIA_ESPACIO_LIBRE_BLOQUE_HPP
#define ESTRATEGIA_ESPACIO_LIBRE_BLOQUE_HPP

#include "puntero_intrusivo.hpp"
#include "EstrategiaAlmacenamientoEspacioLibre.hpp"

/**
 * Estrategia de almacenamiento de espacio libre para indice b sharp.
 */
class EstrategiaEspacioLibreBloque: public EstrategiaAlmacenamientoEspacioLibre {
	public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<EstrategiaEspacioLibreBloque> puntero;
		/**
		 * Constructor de la clase EstrategiaEspacioLibreBloque.
		 */
		EstrategiaEspacioLibreBloque(unsigned int longitud_maxima, float porcentaje_ocupado, const std::string& nombre_archivo) throw();
		/**
		 * Destructor virtual de la clase EstrategiaEspacioLibreBloque.
		 */
		virtual ~EstrategiaEspacioLibreBloque() throw();
	protected:
		virtual bool es_espacio_libre(unsigned int espacio_ocupado) throw();
	private:
		/**
		 * Almacena la longitud_maxima de un bloque dentro del indice b sharp.
		 */
		unsigned int longitud_maxima;
		/**
		 * Almacena el porcentaje ocupado de un bloue dentro del indice b sharp.
		 */
		float porcentaje_ocupado;
};

#endif /** ESTRATEGIA_ESPACIO_LIBRE_BLOQUE_HPP */

