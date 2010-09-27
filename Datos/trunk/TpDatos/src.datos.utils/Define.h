/*
 * Define.h
 *
 *  Created on: 04/10/2009
 *      Author: oscar
 */


#ifndef DEFINE_H_
#define DEFINE_H_
/*
 *
 */
#define DEBUG 0
#define NUM_FIELDS_MAILS 6
#define NUM_FIELDS_REG_PRIMARY 2
#define BLOCK_SIZE 64
#define BLOCK_SIZE_MAILS 32768
//TODO IMPORTANTE NO MODIFICAR ENTE ORDEN
#define TYPE_REG_PRIMARY 1
#define TYPE_REG_CLASSIFICATION 2
#define TYPE_REG_SELECTION 3
#define TYPE_MAIL 4
#define TYPE_KEY_INTEGER 5
#define TYPE_KEY_STRING 6

#define DATA 0
#define INSERTION_OK 0
#define OVERFLOW 1
#define BALANCE 2


#define FROM 1
#define TO 2
#define SUBJECT 3
#define DATE 4

#define TYPE_SECONDARY "Secunadrio"
#define TYPE_PRIMARY "Primario"
#define TYPE_CLASSIFICATION "Clasificacion"
#define TYPE_SELECTION "Seleccion"

#endif /* DEFINE_H_ */
