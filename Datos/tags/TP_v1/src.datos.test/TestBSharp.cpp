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
     IndexBSharp* indexBSharp = new IndexBSharp("BTree.dat",BLOCK_SIZE,TYPE_REG_PRIMARY);

     for (int var = 0; var < 300; ++var) {
    	 if(21==var)
    		 cout<<"";
    		 RegPrimary* regPrimary = new RegPrimary();
    	     KeyIndexPrimary* key= new KeyIndexPrimary(rand()%200);
    	     regPrimary->setKey(key);
    	     regPrimary->setNumberBlock(var*2);
//    	     cout<<"###########################################################"<<endl;
//    	     cout<<" Inserto el : ";
//    	     regPrimary->print(cout);
             indexBSharp->addRegistry(regPrimary);
    	     cout<<endl;
//    	     indexBSharp->print(std::cout);

	}

     indexBSharp->print(std::cout);
     cout<<" esto es una manteca bambino!!!"<<endl;
     delete indexBSharp;

}
void TestBSharp::testsearch(){
     IndexBSharp* indexBSharp = new IndexBSharp("BTree.dat",BLOCK_SIZE,TYPE_REG_PRIMARY);
     RegPrimary* regPrimary = new RegPrimary();
     KeyIndexPrimary* key= new KeyIndexPrimary(113);
     regPrimary->setKey(key);
     regPrimary = (RegPrimary*)indexBSharp->searchRegistry(regPrimary);
     if(regPrimary == NULL)
    	 cout<<"CLAVE: "<<key->getValue()<<" NO ENCONTRADA"<<endl;
     else
    	 regPrimary->print(std::cout);
     delete indexBSharp;

}


void TestBSharp::testInsertRegClassification(){
     IndexBSharp* indexBSharp = new IndexBSharp("BTreeRegClassifi.dat",BLOCK_SIZE,TYPE_REG_CLASSIFICATION);


     for (int var = 0; var < 6; ++var) {
    	 if(var==4)
    		 cout<<"";
			 std::stringstream stream;
    	     std::stringstream attribute;
			 stream << "numero ";
			 attribute<<" attributo ";
			 RegClassification* regClassif = new RegClassification();
    	     stream<< rand()%200;//rand()%n los numeros van de 0 a n-1
    	     //cout<<"stream "<<stream.str()<<endl;
    		 Key* key= new Key(stream.str());
    		 regClassif->setKey(key);
    		 attribute<<var*2;
    		//cout<<"atributo: "<<attribute.str()<<endl;
    		 regClassif->setAttribute(attribute.str());
             indexBSharp->addRegistry(regClassif);
    	     cout<<endl;
    	     stream.clear();
    	     attribute.clear();
    	     indexBSharp->print(std::cout);
	}

     indexBSharp->print(std::cout);
     delete indexBSharp;

}

void TestBSharp::testsearchRegClassification(){
     IndexBSharp* indexBSharp = new IndexBSharp("BTreeRegClassifi.dat",BLOCK_SIZE,TYPE_REG_CLASSIFICATION);
     RegClassification* regClassif = new RegClassification();
     Key* key= new Key();
     key->setValue("numero 177");
     regClassif->setKey(key);
     regClassif = (RegClassification*)indexBSharp->searchRegistry(regClassif);
     if(regClassif == NULL)
    	 cout<<"CLAVE: "<<key->getValue()<<" NO ENCONTRADA"<<endl;
     else
    	 regClassif->print(std::cout);
     delete indexBSharp;

}
