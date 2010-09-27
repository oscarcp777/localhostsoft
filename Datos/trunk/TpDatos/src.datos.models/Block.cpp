/*
 * Block.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Block.h"
#include "FactoryOfRegistry.h"
bool comparator( Registry* reg1, Registry* reg2) {
	int compare= reg1->compareTo(reg2);
	return (compare< 0);

}
Block::Block(unsigned int maxLong, unsigned int numBlock, unsigned int level) throw(){
	this->freeSize=BLOCK_SIZE;
	this->maxLong=maxLong;
	this->numBlock=numBlock;
	this->level= level;
	this->factory= new FactoryOfRegistry();
}
Block::Block(unsigned int sizeBlock,int typeElement,bool indexed){
	this->maxLong=sizeBlock;
	this->indexed=indexed;
	this->typeElement=typeElement;
	this->factory= new FactoryOfRegistry();
}
Block::Block(){
	this->factory= new FactoryOfRegistry();
}
void Block::sortListRegistry(){
     this->regList.sort(comparator);
}
void Block::replaceRegistry(Registry* registryOld,Registry* registryNew) throw(){
	std::replace(this->regList.begin(),this->regList.end(),registryOld,registryNew);
}

void Block::clearListRegistry() throw(){
   this->regList.clear();
}

Block::~Block() throw(){
	list<Registry*>::iterator iterRegistry;
	Registry* reg;
	for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		reg=*iterRegistry;
		delete reg;
	}
	if(this->factory!=NULL)
	 delete this->factory;
}
unsigned int Block::getSize(){
	return this->maxLong;
}
unsigned int Block::getSizeRegistry(){
	unsigned int sizeBusy=0;
	list<Registry*>::iterator iterRegistry;
	Registry* reg;
	for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		reg=*iterRegistry;
		sizeBusy+=reg->getSize();
	}
	return sizeBusy;
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
	int size=this->regList.size();
	return size;
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
	this->unPackListRegistry(buffer,numberElements,this->typeElement);

}
void Block::unPackListRegistry(Buffer* buffer,int numberElements,int typeElement){
	list<Registry*>::iterator iterRegistry;
	Registry* reg;
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
	if(this->indexed)
	buffer->packField(&this->nextNode, sizeof(this->nextNode));
}
int Block::unPackMetadata(Buffer* buffer){
	int numberElements;
	buffer->unPackField(&numberElements,sizeof(numberElements));
	if(this->indexed)
	buffer->unPackField(&this->nextNode,sizeof(this->nextNode));
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

	if (this->posibleToAgregateComponent(registry)){
		this->addReg(registry);
	}
}

void Block::addComponent(Registry* registry,list<Registry*>::iterator it,int pos) throw() {
	if (this->posibleToAgregateComponent(registry)) {
		for (int var = 0; var <pos; var++) {
			it++;
		}
		this->regList.insert(it,registry);
	}
}
unsigned int Block::getOcupedLong() throw() {
	unsigned int sizeBusy=Block::getSizeRegistry();
	sizeBusy += sizeof(unsigned int);
	return sizeBusy;
}

unsigned int Block::getLongBytes() throw(){
	return maxLong;

}

unsigned int Block::getMaxLong() const throw(){
	return maxLong;
}

void Block::setMaxLong(unsigned int maxLong) throw(){
	this->maxLong = maxLong;
}

bool Block::posibleToAgregateComponent(Registry* registry) throw(){

	return (this->getOcupedLong() + registry->getLongBytes() <= this->getMaxLong());

}

unsigned int Block::getAverageWeight() const
{
    return averageWeight;
}

void Block::setAverageWeight(unsigned int averageWeight)
{
    this->averageWeight = averageWeight;
}
int Block::getTypeElement(){
      return typeElement;
 }

void Block::setTypeElement(int typeElement){
      this->typeElement = typeElement;
  }
void Block::setNextBlock(int numBlock){
	this->nextNode = numBlock;
}
int Block::getNextBlock() const{
	return this->nextNode;
}

bool Block::getIndexed() const
{
    return indexed;
}

void Block::setIndexed(bool indexed)
{
    this->indexed = indexed;
}
int Block::getTipeKey(int typeElement){
    if(TYPE_REG_PRIMARY==typeElement)
    	return TYPE_KEY_INTEGER;
    if(TYPE_REG_CLASSIFICATION==typeElement)
        	return TYPE_KEY_STRING;
    return typeElement;
}

