/*
 * TestBSharp.cpp
 *
 *  Created on: 11/09/2010
 *      Author: oscar
 */

#include "TestBSharp.h"
#include "../src.datos.BTreeSharp/IndexBSharp.h"
#include "../src.datos.utils/Define.h"
#include "../src.datos.utils/StringUtils.h"
#include "../src.datos.models/RegPrimary.h"
#include "../src.datos.models/RegClassification.h"
#include "../src.datos.models/KeyInteger.h"
#include "../src.datos.models/RegSelection.h"
#include "../src.datos.models/KeyString.h"
#include <cstdlib>
#include<sstream>
#include <map>
TestBSharp::TestBSharp() {
	// TODO Auto-generated constructor stub

}

TestBSharp::~TestBSharp() {
	// TODO Auto-generated destructor stub
}
void TestBSharp::testInsert(){
	/* initialize random seed: */
	IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTree.dat",BLOCK_SIZE,TYPE_REG_PRIMARY);
	for (int var =0; var < 10000; ++var) {
		RegPrimary* regPrimary = new RegPrimary();
		int keyInt=rand()%1000000;
		KeyInteger* key= new KeyInteger(keyInt);
		regPrimary->setKey(key);
		regPrimary->setNumberBlock(var);
		//		cout<<" Inserto el : ";
		//		regPrimary->print(cout);
		indexBSharp->addRegistry(regPrimary);
		//		indexBSharp->print(std::cout);
	}
	indexBSharp->print(std::cout);
	delete indexBSharp;
	cout<<" esto es una manteca bambino!!!"<<endl;


}
void TestBSharp::testInsertAndDelete(){
	/* initialize random seed: */
	int cantidad_insertar = 50000;
	map<int,int> vecInserts;
//	std::map vecInserts[cantidad_insertar];
	IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTree.dat",BLOCK_SIZE,TYPE_REG_PRIMARY);
	for (int var =0; var < cantidad_insertar; ++var) {
		int keyInt=rand()%1000000;
		vecInserts[keyInt] = keyInt;
	}
	int i=0;
	std::map<int,int>::iterator it;
	int var = 0;
	for(it = vecInserts.begin() ; it != vecInserts.end(); it++){
		RegPrimary* regPrimary = new RegPrimary();
		KeyInteger* key= new KeyInteger((*it).second);
		regPrimary->setKey(key);
		regPrimary->setNumberBlock(var);
//		cout<<" Inserto el : "<<i++;
//		regPrimary->print(cout);
		indexBSharp->addRegistry(regPrimary);
		var++;
		}

	indexBSharp->print(std::cout);

i=0;
	for(it = (vecInserts.end())-- ; it != vecInserts.begin(); it--){
		i++;
//		if (i >=3018)
//			indexBSharp->print(std::cout);
		RegPrimary* regPrimary = new RegPrimary();
		KeyInteger* key= new KeyInteger((*it).second);
		regPrimary->setKey(key);
//		cout<<" Deleteo el : "<<i<<" ";
//		regPrimary->print(cout);
		indexBSharp->deleteRegistry(regPrimary);
	}
	RegPrimary* regPrimary = new RegPrimary();
	KeyInteger* key= new KeyInteger((*it).second);
	regPrimary->setKey(key);
	cout<<" Deleteo el : ";
	regPrimary->print(cout);
	indexBSharp->deleteRegistry(regPrimary);

	//	for (int var = cantidad_insertar-1; var >= 0; --var) {
	//			RegPrimary* regPrimary = new RegPrimary();
	//			int keyInt = vecInserts[var];
	//			KeyInteger* key= new KeyInteger(keyInt);
	//			regPrimary->setKey(key);
	//			regPrimary->setNumberBlock(var);
	////			if (var >= 491){
	////				std::cout <<"";
	////				indexBSharp->print(std::cout);
	////			}
	//			std::cout << "----A Eliminar----";
	//					std::cout << "ID: " << keyInt << std::endl;
	//
	//			indexBSharp->deleteRegistry(regPrimary);
	//
	//			std::cout << "VAR: " << var << " REGISTRO ELIMINADO id: " << keyInt << std::endl;
	//		}
	indexBSharp->print(std::cout);

	delete indexBSharp;
	cout<<" esto es una manteca bambino!!!"<<endl;

}
void TestBSharp::testInsertAndSearch(){
	int cantidadAInsertar = 50000;
	IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTreeInsertandSearch.dat",BLOCK_SIZE,TYPE_REG_PRIMARY);
	indexBSharp->print(std::cout);
	int vecInserts[cantidadAInsertar];
	int j=0;
	for (int var =0; var < cantidadAInsertar; ++var) {
		RegPrimary* regPrimary = new RegPrimary();
		int keyInt=rand()%1000000;
		KeyInteger* key= new KeyInteger(keyInt);
		regPrimary->setKey(key);
		regPrimary->setNumberBlock(var);
		indexBSharp->addRegistry(regPrimary);
		vecInserts[var]=keyInt;
	}
	for (int var = cantidadAInsertar - 1; var >= 0; --var) {
		RegPrimary* regPrimary = new RegPrimary();
		KeyInteger* key= new KeyInteger(vecInserts[var]);
		regPrimary->setKey(key);
		regPrimary = (RegPrimary*)indexBSharp->searchRegistry(regPrimary);
		if(regPrimary == NULL)
			cout<<"CLAVE: "<<key->getValue()<<" NO ENCONTRADA"<<endl;
		else{
			cout<<"SE ENCONTRO : ";
			regPrimary->print(std::cout);
			j++;
		}
	}
	cout<<" Se encontraron "<< j << " registros!" <<endl;
	delete indexBSharp;
}
void TestBSharp::testInsertAndSearchRegClassification(){
	int cantidadAInsertar = 1000;
	vector<string> vec;
	srand(time(NULL));
	int j=0;
	IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTreeRegClassifi.dat",BLOCK_SIZE,TYPE_REG_CLASSIFICATION);
	for (int var = 0; var < cantidadAInsertar; ++var) {
		RegClassification* regClassif = new RegClassification();
		string keyString=StringUtils::getPassword(15);
		vec.push_back(keyString);
		KeyString* key= new KeyString(keyString);
		regClassif->setKey(key);
		regClassif->setNumBlock(var);
		regClassif->addIuc(new KeyInteger(var));
		cout<<"\n  Inserto el : "<<var<<" ";
		//					regClassif->print(cout);
		indexBSharp->addRegistry(regClassif);
	}
	indexBSharp->print(std::cout);
   cout<<"inserto bien"<<endl;
	for (std::vector<string>::iterator it=vec.begin(); it!=vec.end(); ++it) {
		RegClassification* regClassif = new RegClassification();
		KeyString* key= new KeyString(*it);
		regClassif->setKey(key);
		RegClassification* regClassifind= (RegClassification*)indexBSharp->searchRegistry(regClassif);
		if(regClassif == NULL){
			cout<<"CLAVE: "<<key->getValue()<<" NO ENCONTRADA"<<endl;
			j++;
		}else{
			regClassifind->print(cout);
		}

		delete regClassif;
//		delete regClassifind;
	}
	cout<<"No Se encontraron "<< j << " registros!" <<endl;
	delete indexBSharp;
}
void TestBSharp::testsearchRegClassification(){
	IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTreeRegClassifi.dat",BLOCK_SIZE,TYPE_REG_CLASSIFICATION);
	indexBSharp->print(cout);
	return;
	RegClassification* regClassif = new RegClassification();
	KeyString* key= new KeyString("3bmTRQYeUovy");
	regClassif->setKey(key);
	regClassif->addIuc(new KeyInteger(620));
	RegClassification* regFind = NULL;
//	regFind = (RegClassification*)indexBSharp->searchRegistry(regClassif);
		indexBSharp->deleteRegistry(regClassif);
//	indexBSharp->addRegistry(regClassif);lista de Iuc : (620)(678)
	if(regFind == NULL)
		cout<<"CLAVE: "<<"03g"<<" NO ENCONTRADA"<<endl;
	else
		regFind->print(std::cout);
//	delete regClassif;
//	delete regFind;
		indexBSharp->print(cout);
	delete indexBSharp;

}

void TestBSharp::testsearch(){
	IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTreeInsertandSearch.dat",BLOCK_SIZE,TYPE_REG_PRIMARY);
	int j=0;
	for (int var =0; var < 1000; ++var) {
		RegPrimary* regPrimary = new RegPrimary();
		int keyInt=rand()%1000000;
		KeyInteger* key= new KeyInteger(keyInt);
		regPrimary->setKey(key);
		regPrimary = (RegPrimary*)indexBSharp->searchRegistry(regPrimary);
		if(regPrimary == NULL)
			cout<<"CLAVE: "<<key->getValue()<<" NO ENCONTRADA"<<endl;
		else{
			cout<<"SE ENCONTRO : ";
			regPrimary->print(std::cout);
			j++;
		}
	}
	cout<<" Se encontraron "<< j << " registros!" <<endl;
	delete indexBSharp;

}void TestBSharp::testInsertMails(){
	IndexBSharp* indexBSharp = new IndexBSharp("files/santiagodonikian.IndPrimario",BLOCK_SIZE,TYPE_REG_PRIMARY);
	indexBSharp->print(cout);
	return;
	int max=8;
	for (int var =1; var <=max; ++var) {
		RegPrimary* regPrimary = new RegPrimary();
			KeyInteger* key= new KeyInteger(var);
			regPrimary->setKey(key);
			indexBSharp->deleteRegistry(regPrimary);
	}
	indexBSharp->print(cout);
	delete indexBSharp;
	return;
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



void TestBSharp::testInsertRegClassification(){
	IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTreeRegClassifi.dat",BLOCK_SIZE,TYPE_REG_CLASSIFICATION);

	for (int var = 0; var < 300; ++var) {
		RegClassification* regClassif = new RegClassification();
		string keyString="caceres.oscar7@gmail.com";
		if(var>50)
			keyString="santiagoDonikian@gmail.com";
		if(var>100)
			keyString="r_dubini@gmail.com";
		if(var>150)
			keyString="facundosaravia@gmail.com";
		if(var>250)
			keyString="santiagoRocha@gmail.com";
		KeyString* key= new KeyString(keyString);
		regClassif->setKey(key);
		regClassif->addIuc(new KeyInteger(var));
		indexBSharp->addRegistry(regClassif);
	}
	indexBSharp->print(std::cout);
	RegClassification* regFind1=new RegClassification();
	KeyString* key= new KeyString("caceres.oscar7@gmail.com");
	regFind1->setKey(key);
	regFind1=(RegClassification*)indexBSharp->searchRegistry(regFind1);
	regFind1->print(cout);
	RegClassification* regFind2=new RegClassification();
	 key= new KeyString("santiagoDonikian@gmail.com");
	regFind2->setKey(key);
	regFind2=(RegClassification*)indexBSharp->searchRegistry(regFind2);
	regFind2->print(cout);
	RegClassification* regFind3=new RegClassification();
    key= new KeyString("r_dubini@gmail.com");
	regFind3->setKey(key);
	regFind3=(RegClassification*)indexBSharp->searchRegistry(regFind3);
	regFind3->print(cout);
	RegClassification* regFind4=new RegClassification();
    key= new KeyString("facundosaravia@gmail.com");
	regFind4->setKey(key);
	regFind4=(RegClassification*)indexBSharp->searchRegistry(regFind4);
	regFind4->print(cout);
	RegClassification* regFind5=new RegClassification();
	 key= new KeyString("santiagoRocha@gmail.com");
	regFind5->setKey(key);
	regFind5=(RegClassification*)indexBSharp->searchRegistry(regFind5);
	regFind5->print(cout);

	cout<<" esto es una manteca bambino!!!"<<endl;
	delete regFind1;
	delete regFind2;
	delete regFind3;
	delete regFind4;
	delete regFind5;
	delete indexBSharp;

}



void TestBSharp::testIterator(){
	IndexBSharp* indexBSharp = new IndexBSharp("Datos.2c2010.IndSecundario.Seleccion.From.asyura.from@gmail.com",BLOCK_SIZE,TYPE_REG_SELECTION);
	IteratorBSharp* it = indexBSharp->getIterator();
	RegSelection* reg;
	while (it->hasNext()){
		reg = (RegSelection* )(it->next());
		reg->print(std::cout);
	}
	delete indexBSharp;

}
void TestBSharp::testInsertRegSelection(){
	IndexBSharp* indexBSharp = new IndexBSharp("BTreeRegSelection.dat",BLOCK_SIZE,TYPE_REG_SELECTION);


	for (int var = 0; var < 100; ++var) {
		RegSelection* regSelection = new RegSelection();
		KeyInteger* key= new KeyInteger(var);
		regSelection->setKey(key);
		cout<<" Inserto el : ";
		regSelection->print(cout);
		indexBSharp->addRegistry(regSelection);

	}

	indexBSharp->print(std::cout);
	delete indexBSharp;
}
void TestBSharp::testPrint(){
	IndexBSharp* indexBSharp = new IndexBSharp("files/storage/elfacu_sanchez.IndPrimario",BLOCK_SIZE,TYPE_REG_PRIMARY);
	indexBSharp->print(std::cout);
	delete indexBSharp;
}
