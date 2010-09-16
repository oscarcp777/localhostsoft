/*
 * TestMailBlockManager.h
 *
 *  Created on: 09/09/2010
 *      Author: richy
 */

#ifndef TESTMAILBLOCKMANAGER_H_
#define TESTMAILBLOCKMANAGER_H_
#include "../src.datos.storage/MailBlockManager.h"
#include "../src.datos.utils/Define.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "../src.datos.models/Mail.h"


class TestMailBlockManager {
public:
	TestMailBlockManager();
	virtual ~TestMailBlockManager();
	void testPackMail();
	void testUnpackMail();
};

#endif /* TESTMAILBLOCKMANAGER_H_ */
