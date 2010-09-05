#ifndef ESTRATEGIA_ALMACENAMIENTO_B_SHARP_HPP
#define ESTRATEGIA_ALMACENAMIENTO_B_SHARP_HPP

#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"
#include "archivo.hpp"
#include "bloque_interno_b_sharp.hpp"
#include "bloque_externo_b_sharp.hpp"
#include "esquema.hpp"
#include "RegistroLongitudVariable.hpp"
#include "registro.hpp"
#include "campo_booleano.hpp"
#include "campo_cadena.hpp"
#include "campo_doble.hpp"
#include "campo_entero.hpp"
#include "campo_flotante.hpp"
#include "campo_largo.hpp"
#include<string>
#include<cstring>

/**
 * Clase EstrategiaAlmacenamientoBSharp que define estrategia de almacenamiento
 * de bloques de un arbol B sharp.
 */
class EstrategiaAlmacenamientoBSharp: public ContadorReferencias {
	public:
		/**
		 * Define el tipo de dato puntero.
		 */
		typedef PunteroIntrusivo<EstrategiaAlmacenamientoBSharp> puntero;
		/**
		 * Constructor de la clase EstrategiaAlmacenamientoBSharp.
		 */
		EstrategiaAlmacenamientoBSharp(Esquema::puntero esquema, Clave::puntero clavePrimaria) throw();
		/**
		 * Destructor virtual de la clase EstrategiaAlmacenamientoBSharp.
		 */
		virtual ~EstrategiaAlmacenamientoBSharp() throw();
		/**
		 * Escribe un bloque en el archivo con el numero de bloque dado...
		 */
		bool escribir_bloque(unsigned int numero_bloque, BloqueBSharp::puntero bloque, Archivo::puntero archivo) throw();
		/**
		 * Lee un bloque en el archivo con el numero de bloque dado...
		 */
		BloqueBSharp::puntero leer_bloque(unsigned int numero_bloque, Archivo::puntero archivo) throw();
		/**
		 * Agrega un bloque en el archivo...
		 */
		unsigned int agregar_bloque(BloqueBSharp::puntero bloque, Archivo::puntero archivo) throw();
	private:
		/**
		 * Obtiene el esquema de registros contenidos en los bloques del indice b sharp.
		 */
		Esquema::puntero obtener_esquema() const throw();
		/**
		 * Obtiene la clave primaria de registros contenidos en los bloques del indice b sharp.
		 */
		Clave::puntero obtener_clave_primaria() const throw();
		/**
		 * Escribe un bloque a una cadena de bytes...
		 */
		char* escribir_bloque_en_bytes(BloqueBSharp::puntero bloque) throw();
		/**
		 * Escribe un bloque interno a una cadena de bytes...
		 */
		char* escribir_bloque_interno_en_bytes(BloqueInternoBSharp::puntero bloque) throw();
		/**
		 * Escribe un bloque externo a una cadena de bytes...
		 */
		char* escribir_bloque_externo_en_bytes(BloqueExternoBSharp::puntero bloque) throw();
		/**
		 * Lee un bloque desde una cadena de bytes...
		 */
		BloqueBSharp::puntero leer_bloque_desde_bytes(char* bytes, unsigned int longitud_bytes_bloque) throw();
		/**
		 * Lee un bloque interno desde una cadena de bytes...
		 */
		BloqueInternoBSharp::puntero leer_bloque_interno_desde_bytes(char* bytes, unsigned int longitud_bytes_bloque) throw();
		/**
		 * Lee un bloque externo desde una cadena de bytes...
		 */
		BloqueExternoBSharp::puntero leer_bloque_externo_desde_bytes(char* bytes, unsigned int longitud_bytes_bloque) throw();
		/**
		 * Almacena el esquema de registros contenidos en los bloques del indice b sharp.
		 */
		Esquema::puntero esquema;
		/**
		 * Almacena la clave primaria de registros contenidos en los bloques del indice b sharp.
		 */
		Clave::puntero clavePrimaria;
};

#endif /** ESTRATEGIA_ALMACENAMIENTO_B_SHARP_HPP */

