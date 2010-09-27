/*
 * Classification.cpp
 *
 *  Created on: 26/09/2010
 *      Author: richy
 */

#include "Classification.h"
#include "../src.datos.utils/Define.h"
#include "../src.datos.BTreeSharp/IndexBSharp.h"
#include "../src.datos.models/RegPrimary.h"
#include "../src.datos.models/RegClassification.h"
#include "../src.datos.models/KeyInteger.h"
#include "../src.datos.models/KeyString.h"
#include "../src.datos.models/RegSelection.h"
#include "../src.datos.utils/StringUtils.h"


Classification::Classification() {
	// TODO Auto-generated constructor stub

}

Classification::~Classification() {
	// TODO Auto-generated destructor stub
}
void Classification::loadSecondaryIndex(IndexConfig* indexConfig, IteratorBSharp* it){
	if(indexConfig->getTypeSecundaryIndex().compare((char*)TYPE_CLASSIFICATION) == 0)
				this->loadClassificationIndex(indexConfig,it);

			else if(indexConfig->getTypeSecundaryIndex().compare((char*)TYPE_SELECTION) == 0)
				this->loadSelectionIndex(indexConfig,it);
}
void Classification::loadClassificationIndex(IndexConfig* indexConfig,IteratorBSharp* it){
	IndexBSharp* secondaryIndex = new IndexBSharp(indexConfig->getFileName(),indexConfig->getBlockSize(),TYPE_REG_CLASSIFICATION);
	RegPrimary* regPrimary;
	RegClassification* regClassification;
	KeyString* key;
	int condition = indexConfig->getCondition();
	string value = indexConfig->getValue();



	while (it->hasNext()){
		regPrimary = (RegPrimary*)it->next();
		if(regPrimary->getMail()->containCondition(condition,value)){
			regClassification = new RegClassification();
			key = new KeyString(value);
			regClassification->setKey(key);
			regClassification->addIuc((KeyInteger*)regPrimary->getMail()->getKey()->clone());
			secondaryIndex->addRegistry(regClassification);
		}
	}
	delete secondaryIndex;
	delete it;
}
void Classification::loadSelectionIndex(IndexConfig* indexConfig,IteratorBSharp* it){
	IndexBSharp* secondaryIndex = new IndexBSharp(indexConfig->getFileName(),indexConfig->getBlockSize(),TYPE_REG_SELECTION);
	RegPrimary* regPrimary;
	RegSelection* regSelection;
	int condition = indexConfig->getCondition();
	string value = indexConfig->getValue();
	cout<<"condition: "<<condition<<endl;
	cout<<"value: "<<value<<endl;

	while (it->hasNext()){
		regPrimary = (RegPrimary*)it->next();
		if(regPrimary->getMail()->containCondition(condition,value)){
			cout<<"ENTRO*******************************************"<<endl;
			regSelection = new RegSelection();
			regSelection->setKey((Key*)regPrimary->getMail()->getKey()->clone());
			secondaryIndex->addRegistry(regSelection);
		}
	}
	secondaryIndex->print(std::cout);
	delete secondaryIndex;
	delete it;
}
