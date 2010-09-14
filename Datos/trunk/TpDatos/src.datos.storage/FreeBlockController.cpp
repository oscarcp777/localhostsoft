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
FreeBlockController::FreeBlockController(const std::string& nameFile) throw() {
	this->binaryFile = new BinaryFile();
	if(!this->binaryFile->isCreated(nameFile))
		this->binaryFile->create(nameFile);
	else
		this->binaryFile->open(nameFile);
}


void FreeBlockController::writeSizeBusy(unsigned int position, unsigned int sizeBusy) throw() {
	this->mapSizeBusy[position]=sizeBusy;
}
bool FreeBlockController::isSpaceFree(unsigned int sizeBusy) throw() {
//	unsigned int longitud_maxima_ocupada = ((float) this->longitud_maxima * this->porcentaje_ocupado);
	return sizeBusy == 0;
}
unsigned int FreeBlockController::searchSizeBusy() throw() {
	map<unsigned int,unsigned int>::iterator it;
	unsigned int sizeBusy = this->mapSizeBusy.size();
	for( it=this->mapSizeBusy.begin(); it != this->mapSizeBusy.end(); ++it ){
			if(it->second==0){
				return it->first;
			}
		}

	return sizeBusy++;
}
