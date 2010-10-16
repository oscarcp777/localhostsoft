/*
 * InfoPerDoc.h
 *
 *  Created on: 16/10/2010
 *      Author: Facundo
 */

#ifndef INFOPERDOC_H_
#define INFOPERDOC_H_

#include "KeyInteger.h"
#include <list>

class InfoPerDoc {
public:
	InfoPerDoc();
	virtual ~InfoPerDoc();
private:
	KeyInteger* iuc;
	list <int> listOfPositions;
};

#endif /* INFOPERDOC_H_ */
