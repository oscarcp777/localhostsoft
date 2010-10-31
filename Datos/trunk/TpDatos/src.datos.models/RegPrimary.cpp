/*
 * RegPrimary.cpp
 *
 *  Created on: 11/09/2010
 *      Author: oscar
 */

#include "RegPrimary.h"
#include "Key.h"
#include "KeyInteger.h"
#include "../src.datos.BTreeSharp/BlockDataManager.h"

RegPrimary::RegPrimary() {
	this->mail = NULL;
	this->numberBlock=-1;
}

RegPrimary::~RegPrimary() {

}
Registry* RegPrimary::clone(){
	RegPrimary* regPrimary = new RegPrimary();
	regPrimary->setKey((KeyInteger*)this->getKey()->clone());
	regPrimary->setNumberBlock(this->numberBlock);
	return regPrimary;
}
Registry* RegPrimary::cloneRegKey(){
	return this->getKey()->clone();
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
	KeyInteger* key=NULL;
	if(registry->getKey()==NULL){
		key=(KeyInteger*)registry;
	}
	else{
        key=(KeyInteger*)registry->getKey();
	}
  return this->getKey()->compareTo(key);
}
unsigned int RegPrimary::getSize(){
	int size=this->getKey()->getSize()+sizeof(this->numberBlock);
    return size;
}
int RegPrimary::print(std::ostream& outStream){
	outStream<<"key: ";
	this->getKey()->print(outStream);
	outStream<<" : offset ";
	outStream<<this->numberBlock;
	outStream<<endl;
	if(this->mail != NULL)
		this->mail->print(outStream);

	if(DATA==1&&DATA_SHOW==1){
		BlockDataManager* manager= new BlockDataManager();
		list<Registry*>::iterator iterRegistry;
		Block* blockMails;
		blockMails=manager->readBlockData(this->getNumberBlock(),this->container);
		outStream<<"Iucs de los Mails: ";
		for(iterRegistry = blockMails->iteratorBegin(); iterRegistry != blockMails->iteratorEnd(); iterRegistry++){
			Mail* mail=(Mail*)*iterRegistry;
			mail->getKey()->print(std::cout);

		}
		delete manager;
	}
	outStream<<endl;
	outStream<<endl;
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


