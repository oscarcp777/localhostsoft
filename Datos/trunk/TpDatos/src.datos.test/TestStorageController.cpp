/*
 * TestStorageController.cpp
 *
 *  Created on: 25/09/2010
 *      Author: richy
 */

#include "TestStorageController.h"
#include "../src.datos.storage/StorageController.h"

TestStorageController::TestStorageController() {
	// TODO Auto-generated constructor stub

}

TestStorageController::~TestStorageController() {
	// TODO Auto-generated destructor stub
}
void TestStorageController::testConnectAndCreatePrimaryIndex(){
	StorageController* controller = new StorageController();
	string userName = "Datos.2c2010";
	string pass = "75067506";
	IndexBSharp* index = controller->generatePrimaryIndex((char*)userName.c_str(),(char*)pass.c_str());
	index->print(std::cout);
}
