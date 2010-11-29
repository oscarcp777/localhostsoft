/*
 * TextFile.cpp
 *
 *  Created on: 25/03/2010
 *      Author: oscar
 */

#include "TextFile.h"

TextFile::TextFile() {

}

TextFile::~TextFile() {

}

void TextFile::create(string fileName){
	fileName.size();
}
void TextFile::end(){
	this->file.seekp(0, std::ios_base::end);
}
void TextFile::open(string fileName){

	this->file.open(fileName.c_str(),ios::in | ios::out);

	if (!this->file.is_open()){
		this->file.clear();
		this->file.open(fileName.c_str(), ios::app|ios::out);
		this->file.close();
		this->file.open(fileName.c_str(), ios::in | ios::out);
	}

	if (!this->file.is_open()){
		throw ios_base::failure("El archivo no pudo ser abierto");
	}
}
