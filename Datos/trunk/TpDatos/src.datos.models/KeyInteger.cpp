/*
 * KeyInteger.cpp
 *
 *  Created on: 11/09/2010
 *      Author: oscar
 */

#include "KeyInteger.h"

KeyInteger::KeyInteger(int value) {
this->value=value;
this->key=NULL;

}
KeyInteger::KeyInteger() {
	this->key=NULL;
}
Registry* KeyInteger::cloneRegKey(){
  return this->clone();
}
KeyInteger::~KeyInteger() {
	// TODO Auto-generated destructor stub
}
void KeyInteger::pack(Buffer* buffer){
      buffer->packField(&this->value,sizeof(this->value));
}
void KeyInteger::unPack(Buffer* buffer){
	buffer->unPackField(&this->value,sizeof(this->value));
}
unsigned int KeyInteger::getSize(){
	return sizeof(this->value);
}
int KeyInteger::getLongBytes(){
	return this->getSize();
}
int  KeyInteger::print(std::ostream& outStream){
	outStream<<"(";
	outStream<<this->value;
	outStream<<")";
     return 1;
}
int  KeyInteger::getValue(){
	return this->value;
}
bool KeyInteger::equals(Registry* comp){
	KeyInteger* key = (KeyInteger*) comp;
	return this->value == key->getValue();
}
int KeyInteger::compareTo(Registry* registry){
	KeyInteger* key = (KeyInteger*) registry;
	 if(this->value > key->getValue())
		 return 1;
	 else  if(this->value < key->getValue())
		 return -1;
	 else return 0;

}
Registry* KeyInteger::clone(){
	return new KeyInteger(this->value);

}
unsigned int KeyInteger::getlongBytesCompressed(){
  return BitOutput::getOcupedBytes(this->value);
}
void KeyInteger::packCompressed(BitOutput* compressor){
	compressor->writeDelta(this->value);
}
void KeyInteger::unPackCompressed(BitInput* compressor){
  this->value=compressor->readDelta();
}
