/*
 * RegKeyPrimary.cpp
 *
 *  Created on: 16/09/2010
 *      Author: oscar
 */

#include "RegKeyPrimary.h"
#include "Key.h"
#include "KeyIndexPrimary.h"
RegKeyPrimary::RegKeyPrimary() {
	// TODO Auto-generated constructor stub

}

RegKeyPrimary::~RegKeyPrimary() {
	// TODO Auto-generated destructor stub
}
Registry* RegKeyPrimary::clone(){
	RegKeyPrimary* regKeyPrimary = new RegKeyPrimary();
	regKeyPrimary->setKey((KeyIndexPrimary*)this->getKey()->clone());
	return regKeyPrimary;
}
bool RegKeyPrimary::equals(Registry* registry){
	KeyIndexPrimary* key=(KeyIndexPrimary*)registry->getKey();
	return this->getKey()->equals(key);
}
void RegKeyPrimary::pack(Buffer* buffer){
	this->getKey()->pack(buffer);
}
void RegKeyPrimary::unPack(Buffer* buffer){
	this->setKey(new KeyIndexPrimary(0));
	this->getKey()->unPack(buffer);
}
int RegKeyPrimary::compareTo(Registry* registry){
	KeyIndexPrimary* key=(KeyIndexPrimary*)registry->getKey();
	return this->getKey()->compareTo(key);
}
unsigned int RegKeyPrimary::getSize(){
	KeyIndexPrimary* key=(KeyIndexPrimary*)this->getKey();
	return key->getSize();
}
int RegKeyPrimary::print(std::ostream& outStream){
	KeyIndexPrimary* key=(KeyIndexPrimary*)this->getKey();
	key->print(outStream);
	return 1;
}
int RegKeyPrimary::getLongBytes(){
	return getSize();
}
Registry* RegKeyPrimary::cloneRegKey(){
	return NULL;

}
