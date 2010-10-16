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
	for(it= this->currentWords->getWordsBegin(); it != this->currentWords->getWordsEnd(); it++ ){
			cout<<*it<<endl;
	}
	this->removeStopWords();
	cout<<"DESPUES DE REMOVER STOP WORDS"<<endl;
	for(it= this->currentWords->getWordsBegin(); it != this->currentWords->getWordsEnd(); it++ ){
		cout<<*it<<endl;
		}
	delete this->currentWords;
}

void ManagerInvertedIndex::removeStopWords(){
	vector<string>::iterator it;
	for(it= this->currentWords->getWordsBegin(); it != this->currentWords->getWordsEnd(); it++ ){
		if(this->stopWords->contains(*it))
			this->currentWords->removeWord(it);
	}
}
