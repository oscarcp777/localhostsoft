#ifndef BLOQUE_HPP
#define BLOQUE_HPP

#include "puntero_intrusivo.hpp"
#include "componentecompuesto.hpp"
#include "registro.hpp"
#include <list>

/**
 * Clase base para el tipo de componente bloque.
 */
class Bloque: public ComponenteCompuesto {
	public:
		/**
		 * Definicion del tipo puntero.
		 */
		typedef PunteroIntrusivo<Bloque> puntero;
		/**
		 * Constructor de la clase Bloque.
		 */
		Bloque(unsigned int longitud_maxima) throw();
		/**
		 * Destructor virtual de la clase Bloque.
		 */
		virtual ~Bloque() throw();
		/**
		 * Obtiene la longitud maxima en bytes del bloque.
		 */
		unsigned int get_longitud_maxima() const throw();
		/**
		 * Establece la longitud maxima en bytes del bloque.
		 */
		void set_longitud_maxima(unsigned int longitud_maxima) throw();
		/**
		 * Obtiene la longitud en bytes  del bloque.
		 */
		virtual unsigned int GetLongitudBytes() const throw();
		/**
		 * Obtiene la longitud ocupada en bytes del bloque.
		 */
		virtual unsigned int obtener_longitud_ocupada() const throw();
		/**
		 * Decide si puede agregar un componente.
		 */
		virtual bool puede_agregar_componente(Componente::puntero componente) const throw();
	private:
		/**
		 * Almacena la longitud maxima en bytes del bloque.
		 */
		unsigned int longitud_maxima;
	protected:
		/**
		 * Devuelve el espacio de metadata utilizado
		 */
		virtual unsigned int obtener_espacio_metadata() const;

};

#endif /** BLOQUE_HPP */

