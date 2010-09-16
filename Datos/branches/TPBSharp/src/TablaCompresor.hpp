#ifndef TablaCompresor_HPP_INCLUDED
#define TablaCompresor_HPP_INCLUDED

#define MOST_USED 101
#define MAX_UNSIGNED_BYTE_VALUE 256

#include "SymbolContext.hpp"
#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"

/**
* Clase TablaCompresor que define la tabla a usar en el compresor aritmetico
*/
class TablaCompresor: public ContadorReferencias
{
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<TablaCompresor> puntero;
        /**
         * Constructor
         */
        TablaCompresor();
        /**
         * Destructor
         */
        ~TablaCompresor() throw();
        /**
         * Inicializa la tabla
         */
        void inicializar();
        /**
         * Aumenta la frecuencia del simbolo
         */
        void IncrementarFrecuencia(const unsigned char simbolo);
        /**
         * Obtiene la probabilidad de aparicion
         */
        void CalcularProbabilidad(const unsigned char simbolo, double &probabilidadSimboloAnterior, double &probabilidadSimbolo);

    protected:
        /**
         * Contexto del simbolo
         */
        SymbolContext::puntero contextos[MAX_UNSIGNED_BYTE_VALUE];
        /**
         * Contexto actual
         */
        unsigned char contextoActual;
};

#endif // TablaCompresor_HPP_INCLUDED
