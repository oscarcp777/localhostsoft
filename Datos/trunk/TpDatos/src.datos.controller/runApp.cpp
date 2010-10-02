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
	std::string strEmail = "Datos.2c2010";
	std::string strPass = "75067506";
	Controller* control= new Controller();
//	std::cout << "INGRESE SU DIRECCION DE E-MAIL: ";
//	std::cin >> strEmail;
//
//	control->addEmail(strEmail);
//	std::cout << "INGRESE SU PASSWORD: ";
//	std::cin >> strPass;
//	control->addPass(strPass);
//	control->createPrimaryIndex();
//****************************************

//*****CREA INDICE DE CLASIFICACION***
/*	IndexConfig* configOne = new IndexConfig();
	configOne->setUserName(strEmail);
	configOne->setTypeIndex(TYPE_SECONDARY);
	configOne->setTypeSecundaryIndex(TYPE_CLASSIFICATION);
	configOne->setCondition(FROM);
	configOne->setFilterName("Clasificacion1");
	control->addSecondIndex(configOne);
	control->loadSecondIndex(configOne);*/
//***********************************

//*******CREA INDICE DE SELECCION*******
//	IndexConfig* configTwo = new IndexConfig();
//	configTwo->setUserName(strEmail);
//	configTwo->setTypeIndex(TYPE_SECONDARY);
//	configTwo->setTypeSecundaryIndex(TYPE_SELECTION);
//	configTwo->setCondition(FROM);
//	configTwo->setValue("asyura.from@gmail.com");
//	configTwo->setFilterName("Seleccion1");
//	control->addSecondIndex(configTwo);
//	IndexConfig* configOne = new IndexConfig();
//	configOne = control->loadIndexConfig("Seleccion1");
//	control->loadSecondIndex(configOne);

//***********************************

//***********BUSQUEDA SOBRE PRIMARIO********
/*	Controller* control= new Controller();
	control->searchMails("[PrimarioDatos.2c2010=1,4,6,8,22,30,7,171,200,98,276]");
	list<Mail*>::iterator it;
	for(it= control->iteratorBeginListOfMails(); it != control->iteratorEndListOfMails(); it++){
			(*it)->print(cout);
	}
//*/
//******************************************************


//***********BUSQUEDA SOBRE SECUNDARIO SELECCION********
	//Controller* control= new Controller();
	cout<<"------------------------------------------------------------------------------------------"<<endl;
	control->searchMails("[Seleccion1= ]");

	list<int>::iterator it;
	for(it= control->iteratorBeginListOfIucs(); it != control->iteratorEndListOfIucs(); it++){
		cout<<"IUC: "<<*it<<endl;
	}
cout<<"salio con cantidad de resultados: "<< control->getListOfIUCS().size() <<endl;
//******************************************************

//***********BUSQUEDA SOBRE SECUNDARIO CLASIFICACION********
//	Controller* control= new Controller();
//	control->searchMails("[Clasificacion1=santiagodonikian@gmail.com]");
//
//	list<int>::iterator it;
//	for(it= control->iteratorBeginListOfIucs(); it != control->iteratorEndListOfIucs(); it++){
//		cout<<"IUC: "<<*it<<endl;
//	}
//******************************************************

	delete control;
	return 0;
}
