#include "EstrategiaRecursoEscrituraDiferida.hpp"

EstrategiaRecursoEscrituraDiferida::EstrategiaRecursoEscrituraDiferida()
{
    //ctor
}

EstrategiaRecursoEscrituraDiferida::~EstrategiaRecursoEscrituraDiferida() throw()
{
    //dtor
}

bool EstrategiaRecursoEscrituraDiferida::agregar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento  ) throw()
{
    return NULL;
}

bool EstrategiaRecursoEscrituraDiferida::borrar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento  ) throw()
{
    return false;
}

Registro::puntero EstrategiaRecursoEscrituraDiferida::buscar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento   ) throw()
{
    return NULL;
}
