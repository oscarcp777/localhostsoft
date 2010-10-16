/*
 * InfoPerDoc.h
 *
 *  Created on: 16/10/2010
 *      Author: Facundo
 */

#ifndef INFOPERDOC_H_
#define INFOPERDOC_H_

#include <list>
#include <iostream>
using namespace std;

class InfoPerDoc {
public:
	InfoPerDoc(int iuc);
	virtual ~InfoPerDoc();
	void setIuc(int iuc);
	int getIuc();
	void addPosition(int pos);
	void print(std::ostream& outStream);
private:
	int iuc;
	list<int> listOfPositions;
};

#endif /* INFOPERDOC_H_ */
