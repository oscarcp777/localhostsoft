/*
 * BlockDataManager.cpp
 *
 *  Created on: 30/09/2010
 *      Author: oscar
 */

#include "BlockDataManager.h"
#include "../src.datos.models/KeyInteger.h"
#include "../src.datos.storage/BitArrayBufferCompression.h"

BlockDataManager::BlockDataManager() {
	// TODO Auto-generated constructor stub

}

BlockDataManager::~BlockDataManager() {
	// TODO Auto-generated destructor stub
}
Registry* BlockDataManager::insertInfoPerDoc(RegInvertedIndex* registryNew,RegInvertedIndex* registryFind,ContainerInsertDataBlock* container){
	CompressedBlock* blockInfoPerDoc;
	unsigned int numBlock=0;
	if(registryFind!=NULL){
		numBlock=registryFind->getNumBlock();
		blockInfoPerDoc=this->readDataBlockCompressed(numBlock,container);
			while(blockInfoPerDoc->getNextBlock()!=NEXT_BLOCK_INVALID){
				numBlock=blockInfoPerDoc->getNextBlock();
				delete blockInfoPerDoc;
				blockInfoPerDoc=this->readDataBlockCompressed(numBlock,container);

			}

		if(blockInfoPerDoc->posibleToAgregateRegCompressed(registryNew->getInfoPerDoc())){
			blockInfoPerDoc->addReg(registryNew->getInfoPerDoc());

			this->writeDataBlockCompressed(blockInfoPerDoc,numBlock,container);
			registryNew->clearInfoPerDoc();
			delete registryNew;
			return NULL;
		}else{
			registryNew= (RegInvertedIndex*)this->insertInvertedIndexBlockNew(registryNew,container);
			blockInfoPerDoc->setNextBlock(registryNew->getNumBlock());
			this->writeDataBlockCompressed(blockInfoPerDoc,numBlock,container);
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
			while(blockIucs->getNextBlock()!=NEXT_BLOCK_INVALID){
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
	CompressedBlock* blockInfoPerDoc;
	int newNumBlock=0;
	regIndex->setNumBlock(numBlock);
	blockInfoPerDoc=this->readDataBlockCompressed(numBlock,container);
	loadListInfoPerDoc(listInfoPerDoc,blockInfoPerDoc->iteratorBegin(),blockInfoPerDoc->iteratorEnd());
	blockInfoPerDoc->clearListRegistry();
	newNumBlock=blockInfoPerDoc->getNextBlock();
		while(newNumBlock!=NEXT_BLOCK_INVALID){
			delete blockInfoPerDoc;
			blockInfoPerDoc=this->readDataBlockCompressed(newNumBlock,container);
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
		while(newNumBlock!=NEXT_BLOCK_INVALID){
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
		//cout<<mail->getSize()<<endl;
		//cout<<messsage.size()<<endl;
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
	CompressedBlock* blockIucNew= new CompressedBlock(container->getSizeBlockData(),container->getTypeElementData(),container->getIndexed());
	blockIucNew->addReg(((RegInvertedIndex*)registry)->getInfoPerDoc());
	((RegInvertedIndex*)registry)->setNumBlock(numblock);
	this->writeDataBlockCompressed(blockIucNew,numblock,container);
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
CompressedBlock* BlockDataManager::readDataBlockCompressed(unsigned int numBlock,ContainerInsertDataBlock* container){
	BitArrayBufferCompression* buffer= new BitArrayBufferCompression(container->getSizeBlockData());
	container->getBinaryFile()->read(buffer->getData(),container->getSizeBlockData(),container->getSizeBlockData()*numBlock);
	CompressedBlock* block = new CompressedBlock(container->getSizeBlockData(),container->getTypeElementData(),container->getIndexed());
	block->unPackCompressed(buffer);
	delete buffer;
	return block;
}
void BlockDataManager::writeDataBlockCompressed(CompressedBlock* block ,unsigned int numBlock,ContainerInsertDataBlock* container){
	BitArrayBufferCompression* buffer= new BitArrayBufferCompression(container->getSizeBlockData());
	block->packCompressed(buffer);
	container->getBinaryFile()->write(buffer->getData(),container->getSizeBlockData(),container->getSizeBlockData()*numBlock);
	delete block;
	block=NULL;
}
Block* BlockDataManager::readBlockData(unsigned int numBlock,ContainerInsertDataBlock* container){
	BitArrayBufferCompression* buffer= new BitArrayBufferCompression(container->getSizeBlockData());
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


void BlockDataManager::deleteBlockIndexed(int numberBlock,ContainerInsertDataBlock* container){
	Block* blockIucs;
	int newNumBlock=0;
	if(container->getTypeElement()==TYPE_REG_CLASSIFICATION)
		blockIucs=this->readBlockData(numberBlock,container);
	if(container->getTypeElement()==TYPE_REG_INVERTED_INDEX)
		blockIucs=this->readDataBlockCompressed(numberBlock,container);
	container->getFreeBlockController()->writeFreeBlock(numberBlock);
	newNumBlock=blockIucs->getNextBlock();
	while(newNumBlock!=NEXT_BLOCK_INVALID){
		delete blockIucs;
		if(container->getTypeElement()==TYPE_REG_CLASSIFICATION)
			blockIucs=this->readBlockData(newNumBlock,container);
		if(container->getTypeElement()==TYPE_REG_INVERTED_INDEX)
			blockIucs=this->readDataBlockCompressed(newNumBlock,container);
		container->getFreeBlockController()->writeFreeBlock(numberBlock);
		newNumBlock=blockIucs->getNextBlock();
	}
	delete blockIucs;
}
void BlockDataManager::deleteMailInBlockData(int numberBlock ,RegPrimary* registry,ContainerInsertDataBlock* container){

		Block* blockMails=this->readBlockData(numberBlock,container);
		Registry* reg=NULL;
		for(list<Registry*>::iterator iterRegistry = blockMails->iteratorBegin(); iterRegistry != blockMails->iteratorEnd(); iterRegistry++){
		     reg=*iterRegistry;
			if(registry->equals(reg)){
              break;
			}
		}
		if(reg!=NULL)
		blockMails->removeReg(reg);
		else
			cout<<"no se pudo remover no existe el mail en el bloque"<<endl;
		this->writeBlockData(blockMails,numberBlock,container);
}
