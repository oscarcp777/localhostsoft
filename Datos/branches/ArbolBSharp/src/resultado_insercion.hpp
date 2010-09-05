#ifndef RESULTADO_INSERCION_HPP
#define RESULTADO_INSERCION_HPP

#include "registro.hpp"

/**
 * Definicion de la clase ResultadoInsercion que representa el resultado de la insercion de
 * un registro en un bloque dentro del indice b sharp.
 */
class ResultadoInsercion {
	public:
		/**
		 * Constructor de la clase ResultadoInsercion.
		 */
		ResultadoInsercion() throw();
		/**
		 * Destructor virtual de la clase ResultadoInsercion.
		 */
		virtual ~ResultadoInsercion() throw();
		/**
		 * Establece el regsitro con la clve de dato media luego de una division de bloques.
		 * @param registro_clave_media - El registro con la clave de dato media luego de una division de bloques.
		 */
		void establecer_registro_clave_media(const Registro::puntero& registro_clave_media) throw();
		/**
		 * Obtiene el registro con la clave de dato media luego de una division de bloques.
		 * @param Registro::puntero - El registro con la clave de dato media luego de una division de bloques.
		 */
		const Registro::puntero& obtener_registro_clave_media() const throw();
		/**
		 * Establece el numero de bloque izquierdo luego de una division de bloques.
		 * @param numero_bloque - El numero de bloque izquierdo luego de una division de bloques.
		 */
		void establecer_bloque_izquierdo(unsigned int numero_bloque) throw();
		/**
		 * Obtiene el numero de bloque izquierdo luego de una division de bloques.
		 * @return unsigned int - El numero de bloque izquierdo luego de una division de bloques.
		 */
		unsigned int obtener_bloque_izquierdo() const throw();
		/**
		 * Establece el numero de bloque derecho luego de una division de bloques.
		 * @param numero_bloque - El numero de bloque derecho luego de una division de bloques.
		 */
		void establecer_bloque_derecho(unsigned int numero_bloque) throw();
		/**
		 * Obtiene el numero de bloque derecho luego de una division de bloques.
		 * @return unsigned int - El numero de bloque derecho luego de una division de bloques.
	 	 */
		unsigned int obtener_bloque_derecho() const throw();
	private:
		/**
		 * Almacena el registro con la clave de dato media luego de una division de bloques.
		 */
		Registro::puntero registro_clave_media;
		/**
		 * Almacena el numero de bloque izquierdo luego de una division de bloques.
		 */
		unsigned int bloque_izquierdo;
		/**
		 * Almacena el numero de bloque derecho luego de una division de bloques.
		 */
		unsigned int bloque_derecho;
};

#endif /** RESULTADO_INSERCION_HPP */

