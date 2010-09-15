/*
 * FactoryOfRegistry.cpp
 *
 *  Created on: 12/09/2010
 *      Author: oscar
 */

#include "FactoryOfRegistry.h"
#include "Mail.h"
#include "RegPrimary.h"
#include "Dir.h"
#include "KeyIndexPrimary.h"
#include "../src.datos.utils/Define.h"

FactoryOfRegistry::FactoryOfRegistry() {
	// TODO Auto-generated constructor stub

}

FactoryOfRegistry::~FactoryOfRegistry() {
	// TODO Auto-generated destructor stub
}
Registry* FactoryOfRegistry::createRegistry(int type){

	switch(type){

	case TYPE_REG_PRIMARY: return new RegPrimary();
	break;
	case TYPE_MAIL: return new Mail();
	break;
	case TYPE_DIRECTION: return new Dir();
	break;
	case TYPE_KEY: return new RegPrimary(true);
	break;
	default: return NULL;
	}
}
