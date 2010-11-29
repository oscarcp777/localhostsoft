/*
 * InfoPerDoc.cpp
 *
 *  Created on: 16/10/2010
 *      Author: Facundo
 */

#include "InfoPerDoc.h"


InfoPerDoc::InfoPerDoc() {
}
InfoPerDoc::~InfoPerDoc() {
	// TODO Auto-generated destructor stub
}
unsigned int InfoPerDoc::getlongBytesCompressed(){
	int sizeBusy=0;
	KeyInteger* key =(KeyInteger*)this->getKey();
	sizeBusy+=key->getlongBytesCompressed();
	int cantElement=this->listOfPositions.size();
	sizeBusy+=BitOutput::getOcupedBytes(cantElement);
	list<KeyInteger*>::iterator it;
		for(it = this->listOfPositions.begin() ; it != this->listOfPositions.end() ; it++){
			KeyInteger* key=(KeyInteger*)*it;
			sizeBusy+=key->getlongBytesCompressed();
		}
     return sizeBusy;
}
Registry* InfoPerDoc::clone(){
	return NULL;
}
void InfoPerDoc::chancePositionForDistancesAndReverse(bool reverse){
	list<KeyInteger*>::iterator it=this->listOfPositions.begin();
	KeyInteger* first=(KeyInteger*)*it;
	int firstPosition=first->getValue();
	it++;
	
		for(; it != this->listOfPositions.end() ; it++){
			KeyInteger* reg=(KeyInteger*)*it;
			int value=reg->getValue();
			if(!reverse){
			reg->setValue(value-firstPosition);
			firstPosition=value;
			}
			else{
			reg->setValue(value+firstPosition);
			firstPosition=reg->getValue();
			}
//			cout<<"########### este es el valor guardado :"<<reg->getValue()<<endl;
		}
}

bool InfoPerDoc::equals(Registry* comp){
	comp->getKey();
	return NULL;
}
void InfoPerDoc::pack(Buffer* buffer){
	buffer->init();
}
void InfoPerDoc::unPack(Buffer* buffer){
	buffer->init();
}
void InfoPerDoc::packCompressed(BitOutput* compressor){
	KeyInteger* key =(KeyInteger*)this->getKey();
	key->packCompressed(compressor);
	int size=this->listOfPositions.size();
	compressor->writeDelta(size);
	list<KeyInteger*>::iterator it;
	for(it = this->listOfPositions.begin() ; it != this->listOfPositions.end() ; it++){
		KeyInteger* key=(KeyInteger*)*it;
		key->packCompressed(compressor);
	}
}
void InfoPerDoc::unPackCompressed(BitInput* compressor){
	this->setKey(new KeyInteger());
	KeyInteger* key =(KeyInteger*)this->getKey();
	key->unPackCompressed(compressor);
	int numberElements=compressor->readDelta();
	for(int i=0; i<numberElements; i++){
		this->listOfPositions.push_back(new KeyInteger());
	}
	list<KeyInteger*>::iterator it;
	for(it = this->listOfPositions.begin() ; it != this->listOfPositions.end() ; it++){
		KeyInteger* key=(KeyInteger*)*it;
		key->unPackCompressed(compressor);
	}
}
int InfoPerDoc::getLongBytes(){
	return this->getSize();
}
Registry* InfoPerDoc::cloneRegKey(){
	return NULL;
}
int InfoPerDoc::compareTo(Registry* registry){
	KeyInteger* key=NULL;
	if(registry->getKey()==NULL){
		key=(KeyInteger*)registry;
	}
	else{
		key=(KeyInteger*)registry->getKey();
	}
	return this->getKey()->compareTo(key);
}
unsigned int InfoPerDoc::getSize(){
	return ((KeyInteger*)this->getKey())->getLongBytes()+this->listOfPositions.size()*sizeof(unsigned int);
}

void InfoPerDoc::addPosition(KeyInteger* pos){
	this->listOfPositions.push_back(pos);
}
list<KeyInteger*>::iterator InfoPerDoc::getBeginListPositions(){
	return this->listOfPositions.begin();
}
list<KeyInteger*>::iterator InfoPerDoc::getEndListPositions(){
	return this->listOfPositions.end();
}

bool InfoPerDoc::compareDistance(InfoPerDoc* infoPerDoc, int distance){
	list<KeyInteger*>::iterator it;
	list<KeyInteger*>::iterator itSecondary;
	int pos;
	int posSecundary;
	for(it = this->listOfPositions.begin(); it != this->listOfPositions.end(); it++){
		pos = ((KeyInteger*)(*it))->getValue();
		//cout<<"POS: "<<pos<<endl;
		for(itSecondary= infoPerDoc->getBeginListPositions(); itSecondary != infoPerDoc->getEndListPositions(); itSecondary++){
			posSecundary = ((KeyInteger*)(*itSecondary))->getValue();
			//cout<<"posSecundary: "<<posSecundary<<endl;
			if(abs(pos - posSecundary) == distance)
				return true;
		}
	}
	return false;
}
int InfoPerDoc::print(ostream& outStream){
	outStream<<"IUC: ";
	this->getKey()->print(outStream);
	list<KeyInteger*>::iterator it;
	outStream<<"pos: ";
	for(it = this->listOfPositions.begin() ; it != this->listOfPositions.end() ; it++){
		KeyInteger* key=(KeyInteger*)*it;
		key->print(outStream);
	}
	outStream<<endl;
	return 1;
}
