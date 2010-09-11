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
int Key::getSize(){
	if(this->getValueInt()>=0)return sizeof(int);
	else return this->value.length();
}
bool Key::equals(Registry* comp){
	Key* key= (Key*)comp;
	return((this->value.compare(key->getValue())==0));
}
int Key::getValueInt(){
	int i=-1;
	istringstream myStream(this->value);
	myStream>>i;
	return i;
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
	outStream<<"Clave : "<<this->value<<endl;
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
	cloneKey->setValue(this->getValue());
	return cloneKey;
}

