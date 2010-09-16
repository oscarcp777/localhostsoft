/*
 * KeyIndexPrimary.h
 *
 *  Created on: 11/09/2010
 *      Author: oscar
 */

#ifndef KEYINDEXPRIMARY_H_
#define KEYINDEXPRIMARY_H_
#include "Key.h"

class KeyIndexPrimary :public Key{
public:
	KeyIndexPrimary(int value);
	KeyIndexPrimary();
	virtual ~KeyIndexPrimary();
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);
	unsigned int getSize();
	int getLongBytes();
	int print(std::ostream& outStream);
	bool equals(Registry* comp);
	int getValue();
	int compareTo(Registry* registry);
	Registry* clone();
	Registry* cloneRegKey();

private:
	int value;
};

#endif /* KEYINDEXPRIMARY_H_ */
