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
	Buffer* buffer = new Buffer(sizeof(int));
	buffer->packField(&sizeBusy,sizeof(sizeBusy));
	this->binaryFile->write(buffer->getData(),sizeof(int),position*sizeof(int));
	delete buffer;
}

unsigned int FreeBlockController::readSizeBusy(unsigned int position) throw() {
	unsigned int sizeBusy;
	this->binaryFile->read((char*) &sizeBusy, position);
	return sizeBusy;
}

unsigned int FreeBlockController::searchSizeBusy() throw() {
//	unsigned int countBlock = this->binaryFile->getCountBlockInFile(sizeof(int));
//	unsigned int cont = 0;
	unsigned int sizeBusy = 0;
//	bool find = false;
//TODO ver manejode bloques libres
//TODO
//	while (cont < countBlock && !find) {
//		this->binaryFile->read((char*) &sizeBusy, cont);
//		if (this->es_espacio_libre(sizeBusy)) {
//			find = true;
//		} else {
//			++cont;
//		}
//	}
//
//	if (!find) {
//		sizeBusy = 0;
//		this->binaryFile->agregar((char *) &sizeBusy);
//	}
	return sizeBusy;
}
