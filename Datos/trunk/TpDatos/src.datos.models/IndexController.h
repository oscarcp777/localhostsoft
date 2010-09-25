/*
 * IndexController.h
 *
 *  Created on: 25/09/2010
 *      Author: richy
 */

#ifndef INDEXCONTROLLER_H_
#define INDEXCONTROLLER_H_
#include <string>
#include "../src.datos.models/IndexConfig.h"

class IndexController {
public:
	IndexController();
	virtual ~IndexController();
	IndexConfig* generateClassificationIndex(char* userName,int condition); //estan todos los del primario. tengo q saber atributo  (CONSTANTE)
	IndexConfig* generateSelectionIndex(char* userName, int condition, std::string value); //existen menos q en el primario.......tengo q saber atributo y valor, (CONSTANTE,VALOR)

};

#endif /* INDEXCONTROLLER_H_ */
