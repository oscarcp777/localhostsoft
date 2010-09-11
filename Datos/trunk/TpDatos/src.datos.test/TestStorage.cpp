/*
 * TestStorage.cpp
 *
 *  Created on: 04/09/2010
 *      Author: oscar
 */

#include "TestStorage.h"

TestStorage::TestStorage() {
	// TODO Auto-generated constructor stub

}

TestStorage::~TestStorage() {
	// TODO Auto-generated destructor stub
}
void TestStorage::testMails(){
	BinaryFile* file = new BinaryFile();
	Buffer* buffer = new Buffer(BLOCK_SIZE);
	Mail* mailUno = new Mail();
	Mail* mailDos = new Mail();
	mailUno->setDate("27/8/2009");
	mailUno->setFrom("richy");
	mailUno->setMessage("aprobamooooossss");
	mailUno->setSubject("trabajo practico");
	mailUno->setTo("yogui");

	file->create("files/storage/PruebaMail.dat");
	mailUno->pack(buffer);
	file->write(buffer->getData(),buffer->getBufferSize(),0);
	file->close();

	buffer->clear();
	file->open("files/storage/PruebaMail.dat");
	file->read(buffer->getData(),buffer->getMaxBytes(),0);
	file->close();
	cout << "buffer: "<<buffer->getData()<< endl;
	mailDos->unPack(buffer);

	cout << "date: "<<mailUno->getDate()<< endl;
	cout << "date: "<<mailDos->getDate()<< endl;
	delete buffer;
	delete file;
	delete mailUno;
	delete mailDos;
}
void TestStorage::testBlock(){
	BinaryFile* file = new BinaryFile();
	Block* block = new Block(200,0,0);
	Mail* mail1 = new Mail();
	mail1->setKey(new Key("100"));
	mail1->setDate("27/8/2009");
	mail1->setFrom("richy");
	mail1->setMessage("aprobamooooossss");
	mail1->setSubject("trabajo practico");
	mail1->setTo("yogui");

	Mail* mail2 = new Mail();
	mail2->setKey(new Key("101"));
	mail2->setDate("27/18/2009");
	mail2->setFrom("oscar");
	mail2->setMessage("aprobamooooossss");
	mail2->setSubject("texto de nada");
	mail2->setTo("richy");

	Mail* mail3 = new Mail();
	mail3->setKey(new Key("102"));
	mail3->setDate("27/38/2009");
	mail3->setFrom("richy");
	mail3->setMessage("trabajode nada de nada");
	mail3->setSubject("trabajo trabajo");
	mail3->setTo("yogui");
   Buffer* buffer= new Buffer(200);
	block->addReg(mail1);
	block->addReg(mail2);
	block->addReg(mail3);
	block->pack(buffer);
	file->create("PruebaMail.dat");
	file->write(buffer->getData(),0);
	file->close();

	Block* block2 = new Block(200,0,0);
	file->open("PruebaMail.dat");
	file->read(buffer->getData(),0);
	block->unPack(buffer);
	file->close();

    block2->print(std::cout);
	delete file;
	delete block;
	delete block2;
}
