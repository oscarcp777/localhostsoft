/*
 * KeyString.cpp
 *
 *  Created on: 24/09/2010
 *      Author: oscar
 */

#include "KeyString.h"

KeyString::KeyString(string value) {
	this->value=value;
	this->key=NULL;
}
KeyString::KeyString(){
	this->key=NULL;
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
	    int size=this->value.size();
		buffer->packField(&size, sizeof(size));
		buffer->packField(this->value.c_str(),size);
}
void KeyString::unPack(Buffer* buffer){
	int size;
	buffer->unPackField(&size, sizeof(size));
	buffer->unPackFieldString(this->value,size);
}
int  KeyString::print(std::ostream& outStream){
	outStream<<" Clave : "<<this->value;
     return 1;
}
int KeyString::getLongBytes(){
	return this->getSize();
}
void KeyString::setValue(string value){
	this->value = value;
}

Registry* KeyString::clone(){
	return  new KeyString(this->getValue());
}

int KeyString::compareTo(Registry* registry){
	KeyString* key=(KeyString*)registry;
	int result=this->value.compare(key->getValue());
	if(result < 0)
		return 1;
	else if(result > 0)
		return -1;
	else return 0;
}
Registry* KeyString::cloneRegKey(){
	return this->clone();
}
