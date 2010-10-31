/*
 * RegInvertedIndex.cpp
 *
 *  Created on: 16/10/2010
 *      Author: Facundo
 */

#include "RegInvertedIndex.h"
#include "../src.datos.BTreeSharp/BlockDataManager.h"
RegInvertedIndex::RegInvertedIndex() {
 this->numBlock=NEXT_BLOCK_INVALID;

}
InfoPerDoc* RegInvertedIndex::getInfoPerDoc()
{
	return (InfoPerDoc*)this->infoPerDoc.back();
}

RegInvertedIndex::~RegInvertedIndex() {
	// TODO Auto-generated destructor stub
}

void RegInvertedIndex::addInfoPerDoc(InfoPerDoc* infoPerDoc){
	this->infoPerDoc.push_back(infoPerDoc);
}
InfoPerDoc* RegInvertedIndex::getFirstInfoPerDoc(){
	return (*this->infoPerDoc.begin());
}

list<InfoPerDoc*>::iterator RegInvertedIndex::getBeginListInfoPerDoc(){
	return this->infoPerDoc.begin();
}
list<InfoPerDoc*>::iterator RegInvertedIndex::getEndListInfoPerDoc(){
	return this->infoPerDoc.end();
}
int RegInvertedIndex::getNumBlock()
{
	return numBlock;
}
void RegInvertedIndex::setNumBlock(int numBlock){
	this->numBlock = numBlock;
}
void RegInvertedIndex::setListInfoPerDoc(list<InfoPerDoc*> &listInfoPerDocNew){
	this->infoPerDoc.clear();
	listInfoPerDocNew.swap(this->infoPerDoc);
}
Registry* RegInvertedIndex::clone(){
	RegInvertedIndex* regClone = new RegInvertedIndex();
	regClone->setKey((KeyString*)this->getKey()->clone());
	regClone->setNumBlock(this->numBlock);
	return regClone;
}
bool RegInvertedIndex::equals(Registry* registry){
	KeyString* key=(KeyString*)registry->getKey();
	return this->getKey()->equals(key) ;
}
void RegInvertedIndex::pack(Buffer* buffer){//TODO
	this->getKey()->pack(buffer);
	buffer->packField(&this->numBlock,sizeof(this->numBlock));
}
void RegInvertedIndex::unPack(Buffer* buffer){//TODO
	this->setKey(new KeyString(""));
	this->getKey()->unPack(buffer);
	buffer->unPackField(&this->numBlock,sizeof(this->numBlock));
}
int RegInvertedIndex::getLongBytes(){
	return this->getSize();
}
int RegInvertedIndex::compareTo(Registry* registry){
	KeyString* key=NULL;
	if(registry->getKey()==NULL){
		key=(KeyString*)registry;
	}
	else{
		key=(KeyString*)registry->getKey();
	}
	return this->getKey()->compareTo(key);
}
unsigned int RegInvertedIndex::getSize(){
	KeyString* key=(KeyString*)this->getKey();
	return key->getSize()+sizeof(this->numBlock); //TODO
}
Registry* RegInvertedIndex::cloneRegKey(){
	return this->getKey()->clone();
}

int RegInvertedIndex::print(std::ostream& outStream){
	outStream<<"key: ";
	((KeyString*)this->key)->print(outStream);
	outStream<<" : " ;
	outStream<<"offset :"<<numBlock<<endl;
	list<InfoPerDoc*>::iterator it;
	if(this->infoPerDoc.empty()){
		if(DATA==1&&DATA_SHOW==1){
			BlockDataManager* manager= new BlockDataManager();
			manager->loadListInfoPerDocBlockData(this,this->numBlock,this->container);
			delete manager;
		}
	}
	int sizeCompressed=0;
	int sizeNormal=0;
	for(it = this->infoPerDoc.begin() ; it != this->infoPerDoc.end() ; it++){
		InfoPerDoc* info=(InfoPerDoc*)(*it);
		info->print(outStream);
		sizeCompressed+=info->getlongBytesCompressed();
		sizeNormal+=info->getLongBytes();
	}
	if(!this->infoPerDoc.empty()){
		outStream << "-OCUPA : " << sizeCompressed;
		outStream<<" BYTES ";
		outStream << " (SIN COMPRIMIR OCUPARIA: " <<sizeNormal<<")";
		outStream<<endl;
	}
	outStream<<endl;
	return 0;
}
void RegInvertedIndex::clearInfoPerDoc(){
    this->infoPerDoc.clear();
}
