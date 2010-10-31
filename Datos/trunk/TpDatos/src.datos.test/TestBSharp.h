/*
 * TestBSharp.h
 *
 *  Created on: 11/09/2010
 *      Author: oscar
 */

#ifndef TESTBSHARP_H_
#define TESTBSHARP_H_
#include <iostream>
using namespace std;
class TestBSharp {
public:
	TestBSharp();
	virtual ~TestBSharp();
	void testInsert();
	void testInsertAndSearch();
	void testsearch();
	void testInsertRegClassification();
	void testsearchRegClassification();
	void testInsertMails();
	void testIterator();
	void testInsertRegSelection();
	void testInsertAndSearchRegClassification();
	void testPrint();
	void testInsertAndDelete();
	void testInsertAndDeleteVariable();
};

#endif /* TESTBSHARP_H_ */
