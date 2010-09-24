/*
 * KeyString.cpp
 *
 *  Created on: 24/09/2010
 *      Author: oscar
 */

#include "KeyString.h"

KeyString::KeyString(string value) {
	this->value=value;

}
KeyString::KeyString(){

}
KeyString::~KeyString() {
	// TODO Auto-generated destructor stub
}
string KeyString::getValue(){
	return this->value;
}
unsigned int KeyString::getSize(){
	return this->value.size()+sizeof(int);
}
bool KeyString::equals(Registry* comp){
	KeyString* key= (KeyString*)comp;
	return((this->value.compare(key->getValue())==0));
}
void KeyString::pack(Buffer* buffer){
	    int size=this->getSize();
		buffer->packField(&size, sizeof(size));
		buffer->packField(this->value.c_str(),this->getSize());
}
void KeyString::unPack(Buffer* buffer){
	int size;
	buffer->unPackField(&size, sizeof(size));
	buffer->unPackFieldString(this->value,size);
}
int  KeyString::print(std::ostream& outStream){
	outStream<<"Clave : "<<this->value;
     return 1;
}
int KeyString::getLongBytes(){
	return this->getSize();
}
void KeyString::setValue(string value){
	this->value = value;
}

Registry* KeyString::clone(){
	KeyString* cloneKeyString = new KeyString();
	string copy = this->getValue();
	cloneKeyString->setValue(copy);
	return cloneKeyString;
}

int KeyString::compareTo(Registry* registry){
	KeyString* key=(KeyString*)registry;
	return this->value.compare(key->getValue());
}
Registry* KeyString::cloneRegKey(){
	return NULL;
}
