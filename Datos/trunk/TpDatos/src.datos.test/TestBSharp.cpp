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
#include "../src.datos.models/KeyInteger.h"
#include "../src.datos.models/KeyString.h"
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
	for (int var =0; var < 10000; ++var) {
		RegPrimary* regPrimary = new RegPrimary();
		int keyInt= rand()%1000000;
		KeyInteger* key= new KeyInteger(keyInt);
		regPrimary->setKey(key);
		regPrimary->setNumberBlock(var);
//		cout<<"###########################################################"<<endl;
//		cout<<" Inserto el : ";
//		regPrimary->print(cout);
		indexBSharp->addRegistry(regPrimary);

	}

	indexBSharp->print(std::cout);
	cout<<" esto es una manteca bambino!!!"<<endl;
	delete indexBSharp;

}
void TestBSharp::testInsertMails(){
	IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTreeMails.dat",BLOCK_SIZE,TYPE_REG_PRIMARY);
	Mail* mail1 = new Mail();
	Mail* mail2= new Mail();
	Mail* mail3= new Mail();
	Mail* mail4 = new Mail();
	Mail* mail5 = new Mail();
	Mail* mail6 = new Mail();
	Mail* mail7 = new Mail();
	Mail* mail8 = new Mail();

	mail1->setDate("27/8/2009");
	mail1->setFrom("richy");
	mail1->setMessage("aprobamooooossss");
	mail1->setSubject("trabajo practico");
	mail1->setTo("yogui");

	mail2->setDate("2/5/1985");
	mail2->setFrom("ALUMNOS");
	mail2->setMessage("PLEBISITOOOOOOO YAAAAAAAAAAAAAAAAAAAAAAAA JAJJA");
	mail2->setSubject("ingenieria ");
	mail2->setTo("DAMS");

	mail3->setDate("5/5/3485");
	mail3->setFrom("yo");
	mail3->setMessage("River Plate");
	mail3->setSubject("Campeon 2010, osky este año river la rompe");
	mail3->setTo("BUBU");

	mail4->setDate("2/5/1985");
	mail4->setFrom("oscar");
	mail4->setMessage("san Lorenzo ");
	mail4->setSubject("2 a 1, la comieron bosteros horribles");
	mail4->setTo("palermo");

	mail5->setDate("2/5/1985");
	mail5->setFrom("santy");
	mail5->setMessage("auto: 207 compact full full full full fullfullfull full full fullfullfull full fullfullfull fullfullfullfullfullfull");
	mail5->setSubject("Campeon 2010");
	mail5->setTo("BUBU");

	mail6->setDate("2/5/1985");
	mail6->setFrom("facu");
	mail6->setMessage("casa quiero ir");
	mail6->setSubject("Campeon 2010");
	mail6->setTo("BUBU");


	mail7->setDate("2/5/1985");
	mail7->setFrom("fiuba");
	mail7->setMessage("mundo hola mundo hola mundo hola mundoooooooooooo");
	mail7->setSubject("Campeon 2010");
	mail7->setTo("BUBU");

	mail8->setDate("2/5/1985");
	mail8->setFrom("vaio");
	mail8->setMessage("WSOP world series of poker");
	mail8->setSubject("Campeon 2010");
	mail8->setTo("BUBU");

	RegPrimary* regPrimary1 = new RegPrimary();
	KeyInteger* key1= new KeyInteger(1);
	mail1->setKey((KeyInteger*)key1->clone());
	regPrimary1->setKey(key1);
	regPrimary1->setMail(mail1);

	RegPrimary* regPrimary2 = new RegPrimary();
	KeyInteger* key2= new KeyInteger(2);
	mail2->setKey((KeyInteger*)key2->clone());
	regPrimary2->setKey(key2);
	regPrimary2->setMail(mail2);

	RegPrimary* regPrimary3 = new RegPrimary();
	KeyInteger* key3= new KeyInteger(3);
	regPrimary3->setKey(key3);
	mail3->setKey((KeyInteger*)key3->clone());
	regPrimary3->setMail(mail3);

	RegPrimary* regPrimary4 = new RegPrimary();
	KeyInteger* key4= new KeyInteger(4);
	mail4->setKey((KeyInteger*)key4->clone());
	regPrimary4->setKey(key4);
	regPrimary4->setMail(mail4);

	RegPrimary* regPrimary5 = new RegPrimary();
	KeyInteger* key5= new KeyInteger(5);
	mail5->setKey((KeyInteger*)key5->clone());
	regPrimary5->setKey(key5);
	regPrimary5->setMail(mail5);

	RegPrimary* regPrimary6 = new RegPrimary();
	KeyInteger* key6= new KeyInteger(6);
	mail6->setKey((KeyInteger*)key6->clone());
	regPrimary6->setKey(key6);
	regPrimary6->setMail(mail6);

	RegPrimary* regPrimary7 = new RegPrimary();
	KeyInteger* key7= new KeyInteger(7);
	mail7->setKey((KeyInteger*)key7->clone());
	regPrimary7->setKey(key7);
	regPrimary7->setMail(mail7);

	RegPrimary* regPrimary8 = new RegPrimary();
	KeyInteger* key8= new KeyInteger(8);
	mail8->setKey((KeyInteger*)key8->clone());
	regPrimary8->setKey(key8);
	regPrimary8->setMail(mail8);


	indexBSharp->addRegistry(regPrimary1);
	indexBSharp->addRegistry(regPrimary2);
	indexBSharp->addRegistry(regPrimary3);
	indexBSharp->addRegistry(regPrimary4);
	indexBSharp->print(std::cout);
	indexBSharp->addRegistry(regPrimary5);
	indexBSharp->addRegistry(regPrimary6);
	indexBSharp->addRegistry(regPrimary7);
	indexBSharp->print(std::cout);
	indexBSharp->addRegistry(regPrimary8);

	indexBSharp->print(std::cout);
	cout<<" esto es una manteca bambino!!!"<<endl;
	delete indexBSharp;

}
void TestBSharp::testsearch(){
	IndexBSharp* indexBSharp = new IndexBSharp("BTree.dat",BLOCK_SIZE,TYPE_REG_PRIMARY);
	RegPrimary* regPrimary = new RegPrimary();
	KeyInteger* key= new KeyInteger(113);
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


	for (int var = 0; var < 100; ++var) {
		if(var==16)
			cout<<"";
		std::stringstream stream;
		std::stringstream attribute;
		attribute<<" attributo ";
		RegClassification* regClassif = new RegClassification();
		stream<< rand()%1000;//rand()%n los numeros van de 0 a n-1
		// 	     stream<< var;
		stream << "_numero";
		string keyString=stream.str();
		KeyString* key= new KeyString(keyString);
		regClassif->setKey(key);
		attribute<<var*2+10;
		regClassif->setAttribute(attribute.str());
		//    		 cout<<"###########################################################"<<endl;
		cout<<" Inserto el : ";
		regClassif->print(cout);
		indexBSharp->addRegistry(regClassif);
		//cout<<endl;
		stream.clear();
		attribute.clear();
		indexBSharp->print(std::cout);
	}

	indexBSharp->print(std::cout);
	cout<<" esto es una manteca bambino!!!"<<endl;
	delete indexBSharp;
}

void TestBSharp::testsearchRegClassification(){
	IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTreeRegClassifi.dat",BLOCK_SIZE,TYPE_REG_CLASSIFICATION);
	RegClassification* regClassif = new RegClassification();
	KeyString* key= new KeyString("29_numero");
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
