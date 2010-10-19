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
Registry* BlockDataManager::insertInfoPerDoc(RegInvertedIndex* registryNew,RegInvertedIndex* registryFind,ContainerInsertDataBlock* container){
	Block* blockIucs;
	unsigned int numBlock=0;
	if(registryFind!=NULL){
		numBlock=registryFind->getNumBlock();
		blockIucs=this->readBlockData(numBlock,container);
			while(blockIucs->getNextBlock()!=-1){
				numBlock=blockIucs->getNextBlock();
				delete blockIucs;
				blockIucs=this->readBlockData(numBlock,container);

			}

		if(blockIucs->posibleToAgregateComponent(registryNew->getInfoPerDoc())){
			blockIucs->addReg(registryNew->getInfoPerDoc());

			this->writeBlockData(blockIucs,numBlock,container);
			registryNew->clearInfoPerDoc();
			delete registryNew;
			return NULL;
		}else{
			registryNew= (RegInvertedIndex*)this->insertInvertedIndexBlockNew(registryNew,container);
			blockIucs->setNextBlock(registryNew->getNumBlock());
			this->writeBlockData(blockIucs,numBlock,container);
			registryNew->clearInfoPerDoc();
			delete registryNew;
			return NULL;
		}
	}else{
		return this->insertInvertedIndexBlockNew(registryNew,container);
	}

	return NULL;
}
Registry* BlockDataManager::insertIucInBlockData(RegClassification* registryNew,RegClassification* registryFind,ContainerInsertDataBlock* container){
	Block* blockIucs;
	unsigned int numBlock=0;
	if(registryFind!=NULL){
		numBlock=registryFind->getNumBlock();
		blockIucs=this->readBlockData(numBlock,container);
			while(blockIucs->getNextBlock()!=-1){
				numBlock=blockIucs->getNextBlock();
				delete blockIucs;
				blockIucs=this->readBlockData(numBlock,container);

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
void  BlockDataManager::loadListInfoPerDoc(list<InfoPerDoc*> &listRegistry, list<Registry*>::iterator itBegin,list<Registry*>::iterator itEnd){
	while (itBegin != itEnd) {
		listRegistry.push_back((InfoPerDoc*)*itBegin);
		itBegin++;
	}
}
void BlockDataManager::loadListInfoPerDocBlockData(RegInvertedIndex* regIndex,unsigned  int numBlock,ContainerInsertDataBlock* container){
	list<InfoPerDoc*> listInfoPerDoc;
	Block* blockInfoPerDoc;
	int newNumBlock=0;
	blockInfoPerDoc=this->readBlockData(numBlock,container);
	loadListInfoPerDoc(listInfoPerDoc,blockInfoPerDoc->iteratorBegin(),blockInfoPerDoc->iteratorEnd());
	blockInfoPerDoc->clearListRegistry();
	newNumBlock=blockInfoPerDoc->getNextBlock();
		while(newNumBlock!=-1){
			delete blockInfoPerDoc;
			blockInfoPerDoc=this->readBlockData(newNumBlock,container);
			loadListInfoPerDoc(listInfoPerDoc,blockInfoPerDoc->iteratorBegin(),blockInfoPerDoc->iteratorEnd());
			blockInfoPerDoc->clearListRegistry();
			newNumBlock=blockInfoPerDoc->getNextBlock();
		}

	regIndex->setListInfoPerDoc(listInfoPerDoc);
	blockInfoPerDoc->clearListRegistry();
	delete blockInfoPerDoc;

}
void BlockDataManager::loadListIucBlockData(RegClassification* regClas,unsigned  int numBlock,ContainerInsertDataBlock* container){
	list<KeyInteger*> listIucs;
	Block* blockIucs;
	int newNumBlock=0;
	blockIucs=this->readBlockData(numBlock,container);
	loadListRegistry(listIucs,blockIucs->iteratorBegin(),blockIucs->iteratorEnd());
	blockIucs->clearListRegistry();
	newNumBlock=blockIucs->getNextBlock();
		while(newNumBlock!=-1){
			delete blockIucs;
			blockIucs=this->readBlockData(newNumBlock,container);
			loadListRegistry(listIucs,blockIucs->iteratorBegin(),blockIucs->iteratorEnd());
			blockIucs->clearListRegistry();
			newNumBlock=blockIucs->getNextBlock();
		}

	regClas->setListIuc(listIucs);
	blockIucs->clearListRegistry();
	delete blockIucs;

}
Mail* BlockDataManager::validedSizeMail(Mail* mail,ContainerInsertDataBlock* container){

	if(mail->getSize()>container->getSizeBlockData()){
		string messsage=mail->getMessage();
		cout<<mail->getSize()<<endl;
		cout<<messsage.size()<<endl;
		unsigned int sizeMaxMessage =container->getSizeBlockData()-((mail->getSize()-messsage.size())+sizeof(unsigned int));
		messsage=messsage.substr(0,sizeMaxMessage);
		mail->setMessage(messsage);
	}
	return mail;

}
Registry* BlockDataManager::insertMailInBlockData(RegPrimary* registryNew,RegPrimary* registryFind,ContainerInsertDataBlock* container){

	registryNew->setMail(validedSizeMail(registryNew->getMail(),container));
	registryNew->getMail();
	if(registryFind!=NULL){
		Block* blockMails=this->readBlockData(registryFind->getNumberBlock(),container);
		if(blockMails->posibleToAgregateComponent(registryNew->getMail())){
			blockMails->addReg(registryNew->getMail());
			this->writeBlockData(blockMails,registryFind->getNumberBlock(),container);
			delete registryNew;
			return NULL;
		}
		else{
			delete blockMails;
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
Registry* BlockDataManager::insertInvertedIndexBlockNew(RegInvertedIndex* registry,ContainerInsertDataBlock* container){
	unsigned int numblock=container->getFreeBlockController()->searchFreeBlock();
	Block* blockIucNew= new Block(container->getSizeBlockData(),container->getTypeElementData(),container->getIndexed());
	blockIucNew->addReg(((RegInvertedIndex*)registry)->getInfoPerDoc());
	((RegInvertedIndex*)registry)->setNumBlock(numblock);
	this->writeBlockData(blockIucNew,numblock,container);
	registry->clearInfoPerDoc();
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
	block=NULL;
	delete buffer;
}
