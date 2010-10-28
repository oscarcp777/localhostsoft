/*
 * TestCompression.h
 *
 *  Created on: 18/10/2010
 *      Author: oscar
 */

#ifndef TESTCOMPRESSION_H_
#define TESTCOMPRESSION_H_
#include <iostream>
#include "../src.datos.utils/Define.h"
using namespace std;

class TestCompression {
public:
	TestCompression();
	virtual ~TestCompression();
	void testUnario();
	void testGamma();
	void testDelta();
	void testDelta2();
};

#endif /* TESTCOMPRESSION_H_ */
