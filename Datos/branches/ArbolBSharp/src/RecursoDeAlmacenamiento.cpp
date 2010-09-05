#include "RecursoDeAlmacenamiento.hpp"

RecursoDeAlmacenamiento::RecursoDeAlmacenamiento(EstrategiaRecurso::puntero estRecur, EstrategiaAlmacenamiento::puntero estAlmac, EstrategiaIndice::puntero estIndice, Almacenamiento::puntero parchivo, Almacenamiento::puntero pbuffer)
{
    this->estrategia_almacenamiento = estAlmac;
    this->estrategia_indice = estIndice;
    this->estrategia_recurso = estRecur;
    this->archivo = parchivo;
    this->buffer = pbuffer;
}

RecursoDeAlmacenamiento::~RecursoDeAlmacenamiento() throw()
{
    //dtor
}


Registro::puntero RecursoDeAlmacenamiento::buscar_registro( Registro::puntero registro_consulta )
{
    Registro::puntero registro_encontrado;
    registro_encontrado = this->estrategia_indice->buscar_registro( registro_consulta );
    if (registro_encontrado==NULL)
        return NULL;
    //OJO -> indice debe devolver un registro con obtener_campo("posicionAlmacenamiento") valido
    return this->estrategia_recurso->buscar_registro( registro_encontrado, this->archivo, this->buffer, this->estrategia_almacenamiento );
}

bool RecursoDeAlmacenamiento::agregar_registro( Registro::puntero registro )
{
    this->estrategia_recurso->agregar_registro( registro, this->archivo, this->buffer, this->estrategia_almacenamiento  );

    if (this->estrategia_indice!=NULL)
    {
        this->estrategia_indice->agregar_registro( registro );
    }

    return true;
}

bool RecursoDeAlmacenamiento::remover_registro( Registro::puntero registro )
{
    this->estrategia_recurso->borrar_registro( registro, this->archivo, this->buffer, this->estrategia_almacenamiento  );

    if (this->estrategia_indice!=NULL)
        this->estrategia_indice->borrar_registro( registro );

    return true;
}
