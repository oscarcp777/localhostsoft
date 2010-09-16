#ifndef ARCHIVO_HPP
#define ARCHIVO_HPP

#include<string>
#include<fstream>
#include "puntero_intrusivo.hpp"
#include "clave.hpp"
#include "esquema.hpp"
#include "almacenamiento.hpp"

/**
 * Clase Archivo que modela un almacenamiento del tipo archivo
 */
class Archivo: public Almacenamiento {
	public:
		/**
		 * Definicion del tipo de dato puntero.
		 */
		typedef PunteroIntrusivo<Archivo> puntero;
		/**
		 * Constructor de la clase Archivo.
		 */
		Archivo(unsigned int longitud, const std::string& nombre_archivo, TipoAlmacenamiento tipo) throw();
		/**
		 * Constructor de la clase Archivo.
		 */
		Archivo(unsigned int longitud, const std::string& nombre_archivo, Esquema::puntero esquema, std::list<Clave::puntero>& listaClaves, TipoAlmacenamiento tipo) throw();
		/**
		 * Constructor de la clase Archivo.
		 */
		Archivo(unsigned int longitud, const std::string& nombre_archivo, Esquema::puntero esquema, EsquemaBloque::puntero esquemaBloque, std::list<Clave::puntero>& listaClaves, TipoAlmacenamiento tipo) throw();
		/**
		 * Destructor virtual de la clase Archivo.
		 */
		virtual ~Archivo() throw();
		/**
		 * Crea un archivo de datos con el esquema y claves especificado.
		 */
		static void crearModoTexto(const std::string& nombre_archivo, Esquema::puntero esquema, const std::list<Clave::puntero>& listaClaves) throw();
		/**
		 * Crea un archivo de datos con el esquema y claves especificado.
		 */
		static void crearModoBinario(const std::string& nombre_archivo, Esquema::puntero esquema, const std::list<Clave::puntero>& listaClaves) throw();
		/**
		 * Escribe el header en el archivo con el esquema y claves especificado.
		 */
		static void escribirHeaderModoTexto(std::fstream& archivoTemporal, Esquema::puntero esquema, const std::list<Clave::puntero>& listaClaves) throw();
		/**
		 * Escribe el header en el archivo con el esquema y claves especificado.
		 */
		static void escribirHeaderModoBinario(std::fstream& archivoTemporal, Esquema::puntero esquema, const std::list<Clave::puntero>& listaClaves) throw();
		/**
		 * Escribe el esquema del bloque en el archivo.
		 */
		void escribirEsquemaBloqueModoTexto(std::fstream& archivoEsquemaBloque, EsquemaBloque::puntero esquemaBloque);
		/**
		 * Lee el header del archivo con el esquema y claves especificado.
		 */
		void leerHeaderModoTexto() throw();
		/**
		 * Lee el header del archivo con el esquema y claves especificado.
		 */
		void leerHeaderModoBinario() throw();
		/**
		 * Lee el header del archivo con el esquema y claves especificado.
		 */
		void LeerHeader();
		/**
		 * Lee el esquema del bloque
		 */
		void LeerHeaderBloque();
		/**
		 * Lee eel espacio libre en la poscion
		 */
		int LeerEspacioBloque( int posicion ) throw();
		/**
		 * Obtiene la lista de claves de datos del archivo.
		 */
		std::list<Clave::puntero> obtener_claves() const throw();
		/**
		 * Establece el nombre del archivo.
		 */
		void establecer_nombre_archivo(const std::string& nombre_archivo) throw();
		/**
		 * Obtiene el nombre del archivo.
		 */
		std::string obtener_nombre_archivo() const throw();
		/**
		 * Abre el archivo en modo texto.
		 */
		void abrirModoTexto() throw();
		/**
		 * ABre el archivo en modo binario.
		 */
		void abrirModoBinario() throw();
		/**
		 * Cierra el archivo.
		 */
		void cerrar() throw();
		/**
		 * Escribe una secuencia de bytes en el almacenamiento
		 * en la posicion dada por indice.
		 */
		bool escribir(const char* bytes, unsigned int posicion) throw();
		/**
		 * Escribe una secuencia de bytes en el almacenamiento
		 * en la posicion dada por indice.
		 */
		bool escribirTexto(const char* bytes, unsigned int posicion) throw();
		/**
		 * Leer una secuencia de bytes desde el almacenamiento
		 * en la posicion dada por indice.
		 */
		bool leer(char* bytes, unsigned int posicion) throw();
		/**
		 * Agrega una secuencia de bytes en el almacenamiento
		 * al final, devuelve el numero de registro agregado.
		 */
		bool agregar(char* bytes) throw();
		/**
		 * Obtiene la cantidad de registros almacenados en el archivo.
		 */
		unsigned int obtener_cantidad_registros() throw();
		/**
		 * Actualiza el esquema bloque
		 */
		void ActualizarEsquemaBloque(EsquemaBloque::puntero esquemaBloque);

		int GetEspacioLibre();
	private:
		/**
		 * Almacena el nombre del archivo.
		 */
		std::string nombre_archivo;
		/**
		 * Almacena el nombre del archivo que almacena el header.
		 */
		std::string nombre_archivo_header;
		/**
		 * Almacena el nombre del archivo que almacena el esquema del bloque.
		 */
		std::string nombre_archivo_esquemaBloque;
		/**
		 * Almacena el stream usado para el archivo.
		 */
		std::fstream archivo;
		/**
		 * Almacena el stream usado para el esquema de datos guardado en el archivo.
		 */
		std::fstream archivoHeader;
		/**
		 * Almacena el stream usado para el esquema del bloque guardado en el archivo.
		 */
		std::fstream archivoEsquemaBloque;
		/**
		 * Almacena el offset de comienzo de header del archivo.
		 */
		unsigned int offset_header;
};

#endif /** ARCHIVO_HPP */

