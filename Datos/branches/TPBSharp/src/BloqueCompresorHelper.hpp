#ifndef BLOQUE_COMPRESOR_HELPER_HPP
#define BLOQUE_COMPRESOR_HELPER_HPP

#include "CompresorAritmetico.hpp"
#include "campo_booleano.hpp"
#include "campo_cadena.hpp"
#include "campo_doble.hpp"
#include "campo_entero.hpp"
#include "campo_flotante.hpp"
#include "campo_largo.hpp"
#include "clave.hpp"
#include "esquema.hpp"
#include "registro.hpp"
#include "RegistroLongitudVariable.hpp"
#include<sstream>

/**
 * Clase que se encarga de transformar registros een un stream de texto como entrada para el compresor
 * aritmetico de orden 1 usado en el bloque compresor.
 * Ademas lee registros desde un stream de texto como salida del descompresor usado por el bloque compresor.
 */
class BloqueCompresorHelper {
	public:
		/**
		 * Escribe un registro en un stream de texto usando el esquema para conocer todos los campos del registro.
		 */
		static void escribir_registro(Esquema::puntero& esquema, Registro::puntero& registro, std::stringstream& stream) throw();
		/**
		 * Lee un registro desde un stream de texto usando el esquema y clave primaria para conocer todos los campso del registro y la
		 * clave primaria.
		 */
		static Registro::puntero leer_registro(Esquema::puntero& esquema, Clave::puntero& clavePrimaria, std::stringstream& stream) throw();
		/**
		 * Comprime un unico registro usando un compresor aritmetico de orden 1.
		 */
		static std::string comprimir_registro(Esquema::puntero& esquema, Registro::puntero& registro) throw();
};

#endif /** BLOQUE_COMPRESOR_HELPER_HPP */

