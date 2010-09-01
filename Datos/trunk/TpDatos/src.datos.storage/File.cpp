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
void File::read(std::string& datos){

	/* verifica que el file esté abierto */
	if (this->file.is_open()) {
		/* lee del file una linea */
		getline(this->file, datos);
		/* chequea si se ha producido un error */
		if (this->file.fail())
			/* arroja una excepción ante la imposibilidad de leer un reg */
			throw string("Read line error");
	}
	else {
		/* arroja una excepción porque el file no está abierto */
		throw string("File not open");
	}
}


void File::read(char* buffer, int tamanio, int pos){

	if (this->file.is_open()) {
		if(pos>=0)
			this->file.seekg(pos);
		this->file.read(buffer,tamanio);
	}
	else {
		/* arroja una excepción porque el file no está abierto */
		throw string("File not open");
	}

}
void File::readInteger(int* num, int pos){
	if (this->file.is_open()) {
			if(pos>=0)
				this->file.seekg(pos);
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
			this->file.seekp(pos);
		this->file.write(buffer,tamanio);


	}

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

}


std::string File::toString(){
	return "File";
}


ostream& File::getStream(){
	return file;
}


