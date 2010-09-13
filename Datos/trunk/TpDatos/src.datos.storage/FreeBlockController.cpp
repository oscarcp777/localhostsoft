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
	this->binaryFile->write((char*)&sizeBusy,sizeof(unsigned int),position*sizeof(unsigned int));
}

unsigned int FreeBlockController::readSizeBusy(unsigned int position) throw() {
	unsigned int sizeBusy;
	this->binaryFile->read((char*) &sizeBusy, position*sizeof(unsigned int));
	return sizeBusy;
}
bool FreeBlockController::isSpaceFree(unsigned int sizeBusy) throw() {
//	unsigned int longitud_maxima_ocupada = ((float) this->longitud_maxima * this->porcentaje_ocupado);
	return sizeBusy == 0;
}
unsigned int FreeBlockController::searchSizeBusy() throw() {
	unsigned int countBlock = this->binaryFile->getCountBlockInFile(sizeof(unsigned int));
	unsigned int cont = 0;
	unsigned int sizeBusy = 0;
	bool find = false;

	while (cont < countBlock && !find) {
		this->binaryFile->read((char*) &sizeBusy, cont*sizeof(unsigned int));
		if (this->isSpaceFree(sizeBusy)) {
			find = true;
		} else {
			++cont;
		}
	}

	if (!find) {
		sizeBusy = 0;
		this->binaryFile->write((char *) &sizeBusy,sizeof(sizeBusy));
	}
	return sizeBusy;
}
