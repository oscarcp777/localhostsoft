#include "SymbolContext.hpp"
#include <cstdlib>

SymbolContext::SymbolContext()
{
        apariciones = NULL;
        total = MAX_UNSIGNED_BYTE_VALUE;
}

SymbolContext::~SymbolContext() throw()
{
        if (apariciones != NULL)
            delete [] apariciones;
}

void SymbolContext::Iniciar()
{
        if (apariciones == NULL)
        {
                apariciones = new unsigned int[MAX_UNSIGNED_BYTE_VALUE];

                for (int i = 0; i < MAX_UNSIGNED_BYTE_VALUE; ++i)
                        apariciones[i] = i+1;
        }
}

void SymbolContext::IncrementarFrecuencia(const unsigned char simbolo)
{
        Iniciar();
        total++;

        for (unsigned int i = simbolo ; i < MAX_UNSIGNED_BYTE_VALUE; ++i)
                ++apariciones[i];
}

void SymbolContext::CalcularProbabilidad(const unsigned char simbolo, double &probabilidadSimboloAnterior, double &probabilidadSimbolo)
{
        Iniciar();

        probabilidadSimboloAnterior = 0;
        if (simbolo != 0)
                probabilidadSimboloAnterior = (double) apariciones[simbolo - 1] / total;

        probabilidadSimbolo = (double) apariciones[simbolo] / total;
}
