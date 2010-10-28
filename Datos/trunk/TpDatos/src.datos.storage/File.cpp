/*
 * Archivo.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Santiago
 */

#include "File.h"

using namespace std;


File::File(){
}

File::~File() {
}
void File::flush(){
    this->file.flush();
}
bool File::read(std::string& datos){

	/* verifica que el file esté abierto */
	if (this->file.is_open()) {
		/* lee del file una linea */
		getline(this->file, datos);
		/* chequea si se ha producido un error */
		if (this->file.fail()){
			/* el archivo esta vacio */
			this->file.clear();
		}
		return true;

	}
	else {
		/* arroja una excepción porque el file no está abierto */
		return false;
		throw string("File not open");

	}

}


bool File::read(char* buffer, int tamanio, int pos){

	if (this->file.is_open()) {
		if(pos>=0)
			this->file.seekg(pos, std::ios_base::beg);
		else
		this->file.seekp(0, std::ios_base::end);

		this->file.read(buffer,tamanio);
	}
	else {
		/* arroja una excepción porque el file no está abierto */
		throw string("File not open");
	}
	bool good = this->file.good();

		if (!good) {
			this->file.clear();
		}
		return good;

}
void File::readInteger(int* num, int pos){
	if (this->file.is_open()) {
			if(pos>=0){
				this->file.seekg(pos, std::ios_base::beg);
			}
			this->file.read(reinterpret_cast<char*>(num),sizeof(num));
		}
		else {
			/* arroja una excepción porque el file no está abierto */
			throw string("File not open");
		}
}


int File::write(std::string registro){

	if (this->file.is_open()) {
		this->file << registro<<endl;

		if (this->file.fail())
			// si se produjo un error, arroja una excepción
			throw std::ios_base::failure("Write line error");

	} else {
		/* arroja una excepción porque el file no está abierto */
		throw string("File not open");
	}
	return 1;
}


void File::write(char* buffer, int tamanio, int pos){

	if (this->file.is_open()) {
		if (pos >= 0)
			this->file.seekp(pos, std::ios_base::beg);
		else
			this->file.seekp(0, std::ios_base::end);
		this->file.write(buffer,tamanio);


	}

}
unsigned int File::getCountBlockInFile(int sizeBlock) throw() {
	this->file.seekp(0, std::ios_base::end);
	unsigned int position = this->file.tellp();
	unsigned int countBlock = position / sizeBlock;
	return countBlock;
}


void File::writeInteger(int* num, int pos){

	if (this->file.is_open()) {
		if (pos >= 0)
			this->file.seekp(pos);
		this->file.write((char*)num,sizeof(num));


	}

}
void File::close(){
	this->file.close();
	if (this->file.fail())
		throw string("File not close");
}


std::string File::toString(){
	return "File";
}


ostream& File::getStream(){
	return file;
}


