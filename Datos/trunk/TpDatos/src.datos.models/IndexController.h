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
#include "../src.datos.BTreeSharp/IndexBSharp.h"

class IndexController {
public:
	IndexController();
	virtual ~IndexController();
	void generateClassificationIndex(IndexConfig* indexConfig); //estan todos los del primario. tengo q saber atributo  (CONSTANTE)
	void generateSelectionIndex(IndexConfig* indexConfig); //existen menos q en el primario.......tengo q saber atributo y valor, (CONSTANTE,VALOR)
	void generateSecondaryIndex(IndexBSharp* primaryIndex,IndexConfig* indexConfig);
};

#endif /* INDEXCONTROLLER_H_ */
