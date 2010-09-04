/*
 * Registry.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef REGISTRY_H_
#define REGISTRY_H_

#include "Component.h"

class Key;

class Registry: public Component {
public:
	Registry();
	virtual ~Registry();
	virtual bool equals(Component* comp)=0;
	Key* getKey();
private:
	Key* key;
};

#endif /* REGISTRY_H_ */
