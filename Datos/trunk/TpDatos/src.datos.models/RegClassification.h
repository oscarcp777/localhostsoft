/*
 * RegClassification.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef REGCLASSIFICATION_H_
#define REGCLASSIFICATION_H_

#include "Registry.h"

class RegClassification: public Registry {
public:
	RegClassification();
	virtual ~RegClassification();
	Registry* clone();
};

#endif /* REGCLASSIFICATION_H_ */
