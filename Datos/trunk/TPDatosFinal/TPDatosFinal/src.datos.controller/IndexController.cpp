/*
 * IndexController.cpp
 *
 *  Created on: 25/09/2010
 *      Author: richy
 */

#include "IndexController.h"
#include "../src.datos.utils/Define.h"
#include "../src.datos.utils/StringUtils.h"
#include "../src.datos.BTreeSharp/IndexBSharp.h"


IndexController::IndexController() {
	// TODO Auto-generated constructor stub

}

IndexController::~IndexController() {
	// TODO Auto-generated destructor stub
}


void IndexController::generateClassificationIndex(IndexConfig* indexConfig){
	//estan todos los del primario. tengo q saber atributo  (CONSTANTE)
	string fileName = indexConfig->getFilterName();
	fileName += ".IndSecundario.Clasificacion."+StringUtils::convertConditionIntToString(indexConfig->getCondition());
	IndexBSharp* primaryIndex = new IndexBSharp(PATHFILES+fileName,BLOCK_SIZE,TYPE_REG_CLASSIFICATION);
	indexConfig->setBlockSize(BLOCK_SIZE);
	indexConfig->setFileName(fileName);
	delete primaryIndex;
}
void IndexController::generateSelectionIndex(IndexConfig* indexConfig){
	//existen menos q en el primario.......tengo q saber atributo y valor, (CONSTANTE,VALOR)
	string fileName = indexConfig->getFilterName();
	fileName += ".IndSecundario.Seleccion."+StringUtils::convertConditionIntToString(indexConfig->getCondition())+"."+indexConfig->getValue();
	IndexBSharp* primaryIndex = new IndexBSharp(PATHFILES+fileName,BLOCK_SIZE,TYPE_REG_SELECTION);
	indexConfig->setBlockSize(BLOCK_SIZE);
	indexConfig->setFileName(fileName);
	delete primaryIndex;

}

void IndexController::generateInvertedIndex(IndexConfig* indexConfig){
	string fileName = indexConfig->getFilterName();
	fileName += ".IndSecundario.Invertido";
	IndexBSharp* primaryIndex = new IndexBSharp(PATHFILES+fileName,BLOCK_SIZE,TYPE_REG_INVERTED_INDEX);
	indexConfig->setBlockSize(BLOCK_SIZE);
	indexConfig->setFileName(fileName);
	delete primaryIndex;
}
void IndexController::generateSecondaryIndex(IndexBSharp* primaryIndex,IndexConfig* indexConfig){

	if(indexConfig->getTypeSecundaryIndex().compare((char*)TYPE_CLASSIFICATION) == 0)
		this->generateClassificationIndex(indexConfig);

	else if(indexConfig->getTypeSecundaryIndex().compare((char*)TYPE_SELECTION) == 0)
		this->generateSelectionIndex(indexConfig);

	else if(indexConfig->getTypeSecundaryIndex().compare((char*)TYPE_INVERTED_INDEX) == 0)
			this->generateInvertedIndex(indexConfig);
}


