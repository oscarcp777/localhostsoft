/*
 * RegClassification.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "RegClassification.h"
#include "KeyString.h"
#include "RegKeyClassification.h"

RegClassification::RegClassification() {
	// TODO Auto-generated constructor stub

}

RegClassification::~RegClassification() {
	// TODO Auto-generated destructor stub
}

Registry* RegClassification::clone(){
	RegClassification* regClone = new RegClassification();
	regClone->setKey((Key*)this->getKey()->clone());
	regClone->setAttribute(this->attribute);
	return regClone;
}
bool RegClassification::equals(Registry* registry){
	Key* key=(Key*)registry->getKey();
	return this->getKey()->equals(key) ;
}
void RegClassification::pack(Buffer* buffer){
	this->getKey()->pack(buffer);
	int size = this->attribute.size();
	buffer->packField(&size, sizeof(size));
	buffer->packField(this->attribute.c_str(),size);
}
void RegClassification::unPack(Buffer* buffer){
	this->setKey(new KeyString(""));
	this->getKey()->unPack(buffer);
	int size;
	buffer->unPackField(&size, sizeof(size));
	buffer->unPackFieldString(this->attribute,size);
}
int RegClassification::compareTo(Registry* registry){
	Key* key=(Key*)registry->getKey();
	return this->getKey()->compareTo(key);
}
unsigned int RegClassification::getSize(){
	Key* key=(Key*)this->getKey();
	return key->getSize()+sizeof(int)+this->attribute.size();
}
int RegClassification::print(std::ostream& outStream){
	this->getKey()->print(outStream);
		outStream<<" | ";
		outStream<<this->attribute;
		outStream<<endl;
	return 1;
}
int RegClassification::getLongBytes(){
	return this->getSize();
}
Registry* RegClassification::cloneRegKey(){
	RegKeyClassification* regKeyClassification=new RegKeyClassification();
	regKeyClassification->setKey(this->getKey());
	return regKeyClassification;
}
std::string RegClassification::getAttribute() {
	return this->attribute;
}
void RegClassification::setAttribute(std::string atribute){
	this->attribute = atribute;
}

int RegClassification::getNumBlock() const
{
    return numBlock;
}

void RegClassification::addIuc(unsigned int iuc)
{
	this->listIuc.push_back(iuc);
}

void RegClassification::setNumBlock(int numBlock)
{
    this->numBlock = numBlock;
}


