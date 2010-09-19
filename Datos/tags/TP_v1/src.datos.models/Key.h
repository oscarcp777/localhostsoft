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
	virtual bool equals(Registry* comp);
	string getValue();
	virtual unsigned int getSize();
	virtual void pack(Buffer* buffer);
	virtual void unPack(Buffer* buffer);
	virtual int print(std::ostream& outStream);
    virtual int getLongBytes();
    Registry* clone();
    void setValue(string value);
    virtual int compareTo(Registry* registry);
    Registry* cloneRegKey();

private:
	string value;
};

#endif /* KEY_H_ */