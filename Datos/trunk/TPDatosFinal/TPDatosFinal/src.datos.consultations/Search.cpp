/*
 * Search.cpp
 *
 *  Created on: 26/09/2010
 *      Author: Facundo
 */

#include "Search.h"
#include<iostream>
int Search::sizeOfListIndex(){
	return this->listOfIndex.size();
}
void Search::pushStrSearch(std::string strSearch){
	this->listStrSearch.push_back(strSearch);
}
unsigned int Search::getNumOfIndex(){
	return sizeOfIndexes;
}
std::string Search::popStrSearch(){
	std::string str = *this->listStrSearch.begin();
	this->listStrSearch.pop_front();
	return str;
}
void Search::setIndex(std::string index){
	this->listOfIndex.push_back(index);
}
std::string Search::getIndex(){
	std::string aux = "";
	list<string>::iterator it = this->listOfIndex.begin();
	aux = *it;
	this->listOfIndex.pop_front();
	return aux;
}
void Search::setIuc(int iuc){
	this->listOfIucs.push_back(iuc);
}
void Search::setNumOfIndex(int size){
	this->sizeOfIndexes = size;
}
void Search::printIndexNames(){
	list<string>::iterator current = this->listOfIndex.begin();
	while(current != this->listOfIndex.end()){
		current++;
		}

}
list<int> Search::getListOfIucs(){
	return this->listOfIucs;
}
list<int>::iterator Search::getIteratorBeginListOfIucs(){
	return this->listOfIucs.begin();
}
list<int>::iterator Search::getIteratorEndListOfIucs(){
	return this->listOfIucs.end();
}
Search::Search() {
	// TODO Auto-generated constructor stub

}

Search::~Search() {
	// TODO Auto-generated destructor stub
}
