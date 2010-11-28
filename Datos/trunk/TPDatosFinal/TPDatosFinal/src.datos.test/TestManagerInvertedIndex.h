/*
 * TestManagerInvertedIndex.h
 *
 *  Created on: 16/10/2010
 *      Author: richy
 */

#ifndef TESTMANAGERINVERTEDINDEX_H_
#define TESTMANAGERINVERTEDINDEX_H_
#include "../src.datos.controller/ManagerInvertedIndex.h"
#include "../src.datos.models/KeyInteger.h"

class TestManagerInvertedIndex {
public:
	TestManagerInvertedIndex();
	virtual ~TestManagerInvertedIndex();
	void testInsert();
	void testSearch();
};

#endif /* TESTMANAGERINVERTEDINDEX_H_ */
