/*
 * Block.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Block.h"

Block::Block() {
	this->freeSize=BLOCK_SIZE;
	this->buffer= new Buffer(BLOCK_SIZE);

}
int Block::getSize(){
   return BLOCK_SIZE;
}
Buffer* Block::getBuffer(){
  return this->buffer;
}
Block::~Block() {
	list<Registry*>::iterator iterRegistry;
		Registry* reg;
		for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
			reg=*iterRegistry;
			delete reg;
		}
}
int Block::getNumElements(){
	return this->regList.size();
}

int Block::getFreeSize(){
	return this->freeSize;
}

void Block::addReg(Registry* reg){
		this->regList.push_back(reg);
		this->freeSize-=reg->getSize();

}

Registry* Block::getReg(Key* key){
	list<Registry*>::iterator iterRegistry;
	Registry* reg;
	for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		reg=*iterRegistry;
		if(key->equals(reg->getKey())){
			return reg;
		}
	}
	return NULL;
}
void Block::pack(){
	list<Registry*>::iterator iterRegistry;
	Registry* reg;
	this->packMetadata();
	for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		reg=*iterRegistry;
		reg->pack(this->buffer);
	}

}
void Block::unPack(){
	list<Registry*>::iterator iterRegistry;
	Registry* reg;
	int numberElements;
	numberElements = this->unPackMetadata();
	//TODO llamar a la fabrica con una constante para saber que clase instanciar

	for(int i=0; i<numberElements; i++){
		this->regList.push_back(new Mail());//TODO CAMBIAR no va new Mail()
	}
	for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		reg=*iterRegistry;
		reg->unPack(this->buffer);
	}
}

void Block::packMetadata(){
	int numberElements = this->regList.size();
	this->buffer->packField(&numberElements, sizeof(numberElements));
	this->buffer->packField(&this->freeSize, sizeof(this->freeSize));
}
int Block::unPackMetadata(){
	int numberElements;
	this->buffer->unPackField(&numberElements,sizeof(numberElements));
	this->buffer->unPackField(&this->freeSize,sizeof(this->freeSize));
	return numberElements;
}
int Block::print(){
	list<Registry*>::iterator iterRegistry;
		Registry* reg;
		for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
			reg=*iterRegistry;
			reg->print();
		}
		return 1;
}
