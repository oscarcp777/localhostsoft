#ifndef CLAVE_HPP
#define CLAVE_HPP

#include<list>
#include<string>
#include<algorithm>

#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"

/**
 * Clase que representa una clave de un registro de datos.
 */
class Clave: public ContadorReferencias {
	public:
		/**
		 * Defnicion del tipo puntero.
		 */
		typedef PunteroIntrusivo<Clave> puntero;
		/**
		 * Definicion del tipo iterador_campos.
		 */
		typedef std::list<std::string>::iterator iterador_campos;
		/**
		 * Definicion del tipo iterador_campos constante.
		 */
		typedef std::list<std::string>::const_iterator iterador_campos_constante;
		/**
		 * Constructor de la clase Clave.
		 */
		Clave() throw();
		/**
		 * Destructor virtual de la clase Clave.
		 */
		virtual ~Clave() throw();
		/**
		 * Agrega un campo a la clave.
		 */
		void agregar_campo(const std::string& nombre_campo) throw();
		/**
		 * Remueve un campo de la clave.
		 */
		void remover_campo(const std::string& nombre_campo) throw();
		/**
		 * Obtiene la cantidad de campos de la clave.
		 */
		unsigned int cantidad_campos() const throw();
		/**
		 * Obtiene un iterador al primer campo de la clave.
		 */
		Clave::iterador_campos primer_campo() throw();
		/**
		 * Obtiene un iterador constante al primer campo de la clave.
		 */
		Clave::iterador_campos_constante primer_campo() const throw();
		/**
		 * Obtiene un iterador al ultimo campo de la clave.
		 */
		Clave::iterador_campos ultimo_campo() throw();
		/**
		 * Obtiene un iterador constante al ultimo campo de la clave.
		 */
		Clave::iterador_campos_constante ultimo_campo() const throw();
		/**
		 * Clona la clase Clave.
		 */
		virtual Clave::puntero clonar() const throw();
	private:
		/**
		 * Almacena la lista de campos.
		 */
		std::list<std::string> listaCampos;
};

#endif /** CLAVE_HPP */

