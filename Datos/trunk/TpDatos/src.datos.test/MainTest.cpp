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
#include "TestManagerInvertedIndex.h"



using namespace std;

int main12345(int argc,char** argv) {

//	TestBSharp* test = new TestBSharp();
//	test->testInsert();
//	test->testsearch();
//	test->testInsertAndSearch();
//	test->testInsertRegClassification();
//	test->testsearchRegClassification();
//	test->testInsertAndSearchRegClassification();
//	test->testInsertMails();
//	test->testPrint();
//	delete test;
/*
	//TEST STORAGE
   TestStorage* teststorage = new TestStorage();
   teststorage->testBlock();
   delete teststorage;

*/

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
	TestManagerInvertedIndex* myTest = new TestManagerInvertedIndex();
	myTest->test();
	delete myTest;
//*********************************************************************
	return 0;
}


