#ifndef ESTRATEGIAALMACENAMIENTODIRECTORYHASH_HPP_INCLUDED
#define ESTRATEGIAALMACENAMIENTODIRECTORYHASH_HPP_INCLUDED
#include "almacenamiento.hpp"
#include <stdlib.h>
#include <stdio.h>

/**
 * Clase que define una estrategia para almacenar la tabla de directorios del Hash.
  */
class EstrategiaAlmacenamientoDirectoryHash
{
    private:
        Almacenamiento::puntero almacenamiento;

    public:
        EstrategiaAlmacenamientoDirectoryHash();
        ~EstrategiaAlmacenamientoDirectoryHash();

        /**
         * Guardo el registro con la posicion del bloque.
         */
        bool guardar_registro(int bucket_position, Almacenamiento::puntero almacenamiento, int posicion);

        /**
         * Guarda la profundidad.
         */
        bool guardar_profundidad(int d, Almacenamiento::puntero almacenamiento);

        /**
         * Guarda el tamanio del bloque.
         */
        bool guardar_tamanio_bloque(int tam, Almacenamiento::puntero almacenamiento);

        /**
         * Obtengo el valor del registro en la posicion.
         */
        int obtener_registro( int posicion, Almacenamiento::puntero almacenamiento);

        /**
         * Obtengo el tamanio del bloque.
         */
        int obtener_tamanio_bloque(Almacenamiento::puntero almacenamiento);

        /**
         * Obtengo la profundidad.
         */
        int obtener_profundidad(Almacenamiento::puntero almacenamiento);
};


#endif // ESTRATEGIAALMACENAMIENTODIRECTORYHASH_HPP_INCLUDED
