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
	Key();
	virtual ~Key();
	bool equals(Component* comp);
	int getValue();

private:
	int value;
};

#endif /* KEY_H_ */
