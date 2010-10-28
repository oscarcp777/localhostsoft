/*
 * FreeBlockList.cpp
 *
 *  Created on: 24/04/2010
 *      Author: Santiago
 */

#include "FreeBlockController.h"
#include "Buffer.h"


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
		this->loadNumBlockFree();
	}
	this->counterBlock=counterBlock;
}
void FreeBlockController::loadNumBlockFree(){
	int numBlock=0,i=0;
	Buffer* buffer=new Buffer(this->binaryFile->sizeFile());
	this->binaryFile->read(buffer->getData(),buffer->getMaxBytes(),0);
	int cantNumBlocks=0;
	buffer->unPackField(&cantNumBlocks,sizeof(cantNumBlocks));
	while(i<cantNumBlocks){
		buffer->unPackField(&numBlock,sizeof(numBlock));
		this->vectorFreeBlock.push_back(numBlock);
		i++;
	}
	delete buffer;
}
void FreeBlockController::writeFreeBlock(unsigned int numBlock) throw() {
	this->vectorFreeBlock.push_back(numBlock);
	this->writeFreeBlock();
}
void FreeBlockController::writeFreeBlock(){
	int size=this->vectorFreeBlock.size();
	Buffer* buffer= new Buffer(size*sizeof(int)*2);
	buffer->packField(&size,sizeof(size));
	for (vector<unsigned int>::iterator it = this->vectorFreeBlock.begin(); it!=this->vectorFreeBlock.end(); ++it) {
		int numBlock=*it;
		buffer->packField(&numBlock,sizeof(numBlock));
	}
	this->binaryFile->write(buffer->getData(),buffer->getMaxBytes(),0);
	delete buffer;
}
unsigned int FreeBlockController::searchFreeBlock() throw() {
	if(this->vectorFreeBlock.size()!=0){
		unsigned int numBlock=this->vectorFreeBlock.back();
		this->vectorFreeBlock.pop_back();
		this->writeFreeBlock();
		return numBlock;
	}
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
void FreeBlockController::print(std::ostream& streamSalida){
	for (vector<unsigned int>::iterator it = this->vectorFreeBlock.begin(); it!=this->vectorFreeBlock.end(); ++it) {
		streamSalida<<" bloque libre : ";
		streamSalida<<*it;
		streamSalida<<endl;
	}
}

