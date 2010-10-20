/*
 * TestCompression.cpp
 *
 *  Created on: 18/10/2010
 *      Author: oscar
 */

#include "TestCompression.h"

TestCompression::TestCompression() {
	// TODO Auto-generated constructor stub

}

TestCompression::~TestCompression() {
	// TODO Auto-generated destructor stub
}


void testCompression(){
	 short signed cero = 0, uno = 1, dos = 2;
	  cout << "0 << 1 == " << (cero << 1) << endl;
	  cout << "1 << 1 == " << (uno << 1) << endl;
	  cout << "2 << 1 == " << (dos << 1) << endl;

}
