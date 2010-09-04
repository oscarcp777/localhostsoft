//============================================================================
// Name        : TpDatos.cpp
// Author      : Oscar caceres
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "../src.datos.models/Mail.h"
#include "../src.datos.storage/Buffer.h"
#include "../src.datos.storage/BinaryFile.h"
using namespace std;

int main() {
	cout << "!!!malditos monos !!!" << endl; // prints !!!Hello World!!!
	BinaryFile* file = new BinaryFile();
	Buffer* buffer = new Buffer(500);
	Mail* mailUno = new Mail();
	Mail* mailDos = new Mail();
	mailUno->setDate("27/8/2009");
	mailUno->setFrom("richy");
	mailUno->setMessage("aprobamooooossss");
	mailUno->setSubject("trabajo practico");
	mailUno->setTo("yogui");

	file->create("PruebaMail");
	mailUno->pack(buffer);
	file->write(buffer->getData(),buffer->getBufferSize(),0);
	file->close();

	buffer->clear();
	file->open("PruebaMail");
	file->read(buffer->getData(),buffer->getMaxBytes(),0);

	cout << "buffer: "<<buffer->getData()<< endl;
	mailDos->unPack(buffer);

	cout << "date: "<<mailUno->getDate()<< endl;
	cout << "date: "<<mailDos->getDate()<< endl;
	return 0;
}
