/*
 * LeafNode.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "LeafNode.h"

LeafNode::LeafNode(int typeElement,unsigned int maxLong, unsigned int numBlock, unsigned int level) throw():Node(maxLong,numBlock,level){
    this->nextNode=-1;
   this->typeElement=typeElement;
   this->setMaxLong(maxLong);
   this->setNumBlock(numBlock);
   this->setLevel(level);
}
LeafNode::LeafNode(int typeElement,unsigned int maxLong){
	this->typeElement=typeElement;
	this->setMaxLong(maxLong);
}
LeafNode::~LeafNode()throw() {
	// TODO Auto-generated destructor stub
}

unsigned int LeafNode::getOcupedLong() throw(){
	unsigned int sizeBusy=Block::getSizeRegistry();
	sizeBusy += this->getMetadata();
	return sizeBusy;
}
unsigned int LeafNode::getMetadata(){
     return sizeof(unsigned int)*4;
}
Registry* LeafNode::insertBlockData(Registry* registry,ContainerInsertDataBlock* container){

	if(container->getTypeElement()==TYPE_REG_PRIMARY){
		registry=insertBlockMails( registry, container);
	}
	if(container->getTypeElement()==TYPE_REG_CLASSIFICATION){
		registry=insertBlockRegClassification( registry, container);
		}

return registry;
}
Registry* LeafNode::searchRegistryBlockData(Registry* registry,ContainerInsertDataBlock* container){
	if(container->getTypeElement()==TYPE_REG_PRIMARY){
		registry=searchBlockMails(registry, container);
	}
	if(container->getTypeElement()==TYPE_REG_CLASSIFICATION){
		registry=searchBlockRegClassification(registry, container);
	}

	return registry;
}
Block* LeafNode::readBlockData(unsigned int numBlock,ContainerInsertDataBlock* container){
       Buffer* buffer= new Buffer(container->getSizeBlockData());
       container->getBinaryFile()->read(buffer->getData(),container->getSizeBlockData(),container->getSizeBlockData()*numBlock);
       Block* block = new Block(container->getSizeBlockData(),container->getTypeElementData(),container->getIndexed());
       		block->unPack(buffer);
       		delete buffer;
       return block;
}
void LeafNode::writeBlockData(Block* block ,unsigned int numBlock,ContainerInsertDataBlock* container){
	 Buffer* buffer= new Buffer(container->getSizeBlockData());
	 block->pack(buffer);
     container->getBinaryFile()->write(buffer->getData(),container->getSizeBlockData(),container->getSizeBlockData()*numBlock);
     delete block;
     delete buffer;
}

Registry* LeafNode::insertMailBlockNew(Registry* registry,ContainerInsertDataBlock* container){
	unsigned int numblock=container->getFreeBlockController()->searchFreeBlock();
	Block* blockMailsNew= new Block(container->getSizeBlockData(),container->getTypeElementData(),container->getIndexed());
	blockMailsNew->addReg(((RegPrimary*)registry)->getMail());
	((RegPrimary*)registry)->setNumberBlock(numblock);
	this->writeBlockData(blockMailsNew,numblock,container);
	((RegPrimary*)registry)->setMail(NULL);
	return registry;
}

Registry* LeafNode::insertIucBlockNew(Registry* registry,ContainerInsertDataBlock* container){
	unsigned int numblock=container->getFreeBlockController()->searchFreeBlock();
	Block* blockIucNew= new Block(container->getSizeBlockData(),container->getTypeElementData(),container->getIndexed());
	blockIucNew->addReg(((RegClassification*)registry)->getIuc());
	((RegClassification*)registry)->setNumBlock(numblock);
	this->writeBlockData(blockIucNew,numblock,container);
	return registry;
}

Registry* LeafNode::insertBlockMails(Registry* registry,ContainerInsertDataBlock* container){
	list<Registry*>::iterator iterRegistry;
	Registry* reg=registry;
	Block* blockMails;
	if(this->regList.size()==0){
		return this->insertMailBlockNew(registry,container);
	}
	for ( iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		reg=*iterRegistry;
		if(registry->compareTo(reg)<0){
			//si entro es menor al actual entonces retrocedo un reg que es donde debo insertar
			iterRegistry--;
			reg=*iterRegistry;
			break;
		}
	}
	RegPrimary* regPrevious=(RegPrimary*)reg;
	blockMails=this->readBlockData(regPrevious->getNumberBlock(),container);

	if(blockMails->posibleToAgregateComponent(((RegPrimary*)registry)->getMail())){
		blockMails->addReg(((RegPrimary*)registry)->getMail());
		this->writeBlockData(blockMails,regPrevious->getNumberBlock(),container);
		delete registry;
		return NULL;
	}else{
		return this->insertMailBlockNew(registry,container);
	}
	return NULL;
}
Registry* LeafNode::insertBlockRegClassification(Registry* registry,ContainerInsertDataBlock* container){
	list<Registry*>::iterator iterRegistry;
	Registry* reg;
	Block* blockIucs;
	bool find = false;
	for ( iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		reg=*iterRegistry;
		if(registry->equals(reg)){
			find = true;
			break;
		}
	}
	if(find == true){
		RegClassification* regClass=(RegClassification*)reg;
		blockIucs=this->readBlockData(regClass->getNumBlock(),container);
		blockIucs->addReg(((RegClassification*)registry)->getIuc());
		this->writeBlockData(blockIucs,regClass->getNumBlock(),container);
		delete registry;
		return NULL;
	}else{
		return this->insertIucBlockNew(registry,container);
	}
	return NULL;


return registry;
}
Registry* LeafNode::searchBlockRegClassification(Registry* registry,ContainerInsertDataBlock* container){
//	list<Registry*>::iterator iterRegistry;
//	Registry* reg;
//	for ( iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
//		reg=*iterRegistry;
//		if(registry->equals(reg)){
//			break;
//		}
//	}
	//		RegClassification* regPrevious=(RegClassification*)reg;


	return NULL;//registry;
}
void LeafNode::printMails(std::ostream& outStream,Registry* reg, ContainerInsertDataBlock* container){
	list<Registry*>::iterator iterRegistry;
		Block* blockMails;
		RegPrimary* regPrevious=(RegPrimary*)reg;
		blockMails=this->readBlockData(regPrevious->getNumberBlock(),container);
		for(iterRegistry = blockMails->iteratorBegin(); iterRegistry != blockMails->iteratorEnd(); iterRegistry++){
			reg=*iterRegistry;
			((RegPrimary*)reg)->print(std::cout);

		}

}
Registry* LeafNode::searchBlockMails(Registry* registry,ContainerInsertDataBlock* container){
	list<Registry*>::iterator iterRegistry;
	Registry* reg=registry;
	Block* blockMails;
	if(this->regList.size()==0){
		return NULL;
	}
	for ( iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		reg=*iterRegistry;
		if(registry->compareTo(reg)<0){
			//si entro es menor al actual entonces retrocedo un reg que es donde debo insertar
			iterRegistry--;
			reg=*iterRegistry;
			break;
		}
	}
	RegPrimary* regPrevious=(RegPrimary*)reg;
	blockMails=this->readBlockData(regPrevious->getNumberBlock(),container);
	for(iterRegistry = blockMails->iteratorBegin(); iterRegistry != blockMails->iteratorEnd(); iterRegistry++){
		reg=*iterRegistry;
		if(registry->compareTo(reg) == 0){
			((RegPrimary*)registry)->setMail((Mail*)reg);
			return registry;
		}
	}

	return NULL;
}
bool LeafNode::isLeaf() const throw(){
	return true;
}
bool LeafNode::isUnderflow(unsigned int sizeMinumum)throw() {
    unsigned int percentUnderflow = sizeMinumum;
    percentUnderflow = (sizeMinumum-(0.5*this->getAverageWeight()))+getMetadata();
    return (this->getOcupedLong()< percentUnderflow);
}

bool LeafNode::posibleToAgregateComponent(Registry* registry) throw(){
   unsigned int ocupedLong=this->getOcupedLong();
   unsigned int longBytes=registry->getLongBytes();
	return (( ocupedLong+longBytes)  <= this->getMaxLong());

}

void LeafNode::pack(Buffer* buffer){
	this->packMetadata(buffer);
	this->packListRegistry(buffer);
}
void LeafNode::unPack(Buffer* buffer){
	int numElements = this->unPackMetadata(buffer);
	this->unPackListRegistry(buffer,numElements,this->typeElement);
}
void LeafNode::packMetadata(Buffer* buffer){
	int level = this->getLevel();
	buffer->packField(&level,sizeof(level));
	int numBlock = this->getNumBlock();
	buffer->packField(&numBlock,sizeof(numBlock));
	int nextNode = this->nextNode;
	buffer->packField(&nextNode,sizeof(nextNode));
	int numElements = this->getNumElements();
	buffer->packField(&numElements,sizeof(numElements));
}
int LeafNode::unPackMetadata(Buffer* buffer){
	int level;
	int numBlock;
	int nextNode;
	int numElements;
	buffer->unPackField(&level, sizeof(level));
	buffer->unPackField(&numBlock, sizeof(numBlock));
	buffer->unPackField(&nextNode, sizeof(nextNode));
	buffer->unPackField(&numElements, sizeof(numElements));
	this->setLevel(level);
	this->setNumBlock(numBlock);
	this->setNextBlock(nextNode);
	return numElements;
}



