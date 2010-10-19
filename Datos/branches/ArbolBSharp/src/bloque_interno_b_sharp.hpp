#ifndef BLOQUE_INTERNO_B_SHARP_HPP
#define BLOQUE_INTERNO_B_SHARP_HPP

#include "puntero_intrusivo.hpp"
#include "bloque_b_sharp.hpp"

/**
 * Clase BloqueInternoBSharp representa a un bloque dentro del index set
 * de un arbol b sharp, que contiene links o ramas a los bloques hijos.
 */
class BloqueInternoBSharp: public BloqueBSharp {
	public:
		/**
		 * Define el tipo de dato puntero.
		 */
		typedef PunteroIntrusivo<BloqueInternoBSharp> puntero;
		/**
		 * Define el tipo de dato contenedor_ramas.
		 */
		typedef std::vector<int> contenedor_ramas;
		/**
		 * Define el tipo de dato iterador_rama.
		 */
		typedef std::vector<int>::iterator iterador_rama;
		/**
		 * Define eltipo de dato interador_rama_constante.
		 */
		typedef std::vector<int>::const_iterator iterador_rama_constante;
		/**
		 * Constructor de la clase BloqueInternoBSharp.
		 * Recibe como parametro la longitud maxima en bytes y el nivel
		 * del bloque en el arbol b sharp.
		 */
		BloqueInternoBSharp(unsigned int longitud_maxima, unsigned int numero_bloque, unsigned int nivel) throw();
		/**
		 * Destructor virtual de la clase BloqueInternoBSharp.
		 */
		virtual ~BloqueInternoBSharp() throw();
		/**
		 * Agrega una rama al bloque interno b sharp.
		 */
		void agregar_rama(int rama) throw();
		void agregar_rama(int rama, BloqueInternoBSharp::iterador_rama posicion) throw();
		/**
		 * Remueve una rama del bloque interno b sharp.
		 */
		void remover_rama(BloqueInternoBSharp::iterador_rama posicion) throw();
		/**
		 * Remueve la ultima rama del bloque interno b sharp.
		 */
		void remover_ultima_rama() throw();
		/**
		 * Transfiere todas las ramas del indice b sharp al contenedor de ramas.
		 */
		void transferir_ramas(BloqueInternoBSharp::contenedor_ramas& contenedor_ramas) throw();
		/**
		 * Elimina todas las ramas del indice b sharp del contenedor de ramas.
		 */
		void vaciar_ramas() throw();
		/**
		 * Verifica si contiene una rama dentro del bloque interno b sharp.
		 */
		bool contiene_rama(int rama) throw();
		/**
		 * Obtiene la rama del bloque interno b sharp dada por posicion.
		 */
		int obtener_rama(unsigned int indice) const throw();
		/**
		 * Obtiene la cantidad de ramas del bloque interno b sharp.
		 */
		unsigned int cantidad_ramas() const throw();
		/**
		 * Obtiene un iterador a la primer rama del bloque interno b sharp.
		 */
		BloqueInternoBSharp::iterador_rama primer_rama() throw();
		/**
		 * Obtiene un iterador a la primer rama del bloque interno b sharp.
		 */
		BloqueInternoBSharp::iterador_rama_constante primer_rama() const throw();
		/**
		 * Obtiene un iterador a la ultima rama del bloque interno b sharp.
		 */
		BloqueInternoBSharp::iterador_rama ultima_rama() throw();
		/**
		 * Obtiene un iterador a la ultima rama del bloque interno b sharp.
		 */
		BloqueInternoBSharp::iterador_rama_constante ultima_rama() const throw();
		/**
         * Decide si puede agregar un componente.
         */
        virtual bool puede_agregar_componente(Componente::puntero componente) const throw();
		/**
		 * Obtiene la longitud ocupada del bloque.
		 */
		virtual unsigned int obtener_longitud_ocupada() const throw();
		/**
		 * Devuelve si hay subflujo o no
		 */
		virtual bool hay_subflujo(unsigned int espacioMin) const throw();
	private:
		/**
		 * Almacena la lista de ramas del bloque interno b sharp.
		 */
		BloqueInternoBSharp::contenedor_ramas listaRamas;
		/**
		 * Devuelve el espacio de metadata utilizado
		 */
		virtual unsigned int obtener_espacio_metadata() const;
};

#endif /** BLOQUE_INTERNO_B_SHARP_HPP */

