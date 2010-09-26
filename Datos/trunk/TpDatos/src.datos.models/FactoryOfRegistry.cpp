/*
 * FactoryOfRegistry.cpp
 *
 *  Created on: 12/09/2010
 *      Author: oscar
 */

#include "FactoryOfRegistry.h"
#include "Mail.h"
#include "RegPrimary.h"
#include "RegKeyPrimary.h"
#include "KeyInteger.h"
#include "RegClassification.h"
#include "RegSelection.h"
#include "RegKeyClassification.h"
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
	case TYPE_REG_KEY_PRIMARY: return new RegKeyPrimary();
		break;
	case TYPE_REG_CLASSIFICATION: return new RegClassification();
			break;
	case TYPE_REG_KEY_CLASSIF_INDEX: return new RegKeyClassification();
			break;
	case TYPE_MAIL: return new Mail();
		break;
	case TYPE_REG_SELECTION: return new RegSelection();
			break;

	default: return NULL;
	}
}
