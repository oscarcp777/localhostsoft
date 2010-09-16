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
		 * Establece el regsitro con la clave de dato izquierda luego de una division de bloques de 2 a 3.
		 * @param registro_clave_izq - El registro con la clave de dato izquierda luego de una division de bloques de 2 a 3.
		 */
		void establecer_registro_clave_izq(const Registro::puntero& registro_clave_izq) throw();
		/**
		 * Establece el regsitro con la clave de dato derecha luego de una division de bloques de 2 a 3.
		 * @param registro_clave_der - El registro con la clave de dato derecha luego de una division de bloques de 2 a 3.
		 */
		void establecer_registro_clave_der(const Registro::puntero& registro_clave_der) throw();
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
		/**
		 * Establece el numero de bloque medio luego de una division de bloques de 2 a 3.
		 * @param numero_bloque - El numero de bloque medio luego de una division de bloques de 2 a 3.
		 */
		void establecer_bloque_medio(unsigned int numero_bloque) throw();
		/**
		 * Obtiene el numero de bloque medio luego de una division de bloques de 2 a 3.
		 * @return unsigned int - El numero de bloque medio luego de una division de bloques de 2 a 3.
		 */
		unsigned int obtener_bloque_medio() const throw();
	private:
		/**
		 * Almacena el registro con la clave de dato media luego de una division de bloques para el split simple.
		 */
		Registro::puntero registro_clave_media;
		/**
		 * Almacena el registro con la clave de dato izquierda luego de una division de bloques para el split de 2 a 3.
		 */
		Registro::puntero registro_clave_izq;
		/**
		 * Almacena el registro con la clave de dato derecha luego de una division de bloques para el split de 2 a 3.
		 */
		Registro::puntero registro_clave_der;
		/**
		 * Almacena el numero de bloque izquierdo luego de una division de bloques.
		 */
		unsigned int bloque_izquierdo;
		/**
		 * Almacena el numero de bloque derecho luego de una division de bloques.
		 */
		unsigned int bloque_derecho;
		/**
		 * Almacena el numero de bloque medio luego de una division de bloques de 2 a 3.
		 */
		unsigned int bloque_medio;
};

#endif /** RESULTADO_INSERCION_HPP */

