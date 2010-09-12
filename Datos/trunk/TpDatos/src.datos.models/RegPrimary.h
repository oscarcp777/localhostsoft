/*
 * RegPrimary.h
 *
 *  Created on: 11/09/2010
 *      Author: oscar
 */

#ifndef REGPRIMARY_H_
#define REGPRIMARY_H_
#include "Registry.h"
#include <list>

class RegPrimary : public Registry {
public:
	RegPrimary();

	virtual ~RegPrimary();
	Registry* clone();
	bool equals(Registry* comp);
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);
	int getLongBytes() ;
	int compareTo(Registry* registry);
	int getSize();
	int print(std::ostream& outStream);
    int getNumberBlock() ;
    void setNumberBlock(int numberBlock);


private:
	int numberBlock;
};

#endif /* REGPRIMARY_H_ */
