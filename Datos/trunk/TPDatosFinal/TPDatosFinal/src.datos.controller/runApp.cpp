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

void calculateIntersection(unsigned int numSearchs, list<int>* listIucs){
	list<int>::iterator it;
	list<int>::iterator itAux;
	list<int>::iterator itAux2;
	bool halt;
	list<int> finalList;
	unsigned int count;
	//cout<<"numSearchs: "<<numSearchs<<endl;
	(*listIucs).sort();
//	cout<<"IUC: ";
//	for(it= (*listIucs).begin(); it != (*listIucs).end(); it++){
//						cout<<*it<<", ";
//		}
//	cout<<endl;
	for(it = (*listIucs).begin(); it != (*listIucs).end(); it++){
		halt = false;
		itAux2 = it;
		itAux2++;
		count = 1;
		for(itAux = itAux2; ((itAux != (*listIucs).end())&& !halt); itAux++){
			if(*it == *itAux){
				count++;
			}
			else{
				if(count == numSearchs){
					finalList.push_back(*it);
				}
				halt = true;
			}
		}
	}

	(*listIucs).clear();
	(*listIucs).merge(finalList);

}

void printResult(Controller* control){

	list<int>::iterator it;
	unsigned int numSearchs = control->getSearch()->getNumOfIndex();
	if (numSearchs > 1)
		calculateIntersection(numSearchs, control->getListOfIucs());
		//cout<< "RESULTADO "<<endl;

		for(it= control->iteratorBeginListOfIucs(); it != control->iteratorEndListOfIucs(); it++){
			cout<<"IUC: "<<*it<<endl;
		}

		list<Mail*>::iterator it2;
		for(it2= control->iteratorBeginListOfMails(); it2 != control->iteratorEndListOfMails(); it2++){
			(*it2)->print(cout);
		}

}


int mainfghfghfghfgh(int argc,char** argv){

	//----- ./Aplicacion -c
	//----- ./Aplicacion -f stringAbuscar
	//----- ./Application -si email TYPE_CLASSIFICATION/TYPE_SELECTION CONDITION (VALOR) filterName
	//----- ./Application -li filterName

	std::string userMail;
	std::string userPass;

	if(strcmp(argv[1],"-t") != 0){//Si el comando no es el de test, pide usuario y pass

		std::cout << "Ingrese su cuenta de correo: ";
		std::cin >> userMail;
		std::cout << "Ingrese su contraseña: ";
		std::cin >> userPass;


	}else{
		userMail = "Test";
		userPass = "pass";

	}


	Controller* control = new Controller(userMail,userPass);

		/*Analisis de argumentos*/
		if(argc>1){
		if ((strcmp(argv[1],"-c")==0) && (argc == 2)){
			control->createPrimaryIndex();
		}else if ((strcmp(argv[1],"-f") == 0) && (argc == 3)){
			std::string strSearch(argv[2]);
			control->searchMails(strSearch);
			printResult(control);
		}else if((strcmp(argv[1],"-d") == 0) && (argc == 3)){
			int iuc = atoi(argv[2]);
			control->deleteIuc(iuc);
		}else if (strcmp(argv[1],"-si") == 0 && (argc > 3)){
			IndexConfig* configOne = new IndexConfig();
			configOne->setUserName(userMail);
			configOne->setTypeIndex("Secundario");
			std::string typeSecondaryIndex(argv[2]);
			configOne->setTypeSecundaryIndex(typeSecondaryIndex);
			configOne->setCondition(atoi(argv[3]));
			if((typeSecondaryIndex.compare("Clasificacion") == 0 ) && (argc == 5)){
				std::string filterName(argv[4]);
				configOne->setFilterName(filterName);
			}else if((typeSecondaryIndex.compare("Seleccion") == 0) && (argc == 6)){
				std::string value(argv[4]);
				configOne->setValue(value);
				std::string filterName(argv[5]);
				configOne->setFilterName(filterName);
			}
			else if(typeSecondaryIndex.compare("Invertido") == 0){
				std::string filterName(argv[3]);
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
				cout<<"*******************Creando indice primario...PrimarioTest"<<endl<<endl;
				control->createPrimaryIndex();
				cout<<"*******************Indice primario creado exitosamente..."<<endl<<endl;

				cout<<"*******************Creando y cargando indice secundario de seleccion...SEL_TEST  filtro FROM=michael.richters@gmail.com"<<endl<<endl;
				IndexConfig* configSelection = new IndexConfig();
				IndexConfig* config;
				configSelection->setUserName(userMail);
				configSelection->setTypeIndex("Secundario");
				configSelection->setTypeSecundaryIndex("Seleccion");
				configSelection->setCondition(1);
				configSelection->setValue("michael.richters@gmail.com");
				configSelection->setFilterName("SEL_TEST");
				control->addSecondIndex(configSelection);
				config = control->loadIndexConfig("SEL_TEST");
				control->loadSecondIndex(config);
				cout<<"*******************Indice secundario de seleccion creado exitosamente..."<<endl<<endl;

				cout<<"*******************Creando indice secundario de clasificacion...CLAS_TEST"<<endl<<endl;
				IndexConfig* configClasification = new IndexConfig();
				configClasification->setUserName(userMail);
				configClasification->setTypeIndex("Secundario");
				configClasification->setTypeSecundaryIndex("Clasificacion");
				configClasification->setCondition(1);
				configClasification->setFilterName("CLAS_TEST");
				control->addSecondIndex(configClasification);
				config = control->loadIndexConfig("CLAS_TEST");
				control->loadSecondIndex(config);
				cout<<"*******************Indice secundario de clasificacion creado exitosamente..."<<endl<<endl;

				cout<<"*******************Creando indice invertido...INV_TEST"<<endl<<endl;
				IndexConfig* configInvert = new IndexConfig();
				configInvert->setUserName(userMail);
				configInvert->setTypeIndex("Secundario");
				configInvert->setTypeSecundaryIndex("Invertido");
				configInvert->setFilterName("INV_TEST");
				control->addSecondIndex(configInvert);
				config = control->loadIndexConfig("INV_TEST");
				control->loadSecondIndex(config);
				cout<<"*******************Indice secundario de clasificacion creado exitosamente..."<<endl<<endl;

				cout<<"*******************Busqueda sobre primario...-f [PrimarioTest=3,10,15,20]"<<endl;
				string parameters = "[PrimarioTest=3,10,15,20]";
				control->searchMails(parameters);
				list<Mail*>::iterator itPrimary;
				for(itPrimary= control->iteratorBeginListOfMails(); itPrimary != control->iteratorEndListOfMails(); itPrimary++){
					(*itPrimary)->print(cout);
				}
				cout<<"*******************Fin busqueda..."<<endl<<endl;

				cout<<"*******************Busqueda sobre secundario seleccion...-f [SEL_TEST=]..."<<endl<<endl;
				control->searchMails("[SEL_TEST=]");

				list<int>::iterator it;
				for(it= control->iteratorBeginListOfIucs(); it != control->iteratorEndListOfIucs(); it++){
					cout<<"IUC: "<<*it<<endl;
				}
				cout<<"*******************Fin busqueda..."<<endl<<endl;

				control->clearListsIucs();
				cout<<"*******************Busqueda sobre secundario clasificacion...-f [CLAS_TEST=michael.richters@gmail.com]"<<endl;
				control->searchMails("[CLAS_TEST=michael.richters@gmail.com]");

				list<int>::iterator it2;
				for(it2= control->iteratorBeginListOfIucs(); it2 != control->iteratorEndListOfIucs(); it2++){
					cout<<"IUC: "<<*it2<<endl;
				}
				cout<<"*******************Fin busqueda..."<<endl<<endl;

				control->clearListsIucs();
				cout<<"*******************Busqueda sobre invertido...-f [INV_TEST=UNIX sigue siendo un fenómeno]"<<endl;
				control->searchMails("[INV_TEST=UNIX sigue siendo un fenómeno]");

				list<int>::iterator it3;
				for(it3= control->iteratorBeginListOfIucs(); it3 != control->iteratorEndListOfIucs(); it3++){
					cout<<"IUC: "<<*it3<<endl;
				}
				cout<<"*******************Fin busqueda..."<<endl<<endl;

				control->clearListsIucs();
				cout<<"*******************Busqueda compuesta...-f [INV_TEST=el hardware y el software][SEL_TEST=][CLAS_TEST=michael.richters@gmail.com]"<<endl;
				control->searchMails("[INV_TEST=el hardware y el software][SEL_TEST=][CLAS_TEST=michael.richters@gmail.com]");
				calculateIntersection(3,control->getListOfIucs());
				list<int>::iterator it4;
				for(it4= control->iteratorBeginListOfIucs(); it4 != control->iteratorEndListOfIucs(); it4++){
					cout<<"IUC: "<<*it4<<endl;
				}
				cout<<"*******************Fin busqueda..."<<endl<<endl;


				cout<<"*******************Borrar mail... -d 2"<<endl<<endl;
				control->deleteIuc(2);
				cout<<"*******************Fin Borrar mail..."<<endl<<endl;

				cout<<"*******************Borrar mail... -d 8"<<endl<<endl;
				control->deleteIuc(8);
				cout<<"*******************Fin Borrar mail..."<<endl<<endl;

				cout<<"*******************Borrar mail... -d 20"<<endl<<endl;
				control->deleteIuc(20);
				cout<<"*******************Fin Borrar mail..."<<endl<<endl;




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
