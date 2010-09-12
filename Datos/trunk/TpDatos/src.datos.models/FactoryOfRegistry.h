/*
 * FactoryOfRegistry.h
 *
 *  Created on: 12/09/2010
 *      Author: oscar
 */

#ifndef FACTORYOFREGISTRY_H_
#define FACTORYOFREGISTRY_H_
#include "Registry.h"

class FactoryOfRegistry {
public:
	FactoryOfRegistry();
	virtual ~FactoryOfRegistry();
	Registry* createRegistry(int type);
};

#endif /* FACTORYOFREGISTRY_H_ */
