/*
 * Key.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef KEY_H_
#define KEY_H_


#include "Registry.h"

class Key: public Registry {
public:
	Key(string value);
	Key();
	virtual ~Key();
	bool equals(Registry* comp);
	string getValue();
	int getSize();
	int getValueInt();
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);
    int print();
private:
	string value;
};

#endif /* KEY_H_ */
