#ifndef HASH_BUCKET_HPP_INCLUDED
#define HASH_BUCKET_HPP_INCLUDED

#define BUCKET_SIZE 4
#include "CampoStream.hpp"
#include "clave.hpp"

typedef struct{
    int tamanio;
    string clave;
    unsigned int posicion_almacenamiento;
}Trow;

/**
 * Clase que define el objeto bloque o bucket del Hash.
  */
class HashBucket{

    private:

        int posicion_almacenamiento;
        int db; //Se refiere a la profundidad
        int espacio_libre; //Cantidad de espacio libre
        int occ ; //Lugares ocupados
        Trow rows[30];/* Supongo un tamanio fijo maximo de rows por
                         * bucket ya que si son mas la busqueda por hash
                         * terminaria siendo una busqueda secuencial*/

    public:

        HashBucket(int pdb, int longitud);
        ~HashBucket();


        /**
         * Agrega registro con clave y posicionEnAlmacenamiento.
         */
        bool  agregar( string& clave, unsigned int posicionEnAlmacenamiento );

        /**
         * Obtengo la clave y la posicion_en_almacenamiento del registro en el orden.
         */
        bool  obtener( int orden, string& pclave, unsigned int& pos_en_almacenamiento);

        /**
         * Elimina el registro con clave pclave.
         */
        bool  quitar(string pclave);

        /**
         * Incrementa profundidad.
         */
        void  incrementar_profundidad();

        /**
         * Disminuye profundidad.
         */
        void  disminuir_profundidad();

        /**
         * Disminuye en bytes el tamanio libre.
         */
        void  decrementar_espacio_libre( int bytes ){ this->espacio_libre = this->espacio_libre-bytes; }

        /**
         * Obtengo profundidad.
         */
        int   obtener_d(){ return this->db; }

        /**
         * Obtengo espacio libre.
         */
        int   obtener_espacio_libre(){ return this->espacio_libre; }

        /**
         * Obtengo cantidad de registros ocupados.
         */
        int   obtener_occ(){ return this->occ; }

        /**
         * Obtengo posicion en almacenamiento.
         */
        int   obtener_posicion_almacenamiento() { return this->posicion_almacenamiento;}

        /**
         * Establece profundidad.
         */
        void  establecer_d(int d){ this->db = d; }

        /**
         * Establece espacio libre.
         */
        void  establecer_espacio_libre(int e){ this->espacio_libre = e; }

        /**
         * Establece cantidad de registros ocupados.
         */
        void  establecer_occ(int o){ this->occ = o; }

        /**
         * Establece al bloque su posicion en almacenamiento.
         */
        void   establecer_posicion_almacenamiento( int pos ) { this->posicion_almacenamiento = pos;}
};
#endif // HASH_BUCKET_HPP_INCLUDED
