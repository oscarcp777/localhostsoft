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
#include "../src.datos.models/RegClassification.h"
#include "../src.datos.models/KeyIndexPrimary.h"
#include <cstdlib>
#include<sstream>
TestBSharp::TestBSharp() {
	// TODO Auto-generated constructor stub

}

TestBSharp::~TestBSharp() {
	// TODO Auto-generated destructor stub
}
void TestBSharp::testInsert(){
     IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTree.dat",BLOCK_SIZE,TYPE_REG_PRIMARY);

     for (int var = 0; var < 500; ++var) {
    	 if(12==var)
    		 cout<<"";
    		 RegPrimary* regPrimary = new RegPrimary();
    	     KeyIndexPrimary* key= new KeyIndexPrimary(var);
    	     regPrimary->setKey(key);
    	     regPrimary->setNumberBlock(var*2);
//    	     cout<<"###########################################################"<<endl;
//    	     cout<<" Inserto el : ";
//    	     regPrimary->print(cout);
             indexBSharp->addRegistry(regPrimary);
//    	     cout<<endl;
//    	     indexBSharp->print(std::cout);

	}

     indexBSharp->print(std::cout);
     cout<<" esto es una manteca bambino!!!"<<endl;
     delete indexBSharp;

}
void TestBSharp::testsearch(){
     IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTree.dat",BLOCK_SIZE,TYPE_REG_PRIMARY);
     RegPrimary* regPrimary = new RegPrimary();
     KeyIndexPrimary* key= new KeyIndexPrimary(499);
     regPrimary->setKey(key);
     regPrimary = (RegPrimary*)indexBSharp->searchRegistry(regPrimary);
     if(regPrimary == NULL)
    	 cout<<"CLAVE: "<<key->getValue()<<" NO ENCONTRADA"<<endl;
     else
    	 regPrimary->print(std::cout);
     delete indexBSharp;

}


void TestBSharp::testInsertRegClassification(){
     IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTreeRegClassifi.dat",BLOCK_SIZE,TYPE_REG_CLASSIFICATION);


     for (int var = 0; var < 500; ++var) {
    	 if(var==16)
    		 cout<<"";
			 std::stringstream stream;
    	     std::stringstream attribute;
			 attribute<<" attributo ";
			 RegClassification* regClassif = new RegClassification();
//    	     stream<< rand()%200;//rand()%n los numeros van de 0 a n-1
    	     stream<< var;
    	     stream << "_numero";
    	     string keyString=stream.str();
    		 Key* key= new Key(keyString);
    		 regClassif->setKey(key);
    		 attribute<<var*2+10;
    		 regClassif->setAttribute(attribute.str());
//    		 cout<<"###########################################################"<<endl;
//             cout<<" Inserto el : ";
             regClassif->print(cout);
             indexBSharp->addRegistry(regClassif);
//    	     cout<<endl;
    	     stream.clear();
    	     attribute.clear();
//    	     indexBSharp->print(std::cout);
	}

     indexBSharp->print(std::cout);
     cout<<" esto es una manteca bambino!!!"<<endl;
       delete indexBSharp;
}

void TestBSharp::testsearchRegClassification(){
     IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTreeRegClassifi.dat",BLOCK_SIZE,TYPE_REG_CLASSIFICATION);
     RegClassification* regClassif = new RegClassification();
     Key* key= new Key();
     key->setValue("29_numero");
     regClassif->setKey(key);
     RegClassification* regFind = (RegClassification*)indexBSharp->searchRegistry(regClassif);
     if(regFind == NULL)
    	 cout<<"CLAVE: "<<key->getValue()<<" NO ENCONTRADA"<<endl;
     else
    	 regFind->print(std::cout);
     delete regClassif;
     delete regFind;
     delete indexBSharp;

}
