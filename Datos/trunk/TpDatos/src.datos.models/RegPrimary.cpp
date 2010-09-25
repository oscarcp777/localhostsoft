/*
 * RegPrimary.cpp
 *
 *  Created on: 11/09/2010
 *      Author: oscar
 */

#include "RegPrimary.h"
#include "Key.h"
#include "KeyInteger.h"
#include "RegKeyPrimary.h"

RegPrimary::RegPrimary() {
	this->mail = NULL;
}

RegPrimary::~RegPrimary() {
	// TODO Auto-generated destructor stub
}
Registry* RegPrimary::clone(){
	RegPrimary* regPrimary = new RegPrimary();
	regPrimary->setKey((KeyInteger*)this->getKey()->clone());
	regPrimary->setNumberBlock(this->numberBlock);
	return regPrimary;
}
Registry* RegPrimary::cloneRegKey(){
	RegKeyPrimary* regKeyPrimary = new RegKeyPrimary();
	regKeyPrimary->setKey((KeyInteger*)this->getKey()->clone());
	return regKeyPrimary;
}
bool RegPrimary::equals(Registry* registry){
	KeyInteger* key=(KeyInteger*)registry->getKey();
 return this->getKey()->equals(key);
}
void RegPrimary::pack(Buffer* buffer){
	this->getKey()->pack(buffer);
	buffer->packField(&this->numberBlock,sizeof(this->numberBlock));
}
void RegPrimary::unPack(Buffer* buffer){
	this->setKey(new KeyInteger(0));
	this->getKey()->unPack(buffer);
	buffer->unPackField(&this->numberBlock,sizeof(this->numberBlock));
}
int RegPrimary::compareTo(Registry* registry){
	KeyInteger* key=(KeyInteger*)registry->getKey();
  return this->getKey()->compareTo(key);
}
unsigned int RegPrimary::getSize(){
    return NUM_FIELDS_REG_PRIMARY*sizeof(int);
}
int RegPrimary::print(std::ostream& outStream){
	this->getKey()->print(outStream);
	outStream<<" | ";
	outStream<<"numero Bloque: ";
	outStream<<this->numberBlock;
	outStream<<endl;
	if(this->mail != NULL)
		this->mail->print(outStream);
	return 1;
}
 int RegPrimary::getLongBytes(){
	 return getSize();
}
 int RegPrimary::getNumberBlock(){
     return numberBlock;
 }

 void RegPrimary::setNumberBlock(int numberBlock)
 {
     this->numberBlock = numberBlock;
 }

Mail *RegPrimary::getMail() const
{
    return mail;
}

void RegPrimary::setMail(Mail *mail)
{
    this->mail = mail;
}


