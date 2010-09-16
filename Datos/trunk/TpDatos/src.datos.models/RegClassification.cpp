/*
 * RegClassification.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "RegClassification.h"
#include "Key.h"

RegClassification::RegClassification() {
	// TODO Auto-generated constructor stub

}

RegClassification::~RegClassification() {
	// TODO Auto-generated destructor stub
}

Registry* RegClassification::clone(){
	RegClassification* regClone = new RegClassification();
	regClone->setKey((Key*)this->getKey()->clone());
	return regClone;
}
bool RegClassification::equals(Registry* registry){
	Key* key=(Key*)registry->getKey();
	return this->getKey()->equals(key) && this->attribute.compare(((RegClassification*)registry)->getAttribute());
}
void RegClassification::pack(Buffer* buffer){
	this->getKey()->pack(buffer);
	int size = this->attribute.size();
	buffer->packField(&size, sizeof(size));
	buffer->packField(this->attribute.c_str(),this->attribute.size());
}
void RegClassification::unPack(Buffer* buffer){
	this->setKey(new Key());
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
	return key->getSize()+this->attribute.size();
}
int RegClassification::print(std::ostream& outStream){
	Key* key=(Key*)this->getKey();
	outStream<<this->attribute<<" ";
	key->print(outStream);
	return 1;
}
int RegClassification::getLongBytes(){
	return this->getSize()+this->attribute.size();
}
Registry* RegClassification::cloneRegKey(){
	Key* key = new Key();
	key->setValue(this->getKey()->getValue());
	return key;
}
std::string RegClassification::getAttribute() {
	return this->attribute;
}
void RegClassification::setAttribute(std::string atribute){
	this->attribute = atribute;
}
