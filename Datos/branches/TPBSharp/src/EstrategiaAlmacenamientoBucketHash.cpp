#include "EstrategiaAlmacenamientoBucketHash.hpp"
#include "CampoStream.hpp"
#include <string.h>

EstrategiaAlmacenamientoBucketHash::EstrategiaAlmacenamientoBucketHash()
{
    this->posicion_disponible = 0;
}

EstrategiaAlmacenamientoBucketHash::~EstrategiaAlmacenamientoBucketHash()
{
}

/*
 * Guardo el bloque y me devuelve la posicion donde entro.
 * El Almacenamiento tiene tamanio fijo minimo
 */
int EstrategiaAlmacenamientoBucketHash::guardar_bloque(HashBucket * bucket, Almacenamiento::puntero almacenamiento)
{
    CampoStream::puntero buffer = new CampoStream();
    char * string_a_escribir = new char[almacenamiento->obtener_longitud_en_bytes()];

    if (bucket->obtener_posicion_almacenamiento()<0)
    {
        bucket->establecer_posicion_almacenamiento( this->posicion_disponible );
        posicion_disponible++;
    }

    //Serializo Header del Bloque

    int dd = bucket->obtener_d();
    int occc = bucket->obtener_occ();
    int ee = bucket->obtener_espacio_libre();
    buffer->insert( (void *) dd, TIPO_CAMPO_ENTERO);
    buffer->insert( (void *) occc, TIPO_CAMPO_ENTERO);
    buffer->insert( (void *) ee, TIPO_CAMPO_ENTERO);

    string clave;
    unsigned int pos;
    int entro = 0;
    while(  entro<occc && bucket->obtener(entro, clave, pos ) )
    {
        entro ++;
        buffer->insert( (void *) clave.length(), TIPO_CAMPO_ENTERO);
        buffer->insert( (string) clave );
        buffer->insert( (void *) pos, TIPO_CAMPO_ENTERO);
    }
    if ( entro == 0 )
    {
        buffer->insert( (void *) entro, TIPO_CAMPO_ENTERO);
        buffer->insert( (void *) entro, TIPO_CAMPO_ENTERO);
    }
    string puntero = buffer->str_string();
    memcpy( string_a_escribir,  puntero.c_str(), buffer->size());

    bool resultado = almacenamiento->escribir(string_a_escribir, bucket->obtener_posicion_almacenamiento());

    delete[] string_a_escribir;

    if ( resultado == false )
        return -1;

    return (bucket->obtener_posicion_almacenamiento());
}


/*
 * Guardo el bloque y me devuelve la posicion donde entro.
 */
HashBucket * EstrategiaAlmacenamientoBucketHash::obtener_bloque( int posicion, Almacenamiento::puntero almacenamiento )
{;
    int tamanio_total = 0;
    int d, espacio_libre, tamanio, occ, posicion_en_almacenamiento;
    int longitud = almacenamiento->obtener_longitud_en_bytes();
    char * a;
    a = (char *) malloc ( longitud );

    almacenamiento->leer( a, posicion );

    CampoStream* buffer = new CampoStream();
    buffer->str( a, longitud );
    buffer->get( tamanio_total );
    buffer->get( d );
    buffer->get( occ );
    buffer->get( espacio_libre );

    HashBucket * hb = new HashBucket( d, longitud );

    if (occ == 0)
    {
        buffer->get(tamanio );
        buffer->get(posicion_en_almacenamiento);
    }
    while( occ > hb->obtener_occ()  )// && (1024-tamanio_acumulado)>espacio_libre && (16+tamanio_acumulado)<tamanio_total )
    {
        buffer->get(tamanio );
        string c;
        buffer->get(c, tamanio);;
        buffer->get(posicion_en_almacenamiento);
        hb->agregar( c, posicion_en_almacenamiento);
    }
    hb->establecer_espacio_libre( espacio_libre );

    free( a );
    delete( buffer );

    if (hb->obtener_posicion_almacenamiento()<0)
       hb->establecer_posicion_almacenamiento( posicion );

    return hb;
}

