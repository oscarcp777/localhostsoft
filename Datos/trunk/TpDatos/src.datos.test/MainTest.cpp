//============================================================================
// Name        : TpDatos.cpp
// Author      : Oscar caceres
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include "TestStorage.h"
#include "TestMailBlockManager.h"

using namespace std;

int main() {
/*
	//TEST STORAGE
   TestStorage* teststorage = new TestStorage();
   teststorage->testBlock();
   delete teststorage;

*/

//***********************************************
   	//TEST MAIL BLOCK MANAGER
      TestMailBlockManager* testMailManager = new TestMailBlockManager();
      //testMailManager->testPackMail();
      testMailManager->testUnpackMail();
      delete testMailManager;
//***********************************************

   return 0;
}
