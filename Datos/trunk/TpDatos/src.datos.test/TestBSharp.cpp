/*
 * TestBSharp.cpp
 *
 *  Created on: 11/09/2010
 *      Author: oscar
 */

#include "TestBSharp.h"
#include "../src.datos.BTreeSharp/IndexBSharp.h"
#include "../src.datos.utils/Define.h"
#include "../src.datos.models/RegPrimary.h"
#include "../src.datos.models/KeyIndexPrimary.h"
TestBSharp::TestBSharp() {
	// TODO Auto-generated constructor stub

}

TestBSharp::~TestBSharp() {
	// TODO Auto-generated destructor stub
}
void TestBSharp::testInsert(){
     IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTree.dat",BLOCK_SIZE,TYPE_REG_PRIMARY);

     for (int var = 0; var < 100; ++var) {
    	 if(var == 13)
    		 cout<<"14 insert";
    	 else{
    		 RegPrimary* regPrimary = new RegPrimary();
    	     KeyIndexPrimary* key= new KeyIndexPrimary(var+100);
    	     regPrimary->setKey(key);
    	     regPrimary->setNumberBlock(var+4);
    	     indexBSharp->addRegistry(regPrimary);
    	 }
	}

     indexBSharp->print(std::cout);
     delete indexBSharp;

}
void TestBSharp::testsearch(){
     IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTree.dat",BLOCK_SIZE,TYPE_REG_PRIMARY);
     RegPrimary* regPrimary = new RegPrimary();
     KeyIndexPrimary* key= new KeyIndexPrimary(185);
     regPrimary->setKey(key);
     regPrimary = (RegPrimary*)indexBSharp->searchRegistry(regPrimary);
     regPrimary->print(std::cout);
     delete indexBSharp;

}
