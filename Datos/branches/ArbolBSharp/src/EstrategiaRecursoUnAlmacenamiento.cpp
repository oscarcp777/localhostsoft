#include "EstrategiaRecursoUnAlmacenamiento.hpp"


EstrategiaRecursoUnAlmacenamiento::EstrategiaRecursoUnAlmacenamiento()
{
    //ctor
}

EstrategiaRecursoUnAlmacenamiento::~EstrategiaRecursoUnAlmacenamiento() throw()
{
    //dtor
}

bool EstrategiaRecursoUnAlmacenamiento::agregar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento  ) throw()
{
    return NULL;
}

bool EstrategiaRecursoUnAlmacenamiento::borrar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento  ) throw()
{
    return false;
}

Registro::puntero EstrategiaRecursoUnAlmacenamiento::buscar_registro(  Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento   ) throw()
{
    return NULL;
}
