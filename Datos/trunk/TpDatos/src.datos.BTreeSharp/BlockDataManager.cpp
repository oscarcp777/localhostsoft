/*
 * BlockDataManager.cpp
 *
 *  Created on: 30/09/2010
 *      Author: oscar
 */

#include "BlockDataManager.h"
#include "../src.datos.models/KeyInteger.h"

BlockDataManager::BlockDataManager() {
	// TODO Auto-generated constructor stub

}

BlockDataManager::~BlockDataManager() {
	// TODO Auto-generated destructor stub
}
Registry* BlockDataManager::insertIucInBlockData(RegClassification* registryNew,RegClassification* registryFind,ContainerInsertDataBlock* container){
	Block* blockIucs;
	unsigned int numBlock=0;
	if(registryFind!=NULL){
		numBlock=registryFind->getNumBlock();
		blockIucs=this->readBlockData(numBlock,container);
			while(blockIucs->getNextBlock()!=-1){
				numBlock=blockIucs->getNextBlock();
				blockIucs=this->readBlockData(blockIucs->getNextBlock(),container);

			}

		if(blockIucs->posibleToAgregateComponent(registryNew->getIuc())){
			blockIucs->addReg(registryNew->getIuc());

			this->writeBlockData(blockIucs,numBlock,container);
			registryNew->clearListIuc();
			delete registryNew;
			return NULL;
		}else{
			registryNew= (RegClassification*)this->insertIucBlockNew(registryNew,container);
			blockIucs->setNextBlock(registryNew->getNumBlock());
			this->writeBlockData(blockIucs,numBlock,container);
			registryNew->clearListIuc();
			delete registryNew;
			return NULL;
		}
	}else{
		return this->insertIucBlockNew(registryNew,container);
	}
	return NULL;
}
void  BlockDataManager::loadListRegistry(list<KeyInteger*> &listRegistry, list<Registry*>::iterator itBegin,list<Registry*>::iterator itEnd){
	while (itBegin != itEnd) {
		listRegistry.push_back((KeyInteger*)*itBegin);
		itBegin++;
	}
}

void BlockDataManager::loadListIucBlockData(RegClassification* regClas,unsigned  int numBlock,ContainerInsertDataBlock* container){
	list<KeyInteger*> listIucs;
	Block* blockIucs;
	blockIucs=this->readBlockData(numBlock,container);
	loadListRegistry(listIucs,blockIucs->iteratorBegin(),blockIucs->iteratorEnd());
	blockIucs->clearListRegistry();
	delete blockIucs;
		while(blockIucs->getNextBlock()!=-1){
			Block* block=this->readBlockData(blockIucs->getNextBlock(),container);
			loadListRegistry(listIucs,blockIucs->iteratorBegin(),blockIucs->iteratorEnd());
			block->clearListRegistry();
			delete block;
		}

	regClas->setListIuc(listIucs);

}
Registry* BlockDataManager::insertMailInBlockData(RegPrimary* registryNew,RegPrimary* registryFind,ContainerInsertDataBlock* container){

	if(registryFind!=NULL){
		Block* blockMails=this->readBlockData(registryFind->getNumberBlock(),container);
		if(blockMails->posibleToAgregateComponent(registryNew->getMail())){
			blockMails->addReg(registryNew->getMail());
			this->writeBlockData(blockMails,registryFind->getNumberBlock(),container);
			delete registryNew;
			return NULL;
		}
		else{
			return this->insertMailBlockNew(registryNew,container);
		}
	}else{
		return this->insertMailBlockNew(registryNew,container);
	}
	return NULL;
}
Registry* BlockDataManager::insertIucBlockNew(RegClassification* registry,ContainerInsertDataBlock* container){
	unsigned int numblock=container->getFreeBlockController()->searchFreeBlock();
	Block* blockIucNew= new Block(container->getSizeBlockData(),container->getTypeElementData(),container->getIndexed());
	blockIucNew->addReg(((RegClassification*)registry)->getIuc());
	((RegClassification*)registry)->setNumBlock(numblock);
	this->writeBlockData(blockIucNew,numblock,container);
	registry->clearListIuc();
	return registry;
}
Registry* BlockDataManager::insertMailBlockNew(RegPrimary* registry,ContainerInsertDataBlock* container){
	unsigned int numblock=container->getFreeBlockController()->searchFreeBlock();
	Block* blockMailsNew= new Block(container->getSizeBlockData(),container->getTypeElementData(),container->getIndexed());
	blockMailsNew->addReg(((RegPrimary*)registry)->getMail());
	((RegPrimary*)registry)->setNumberBlock(numblock);
	this->writeBlockData(blockMailsNew,numblock,container);
	((RegPrimary*)registry)->setMail(NULL);
	return registry;
}
Block* BlockDataManager::readBlockData(unsigned int numBlock,ContainerInsertDataBlock* container){
	Buffer* buffer= new Buffer(container->getSizeBlockData());
	container->getBinaryFile()->read(buffer->getData(),container->getSizeBlockData(),container->getSizeBlockData()*numBlock);
	Block* block = new Block(container->getSizeBlockData(),container->getTypeElementData(),container->getIndexed());
	block->unPack(buffer);
	delete buffer;
	return block;
}
void BlockDataManager::writeBlockData(Block* block ,unsigned int numBlock,ContainerInsertDataBlock* container){
	Buffer* buffer= new Buffer(container->getSizeBlockData());
	block->pack(buffer);
	container->getBinaryFile()->write(buffer->getData(),container->getSizeBlockData(),container->getSizeBlockData()*numBlock);
	delete block;
	delete buffer;
}
