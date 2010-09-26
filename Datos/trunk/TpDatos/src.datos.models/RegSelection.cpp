/*
 * RegSelection.cpp
 *
 *  Created on: 26/09/2010
 *      Author: richy
 */

#include "RegSelection.h"
#include "Key.h"
#include "KeyInteger.h"

RegSelection::RegSelection() {
	// TODO Auto-generated constructor stub

}

RegSelection::~RegSelection() {
	// TODO Auto-generated destructor stub
}

Registry* RegSelection::clone(){
	RegSelection* regClone = new RegSelection();
	regClone->setKey((Key*)this->getKey()->clone());
	return regClone;
}
bool RegSelection::equals(Registry* registry){
	Key* key=(Key*)registry->getKey();
	return this->getKey()->equals(key) ;
}
void RegSelection::pack(Buffer* buffer){
	this->getKey()->pack(buffer);

}
void RegSelection::unPack(Buffer* buffer){
	this->setKey(new KeyInteger(-1));
	this->getKey()->unPack(buffer);

}
int RegSelection::compareTo(Registry* registry){
	Key* key=(Key*)registry->getKey();
	return this->getKey()->compareTo(key);
}
unsigned int RegSelection::getSize(){
	Key* key=(Key*)this->getKey();
	return key->getSize()+sizeof(int);
}
int RegSelection::print(std::ostream& outStream){
	this->getKey()->print(outStream);

	return 1;
}
int RegSelection::getLongBytes(){
	return this->getSize();
}
Registry* RegSelection::cloneRegKey(){
	return this->clone();
}
