/*
 * IndexController.h
 *
 *  Created on: 25/09/2010
 *      Author: richy
 */

#ifndef INDEXCONTROLLER_H_
#define INDEXCONTROLLER_H_

#include "../src.datos.BTreeSharp/IndexBSharp.h"
#include <list>
class IndexController {
public:
	IndexController();
	virtual ~IndexController();
};

void generatePrimaryIndex(list<Mail*> mailList);
void generateClassificationIndex(IndexBSharp* primaryIndex,int condition); //estan todos los del primario. tengo q saber atributo  (CONSTANTE)
void generateSelectionIndex(IndexBSharp* primaryIndex,int condition, string value); //existen menos q en el primario.......tengo q saber atributo y valor, (CONSTANTE,VALOR)

#endif /* INDEXCONTROLLER_H_ */
