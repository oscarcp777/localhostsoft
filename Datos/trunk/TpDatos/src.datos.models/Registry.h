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
	virtual void pack(Buffer* buffer)=0;
	virtual void unPack(Buffer* buffer)=0;
	virtual int getLongBytes() = 0;
	virtual Registry* clone() = 0;
	virtual int compareTo(Registry* registry) = 0;
    bool isInternal();
    void setInternal(bool internal);
protected:
	Key* key;
	bool internal;
};

#endif /* REGISTRY_H_ */