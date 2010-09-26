/*
 * Classification.h
 *
 *  Created on: 26/09/2010
 *      Author: richy
 */

#ifndef CLASSIFICATION_H_
#define CLASSIFICATION_H_
#include "../src.datos.models/IndexConfig.h"
#include "../src.datos.BTreeSharp/IteratorBSharp.h"

class Classification {
public:
	Classification();
	virtual ~Classification();
	void loadSecondaryIndex(IndexConfig* indexConfig, IteratorBSharp* it);
private:
	void loadClassificationIndex(IndexConfig* indexConfig, IteratorBSharp* it);
	void loadSelectionIndex(IndexConfig* indexConfig, IteratorBSharp* it);
};

#endif /* CLASSIFICATION_H_ */
