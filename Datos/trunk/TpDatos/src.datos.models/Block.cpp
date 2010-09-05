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
	for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		reg=*iterRegistry;
		reg->pack(this->buffer);
	}

}
void Block::unPack(){
	list<Registry*>::iterator iterRegistry;
	Registry* reg;
	for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		reg=*iterRegistry;
		reg->unPack(this->buffer);
	}
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
