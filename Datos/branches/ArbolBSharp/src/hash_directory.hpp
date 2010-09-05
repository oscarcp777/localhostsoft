#ifndef HASH_DIRECTORY_HPP_INCLUDED
#define HASH_DIRECTORY_HPP_INCLUDED
#include "almacenamiento.hpp"
#include "hash_bucket.hpp"
#include "EstrategiaAlmacenamientoDirectoryHash.hpp"
#include "EstrategiaAlmacenamientoBucketHash.hpp"

typedef struct{
    int posicion_almacenamiento_bucket;
}RegistroHA;


/**
 * Clase encargada de manejar la tabla de directorios del Hash.
  */
class HashDirectory{

    private:
        int tamanio_bloque;
        int d; //se refiere a la profundidad
        int size; //cantidad de ocupados
        Almacenamiento::puntero almacenamiento_directory;
        Almacenamiento::puntero almacenamiento_bucket;
        EstrategiaAlmacenamientoDirectoryHash * estrategia_directory;
        EstrategiaAlmacenamientoBucketHash * estrategia_bucket;
        RegistroHA directory_registry ;

    public:

        HashDirectory(Almacenamiento::puntero palmacenamiento_directory, Almacenamiento::puntero palmacenamiento_bucket, int ptamanio_bloque);
        ~HashDirectory();

        /**
         * Duplico la tabla.
         */
        void duplicar( int pos_causante );

        /**
         * Verifico si debo de-duplicar la tabla y lo hago.
         */
         void verificar_merge( void );

        /**
         * Obtengo profundidad.
         */
        int obtener_profundidad();

        /**
         * Obtengo tamanio de la tabla.
         */
        int obtener_size();

        /**
         * Obtengo la poscion del bucket en la posicion pos de la tabla.
         */
        int obtener_pos_bucket( int pos );

        /**
         * Obtengo bloque completo correspondiente a la posicion pos.
         */
        HashBucket * obtener_bucket( int pos );

        /**
         * Guardo el bloque en la posicion pos.
         */
        void agregar_bucket( HashBucket * pb, int pos );

};

#endif // HASH_DIRECTORY_HPP_INCLUDED
