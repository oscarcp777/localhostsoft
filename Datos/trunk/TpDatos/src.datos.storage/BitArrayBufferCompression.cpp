/*
 * BitArrayBufferCompression.cpp
 *
 *  Created on: 23/10/2010
 *      Author: oscar
 */

#include "BitArrayBufferCompression.h"
#include "../src.datos.compression/BitInput.h"
#include "../src.datos.compression/BitOutput.h"

BitArrayBufferCompression::BitArrayBufferCompression(int maxBytes):Buffer(maxBytes)  {

}

BitArrayBufferCompression::~BitArrayBufferCompression() {

}
void BitArrayBufferCompression::write(int b){
    char field=(char)b;
	this->packField(&field,sizeof(char));
}

void BitArrayBufferCompression::reset(){
   this->clear();
}
char* BitArrayBufferCompression::toByteArray(){
	return this->buffer;
}


string BitArrayBufferCompression::toString(){
	string str="";
	str.assign(this->buffer);
	return str;
}

int BitArrayBufferCompression::read(){
	  char field='0';
	  this->unPackField(&field,sizeof(char));
	  return field;
}

