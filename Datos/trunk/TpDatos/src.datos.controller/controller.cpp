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
	std::string strEmail;
	std::string strPass;
	std::cout << "llegue ";
	Controller control;
	std::cout << "INGRESE SU DIRECCION DE E-MAIL: ";
	std::cin >> strEmail;
	control.addEmail(strEmail);
	std::cout << "INGRESE SU PASSWORD: ";
	std::cin >> strPass;
	control.addPass(strPass);
	IndexConfig* index = new IndexConfig();
	index->setFileName("prueba.dat");
	index->setUserName("prueba@hotmail.com");
	index->setTypeIndex("primario");
//	index->setTypeSecundaryIndex("seleccion");
//	index->setCondition(2);
//	index->setValue("ale");
	control.addIndexToFile(index);
	control.printIndexNames();
	control.parseStrSearch("[calsificacion1= ][clasificacion2=para][clasificacion3=2,3,4,5]");


	return 0;
}
