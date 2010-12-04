/*
 * CompressedBlock.cpp
 *
 *  Created on: 24/10/2010
 *      Author: oscar
 */

#include "CompressedBlock.h"


CompressedBlock::CompressedBlock(unsigned int sizeBlock,int typeElement,bool indexed):Block(sizeBlock,typeElement,indexed) {
	this->compressorBitInput=NULL;
	this->compressorBitOutput=NULL;
}


CompressedBlock::~CompressedBlock() {
	if(this->compressorBitInput!=NULL)
		delete this->compressorBitInput;
	if(this->compressorBitOutput!=NULL)
		delete this->compressorBitOutput;
}
void CompressedBlock::loadOutPutCompressor(BitArrayBufferCompression* buffer){
	this->compressorBitOutput= new BitOutput(buffer);
}
void CompressedBlock::loadInPutCompressor(BitArrayBufferCompression* buffer){
	this->compressorBitInput= new BitInput(buffer);
}
void CompressedBlock::packCompressed(BitArrayBufferCompression* buffer){
	this->chancePositionForDistancesAndReverse(false);
	this->loadOutPutCompressor(buffer);
	this->packMetadata(buffer);
	this->packListRegistryCompressed();
	this->compressorBitOutput->flush();
//	cout<<"cantidad de bytes que se escribe en disco buffer :"<<buffer->getNextByte()<<endl;

}
void CompressedBlock::unPackCompressed(BitArrayBufferCompression* buffer){
	int numberElements = this->unPackMetadata(buffer);
	this->loadInPutCompressor(buffer);
	this->unPackListRegistryCompressed(numberElements,this->typeElement);
	this->chancePositionForDistancesAndReverse(true);
}



int CompressedBlock::unPackMetadataCompressed(){
	int numberElements=0;
	numberElements=this->compressorBitInput->readDelta();
	if(this->indexed)
		this->nextNode=compressorBitInput->readDelta();
	return numberElements;

}
void CompressedBlock::packMetadataCompressed(){
	int numberElements = this->regList.size();
	this->compressorBitOutput->writeDelta(numberElements);
	if(this->indexed)
		this->compressorBitOutput->writeDelta(this->nextNode);
}

void CompressedBlock::packListRegistryCompressed(){
	list<Registry*>::iterator iterRegistry;

	for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		InfoPerDoc* reg=(InfoPerDoc*)*iterRegistry;
		reg->chancePositionForDistancesAndReverse(false);
		reg->packCompressed(this->compressorBitOutput);
//		reg->print(cout);
//				cout<<"cantidad de bytes en buffer :"<<this->compressorBitOutput->getBytesCompressed()<<endl;
//				cout<<"getlongBytesCompressed :"<<reg->getlongBytesCompressed()<<endl;
	}
}
unsigned int CompressedBlock::getSizeRegCompressed(){
	unsigned int sizeBusy=0;
	list<Registry*>::iterator iterRegistry;
	for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		InfoPerDoc* reg=(InfoPerDoc*)*iterRegistry;
		sizeBusy+=reg->getlongBytesCompressed();
	}
	return sizeBusy;
}
void CompressedBlock::chancePositionForDistancesAndReverse(bool reverse){
	list<Registry*>::iterator it=this->regList.begin();
	InfoPerDoc* first=(InfoPerDoc*)*it;
	int firstPosition=((KeyInteger*)first->getKey())->getValue();
	it++;
	for(; it != this->regList.end() ; it++){
		InfoPerDoc* reg=(InfoPerDoc*)*it;
		int value=((KeyInteger*)reg->getKey())->getValue();
		if(!reverse){
			((KeyInteger*)reg->getKey())->setValue(value-firstPosition);
			firstPosition=value;
		}else{
			((KeyInteger*)reg->getKey())->setValue(value+firstPosition);
			firstPosition=((KeyInteger*)reg->getKey())->getValue();
		}
//	cout<<"########### este es el valor guardado :CompressedBlock "<<((KeyInteger*)reg->getKey())->getValue()<<endl;
	}
}
unsigned int CompressedBlock::getOcupedLongCompressed(){
	unsigned int sizeBusy=this->getSizeRegCompressed();
	sizeBusy += sizeof(unsigned int);
	if(this->indexed)
		sizeBusy += sizeof(unsigned int);
	return sizeBusy;
}
bool CompressedBlock::posibleToAgregateRegCompressed(InfoPerDoc* registry){

	return (this->getOcupedLongCompressed() + registry->getlongBytesCompressed() <= this->getMaxLong());

}
void CompressedBlock::unPackListRegistryCompressed( int numberElements, int typeElement){
	list<Registry*>::iterator iterRegistry;
	for(int i=0; i<numberElements; i++){
		this->regList.push_back(factory->createRegistry(typeElement));
	}
	for (iterRegistry=this->regList.begin(); iterRegistry!=this->regList.end(); iterRegistry++){
		InfoPerDoc* reg=(InfoPerDoc*)*iterRegistry;
		reg->unPackCompressed(this->compressorBitInput);
		reg->chancePositionForDistancesAndReverse(true);
	}
}

