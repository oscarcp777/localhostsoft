/*
 * Controller.cpp
 *
 *  Created on: 24/09/2010
 *      Author: Facundo
 */

#include "Controller.h"
#include "../src.datos.models/RegSelection.h"
#include "../src.datos.consultations/Consultation.h"
#include "ManagerInvertedIndex.h"
#include "../src.datos.utils/Define.h"

Controller::Controller() {
	this->programFile = new TextFile();
	this->primaryTree = NULL;
	this->loadIndexNames();
	this->search = NULL;
}
Controller::Controller(std::string userMail) {
	string fileName= "";
			fileName+=PATHFILES;
			fileName+=userMail+".dat";
	this->fileNameAccount = fileName;
	this->strEmail = userMail;
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
	if (size == 7){//PRIMARIO
		index->setLoaded(atoi(tokens.at(0).c_str()));
		index->setLastIuc(atoi(tokens.at(1).c_str()));
		index->setBlockSize(atoi(tokens.at(2).c_str()));
		index->setFilterName(tokens.at(3));
		index->setFileName(tokens.at(4));
		index->setUserName(tokens.at(5));
		index->setTypeIndex(tokens.at(6));
	}
	if (size == 8){//INVERTIDO
		index->setLoaded(atoi(tokens.at(0).c_str()));
		index->setLastIuc(atoi(tokens.at(1).c_str()));
		index->setBlockSize(atoi(tokens.at(2).c_str()));
		index->setFilterName(tokens.at(3));
		index->setFileName(tokens.at(4));
		index->setUserName(tokens.at(5));
		index->setTypeIndex(tokens.at(6));
		index->setTypeSecundaryIndex(tokens.at(7));
	}
	if (size == 9){//CLASIFICACION
		index->setLoaded(atoi(tokens.at(0).c_str()));
		index->setLastIuc(atoi(tokens.at(1).c_str()));
		index->setBlockSize(atoi(tokens.at(2).c_str()));
		index->setFilterName(tokens.at(3));
		index->setFileName(tokens.at(4));
		index->setUserName(tokens.at(5));
		index->setTypeIndex(tokens.at(6));
		index->setTypeSecundaryIndex(tokens.at(7));
		index->setCondition(atoi(tokens.at(8).c_str()));
	}
	if (size == 10){//SELECCION
		index->setLoaded(atoi(tokens.at(0).c_str()));
		index->setLastIuc(atoi(tokens.at(1).c_str()));
		index->setBlockSize(atoi(tokens.at(2).c_str()));
		index->setFilterName(tokens.at(3));
		index->setFileName(tokens.at(4));
		index->setUserName(tokens.at(5));
		index->setTypeIndex(tokens.at(6));
		index->setTypeSecundaryIndex(tokens.at(7));
		index->setCondition(atoi(tokens.at(8).c_str()));
		index->setValue(tokens.at(9));
	}

}
void Controller::loadIndexNames(){

	this->programFile->open(this->fileNameAccount);
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
std::string Controller::getEmail(){
	return this->strEmail;
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
		this->programFile->open(this->fileNameAccount);
		std::string loaded = StringUtils::convertirAString(index->isLoaded());
		std::string lastIuc = StringUtils::convertirAString(index->getLastIuc());
		std::string sizeBlock = StringUtils::convertirAString(index->getBlockSize());
		std::string aux= loaded+ "|"+ lastIuc + "|"+ sizeBlock+"|"+ index->getFilterName()+"|"+ index->getFileName()+"|"+index->getUserName() + "|"+index->getTypeIndex();
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
void Controller::overWriteFile(){

	remove(this->fileNameAccount.c_str());
	this->programFile->open(this->fileNameAccount);
	IndexConfig* index;
	list<IndexConfig*>::iterator current = this->indexes.begin();
	while(current != this->indexes.end()){//recorro la lista de todos lo indices que tiene el programa
		index = (IndexConfig*)*current;
		std::string loaded = StringUtils::convertirAString(index->isLoaded());
		std::string lastIuc = StringUtils::convertirAString(index->getLastIuc());
		std::string sizeBlock = StringUtils::convertirAString(index->getBlockSize());
		std::string aux= loaded+ "|"+lastIuc + "|"+ sizeBlock+"|"+ index->getFilterName()+"|"+ index->getFileName()+"|"+index->getUserName() + "|"+index->getTypeIndex();
		if(index->getTypeSecundaryIndex() != "")
			aux = aux +"|"+index->getTypeSecundaryIndex();
		if( index->getCondition() != 0){
			std::string valor = StringUtils::convertirAString(index->getCondition());
			aux = aux +"|"+valor;
		}
		if( index->getValue() != "")
			aux = aux +"|"+index->getValue();

		this->programFile->write(aux);
		current++;
	}
	this->programFile->end();
	this->programFile->close();

}
void Controller::addSecondIndex(IndexConfig* indexConfig) {

	if(this->searchIndex(indexConfig->getFilterName())){
		cout<<"No se puede crear, ya existe el indice con nombre: "<<indexConfig->getFilterName()<<endl;
	}else{
		//crea un archivo del indice secundario vacio, agrega en la lista de indices y genera un boton por el indice
		IndexController* indexController = new IndexController();
		indexController->generateSecondaryIndex(indexConfig);
		this->addIndexToFile(indexConfig);
		this->indexes.push_back(indexConfig);
		delete indexController;
	}
}

void Controller::updateIndexesDelete(Mail* mail){
	std::string value;
	IndexBSharp* secondaryIndex;
	list<IndexConfig*>::iterator current = this->indexes.begin();
	while(current != this->indexes.end()){//recorro la lista de todos lo indices que tiene el programa
		if(TYPE_SELECTION == (*current)->getTypeSecundaryIndex()){
			secondaryIndex = new IndexBSharp(PATHFILES+(*current)->getFileName(),(*current)->getBlockSize(),TYPE_REG_SELECTION);
			RegSelection* regSelection = new RegSelection();
			regSelection->setKey((Key*)mail->getKey()->clone());
			cout<<"INDICE: "<< (*current)->getFilterName() <<endl;
			secondaryIndex->deleteRegistry(regSelection);/////////////////////////DELETE
			secondaryIndex->print(cout);
			delete secondaryIndex;

		}
		if(TYPE_CLASSIFICATION == (*current)->getTypeSecundaryIndex() ){
			secondaryIndex = new IndexBSharp(PATHFILES+(*current)->getFileName(),(*current)->getBlockSize(),TYPE_REG_CLASSIFICATION);
			RegClassification* regClassification = new RegClassification();
			KeyString* key = new KeyString(mail->getCondition((*current)->getCondition()));
			regClassification->setKey(key);
			regClassification->addIuc((KeyInteger*) mail->getKey()->clone());
			cout<<"INDICE: "<< (*current)->getFilterName() <<endl;
			secondaryIndex->deleteRegistry(regClassification);///////////////////////DELETE
			secondaryIndex->print(cout);
			delete secondaryIndex;

		}
		if(TYPE_INVERTED_INDEX == (*current)->getTypeSecundaryIndex()){
			IndexBSharp* secondaryIndex = new IndexBSharp(PATHFILES+(*current)->getFileName(),(*current)->getBlockSize(),TYPE_REG_INVERTED_INDEX);
			//cout<<"INDICE: "<< (*current)->getFilterName() <<endl;
			//ManagerInvertedIndex* manager = new ManagerInvertedIndex();
			//manager->deleteMessageWords(mail,secondaryIndex);
			delete secondaryIndex;
		}
		current++;
	}
}

void Controller::updateIndexes(Mail* mail){
	int condition;
	std::string value;
	IndexBSharp* secondaryIndex;
	list<IndexConfig*>::iterator current = this->indexes.begin();
	while(current != this->indexes.end()){//recorro la lista de todos lo indices que tiene el programa
		if(TYPE_SELECTION == (*current)->getTypeSecundaryIndex()){
			condition = (*current)->getCondition();
			value = (*current)->getValue();
			if(mail->containCondition(condition,value)){
				secondaryIndex = new IndexBSharp(PATHFILES+(*current)->getFileName(),(*current)->getBlockSize(),TYPE_REG_SELECTION);
				RegSelection* regSelection = new RegSelection();
				regSelection->setKey((Key*)mail->getKey()->clone());
				secondaryIndex->addRegistry(regSelection);
				secondaryIndex->print(cout);
				delete secondaryIndex;
			}
		}
		if(TYPE_CLASSIFICATION == (*current)->getTypeSecundaryIndex() ){
			condition = (*current)->getCondition();
			secondaryIndex = new IndexBSharp(PATHFILES+(*current)->getFileName(),(*current)->getBlockSize(),TYPE_REG_CLASSIFICATION);
			RegClassification* regClassification = new RegClassification();
			KeyString* key = new KeyString(mail->getCondition(condition));
			regClassification->setKey(key);
			regClassification->addIuc((KeyInteger*) mail->getKey()->clone());
			secondaryIndex->addRegistry(regClassification);
			secondaryIndex->print(cout);
			delete secondaryIndex;
		}
		if(TYPE_INVERTED_INDEX == (*current)->getTypeSecundaryIndex()){
			IndexBSharp* secondaryIndex = new IndexBSharp(PATHFILES+(*current)->getFileName(),(*current)->getBlockSize(),TYPE_REG_INVERTED_INDEX);
			ManagerInvertedIndex* manager = new ManagerInvertedIndex();
			manager->loadMessageWords(mail,secondaryIndex);
			delete secondaryIndex;
		}
		current++;
	}
}

int Controller::createPrimaryIndex() {
	StorageController* storage = new StorageController();
	IndexConfig* configIndex = new IndexConfig();
	configIndex->setUserName(this->strEmail);
	if (this->primaryTree == NULL){
		this->primaryTree = storage->generatePrimaryIndex((char*)this->strEmail.c_str(),(char*)this->strPass.c_str(),configIndex);
		configIndex->setLoaded(true);
		this->addIndexToFile(configIndex);
		this->indexes.push_back(configIndex);
		this->primaryTree->print(cout);//////////////////////////////////////////////
	}else{
		//busco si el arbol primario ya existe, si existe configIndex tiene seteado el ultimo IUC
		if(this->searchPrimaryIndex(configIndex)){
			int iuc = configIndex->getLastIuc();
			this->primaryTree = storage->generatePrimaryIndex((char*)this->strEmail.c_str(),(char*)this->strPass.c_str(),configIndex);
			this->primaryTree->print(cout);/////////////////////////////////////////
			list<IndexConfig*>::iterator current = this->indexes.begin();
			int result = 1;
			string auxEmail;
			//actualizo en la lista de indices el primario, con el ultimo iuc
			while((current != this->indexes.end())&& result != 0){//recorro la lista de todos lo indices que tiene el programa
				auxEmail = (*current)->getUserName();
				result =auxEmail.compare(configIndex->getUserName());
				if (result == 0){
					(*current)->setLastIuc(configIndex->getLastIuc());
					break;
				}
				current++;
			}
			this->overWriteFile();
			//int lastIuc = configIndex->getLastIuc();//no lo necesito
			IteratorBSharp* it = this->primaryTree->getIterator();
			RegPrimary* regPrimary = new RegPrimary;
			regPrimary->setKey(new KeyInteger(iuc));
			RegPrimary* regPrimaryIter = (RegPrimary*) it->next();
			//me ubico en la posicion del primer iuc nuevo
			while(it->hasNext() && ((regPrimaryIter->getMail()->getIuc()) != iuc)){
				regPrimaryIter =(RegPrimary*) it->next();
			}

			Mail* mail;
			mail = regPrimaryIter->getMail();
			this->updateIndexes(mail);//actualizo secundarios
			while (it->hasNext()){
				regPrimaryIter = (RegPrimary*)it->next();
				mail = regPrimaryIter->getMail();
				this->updateIndexes(mail);
			}
			delete it;
		}
	}
	delete storage;
	return 0;
}

int Controller::loadSecondIndex(IndexConfig* indexConfig){

	if(this->indexes.size() != 0){

		if(this->getIndex(indexConfig->getFilterName())->isLoaded()){
			cout<<"Ya fue cargado el indice "<<indexConfig->getFilterName()<<endl;
			return 1;
		}else{
			Classification* classification = new Classification();
			if(this->primaryTree == NULL)
				this->createPrimaryIndex();
			classification->loadSecondaryIndex(indexConfig,this->primaryTree->getIterator());

			std::string index(indexConfig->getFilterName());
			std::string auxIndex;
			int result = -1;
			list<IndexConfig*>::iterator current = this->indexes.begin();
			while((current != this->indexes.end())&& result != 0){//recorro la lista de todos lo indices que tiene el programa
				auxIndex = (*current)->getFilterName();
				result =auxIndex.compare(index);
				if (result == 0){
					(*current)->setLoaded(true);//lo seteo como cargado
				}
				current++;
			}

			this->overWriteFile();
			delete classification;
			return 0;

		}
	}else{
		cout<<"Debe crear el indice, antes de cargarlo "<<indexConfig->getFilterName()<<endl;
	}
	return 1;
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
			search->pushStrSearch(filterValue);
			search->setIndex(filterName);
			posInitial = strSearch.find("[",posFinal)+1;
			posFinal = strSearch.find("]",posInitial);
		}
		search->setNumOfIndex(search->sizeOfListIndex());
		return search;
	} else return NULL;
}
std::string Controller::getMails(std::string strListOfIucs){
		std::string strResult;
		vector<string> tokens;
		list<int> listOfIucs;
		StringUtils::Tokenize(strListOfIucs, tokens," ");
		int size=tokens.size();
		for (int i = 0; i < size; ++i) {
			listOfIucs.push_back(atoi(tokens.at(i).c_str()));
		}
		Mail* mail;
		IndexConfig* indexConfig = new IndexConfig();
				indexConfig = loadIndexConfig("Primario"+this->strEmail);
		Consultation* consultation = new Consultation();
		list<int>::iterator it = listOfIucs.begin();
		while(it != listOfIucs.end()){
			RegPrimary* regPrimary = new RegPrimary;
			regPrimary->setKey(new KeyInteger((int)*it));
			consultation->consultPrimaryIndex(indexConfig ,regPrimary);
			if(regPrimary->getMail() != NULL){
				mail = ((Mail*)regPrimary->getMail()->clone());
				strResult += mail->toString();
			}
			it++;
			delete regPrimary->getMail();
			delete regPrimary;


}
return strResult;
}
int Controller::searchMails(std::string strSearch){
	Consultation* consultation = new Consultation();
	this->strSearch = strSearch;
	this->search = this->parseStrSearch(strSearch);
	std::string index;
	std::string auxIndex;
	int result;
	std::string subSearch;
	bool find = false;
	int cant = this->search->sizeOfListIndex();// tamaño de la lista de indices a buscar
	for (int i = 0; i < cant; ++i) {
			result = -1;
			auxIndex = this->search->getIndex();
			list<IndexConfig*>::iterator current = this->indexes.begin();
			subSearch = this->search->popStrSearch();
			while((current != this->indexes.end())&& result != 0){//recorro la lista de todos lo indices que tiene el programa
					index = (*current)->getFilterName();
					result =auxIndex.compare(index);
					if (result == 0){
						find = true;
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
							consultation->consultSecondaryIndex(*current,&this->listOfIucs, subSearch);

					}
					current++;
					}
			if(!find){
				cout<<"No existe el indice: "<< auxIndex<<endl;////
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

IndexConfig* Controller::getIndex(std::string index){

	std::string auxIndex;
	int result = -1;
	list<IndexConfig*>::iterator current = this->indexes.begin();
	while((current != this->indexes.end())&& result != 0){//recorro la lista de todos lo indices que tiene el programa
		auxIndex = (*current)->getFilterName();
		result =auxIndex.compare(index);
			if (result == 0){
				return (*current);
			}
		current++;
	}
	return NULL;
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
bool Controller::searchPrimaryIndex(IndexConfig* indexConfig){

	std::string auxEmail = indexConfig->getUserName();
	int result = -1;
	list<IndexConfig*>::iterator current = this->indexes.begin();
	while((current != this->indexes.end())&& result != 0){//recorro la lista de todos lo indices que tiene el programa
		auxEmail = (*current)->getUserName();
		result =auxEmail.compare(indexConfig->getUserName());
			if (result == 0){
				indexConfig->setLastIuc((*current)->getLastIuc());

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

void Controller::deleteIuc(int iuc){
	RegPrimary* regPrimary = new RegPrimary();
	KeyInteger* key= new KeyInteger(iuc);
	regPrimary->setKey(key);
	RegPrimary* reg = (RegPrimary*) this->primaryTree->searchRegistry(regPrimary);
	if(reg != NULL){
		Mail* mail = reg->getMail();
		this->updateIndexesDelete(mail);
		this->primaryTree->deleteRegistry(regPrimary);
		cout<<"***********INDICE: "<< "************ARBOL PRIMARIO"<<endl;
		this->primaryTree->print(cout);
	}else{
		cout<<"El arbol primario no posee el IUC: "<< iuc<<endl;
	}

}

list<int>* Controller::getListOfIucs(){
	return &this->listOfIucs;
}




