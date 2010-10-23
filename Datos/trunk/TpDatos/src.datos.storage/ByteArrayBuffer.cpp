/*
 * ByteArrayBuffer.cpp
 *
 *  Created on: 23/10/2010
 *      Author: oscar
 */

#include "ByteArrayBuffer.h"

ByteArrayBuffer::ByteArrayBuffer(int maxBytes):Buffer(maxBytes) {
	// TODO Auto-generated constructor stub

}

ByteArrayBuffer::~ByteArrayBuffer() {
	// TODO Auto-generated destructor stub
}

void ByteArrayBuffer::write(int b){
    char field=(char)b;
	this->packField(&field,sizeof(char));
}

void ByteArrayBuffer::reset(){
   this->clear();
}
char* ByteArrayBuffer::toByteArray(){
	return this->buffer;
}


string ByteArrayBuffer::toString(){
	string str="";
	str.assign(this->buffer);
	return str;
}

int ByteArrayBuffer::read(){
	  char field='0';
	  this->unPackField(&field,sizeof(char));
	  return field;
}


