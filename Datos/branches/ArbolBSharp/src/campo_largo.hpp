#ifndef CAMPO_LARGO_HPP
#define CAMPO_LARGO_HPP

#include "puntero_intrusivo.hpp"
#include "campo.hpp"

/**
 * Clase que define un campo largo dentro de un registro.
 */
class CampoLargo: public Campo {
	public:
		/**
		 * Define el tipo de dato puntero.
		 */
		typedef PunteroIntrusivo<CampoLargo> puntero;
		/**
		 * Constructor de la clase CampoLargo.
		 */
		CampoLargo(long valor) throw();
		/**
		 * Destructor virtual de la clase CampoLargo.
		 */
		virtual ~CampoLargo() throw();
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
		 * Clona la clase CampoLargo.
		 */
		virtual Campo::puntero clonar() const throw();
		/**
		 * Operador de comparacion de la clase CampoLargo.
		 */
		bool operator == (const Campo& rhs) throw();
		/**
		 * Operador de comparacion de la clase CampoLargo.
		 */
		bool operator < (const Campo& rhs) throw();
		/**
		 * Operador de comparacion de la clase CampoLargo.
		 */
		bool operator > (const Campo& rhs) throw();
	private:
		long valor;
};

#endif /** CAMPO_LARGO_HPP */

