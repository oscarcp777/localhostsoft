#ifndef CAMPO_HPP
#define CAMPO_HPP

#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"
#include "tipo_campo.hpp"

/**
 * Clase base para los campos de un registro.
 */
class Campo: public ContadorReferencias {
	public:
		/**
		 * Definicion del tipo puntero.
		 */
		typedef PunteroIntrusivo<Campo> puntero;
		/**
		 * Destructor virtual de la clase Campo.
		 */
		virtual ~Campo() throw();
		/**
		 * Obtiene el tipo de campo del campo.
		 */
		virtual TipoCampo obtener_tipo_campo() const throw() = 0;
		/**
		 * Obtiene la longitud del campo en bytes.
		 */
		virtual unsigned int obtener_longitud_en_bytes() const throw() = 0;
		/**
		 * Obtiene el valor del campo.
		 */
		virtual const void* obtener_valor() const throw() = 0;
		/**
		 * Establece el valor del campo.
		 */
		virtual void establecer_valor(const void* valor) throw() = 0;
		/**
		 * Operador de comparacion de la clase Campo.
		 */
		virtual bool operator == (const Campo& rhs) throw() = 0;
		/**
		 * Operador de comparacion de la clase Campo.
		 */
		virtual bool operator > (const Campo& rhs) throw() = 0;
		/**
		 * Operador de comparacion de la clase Campo.
		 */
		virtual bool operator < (const Campo& rhs) throw() = 0;
		/**
		 * Clona la clase campo.
		 */
		virtual Campo::puntero clonar() const throw();
	protected:
		/**
		 * Constructor protegido de la clase Campo.
		 */
		Campo() throw();
};

#endif /** CAMPO_HPP */

