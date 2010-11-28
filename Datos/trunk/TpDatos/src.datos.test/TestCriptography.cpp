/*
 * TestCriptography.cpp
 *
 *  Created on: 14/11/2010
 *      Author: Santiago
 */

#include "TestCriptography.h"
#include "../src.datos.storage/Buffer.h"

TestCriptography::TestCriptography() {
	// TODO Auto-generated constructor stub

}

TestCriptography::~TestCriptography() {
	// TODO Auto-generated destructor stub
}

void TestCriptography::unitTest(){

	cout << "Prueba Encriptacion" << endl;

	Hill* hill = Hill::getInstance();
	hill->initialize(8,"clave");

	hill->printKeyMatrix();
	hill->printKeyInvertedMatrix();

	string textEncrypted = hill->encrypt("hola, anda todo joya, jejeje por favor que falle la puta madre  esto es un texto ultrapoderoso que testea toda encriptacion sisi");
	cout << "Texto Encriptado: " << textEncrypted << endl;
	string textDecrypted = hill->decrypt(textEncrypted);
	cout << "Texto Desencriptado: " << textDecrypted << endl;


	delete hill;

}
void TestCriptography::unitTestWithBuffer(){

	cout << "Prueba Encriptacion" << endl;

	Hill* hill = Hill::getInstance();
	hill->initialize(8,"clave");

	hill->printKeyMatrix();
	hill->printKeyInvertedMatrix();
	Buffer*  buffer= new Buffer(64);
	int number=1;
	buffer->packField(&number,sizeof(number));
	number=5;
	buffer->packField(&number,sizeof(number));
	number=6;
	buffer->packField(&number,sizeof(number));
	number=200;
	buffer->packField(&number,sizeof(number));
	string str="mensaje largoo jajajajJAJAJAAJJOOOO";
	int size=str.size();
	buffer->packField(&size, sizeof(size));
	buffer->packField(str.c_str(),size);
	Buffer*  bufferCrypted = hill->encrypt(buffer->getData(),buffer->getMaxBytes());
	Buffer*  bufferDecrypted = hill->decrypt(bufferCrypted->getData(),buffer->getMaxBytes());
	number=0;
	bufferDecrypted->unPackField(&number,sizeof(number));
	cout << "Desencriptado: " << number <<" Original :"<<1<< endl;
	bufferDecrypted->unPackField(&number,sizeof(number));
	cout << "Desencriptado: " << number <<" Original :"<<5<< endl;
	bufferDecrypted->unPackField(&number,sizeof(number));
	cout << "Desencriptado: " << number <<" Original :"<<6<< endl;
	bufferDecrypted->unPackField(&number,sizeof(number));
	cout << "Desencriptado: " << number <<" Original :"<<200<< endl;
	bufferDecrypted->unPackField(&size, sizeof(size));
	string newSrt="";
	bufferDecrypted->unPackFieldString(newSrt,size);
	cout<<newSrt<<endl;
	delete hill;
	delete bufferDecrypted;
	delete bufferCrypted;
	delete buffer;

}
