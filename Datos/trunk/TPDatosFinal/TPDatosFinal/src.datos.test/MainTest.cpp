//============================================================================
// Name        : TpDatos.cpp
// Author      : Oscar caceres
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>
#include "TestBSharp.h"
#include "TestStorageController.h"
#include "TestCompression.h"
#include "TestManagerInvertedIndex.h"
#include "TestCriptography.h"
#include "TestStorage.h"



using namespace std;

int main() {

//	TestBSharp* test = new TestBSharp();
//	test->testInsert();
//	test->testsearch();
//	test->testInsertAndSearch();
//	test->testInsertRegClassification();
//	test->testsearchRegClassification();
//	test->testInsertAndSearchRegClassification();
//	test->testInsertMails();
//	test->testPrint();
//	test->testInsertAndDelete();
//	test->testInsertAndDeleteVariable();
//	delete test;
///*
	//TEST STORAGE
   TestStorage* teststorage = new TestStorage();
   teststorage->testParserMails();
   delete teststorage;

//*/

//***********************************************
   	//TEST MAIL BLOCK MANAGER
//      TestMailBlockManager* testMailManager = new TestMailBlockManager();
//      //testMailManager->testPackMail();
//      testMailManager->testUnpackMail();
//      delete testMailManager;
//***********************************************
//	TestStorageController* test = new TestStorageController();
//	test->testConnectAndCreatePrimaryIndex();
//	test->testPrintPrimaryIndex();
//	test->testSearchPrimaryIndex();



//**********************TEST MANAGER INVERTED INDEX*******************
//	TestCompression* myTest = new TestCompression();
//	myTest->testDelta2();
//	delete myTest;
//*********************************************************************

//**********************TEST CRIPTOGRAPHY******************************
//	TestCriptography* test = new TestCriptography();
//    test->unitTest();
////	test->unitTestWithBuffer();
//	delete test;
//*********************************************************************

//	TestManagerInvertedIndex* myTest = new TestManagerInvertedIndex();
//	myTest->testInsert();
//	myTest->testSearch();
//	delete myTest;

	return 0;
}


