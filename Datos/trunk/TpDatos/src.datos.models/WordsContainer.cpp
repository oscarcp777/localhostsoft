/*
 * WordsContainer.cpp
 *
 *  Created on: 16/10/2010
 *      Author: richy
 */

#include "WordsContainer.h"

WordsContainer::WordsContainer(string message) {
	this->parserMailWords(message);
}

WordsContainer::WordsContainer(int iuc, string message) {
	this->iuc = iuc;
	this->parserMailWords(message);
}

WordsContainer::~WordsContainer() {
	this->words.clear();
}
int WordsContainer::getIuc(){
	return this->iuc;
}
void WordsContainer::setIuc(int iuc){
	this->iuc = iuc;
}
vector<string>::iterator WordsContainer::getWordsBegin(){
	return this->words.begin();
}
vector<string>::iterator WordsContainer::getWordsEnd(){
	return this->words.end();
}

void WordsContainer::parserMailWords(string message){
	string delim = " ";
	StringUtils::Tokenize(message,this->words,delim);
	cout<<"cantidad palabras: "<<this->words.size()<<endl;
}

void WordsContainer::removeWord(vector<string>::iterator it){
		this->words.erase(it);
}

bool WordsContainer::contains(string word){
	//find devuelve end si no encuentra, si encuentra devuelve un it
	if(std::find(this->words.begin(),this->words.end(),word) != this->words.end())
			return true;
	else
		return false;
}
