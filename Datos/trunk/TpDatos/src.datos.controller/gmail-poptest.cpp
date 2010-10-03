/* this is part of the libspopc library sources
 * copyright � 2002 Benoit Rouits <brouits@free.fr>
 * released under the terms of GNU LGPL
 * (GNU Lesser General Public Licence).
 * libspopc offers simple API for a pop3 client (MTA).
 * See RFC 1725 for pop3 specifications.
 * more information on http://brouits.free.fr/libspopc/
 */

#include "gmail-poptest.h"
#include <string.h> /* use of strcpy() */
#include <stdio.h> /* use of printf() */
#include <stdlib.h> /* use of exit() */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include "../lib/libspopc.h"



void pop3_cert_setup(const char *certfile);

int connection(char* username,char* password, StorageController* storageController){

	if(CONNECT == 1){
		pop3sock_t mysock;
		char myservername[64];

		struct hostent myserver;
		struct sockaddr_in myconnection;

		char* srvdata=NULL;
		char* mymessage=NULL;
		int nport;
		int i=0;


		strcpy(myservername,SERVER);
		nport=PORT;

		libspopc_init();

		mysock=pop3_prepare(myservername,nport,&myconnection,&myserver);
		if(BAD_SOCK==mysock){
			printf("check your network...\n");
			exit(1);
		}
		srvdata=pop3_connect(mysock,&myconnection);
		if (!srvdata){
			printf("connection problem...\n");
			exit(1);
		}
		free(srvdata);
		srvdata=pop3_user(mysock,username);
		free(srvdata);
		srvdata=pop3_pass(mysock,password);
		free(srvdata);
		/* Fin Conexi�n */

		/* Inicio de Test */
		printf("DESCARGANDO MAILS DE LA CUENTA\n");
		srvdata=pop3_stat(mysock);
		int numberOfMails = stat2num(srvdata);
		printf("stat: %d mail(s)\n",numberOfMails);
		printf("stat: %d bytes\n",stat2bytes(srvdata));
		free(srvdata);

		i = 5;//numberOfMails;
		while(i){
			srvdata=pop3_retr(mysock,i);
			mymessage=retr2msg(srvdata);
			free(srvdata);
			storageController->addMail(mymessage);
			free(mymessage);mymessage=NULL;
			i--;
		}

		srvdata=pop3_quit(mysock);
		free(srvdata); srvdata=NULL;
		pop3_disconnect(mysock, &myserver);
		libspopc_clean();
	}
	else{
		cout<<"DESCARGANDO MAILS DE ARCHIVOS"<<endl;
		TextFile* file = new TextFile();
		file->open(MAILSFILE);
		std::string linea = "";
		std::string mail;
		file->read(linea);

		while(linea.compare("\0") != 0) {
			mail = "";
			while(linea.compare((char*)BOUNDARYMAIL) != 0){
				mail+=linea+"\n";
				file->read(linea);
			}
			mail+="¡¡END MAIL!!";
			storageController->addMail((char*)mail.c_str());
			file->read(linea);
		}
		file->close();
         delete file;
	}
	return 0;
}

