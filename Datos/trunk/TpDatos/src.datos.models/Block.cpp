/*
 * Block.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Block.h"

Block::Block(unsigned int maxLong, unsigned int numBlock, unsigned int level) throw(){
	this->freeSize=BLOCK_SIZE;
	this->buffer= new Buffer(BLOCK_SIZE);

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
Buffer* Block::getBuffer(){
  return this->buffer;
}
list<Registry*>::iterator Block::iterator(){
	return this->regList.begin();
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

void Block::addComponent(Component* component) throw(){
	//TODO MODIFICAR CODIFO TOPO
	//	if (componente != NULL) {
//			if (this->puede_agregar_componente(componente)) {
//			            Bloque::agregar_componente(componente);
//			}
//		} else {
//			std::cout << "No se pudo agregar en bloque BSharp... " << std::endl;
//		}
}

void Block::addComponent(Component* component, int pos/*, ComponenteCompuesto::iterador_componentes posicion*/) throw(){
	//TODO MODIFICAR CODIFO TOPO
	//	if (componente != NULL) {
//		if (this->puede_agregar_componente(componente)) {
//			Bloque::agregar_componente(componente, posicion);
//		}
//	}
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
bool Block::posibleToAgregateComponent(Component* component) const throw(){
	unsigned int ocupedLong = this->getOcupedLong();
	if (component != NULL) {
		if (ocupedLong + component->getLongBytes() <= this->getMaxLong()) {
			return true;
		} else {
			return false;
		}
	}
	return true;
}
