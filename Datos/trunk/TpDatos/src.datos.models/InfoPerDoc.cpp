/*
 * InfoPerDoc.cpp
 *
 *  Created on: 16/10/2010
 *      Author: Facundo
 */

#include "InfoPerDoc.h"

InfoPerDoc::InfoPerDoc(int iuc) {
	this->iuc = iuc;
}

InfoPerDoc::~InfoPerDoc() {
	// TODO Auto-generated destructor stub
}
void InfoPerDoc::setIuc(int iuc){
	this->iuc = iuc;
}
int InfoPerDoc::getIuc(){
	return this->iuc;
}
void InfoPerDoc::addPosition(int pos){
	this->listOfPositions.push_back(pos);
}
void InfoPerDoc::print(std::ostream& outStream){
	outStream<<"IUC: "<<this->iuc<<endl;
	list<int>::iterator it;
	outStream<<"pos: ";
		for(it = this->listOfPositions.begin() ; it != this->listOfPositions.end() ; it++){
			outStream<<*it<<" ";
		}
		outStream<<endl;
}
