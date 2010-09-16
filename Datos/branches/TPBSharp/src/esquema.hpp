#ifndef ESQUEMA_HPP
#define ESQUEMA_HPP

#include<map>
#include<string>
#include<algorithm>

#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"
#include "tipo_campo.hpp"

/**
 * Clase Esquema que representa el esquema de una clave y / o registro.
 */
class Esquema: public ContadorReferencias {
	public:
		/**
		 * Definicion del tipo puntero.
		 */
		typedef PunteroIntrusivo<Esquema> puntero;
		/**
		 * Definicion del tipo iterador_campos.
		 */
		typedef std::map<std::string, TipoCampo>::iterator iterador_campos;
		/**
		 ^Definicion del tipo iterador_campos_constante.
		*/
		typedef std::map<std::string, TipoCampo>::const_iterator iterador_campos_constante;
		/**
		 * Constructor de la clase Esquema.
		 */
		Esquema() throw();
		/**
		 * Destructor virtual de la clase Esquema.
		 */
		virtual ~Esquema() throw();
		/**
		 * Agrega un tipo de campo de la lista de tipos de campo.
		 */
		void agregar_campo(const std::string& nombre_campo, TipoCampo tipo_campo) throw();
		/**
		 * Remueve un tipo de campo de la lista de tipos de campo.
		 */
		void remover_campo(const std::string& nombre_campo) throw();
		/**
		 * Verifica si contiene un tipo de campo en la lista de tipos de campo.
		 */
		bool contiene_campo(const std::string& nombre_campo) throw();
		/**
		 * Obtiene un tipo de campo de la lista de tipos de campo.
		 */
		TipoCampo obtener_campo(const std::string& nombre_campo) throw();
		/**
		 * Obtiene la cantidad de tipos de campo en la lista.
		 */
		unsigned int cantidad_campos() const throw();
		/**
		 * Obtiene un iterador al primer tipo de campo de la lista de tipos de campo.
		 */
		Esquema::iterador_campos primer_campo() throw();
		/**
		 * Obtiene un iterador constante al primer tipo de campo de la lista de tipos de campo.
		 */
		Esquema::iterador_campos_constante primer_campo() const throw();
		/**
		 * Obtiene un iterador al ultimo tipo de campo de la lista de tipos de campo.
		 */
		Esquema::iterador_campos ultimo_campo() throw();
		/**
		 * Obtiene un iterador constante al ultimo tipo de campo de la lista de tipos de campo.
		 */
		Esquema::iterador_campos_constante ultimo_campo() const throw();
		/**
		 * Metodo clonar de la clase Esquema.
		 */
		virtual Esquema::puntero clonar() const throw();
	private:
		/**
		 * Almacena la lista de tipos de campo.
		 */
		std::map<std::string, TipoCampo> listaCampos;
};

#endif /** ESQUEMA_HPP */

