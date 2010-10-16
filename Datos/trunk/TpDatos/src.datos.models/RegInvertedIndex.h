/*
 * RegInvertedIndex.h
 *
 *  Created on: 16/10/2010
 *      Author: Facundo
 */

#ifndef REGINVERTEDINDEX_H_
#define REGINVERTEDINDEX_H_

#include "Registry.h"
#include "InfoPerDoc.h"
#include <list>

class RegInvertedIndex{

public:
	RegInvertedIndex();
	virtual ~RegInvertedIndex();

private:
//	string word;
	int numBlock;
	list<InfoPerDoc*> infoPerDoc;

};

#endif /* REGINVERTEDINDEX_H_ */
