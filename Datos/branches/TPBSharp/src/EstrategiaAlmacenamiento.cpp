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

bool EstrategiaAlmacenamiento::Eliminar(int posicion, Almacenamiento::puntero almacenamiento)
{

}

void EstrategiaAlmacenamiento::SetRegistroConDatosClave( Registro::puntero registro)
{
    return;
}

bool EstrategiaAlmacenamiento::por_buffer()
{
    return porb;
}

void EstrategiaAlmacenamiento::set_por_buffer( bool por_buffer )
{
    porb = por_buffer;
}
