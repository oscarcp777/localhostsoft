#include "EstrategiaAlmacenamiento.hpp"

EstrategiaAlmacenamiento::EstrategiaAlmacenamiento() throw()
{
}

EstrategiaAlmacenamiento::~EstrategiaAlmacenamiento() throw()
{
}

bool EstrategiaAlmacenamiento::Escribir(int posicion, Componente::puntero componente, Almacenamiento::puntero almacenamiento)
{
    return true;
}

Componente::puntero EstrategiaAlmacenamiento::Leer(int posicion, Almacenamiento::puntero almacenamiento, Clave::puntero clave)
{
    return 0;
}

int EstrategiaAlmacenamiento::AgregarAlFinal(Componente::puntero componente, Almacenamiento::puntero almacenamiento)
{
    return 0;
}
