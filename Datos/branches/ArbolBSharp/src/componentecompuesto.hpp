#ifndef COMPONENTE_COMPUESTO_HPP
#define COMPONENTE_COMPUESTO_HPP

#include<vector>
#include<algorithm>

#include "puntero_intrusivo.hpp"
#include "componente.hpp"

/**
 * Clase componente que a su vez es contenedor de otros componentes.
 */
class ComponenteCompuesto: public Componente {
	public:
		/**
		 * Definicion del tipo puntero.
		 */
		typedef PunteroIntrusivo<ComponenteCompuesto> puntero;
		/**
		 * Definicion del tipo contenedor_componentes.
		 */
		typedef std::vector<Componente::puntero> contenedor_componentes;
		/**
		 * Definicion del tipo iterador.
		 */
		typedef std::vector<Componente::puntero>::iterator iterador_componentes;
		/**
		 * Definicion del tipo iterador_constante.
		 */
		typedef std::vector<Componente::puntero>::const_iterator iterador_componentes_constante;
		/**
		 * Constructor de la clase ComponenteCompuesto.
		 */
		ComponenteCompuesto() throw();
		/**
		 * Destructor virtual de la clase ComponenteCompuesto.
		 */
		virtual ~ComponenteCompuesto() throw();
		/**
		 * Agrega un componente a la lista de componentes.
		 */
		virtual void agregar_componente(Componente::puntero componente) throw();
		/**
		 * Agrega un componente a la lista de componentes antes del componente especificado.
		 */
		virtual void agregar_componente(Componente::puntero componente, ComponenteCompuesto::iterador_componentes posicion) throw();
		/**
		 * Remueve un componente de la lista de componentes.
		 */
		virtual void remover_componente(Componente::puntero componente) throw();
		/**
		 * Transfiere todos los componentes de la lista de componentes, a la lista de componentes pasada por parametro
		 * vaciando el componente compuesto.
		 */
		virtual void transferir_componentes(ComponenteCompuesto::contenedor_componentes& contenedor_componentes) throw(); 
		/**
		 * Verifica si contiene un componente en la lista de componentes.
		 */
		virtual bool contiene_componente(Componente::puntero componente) throw();
		/**
		 * Obtiene el componente en el indice #indice# de la lista de componentes.
		 */
		Componente::puntero obtener_componente(unsigned int indice) throw();
		/**
		 * Obtiene la cantidad de componentes en la lista.
		 */
		unsigned int cantidad_componentes() const throw();
		/**
		 * Obtiene un iterador al primer componente de la lista de componentes.
		 */
		virtual ComponenteCompuesto::iterador_componentes primer_componente() throw();
		/**
		 * Obtiene un iterador constante al primer componente de la lista de componentes.
		 */
		virtual ComponenteCompuesto::iterador_componentes_constante primer_componente() const throw();
		/**
		 * Obtiene un iterador al ultimo componente de la lista de componentes.
		 */
		virtual ComponenteCompuesto::iterador_componentes ultimo_componente() throw();
		/**
		 * Obtiene un iterador al ultimo componente de la lista de componentes.
		 */
		virtual ComponenteCompuesto::iterador_componentes_constante ultimo_componente() const throw();
	private:
		/**
		 * Almacena la lista de componentes.
		 */
		ComponenteCompuesto::contenedor_componentes listaComponentes;
};

#endif /** COMPONENTE_COMPUESTO_HPP */

