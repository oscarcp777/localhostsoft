/*
 *
 * Buffer.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Buffer.h"


Buffer::Buffer(int maxBytes){
	if(maxBytes < 0) maxBytes = 0;
	this->maxBytes = maxBytes;
	this->buffer = new char[this->maxBytes];
	memset(this->buffer,0,this->maxBytes);
	this->bufferSize = 0;
	this->init();
}
void Buffer::init(){
	this->nextByte = 0;
}
Buffer::~Buffer() {
	  delete[] buffer;
}

void Buffer::clear(){
	this->nextByte = 0;
	this->bufferSize = 0;
    memset(this->buffer,0,this->maxBytes);
}
int Buffer::packField(const void* field,int size){
	int len;// longitud de la cadena para ser embalado
	if(size>=0)len=size;
	else len=strlen((char*)field);
	int start =this->nextByte;
	this->nextByte+=len;
	if(this->nextByte>this->maxBytes){return -1;}
	memcpy(&this->buffer[start],field,len);
	this->bufferSize=this->nextByte;
	return len;
}
int Buffer::unPackField(void* field,int size){
	if(this->nextByte>=this->maxBytes)return -1;// no hay mas campos
	int start =this->nextByte;
	this->nextByte+=size;
	memcpy(field,&buffer[start],size);
	return size;
}

/*Obtiene un string en la siguiente posicio del stream.*/
int Buffer::unPackFieldString(string& field, int size){
	char* aux = new char[size+1];
	  int pos=this->unPackField(aux,size);
	aux[size] = '\0';
	field = aux;
	delete[] aux;

	return pos;
}
char *Buffer::getData() const
{
    return buffer;
}

int Buffer::getBufferSize() const
{
    return bufferSize;
}

int Buffer::getMaxBytes() const
{
    return maxBytes;
}

int Buffer::getNextByte() const
{
    return nextByte;
}



void Buffer::setBufferSize(int bufferSize)
{
    this->bufferSize = bufferSize;
}

void Buffer::setMaxBytes(int maxBytes)
{
    this->maxBytes = maxBytes;
}

void Buffer::setNextByte(int nextByte)
{
    this->nextByte = nextByte;
}

int Buffer::print(){
    cout<<this->buffer<<endl;
    return 1;
}

