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
		 * Almacena el tipo de dato puntero.
		 */
		typedef PunteroIntrusivo<BloqueBSharp> puntero;
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
		 * Obtiene el numero de3 bloque en el arbol B sharp.
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
		 * Devuelve si el bloque es hoja o no, si su nivel es 0.
		 */
		virtual bool es_hoja() const throw();
		/**
		 * Agrega un componente al bloque en el arbol b sharp.
		 */
		virtual void agregar_componente(Componente::puntero componente) throw();
		/**
		 * Agrega un componente al bloque en el arbol B sharp en la posicion especificada.
		 */
		virtual void agregar_componente(Componente::puntero componente, ComponenteCompuesto::iterador_componentes posicion) throw();
		/**
		 * Obtiene la longitud en bytes ocupada del bloque.
		 */
		virtual unsigned int obtener_longitud_ocupada() const throw();
	private:
		/**
		 * Almacena el numero de bloque en el arbol B sharp.
		 */
		unsigned int numero_bloque;
		/**
		 * Almacena el nivel del bloque en el arbol b sharp.
		 */
		unsigned int nivel;
};

#endif /** BLOQUE_B_SHARP_HPP */

