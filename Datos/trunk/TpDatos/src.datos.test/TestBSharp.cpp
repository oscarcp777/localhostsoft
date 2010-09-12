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
     RegPrimary* regPrimary = new RegPrimary();
     KeyIndexPrimary* key= new KeyIndexPrimary(1);
     regPrimary->setKey(key);
     regPrimary->setNumberBlock(0);
     indexBSharp->addRegistry(regPrimary);
     delete indexBSharp;

}
void TestBSharp::testsearch(){
     IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTree.dat",BLOCK_SIZE,TYPE_REG_PRIMARY);
     RegPrimary* regPrimary = new RegPrimary();
     KeyIndexPrimary* key= new KeyIndexPrimary(1);
     regPrimary->setKey(key);
     indexBSharp->searchRegistry(regPrimary);
     indexBSharp->print(std::cout);
     delete indexBSharp;

}
