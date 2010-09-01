/*
 * Define.h
 *
 *  Created on: 04/10/2009
 *      Author: oscar
 */


#ifndef DEFINE_H_
#define DEFINE_H_


/*
 * Definiciones correspondiente al logger.
 */
#define PATH_LOGGER "files/log"
#define PATH_CONFIG "files/config"
#define SIZE_SYSTEM_TIME 25
#define MAX_FILE_SIZE 1048576
/*
 * Definiciones correspondiente al hash.
 */
#define EXT_TABLE ".tbl"
#define EXT_CUBE ".cb"
#define EXT_FREE_CUBE ".fcb"
#define PORCENT_FREE_CUBE 0.2
#define SIZE_METADATA 12

/*
 * Definiciones correspondiente al arbol.
 */
#define PORCENT_BLOCK_SIZE 0.2
/*
 * Definiciones correspondientes a usos generales.
 */
#define TAB "		"
#define TRUE 1;
#define FALSE 0;
#define SIZE_CUBE 512

























#define CLAVE_TAMANIO "|tamanio=|"
#define CLAVE_ALMACENAMIENTO "almacenamiento=|"
#define CLAVE_TAG_PRIMARIA "|clavePrimaria=|"
#define PRIMER_BLOQUE "0=|"
#define PRIMER_REGISTRO "-1|"
#define PORCENTAJE_ESPACIO_LIBRE_BLOQUE 0.1
#define ESTRATEGIA_ALMACENAMIENTO_TEXTO "estrategiaAlmacTexto"
#define ESTRATEGIA_ALMACENAMIENTO_REGISTROS "estrategiaAlmacRegistros"
#define ESTRATEGIA_ALMACENAMIENTO_BLOQUES "estrategiaAlmacBloques"
#define ARCHIVO "archivo"
#define BUFFER "buffer"
#define BINARIO "binario"
#define TEXTO "texto"
#define DELIMITADOR "|"
#define DELIMITADOR_SHARP "#"
#define COMPUESTO "compuesto"
#define ALMACENAMIENTO_ARCHIVO 0
#define ALMACENAMIENTO_BUFFER 1
#define TAM_BUFFER 32768 // 2 a la 15 :P
#define INDEXADO_HASH_EXTENSIBLE "indexadoHashExtensible"
#define INDEXADO_BSHARP "indexadoBSharp"
#define METADATA "MetaData"
#define INDICE_PRIMARIO "IndPrim"
#define ESTRATEGIA_ALMACENAMIENTO "almacenamiento"
#define TIPO_INDEXACION "indexacion"
#define CLAVE_INDEXACION "|indexacion=|"
#define TAMANIO "tamanio"
#define CLAVE_PRIMARIA "clavePrimaria"
#define MAX_LINEA 2000

class Define{
public:
	static const char DELIMITADOR1 = '|';
};


#endif /* DEFINE_H_ */
