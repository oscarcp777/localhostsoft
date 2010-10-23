/*
 * TestManagerInvertedIndex.cpp
 *
 *  Created on: 16/10/2010
 *      Author: richy
 */

#include "TestManagerInvertedIndex.h"
#include "../src.datos.BTreeSharp/IndexBSharp.h"

TestManagerInvertedIndex::TestManagerInvertedIndex() {
	// TODO Auto-generated constructor stub

}

TestManagerInvertedIndex::~TestManagerInvertedIndex() {
	// TODO Auto-generated destructor stub
}
void TestManagerInvertedIndex::testInsert(){
	IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTree.dat",BLOCK_SIZE,TYPE_REG_INVERTED_INDEX);

	ManagerInvertedIndex* manager = new ManagerInvertedIndex();
	Mail* mail = new Mail();
	Mail* mail2 = new Mail();
	KeyInteger* key = new KeyInteger(10);
	KeyInteger* key2 = new KeyInteger(25);

	mail->setKey(key);
	mail->setDate("27/8/2009");
	mail->setFrom("richy@lalala.com.ar");
	mail->setMessage("Hola CARACAS mundo borra la ARGENTINA siguiente stop word ARGENTINA aqui ahi ahì CARACAS lo mas fragil mundo de la locura ARGENTINA trabajo ser trabajan ARGENTINA voy al mundia de brasil ARGENTINA");
	mail->setSubject("trabajo practico");
	mail->setTo("yogui");

	mail2->setKey(key2);
	mail2->setDate("27/8/2009");
	mail2->setFrom("richy@lalala.com.ar");
	mail2->setMessage("ARGENTINA CARACAS brasil ARGENTINA");
	mail2->setSubject("trabajo practico");
	mail2->setTo("yogui");

	manager->loadMessageWords(mail,indexBSharp);
	manager->loadMessageWords(mail2,indexBSharp);

	indexBSharp->print(std::cout);
	delete indexBSharp;
		cout<<" esto es una manteca bambino!!!"<<endl;
	delete manager;
	delete mail;


}
void TestManagerInvertedIndex::testSearch(){
	IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTree.dat",BLOCK_SIZE,TYPE_REG_INVERTED_INDEX);
	RegInvertedIndex* regInvertedIndex= new RegInvertedIndex();
	regInvertedIndex->setKey(new KeyString("ARGENTINA"));
	indexBSharp->searchRegistry(regInvertedIndex);
	regInvertedIndex->print(cout);
	delete indexBSharp;
	delete regInvertedIndex;
	cout<<" esto es una manteca bambino!!!"<<endl;
}
