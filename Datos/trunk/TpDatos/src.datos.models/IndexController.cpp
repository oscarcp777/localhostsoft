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

IndexConfig* IndexController::generateClassificationIndex(char* userName, int condition){
	//estan todos los del primario. tengo q saber atributo  (CONSTANTE)
	IndexConfig* config = new IndexConfig();
	string fileName = userName;
	fileName += ".IndSecundario.Clasificacion."+StringUtils::convertConditionIntToString(condition);
	IndexBSharp* primaryIndex = new IndexBSharp(fileName,BLOCK_SIZE,TYPE_REG_CLASSIFICATION);
	config->setBlockSize(BLOCK_SIZE);
	config->setFileName(fileName);
	config->setTypeIndex(TYPE_SECONDARY);
	config->setTypeSecundaryIndex(TYPE_CLASSIFICATION);
	config->setCondition(condition);
	delete primaryIndex;
	return config;
}
IndexConfig* IndexController::generateSelectionIndex(char* userName,int condition, string value){
	//existen menos q en el primario.......tengo q saber atributo y valor, (CONSTANTE,VALOR)
	IndexConfig* config = new IndexConfig();
	string fileName = userName;
	fileName += ".IndSecundario.Seleccion."+StringUtils::convertConditionIntToString(condition)+"."+value;
	IndexBSharp* primaryIndex = new IndexBSharp(fileName,BLOCK_SIZE,TYPE_REG_KEY_SELECTION);
	config->setBlockSize(BLOCK_SIZE);
	config->setFileName(fileName);
	config->setTypeIndex(TYPE_SECONDARY);
	config->setTypeSecundaryIndex(TYPE_SELECTION);
	config->setCondition(condition);
	config->setValue(value);
	delete primaryIndex;
	return config;

}
