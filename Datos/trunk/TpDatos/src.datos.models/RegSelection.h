/*
 * RegSelection.h
 *
 *  Created on: 26/09/2010
 *      Author: richy
 */

#ifndef REGSELECTION_H_
#define REGSELECTION_H_
#include "Registry.h"

class RegSelection : public Registry{
public:
	RegSelection();
	virtual ~RegSelection();
	Registry* clone();
	bool equals(Registry* comp);
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);
	int getLongBytes();
	Registry* cloneRegKey();
	int compareTo(Registry* registry);
	unsigned int getSize();
	int print(std::ostream& outStream);

};

#endif /* REGSELECTION_H_ */
