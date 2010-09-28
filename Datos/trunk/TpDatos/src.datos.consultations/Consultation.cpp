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
void Consultation::consultPrimaryIndex(IndexConfig* indexConfig,list<int> IucList,list<Mail*>* listOfMails){
	IndexBSharp* primaryIndex = new IndexBSharp(indexConfig->getFileName(),indexConfig->getBlockSize(),TYPE_REG_PRIMARY);
	IteratorBSharp* iter = primaryIndex->getIterator();

	while(iter->hasNext())
		(*listOfMails).push_back((Mail*)(iter->next()));

	delete primaryIndex;

}

void Consultation::consultSecondaryIndex(IndexConfig* indexConfig,list<int>* listOfIucs){
	IteratorBSharp* iter;
	IndexBSharp* secondaryIndex;
	RegClassification* regClassification;
	RegSelection* regSelection;

	if(indexConfig->getTypeSecundaryIndex().compare((char*)TYPE_SELECTION) == 0){
		secondaryIndex = new IndexBSharp(indexConfig->getFileName(),BLOCK_SIZE/*TODO indexConfig->getBlockSize()*/,TYPE_REG_SELECTION);
		iter = secondaryIndex->getIterator();
		while(iter->hasNext()){
			regSelection = 	(RegSelection*) iter->next();
			(*listOfIucs).push_back(((KeyInteger*)(regSelection->getKey()))->getValue());
		}

	}
	else{
		secondaryIndex = new IndexBSharp(indexConfig->getFileName(),BLOCK_SIZE/*TODO indexConfig->getBlockSize()*/,TYPE_REG_CLASSIFICATION);
		iter = secondaryIndex->getIterator();
		while(iter->hasNext()){
			regClassification = (RegClassification*)iter->next();
			(*listOfIucs).push_back(regClassification->getIuc()->getValue());
		}
	}

	delete secondaryIndex;
	delete iter;

}
