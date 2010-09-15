/*
 * RegPrimary.cpp
 *
 *  Created on: 11/09/2010
 *      Author: oscar
 */

#include "RegPrimary.h"
#include "Key.h"
#include "KeyIndexPrimary.h"

RegPrimary::RegPrimary() {
	this->setInternal(false);

}
RegPrimary::RegPrimary(bool internal) {
	this->setInternal(internal);
}
RegPrimary::~RegPrimary() {
	// TODO Auto-generated destructor stub
}
Registry* RegPrimary::clone(){
	RegPrimary* regPrimary = new RegPrimary();
	regPrimary->setInternal(true);
	regPrimary->setKey((KeyIndexPrimary*)this->getKey()->clone());
	return regPrimary;
}
bool RegPrimary::equals(Registry* registry){
	KeyIndexPrimary* key=(KeyIndexPrimary*)registry->getKey();
 return this->getKey()->equals(key);
}
void RegPrimary::pack(Buffer* buffer){
	this->getKey()->pack(buffer);
	if(!this->isInternal())
	buffer->packField(&this->numberBlock,sizeof(this->numberBlock));
}
void RegPrimary::unPack(Buffer* buffer){
	this->setKey(new KeyIndexPrimary(0));
	this->getKey()->unPack(buffer);
	if(!this->isInternal())
	buffer->unPackField(&this->numberBlock,sizeof(this->numberBlock));
}
int RegPrimary::compareTo(Registry* registry){
	KeyIndexPrimary* key=(KeyIndexPrimary*)registry->getKey();
  return this->getKey()->compareTo(key);
}
unsigned int RegPrimary::getSize(){
	int sizeBusyAll=0;
	if(!this->isInternal())
		sizeBusyAll=NUM_FIELDS_REG_PRIMARY*sizeof(int);
	else{
		KeyIndexPrimary* key=(KeyIndexPrimary*)this->getKey();
		sizeBusyAll=key->getSize();
	}

    return sizeBusyAll;
}
int RegPrimary::print(std::ostream& outStream){
	this->getKey()->print(outStream);
	if(!this->isInternal()){
	outStream<<" | ";
	outStream<<"numero Bloque: ";outStream<<this->numberBlock;
	}
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
