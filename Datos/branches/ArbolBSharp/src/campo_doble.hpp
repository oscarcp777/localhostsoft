#ifndef CAMPO_DOBLE_HPP
#define CAMPO_DOBLE_HPP

#include "puntero_intrusivo.hpp"
#include "campo.hpp"

/**
 * Clase que define un campo entero dentro de un registro.
 */
class CampoDoble: public Campo {
	public:
		/**
		 * Define el tipo de dato puntero.
		 */
		typedef PunteroIntrusivo<CampoDoble> puntero;
		/**
		 * Constructor de la clase CampoDoble.
		 */
		CampoDoble(double valor) throw();
		/**
		 * Destructor virtual de la clase CampoDoble.
		 */
		virtual ~CampoDoble() throw();
		/**
		 * Obtiene el tipo de campo del campo.
		 */
		virtual TipoCampo obtener_tipo_campo() const throw();
		/**
		 * Obtiene el valor del campo.
		 */
		virtual const void* obtener_valor() const throw();
		/**
		 * Establece el valor del campo.
		 */
		virtual void establecer_valor(const void* valor) throw();
		/**
		 * Obtiene la longitud en bytes del campo.
		 */
		virtual unsigned int obtener_longitud_en_bytes() const throw();
		/**
		 * Clona la clase CampoDoble.
		 */
		virtual Campo::puntero clonar() const throw();
		/**
		 * Operador de comparacion de la clase CampoDoble.
		 */
		bool operator == (const Campo& rhs) throw();
		/**
		 * Operador de comparacion de la clase CampoDoble.
		 */
		bool operator < (const Campo& rhs) throw();
		/**
		 * Operador de comparacion de la clase CampoDoble.
		 */
		bool operator > (const Campo& rhs) throw();
	private:
		double valor;
};

#endif /** CAMPO_DOBLE_HPP */

