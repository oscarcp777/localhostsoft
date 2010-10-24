/*
 * Controller.cpp
 *
 *  Created on: 24/09/2010
 *      Author: Facundo
 */

#include "Controller.h"
#include "../src.datos.consultations/Consultation.h"
#include "../src.datos.utils/Define.h"

Controller::Controller() {
	this->programFile = new TextFile();
	this->primaryTree = NULL;
	this->loadIndexNames();
	this->search = NULL;
}

Controller::~Controller() {
	delete this->programFile;
	if(this->primaryTree != NULL)
		delete this->primaryTree;

	if(this->search != NULL)
		delete this->search;

	list<IndexConfig*>::iterator itIndex;
	IndexConfig* indexConfig;
	for(itIndex = this->indexes.begin(); itIndex != this->indexes.end(); itIndex++){
		indexConfig = *itIndex;
		delete indexConfig;
	}

	list<Mail*>::iterator itMails;
	Mail* mail;
	for (itMails=this->listOfMails.begin(); itMails!=this->listOfMails.end(); itMails++){
			mail=*itMails;
			delete mail;
		}

}
void Controller::clearListsIucs(){
	this->listOfIucs.clear();
}
void Controller::loadInfoIndex(std::string linea,IndexConfig* index){

	vector<string> tokens;

	StringUtils::Tokenize(linea, tokens,"|");

	int size=tokens.size();
	if (size == 5){
		index->setBlockSize(atoi(tokens.at(0).c_str()));
		index->setFilterName(tokens.at(1));
		index->setFileName(tokens.at(2));
		index->setUserName(tokens.at(3));
		index->setTypeIndex(tokens.at(4));
	}
	if (size == 6){
		index->setBlockSize(atoi(tokens.at(0).c_str()));
		index->setFilterName(tokens.at(1));
		index->setFileName(tokens.at(2));
		index->setUserName(tokens.at(3));
		index->setTypeIndex(tokens.at(4));
		index->setTypeSecundaryIndex(tokens.at(5));
	}
	if (size == 7){
		index->setBlockSize(atoi(tokens.at(0).c_str()));
		index->setFilterName(tokens.at(1));
		index->setFileName(tokens.at(2));
		index->setUserName(tokens.at(3));
		index->setTypeIndex(tokens.at(4));
		index->setTypeSecundaryIndex(tokens.at(5));
		index->setCondition(atoi(tokens.at(6).c_str()));
	}
	if (size == 8){
		index->setBlockSize(atoi(tokens.at(0).c_str()));
		index->setFilterName(tokens.at(1));
		index->setFileName(tokens.at(2));
		index->setUserName(tokens.at(3));
		index->setTypeIndex(tokens.at(4));
		index->setTypeSecundaryIndex(tokens.at(5));
		index->setCondition(atoi(tokens.at(6).c_str()));
		index->setValue(tokens.at(7));
	}

}
void Controller::loadIndexNames(){
	string fileName= "";
	fileName+=PATHFILES;
	fileName+="config.dat";
	this->programFile->open(fileName);
	std::string linea = "";
	this->programFile->read(linea);
	int i=0;
	while(linea.compare("\0") != 0) {
		//procesar linea
		IndexConfig* index = new IndexConfig();
		this->loadInfoIndex(linea, index);
		if(index->getTypeIndex().compare("Primario") == 0){
			//index->print();
			this->primaryTree = new IndexBSharp(PATHFILES+index->getFileName(),index->getBlockSize(),TYPE_REG_PRIMARY);
		}
		this->indexes.push_back(index);//en realidad tengo que meter los registros
		this->programFile->read(linea);
		i++;
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
Search* Controller::getSearch(){
	return this->search;
}
void Controller::setSearch(Search* search){
	this->search = search;
}
void Controller::addIndexToFile(IndexConfig* index){

	if(!searchIndex(index->getFilterName())){
		string fileName= "";
		fileName+=PATHFILES;
		fileName+="config.dat";
		this->programFile->open(fileName);
		std::string sizeBlock = StringUtils::convertirAString(index->getBlockSize());
		std::string aux= sizeBlock+"|"+ index->getFilterName()+"|"+ index->getFileName()+"|"+index->getUserName() + "|"+index->getTypeIndex();
		if(index->getTypeSecundaryIndex() != "")
			aux = aux +"|"+index->getTypeSecundaryIndex();
		if( index->getCondition() != 0){
			std::string valor = StringUtils::convertirAString(index->getCondition());
			aux = aux +"|"+valor;
		}
		if( index->getValue() != "")
					aux = aux +"|"+index->getValue();
		this->programFile->end();
		this->programFile->write(aux);
		this->programFile->close();
	}
}
void Controller::addSecondIndex(IndexConfig* indexConfig) {
	//crea un archivo del indice secundario vacio, agrega en la lista de indices y genera un boton por el indice
	IndexController* indexController = new IndexController();
	indexController->generateSecondaryIndex(this->primaryTree,indexConfig);
	this->addIndexToFile(indexConfig);
	this->indexes.push_back(indexConfig);

	delete indexController;

}

int Controller::createPrimaryIndex() {
	if (this->primaryTree == NULL){
		StorageController* storage = new StorageController();
		IndexConfig* configIndex = new IndexConfig();

		this->primaryTree = storage->generatePrimaryIndex((char*)this->strEmail.c_str(),(char*)this->strPass.c_str(),configIndex);
		this->addIndexToFile(configIndex);
		this->indexes.push_back(configIndex);
		this->primaryTree->print(cout);
		delete storage;

	}else{
		cout<<"Ya exite un arbol primario"<<endl;
	}
	return 0;
}


int Controller::loadSecondIndex(IndexConfig* indexConfig){
	Classification* classification = new Classification();
	if(this->primaryTree == NULL)
		this->createPrimaryIndex();
 	classification->loadSecondaryIndex(indexConfig,this->primaryTree->getIterator());

 	delete classification;
	return 0;
}
void Controller::convertStringToListOfInt(Search* search,std::string str){

	vector<string> tokens;
	StringUtils::Tokenize(str, tokens,",");
	int size=tokens.size();
	for (int i = 0; i < size; ++i) {
		search->setIuc(atoi(tokens.at(i).c_str()));
	}

}
Search* Controller::parseStrSearch(std::string strSearch){
	std::string aux;
	std::string filterName;
	std::string filterValue;
	int result = 0;// this->strSearchValidation(strSearch);
	if (result == 0){
		Search* search =new Search();

		int posInitial = 1;//strSearch.find("[",0);
		int posFinal= 1;//strSearch.find("]",posInitial);
		int pos;
		posFinal = strSearch.find("]",posInitial);
		while((posInitial > 0) && (posFinal > 0)){
			aux = strSearch.substr(posInitial,posFinal-posInitial);
			pos = aux.find("=",0);
			filterName = aux.substr(0,pos);
			filterValue = aux.substr(pos+1,(aux.length()-1)- pos);
			this->convertStringToListOfInt(search,filterValue);
			search->setStrSearch(filterValue);
			search->setIndex(filterName);
//			std::cout<<filterName<<std::endl;
//			std::cout<<filterValue<<std::endl;
			posInitial = strSearch.find("[",posFinal)+1;
			posFinal = strSearch.find("]",posInitial);
		}

		return search;
	} else return NULL;
}
int Controller::searchMails(std::string strSearch){
	Consultation* consultation = new Consultation();
	this->strSearch = strSearch;
	this->search = this->parseStrSearch(strSearch);
	std::string index;
	std::string auxIndex;
	int result = -1;
	int cant = this->search->sizeOfListIndex();// tamaño de la lista de indices a buscar
		for (int i = 0; i < cant; ++i) {
			auxIndex = this->search->getIndex();
			list<IndexConfig*>::iterator current = this->indexes.begin();

			while((current != this->indexes.end())&& result != 0){//recorro la lista de todos lo indices que tiene el programa
					index = (*current)->getFilterName();
					result =auxIndex.compare(index);
					if (result == 0){
						if((*current)->getTypeIndex().compare((char*)TYPE_PRIMARY) == 0){
							//TODO falta devolverlo en algun lado y si son muchos iuc buscar muchos registros
							//como me pasa facu el iuc para seterle la clave al regPrimary???
							list<int>::iterator it = this->search->getIteratorBeginListOfIucs();
							while(it != this->search->getIteratorEndListOfIucs()){
								RegPrimary* regPrimary = new RegPrimary;
								regPrimary->setKey(new KeyInteger((int)*it));
								consultation->consultPrimaryIndex(*current,regPrimary);
								if(regPrimary->getMail() != NULL)
									this->listOfMails.push_back((Mail*)regPrimary->getMail()->clone());
								it++;
								delete regPrimary->getMail();
								delete regPrimary;
							}

						}
						else
							consultation->consultSecondaryIndex(*current,&this->listOfIucs, this->search->getStrSearch());

					}
					current++;
					}
		}
		delete consultation;
	return 0;
}

list<int>::iterator Controller::iteratorBeginListOfIucs(){
	return this->listOfIucs.begin();
}
list<int>::iterator Controller::iteratorEndListOfIucs(){
	return this->listOfIucs.end();
}
list<Mail*>::iterator Controller::iteratorBeginListOfMails(){
	return this->listOfMails.begin();
}
list<Mail*>::iterator Controller::iteratorEndListOfMails(){
	return this->listOfMails.end();
}

bool Controller::searchIndex(std::string index){

	std::string auxIndex;
	int result = -1;
	list<IndexConfig*>::iterator current = this->indexes.begin();
	while((current != this->indexes.end())&& result != 0){//recorro la lista de todos lo indices que tiene el programa
		auxIndex = (*current)->getFilterName();
		result =auxIndex.compare(index);
			if (result == 0){
				return true;
			}
		current++;
	}
	return false;
}

IndexConfig* Controller::loadIndexConfig(std::string index){

	std::string auxIndex;
	int result = -1;
	list<IndexConfig*>::iterator current = this->indexes.begin();
	while((current != this->indexes.end())&& result != 0){//recorro la lista de todos lo indices que tiene el programa
		auxIndex = (*current)->getFilterName();
		result =auxIndex.compare(index);
			if (result == 0){
				return *current;
			}
		current++;
	}
	return NULL;
}
list<int> Controller::getListOfIUCS(){
	return this->listOfIucs;
}
list<Mail*> Controller::getListOfMails(){
	return this->listOfMails;
}


int Controller::strSearchValidation(std::string strSearch){
	std::string aux;
	std::string filterName;
	std::string filterValue;
	int result=0;
//	int pos;
//	int posAux;
	int posInitial = strSearch.find("[",0);
	int posFinal = strSearch.find("]",posInitial);
	if ((posInitial == -1) && (posFinal == -1)){
		std::cout<<"Error en el string de busqueda, no se encuentran los parametros [ ] "<<std::endl;
		return 1;
	}
//	while((posInitial >= 0) && (posFinal > 0)){
//		if(posFinal>posInitial){
//			aux = strSearch.substr(posInitial,posFinal-posInitial);
//			pos = aux.find("=",0);
//			if(pos==-1){
//				std::cout<<"Error en el string de busqueda, no se encuentra el parametro = "<<std::endl;
//			}
//			posAux = aux.find("=",0);
//			if(posAux > -1){
//				std::cout<<"Error en el string de busqueda, existe mas de un signo = "<<std::endl;
//			}
//			filterName = aux.substr(0,pos);
//			//validar que exista el indice
//			if (!searchIndex(filterName)){
//				std::cout<<"Error en el string de busqueda, no existe el nombre de indice: "<< filterName <<std::endl;
//				result = 1;
//			}
//
//			filterValue = aux.substr(pos+1,(aux.length()-1)- pos);
//
//			posInitial = strSearch.find("[",posFinal)+1;
//			posFinal = strSearch.find("]",posInitial);
//		}else{
//			std::cout<<" Error en el string de busqueda, incorrecta ubicacion de corchetes [ ] "<<std::endl;
//		}
//	}


	return result;
}









