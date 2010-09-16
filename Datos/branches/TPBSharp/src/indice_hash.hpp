#ifndef INDICE_HASH_HPP_INCLUDED
#define INDICE_HASH_HPP_INCLUDED
#include "archivo.hpp"
#include "estrategia_indice.hpp"
#include "comparador_clave.hpp"
#include "bloque.hpp"
#include "hash_directory.hpp"
#include "hash_bucket.hpp"

/**
 * Clase que define una estrategia de indice hash Extensible.
  */
class IndiceHash: public EstrategiaIndice {
    private:
        /**
        * Tabla Hash.
        */
        HashDirectory            * tabla_hash;
        /**
        * Almacena la referencia al almacenamiento de la tabla de directorios.
        */
        Almacenamiento::puntero  almacenamiento_tabla;
        /**
        * Almacena la referencia al almacenamiento de los bloques.
        */
        Almacenamiento::puntero  almacenamiento_bucket;
        /**
        * Almacena el esquema.
        */
        Esquema::puntero    esquema;
        /**
        * Almacena el comparador de clave.
        */
        ComparadorClave::puntero comparadorClave;
        /**
        * Almacena la clave.
        */
        Clave::puntero clave;
        /**
        * Almacena el tamanio de bloque definido por el usuario.
        */
        int tamanio_bloque;
    public:

        /**
        * Constructor de la clase IndiceHash.
        */
        IndiceHash( Esquema::puntero esquema, Clave::puntero clavePrimaria,
                            ComparadorClave::puntero comparadorClave,
                            int ptamanio_bloque, const std::string& nombre_indice) throw();
        /**
         * Destructor virtual de la clase IndiceHash.
         */
        virtual ~IndiceHash() throw();
        /**
         * Agrega un registro en el indice. La posicionEnAlmacenamiento me dice donde esta el registro integro,
         * donde ir a buscarlo.
         */
         virtual void agregar_registro(Registro::puntero registro) throw();
                 /**
         * Agrega un registro en el indice. La posicionEnAlmacenamiento me dice donde esta el registro integro,
         * donde ir a buscarlo.
         */
         virtual void agregar_registro(string& clave_string, int posicionEnAlmacenamiento) throw();
         /**
          * Borra un registro del indice.
          */
         virtual void borrar_registro(Registro::puntero registro) throw();
         /**
          * Obtiene la posicion en almacenamiento del registro.
          */
         virtual Registro::puntero  buscar_registro(Registro::puntero registro) throw();


};
#endif // INDICE_HASH_HPP_INCLUDED
