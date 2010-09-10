/*
 * TestMailBlockManager.cpp
 *
 *  Created on: 09/09/2010
 *      Author: richy
 */

#include "TestMailBlockManager.h"

TestMailBlockManager::TestMailBlockManager() {
	// TODO Auto-generated constructor stub

}

TestMailBlockManager::~TestMailBlockManager() {
	// TODO Auto-generated destructor stub
}

void TestMailBlockManager::testPackMail(){
	MailBlockManager* manager = new MailBlockManager("mailsFile", BLOCK_SIZE);
	Mail* mailUno = new Mail();
	Mail* mailDos = new Mail();
	Mail* mailTres = new Mail();
	Mail* mail4 = new Mail();
	Mail* mail5 = new Mail();
	Mail* mail6 = new Mail();
	Mail* mail7 = new Mail();
	Mail* mail8 = new Mail();

	mailUno->setDate("27/8/2009");
	mailUno->setFrom("richy");
	mailUno->setMessage("aprobamooooossss");
	mailUno->setSubject("trabajo practico");
	mailUno->setTo("yogui");

	mailDos->setDate("2/5/1985");
	mailDos->setFrom("ALUMNOS");
	mailDos->setMessage("PLEBISITOOOOOOO YAAAAAAAAAAAAAAAAAAAAAAAA JAJJA");
	mailDos->setSubject("ingenieria ");
	mailDos->setTo("DAMS");

	mailTres->setDate("5/5/3485");
	mailTres->setFrom("yo");
	mailTres->setMessage("River Plate");
	mailTres->setSubject("Campeon 2010, osky este año river la rompe");
	mailTres->setTo("BUBU");

	mail4->setDate("2/5/1985");
	mail4->setFrom("oscar");
	mail4->setMessage("san Lorenzo ");
	mail4->setSubject("2 a 1, la comieron bosteros horribles");
	mail4->setTo("palermo");

	mail5->setDate("2/5/1985");
	mail5->setFrom("santy");
	mail5->setMessage("auto: 207 compact full full full full fullfullfull full full fullfullfull full fullfullfull fullfullfullfullfullfull");
	mail5->setSubject("Campeon 2010");
	mail5->setTo("BUBU");

	mail6->setDate("2/5/1985");
	mail6->setFrom("facu");
	mail6->setMessage("casa quiero ir");
	mail6->setSubject("Campeon 2010");
	mail6->setTo("BUBU");


	mail7->setDate("2/5/1985");
	mail7->setFrom("fiuba");
	mail7->setMessage("mundo hola mundo hola mundo hola mundoooooooooooo");
	mail7->setSubject("Campeon 2010");
	mail7->setTo("BUBU");

	mail8->setDate("2/5/1985");
	mail8->setFrom("vaio");
	mail8->setMessage("WSOP world series of poker");
	mail8->setSubject("Campeon 2010");
	mail8->setTo("BUBU");

	manager->packMail(mailUno);
	manager->packMail(mailDos);
	manager->packMail(mailTres);
	manager->packMail(mail4);
	manager->packMail(mail5);
	manager->packMail(mail6);
	manager->packMail(mail5);
	manager->packMail(mail6);
	manager->packMail(mail6);
	//manager->packMail(mail7);
	//manager->packMail(mail8);

	manager->close();

	delete manager;
	delete mailUno;
	delete mailDos;
	delete mailTres;
	delete mail4;
	delete mail5;
	delete mail6;
	delete mail7;
	delete mail8;

}
void TestMailBlockManager::testUnpackMail(){
	MailBlockManager* manager = new MailBlockManager("mailsFile", BLOCK_SIZE);
	std::vector<Mail*>::iterator it;
	int idBloqueALeer = 1;
	std::vector<Mail*> mailList = manager->loadMailsInBlock(idBloqueALeer);

	for (it = mailList.begin(); it!=mailList.end(); it++){
		(*it)->print();
		cout<<endl;
	}

	delete manager;
}
