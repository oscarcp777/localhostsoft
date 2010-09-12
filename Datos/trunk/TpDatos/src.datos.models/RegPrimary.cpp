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
	// TODO Auto-generated constructor stub

}

RegPrimary::~RegPrimary() {
	// TODO Auto-generated destructor stub
}
Registry* RegPrimary::clone(){
	return NULL;
}
bool RegPrimary::equals(Registry* comp){
 return true;
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
  return 1;
}
int RegPrimary::getSize(){
    return NUM_FIELDS_REG_PRIMARY*sizeof(int);
}
int RegPrimary::print(std::ostream& outStream){
	outStream<<"numero Bloque: "<<this->numberBlock<<"   clave: "<<this->getKey()->print(outStream)<<endl;
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
