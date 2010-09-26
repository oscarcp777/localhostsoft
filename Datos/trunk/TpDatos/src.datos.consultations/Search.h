/*
 * Search.h
 *
 *  Created on: 26/09/2010
 *      Author: Facundo
 */

#ifndef SEARCH_H_
#define SEARCH_H_

#include <string>
#include <list>

using namespace std;
class Search {
public:
	int sizeOfListIndex();
	void setStrSearch(std::string strSearch);
	std::string getStrSearch();
	void setIndex(std::string index);
	std::string getIndex();
	void printIndexNames();
	Search();
	virtual ~Search();
private:
	std::string strSearch;
	list<string> listOfIndex;
};

#endif /* SEARCH_H_ */
