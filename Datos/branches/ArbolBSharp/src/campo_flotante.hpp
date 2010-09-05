#ifndef CAMPO_FLOTANTE_HPP
#define CAMPO_FLOTANTE_HPP

#include "puntero_intrusivo.hpp"
#include "campo.hpp"

/**
 * Clase que define un campo entero dentro de un registro.
 */
class CampoFlotante: public Campo {
	public:
		/**
		 * Define el tipo de dato puntero.
		 */
		typedef PunteroIntrusivo<CampoFlotante> puntero;
		/**
		 * Constructor de la clase CampoFlotante.
		 */
		CampoFlotante(float valor) throw();
		/**
		 * Destructor virtual de la clase CampoFlotante.
		 */
		virtual ~CampoFlotante() throw();
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
		 * Clona la clase CampoFlotante.
		 */
		virtual Campo::puntero clonar() const throw();
		/**
		 * Operador de comparacion de la clase CampoFlotante.
		 */
		bool operator == (const Campo& rhs) throw();
		/**
		 * Operador de comparacion de la clase CampoFlotante.
		 */
		bool operator < (const Campo& rhs) throw();
		/**
		 * Operador de comparacion de la clase CampoFlotante.
		 */
		bool operator > (const Campo& rhs) throw();
	private:
		float valor;
};

#endif /** CAMPO_FLOTANTE_HPP */

