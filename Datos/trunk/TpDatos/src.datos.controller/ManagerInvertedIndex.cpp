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
	file->close();
//	vector<string>::iterator it;
//	for(it= this->stopWords->getWordsBegin(); it != this->stopWords->getWordsEnd(); it++ ){
//		cout<<*it<<endl;
//	}
	delete file;
}

ManagerInvertedIndex::~ManagerInvertedIndex() {
	delete this->stopWords;
}

void ManagerInvertedIndex::loadMessageWords(Mail* mail){
	this->currentWords = new WordsContainer(mail->getIuc(), mail->getMessage());
	vector<string>::iterator it;
	RegInvertedIndex* regInvertedIndex;
	InfoPerDoc* infoPerDoc;
	this->removeStopWords();
	int count = 0;
	for(it= this->currentWords->getWordsBegin(); it != this->currentWords->getWordsEnd(); it++ ){
		regInvertedIndex = this->regMap[*it];

		if(regInvertedIndex == NULL){//aparicion termino por primera vez
			regInvertedIndex = new RegInvertedIndex();
			regInvertedIndex->setKey(new KeyString(*it));
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
	this->printMap(cout);
	delete this->currentWords;

}

void ManagerInvertedIndex::removeStopWords(){
	vector<string>::iterator it;
	for(it= this->currentWords->getWordsBegin(); it != this->currentWords->getWordsEnd(); it++ ){
		if(this->stopWords->contains(*it))
			this->currentWords->removeWord(it);
	}
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