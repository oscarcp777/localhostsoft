#include "EstrategiaRecursoEscrituraDirecta.hpp"

EstrategiaRecursoEscrituraDirecta::EstrategiaRecursoEscrituraDirecta()
{
    this->posicion_en_almacenamiento = 0;
}

EstrategiaRecursoEscrituraDirecta::~EstrategiaRecursoEscrituraDirecta() throw()
{
    //dtor
}

bool EstrategiaRecursoEscrituraDirecta::agregar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento  ) throw()
{
    bool insertado = false;
    if(estrategia_almacenamiento->Escribir(this->posicion_en_almacenamiento,registro,archivo))
        insertado = true;

    registro->agregar_campo("posicionAlmacenamiento", new CampoEntero(this->posicion_en_almacenamiento));

    this->posicion_en_almacenamiento ++;

    return insertado;

/*  ASI DEBERIA SER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    EL PROBLEMA ES QUE ESCRIBIR NO DEVUELVE NUNCA FALSO PARA REGISTROS!!!!!!
    bool insertado = false;
    if(estrategia_almacenamiento->Escribir(this->posicion_en_almacenamiento,registro,archivo))
        insertado = true;

    while (insertado == false)
    {
        this->posicion_en_almacenamiento ++;
        if (estrategia_almacenamiento->Escribir(this->posicion_en_almacenamiento,registro,archivo))
            insertado = true;
    }

    registro->agregar_campo("posicionAlmacenamiento", new CampoEntero(this->posicion_en_almacenamiento));
*/
}

bool EstrategiaRecursoEscrituraDirecta::borrar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento  ) throw()
{
    //Se borro del indice

    return false;
}

Registro::puntero EstrategiaRecursoEscrituraDirecta::buscar_registro(  Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero Buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento   ) throw()
{
    //Registro me lo acaba de devolver el indice
    int posicion = *((int*) registro->obtener_campo("posicionAlmacenamiento")->obtener_valor());
    RegistroLongitudVariable::puntero regLevantado = estrategia_almacenamiento->Leer(posicion, archivo, registro->obtener_clave_primaria());
    return regLevantado;
}
