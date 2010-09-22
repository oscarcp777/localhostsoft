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


using namespace std;

int mainsfesf(int argc,char** argv) {
	TestBSharp* test= new TestBSharp();
	test->testInsert();
//	test->testsearch();
//	test->testInsertRegClassification();
//	test->testsearchRegClassification();
	delete test;
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


   return 0;
}


