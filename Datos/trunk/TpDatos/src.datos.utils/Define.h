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
#define SERVER "pop.gmail.com"// "pop.mail.yahoo.com"
#define PORT  995 // 995 para gmail, 110 para yahoo
#define CONNECT 1 // 1 se conecta a la cuenta, 0 baja de un archivo
#define MAILSFILE "./files/mailsMediano"
#define PATHFILES "files/storage/"
#define STOP_WORDS_FILE "./files/stopwords.txt"



#define BOUNDARYMAIL "**********"
#define DEBUG 0
#define NUM_FIELDS_MAILS 6
#define NUM_FIELDS_REG_PRIMARY 2
#define BLOCK_SIZE 512
#define BLOCK_SIZE_MAILS 32768
//TODO IMPORTANTE NO MODIFICAR ENTE ORDEN
#define TYPE_REG_PRIMARY 1
#define TYPE_REG_CLASSIFICATION 2
#define TYPE_REG_SELECTION 3
#define TYPE_MAIL 4
#define TYPE_KEY_INTEGER 5
#define TYPE_KEY_STRING 6
#define TYPE_REG_INVERTED_INDEX 7
#define TYPE_INFO_PER_DOC 8

#define DATA 1
#define INSERTION_OK 0
#define OVERFLOW 1
#define BALANCE 2
#define CORRECT_REMOVE 3
#define UNDERFLOW 4
#define NEXT_BLOCK_INVALID -1


#define FROM 1
#define TO 2
#define SUBJECT 3
#define DATE 4

#define TYPE_SECONDARY "Secundario"
#define TYPE_PRIMARY "Primario"
#define TYPE_CLASSIFICATION "Clasificacion"
#define TYPE_SELECTION "Seleccion"
#define TYPE_INVERTED_INDEX "Invertido"

#endif /* DEFINE_H_ */
