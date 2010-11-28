/*
 * KeyString.h
 *
 *  Created on: 24/09/2010
 *      Author: oscar
 */

#ifndef KEYSTRING_H_
#define KEYSTRING_H_

#include "Key.h"

class KeyString: public Key {
public:
	KeyString(string value);
	KeyString();
	virtual ~KeyString();
	bool equals(Registry* comp);
	string getValue();
	unsigned int getSize();
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);
	int print(std::ostream& outStream);
	int getLongBytes();
	Registry* clone();
	void setValue(string value);
	int compareTo(Registry* registry);
	Registry* cloneRegKey();
private:
	string value;
};

#endif /* KEYSTRING_H_ */
