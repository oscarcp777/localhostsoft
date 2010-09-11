/*
 * FreeBlockList.cpp
 *
 *  Created on: 24/04/2010
 *      Author: Santiago
 */

#include "FreeBlockController.h"


FreeBlockController::~FreeBlockController()throw(){
}
FreeBlockController::FreeBlockController(const std::string& nameFile) throw() {
	this->binaryFile = new BinaryFile();
	this->binaryFile->create(nameFile);
}


void FreeBlockController::writeSizeBusy(unsigned int position, unsigned int sizeBusy) throw() {
	this->binaryFile->write((char*) &sizeBusy, position);
}

unsigned int FreeBlockController::readSizeBusy(unsigned int position) throw() {
	unsigned int sizeBusy;
	this->binaryFile->read((char*) &sizeBusy, position);
	return sizeBusy;
}

unsigned int FreeBlockController::searchSizeBusy() throw() {
//	unsigned int cantidad_elementos = this->binaryFile->();
//	unsigned int contador = 0;
//	unsigned int espacio_ocupado = 0;
//	bool encontrado = false;
//
//	while (contador < cantidad_elementos && !encontrado) {
//		this->archivo->leer((char*) &espacio_ocupado, contador);
//		if (this->es_espacio_libre(espacio_ocupado)) {
//			encontrado = true;
//		} else {
//			++contador;
//		}
//	}
//
//	if (!encontrado) {
//		espacio_ocupado = 0;
//		this->archivo->agregar((char *) &espacio_ocupado);
//	}
	return 1;
}
