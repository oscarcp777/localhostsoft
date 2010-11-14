/*
 * TestCriptography.cpp
 *
 *  Created on: 14/11/2010
 *      Author: Santiago
 */

#include "TestCriptography.h"

TestCriptography::TestCriptography() {
	// TODO Auto-generated constructor stub

}

TestCriptography::~TestCriptography() {
	// TODO Auto-generated destructor stub
}

void TestCriptography::unitTest(){

	cout << "Prueba Encriptacion" << endl;

	Hill* hill = new Hill(2,"claveNoUtilizadaAun");
	hill->printKeyMatrix();
	hill->printKeyInvertedMatrix();

	string textEncrypted = hill->encrypt("hola, anda todo joya, jejeje");
	cout << "Texto Encriptado: " << textEncrypted << endl;

	string textDecrypted = hill->decrypt(textEncrypted);
	cout << "Texto Desencriptado: " << textDecrypted << endl;


	delete hill;

}


