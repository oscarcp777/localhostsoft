#include "archivo.hpp"
#include "EstrategiaAlmacenamientoBloques.hpp"
#include "EstrategiaAlmacenamientoCompuestoComprimido.hpp"
#include "EstrategiaRecursoEscrituraDirecta.hpp"
#include "indice_secuencial.hpp"

EstrategiaRecursoEscrituraDirecta::EstrategiaRecursoEscrituraDirecta()
{
    this->posicion_en_almacenamiento = 0;
    this->posicion_en_buffer = 0;
    this->total_en_buffer = 5;
    this->actualmente_en_buffer = (int *) malloc ( sizeof(int) * (this->total_en_buffer+1) );

    for ( int i=0; i<5; i++)
    {
        this->actualmente_en_buffer[i]=-1;
    }
}

EstrategiaRecursoEscrituraDirecta::~EstrategiaRecursoEscrituraDirecta() throw()
{
    free( this->actualmente_en_buffer );
}

int EstrategiaRecursoEscrituraDirecta::proximo_en_buffer( int pos )
{
    int p = this->si_esta_en_buffer( pos );
    if ( p>0)
    {
        return p;
    }
    if (this->posicion_en_buffer < this->total_en_buffer)
    {
        this->posicion_en_buffer++;
        this->actualmente_en_buffer[this->posicion_en_buffer] = pos;
        return this->posicion_en_buffer ;
    }
    else
    {
        this->posicion_en_buffer++;
        this->posicion_en_buffer = 0;
        this->actualmente_en_buffer[this->posicion_en_buffer] = pos;
        return this->posicion_en_buffer ;
    }
}

int EstrategiaRecursoEscrituraDirecta::si_esta_en_buffer( int pos )
{
    for ( int i = 0; i<this->total_en_buffer; i++)
    {
        if (this->actualmente_en_buffer[i]==pos)
            return i;
    }
    return -1;
}

bool EstrategiaRecursoEscrituraDirecta::agregar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer   ) throw()
{
    bool insertado = false;
    TipoAlmacenamiento al = archivo->GetTipoAlmacenamiento();
    this->posicion_en_almacenamiento = estrategia_almacenamiento->AgregarAlFinal(registro, archivo);
    if (al==Bloques)
        ((Archivo::puntero)archivo)->ActualizarEsquemaBloque(((EstrategiaAlmacenamientoBloques::puntero)estrategia_almacenamiento)->GetEsquemaBloque());

    if (this->posicion_en_almacenamiento<0) return insertado;

    int p = this->proximo_en_buffer(this->posicion_en_almacenamiento);

    int aa = buffer->obtener_longitud_en_bytes();
    estrategia_almacenamiento_buffer->Escribir(p , registro, buffer);

    insertado = true;
    registro->agregar_campo("posicionAlmacenamiento", new CampoEntero(this->posicion_en_almacenamiento));

    return insertado;

}

bool EstrategiaRecursoEscrituraDirecta::borrar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer   ) throw()
{
    //Se borro del indice

    return false;
}

Registro::puntero EstrategiaRecursoEscrituraDirecta::buscar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer , IndiceSecuencial::puntero indice_secuencial  ) throw()
{
    //Registro me lo acaba de devolver el indice
    bool encontrado = false;
    int posicion = *((int*) registro->obtener_campo("posicionAlmacenamiento")->obtener_valor());
    estrategia_almacenamiento->SetRegistroConDatosClave(registro);
    estrategia_almacenamiento_buffer->SetRegistroConDatosClave(registro);
    Registro::puntero regLevantado ;
/*
    ComparadorClave::puntero cc;
    if (archivo->GetTipoAlmacenamiento()==Bloques)
        cc = ((EstrategiaAlmacenamientoBloques::puntero )estrategia_almacenamiento)->GetComparador();

    if (archivo->GetTipoAlmacenamiento()==Compresor)
        cc = ((EstrategiaAlmacenamientoCompuestoComprimido::puntero)estrategia_almacenamiento)->GetComparador();

   IndiceSecuencial::puntero is = new IndiceSecuencial( cc );
  */ regLevantado = indice_secuencial->Buscar((Buffer::puntero)buffer, registro, registro->obtener_clave_primaria());
   if ( regLevantado != NULL )
   {
       encontrado = true;
   }

    if (encontrado == false)
    {
        estrategia_almacenamiento->set_por_buffer( false );//OJO ACA
        regLevantado = estrategia_almacenamiento->Leer(posicion, archivo, registro->obtener_clave_primaria());
        estrategia_almacenamiento_buffer->set_por_buffer( true );
        estrategia_almacenamiento_buffer->Escribir( this->proximo_en_buffer(posicion), regLevantado, buffer);
    }

    return regLevantado;
}
