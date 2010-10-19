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

private:

	list<KeyInteger*> listOfPositions;
};

#endif /* INFOPERDOC_H_ */
