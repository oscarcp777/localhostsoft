//============================================================================
// Name        : controller.cpp
// Author      : Facundo Sanchez Galindo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Controller.h"
using namespace std;


int mainOSALF(int argc, char** ) {
	std::string strEmail;
	std::string strPass;
	Controller* control= new Controller();
	std::cout << "INGRESE SU DIRECCION DE E-MAIL: ";
//	std::cin >> strEmail;

	control->addEmail("Datos.2c2010");
	std::cout << "INGRESE SU PASSWORD: ";
//	std::cin >> strPass;
	control->addPass("75067506");
	control->createPrimaryIndex();



	IndexConfig* config = new IndexConfig();
	config->setUserName(strEmail);
	config->setTypeIndex(TYPE_SECONDARY);
	config->setTypeSecundaryIndex(TYPE_SELECTION);
	config->setCondition(FROM);
	config->setValue("asyura.from@gmail.com");
	config->setFilterName("Clasificacion 1");
	control->addSecondIndex(config);

	control->loadSecondIndex(config);

	return 0;
}
