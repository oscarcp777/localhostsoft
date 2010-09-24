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
	virtual bool equals(Registry* comp)=0;
	virtual unsigned int getSize()=0;
	virtual void pack(Buffer* buffer)=0;
	virtual void unPack(Buffer* buffer)=0;
	virtual int print(std::ostream& outStream)=0;
    virtual int getLongBytes()=0;
    Registry* clone()=0;
    virtual int compareTo(Registry* registry)=0;
    Registry* cloneRegKey()=0;


};

#endif /* KEY_H_ */
