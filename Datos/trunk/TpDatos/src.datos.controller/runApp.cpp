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


int main(int argc, char** ) {


//*****SE CONECTA Y CREA INDICE PRIMARIO***
/*	std::string strEmail;
	std::string strPass;
	Controller* control= new Controller();
	std::cout << "INGRESE SU DIRECCION DE E-MAIL: ";
	std::cin >> strEmail;

	control->addEmail(strEmail);
	std::cout << "INGRESE SU PASSWORD: ";
	std::cin >> strPass;
	control->addPass(strPass);
	control->createPrimaryIndex();*/
//****************************************

//*****CREA INDICE DE CLASIFICACION***
/*	IndexConfig* configOne = new IndexConfig();
	configOne->setUserName(strEmail);
	configOne->setTypeIndex(TYPE_SECONDARY);
	configOne->setTypeSecundaryIndex(TYPE_CLASSIFICATION);
	configOne->setCondition(FROM);
	configOne->setValue("asyura.from@gmail.com");
	configOne->setFilterName("Clasificacion 1");
	control->addSecondIndex(configOne);
	control->loadSecondIndex(configOne);*/
//***********************************

//*******CREA INDICE DE SELECCION*******
/*	IndexConfig* configTwo = new IndexConfig();
	configTwo->setUserName(strEmail);
	configTwo->setTypeIndex(TYPE_SECONDARY);
	configTwo->setTypeSecundaryIndex(TYPE_SELECTION);
	configTwo->setCondition(FROM);
	configTwo->setValue("asyura.from@gmail.com");
	configTwo->setFilterName("Seleccion1");
	control->addSecondIndex(configTwo);
	control->loadSecondIndex(configTwo);*/
//***********************************


//***********BUSQUEDA SOBRE SECUNDARIO SELECCION********
	Controller* control= new Controller();
	control->searchMails("[Seleccion1= ]");
	list<int>::iterator it;
	for(it= control->iteratorBeginListOfIucs(); it != control->iteratorEndListOfIucs(); it++){
		cout<<"IUC: "<<*it<<endl;
	}

//******************************************************





	return 0;
}
