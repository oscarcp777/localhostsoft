/*
 * Block.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Block.h"
#include "FactoryOfRegistry.h"

Block::Block(unsigned int maxLong, unsigned int numBlock, unsigned int level) throw(){
	this->freeSize=BLOCK_SIZE;
	this->maxLong=maxLong;
	this->numBlock=numBlock;
	this->level= level;
}
Block::Block(){

}
Block::~Block() throw(){
	list<Registry*>::iterator iterRegistry;
		Registry* reg;
		for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
			reg=*iterRegistry;
			delete reg;
		}
}
int Block::getSize(){
   return BLOCK_SIZE;
}

list<Registry*>::iterator Block::iteratorBegin(){
	return this->regList.begin();
}
list<Registry*>::iterator Block::iteratorEnd(){
	return this->regList.end();
}
void Block::setSizeFree(int size){
	this->freeSize = size;
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
void Block::transferRegistry(list<Registry*> &listElement) throw() {
	listElement.clear();
	this->regList.swap(listElement);
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
	this->packMetadata(buffer);
    this->packListRegistry(buffer);

}
void Block::packListRegistry(Buffer* buffer){
	list<Registry*>::iterator iterRegistry;
	Registry* reg;
	for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		reg=*iterRegistry;
		reg->pack(buffer);
	}

}
void Block::unPack(Buffer* buffer){
	int numberElements = this->unPackMetadata(buffer);
   this->unPackListRegistry(buffer,numberElements,TYPE_REG_PRIMARY);

}
void Block::unPackListRegistry(Buffer* buffer,int numberElements,int typeElement){
	list<Registry*>::iterator iterRegistry;
	Registry* reg;
	//TODO llamar a la fabrica con una constante para saber que clase instanciar
	FactoryOfRegistry* factory = new FactoryOfRegistry();
	for(int i=0; i<numberElements; i++){
		this->regList.push_back(factory->createRegistry(typeElement));
	}
	for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		reg=*iterRegistry;
		reg->unPack(buffer);
	}
}
void Block::packMetadata(Buffer* buffer){
	int numberElements = this->regList.size();
    buffer->packField(&numberElements, sizeof(numberElements));
	buffer->packField(&this->freeSize, sizeof(this->freeSize));
}
int Block::unPackMetadata(Buffer* buffer){
	int numberElements;
	buffer->unPackField(&numberElements,sizeof(numberElements));
	buffer->unPackField(&this->freeSize,sizeof(this->freeSize));
	return numberElements;
}
int Block::print(std::ostream& outStream){
	list<Registry*>::iterator iterRegistry;
		Registry* reg;
		for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
			reg=*iterRegistry;
			reg->print(outStream);
		}
		return 1;
}

unsigned int Block::getNumBlock() const throw(){
	return this->numBlock;
}

void Block::setNumBlock(unsigned int numBlock) throw(){
	this->numBlock = numBlock;
}

unsigned int Block::getLevel() const throw(){
	return this->level;
}

void Block::setLevel(unsigned int level) throw(){
	this->level = level;
}

bool Block::isLeaf() const throw(){
	return this->getLevel() == 0;
}

void Block::addComponent(Registry* registry) throw(){
	if (registry != NULL) {
		if (this->posibleToAgregateComponent(registry))
			this->addReg(registry);
	}else {
		std::cout << "No se pudo agregar en bloque BSharp... " << std::endl;
	}
}

void Block::addComponent(Registry* registry,list<Registry*>::iterator it,int pos) throw() {

		if (registry != NULL) {
		if (this->posibleToAgregateComponent(registry)) {
			 for (int var = 0; var < pos; var++) {
				 it++;
			}
			this->freeSize-= registry->getSize();
			this->regList.insert(it,registry);

		}
	}
}
unsigned int Block::getOcupedLong() const throw() {
//	unsigned int longitud_ocupada = Bloque::obtener_longitud_ocupada();
//	longitud_ocupada += sizeof(unsigned int);
//	longitud_ocupada += sizeof(unsigned int);
//	return longitud_ocupada;
	return this->maxLong - this->freeSize;
}

unsigned int Block::getLongBytes() const throw(){
	return maxLong;

}

unsigned int Block::getMaxLong() const throw(){
	return maxLong;
}

void Block::setMaxLong(unsigned int maxLong) throw(){
	this->maxLong = maxLong;
}
int Block::getLongBytes(){
	return this->maxLong;
}
bool Block::posibleToAgregateComponent(Registry* registry) const throw(){
	unsigned int ocupedLong = this->getOcupedLong();
	if (registry != NULL) {
		if (ocupedLong + registry->getLongBytes() <= this->getMaxLong()) {
			return true;
		} else {
			return false;
		}
	}
	return true;
}
