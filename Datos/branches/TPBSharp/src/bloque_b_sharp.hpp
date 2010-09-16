#ifndef BLOQUE_B_SHARP_HPP
#define BLOQUE_B_SHARP_HPP

#include "puntero_intrusivo.hpp"
#include "bloque.hpp"

/**
 * Clase BloqueBSharp que define las propiedades y atributos comunes a un
 * bloque de un arbol b sharp.
 */
class BloqueBSharp: public Bloque {
	public:
		/**
		 * Define el tipo de dato puntero.
		 */
		typedef PunteroIntrusivo<BloqueBSharp> puntero;
		/**
		 * Define el tipo de ID BLOQUE INVALIDO.
		 */
		static const int ID_BLOQUE_INVALIDO = -1;
		/**
		 * Constructor de la clase BloqueBSharp.
		 * Recibe como parametro la longitud del bloque y el nivel
		 * del bloque en el arbol B sharp.
		 */
		BloqueBSharp(unsigned int longitud_maxima, unsigned int numero_bloque, unsigned int nivel) throw();
		/**
		 * Destructor virtual de la clase BloqueBSharp.
		 */
		virtual ~BloqueBSharp() throw();
		/**
		 * Obtiene el numero de bloque en el arbol B sharp.
		 */
		virtual unsigned int obtener_numero_bloque() const throw();
		/**
		 * Establece el numer4o de bloque en el arbol B sharp.
		 */
		virtual void establecer_numero_bloque(unsigned int numero_bloque) throw();
		/**
		 * Obtiene el nivel del bloque en el arbol B sharp.
		 */
		virtual unsigned int obtener_nivel() const throw();
		/**
		 * Establece el nivel del bloque en el arbol B sharp.
		 */
		virtual void establecer_nivel(unsigned int nivel) throw();
		/**
		 * Obtiene el bloque siguiente en el arbol b sharp.
		 */
		int obtener_bloque_siguiente() const throw();
		/**
		 * Establece el bloque siguiente en el arbol b sharp.
		 */
		void establecer_bloque_siguiente(int bloque_siguiente) throw();
		/**
		 * Devuelve si el bloque es hoja o no, si su nivel es 0.
		 */
		virtual bool es_hoja() const throw();
		/**
		 * Obtiene la longitud administrativa en bytes del bloque.
		 */
		virtual unsigned int obtener_longitud_administrativa() throw();
		/**
		 * Devuelve si el bloque esta semi vacio, menos de la mitad de su capacidad.
		 */
		bool esta_semi_vacio() throw();
	private:
		/**
		 * Almacena el numero de bloque en el arbol B sharp.
		 */
		unsigned int numero_bloque;
		/**
		 * Almacena el nivel del bloque en el arbol b sharp.
		 */
		unsigned int nivel;
		/**
		 * Almacena el bloque siguiente en el arbol b sharp.
		 */
		int bloque_siguiente;
		/**
		 * Almacena el bloque previo en el arbol b sharp.
		 */
		int bloque_previo;
};

#endif /** BLOQUE_B_SHARP_HPP */

