/*
 * RegKeyPrimary.cpp
 *
 *  Created on: 16/09/2010
 *      Author: oscar
 */

#include "RegKeyPrimary.h"
#include "Key.h"
#include "KeyInteger.h"
RegKeyPrimary::RegKeyPrimary() {
	// TODO Auto-generated constructor stub

}

RegKeyPrimary::~RegKeyPrimary() {
	// TODO Auto-generated destructor stub
}
Registry* RegKeyPrimary::clone(){
	RegKeyPrimary* regKeyPrimary = new RegKeyPrimary();
	regKeyPrimary->setKey((KeyInteger*)this->getKey()->clone());
	return regKeyPrimary;
}
bool RegKeyPrimary::equals(Registry* registry){
	KeyInteger* key=(KeyInteger*)registry->getKey();
	return this->getKey()->equals(key);
}
void RegKeyPrimary::pack(Buffer* buffer){
	this->getKey()->pack(buffer);
}
void RegKeyPrimary::unPack(Buffer* buffer){
	this->setKey(new KeyInteger(0));
	this->getKey()->unPack(buffer);
}
int RegKeyPrimary::compareTo(Registry* registry){
	KeyInteger* key=(KeyInteger*)registry->getKey();
	return this->getKey()->compareTo(key);
}
unsigned int RegKeyPrimary::getSize(){
	KeyInteger* key=(KeyInteger*)this->getKey();
	return key->getSize();
}
int RegKeyPrimary::print(std::ostream& outStream){
	KeyInteger* key=(KeyInteger*)this->getKey();
	key->print(outStream);
	return 1;
}
int RegKeyPrimary::getLongBytes(){
	return getSize();
}
Registry* RegKeyPrimary::cloneRegKey(){
	return NULL;

}
