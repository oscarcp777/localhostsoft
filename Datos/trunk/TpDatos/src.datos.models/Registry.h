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
	virtual bool equals(Registry* comp)=0;
	Key* getKey();
	void setKey(Key* key);
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);
protected:
	Key* key;
};

#endif /* REGISTRY_H_ */
