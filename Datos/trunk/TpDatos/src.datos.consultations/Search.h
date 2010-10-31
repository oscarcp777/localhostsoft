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
	void pushStrSearch(std::string strSearch);
	std::string popStrSearch();
	void setIndex(std::string index);
	std::string getIndex();
	void setIuc(int iuc);
	void printIndexNames();
	Search();
	virtual ~Search();
	list<int> getListOfIucs();
	list<int>::iterator getIteratorBeginListOfIucs();
	list<int>::iterator getIteratorEndListOfIucs();
	unsigned int getNumOfIndex();
	void setNumOfIndex(int size);
private:
	int sizeOfIndexes;
	list<string> listStrSearch;
	list<string> listOfIndex;
	list<int> listOfIucs;
};

#endif /* SEARCH_H_ */
