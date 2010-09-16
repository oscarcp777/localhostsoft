#include "archivo.hpp"
#include "EstrategiaAlmacenamientoBloques.hpp"
#include "EstrategiaRecursoUnAlmacenamiento.hpp"

EstrategiaRecursoUnAlmacenamiento::EstrategiaRecursoUnAlmacenamiento()
{
    this->posicion_en_almacenamiento = 0;
}

EstrategiaRecursoUnAlmacenamiento::~EstrategiaRecursoUnAlmacenamiento() throw()
{
    //dtor
}

bool EstrategiaRecursoUnAlmacenamiento::agregar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer   ) throw()
{
    bool insertado = false;
    TipoAlmacenamiento al = archivo->GetTipoAlmacenamiento();
    this->posicion_en_almacenamiento = estrategia_almacenamiento->AgregarAlFinal(registro, archivo);
    if (al==Bloques)
        ((Archivo::puntero)archivo)->ActualizarEsquemaBloque(((EstrategiaAlmacenamientoBloques::puntero)estrategia_almacenamiento)->GetEsquemaBloque());


    if (this->posicion_en_almacenamiento<0) return insertado;
    insertado = true;
    registro->agregar_campo("posicionAlmacenamiento", new CampoEntero(this->posicion_en_almacenamiento));

    return insertado;
}

bool EstrategiaRecursoUnAlmacenamiento::borrar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer   ) throw()
{
    //Se borro del indice

    return false;
}

Registro::puntero EstrategiaRecursoUnAlmacenamiento::buscar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer , IndiceSecuencial::puntero indice_secuencial  ) throw()
{
    //Registro me lo acaba de devolver el indice
    int posicion = *((int*) registro->obtener_campo("posicionAlmacenamiento")->obtener_valor());
    estrategia_almacenamiento->SetRegistroConDatosClave(registro);
    Registro::puntero regLevantado = estrategia_almacenamiento->Leer(posicion, archivo, registro->obtener_clave_primaria());
    return regLevantado;
}
