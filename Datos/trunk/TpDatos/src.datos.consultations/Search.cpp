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
void Search::setStrSearch(std::string strSearch){
	this->strSearch = strSearch;
}
std::string Search::getStrSearch(){
	return this->strSearch;
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

void Search::printIndexNames(){
	list<string>::iterator current = this->listOfIndex.begin();
	while(current != this->listOfIndex.end()){
		current++;
		}

}
list<int> Search::getListOfIucs(){
	return this->listOfIucs;
}
Search::Search() {
	// TODO Auto-generated constructor stub

}

Search::~Search() {
	// TODO Auto-generated destructor stub
}
