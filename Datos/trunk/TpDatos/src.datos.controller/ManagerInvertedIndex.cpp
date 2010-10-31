/*
 * ManagerInvertedIndex.cpp
 *
 *  Created on: 16/10/2010
 *      Author: richy
 */

#include "ManagerInvertedIndex.h"


ManagerInvertedIndex::ManagerInvertedIndex() {

	TextFile* file = new TextFile();
	string line;
	file->open(STOP_WORDS_FILE);
	file->read(line);
	//cout<<"linea: "<<line<<endl;
	this->stopWords = new WordsContainer(line);
	this->dirtyWords = new WordsContainer();
	this->loadDirtyWords();
	file->close();
//	vector<string>::iterator it;
//	for(it= this->stopWords->getWordsBegin(); it != this->stopWords->getWordsEnd(); it++ ){
//		cout<<*it<<endl;
//	}
	delete file;
}

ManagerInvertedIndex::~ManagerInvertedIndex() {
	delete this->stopWords;
	delete this->dirtyWords;
}

void ManagerInvertedIndex::loadMessageWords(Mail* mail, IndexBSharp* indexBSharp){


	this->currentWords = new WordsContainer(mail->getIuc(), mail->getMessage());
	vector<string>::iterator it;
	RegInvertedIndex* regInvertedIndex;
	InfoPerDoc* infoPerDoc;
	this->removeStopWords();
	this->removeDirtyWords();
	int count = 1;

	//this->currentWords->print();

	for(it= this->currentWords->getWordsBegin(); it != this->currentWords->getWordsEnd(); it++ ){

		regInvertedIndex = this->regMap[*it];

		if(regInvertedIndex == NULL){//aparicion termino por primera vez
			regInvertedIndex = new RegInvertedIndex();
			regInvertedIndex->setKey(new KeyString(validateSize(*it)));
			infoPerDoc = new InfoPerDoc();
			KeyInteger* key=(KeyInteger*)mail->getKey()->clone();
			infoPerDoc->setKey(key);
			infoPerDoc->addPosition(new KeyInteger(count));
			regInvertedIndex->addInfoPerDoc(infoPerDoc);
			this->regMap[*it] = regInvertedIndex;

		}
		else{//se repite el termino
			infoPerDoc = regInvertedIndex->getFirstInfoPerDoc();
			infoPerDoc->addPosition(new KeyInteger(count));

		}
		count++;
	}
//	this->printMap(cout);
	this->writeOrUpdateInvertedIndex(indexBSharp);
	delete this->currentWords;
	this->regMap.clear();

}
void ManagerInvertedIndex::writeOrUpdateInvertedIndex(IndexBSharp* indexBSharp){
	//TODO monos el arbol lo actualiza solo si ya existe si no agrega uno nuevo no era
	//TODO necesario lo que estaban haciendo de buscarlo antes eso es parte de la logica del arbol
	RegInvertedIndex* regInvertedIndex;
	map<string,RegInvertedIndex*>::iterator it;
	for(it = this->regMap.begin() ; it != this->regMap.end(); it++){
		regInvertedIndex = (*it).second;
		indexBSharp->addRegistry(regInvertedIndex);//se agrega al indice
		}
}


void ManagerInvertedIndex::removeStopWords(){
	vector<string>::iterator it;
	vector<string>::iterator aux;
	for(it= this->currentWords->getWordsBegin(); it != this->currentWords->getWordsEnd(); it++ ){
		if(this->stopWords->contains(*it)){
			aux = it;
			it--;
			this->currentWords->removeWord(aux);
		}
	}
}
void ManagerInvertedIndex::removeStopWordsFromVector(vector<string>* words){
	vector<string>::iterator it;
	vector<string>::iterator auxIt;
	for(it= (*words).begin(); it != (*words).end(); it++ ){
		if(this->stopWords->contains(*it)){
			auxIt = it;
			it--;
			(*words).erase(auxIt);
		}
	}
}
void ManagerInvertedIndex::removeDirtyWords(){
	vector<string>::iterator it;
	vector<string>::iterator aux;
	for(it= this->currentWords->getWordsBegin(); it != this->currentWords->getWordsEnd(); it++ ){
		string token=*it;
		if(this->dirtyWords->contains(token)){
			aux = it;
			it--;
			this->currentWords->removeWord(aux);
		}
	}
}
void ManagerInvertedIndex::loadDirtyWords(){
	this->dirtyWords->addWord("");
	this->dirtyWords->addWord(" ");
	this->dirtyWords->addWord("\n");
	this->dirtyWords->addWord("\t");
	this->dirtyWords->addWord("<");
	this->dirtyWords->addWord(">");
	this->dirtyWords->addWord(":");
	this->dirtyWords->addWord(";");
	this->dirtyWords->addWord("=");
	this->dirtyWords->addWord("-");
}
map<string,RegInvertedIndex*>::iterator ManagerInvertedIndex::getIteratorBegin(){
	return this->regMap.begin();
}
map<string,RegInvertedIndex*>::iterator ManagerInvertedIndex::getIteratorEnd(){
	return this->regMap.end();
}

void  ManagerInvertedIndex::printMap(std::ostream& outStream){
	map<string,RegInvertedIndex*>::iterator it;
	for(it = this->regMap.begin() ; it != this->regMap.end(); it++){
		outStream<<"word map: "<<(*it).first<<endl;
		((*it).second)->print(outStream);
	}

}
string ManagerInvertedIndex::validateSize(string word){
	unsigned int maxSize = BLOCK_SIZE*0.3;
	if(word.size() >= maxSize){
		word = word.substr(0,maxSize-1);
	}
	return word;
}
