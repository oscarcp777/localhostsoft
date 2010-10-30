/*
 * LeafNode.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "LeafNode.h"

LeafNode::LeafNode(int typeElement,unsigned int maxLong, unsigned int numBlock, unsigned int level) throw():Node(maxLong,numBlock,level){
    this->nextNode=NEXT_BLOCK_INVALID;
   this->typeElement=typeElement;
   this->setMaxLong(maxLong);
   this->setNumBlock(numBlock);
   this->setLevel(level);
   this->blockDataManager= new BlockDataManager();
}
LeafNode::LeafNode(int typeElement,unsigned int maxLong){
	this->nextNode=NEXT_BLOCK_INVALID;
	this->typeElement=typeElement;
	this->setMaxLong(maxLong);
	this->blockDataManager= new BlockDataManager();
}
LeafNode::~LeafNode()throw() {
  delete this->blockDataManager;
}

unsigned int LeafNode::getOcupedLong() throw(){
	unsigned int sizeBusy=Block::getSizeRegistry();
	sizeBusy += this->getMetadata();
	return sizeBusy;
}
unsigned int LeafNode::getMetadata(){
     return sizeof(unsigned int)*4;
}
void LeafNode::deleteBlockData(Registry* registry,ContainerInsertDataBlock* container){

	if(container->getTypeElement()==TYPE_REG_PRIMARY){
		deleteBlockMails( registry, container);
	}
	if(container->getTypeElement()==TYPE_REG_CLASSIFICATION){
//		deleteBlockRegClassification( registry, container);
	}
	if(container->getTypeElement()==TYPE_REG_INVERTED_INDEX){
//		deleteBlockRegInvertedIndex( registry, container);
	}

}
Registry* LeafNode::insertBlockData(Registry* registry,ContainerInsertDataBlock* container){

	if(container->getTypeElement()==TYPE_REG_PRIMARY){
		registry=insertBlockMails( registry, container);
	}
	if(container->getTypeElement()==TYPE_REG_CLASSIFICATION){
		registry=insertBlockRegClassification( registry, container);
	}
	if(container->getTypeElement()==TYPE_REG_INVERTED_INDEX){
		registry=insertBlockRegInvertedIndex( registry, container);
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
	if(container->getTypeElement()==TYPE_REG_INVERTED_INDEX){
			registry=searchBlockRegInvertedIndex( registry, container);
		}
	return registry;
}


void LeafNode::deleteBlockMails(Registry* registry,ContainerInsertDataBlock* container){
	int numberBlock=this->searchNumberBlockMail((RegPrimary*)registry);
	if(numberBlock==NEXT_BLOCK_INVALID)
	return ;
    this->blockDataManager->deleteMailInBlockData(numberBlock,(RegPrimary*)registry,container);
}
void LeafNode::deleteBlockDataIndexed(Registry* registry,ContainerInsertDataBlock* container){
	int numberBlock=this->searchNumberBlockMail((RegPrimary*)registry);
	if(numberBlock==NEXT_BLOCK_INVALID)
	return ;
    this->blockDataManager->deleteBlockIndexed(numberBlock,container);
}



Registry* LeafNode::insertBlockMails(Registry* registry,ContainerInsertDataBlock* container){
	list<Registry*>::iterator iterRegistry;
	Registry* reg=NULL;
	for ( iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		reg=*iterRegistry;
		if(registry->compareTo(reg)<0){
			//si entro es menor al actual entonces retrocedo un reg que es donde debo insertar
			iterRegistry--;
			reg=*iterRegistry;
			break;
		}
	}
	return this->blockDataManager->insertMailInBlockData((RegPrimary*)registry,(RegPrimary*)reg,container);

}
Registry* LeafNode::insertBlockRegInvertedIndex(Registry* registry,ContainerInsertDataBlock* container){
	list<Registry*>::iterator iterRegistry;
	Registry* registryFind=NULL;
	for ( iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		registryFind=*iterRegistry;
		if(registry->equals(registryFind))
			break;
		else
			registryFind=NULL;
	}

return this->blockDataManager->insertInfoPerDoc((RegInvertedIndex*)registry,(RegInvertedIndex*)registryFind,container);
}
Registry* LeafNode::insertBlockRegClassification(Registry* registry,ContainerInsertDataBlock* container){
	list<Registry*>::iterator iterRegistry;
	Registry* registryFind=NULL;
	for ( iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		registryFind=*iterRegistry;
		if(registry->equals(registryFind))
			break;
		else
			registryFind=NULL;
	}

return this->blockDataManager->insertIucInBlockData((RegClassification*)registry,(RegClassification*)registryFind,container);
}
Registry* LeafNode::searchBlockRegClassification(Registry* registry,ContainerInsertDataBlock* container){
		int numberBlock=this->searchNumberBlock(registry,container);
		if(numberBlock==NEXT_BLOCK_INVALID)
		return NULL;
		this->blockDataManager->loadListIucBlockData((RegClassification*)registry,numberBlock,container);
		return registry;
}
Registry* LeafNode::searchBlockRegInvertedIndex(Registry* registry,ContainerInsertDataBlock* container){
	int numberBlock=this->searchNumberBlock(registry,container);
	if(numberBlock==NEXT_BLOCK_INVALID)
		return NULL;
	this->blockDataManager->loadListInfoPerDocBlockData((RegInvertedIndex*)registry,numberBlock,container);
	return registry;

}
void LeafNode::printMails(std::ostream& outStream,Registry* reg, ContainerInsertDataBlock* container){
	list<Registry*>::iterator iterRegistry;
		Block* blockMails;
		RegPrimary* regPrevious=(RegPrimary*)reg;
		blockMails=this->blockDataManager->readBlockData(regPrevious->getNumberBlock(),container);
		for(iterRegistry = blockMails->iteratorBegin(); iterRegistry != blockMails->iteratorEnd(); iterRegistry++){
			reg=*iterRegistry;
			((RegPrimary*)reg)->print(std::cout);

		}

}
int LeafNode::searchNumberBlock(Registry* registry,ContainerInsertDataBlock* container){
	list<Registry*>::iterator iterRegistry;
	for ( iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		Registry* reg=*iterRegistry;
		if(registry->equals(reg)){
			if(container->getTypeElement()==TYPE_REG_CLASSIFICATION){
				RegClassification* regClas=(RegClassification*)*iterRegistry;
				return regClas->getNumBlock();
			}
			if(container->getTypeElement()==TYPE_REG_INVERTED_INDEX){
				RegInvertedIndex* regInvert=(RegInvertedIndex*)*iterRegistry;
				return regInvert->getNumBlock();
			}
		}
	}
	return -1;
}
int LeafNode::searchNumberBlockMail(Registry* registry){
        if(this->regList.size()==1)
           return ((RegPrimary*)*this->regList.begin())->getNumberBlock();

		for (list<Registry*>::iterator iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
			RegPrimary*  reg=(RegPrimary*)*iterRegistry;
			if(registry->compareTo(reg)<0){
				//si entro es menor al actual entonces retrocedo un reg que es donde debo insertar
				iterRegistry--;
				reg=(RegPrimary*)*iterRegistry;
				return reg->getNumberBlock();
			}
		}
		return -1;
}
Registry* LeafNode::searchBlockMails(Registry* registry,ContainerInsertDataBlock* container){
	Block* blockMails;
	list<Registry*>::iterator iterRegistry;
	int numberBlock=this->searchNumberBlockMail((RegPrimary*)registry);
	if(numberBlock==NEXT_BLOCK_INVALID)
	return NULL;
	blockMails=this->blockDataManager->readBlockData(numberBlock,container);
	((RegPrimary*)registry)->setNumberBlock(numberBlock);
	for(iterRegistry = blockMails->iteratorBegin(); iterRegistry != blockMails->iteratorEnd(); iterRegistry++){
		Registry* reg=*iterRegistry;
		if(registry->compareTo(reg) == 0){
			((RegPrimary*)registry)->setMail((Mail*)reg->clone());
			delete blockMails;
			return registry;
		}
	}
	delete blockMails;
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



