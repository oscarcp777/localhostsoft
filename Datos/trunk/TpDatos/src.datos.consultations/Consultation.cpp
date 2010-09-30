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

void Consultation::consultSecondaryIndex(IndexConfig* indexConfig,list<int>* listOfIucs, string filterValue){
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
		delete iter;

	}
	else{
		secondaryIndex = new IndexBSharp(indexConfig->getFileName(),BLOCK_SIZE/*TODO indexConfig->getBlockSize()*/,TYPE_REG_CLASSIFICATION);
		RegClassification* searchReg = new RegClassification();
		searchReg->setKey(new KeyString(filterValue));
		searchReg = (RegClassification*)secondaryIndex->searchRegistry(searchReg);
		list<KeyInteger* > auxList = searchReg->getIucs();
		list<KeyInteger*>::iterator actual;
		for (actual = auxList.begin(); actual	!= auxList.end(); ++actual){
			(*listOfIucs).push_back((*actual)->getValue());
		}


		//Esto es para chequear el arbol (print arbol de clasif.pero algo no anda)
//		iter = secondaryIndex->getIterator();
//		while(iter->hasNext()){
//			RegClassification* regC =(RegClassification*) iter->next();
//			regC->print(cout);
//			for (actual = regC->getIucs().begin(); actual	!= regC->getIucs().end(); ++actual){
//						std::cout << "IUC: "<<(*actual)->getValue();
//			}
//			std::cout<<std::endl;
//		}
//		delete iter;
	}

	delete secondaryIndex;

}
