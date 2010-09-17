/*
 * RegKeyClassification.cpp
 *
 *  Created on: 16/09/2010
 *      Author: oscar
 */

#include "RegKeyClassification.h"
#include "Key.h"

RegKeyClassification::RegKeyClassification() {
	// TODO Auto-generated constructor stub

}

RegKeyClassification::~RegKeyClassification() {
	// TODO Auto-generated destructor stub
}
Registry* RegKeyClassification::clone(){
	RegKeyClassification* regKeyClassification = new RegKeyClassification();
	Key* key=(Key*)this->getKey()->clone();
	regKeyClassification->setKey(key);
	return regKeyClassification;
}
bool RegKeyClassification::equals(Registry* registry){
	return this->getKey()->equals(registry->getKey());
}
void RegKeyClassification::pack(Buffer* buffer){
	this->getKey()->pack(buffer);
}
void RegKeyClassification::unPack(Buffer* buffer){
	this->setKey(new Key(""));
	this->getKey()->unPack(buffer);
}
int RegKeyClassification::compareTo(Registry* registry){
	return this->getKey()->compareTo(registry->getKey());
}
unsigned int RegKeyClassification::getSize(){
	return this->getKey()->getSize();
}
int RegKeyClassification::print(std::ostream& outStream){
	this->getKey()->print(outStream);
	return 1;
}
int RegKeyClassification::getLongBytes(){
	return this->getSize();
}
Registry* RegKeyClassification::cloneRegKey(){
	return NULL;

}
