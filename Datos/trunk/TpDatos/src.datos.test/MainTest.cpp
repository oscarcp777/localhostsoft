//============================================================================
// Name        : TpDatos.cpp
// Author      : Oscar caceres
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include "TestStorage.h"
using namespace std;

int main() {
	cout << "!!!malditos monos !!!" << endl; // prints !!!Hello World!!!
   TestStorage* teststorage = new TestStorage();
   teststorage->testBlock();
   delete teststorage;
	return 0;
}
