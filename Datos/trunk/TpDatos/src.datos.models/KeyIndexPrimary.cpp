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
	outStream<<"Clave : KeyIndexPrimary "<<this->value <<endl;
     return 1;
}
int  KeyIndexPrimary::getValue(){
	return this->value;
}
bool KeyIndexPrimary::equals(Registry* comp){
	KeyIndexPrimary* key = (KeyIndexPrimary*) comp;

	return this->value == key->getValue();
}
