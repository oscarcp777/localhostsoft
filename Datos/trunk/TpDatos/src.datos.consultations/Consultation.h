/*
 * Consultation.h
 *
 *  Created on: 28/09/2010
 *      Author: richy
 */

#ifndef CONSULTATION_H_
#define CONSULTATION_H_
#include "../src.datos.models/Mail.h"
#include "../src.datos.models/IndexConfig.h"
#include "../src.datos.models/RegPrimary.h"
#include <list>
class Consultation {
public:
	Consultation();
	virtual ~Consultation();
	void consultPrimaryIndex(IndexConfig* indexConfig,RegPrimary* regPrimary);
	void consultSecondaryIndex(IndexConfig* indexConfig,list<int>* listOfIucs, string filterValue);
};

#endif /* CONSULTATION_H_ */
