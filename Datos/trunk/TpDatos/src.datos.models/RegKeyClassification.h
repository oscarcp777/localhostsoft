/*
 * RegKeyClassification.h
 *
 *  Created on: 16/09/2010
 *      Author: oscar
 */

#ifndef REGKEYCLASSIFICATION_H_
#define REGKEYCLASSIFICATION_H_
#include "Registry.h"
class RegKeyClassification :public Registry{
public:
	RegKeyClassification();
	virtual ~RegKeyClassification();
	Registry* clone();
	bool equals(Registry* comp);
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);
	int getLongBytes() ;
	int compareTo(Registry* registry);
	unsigned int getSize();
	int print(std::ostream& outStream);
	Registry* cloneRegKey();
};

#endif /* REGKEYCLASSIFICATION_H_ */
