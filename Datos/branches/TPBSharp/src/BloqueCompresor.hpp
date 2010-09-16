#ifndef BLOQUECOMPRESOR_HPP
#define BLOQUECOMPRESOR_HPP

#include "bloque.hpp"
#include "BloqueCompresorHelper.hpp"
#include "registro.hpp"
#include "esquema.hpp"
#include "CompresorAritmetico.hpp"
#include<cstdlib>
#include<cstring>

class BloqueCompresor: public Bloque {
    public:
		/**
		 * Definicion del tipo puntero.
		 */
		typedef PunteroIntrusivo<BloqueCompresor> puntero;
        /**
         * Constructor de la clase BloqueCompresor.
         */
        BloqueCompresor(Esquema::puntero esquema, Clave::puntero clavePrimaria, unsigned int longitud_maxima) throw();
        /**
         * Destructor virtual de la clase BloqueCompresor.
         */
        virtual ~BloqueCompresor() throw();
        /**
		 * Obtiene la longitud administrativa ocupada en bytes del bloque.
		 */
		virtual unsigned int obtener_longitud_administrativa() throw();
		/**
		 * Obtiene la longitud de datos ocupada en bytes del bloqu.
		 */
		virtual unsigned int obtener_longitud_datos() throw();
		/**
		 * Obtiene la longitud ocupada en bytes del bloque.
		 */
		virtual unsigned int obtener_longitud_ocupada() throw();
		/**
		 * Decide si puede agregar un componente.
		 */
		virtual bool puede_agregar_componente(Componente::puntero componente) throw();
		/**
		 * Remueve un componente de la lista de componentes y recomprime la lista obtenida.
		 */
		virtual void remover_componente(BloqueCompresor::iterador_componentes componente) throw();
		/**
		 * Obtener datos comprimidos del compresor.
		 */
		char* obtener_datos_comprimidos() throw();
		/**
		 * Establece los datos comprimidos del compresor.
		 */
		void establecer_datos_comprimidos(char* datosComprimidos, unsigned int longitud_comprimida) throw();
    private:
		/**
		 * Serializa todos los registros del componente compuesto a un stream de strings.
		 */
		void escribir_registros(std::stringstream& buffer) throw();
	        /**
	         * Almacena el esquema usado por el bloque compresor.
        	 */
	        Esquema::puntero esquema;
		/**
		 * ALmacena la clave primaria usada por el bloque compresor.
		 */
		Clave::puntero clavePrimaria;
		/**
		 * ALmacena el compresor aritmetico usado por el bloque compresor.
		 */
		CompresorAritmetico::puntero compresorAritmetico;
		/**
		 * Almacena el buffer con los registros comprimidos del bloque compresor.
		 */
		std::string registrosComprimidos;
};

#endif /** BLOQUECOMPRESOR_HPP */


