/*
 * Component.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_
#include "../src.datos.storage/Buffer.h"
#include "../src.datos.utils/Define.h"
#include <iostream>
#include <sstream>
class Component {

public:
	Component();
	virtual ~Component();
	virtual int getSize()=0;
	virtual int print()=0;
	virtual int getLongBytes() = 0;
	virtual void pack(Buffer* buffer)=0;
	virtual void unPack(Buffer* buffer)=0;
};

#endif /* COMPONENT_H_ */
