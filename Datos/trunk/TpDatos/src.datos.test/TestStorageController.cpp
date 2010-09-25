/*
 * TestStorageController.cpp
 *
 *  Created on: 25/09/2010
 *      Author: richy
 */

#include "TestStorageController.h"
#include "../src.datos.models/RegPrimary.h"
#include "../src.datos.models/KeyInteger.h"
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
	controller->generatePrimaryIndex((char*)userName.c_str(),(char*)pass.c_str());
	delete controller;
}
void TestStorageController::testPrintPrimaryIndex(){
	IndexBSharp* index = new IndexBSharp("Datos.2c2010.IndPrimario",BLOCK_SIZE,TYPE_REG_PRIMARY);
	index->print(std::cout);
}

void TestStorageController::testSearchPrimaryIndex(){
	IndexBSharp* index = new IndexBSharp("Datos.2c2010.IndPrimario",BLOCK_SIZE,TYPE_REG_PRIMARY);
	RegPrimary* regPrimary = new RegPrimary();
	KeyInteger* key= new KeyInteger(100);
	regPrimary->setKey(key);
	regPrimary = (RegPrimary*)index->searchRegistry(regPrimary);

	if(regPrimary == NULL)
		cout<<"CLAVE NO ENCONTRADA"<<endl;
	else
		regPrimary->print(std::cout);
	delete index;
}

