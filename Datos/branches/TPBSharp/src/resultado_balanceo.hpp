#ifndef RESULTADO_BALANCEO_HPP
#define RESULTADO_BALANCEO_HPP

#include "registro.hpp"

/**
 * Definicion de la clase ResultadoBalanceo, que representa el resultado de una operacion
 * de balanceo de bloques.
 */
class ResultadoBalanceo {
	public:
		/**
		 * Constructor de la clase ResultadoBalanceo.
		 */
		ResultadoBalanceo() throw();
		/**
		 * Destructor virtual de la clase ResultadoBalanceo.
		 */
		virtual ~ResultadoBalanceo() throw();
		/**
		 * Establece el regsitro con la clve de dato media luego de una division de bloques.
		 * @param registro_clave_media - El registro con la clave de dato media luego de una division de bloques.
		 */
		void establecer_registro_clave_media(const Registro::puntero& registro_clave_media) throw();
		/**
		 * Obtiene el registro con la clave de dato media luego de una division de bloques.
		 * @return Registro::puntero - El registro con la clave de dato media luego de una division de bloques.
		 */
		const Registro::puntero& obtener_registro_clave_media() const throw();
		/**
		 * Establece el numero de bloque hermano derecho usado para balancear.
		 * @param bloque_hermano_derecho - El numero de bloque hermano deecho usado para balancear.
		 */
		void establecer_bloque_hermano_derecho(int bloque_hermano_derecho) throw();
		/**
		 * Obtiene el numero de bloque hermano derecho usado para balancear.
		 * @return int - El numero de bloque hermano derecho usado para balancear.
		 */
		int obtener_bloque_hermano_derecho() const throw();
	private:
		/**
		 * Almacena el registro con la clave de dato media luego de un balanceo de bloques.
		 */
		Registro::puntero registro_clave_media;
		/**
		 * Almaena el numero de bloque hermano derecho usado para balancear.
		 */
		int bloque_hermano_derecho;
};

#endif /** RESULTADO_BALANCEO_HPP */

