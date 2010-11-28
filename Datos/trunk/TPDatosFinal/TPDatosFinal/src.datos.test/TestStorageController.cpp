/*
 * TestStorageController.cpp
 *
 *  Created on: 25/09/2010
 *      Author: richy
 */

#include "TestStorageController.h"
#include "../src.datos.models/RegPrimary.h"
#include "../src.datos.models/KeyInteger.h"
#include "../src.datos.controller/StorageController.h"

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
	IndexConfig* configIndex = new IndexConfig();

	controller->generatePrimaryIndex((char*)userName.c_str(),(char*)pass.c_str(),configIndex);
	delete controller;
}
void TestStorageController::testPrintPrimaryIndex(){
	IndexBSharp* index = new IndexBSharp("Datos.2c2010.IndPrimario",BLOCK_SIZE,TYPE_REG_PRIMARY);
	index->print(std::cout);
	delete index;
}

void TestStorageController::testSearchPrimaryIndex(){
	IndexBSharp* index = new IndexBSharp("Datos.2c2010.IndPrimario",BLOCK_SIZE,TYPE_REG_PRIMARY);
	std::string option;
	int iuc;
	do{
		std::cout << "Ingrese IUC a buscar: ";
		std::cin >> iuc;
		RegPrimary* regPrimary = new RegPrimary();
		KeyInteger* key= new KeyInteger(iuc);
		regPrimary->setKey(key);
		regPrimary = (RegPrimary*)index->searchRegistry(regPrimary);

		if(regPrimary == NULL)
			cout<<"CLAVE NO ENCONTRADA"<<endl;
		else
			regPrimary->print(std::cout);
		delete regPrimary;

		std::cout << "Desea buscar nuevamente? (SI / NO) " << std::endl;
		std::cin >> option;
	} while (option == "SI");

	delete index;
}

