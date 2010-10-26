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
#include "Registry.h"
#include "KeyInteger.h"
using namespace std;

class InfoPerDoc : public Registry{
public:
	InfoPerDoc();
	virtual ~InfoPerDoc();
	void packCompressed(BitOutput* compressor);
	void unPackCompressed(BitInput* compressor);
	unsigned int getlongBytesCompressed();
	Registry* clone();
	bool equals(Registry* comp);
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);
	int getLongBytes();
	Registry* cloneRegKey();
	int compareTo(Registry* registry);
	unsigned int getSize();
	int print(std::ostream& outStream);
	void setIuc(int iuc);
	int getIuc();
	void addPosition(KeyInteger* pos);
	bool compareDistance(InfoPerDoc* infoPerDoc, int distance);
	list<KeyInteger*>::iterator getBeginListPositions();
	list<KeyInteger*>::iterator getEndListPositions();

private:

	list<KeyInteger*> listOfPositions;
};

#endif /* INFOPERDOC_H_ */
