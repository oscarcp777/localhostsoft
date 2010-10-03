/*
 * Consultation.cpp
 *
 *  Created on: 28/09/2010
 *      Author: richy
 */

#include "Consultation.h"
#include "../src.datos.BTreeSharp/IteratorBSharp.h"
#include "../src.datos.BTreeSharp/IndexBSharp.h"
#include "../src.datos.models/KeyString.h"
#include "../src.datos.models/KeyInteger.h"
#include "../src.datos.models/RegSelection.h"
#include "../src.datos.models/RegClassification.h"

Consultation::Consultation() {
	// TODO Auto-generated constructor stub

}

Consultation::~Consultation() {
	// TODO Auto-generated destructor stub
}
void Consultation::consultPrimaryIndex(IndexConfig* indexConfig,RegPrimary* regPrimary){
	IndexBSharp* primaryIndex = new IndexBSharp(PATHFILES+indexConfig->getFileName(),indexConfig->getBlockSize(),TYPE_REG_PRIMARY);
	regPrimary = (RegPrimary*) primaryIndex->searchRegistry(regPrimary);
	delete primaryIndex;
}

void Consultation::consultSecondaryIndex(IndexConfig* indexConfig,list<int>* listOfIucs, string filterValue){
	IteratorBSharp* iter;
	IndexBSharp* secondaryIndex;
	RegSelection* regSelection;

	if(indexConfig->getTypeSecundaryIndex().compare((char*)TYPE_SELECTION) == 0){
		secondaryIndex = new IndexBSharp(PATHFILES+indexConfig->getFileName(),BLOCK_SIZE/*TODO indexConfig->getBlockSize()*/,TYPE_REG_SELECTION);
		iter = secondaryIndex->getIterator();
		while(iter->hasNext()){
			regSelection = 	(RegSelection*) iter->next();
			(*listOfIucs).push_back(((KeyInteger*)(regSelection->getKey()))->getValue());
		}
		delete iter;

	}
	else{
		secondaryIndex = new IndexBSharp(PATHFILES+indexConfig->getFileName(),BLOCK_SIZE/*TODO indexConfig->getBlockSize()*/,TYPE_REG_CLASSIFICATION);
		RegClassification* searchReg = new RegClassification();
		RegClassification* resultReg;
		searchReg->setKey(new KeyString(filterValue));
		resultReg = (RegClassification*)secondaryIndex->searchRegistry(searchReg);
		list<KeyInteger* > auxList = searchReg->getIucs();
		list<KeyInteger*>::iterator actual;
		for (actual = auxList.begin(); actual	!= auxList.end(); ++actual){
			(*listOfIucs).push_back((*actual)->getValue());
		}
		delete searchReg;
		delete resultReg;
	}

	delete secondaryIndex;
	

}
