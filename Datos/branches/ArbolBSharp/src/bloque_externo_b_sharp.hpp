#ifndef BLOQUE_EXTERNO_B_SHARP_HPP
#define BLOQUE_EXTERNO_B_SHARP_HPP

#include "puntero_intrusivo.hpp"
#include "bloque_b_sharp.hpp"

/**
 * Clase BloqueExternoBSharp que representa un bloque del sequence set
 * de un arbol b sharp donde no tiene bloques hijos pero esta enceadenado
 * con bloques siguientes.
 */
class BloqueExternoBSharp: public BloqueBSharp {
	public:
		/**
		 * Define el tipo de dato puntero.
		 */
		typedef PunteroIntrusivo<BloqueExternoBSharp> puntero;
		/**
		 * Define la constante ID_BLOQUE_INVALIDO.
		 */
		static const int ID_BLOQUE_INVALIDO = -1;
	public:
		/**
		 * Constructor de la clase BloqueExternoBSharp.
		 * Recibe como parametro la longitud maxima del bloque b sharp y
		 * el nivel del bloque en el arbol b sharp.
		 */
		BloqueExternoBSharp(unsigned int longitud_maxima, unsigned int numero_bloque) throw();
		/**
		 * Destructor virtual de la clase BloqueExternoBSharp.
		 */
		virtual ~BloqueExternoBSharp() throw();
		/**
		 * Obtiene el id del bloque externo siguiente del arbol b sharp.
		 */
		int obtener_bloque_siguiente() const throw();
		/**
		 * Establece el id del bloque externo siguiente del arbol b sharp.
		 */
		void establecer_bloque_siguiente(int numero_bloque) throw();
		/**
		 * Obtiene la longitud ocupada en bytes del bloque.
		 */
		virtual unsigned int obtener_longitud_ocupada() const throw();
	private:
		/**
		 * Almacena el bloque externo siguiente del arbol b sharp.
		 */
		int bloque_siguiente;
};

#endif /** BLOQUE_EXTERNO_B_SHARP_HPP */

