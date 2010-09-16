#include "TablaCompresor.hpp"

TablaCompresor::TablaCompresor()
{
    this->inicializar();
}

void TablaCompresor::inicializar()
{
    contextoActual = MOST_USED;
    for ( int i = 0; i<MAX_UNSIGNED_BYTE_VALUE; i++)
        contextos[i] = new SymbolContext();
}

TablaCompresor::~TablaCompresor() throw()
{
}

void TablaCompresor::IncrementarFrecuencia(const unsigned char simbolo)
{
    contextos[contextoActual]->IncrementarFrecuencia(simbolo);
    contextoActual = simbolo;
}

void TablaCompresor::CalcularProbabilidad(const unsigned char simbolo, double &probabilidadSimboloAnterior, double &probabilidadSimbolo)
{
    contextos[contextoActual]->CalcularProbabilidad(simbolo, probabilidadSimboloAnterior, probabilidadSimbolo);
}
