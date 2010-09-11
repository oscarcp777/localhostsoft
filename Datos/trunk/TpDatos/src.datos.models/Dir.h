/*
 * Dir.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef DIR_H_
#define DIR_H_

#include "Registry.h"

class Dir: public Registry {
public:
	Dir();
	virtual ~Dir();
	bool equals(Registry* comp);
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);
	int getLongBytes();
	int print(std::ostream& outStream);
	int getSize();
};

#endif /* DIR_H_ */
