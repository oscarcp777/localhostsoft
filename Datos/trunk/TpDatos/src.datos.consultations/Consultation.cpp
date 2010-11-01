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
#include "../src.datos.utils/StringUtils.h"
#include "../src.datos.controller/ManagerInvertedIndex.h"

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
	if(indexConfig->getTypeSecundaryIndex().compare(TYPE_INVERTED_INDEX) == 0){
			secondaryIndex = new IndexBSharp(PATHFILES+indexConfig->getFileName(),BLOCK_SIZE/*TODO indexConfig->getBlockSize()*/,TYPE_REG_INVERTED_INDEX);
			ManagerInvertedIndex* managerInvertedIndex = new ManagerInvertedIndex();
			vector<string> words;
			vector<string>::iterator itWords;
			filterValue = StringUtils::toUpper(filterValue);
			StringUtils::Tokenize(filterValue,words," ");
			managerInvertedIndex->removeStopWordsFromVector(&words);
			list<RegInvertedIndex*> listRegInvInd;
			RegInvertedIndex* reg = NULL;
			//cout<<"consulta sin stopWords: "<<endl;
//			for(itWords = words.begin(); itWords != words.end(); itWords++){
//				cout<<*itWords<<" ";
//			}
//			cout<<endl;
			for(itWords = words.begin(); itWords != words.end(); itWords++){
				RegInvertedIndex* regInvertedIndex= new RegInvertedIndex();
				regInvertedIndex->setKey(new KeyString(*itWords));
				reg = (RegInvertedIndex*)secondaryIndex->searchRegistry(regInvertedIndex);
				if(reg != NULL)
					listRegInvInd.push_back(reg);
			}
			if(listRegInvInd.size() == words.size()){
			//la cantidad de terminos de la consulta tiene q ser igual a los Reg encontrados (es una condicion necesaria) sino no esta la frase
				this->compareConsultResaults(listRegInvInd,listOfIucs);
			}


			delete managerInvertedIndex;
	}
	else if (indexConfig->getTypeSecundaryIndex().compare(TYPE_CLASSIFICATION) == 0){
		secondaryIndex = new IndexBSharp(PATHFILES+indexConfig->getFileName(),BLOCK_SIZE/*TODO indexConfig->getBlockSize()*/,TYPE_REG_CLASSIFICATION);
		RegClassification* searchReg = new RegClassification();
		searchReg->setKey(new KeyString(filterValue));
		searchReg = (RegClassification*)secondaryIndex->searchRegistry(searchReg);
		list<KeyInteger* > auxList = searchReg->getIucs();
		list<KeyInteger*>::iterator actual;
		for (actual = auxList.begin(); actual	!= auxList.end(); ++actual){
			(*listOfIucs).push_back((*actual)->getValue());
		}
		delete searchReg;
	}

	delete secondaryIndex;
	

}
void Consultation::compareConsultResaults(list<RegInvertedIndex*> listRegInvInd,list<int>* listOfIucs){

	list<RegInvertedIndex*>::iterator it;
	list<RegInvertedIndex*>::iterator itSecondary;
	list<InfoPerDoc*>::iterator itInfoPerDoc;
	list<InfoPerDoc*>::iterator lastInfoPerDoc;
	list<InfoPerDoc*>::iterator auxIt;
	list<InfoPerDoc*>::iterator itInfoPerDocSecondary;
	list<int> intersectionIucs;
	list<int>::iterator itNum;
	list<InfoPerDoc*> sameIucInfoPerDoc;
	bool posibleMatch = true;
	bool correctDistances = true;
	//primero hago la interseccion, es decir busco q documentos contienen todos los terminos
	it = listRegInvInd.begin();
		for(itInfoPerDoc =(*it)->getBeginListInfoPerDoc(); itInfoPerDoc != (*it)->getEndListInfoPerDoc(); itInfoPerDoc++){
			posibleMatch = true;

			for (itSecondary = ++listRegInvInd.begin(); (itSecondary != listRegInvInd.end()) && posibleMatch; itSecondary++){
				posibleMatch = false;

				for(itInfoPerDocSecondary = (*itSecondary)->getBeginListInfoPerDoc(); itInfoPerDocSecondary != (*itSecondary)->getEndListInfoPerDoc(); itInfoPerDocSecondary++){

					if((*itInfoPerDoc)->getKey()->compareTo((*itInfoPerDocSecondary)->getKey()) == 0)
						posibleMatch = true;

				}
			}
			if(posibleMatch){
				//cout<<"el IUC: "<<((KeyInteger*)(*itInfoPerDoc)->getKey())->getValue()<<" es candidato"<<endl;
				intersectionIucs.push_back(((KeyInteger*)(*itInfoPerDoc)->getKey())->getValue());
			}
		}

	//verificar las distancias, primero obtengo una lista de infoPerDoc q contenga todos los
	// infoPerDoc con el mismo iuc (de los q dieron en la interseccion), para cada IUC y despues verifico las distancias
	for(itNum = intersectionIucs.begin(); itNum != intersectionIucs.end(); itNum++){
		sameIucInfoPerDoc.clear();
		for(it = listRegInvInd.begin(); it != listRegInvInd.end(); it++){
			for(itInfoPerDoc =(*it)->getBeginListInfoPerDoc(); itInfoPerDoc != (*it)->getEndListInfoPerDoc(); itInfoPerDoc++){
				if(((KeyInteger*)(*itInfoPerDoc)->getKey())->getValue() == (*itNum)){
					sameIucInfoPerDoc.push_back(*itInfoPerDoc);
					break;
				}
			}
		}
		//aca tengo q comparar las disatancias entre los info per doc de la lista sameIucInfoPerDoc
		//si las distancias dan correctas entonces agrego el numero de iuc a listOfIucs(el q me pasan por parametro)
//		cout<<"***********************************"<<endl;
//		for(auxIt = sameIucInfoPerDoc.begin(); auxIt != sameIucInfoPerDoc.end(); auxIt++){
//					(*auxIt)->print(cout);
//		}

		lastInfoPerDoc = sameIucInfoPerDoc.end();
		lastInfoPerDoc--;
			for(itInfoPerDoc = sameIucInfoPerDoc.begin(); itInfoPerDoc != lastInfoPerDoc; itInfoPerDoc++ ){
			auxIt = itInfoPerDoc;
			auxIt++;
			if(!(*itInfoPerDoc)->compareDistance(*auxIt,1)){
				correctDistances = false;
				break;
			}
		}
		if(correctDistances){
			(*listOfIucs).push_back(((KeyInteger*)(*itInfoPerDoc)->getKey())->getValue());
		}
	}





}
