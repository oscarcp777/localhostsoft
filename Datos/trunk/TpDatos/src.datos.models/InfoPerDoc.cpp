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

Registry* InfoPerDoc::clone(){
     return NULL;
}
bool InfoPerDoc::equals(Registry* comp){
	  return NULL;
}
void InfoPerDoc::pack(Buffer* buffer){
	this->getKey()->pack(buffer);
	unsigned int size=this->listOfPositions.size();
	buffer->packField(&size,sizeof(size));
	list<KeyInteger*>::iterator it;
	for(it = this->listOfPositions.begin() ; it != this->listOfPositions.end() ; it++){
		KeyInteger* key=(KeyInteger*)*it;
		key->pack(buffer);
	}
}
void InfoPerDoc::unPack(Buffer* buffer){
	this->setKey(new KeyInteger(-1));
	this->getKey()->unPack(buffer);
	unsigned int numberElements=0;
	buffer->unPackField(&numberElements,sizeof(numberElements));
		for(unsigned int i=0; i<numberElements; i++){
			this->listOfPositions.push_back(new KeyInteger());
		}
	list<KeyInteger*>::iterator it;
	for(it = this->listOfPositions.begin() ; it != this->listOfPositions.end() ; it++){
		KeyInteger* key=(KeyInteger*)*it;
		key->unPack(buffer);
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
		pos = ((KeyInteger*)(*it)->getKey())->getValue();
		for(itSecondary= infoPerDoc->getBeginListPositions(); itSecondary != infoPerDoc->getEndListPositions(); itSecondary++){
			posSecundary = ((KeyInteger*)(*itSecondary)->getKey())->getValue();
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
