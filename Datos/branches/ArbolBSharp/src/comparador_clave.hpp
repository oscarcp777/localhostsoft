#ifndef COMPARADOR_CLAVE_HPP
#define COMPARADOR_CLAVE_HPP

#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"
#include "clave.hpp"
#include "registro.hpp"

class ComparadorClave: public ContadorReferencias {
    public:
        /**
         * Definicion del tipo de dato puntero.
         */
        typedef PunteroIntrusivo<ComparadorClave> puntero;
        /**
         * Constructor de la clase ComparadorClave.
         */
        ComparadorClave() throw();
        /**
         * Destructor virtual de la clase ComparadorClave.
         */
        virtual ~ComparadorClave() throw();
        /**
         * Compara dos claves y devuelve si clave1 es menor que clave2.
         */
        virtual bool es_menor(Clave::puntero clave, Registro::puntero registro1, Registro::puntero registro2) const throw() = 0;
        /**
         * Compara dos claves y devuelve si clave1 es mayor que clave 2.
         */
        virtual bool es_mayor(Clave::puntero clave, Registro::puntero registro1, Registro::puntero registro2) const throw() = 0;
        /**
         * Compara dos claves y devuelve si clave 1 es igual a clave 2.
         */
        virtual bool es_igual(Clave::puntero clave, Registro::puntero registro1, Registro::puntero registro2) const throw() = 0;
};

#endif // COMPARADOR_CLAVE_HPP
