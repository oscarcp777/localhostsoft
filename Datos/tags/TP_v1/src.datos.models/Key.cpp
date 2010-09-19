/*
 * Key.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Key.h"

Key::Key(string value) {
	this->value=value;
}
Key::Key() {
}
Key::~Key() {
	// TODO Auto-generated destructor stub
}
string Key::getValue(){
	return this->value;
}
unsigned int Key::getSize(){
	return this->value.size();
}
bool Key::equals(Registry* comp){
	Key* key= (Key*)comp;
	return((this->value.compare(key->getValue())==0));
}
void Key::pack(Buffer* buffer){
	    int size=this->getSize();
		buffer->packField(&size, sizeof(size));
		buffer->packField(this->value.c_str(),this->getSize());
}
void Key::unPack(Buffer* buffer){
	int size;
	buffer->unPackField(&size, sizeof(size));
	buffer->unPackFieldString(this->value,size);
}
int  Key::print(std::ostream& outStream){
	outStream<<"Clave : "<<this->value;
     return 1;
}
int Key::getLongBytes(){
	//TODO
	return this->value.length();
}
void Key::setValue(string value){
	this->value = value;
}

Registry* Key::clone(){
	Key* cloneKey = new Key();
	string copy = this->getValue();
	cloneKey->setValue(copy);
	cout<<"EN CLONE this->getValue()  "<<this->getValue()<<endl;
	cout<<"EN CLONE cloneKey"<<cloneKey->getValue()<<endl;
	return cloneKey;
}

int Key::compareTo(Registry* registry){
	Key* key=(Key*)registry;
	return this->value.compare(key->getValue());
}
Registry* Key::cloneRegKey(){
	return NULL;
}