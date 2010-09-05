#ifndef BUFFER_HPP
#define BUFFER_HPP

#include<map>
#include<cstring>

#include "puntero_intrusivo.hpp"
#include "almacenamiento.hpp"
#include <string.h>
#include "EsquemaBloque.hpp"

class Buffer: public Almacenamiento {
	public:
		/**
		 * Define el tipo de dato puntero.
		 */
		typedef PunteroIntrusivo<Buffer> puntero;
		/**
		 * Define el tipo de dato iterador.
		 */
		typedef std::map<unsigned int, char*>::iterator iterador;
		/**
		 * Define el tipo de dato iterador constante.
		 */
		typedef std::map<unsigned int, char*>::const_iterator iterador_constante;
		/**
		 * Constructor de la clase Buffer.
		 */
		Buffer(unsigned int longitud) throw();
		/**
		 * Constructor de la clase Buffer.
		 */
		Buffer(unsigned int longitud, Esquema::puntero esquema, std::list<Clave::puntero> listaClaves) throw();
		/**
		 * Constructor de la clase Buffer.
		 */
		Buffer(unsigned int longitud, EsquemaBloque::puntero esquemaBloque, Esquema::puntero esquema, std::list<Clave::puntero> listaClaves) throw();
		/**
		 * Destructor virtual de la clase Buffer.
		 */
		virtual ~Buffer() throw();
		/**
		 * Escribe una secuencia de bytes en el almacenamiento
		 * en la posicion dada por indice.
		 */
		virtual bool escribir(const char* bytes, unsigned int posicion) throw();
		/**
		 * Lee una secuencia de bytes desde el almacenamiento
		 * en la posicion dada por indice.
		 */
		virtual bool leer(char* bytes, unsigned int posicion) throw();
		/**
		 * Obtiene la lista de claves de datos del buffer.
		 */
		std::list<Clave::puntero> obtener_claves();

	private:
		std::map<unsigned int, char*> buffer_interno;

		/**
		 * Almacena la lista de claves de datos del archivo.
		 */
		std::list<Clave::puntero> listaClaves;
};

#endif /** BUFFER_HPP */

