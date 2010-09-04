/*
 * Block.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Block.h"

Block::Block() {
	// TODO Auto-generated constructor stub

}

Block::~Block() {
	// TODO Auto-generated destructor stub
}
int Block::getNumElements(){
	return this->regList.size();
}

int Block::getFreeSize(){
	return this->freeSize;
}

void Block::addReg(Registry* reg){
	this->regList.push_back(reg);
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
void Block::pack(Buffer* buffer){

}
void Block::unPack(Buffer* buffer){

}
