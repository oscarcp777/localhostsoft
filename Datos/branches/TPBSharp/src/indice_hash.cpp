#include "indice_hash.hpp"
#include <math.h>
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "campo.hpp"
#include "campo_entero.hpp"
#include "campo_booleano.hpp"
#include "campo_doble.hpp"
#include "campo_flotante.hpp"
#include "campo_largo.hpp"
#include "campo_cadena.hpp"
#include "buffer.hpp"
#include "almacenamiento.hpp"
#include "RegistroLongitudVariable.hpp"
#include "CampoStream.hpp"

IndiceHash::IndiceHash( Esquema::puntero esquema, Clave::puntero clavePrimaria,
                            ComparadorClave::puntero comparadorClave,
                            int ptamanio_bloque, const std::string& nombre_indice) throw(): EstrategiaIndice(clavePrimaria, esquema) {
	// Establece el esquema del indice
	this->esquema = esquema->clonar();
	// Establece el comparador de claves
	this->comparadorClave = comparadorClave;
	this->clave = clavePrimaria->clonar();
    /*Se definen los almacenamientos*/
    this->almacenamiento_tabla = new Archivo( 8, nombre_indice + ".th.idx",Registros );
    ((Archivo::puntero)this->almacenamiento_tabla)->abrirModoTexto();
    /*Se definen los almacenamientos*/
    this->almacenamiento_bucket = new Archivo( ptamanio_bloque+4, nombre_indice + ".bh.idx", Bloques );
    ((Archivo::puntero)this->almacenamiento_bucket)->abrirModoTexto();
    /*Defino la tabla Hash*/
    this->tabla_hash = new HashDirectory( this->almacenamiento_tabla, this->almacenamiento_bucket, ptamanio_bloque );
    this->tamanio_bloque = ptamanio_bloque;
    /*Bloque_DUMMIE*/
    HashBucket * b = new HashBucket(0, this->tamanio_bloque);
    this->tabla_hash->agregar_bucket( b, 0);

}

IndiceHash::~IndiceHash() throw()
{
}

/*
* sdbm
* This algorithm was created for sdbm (a public-domain reimplementation of ndbm) database library
*/
int hash(const char *str)
{
    int hash = 5381;
    int c;
    int largo = strlen(str);
    for ( int i=0; i<largo; i++)
    {
        c = ((*str));
        hash = hash * 33 + c;
        str++;
    }

    return hash;
}

int minimo_lugar( int pos, int prof )
{
   int min = pos;
   int aux = pos - pow( 2, prof);
   while ( aux >= 0 )
   {
       min = aux;
       aux = min - pow( 2, prof);
   }

   return min;
}

void IndiceHash::agregar_registro(Registro::puntero registro) throw()
{
    stringstream s;
    char delimitador = '|';
    Clave::iterador_campos actual_campo_clave = this->clave->primer_campo();
	Clave::iterador_campos fin_campo_clave = this->clave->ultimo_campo();

	while (actual_campo_clave != fin_campo_clave) {
		Campo::puntero campo = registro->obtener_campo(*actual_campo_clave);

		switch(campo->obtener_tipo_campo())
        {
            case TIPO_CAMPO_CADENA: {std::string cadena =*((std::string*) campo->obtener_valor());
                                    s<<cadena;
                                    break;}
            case TIPO_CAMPO_BOOLEANO: {bool bolean = *((bool*)  campo->obtener_valor());
                                    s<<bolean;
                                    break;}
            case TIPO_CAMPO_ENTERO: {int integer =*((int*)  campo->obtener_valor());
                                    s<<integer;
                                    break;}
            case TIPO_CAMPO_DOBLE: {double doble = *((double*)  campo->obtener_valor());
                                    s<<doble;
                                    break;}
            case TIPO_CAMPO_FLOTANTE: {float flotante = *((float*) campo->obtener_valor());
                                    s<<flotante;;
                                    break;}
            case TIPO_CAMPO_LARGO: {long largo = *((long*)  campo->obtener_valor());
                                    s<<largo;
                                    break;}
        }
        s<<delimitador;
		++actual_campo_clave;
	}
    string clave_string = s.str();

    int pos =*((int*) registro->obtener_campo("posicionAlmacenamiento")->obtener_valor());

    if ( this->buscar_registro( registro ) != NULL )
        printf ("NO SE PUEDE INSERTAR - CLAVE YA EXISTE");
    else this->agregar_registro ( clave_string, pos );

}

void IndiceHash::agregar_registro( string& clave_string, int posicionEnAlmacenamiento) throw()
{
    int res_hash  = hash(clave_string.c_str());
    int mod = fabs(res_hash % (int) (pow ( 2, IndiceHash::tabla_hash->obtener_profundidad() )));

    HashBucket * b = IndiceHash::tabla_hash->obtener_bucket( mod );
    bool res = b->agregar( clave_string, posicionEnAlmacenamiento);

    int prof = b->obtener_d();
    if ( res==true )
    {
        IndiceHash::tabla_hash->agregar_bucket( b, mod);
    }

    if ( (res==false) && (prof< IndiceHash::tabla_hash->obtener_profundidad())
        )
    {
        HashBucket * b_aux = new HashBucket( prof + 1, this->tamanio_bloque );
        int posicion_nuevo_bloque = minimo_lugar( mod, prof );
        IndiceHash::tabla_hash->agregar_bucket( b_aux, posicion_nuevo_bloque );

        HashBucket * b2 = new HashBucket( prof + 1, this->tamanio_bloque );
        posicion_nuevo_bloque = posicion_nuevo_bloque + (pow(2, prof ));
        IndiceHash::tabla_hash->agregar_bucket( b2,  posicion_nuevo_bloque);

        string clave_aux;
        unsigned int pos_aux;
        int entro = 0;
        while(  entro<b->obtener_occ() && b->obtener(entro, clave_aux, pos_aux ) )
        {
             IndiceHash::agregar_registro(clave_aux, pos_aux);
             entro++;
        }

        delete( b_aux );
        delete( b2 );
        IndiceHash::agregar_registro(clave_string, posicionEnAlmacenamiento);
    }

    if ( (res==false) && (prof== IndiceHash::tabla_hash->obtener_profundidad())
        )
    {
        IndiceHash::tabla_hash->duplicar( mod );
        IndiceHash::agregar_registro(clave_string, posicionEnAlmacenamiento);
    }

    delete(b);
}

/*
 * Borra un registro de la tabla de hash, ya no podra ser buscado
 */
void IndiceHash::borrar_registro(Registro::puntero registro) throw()
{
    stringstream s;
    char delimitador = '|';
    Clave::iterador_campos actual_campo_clave = this->clave->primer_campo();
	Clave::iterador_campos fin_campo_clave = this->clave->ultimo_campo();

	while (actual_campo_clave != fin_campo_clave) {
		Campo::puntero campo = registro->obtener_campo(*actual_campo_clave);

		switch(campo->obtener_tipo_campo())
        {
            case TIPO_CAMPO_CADENA: {std::string cadena =*((std::string*) campo->obtener_valor());
                                    s<<cadena;
                                    break;}
            case TIPO_CAMPO_BOOLEANO: {bool bolean = *((bool*)  campo->obtener_valor());
                                    s<<bolean;
                                    break;}
            case TIPO_CAMPO_ENTERO: {int integer =*((int*)  campo->obtener_valor());
                                    s<<integer;
                                    break;}
            case TIPO_CAMPO_DOBLE: {double doble = *((double*)  campo->obtener_valor());
                                    s<<doble;
                                    break;}
            case TIPO_CAMPO_FLOTANTE: {float flotante = *((float*) campo->obtener_valor());
                                    s<<flotante;;
                                    break;}
            case TIPO_CAMPO_LARGO: {long largo = *((long*)  campo->obtener_valor());
                                    s<<largo;
                                    break;}
        }
        s<<delimitador;
		++actual_campo_clave;
	}

    string clave_string = s.str();
    int tamanio = clave_string.length();
    int res_hash  = hash(clave_string.c_str());
    int mod = fabs(res_hash % (int) (pow ( 2, IndiceHash::tabla_hash->obtener_profundidad() )));

    HashBucket * b = IndiceHash::tabla_hash->obtener_bucket( mod );
    int pos_delbloque = IndiceHash::tabla_hash->obtener_pos_bucket( mod );

    int encontrado = 0;
    int entro = 0;
    string clave_aux;
    unsigned int pos_aux;
    while( (entro<b->obtener_occ()) && (b->obtener( entro, clave_aux, pos_aux) && encontrado==0 ))
    {
        if ( clave_aux == clave_string )
        {
            encontrado = 1;
            break;
        }
        entro++;
    }
    if (encontrado == 0)
        return;

    b->quitar( clave_aux );
    int pos_del_bloque = b->obtener_posicion_almacenamiento();

    int nueva_occ = b->obtener_occ();
    int nueva_prof = b->obtener_d();
    int fin = pow( 2, IndiceHash::tabla_hash->obtener_profundidad()) ;

    if (nueva_occ>0 || nueva_prof==0)
    {
        IndiceHash::tabla_hash->agregar_bucket( b, mod );
    }
    else if (nueva_occ == 0 && nueva_prof!=0)
    {
        int salto = pow( 2, nueva_prof - 1);
        int inicio = minimo_lugar( mod, nueva_prof-1 );
        int una_pos = -1,  dos_pos = -1,
        dos_mod = 0, una_mod = 0, pos_aux = -1;
        bool eliminar = true;

        pos_aux = this->tabla_hash->obtener_pos_bucket( inicio );
        una_pos = pos_aux;
        una_mod = inicio;
        inicio = inicio + salto;
        while ( inicio<fin )
        {
            pos_aux = this->tabla_hash->obtener_pos_bucket( inicio );
            if ( pos_aux != una_pos && pos_aux != dos_pos && dos_pos>0 )
            {
                eliminar = false;
            }
            else if ( pos_aux != una_pos && pos_aux != dos_pos && dos_pos<0 )
            {
                dos_pos = pos_aux;
                dos_mod = inicio;
            }
            inicio = inicio + salto;
        }
        if (eliminar==true)
        {
            int a_copiar = -1;
            if ( una_pos!=pos_del_bloque )
                a_copiar = una_mod;
            else a_copiar = dos_mod;

            {
                inicio = minimo_lugar( a_copiar, nueva_prof-1 );
                HashBucket * baux = IndiceHash::tabla_hash->obtener_bucket( a_copiar );
                baux->disminuir_profundidad();

                while ( inicio< fin )
                {
                    this->tabla_hash->agregar_bucket( baux, inicio);
                    inicio = inicio + salto;
                }
            }
            this->tabla_hash->verificar_merge();
        }
    }
        delete(b);
}

/*
 * Devuelve la posicion en almacenamiento mas la clave agrupados en un tipo Registro.
 */
Registro::puntero IndiceHash::buscar_registro(Registro::puntero registro) throw()
{
    stringstream s;
    char delimitador = '|';
    Clave::iterador_campos actual_campo_clave = this->clave->primer_campo();
	Clave::iterador_campos fin_campo_clave = this->clave->ultimo_campo();
	while (actual_campo_clave != fin_campo_clave) {
		Campo::puntero campo = registro->obtener_campo(*actual_campo_clave);

		switch(campo->obtener_tipo_campo())
        {
            case TIPO_CAMPO_CADENA: {std::string cadena =*((std::string*) campo->obtener_valor());
                                    s<<cadena;
                                    break;}
            case TIPO_CAMPO_BOOLEANO: {bool bolean = *((bool*)  campo->obtener_valor());
                                    s<<bolean;
                                    break;}
            case TIPO_CAMPO_ENTERO: {int integer =*((int*)  campo->obtener_valor());
                                    s<<integer;
                                    break;}
            case TIPO_CAMPO_DOBLE: {double doble = *((double*)  campo->obtener_valor());
                                    s<<doble;
                                    break;}
            case TIPO_CAMPO_FLOTANTE: {float flotante = *((float*) campo->obtener_valor());
                                    s<<flotante;;
                                    break;}
            case TIPO_CAMPO_LARGO: {long largo = *((long*)  campo->obtener_valor());
                                    s<<largo;
                                    break;}
        }
        s<<delimitador;
		++actual_campo_clave;
	}

    string clave_string = s.str();
    int tamanio = clave_string.length();

    int res_hash  = hash(clave_string.c_str());

    int mod = fabs(res_hash % (int) (pow ( 2, IndiceHash::tabla_hash->obtener_profundidad() )));

    HashBucket * b = IndiceHash::tabla_hash->obtener_bucket( mod );

    int encontrado = 0;
    int entro = 0;
    string clave_aux;
    unsigned int pos_aux;


    while( (entro<b->obtener_occ()) && b->obtener( entro, clave_aux, pos_aux) && encontrado==0 )
    {
        if ( clave_aux == clave_string )
        {
            encontrado = 1;
            break;
        }
        entro++;
    }

        int tam = clave_aux.size();
        char clave_hash[1024];
        char * p;
        char this_campo[1024];
        char * tc;

    if ( encontrado ==1 )
    {
        strcpy( clave_hash, clave_aux.c_str() );
        p = clave_hash;
        tc = this_campo;

        Registro * aux = new RegistroLongitudVariable( this->clave );

        Clave::iterador_campos actual_campo_clave = this->clave->primer_campo();
        Clave::iterador_campos fin_campo_clave = this->clave->ultimo_campo();

        Campo::puntero ca;

        while (actual_campo_clave != fin_campo_clave) {

            Campo::puntero campo = registro->obtener_campo(*actual_campo_clave);
            while (*p!='|' && *p!='\0'){ *tc = *p; p++; tc++; } *tc='\0';p++;
            switch(campo->obtener_tipo_campo())
            {
                case TIPO_CAMPO_CADENA: { ca = new CampoCadena( this_campo );
                                        aux->agregar_campo( (string)(*actual_campo_clave), ca );
                                        break;}
                case TIPO_CAMPO_BOOLEANO:{ char o = this_campo[0];
                                           bool op = false;
                                           if (o=='1') op = true;
                                           ca = new CampoBooleano( op );
                                           aux->agregar_campo( (string)(*actual_campo_clave), ca );
                                           break;}
                case TIPO_CAMPO_ENTERO: {ca = new CampoEntero( atoi(this_campo) );
                                        aux->agregar_campo( (string)(*actual_campo_clave), ca );
                                        break;}
                case TIPO_CAMPO_DOBLE: {ca = new CampoDoble( atof(this_campo) );
                                        aux->agregar_campo( (string)(*actual_campo_clave), ca );
                                        break;}
                case TIPO_CAMPO_FLOTANTE: {ca = new CampoFlotante( atof(this_campo) );
                                        aux->agregar_campo( (string)(*actual_campo_clave), ca );
                                        break;}
                case TIPO_CAMPO_LARGO: {ca = new CampoLargo( atol(this_campo) );
                                        aux->agregar_campo( (string)(*actual_campo_clave), ca );
                                        break;}
                default: break;
            }
            tc = this_campo;
            ++actual_campo_clave;
        }

        ca = new CampoEntero( pos_aux );
        aux->agregar_campo( "posicionAlmacenamiento", ca );
        delete(b);
        return aux;
    }
    else
    {
        delete(b);
        return NULL;
    }

}
