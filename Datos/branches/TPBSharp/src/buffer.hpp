#ifndef BUFFER_HPP
#define BUFFER_HPP

#include<map>
#include<cstring>

#include "puntero_intrusivo.hpp"
#include "almacenamiento.hpp"
#include <string.h>
#include "EsquemaBloque.hpp"

/**
 * Clase Buffer que modela un almacenamiento de tipo buffer
 */
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
		Buffer(unsigned int longitud, TipoAlmacenamiento tipo) throw();
		/**
		 * Constructor de la clase Buffer.
		 */
		Buffer(unsigned int longitud, Esquema::puntero esquema, std::list<Clave::puntero> listaClaves, TipoAlmacenamiento tipo) throw();
		/**
		 * Constructor de la clase Buffer.
		 */
		Buffer(unsigned int longitud, EsquemaBloque::puntero esquemaBloque, Esquema::puntero esquema, std::list<Clave::puntero> listaClaves, TipoAlmacenamiento tipo) throw();
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
		 * Escribe una secuencia de bytes en el almacenamiento
		 * en la posicion dada por indice.
		 */
		virtual bool escribirTexto(const char* bytes, unsigned int posicion) throw();
		/**
		 * Lee una secuencia de bytes desde el almacenamiento
		 * en la posicion dada por indice.
		 */
		virtual bool leer(char* bytes, unsigned int posicion) throw();
		/**
		 * Lee eel espacio libre en la poscion
		 */
		int  LeerEspacioBloque( int posicion ) throw();
		/**
		 * Obtiene la lista de claves de datos del buffer.
		 */
		std::list<Clave::puntero> obtener_claves();
		/**
		 * Obtiene el primer espacio libre en el buffer
		 */
		int GetEspacioLibre();
		/**
		 * Obtiene la primera tira de bytes del buffer
		 */
		Buffer::iterador primero();
		/**
		 * Obtiene la ultima tira de bytes del buffer
		 */
		Buffer::iterador ultimo();

	private:
		std::map<unsigned int, char*> buffer_interno;

		/**
		 * Almacena la lista de claves de datos del archivo.
		 */
		std::list<Clave::puntero> listaClaves;
};

#endif /** BUFFER_HPP */

