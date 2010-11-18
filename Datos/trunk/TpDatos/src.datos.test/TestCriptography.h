/*
 * TestCriptography.h
 *
 *  Created on: 14/11/2010
 *      Author: Santiago
 */

#ifndef TESTCRIPTOGRAPHY_H_
#define TESTCRIPTOGRAPHY_H_

#include <iostream>
#include "../src.datos.cryptography/Hill.h"

using namespace std;


class TestCriptography {
public:
	TestCriptography();
	virtual ~TestCriptography();

	/**
	 * Prueba basica de ecriptacion, se encripta un msj con una matriz basica y luego se desencripta
	 */
	void unitTest();
	void testTriangularMatrix();
};

#endif /* TESTCRIPTOGRAPHY_H_ */
