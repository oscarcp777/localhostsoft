/* this is part of the libspopc library sources
 * copyright � 2002 Benoit Rouits <brouits@free.fr>
 * released under the terms of GNU LGPL
 * (GNU Lesser General Public Licence).
 * libspopc offers simple API for a pop3 client (MTA).
 * See RFC 1725 for pop3 specifications.
 * more information on http://brouits.free.fr/libspopc/
 */

#include <string.h> /* use of strcpy() */
#include <stdio.h> /* use of printf() */
#include <stdlib.h> /* use of exit() */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include "../lib/libspopc.h"
#include "../src.datos.models/Mail.h"
#include <list>

void pop3_cert_setup(const char *certfile);

int main343434(int argc,char** argv){
	Mail* mail;
	list<Mail*> mailList;
	pop3sock_t mysock;
	char myservername[64];
	char username[64];
	char password[64];

	struct hostent myserver;
	struct sockaddr_in myconnection;

	char* srvdata=NULL;
	char* mymessage=NULL;
	int* mylist;
	int nport;
	int i=0, last; /* 'i'ndex, 'last' cell of an array */

	/* Controlo que se especifiquen todos los atributos necesarios */
	if(argc<3){
		printf("Usage: %s username password [ssl-cert]\n",argv[0]);
		exit(0);
	}


	/* Conexi�n */
	strcpy(username,argv[1]);
	strncpy(argv[1], "****************", strlen(argv[1]));
	strcpy(password,argv[2]);
	strncpy(argv[2], "****************", strlen(argv[2]));

	strcpy(myservername, "pop.gmail.com");
	nport=995;

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
	printf("\n---\nTEST STAT\n\n");
	srvdata=pop3_stat(mysock);
	int numberOfMails = stat2num(srvdata);
	printf("stat: %d mail(s)\n",numberOfMails);
	printf("stat: %d bytes\n",stat2bytes(srvdata));
	free(srvdata);

	printf("\n---\nTEST LIST\n\n");
	srvdata=pop3_list(mysock,0);
	mylist=list2array(srvdata);
	free(srvdata);
	printf("list:\n");
	last=mylist?mylist[0]:0;
	last=5; /* Solo tomo 5 mensajes */
	for(i=1;i<=last;i++){
		printf(" %d: %d bytes\n",i,mylist?mylist[i]:0);
	}
	i--;/* i is the number of messages */
	free(mylist);mylist=NULL;

	printf("\n---\nTEST TOP\n\n");
	srvdata=pop3_top(mysock,i,0);
	mymessage=retr2msg(srvdata);
	printf("last email's header is;\n");
	printf("%s",mymessage);
	free(mymessage);
	free(srvdata);

	printf("\n---\nTEST RETR\n\n");

	while(i){
		srvdata=pop3_retr(mysock,i);
		mymessage=retr2msg(srvdata);
		free(srvdata);
		printf("mail is %d:\n",i);
		//printf("%s",mymessage);
		mail = new Mail;
		mail->parseMail(mymessage);
		mailList.push_back(mail);
		free(mymessage);mymessage=NULL;
		i--;
	}
	list<Mail*>::iterator it;
	for(it=mailList.begin(); it!=mailList.end();it++){
		cout<<"*******************************************************"<<endl;
		(*it)->print(std::cout);
		cout<<"*******************************************************"<<endl;
	}
	/* Comento la funci�n de borrado de mails
	printf("\n---TEST DELE\n\n");
	for(i=1; i<=last; i++){
		srvdata=pop3_dele(mysock, i);
		printf("deleted %d: %s\n",i,srvdata);
		free(srvdata);srvdata=NULL;
	}

	Comento la funci�n de RESET
	printf("\n---TEST RSET\n\n");
	srvdata=pop3_rset(mysock);
	printf("canceled deletion: %s\n", srvdata);
	free(srvdata);srvdata=NULL;
	*/

	srvdata=pop3_quit(mysock);
	free(srvdata); srvdata=NULL;
	pop3_disconnect(mysock, &myserver);

	libspopc_clean();
	mailList.clear();
	exit(0);
}

