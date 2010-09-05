#ifndef CAMPO_ENTERO_HPP
#define CAMPO_ENTERO_HPP

#include "puntero_intrusivo.hpp"
#include "campo.hpp"

/**
 * Clase que define un campo entero dentro de un registro.
 */
class CampoEntero: public Campo {
	public:
		/**
		 * Define el tipo de dato puntero.
		 */
		typedef PunteroIntrusivo<CampoEntero> puntero;
		/**
		 * Constructor de la clase CampoEntero.
		 */
		CampoEntero(int valor) throw();
		/**
		 * Destructor virtual de la clase CampoEntero.
		 */
		virtual ~CampoEntero() throw();
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
		 * Clona la clase CampoEntero.
		 */
		virtual Campo::puntero clonar() const throw();
		/**
		 * Operador de comparacion de la clase CampoEntero.
		 */
		bool operator == (const Campo& rhs) throw();
		/**
		 * Operador de comparacion de la clase CampoEntero.
		 */
		bool operator < (const Campo& rhs) throw();
		/**
		 * Operador de comparacion de la clase CampoEntero.
		 */
		bool operator > (const Campo& rhs) throw();
	private:
		int valor;
};

#endif /** CAMPO_ENTERO_HPP */

