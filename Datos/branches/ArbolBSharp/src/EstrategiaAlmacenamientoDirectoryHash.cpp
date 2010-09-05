#include "EstrategiaAlmacenamientoDirectoryHash.hpp"
#include "CampoStream.hpp"
#include <string.h>

EstrategiaAlmacenamientoDirectoryHash::EstrategiaAlmacenamientoDirectoryHash()
{
}

EstrategiaAlmacenamientoDirectoryHash::~EstrategiaAlmacenamientoDirectoryHash()
{
}

bool EstrategiaAlmacenamientoDirectoryHash::guardar_profundidad( int d, Almacenamiento::puntero almacenamiento )
{
    return guardar_registro( d, almacenamiento, -2);
}


bool EstrategiaAlmacenamientoDirectoryHash::guardar_tamanio_bloque( int tam, Almacenamiento::puntero almacenamiento )
{
    return guardar_registro( tam, almacenamiento, -1);
}

int EstrategiaAlmacenamientoDirectoryHash::obtener_profundidad( Almacenamiento::puntero almacenamiento )
{
    return obtener_registro( -2 , almacenamiento);
}


int EstrategiaAlmacenamientoDirectoryHash::obtener_tamanio_bloque(Almacenamiento::puntero almacenamiento  )
{
    return obtener_registro( -1, almacenamiento );
}

/*
 * Guardo el bloque y me devuelve la posicion donde entro.
 * El Almacenamiento tiene tamanio fijo minimo
 */
bool EstrategiaAlmacenamientoDirectoryHash::guardar_registro( int bucket_position, Almacenamiento::puntero almacenamiento, int posicion)
{
    CampoStream::puntero buffer = new CampoStream();
    posicion = posicion + 2;
    char * string_a_escribir = new char[almacenamiento->obtener_longitud_en_bytes()+1];

    buffer->insert( bucket_position );

    string puntero = buffer->str_string();
    memcpy( string_a_escribir,  puntero.c_str(), buffer->size());

    bool resultado = almacenamiento->escribir(string_a_escribir, posicion );

    delete[] string_a_escribir;

    return resultado;

}

int EstrategiaAlmacenamientoDirectoryHash::obtener_registro( int posicion, Almacenamiento::puntero almacenamiento)
{
    posicion = posicion + 2;
    int bucket_directory=999;
    int tamanio_total = 0;
    //int tamanio = 0;
    int longitud = almacenamiento->obtener_longitud_en_bytes();
    char * a;
    a = (char *) malloc ( longitud );

    almacenamiento->leer( a, posicion );

    CampoStream::puntero buffer = new CampoStream();

    buffer->str( a, longitud  );

    buffer->get( tamanio_total );
    buffer->get( bucket_directory );

    free( a );

    return bucket_directory;

}
