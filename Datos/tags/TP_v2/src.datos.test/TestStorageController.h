/*
 * TestStorageController.h
 *
 *  Created on: 25/09/2010
 *      Author: richy
 */

#ifndef TESTSTORAGECONTROLLER_H_
#define TESTSTORAGECONTROLLER_H_

class TestStorageController {
public:
	TestStorageController();
	virtual ~TestStorageController();
	void testConnectAndCreatePrimaryIndex();
	void testPrintPrimaryIndex();
	void testSearchPrimaryIndex();
	void testIteratorPrimaryIndex();
};

#endif /* TESTSTORAGECONTROLLER_H_ */