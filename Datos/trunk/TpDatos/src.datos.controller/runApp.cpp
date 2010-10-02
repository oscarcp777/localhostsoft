/*
 * Console.cpp
 *
 *  Created on: 01/10/2010
 *      Author: Richard
 */

#include <stddef.h>
#include <iostream>
#include "../src.datos.controller/Controller.h"

using namespace std;



void printResult(Controller* control){

		list<int>::iterator it;
		for(it= control->iteratorBeginListOfIucs(); it != control->iteratorEndListOfIucs(); it++){
			cout<<"IUC: "<<*it<<endl;
		}

		list<Mail*>::iterator it2;
		for(it2= control->iteratorBeginListOfMails(); it2 != control->iteratorEndListOfMails(); it2++){
			(*it2)->print(cout);
		}

}

int main (int argc,char** argv){

	//----- ./Aplicacion -c email pass
	//----- ./Aplicacion -f stringAbuscar
	//----- ./Application -si email TYPE_CLASSIFICATION/TYPE_SELECTION CONDITION (VALOR) filterName
	//----- ./Application -li filterName
		Controller* control = new Controller();

		/*Analisis de argumentos*/
		if(argc>1){
		if (strcmp(argv[1],"-c")==0){
			std::string strEmail(argv[2]);
			std::string strPass(argv[3]);
			control->addEmail(strEmail);
			control->addPass(strPass);
			control->createPrimaryIndex();

		}else if (strcmp(argv[1],"-f")==0){
			std::string strSearch(argv[2]);
			control->searchMails(strSearch);
			printResult(control);
		}else if (strcmp(argv[1],"-si")==0){
			IndexConfig* configOne = new IndexConfig();
			std::string strEmail(argv[2]);
			configOne->setUserName(strEmail);
			configOne->setTypeIndex("Secundario");
			std::string typeSecondaryIndex(argv[3]);
			configOne->setTypeSecundaryIndex(typeSecondaryIndex);
			configOne->setCondition(atoi(argv[4]));
			if(typeSecondaryIndex.compare("Clasificacion") == 0){
				std::string filterName(argv[5]);
				configOne->setFilterName(filterName);
				configOne->print();////////////////////////////print

			}else if(typeSecondaryIndex.compare("Seleccion") == 0){
				std::string value(argv[5]);
				configOne->setValue(value);
				std::string filterName(argv[6]);
				configOne->setFilterName(filterName);
			}
			control->addSecondIndex(configOne);

		}else if (strcmp(argv[1],"-li")==0){
			IndexConfig* configOne = new IndexConfig();
			std::string index(argv[2]);
			configOne = control->loadIndexConfig(index);

			control->loadSecondIndex(configOne);


		}else {
				puts("Argumentos invalidos");
			delete control;
			return EXIT_SUCCESS;
		}
		cout<<"Salida exitosa"<<endl;
		delete control;
		return EXIT_SUCCESS;
	}

		delete control;
		return 0;


		//*****SE CONECTA Y CREA INDICE PRIMARIO***
		/*	std::string strEmail = "Datos.2c2010";
			std::string strPass = "75067506";
			Controller* control= new Controller();*/
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
		/*	//Controller* control= new Controller();
			cout<<"------------------------------------------------------------------------------------------"<<endl;
			control->searchMails("[Seleccion1= ]");

			list<int>::iterator it;
			for(it= control->iteratorBeginListOfIucs(); it != control->iteratorEndListOfIucs(); it++){
				cout<<"IUC: "<<*it<<endl;
			}
		cout<<"salio con cantidad de resultados: "<< control->getListOfIUCS().size() <<endl;*/
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

		//	delete control;

}
