/*
 * StorageController.cpp
 *
 *  Created on: 25/09/2010
 *      Author: richy
 */

#include "StorageController.h"
#include "../src.datos.utils/Define.h"
#include "../src.datos.connection/gmail-poptest.h"
#include "../src.datos.models/Mail.h"
#include "../src.datos.models/KeyInteger.h"
#include "../src.datos.models/RegPrimary.h"

StorageController::StorageController() {
	this->numberOfIuc = 1;

}

StorageController::~StorageController() {
	delete this->primaryIndex;
}
void StorageController::addMail(char* message){
	Mail* mail = this->generateMail(message);
	mail->print(std::cout);
	RegPrimary* regPrimary = new RegPrimary();
	regPrimary->setKey((KeyInteger*)mail->getKey()->clone());
	regPrimary->setMail(mail);
	this->primaryIndex->addRegistry(regPrimary);

}
Mail* StorageController::generateMail(char* message){
	Mail* mail = new Mail();
	mail->parseMail(message);
	KeyInteger* key = new KeyInteger(this->numberOfIuc);
	mail->setKey(key);
	this->numberOfIuc++;
	return mail;
}
IndexBSharp* StorageController::generatePrimaryIndex(char* userName, char* password){
	string fileName = userName;
	fileName += ".IndPrimario";
	this->primaryIndex = new IndexBSharp(fileName,BLOCK_SIZE,TYPE_REG_PRIMARY);
	connection(userName,password,this);

	return this->primaryIndex;
}
