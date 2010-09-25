/*
 * FreeBlockList.cpp
 *
 *  Created on: 24/04/2010
 *      Author: Santiago
 */

#include "FreeBlockController.h"


FreeBlockController::~FreeBlockController()throw(){
	this->binaryFile->close();
	delete this->binaryFile;
}
FreeBlockController::FreeBlockController(string nameFile,unsigned int counterBlock) throw() {
	this->binaryFile = new BinaryFile();
	if(!this->binaryFile->isCreated(nameFile)){
		this->binaryFile->create(nameFile);
	}else{
		this->binaryFile->open(nameFile);
	}
	this->counterBlock=counterBlock;
}


void FreeBlockController::writeFreeBlock(unsigned int numBlock) throw() {
	this->vectorFreeBlock.push_back(numBlock);
	this->binaryFile->write((char*)&numBlock,sizeof(numBlock),-1);
}

unsigned int FreeBlockController::searchFreeBlock() throw() {
	if(this->vectorFreeBlock.size()!=0)
	return this->vectorFreeBlock.back();
	else{
		unsigned int nextBlock=++counterBlock;
		return nextBlock;
	}

}

unsigned int FreeBlockController::getCounterBlock() const
{
    return counterBlock;
}

void FreeBlockController::setCounterBlock(unsigned int counterBlock)
{
    this->counterBlock = counterBlock;
}


