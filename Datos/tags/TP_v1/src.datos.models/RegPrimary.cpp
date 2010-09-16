/*
 * RegPrimary.cpp
 *
 *  Created on: 11/09/2010
 *      Author: oscar
 */

#include "RegPrimary.h"
#include "Key.h"
#include "KeyIndexPrimary.h"
#include "RegKeyPrimary.h"

RegPrimary::RegPrimary() {
}

RegPrimary::~RegPrimary() {
	// TODO Auto-generated destructor stub
}
Registry* RegPrimary::clone(){
	RegPrimary* regPrimary = new RegPrimary();
	regPrimary->setKey((KeyIndexPrimary*)this->getKey()->clone());
	regPrimary->setNumberBlock(this->numberBlock);
	return regPrimary;
}
Registry* RegPrimary::cloneRegKey(){
	RegKeyPrimary* regKeyPrimary = new RegKeyPrimary();
	regKeyPrimary->setKey((KeyIndexPrimary*)this->getKey()->clone());
	return regKeyPrimary;
}
bool RegPrimary::equals(Registry* registry){
	KeyIndexPrimary* key=(KeyIndexPrimary*)registry->getKey();
 return this->getKey()->equals(key);
}
void RegPrimary::pack(Buffer* buffer){
	this->getKey()->pack(buffer);
	buffer->packField(&this->numberBlock,sizeof(this->numberBlock));
}
void RegPrimary::unPack(Buffer* buffer){
	this->setKey(new KeyIndexPrimary(0));
	this->getKey()->unPack(buffer);
	buffer->unPackField(&this->numberBlock,sizeof(this->numberBlock));
}
int RegPrimary::compareTo(Registry* registry){
	KeyIndexPrimary* key=(KeyIndexPrimary*)registry->getKey();
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
