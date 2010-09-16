#include <math.h>
#include "hash_directory.hpp"

HashDirectory::HashDirectory(Almacenamiento::puntero palmacenamiento_directory, Almacenamiento::puntero palmacenamiento_bucket, int ptamanio_bloque)
{
    this->d = 0;
    this->size = 1;
    this->almacenamiento_directory = palmacenamiento_directory;
    this->almacenamiento_bucket = palmacenamiento_bucket;
    this->estrategia_bucket = new EstrategiaAlmacenamientoBucketHash();
    this->estrategia_directory = new EstrategiaAlmacenamientoDirectoryHash();
    this->tamanio_bloque = ptamanio_bloque;
}

HashDirectory::~HashDirectory(){}

int HashDirectory::obtener_profundidad()
{
    return this->d;
}

int HashDirectory::obtener_size()
{
    return this->size;
}

void HashDirectory::duplicar( int pos_causa )
{
    RegistroHA reg;
    this->d++;
    estrategia_directory->guardar_profundidad(this->obtener_profundidad(),this->almacenamiento_directory);
    estrategia_directory->guardar_tamanio_bloque(this->tamanio_bloque, this->almacenamiento_directory);

    for ( int i = 0; i< this->size ; i++)
    {
        int pos_a_copiar = i + pow( 2, (this->d-1));
        reg.posicion_almacenamiento_bucket = estrategia_directory->obtener_registro( i, this->almacenamiento_directory );
        estrategia_directory->guardar_registro( reg.posicion_almacenamiento_bucket, this->almacenamiento_directory, pos_a_copiar );
    }
    this->size = pow( 2, this->d );
}

void HashDirectory::verificar_merge( )
{
    if (this->size == 1)
        return;
    bool merge = true;
    for ( int i = 0; i< (this->size/2) ; i++)
    {
        int pos_a_analizar = i + pow( 2, (this->d-1));
        int posicion_almacenamiento_bucket_1 = estrategia_directory->obtener_registro( i, this->almacenamiento_directory );
        int posicion_almacenamiento_bucket_2 = estrategia_directory->obtener_registro( pos_a_analizar, this->almacenamiento_directory );
        if (posicion_almacenamiento_bucket_1!=posicion_almacenamiento_bucket_2)
            merge = false;
    }

    if (merge == true)
    {
        this->d = this->d - 1;
        this->size = pow( 2, this->d );
        estrategia_directory->guardar_profundidad(this->obtener_profundidad(),this->almacenamiento_directory);
    }
}

HashBucket * HashDirectory::obtener_bucket( int pos )
{
   if (pos < (this->size))
   {
       RegistroHA reg;
       reg.posicion_almacenamiento_bucket = estrategia_directory->obtener_registro( pos, this->almacenamiento_directory );
       return estrategia_bucket->obtener_bloque( reg.posicion_almacenamiento_bucket, this->almacenamiento_bucket );
   }
}

int HashDirectory::obtener_pos_bucket( int pos )
{
   if (pos < (this->size))
   {
       RegistroHA reg;
       reg.posicion_almacenamiento_bucket = estrategia_directory->obtener_registro( pos, this->almacenamiento_directory );
       return reg.posicion_almacenamiento_bucket;
   }
}


void HashDirectory::agregar_bucket( HashBucket * pb, int pos )
{
   RegistroHA reg;
   reg.posicion_almacenamiento_bucket =  estrategia_bucket->guardar_bloque( pb, this->almacenamiento_bucket );
   estrategia_directory->guardar_profundidad(this->obtener_profundidad(),this->almacenamiento_directory);
   estrategia_directory->guardar_tamanio_bloque(this->tamanio_bloque, this->almacenamiento_directory);
   estrategia_directory->guardar_registro( reg.posicion_almacenamiento_bucket, this->almacenamiento_directory, pos );
   if ( pb->obtener_d() < this->obtener_profundidad() )
   {
       pos = pos + pow( 2, pb->obtener_d() );
       while ( pos<this->size )
       {
        estrategia_directory->guardar_registro( reg.posicion_almacenamiento_bucket, this->almacenamiento_directory, pos );
        pos = pos + pow( 2, pb->obtener_d() );
       }
   }
}

