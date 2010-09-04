/*
 * Component.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_
#include "../src.datos.storage/Buffer.h"

class Component {

public:
	Component();
	virtual ~Component();
	virtual void pack(Buffer* buffer)=0;
	virtual void unPack(Buffer* buffer)=0;
};

#endif /* COMPONENT_H_ */
