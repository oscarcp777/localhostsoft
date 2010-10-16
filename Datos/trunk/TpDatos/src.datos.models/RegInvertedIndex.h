/*
 * RegInvertedIndex.h
 *
 *  Created on: 16/10/2010
 *      Author: Facundo
 */

#ifndef REGINVERTEDINDEX_H_
#define REGINVERTEDINDEX_H_

#include "Registry.h"
#include "Key.h"
#include "KeyString.h"
#include "InfoPerDoc.h"
#include <list>

class RegInvertedIndex: public Registry {

public:
	RegInvertedIndex();
	virtual ~RegInvertedIndex();
	void addInfoPerDoc(InfoPerDoc* infoPerDoc);
	InfoPerDoc* getFirstInfoPerDoc();
	bool equals(Registry* comp);
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);
	int getLongBytes();
	Registry* clone();
	Registry* cloneRegKey();
	int compareTo(Registry* registry);
	unsigned int getSize();
	int print(std::ostream& outStream);
	void setNumBlock(int numBlock);
private:
	int numBlock;
	list<InfoPerDoc*> infoPerDoc;

};

#endif /* REGINVERTEDINDEX_H_ */
