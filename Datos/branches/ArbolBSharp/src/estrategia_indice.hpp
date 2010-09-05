#ifndef ESTRATEGIA_INDICE_H
#define ESTRATEGIA_INDICE_H

#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"
#include "esquema.hpp"
#include "registro.hpp"

/**
 * Clase abstracta que define una estrategia de indice.
  * Define metodos comunes a todas las estrategias de indice.
  */
class EstrategiaIndice: public ContadorReferencias {
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<EstrategiaIndice> puntero;
        /**
         * Destructor virtual de la clase EstrategiaIndice.
         */
        virtual ~EstrategiaIndice() throw();
	/**
	 * Obtiene la clave primaria usada para ordenar...
	 */
	Clave::puntero obtener_clave_primaria() const throw();
        /**
         * Agrega un registro en el indice.
         */
         virtual void agregar_registro(Registro::puntero registro) throw() = 0;
         /**
          * Borra un registro del indice.
          */
         virtual void borrar_registro(Registro::puntero registro) throw() = 0;
         /**
          * Obtiene la posicion en almacenamiento del registro.
          */
         virtual Registro::puntero  buscar_registro(Registro::puntero registro) throw() = 0;
    protected:
        /**
         * Constructor de la clase EstrategiaIndice.
         */
         EstrategiaIndice(Clave::puntero clavePrimaria) throw();
    private:
	/**
	 * Establece la clave primaria usada para ordenar...
	 */
	Clave::puntero clavePrimaria;
};

#endif // ESTRATEGIA_INDICE_H
