#ifndef ALMACENAMIENTO_HPP
#define ALMACENAMIENTO_HPP

#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"
#include "esquema.hpp"
#include "clave.hpp"
#include "EsquemaBloque.hpp"
#include "tipo_almacenamiento.hpp"

/**
 * Clase Almacenamiento que define una interfaz para los tipos de almacenamientos
 */
class Almacenamiento: public ContadorReferencias {
	public:
		/**
		 * Definicion del tipo puntero.
		 */
		typedef PunteroIntrusivo<Almacenamiento> puntero;
		/**
		 * Definicion del tipo iterador_claves.
		 */
		typedef std::list<Clave::puntero>::iterator iterador_claves;
		/**
		 * Destructor virtual de la clase Almacenamiento.
		 */
		virtual ~Almacenamiento() throw();
		/**
		 * Escribe una secuencia de bytes en el almacenamiento
		 * en la posicion dada por indice.
		 */
		virtual bool escribir(const char* bytes, unsigned int posicion) throw() = 0;
		/**
		 * Escribe una secuencia de bytes en el almacenamiento
		 * en la posicion dada por indice.
		 */
		virtual bool escribirTexto(const char* bytes, unsigned int posicion) throw() = 0;
		/**
		 * Lee una secuencia de bytes desde el almacenamiento
		 * en la posicion dada por indice.
		 */
		virtual bool leer(char* bytes, unsigned int posicion) throw() = 0;
        /**
		* Obtiene la longitud en bytes disponibles en el bloque = posicion
		*/
        int GetEspacioBloque( int posicion );
        /**
		* Obteniene la longitud en bytes de cada datoa a almacenar.
		*/
		unsigned int obtener_longitud_en_bytes() const throw();
		/**
         * Obtiene el esquema de los datos almacenados
		*/
		virtual Esquema::puntero GetEsquema();
		/**
         * Obtiene el esquema de los datos almacenados
		*/
		virtual EsquemaBloque::puntero GetEsquemaBloque();
		/**
		 * Obtiene la lista de claves de datos del archivo.
		 */
		virtual std::list<Clave::puntero> GetClaves();
		/**
		 * Lee el header con el esquema y claves especificado.
		 */
		virtual void LeerHeader();
		/**
		 * Lee el espacio libre en un bloque particular.
		 */
		virtual int LeerEspacioBloque( int posicion ) throw() = 0;
		/**
		 * Lee el header con el esquema y claves especificado.
		 */
		virtual void LeerHeaderBloque();
        /**
		 * Actualiza el esquema bloque
		 */
		virtual void ActualizarEsquemaBloque(EsquemaBloque::puntero esquemaBloque);
		/**
		 * Obtiene el proximo espacio libre en el almacenamiento
		 */
		virtual int GetEspacioLibre();
		/**
		 * Indica si se almacenan datos por bloques o registros o texto
		 */
		TipoAlmacenamiento GetTipoAlmacenamiento();

	protected:
		/**
		 * Constructor de la clase Almacenamiento.
		 */
		Almacenamiento(unsigned int longitud, TipoAlmacenamiento tipo) throw();
		/**
		 * Establece la longitud en bytes de cada dato a almacenar.
		 */
		void establecer_longitud_en_bytes(unsigned int longitud) throw();
		/**
		 * Almacena el esquema de los datos guardados en el almacenamiento
		 */
		Esquema::puntero esquema;
		/**
		 * Almacena el esquema de bloques de los datos guardados en el almacenamiento cuando es almacenamiento por bloques
		 */
		EsquemaBloque::puntero esquemaBloque;
		/**
		 * Almacena la lista de claves de datos del archivo.
		 */
		std::list<Clave::puntero> listaClaves;

		TipoAlmacenamiento tipoAlmacenamiento;

	private:
		/**
		 * Almacena la longitud en bytes de cada dato a almacenar.
		 */
		unsigned int longitud_en_bytes;
};

#endif /** ALMACENAMIENTO_HPP */

