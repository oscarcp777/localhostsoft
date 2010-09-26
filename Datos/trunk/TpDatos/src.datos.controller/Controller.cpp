/*
 * Controller.cpp
 *
 *  Created on: 24/09/2010
 *      Author: Facundo
 */

#include "Controller.h"
#include "../src.datos.classification/Classification.h"

Controller::Controller() {
	this->programFile = new TextFile();
	this->loadIndexNames();
	this->primaryTree = NULL;

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}
void Controller::loadInfoIndex(std::string linea,IndexConfig* index){

	vector<string> tokens;

	StringUtils::Tokenize(linea, tokens," ");

	int size=tokens.size();
	if (size == 4){
		index->setFilterName(tokens.at(0));
		index->setFileName(tokens.at(1));
		index->setUserName(tokens.at(2));
		index->setTypeIndex(tokens.at(3));
	}
	if (size == 6){
		index->setFilterName(tokens.at(0));
		index->setFileName(tokens.at(1));
		index->setUserName(tokens.at(2));
		index->setTypeIndex(tokens.at(3));
		index->setTypeSecundaryIndex(tokens.at(4));
		index->setCondition(atoi(tokens.at(5).c_str()));
	}
	if (size == 7){
		index->setFilterName(tokens.at(0));
		index->setFileName(tokens.at(1));
		index->setUserName(tokens.at(2));
		index->setTypeIndex(tokens.at(3));
		index->setTypeSecundaryIndex(tokens.at(4));
		index->setCondition(atoi(tokens.at(5).c_str()));
		index->setValue(tokens.at(6));
	}

}
void Controller::loadIndexNames(){

	this->programFile->open("archivo.dat");
	std::string linea = "";
	this->programFile->read(linea);

	while( linea.compare("\0") != 0) {
		//procesar linea
		IndexConfig* index = new IndexConfig();
		this->loadInfoIndex(linea, index);
		this->indexes.push_back(index);//en realidad tengo que meter los registros
		this->programFile->read(linea);
	}
	this->programFile->close();
}
void Controller::printIndexNames(){
	list<IndexConfig*>::iterator current = this->indexes.begin();

	while(current != this->indexes.end()){
		std::cout<<(*current)->getFilterName()<<std::endl;
		std::cout<<(*current)->getFileName()<<std::endl;
		std::cout<<(*current)->getUserName()<<std::endl;
		std::cout<<(*current)->getTypeIndex()<<std::endl;

		if((*current)->getTypeSecundaryIndex() != "")
			std::cout<<(*current)->getTypeSecundaryIndex()<<std::endl;
		if( (*current)->getCondition() != 0)
			std::cout<<(*current)->getCondition()<<std::endl;

		if( (*current)->getValue() != "")
			std::cout<<(*current)->getValue()<<std::endl;

		current++;
		}

}
void Controller::addEmail(std::string email) {
	this->strEmail = email;
}

void Controller::addPass(std::string pass) {
	this->strPass = pass;
}
void Controller::addIndexToFile(IndexConfig* index){

	this->programFile->open("archivo.dat");
	std::string aux= index->getFilterName()+" "+ index->getFileName()+" "+index->getUserName() + " "+index->getTypeIndex();
	if(index->getTypeSecundaryIndex() != "")
		aux = aux +" "+index->getTypeSecundaryIndex();
	if( index->getCondition() != 0){
		std::string valor = StringUtils::convertirAString(index->getCondition());
		aux = aux +" "+valor;
	}
	if( index->getValue() != "")
				aux = aux +" "+index->getValue();
	this->programFile->end();
	this->programFile->write(aux);
	this->programFile->close();

}
void Controller::addSecondIndex(IndexConfig* indexConfig) {
	//crea un archivo del indice secundario vacio, agrega en la lista de indices y genera un boton por el indice
	IndexController* indexController = new IndexController();
	indexController->generateSecondaryIndex(this->primaryTree,indexConfig);
	this->addIndexToFile(indexConfig);
	this->indexes.push_back(indexConfig);

	//creoelIndice

}

int Controller::createPrimaryIndex() {
	StorageController* storage = new StorageController();
	IndexConfig* configIndex = new IndexConfig();
	this->primaryTree = storage->generatePrimaryIndex((char*)this->strEmail.c_str(),(char*)this->strPass.c_str(),configIndex);
	this->primaryTree->print(cout);
	this->addIndexToFile(configIndex);
	this->indexes.push_back(configIndex);

	return 0;
}
int Controller::loadSecondIndex(IndexConfig* indexConfig){
	Classification* classification = new Classification();
	if(this->primaryTree == NULL)
		this->createPrimaryIndex();
    this->primaryTree->print(cout);

	classification->loadSecondaryIndex(indexConfig,this->primaryTree->getIterator());

	return 0;
}
Search* Controller::parseStrSearch(std::string strSearch){
	std::string aux;
	std::string filterName;
	std::string filterValue;
	Search* search =new Search();
	int posInitial =1;
	int posFinal=1;
	int pos;
	posFinal = strSearch.find("]",posInitial);
	while((posInitial > 0) && (posFinal > 0)){
		aux = strSearch.substr(posInitial,posFinal-posInitial);
			pos = aux.find("=",0);
			filterName = aux.substr(0,pos);
			filterValue = aux.substr(pos+1,(aux.length()-1)- pos);
			search->setStrSearch(filterValue);
			search->setIndex(filterName);
			std::cout<<filterName<<std::endl;
			std::cout<<filterValue<<std::endl;
		posInitial = strSearch.find("[",posFinal)+1;
		posFinal = strSearch.find("]",posInitial);
	}

	return search;
}
int Controller::searchMails(std::string strSearch){
	this->strSearch = strSearch;
	this->search = this->parseStrSearch(strSearch);
	std::string index;
	std::string auxIndex;
	int result;
	int cant = this->search->sizeOfListIndex();// tamaño de la lista de indices a buscar
		for (int i = 0; i < cant; ++i) {
			auxIndex = this->search->getIndex();

			//tengo q buscar auxIndex en la lista de indices, en el caso que hayan IUCS fijarse en this->search->strSearch
			//imprimo los IUCS DE ESOS INDICEs terminar
			list<IndexConfig*>::iterator current = this->indexes.begin();

				while((current != this->indexes.end())&& result < 0){
					index = (*current)->getFilterName();
					result =auxIndex.compare(index);
					if (result == 0){
						//funCion de RICHY BUSCAR!!
					}
					current++;
					}
		}

	return 0;
}












