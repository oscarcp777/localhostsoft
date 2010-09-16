/*
 * RegKeyPrimary.h
 *
 *  Created on: 16/09/2010
 *      Author: oscar
 */

#ifndef REGKEYPRIMARY_H_
#define REGKEYPRIMARY_H_
#include "Registry.h"

class RegKeyPrimary :public Registry {
public:
	RegKeyPrimary();
	virtual ~RegKeyPrimary();
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

#endif /* REGKEYPRIMARY_H_ */
