#ifndef COMPONENTE_HPP
#define COMPONENTE_HPP

#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"

/**
 * Clase base de los diferentes componentes del toolkit.
 * Clase base de registros y bloques.
 */
class Componente: public ContadorReferencias {
	public:
		/**
		 * Definicion del tipo de dato puntero.
		 */
		typedef PunteroIntrusivo<Componente> puntero;

		/**
		 * Destructor virtual de la clase Componente.
		 */
		virtual ~Componente() throw();
		/**
		 * Obtiene la longitud en bytes del componente.
		 */
		virtual unsigned int GetLongitudBytes() const throw() = 0;
	protected:
		/**
		 * Constructor protegido de la clase Componente.
		 */
		Componente();
};

#endif /** COMPONENTE_HPP */

