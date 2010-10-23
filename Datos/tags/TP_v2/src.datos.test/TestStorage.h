/*
 * TestStorage.h
 *
 *  Created on: 04/09/2010
 *      Author: oscar
 */

#ifndef TESTSTORAGE_H_
#define TESTSTORAGE_H_
#include "../src.datos.models/Mail.h"
#include "../src.datos.storage/Buffer.h"
#include "../src.datos.storage/BinaryFile.h"
class TestStorage {
public:
	TestStorage();
	virtual ~TestStorage();
	void testMails();
	void testBlock();
};

#endif /* TESTSTORAGE_H_ */
