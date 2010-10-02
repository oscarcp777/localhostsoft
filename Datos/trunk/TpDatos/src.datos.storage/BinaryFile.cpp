/*
 * BinaryFile.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Santiago
 */

#include "BinaryFile.h"

BinaryFile::BinaryFile() {
}

BinaryFile::~BinaryFile() {
}

//ios::trunc crea si no existe o lo abre ver para unificar create y open

void BinaryFile::create(string fileName){

	this->name = fileName;
	this->file.open(fileName.c_str(),ios::trunc|ios::in |ios::out |ios::binary);

}
bool BinaryFile::isCreated(string fileName){
	this->file.open(fileName.c_str(),ios::in|ios::binary);
	if (! this->file.is_open()){
		return false;
	}
	else{
		this->close();
		return true;

	}
}
void BinaryFile::open(string fileName){

	this->name = fileName;
	this->file.open(fileName.c_str(),ios::in |ios::out |ios::binary);

}
void BinaryFile::clear(){
	if(this->file.is_open()){
		this->close();
		this->file.open(this->name.c_str(),ios::trunc|ios::in|ios::out |ios::binary);
	}
}
