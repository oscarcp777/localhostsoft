/*
 * KeyIndexPrimary.cpp
 *
 *  Created on: 11/09/2010
 *      Author: oscar
 */

#include "KeyIndexPrimary.h"

KeyIndexPrimary::KeyIndexPrimary(int value) {
this->value=value;

}
KeyIndexPrimary::KeyIndexPrimary() {
}

KeyIndexPrimary::~KeyIndexPrimary() {
	// TODO Auto-generated destructor stub
}
void KeyIndexPrimary::pack(Buffer* buffer){
      buffer->packField(&this->value,sizeof(this->value));
}
void KeyIndexPrimary::unPack(Buffer* buffer){
	buffer->unPackField(&this->value,sizeof(this->value));
}
int KeyIndexPrimary::getSize(){
	return sizeof(this->value);
}
int KeyIndexPrimary::getLongBytes(){
	return this->getSize();
}
int  KeyIndexPrimary::print(std::ostream& outStream){
	outStream<<"Clave : ";
	outStream<<this->value;
	outStream<<" | ";
     return 1;
}
int  KeyIndexPrimary::getValue(){
	return this->value;
}
bool KeyIndexPrimary::equals(Registry* comp){
	KeyIndexPrimary* key = (KeyIndexPrimary*) comp;

	return this->value == key->getValue();
}
int KeyIndexPrimary::compareTo(Registry* registry){
	KeyIndexPrimary* key = (KeyIndexPrimary*) registry;
	 if(this->value > key->getValue())
		 return 1;
	 else  if(this->value < key->getValue())
		 return -1;
	 else return 0;

}
Registry* KeyIndexPrimary::clone(){
	return new KeyIndexPrimary(this->value);

}
