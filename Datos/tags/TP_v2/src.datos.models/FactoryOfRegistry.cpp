/*
 * FactoryOfRegistry.cpp
 *
 *  Created on: 12/09/2010
 *      Author: oscar
 */

#include "FactoryOfRegistry.h"
#include "Mail.h"
#include "RegPrimary.h"
#include "KeyString.h"
#include "KeyInteger.h"
#include "RegClassification.h"
#include "RegSelection.h"
#include "RegInvertedIndex.h"
#include "InfoPerDoc.h"
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
	case TYPE_REG_CLASSIFICATION: return new RegClassification();
			break;
	case TYPE_MAIL: return new Mail();
		break;
	case TYPE_REG_SELECTION: return new RegSelection();
			break;
	case TYPE_KEY_INTEGER: return new KeyInteger(-1);
				break;
	case TYPE_KEY_STRING: return new KeyString("");
					break;
	case TYPE_REG_INVERTED_INDEX: return new RegInvertedIndex();
						break;
	case TYPE_INFO_PER_DOC: return new InfoPerDoc();
							break;
	default: return NULL;
	}
}
