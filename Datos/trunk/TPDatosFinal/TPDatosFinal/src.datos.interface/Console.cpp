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

void printResult245(Controller* control){

		list<int>::iterator it;
		for(it= control->iteratorBeginListOfIucs(); it != control->iteratorEndListOfIucs(); it++){
			cout<<"IUC: "<<*it<<endl;
		}

		list<Mail*>::iterator it2;
		for(it2= control->iteratorBeginListOfMails(); it2 != control->iteratorEndListOfMails(); it2++){
			(*it2)->print(cout);
		}

}

int main12345678(int argc,char** argv){

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
			printResult245(control);
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
			configOne->print();//////////////////////////////////print
		}else if (strcmp(argv[1],"-li")==0){
			IndexConfig* configOne = new IndexConfig();
			std::string index(argv[2]);
			configOne = control->loadIndexConfig(index);
			configOne->print();//////////////////////////////////print
			control->loadSecondIndex(configOne);


		}else {
				puts("Argumentos invalidos");
			return EXIT_SUCCESS;
		}
		cout<<"Salida exitosa"<<endl;
		return EXIT_SUCCESS;
	}




	return 0;
}
