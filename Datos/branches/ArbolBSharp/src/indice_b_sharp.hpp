#ifndef INDICE_B_SHARP_H
#define INDICE_B_SHARP_H

#define INSERCION_CORRECTA 0
#define HAY_SOBREFLUJO 1
#define HAY_BALANCEO 2

#include<iostream>

#include "puntero_intrusivo.hpp"

#include "estrategia_indice.hpp"
#include "archivo.hpp"
#include "EstrategiaAlmacenamientoBSharp.hpp"
#include "EstrategiaEspacioLibreBloque.hpp"
#include "esquema.hpp"
#include "clave.hpp"
#include "comparador_clave.hpp"
#include "registro.hpp"
#include "bloque_interno_b_sharp.hpp"
#include "bloque_externo_b_sharp.hpp"
#include "resultado_insercion.hpp"

/**
 * Clase que define una estrategia de indice arbol B sharp.
  */
class IndiceBSharp: public EstrategiaIndice {
	public:
        	/**
	         * Define el tipo de dato puntero.
        	 */
	        typedef PunteroIntrusivo<IndiceBSharp> puntero;
		/**
		 * Constructor de la clase IndiceBSharp.
		 * @param nombre_archivo - El nombre del archivo del indice b sharp.
		 * @param esquema - El esquema de datos del indice b sharp.
		 * @param clave - La clave de datos del indice b sharp.
		 * @param comparador_clave - El comparador de clave de datos del indice b sharp.
		 */
		IndiceBSharp(const std::string& nombre_archivo, unsigned int longitud_bloque, const Esquema::puntero& esquema,
			const Clave::puntero& clave, const ComparadorClave::puntero& comparadorClave) throw();
		/**
		 * Destructor virtual de la clase IndiceBSharp.
		 */
		virtual ~IndiceBSharp() throw();
		/**
		 * Agrega un registro en el indice b sharp.
		 */
		virtual void agregar_registro(Registro::puntero registro) throw();
		/**
		 * Remueve un registro en el indice b sharp.
		 */
		virtual void borrar_registro(Registro::puntero registro) throw();
		/**
		 * Busca un registro en el indice b sharp.
		 */
		virtual Registro::puntero buscar_registro(Registro::puntero registro) throw();
		/**
		 * Imprime el arbol en el stream de salida pasado por parametro.
		 */
		void imprimir(std::ostream& streamSalida) throw();
	private:
		/**
		 * Crea el bloque raiz del indice b sharp.
		 */
		void crear_bloque_raiz() throw();
		/**
		 * Lee el bloque raiz del indice b sharp.
		 */
		void leer_bloque_raiz() throw();
		/**
		 * Escribe el bloque raiz del indice b sharp.
		 */
		void escribir_bloque_raiz() throw();
		/**
		 * Maneja el sobreflujo al dividirse el nodo raiz del indice b sharp cuando es hoja.
		 */
		void manejarDivisionRaizHoja(ResultadoInsercion& resultado, const Registro::puntero& registro) throw();
		/**
		 * Maneja el sobreflujo al dividirse el nodo raiz del indice b sharp cuando es interno.
		 */
		void manejarDivisionRaizInterna(ResultadoInsercion& resultado) throw();
		/**
		 * Inserta un registro en un bloque externo.
		 * @param bloqueExterno - El bloque externo donde insertar el registro.
		 * @param regsitro - El registro a insertar.
		 * @param resultado - El resultado de la insercion del registro en el bloque externo.
		 * @param hermano -  El numero de bloque hermano (derecho por defecto)
		 * @return boolean - Retorna true si hubo division del bloque externo.
		 */
		int insertar_bloque_externo(BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro,
			ResultadoInsercion& resultado, unsigned int bloque_hermano) throw();
		/**
		 * Inserta un registro en un bloque externo no lleno.
		 * @param bloqueExterno - El bloque externo donde insertar el registro.
		 * @param registro - El registro a insertar.
		 */
		void insertar_bloque_externo_no_lleno(BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro) throw();
		/**
		* Une la lista de registros de los bloques izquierdo y derecho, y la devuelve en lista_registros
		*/
		void juntarListasComponentes(Bloque::contenedor_componentes& lista_registros,
				Bloque::contenedor_componentes& registrosBloqueIzquierdo,Bloque::contenedor_componentes& registrosBloqueDerecho) throw();
		/**
		 * Une la lista de ramas de los bloques izquierdo y derecho, y la devuelve en lista_registros
		 */
		void juntarListaRamas(BloqueInternoBSharp::contenedor_ramas& lista_ramas,
				BloqueInternoBSharp::contenedor_ramas& ramasBloqueIzquierdo,BloqueInternoBSharp::contenedor_ramas& ramasBloqueDerecho)throw();
		/**
		* Busca insertar el registro balanceando cargas entre el bloque en cuestion y su hermano (derecho o izquierdo)
		*/
		bool balancearBloquesExternos(const Registro::puntero& registro, BloqueExternoBSharp::puntero& bloqueActual, BloqueExternoBSharp::puntero& bloqueHermano, ResultadoInsercion& resultado) throw();
		/**
		 * Inserta un registro en un bloque externo lleno.
		 * @param bloqueExterno - El bloque externo donde insertar el registro.
		 * @param registro - El registro a insertar.
		 * @param resultado - El resultado de insercion del registro en el bloque externo.
		 */
		void insertar_bloque_externo_lleno(BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro,
			ResultadoInsercion& resultado) throw();
		/**
		 * Inserta un registro en un bloque externo lleno.
		 * @param bloqueExterno - El bloque externo donde insertar el registro.
		 * @param bloqueHermano - El bloque hermano del bloque actual.
		 * @param registro - El registro a insertar.
		 * @param resultado - El resultado de insercion del registro en el bloque externo.
		 */
		void insertar_bloque_externo_lleno2(BloqueExternoBSharp::puntero& bloqueExterno,BloqueExternoBSharp::puntero& bloqueHermano, const Registro::puntero& registro,
						ResultadoInsercion& resultado) throw();
		/**
		 * Inserta un registro en un bloque interno.
		 * @param bloqueInterno - El bloque interno donde insertar el registro.
		 * @param registroClave - El registro con la clave a insertar.
		 * @param resultado - El resultado de la insercion del registro en el bloque interno.
		 * @param hermano -  El numero de bloque hermano (derecho por defecto)
		 * @preturn boolean - Retorna true si hubo division del bloque interno.
		 */
		int insertar_bloque_interno(BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registroClave,
			ResultadoInsercion& resultado, unsigned int bloque_hermano, Registro::puntero& registroPadre) throw();
		/**
		 * Inserta un registro en un bloque interno no lleno.
		 * @param bloqueInterno - El bloque interno donde insertar el registro.
		 * @param registroClave - El registro con la clave a insertar.
		 */
		void insertar_bloque_interno_no_lleno(BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registro,
			unsigned int bloque_derecho) throw();
		/**
		 * Busca insertar el registroClave balanceando cargas entre el bloque en cuestion y su hermano (derecho o izquierdo)
		 */
		bool balancearBloquesInternos(BloqueInternoBSharp::puntero& bloqueInterno, BloqueInternoBSharp::puntero& bloqueHermano, ResultadoInsercion& resultado, Registro::puntero& registroPadre) throw();
		/**
		 * Inserta un registro en un bloque interno lleno.
		 * @param bloqueInterno - El bloque interno donde insertar el registro.
		 * @param registroClave - El registro con la clave a insertar.
		 * @param resultado - El resultado de insercion del registro en el bloque interno.
		 */
		void insertar_bloque_interno_lleno(BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registro,
				unsigned int bloque_izquierdo, unsigned int bloque_derecho, ResultadoInsercion& resultado) throw();
		/**
		 * Inserta un registro en un bloque interno lleno.
		 * @param bloqueInterno - El bloque interno donde insertar el registro.
		 * @param bloqueHermano - El bloque interno hermano del bloque actual.
		 * @param registroClave - El registro con la clave a insertar.
		 * @param resultado - El resultado de insercion del registro en el bloque interno.
		 */
		bool insertar_bloque_interno_lleno2(BloqueInternoBSharp::puntero& bloqueInterno, BloqueInternoBSharp::puntero& bloqueHermano, const Registro::puntero& registro,
				ResultadoInsercion& resultado,Registro::puntero& registroPadre) throw();
		/**
		 * Busca la posicion de insercion externa para el registro dado.
		 * @param registro - El registro a insertar en el bloque externo.
		 * @param primer_registro - Iterador al primer registro del bloque externo.
		 * @param ultimo_registro - Iterador al ultimo registro del bloque externo.
		 * @return unsigned int - La posicion de insercion externa para el registro dado.
		 */
		unsigned int buscar_posicion_insercion_externa(const Registro::puntero& registro, BloqueExternoBSharp::iterador_componentes primer_registro,
			BloqueExternoBSharp::iterador_componentes ultimo_registro) throw();
		/**
		 * Busca la posicion de insercion interna para el registro dado.
		 * @param registro - El registro a insertar en el bloque interno.
		 * @param primer_registro - Iterador al primer registro del bloque interno.
		 * @param ultimo_registro - Iterador al ultimo registro del bloque externo.
		 * @param unsigned int - La posicion de insercion interna para el registro dado.
		 */
		unsigned int buscar_posicion_insercion_interna(const Registro::puntero& registro, BloqueInternoBSharp::iterador_componentes primer_registro,
			BloqueInternoBSharp::iterador_componentes ultimo_registro) throw();
		/**
		 * Calcula el peso promedio de los registros contenidos en los bloques a ser divididos
		 */
		unsigned int calcularPromedio(BloqueBSharp::iterador_componentes actual, BloqueBSharp::iterador_componentes ultimo_registro) throw();
		/**
		 * Busca la rama por la cual insertar o buscar un registro.
		 */
		int buscar_rama(const BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registro) throw();
		/**
		 * Busca la rama hermana, por la cual se balancea (mergea o splitea) si no puede insertar
		 */
		int buscar_rama_hermana(const BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registro) throw();
		/**
		 * Estrae la clave de un registro al momento de hacer un split de un bloque hoja.
		 */
		Registro::puntero extraer_clave(const Registro::puntero& registro) throw();
		/**
		 * Busca un registro en un bloque externo devolviendo el registro coincidente.
		 * @param registro - El registro a buscar en el bloque externo.
		 * @return Registro::puntero - El registro encontrado, o NULL si no se encontro.
		 */
		Registro::puntero buscar_bloque_externo(const BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro) throw();
		/**
		 * Busca un registro en un bloque interno devolviendo el registro coincidente.
		 * @param registro - El registro a buscar en el bloque interno.
		 * @return Registro::puntero - El registro encontrado, o NULL si no se encontro.
		 */
		Registro::puntero buscar_bloque_interno(const BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registro) throw();
		/**
		 * Imprime recursivamente el arbol en el strema de salida.
		 */
		void imprimir_recursivo(const BloqueBSharp::puntero& bloqueActual, std::ostream& streamSalida, unsigned int nivel) throw();
		/**
		 * Imprime un registro en la salida.
		 */
		void imprimir_registro(const Registro::puntero& registro, std::ostream& streamSalida) throw();
		/**
		 * Almacena la longitud de los bloques del indice b sharp.
		 */
		unsigned int longitud_bloque;
		/**
		 * Almacena el archivo del indice b sharp.
		 */
		Archivo::puntero archivoIndice;
		/**
		 * Almacena la estrategia de almacenamiento b sharp.
		 */
		EstrategiaAlmacenamientoBSharp::puntero estrategiaAlmacenamiento;
		/**
		 * Almacena la estrategia de espacio libre b sharp.
		 */
		EstrategiaAlmacenamientoEspacioLibre::puntero estrategiaEspacioLibre;
		/**
		 * Almacena el esquema del indice b sharp.
		 */
		Esquema::puntero esquema;
		/**
		 * Almacena la clave del indice b sharp.
		 */
		Clave::puntero clave;
		/**
		 * Almacena el comparador de clave del indice b sharp.
		 */
		ComparadorClave::puntero comparadorClave;
		/**
		 * Almacena el bloque raiz del indice b sharp.
		 */
		BloqueBSharp::puntero bloqueRaiz;
};

#endif // INDICE_B_SHARP_HPP
