#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include<list>
#include<map>
#include<algorithm>

#include "puntero_intrusivo.hpp"
#include "componente.hpp"
#include "clave.hpp"
#include "campo.hpp"

/**
 * Clase base para el tipo de componente registro.
 */
class Registro: public Componente {
	public:
		/**
		 * Definicion del tipo puntero.
		 */
		typedef PunteroIntrusivo<Registro> puntero;
		/**
		 * Definicion del tipo iterador claves.
		 */
		typedef std::list<Clave::puntero>::iterator iterador_claves;
		/**
		 * Definicion del tipo iterador claves constante.
		 */
		typedef std::list<Clave::puntero>::const_iterator iterador_claves_constante;
		/**
		 * Definicion del tipo iterador campos.
		 */
	        typedef std::map<std::string, Campo::puntero>::iterator iterador_campos;
		/**
		 * Definicion del tipo iterador campos constante.
		 */
        typedef std::map<std::string, Campo::puntero>::const_iterator iterador_campos_constante;
        /**
         * Destructor virtual de la clase Registro.
         */
        ~Registro() throw();
		/**
		 * Establece la clave primaria del registro.
		 */
		void establecer_clave_primaria(Clave::puntero clave) throw();
		/**
		 * Obtiene la clave primaria del registro.
		 */
		Clave::puntero obtener_clave_primaria() const throw();
		/**
		 * Agrega una clave secundaria al registro.
		 */
		void agregar_clave_secundaria(Clave::puntero clave) throw();
		/**
		 * Remueve una clave secundaria del registro.
		 */
		void remover_clave_secundaria(Clave::puntero clave) throw();
		/**
		 * Obtiene la cantidad de claves secundarias del registro.
		 */
		unsigned int cantidad_claves_secundarias() const throw();
		/**
		 * Obtiene un iterador a la primer clave secundaria del registro.
		 */
		Registro::iterador_claves primer_clave_secundaria() throw();
		/**
		 * Obtiene un iterador constante a la primer clave secundaria del registro.
		 */
		Registro::iterador_claves_constante primer_clave_secundaria() const throw();
		/**
		 * Obtiene un iterador a la ultima clave secundaria del registro.
		 */
		Registro::iterador_claves ultima_clave_secundaria() throw();
		/**
		 * Obtiene un iterador constante a la ultima clave secundaria del registro.
		 */
		Registro::iterador_claves_constante ultima_clave_secundaria() const throw();
		/**
		 * Agrega un campo al registro.
		 */
		virtual void agregar_campo(const std::string& nombre_campo, Campo::puntero campo) throw();
		/**
		 * Remueve un campo del registro.
		 */
		virtual void remover_campo(const std::string& nombre_campo) throw();
		/**
		 * Verifica si el registro contiene un campo.
		 */
		virtual bool contiene_campo(const std::string& nombre_campo) const throw();
		/**
		 * Obtiene la cantidad de campos del registro.
		 */
		virtual unsigned int cantidad_campos() const throw();
		/**
		 * Obtiene un campo del registro.
		 */
		virtual Campo::puntero obtener_campo(const std::string& nombre_campo) const throw();
		/**
		 * Obtiene la longitud en bytes del registro.
		 */
		unsigned int GetLongitudBytes() const throw();

		unsigned int GetLongitudBytesAlmacenada() const throw();
		/**
		 * Obtiene un iterador al primer campo del registro.
		 */
		Registro::iterador_campos primer_campo() throw();
		/**
		 * Obtiene un iterador constante al primer campo del registro.
		 */
		Registro::iterador_campos_constante primer_campo() const throw();
		/**
		 * Obtiene un iterador al ultimo campo del registro.
		 */
		Registro::iterador_campos ultimo_campo() throw();
		/**
		 * Obtiene un iterador constante al ultimo campo del registro.
		 */
		Registro::iterador_campos_constante ultimo_campo() const throw();
		/**
		 * Clona la clase registro.
		 */
		virtual Registro::puntero clonar() const throw();
		/**
		 * Devuelve la cantidad de campos
		 */
		int GetCantidadDeCampos();
        /**
		 * Vacia la lista de campos agregados al registro
		 */
		void ClearCampos();
    protected:
		/**
		 * Constructor de la clase Registro.
		 */
		Registro(Clave::puntero clave_primaria) throw();
		/**
		 * Almacena la clave primaria del registro.
		 */
	        Clave::puntero clavePrimaria;
		/**
		 * Almacena la lista de claves secundarias del registro.
		 */
		std::list<Clave::puntero> listaClaves;
		/**
		 * Almacena la lista de campos del registro.
		 */
		std::map<std::string, Campo::puntero> listaCampos;
};

#endif /** REGISTRO_HPP */

