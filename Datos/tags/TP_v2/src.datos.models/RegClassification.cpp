/*
 * RegClassification.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "RegClassification.h"
#include "KeyString.h"

RegClassification::RegClassification() {
	this->numBlock=-1;

}

RegClassification::~RegClassification() {
	for (list<KeyInteger*>::iterator it = this->listIuc.begin();it!=this->listIuc.end(); it++) {
		KeyInteger* key=(KeyInteger*)*it;
		delete key;
	}
}
void RegClassification::clearListIuc(){
	this->listIuc.clear();
}
void RegClassification::setListIuc(list<KeyInteger*> &listIucNew){
	this->listIuc.clear();
	listIucNew.swap(this->listIuc);
}
Registry* RegClassification::clone(){
	RegClassification* regClone = new RegClassification();
	regClone->setKey((KeyString*)this->getKey()->clone());
	regClone->setNumBlock(this->numBlock);
	return regClone;
}
bool RegClassification::equals(Registry* registry){
	KeyString* key=(KeyString*)registry->getKey();
	return this->getKey()->equals(key) ;
}
void RegClassification::pack(Buffer* buffer){
	this->getKey()->pack(buffer);
	buffer->packField(&this->numBlock,sizeof(this->numBlock));
}
void RegClassification::unPack(Buffer* buffer){
	this->setKey(new KeyString(""));
	this->getKey()->unPack(buffer);
	buffer->unPackField(&this->numBlock,sizeof(this->numBlock));
}
int RegClassification::compareTo(Registry* registry){
	KeyString* key=NULL;
	if(registry->getKey()==NULL){
		key=(KeyString*)registry;
	}
	else{
		key=(KeyString*)registry->getKey();
	}
	return this->getKey()->compareTo(key);
}
unsigned int RegClassification::getSize(){
	KeyString* key=(KeyString*)this->getKey();
	return key->getSize()+sizeof(this->numBlock);
}
int RegClassification::print(std::ostream& outStream){
	this->getKey()->print(outStream);
	outStream<<" | ";
	outStream<<this->numBlock;
	outStream<<endl;
	if(!this->listIuc.empty()){
		outStream<<"lista de Iuc : ";
		for (list<KeyInteger*>::iterator it = this->listIuc.begin();it!=this->listIuc.end(); it++) {
			KeyInteger* key=(KeyInteger*)*it;
			key->print(outStream);
		}
	outStream<<endl;
	}
	return 1;
}
int RegClassification::getLongBytes(){
	return this->getSize();
}
Registry* RegClassification::cloneRegKey(){
	return this->getKey()->clone();
}

int RegClassification::getNumBlock() const
{
	return numBlock;
}

void RegClassification::addIuc(KeyInteger* keyIuc)
{
	this->listIuc.push_back(keyIuc);
}

KeyInteger* RegClassification::getIuc() const
{
	return (KeyInteger*)this->listIuc.back();
}

list<KeyInteger* > RegClassification::getIucs() const
{
	return this->listIuc;
}

void RegClassification::setNumBlock(int numBlock)
{
	this->numBlock = numBlock;
}

