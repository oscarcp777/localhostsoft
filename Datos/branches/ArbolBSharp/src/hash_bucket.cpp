#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_bucket.hpp"
#include "CampoStream.hpp"

HashBucket::HashBucket (int pdb, int tamanio_bloque)
{
    this->db = pdb;
    this->espacio_libre = tamanio_bloque - 4 - 4 - 4 -4;//
    this->occ = 0;
    this->posicion_almacenamiento = -1;
}

HashBucket::~HashBucket(){}

int compare_rows( const void *_a, const void * _b)
{
    Trow* a = (Trow*) _a;
    Trow* b = (Trow*) _b;

    return ( a->posicion_almacenamiento - b->posicion_almacenamiento);
}

bool HashBucket::agregar( string& pclave, unsigned int ppos )
{
    int tamanio_a_ocupar = pclave.length() + 8;
    if ((this->espacio_libre >= tamanio_a_ocupar) && this->occ<29 )
    {
        this->rows[this->occ].clave = pclave ;
        this->rows[this->occ].posicion_almacenamiento = ppos;
        this->rows[this->occ].tamanio = pclave.length();
        this->occ++;
        this->espacio_libre = this->espacio_libre - tamanio_a_ocupar;

        return true;
    }
    return false;
}


bool HashBucket::obtener(int orden, string& pclave, unsigned int& pos_en_almacenamiento)
{
    if (orden>=0 && orden<=this->occ)
    {
        pclave = this->rows[orden].clave ;
        pos_en_almacenamiento = this->rows[orden].posicion_almacenamiento;

        return true;
    }else return false;
}

bool HashBucket::quitar(string pclave)
{
    int remover = -1;
    if (this->occ>0)
    {
        int i = 0;
        for( i=0; i<this->occ; i++)
        {
            if(this->rows[i].clave == pclave)
            {
                remover  = i;
                break;
            }

        }
        if (remover<0) return false;

        this->espacio_libre = this->espacio_libre + 8 + this->rows[i].tamanio;
        int t = i;
        while (  t<this->occ )
        {
            this->rows[t].clave = this->rows[t+1].clave;
            this->rows[t].posicion_almacenamiento = this->rows[t+1].posicion_almacenamiento;
            this->rows[t].tamanio = this->rows[t+1].tamanio;
            t++;
        }

        this->occ--;


    }else {
    	return false;
    }
    return true;
}

void HashBucket::incrementar_profundidad(){
    HashBucket::db++;
}

void HashBucket::disminuir_profundidad(){
    HashBucket::db--;
}
