/*
 * RegClassification.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef REGCLASSIFICATION_H_
#define REGCLASSIFICATION_H_

#include "Registry.h"

class RegClassification: public Registry {
public:
	RegClassification();
	virtual ~RegClassification();
	Registry* clone();
	bool equals(Registry* comp);
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);
	int getLongBytes();
	Registry* cloneRegKey();
	int compareTo(Registry* registry);
	unsigned int getSize();
	int print(std::ostream& outStream);
	std::string getAttribute() ;
	void setAttribute(std::string atribute);
private:
	std::string attribute;
};

#endif /* REGCLASSIFICATION_H_ */
