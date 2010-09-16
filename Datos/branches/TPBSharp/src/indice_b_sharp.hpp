#ifndef INDICE_B_SHARP_H
#define INDICE_B_SHARP_H

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
#include "resultado_balanceo.hpp"

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
		 * Maneja el sobreflujo al dividirse el nodo raiz del indice b sharp.
		 */
		void manejar_sobreflujo_raiz(ResultadoInsercion& resultado) throw();
		/**
		 * Maneja el subflujo al balancearse o fusionarse dos bloques hijos del bloque raiz del indice b sharp.
		 */
		void manejar_subflujo_raiz() throw();
		/**
		 * Inserta un registro en un bloque externo.
		 * @param bloqueExterno - El bloque externo donde insertar el registro.
		 * @param regsitro - El registro a insertar.
		 * @param resultado - El resultado de la insercion del registro en el bloque externo.
		 * @return boolean - Retorna true si hubo division del bloque externo.
		 */
		bool insertar_bloque_externo(BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro,
			ResultadoInsercion& resultado) throw();
		/**
		 * Inserta un registro en un bloque externo no lleno.
		 * @param bloqueExterno - El bloque externo donde insertar el registro.
		 * @param registro - El registro a insertar.
		 */
		void insertar_bloque_externo_no_lleno(BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro) throw();
		/**
		 * Inserta un registro en un bloque externo lleno.
		 * @param bloqueExterno - El bloque externo donde insertar el registro.
		 * @param registro - El registro a insertar.
		 * @param resultado - El resultado de insercion del registro en el bloque externo.
		 */
		void insertar_bloque_externo_lleno(BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro,
			ResultadoInsercion& resultado) throw();
		/**
		 * Inserta un registro en un bloque interno.
		 * @param bloqueInterno - El bloque interno donde insertar el registro.
		 * @param registroClave - El registro con la clave a insertar.
		 * @param resultado - El resultado de la insercion del registro en el bloque interno.
		 * @preturn boolean - Retorna true si hubo division del bloque interno.
		 */
		bool insertar_bloque_interno(BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registroClave,
			ResultadoInsercion& resultado) throw();
		/**
		 * Inserta un registro en un bloque interno no lleno.
		 * @param bloqueInterno - El bloque interno donde insertar el registro.
		 * @param registroClave - El registro con la clave a insertar.
		 */
		void insertar_bloque_interno_no_lleno(BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registro, 
			unsigned int bloque_derecho) throw();
		/**
		 * Inserta un registro en un bloque interno lleno.
		 * @param bloqueInterno - El bloque interno donde insertar el registro.
		 * @param registroClave - El registro con la clave a insertar.
		 * @param resultado - El resultado de insercion del registro en el bloque interno.
		 */
		void insertar_bloque_interno_lleno(BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registro, 
			unsigned int bloque_derecho, ResultadoInsercion& resultado) throw();
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
		 * Busca la rama por la cual insertar o buscar un registro.
		 */
		int buscar_rama(const BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registro) throw();
		/**
		 * Estrae la clave de un registro al momento de hacer un split de un bloque hoja.
		 */
		Registro::puntero extraer_clave(const Registro::puntero& registro) throw();
		/**
		 * Remueve un registro en un bloque externo.
		 * @param bloqueExterno - El bloque externo donde borrar el regsitro.
		 * @param registro - El registro a borar del bloque externo.
		 * @return bool - Retorna true si hubo subflujo en el bloque externo.
		 */
		bool remover_bloque_externo(BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro) throw();
		/**
		 * Remueve un registro en un bloque interno.
		 * @param bloqueInterno - El bloque interno donde borrar el registtro.
		 * @param registroClave - El registro con la clave a borrar.
		 * @param resultadoBalanceo - El resultado de balancear bloques luego de borrado.
		 */
		bool remover_bloque_interno(BloqueInternoBSharp::puntero& bloqueINterno, const Registro::puntero& registro,
			ResultadoBalanceo& resultadoBalanceo) throw();
		/**
		 * Borra el bloque mas a la izquierda o mas a la derecha cuando esta completamente vacio.
		 * @param bloqueBorrar - El bloque a borrar.
		 */
		void borrar_bloque(BloqueBSharp::puntero& bloqueBorrar) throw();
		/**
		 * Actualiza el bloque padre luego de haber borrado a un bloque hijo mas a la izquierda o mas a al derecha.
		 * @param bloquePadre
		 * @param izquierda
		 */
		void actualizar_borrado(BloqueInternoBSharp::puntero& bloquePadre, bool izquierdo) throw(); 
		/**
		 * Balancea el primer bloque con el segundo bloque, el segundo bloque.
		 * @param primerBloque - Primer bloque a balancear.
		 * @param segundoBloque - Segundo bloque a balancear, debe ser hermano derecho del primer bloque.
		 */
		void balancear_bloques(BloqueBSharp::puntero& primerBloque, BloqueBSharp::puntero& segundoBloque, ResultadoBalanceo& resultado) throw();
		/**
		 * Verifica el primer bloque puede ser fusionado con el segundo bloque.
		 * @param primerBloque - Primer bloque a fusionar.
		 * @param segundoBloque - Segundo bloque a fusionar.
		 * @return boolean - Retorna true si ambos bloques se pueden fusionar.
		 */
		bool puede_fusionar_bloques(BloqueBSharp::puntero& primerBloque, BloqueBSharp::puntero& segundoBloque) throw();
		/**
		 * Fusiona el primer bloque con el segundo bloque, el segundo bloque es removido del indice b sharp.
		 * @param primerBloque - Primer bloque a fusionar.
		 * @param segundBloque - Segundo bloque a fusionar, debe ser hermano derecho del primer bloque.
		 */
		void fusionar_bloques(BloqueBSharp::puntero& primerBloque, BloqueBSharp::puntero& segundoBloque) throw();
		/**
		 * Busca el hermano izquierdo de un bloque, si existe lo devuelve, sino devuelve NULL.
		 * @param bloquePadre - Bloque padre del bloque a buscar su hermano.
		 * @param bloqueHijo - Bloque del cual buscar su hermano.
		 * @return BloqueBSharp::puntero - Retorna el bloque hermano izquierdo si existe, sino devuelve NULL.
		 */
		BloqueBSharp::puntero buscar_hermano_izquierdo(BloqueInternoBSharp::puntero& bloquePadre, BloqueBSharp::puntero& bloqueHijo) throw();
		/**
		 * Busca el hermano derecho de un bloque, si existe lo devuelve, sino devuelve NULL.
		 * @param bloquePadre - Bloque padre del bloque a buscar su hermano.
		 * @param bloqueHijo . Bloque del cual buscar su hermano.
		 * @return BloqueBSharp::puntero - Retorna el bloque hermano derecho si existe, sino devuelve NULL.
		 */
		BloqueBSharp::puntero buscar_hermano_derecho(BloqueInternoBSharp::puntero& bloquePadre, BloqueBSharp::puntero& bloqueHijo) throw();
		/**
		 * Actualiza un bloque interno luego de una operacion de balanceo entre sus bloques hijos.
		 * @param bloqueInterno - Bloque interno a actualizar padre de ambos hijos balanceados.
		 * @param resultadoBalanceo - El resultado de la operacion de balanceo.
		 */
		void actualizar_balanceo(BloqueInternoBSharp::puntero& bloqueInterno, ResultadoBalanceo& resultadoBalanceo) throw();
		/**
		 * Actualiza un bloque interno lueg de una operacion de fusion entre sus bloques hijos.
		 * @param bloqueInterno - Bloque interno a actualizar, padre de ambos hijos fusionados.
		 * @param numero_bloque_eliminado - Numero de bloque eliminado como parte de la fusion (Hermano derecho).
		 */
		void actualizar_fusion(BloqueInternoBSharp::puntero& bloqueInterno, int numero_bloque_eliminado) throw();
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
