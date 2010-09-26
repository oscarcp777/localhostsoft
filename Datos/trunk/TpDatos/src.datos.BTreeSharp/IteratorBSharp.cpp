/*
 * IteratorBSharp.cpp
 *
 *  Created on: 25/09/2010
 *      Author: San
 */

#include "IteratorBSharp.h"

IteratorBSharp::IteratorBSharp(unsigned int firstNode, int typeElement, BinaryFile* binaryFile, int sizeBlock, ContainerInsertDataBlock* containerInsertDataBlock) {
	this->sizeBlock = sizeBlock;
	this->binaryFile = binaryFile;
	this->typeElement = typeElement;
	this->firstIteration = true;
	this->containerInsertDataBlock = containerInsertDataBlock;
	this->dataBlock = NULL;

	// Leo el primer nodo hoja
	this->currentNode = this->readNode(firstNode);
	// Me paro en la primer clave del nodo
	this->currentRegistry = this->currentNode->iteratorBegin();

	// Si es registro primario leo su bloque de datos y obtengo el primer dato
	if (this->typeElement == TYPE_REG_PRIMARY){
		// Si el nodo no esta vacio
		if (this->currentRegistry != this->currentNode->iteratorEnd()){
			RegPrimary* reg=(RegPrimary*)*this->currentRegistry;
			this->dataBlock = this->readBlockData(reg->getNumberBlock());
			this->currentDataRegistry = this->dataBlock->iteratorBegin();
		}
	}


}

IteratorBSharp::~IteratorBSharp() {
	delete this->currentNode;
	if (this->dataBlock != NULL)
		delete this->dataBlock;
}

bool IteratorBSharp::hasNext() throw(){

	list<Registry*>::iterator endComp = this->currentNode->iteratorEnd();
	list<Registry*>::iterator aux = this->currentRegistry;


	if (firstIteration == true){
		if(this->currentRegistry != this->currentNode->iteratorEnd())
			return true;
		else
			return false;
	}

	if (this->typeElement == TYPE_REG_PRIMARY){
		list<Registry*>::iterator endData = this->dataBlock->iteratorEnd();
		list<Registry*>::iterator itData = this->currentDataRegistry;
		itData++;
		if (itData != endData)
			return true;
	}
	aux++;
	if (aux != endComp) {
		return true;
	}else if (this->currentNode->getNextBlock() != -1){
		return true;
	}

	return false;
}

Registry* IteratorBSharp::next() throw(){

	// Si es la primer iteracion no incremento nada devuelvo el registro actual
	if (firstIteration == true){
		firstIteration = false;
		// Si es registro primario le seteo el valor
		if (this->typeElement == TYPE_REG_PRIMARY){
			RegPrimary* reg=(RegPrimary*)*this->currentRegistry;
			reg->setMail((Mail*)*this->currentDataRegistry);
		}
		//(*this->currentRegistry)->print(std::cout);
		return (*this->currentRegistry);
	}


	// Busco el siguiente registro
	// Si es registro primario primero intento incrementar en el archivo de datos
	if (this->typeElement == TYPE_REG_PRIMARY){
		list<Registry*>::iterator endData = this->dataBlock->iteratorEnd();
		if (++this->currentDataRegistry != endData){
			RegPrimary* reg=(RegPrimary*)*this->currentRegistry;
			reg->setMail((Mail*)*this->currentDataRegistry);
			//(*this->currentRegistry)->print(std::cout);
			return (*this->currentRegistry);
		}
	}

	list<Registry*>::iterator endComp = this->currentNode->iteratorEnd();
	if (++this->currentRegistry == endComp){
		delete this->currentNode;
		this->currentNode = this->readNode(this->currentNode->getNextBlock());
		this->currentRegistry = this->currentNode->iteratorBegin();
	}

	if (this->typeElement == TYPE_REG_PRIMARY){
		RegPrimary* reg=(RegPrimary*)*this->currentRegistry;
		delete this->dataBlock;
		this->dataBlock = this->readBlockData(reg->getNumberBlock());
		this->currentDataRegistry = this->dataBlock->iteratorBegin();
		reg->setMail((Mail*)*this->currentDataRegistry);
	}

	//(*this->currentRegistry)->print(std::cout);
	return (*this->currentRegistry);

}





LeafNode* IteratorBSharp::readNode(unsigned int numBlock) throw() {
	Buffer* buffer;
	int tam;
	LeafNode* node = NULL;
	if (numBlock == 0)
		tam = 2*this->sizeBlock;
	else
		tam = this->sizeBlock;
	buffer = new Buffer(tam);
	if(this->binaryFile->read(buffer->getData(),buffer->getMaxBytes(),this->sizeBlock*numBlock)){
		node = readNodeBytes(buffer,tam);
	}
	delete buffer;
	return node;
}

LeafNode* IteratorBSharp::readNodeBytes(Buffer* buffer, int sizeBlock) throw(){
	unsigned int levelNode;
	if (buffer->getData() != NULL) {
		buffer->unPackField(&levelNode, sizeof(levelNode));
		buffer->init();
		return readLeafNodeBytes(buffer, sizeBlock);
	}

}

LeafNode* IteratorBSharp::readLeafNodeBytes(Buffer* buffer, int sizeBlock) throw(){
	LeafNode* leafNode= new LeafNode(this->typeElement,sizeBlock);
	leafNode->unPack(buffer);
	return leafNode;
}


Block* IteratorBSharp::readBlockData(unsigned int numBlock) throw(){
	Buffer* buffer= new Buffer(this->containerInsertDataBlock->getSizeBlockData());
	this->containerInsertDataBlock->getBinaryFile()->read(buffer->getData(),this->containerInsertDataBlock->getSizeBlockData(),this->containerInsertDataBlock->getSizeBlockData()*numBlock);
	Block* block = new Block(this->containerInsertDataBlock->getSizeBlockData(),this->containerInsertDataBlock->getTypeElementData(),this->containerInsertDataBlock->getIndexed());
	block->unPack(buffer);
	delete buffer;
	return block;
}


