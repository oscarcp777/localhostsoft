#ifndef CAMPO_CADENA_HPP
#define CAMPO_CADENA_HPP

#include<string>

#include "puntero_intrusivo.hpp"
#include "campo.hpp"

/**
 * Clase que define un campo cadena dentro de un registro.
 */
class CampoCadena: public Campo {
	public:
		/**
		 * Define el tipo de dato puntero.
		 */
		typedef PunteroIntrusivo<CampoCadena> puntero;
		/**
		 * Constructor de la clase CampoCadena.
		 */
		CampoCadena(std::string valor) throw();
		/**
		 * Destructor virtual de la clase CampoCadena.
		 */
		virtual ~CampoCadena() throw();
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
		 * Clona la clase CampoCadena.
		 */
		virtual Campo::puntero clonar() const throw();
		/**
		 * Operador de comparacion de la clase CampoCadena.
		 */
		bool operator == (const Campo& rhs) throw();
		/**
		 * Operador de comparacion de la clase CampoCadena.
		 */
		bool operator < (const Campo& rhs) throw();
		/**
		 * Operador de comparacion de la clase CampoCadena.
		 */
		bool operator > (const Campo& rhs) throw();
	private:
		std::string valor;
};

#endif /** CAMPO_CADENA_HPP */

