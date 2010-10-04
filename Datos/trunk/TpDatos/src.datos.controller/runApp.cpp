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


int main(int argc,char** argv){

	//----- ./Aplicacion -c email pass
	//----- ./Aplicacion -f stringAbuscar
	//----- ./Application -si email TYPE_CLASSIFICATION/TYPE_SELECTION CONDITION (VALOR) filterName
	//----- ./Application -li filterName
		Controller* control = new Controller();

		/*Analisis de argumentos*/
		if(argc>1){
		if ((strcmp(argv[1],"-c")==0) && (argc == 4)){
			std::string strPass = argv[3];
			std::string strEmail = argv[2];
			control->addEmail(strEmail);
			control->addPass(strPass);
			control->createPrimaryIndex();

		}else if ((strcmp(argv[1],"-f") == 0) && (argc == 3)){
			std::string strSearch(argv[2]);
			control->searchMails(strSearch);
			printResult(control);
		}else if (strcmp(argv[1],"-si") == 0 && (argc > 4)){
			IndexConfig* configOne = new IndexConfig();
			std::string strEmail(argv[2]);
			configOne->setUserName(strEmail);
			configOne->setTypeIndex("Secundario");
			std::string typeSecondaryIndex(argv[3]);
			configOne->setTypeSecundaryIndex(typeSecondaryIndex);
			configOne->setCondition(atoi(argv[4]));
			if((typeSecondaryIndex.compare("Clasificacion") == 0 ) && (argc == 6)){
				std::string filterName(argv[5]);
				configOne->setFilterName(filterName);
				//configOne->print();////////////////////////////print

			}else if((typeSecondaryIndex.compare("Seleccion") == 0) && (argc == 7)){
				std::string value(argv[5]);
				configOne->setValue(value);
				std::string filterName(argv[6]);
				configOne->setFilterName(filterName);
			}
			control->addSecondIndex(configOne);
		}else if ((strcmp(argv[1],"-li")==0 )&& (argc == 3)){
			IndexConfig* configOne;
			std::string index(argv[2]);
			configOne = control->loadIndexConfig(index);
			control->loadSecondIndex(configOne);


		}else if((strcmp(argv[1],"-t")==0) && (argc == 2 )){
			if(CONNECT == 0){
				cout<<"Creando indice primario...PrimarioTest"<<endl;
				std::string strPass = "pass";
				std::string strEmail = "Test";
				control->addEmail(strEmail);
				control->addPass(strPass);
				control->createPrimaryIndex();
				cout<<"Indice primario creado exitosamente..."<<endl;

				cout<<"Creando y cargando indice secundario de seleccion...SEL_TEST"<<endl;
				IndexConfig* configSelection = new IndexConfig();
				IndexConfig* config;
				configSelection->setUserName(strEmail);
				configSelection->setTypeIndex("Secundario");
				configSelection->setTypeSecundaryIndex("Seleccion");
				configSelection->setCondition(1);
				configSelection->setValue("michael.richters@gmail.com");
				configSelection->setFilterName("SEL_TEST");
				control->addSecondIndex(configSelection);
				config = control->loadIndexConfig("SEL_TEST");
				control->loadSecondIndex(config);
				cout<<"Indice secundario de seleccion creado exitosamente..."<<endl;

				cout<<"Creando indice secundario de clasificacion...CLAS_TEST"<<endl;
				IndexConfig* configClasification = new IndexConfig();
				configClasification->setUserName(strEmail);
				configClasification->setTypeIndex("Secundario");
				configClasification->setTypeSecundaryIndex("Clasificacion");
				configClasification->setCondition(1);
				configClasification->setFilterName("CLAS_TEST");
				control->addSecondIndex(configClasification);
				config = control->loadIndexConfig("CLAS_TEST");
				control->loadSecondIndex(config);
				cout<<"Indice secundario de clasificacion creado exitosamente..."<<endl;


				cout<<"Busqueda sobre primario...[PrimarioTest=5,6,11]"<<endl;
				string parameters = "[PrimarioTest=5,6,11]";
				control->searchMails(parameters);
				list<Mail*>::iterator itPrimary;
				for(itPrimary= control->iteratorBeginListOfMails(); itPrimary != control->iteratorEndListOfMails(); itPrimary++){
					(*itPrimary)->print(cout);
				}
				cout<<"Fin busqueda..."<<endl;

				cout<<"Busqueda sobre secundario seleccion...[SEL_TEST=]..."<<endl;
				control->searchMails("[SEL_TEST=]");

				list<int>::iterator it;
				for(it= control->iteratorBeginListOfIucs(); it != control->iteratorEndListOfIucs(); it++){
					cout<<"IUC: "<<*it<<endl;
				}
				cout<<"Fin busqueda..."<<endl;

				control->clearListsIucs();
				cout<<"Busqueda sobre secundario clasificacion... [CLAS_TEST=michael.richters@gmail.com]"<<endl;
				control->searchMails("[CLAS_TEST=michael.richters@gmail.com]");

				list<int>::iterator it2;
				for(it2= control->iteratorBeginListOfIucs(); it2 != control->iteratorEndListOfIucs(); it2++){
					cout<<"IUC: "<<*it2<<endl;
				}
				cout<<"Fin busqueda..."<<endl;

			}
		}else{
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

}
