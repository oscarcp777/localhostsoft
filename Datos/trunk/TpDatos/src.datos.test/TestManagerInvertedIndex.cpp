/*
 * TestManagerInvertedIndex.cpp
 *
 *  Created on: 16/10/2010
 *      Author: richy
 */

#include "TestManagerInvertedIndex.h"

TestManagerInvertedIndex::TestManagerInvertedIndex() {
	// TODO Auto-generated constructor stub

}

TestManagerInvertedIndex::~TestManagerInvertedIndex() {
	// TODO Auto-generated destructor stub
}
void TestManagerInvertedIndex::test(){
	ManagerInvertedIndex* manager = new ManagerInvertedIndex();
	Mail* mail = new Mail();
	KeyInteger* key = new KeyInteger(10);

	mail->setKey(key);
	mail->setDate("27/8/2009");
	mail->setFrom("richy@lalala.com.ar");
	mail->setMessage("Hola CARACAS mundo borra la siguiente stop word ARGENTINA aqui ahi ahì CARACAS lo mas fragil mundo de la locura trabajo ser trabajan ARGENTINA voy al mundia de brasil");
	mail->setSubject("trabajo practico");
	mail->setTo("yogui");
	manager->loadMessageWords(mail);

	delete manager;
	delete mail;


}
