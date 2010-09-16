#ifndef SYMBOLCONTEXT_HPP_INCLUDED
#define SYMBOLCONTEXT_HPP_INCLUDED

#define MAX_UNSIGNED_BYTE_VALUE 256

#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"
/**
* Clase SymbolContext que define un contexto para el simbolo
*/
class SymbolContext: public ContadorReferencias
{
    public:
        /**
        * Define el tipo de dato puntero.
        */
        typedef PunteroIntrusivo<SymbolContext> puntero;
        /**
        * Constructor
        */
        SymbolContext();
        /**
        * Destructor
        */
        virtual ~SymbolContext() throw();
        /**
        * Aumenta la frecuencia del simbolo
        */
        void IncrementarFrecuencia(const unsigned char simbolo);
        /**
        * Calcula la probabilidad del simbolo
        */
        void CalcularProbabilidad(const unsigned char simbolo, double &probabilidadSimboloAnterior, double &probabilidadSimbolo);
    private:
        /**
        * Total
        */
        unsigned int total;
        /**
        * Apariciones del simbolo
        */
        unsigned int *apariciones;
        /**
        * Inicia el contexto del simbolo
        */
        void Iniciar();
};

#endif // SYMBOLCONTEXT_HPP_INCLUDED
