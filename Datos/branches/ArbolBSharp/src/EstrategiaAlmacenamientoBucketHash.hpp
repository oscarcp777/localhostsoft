#ifndef ESTRATEGIAALMACENAMIENTOBUCKETHASH_HPP_INCLUDED
#define ESTRATEGIAALMACENAMIENTOBUCKETHASH_HPP_INCLUDED
#include "almacenamiento.hpp"
#include "hash_bucket.hpp"

/**
 * Clase que define una estrategia para almecenar los bloques o buckets del Hash.
  */
class EstrategiaAlmacenamientoBucketHash
{
    private:
        Almacenamiento::puntero almacenamiento;
        int posicion_disponible;

    public:
        EstrategiaAlmacenamientoBucketHash();
        ~EstrategiaAlmacenamientoBucketHash();

        /**
         * Guardo el bloque y me devuelve la posicion donde entro.
         */
        int guardar_bloque(HashBucket * bucket, Almacenamiento::puntero almacenamiento);

        /**
         * Obtengo el bloque completo.
         */
        HashBucket * obtener_bloque( int posicion, Almacenamiento::puntero almacenamiento);
};


#endif // ESTRATEGIAALMACENAMIENTOBUCKETHASH_HPP_INCLUDED
