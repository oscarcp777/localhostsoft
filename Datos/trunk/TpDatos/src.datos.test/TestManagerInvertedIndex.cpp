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
	Mail* mail3 = new Mail();
	KeyInteger* key = new KeyInteger(10);
	KeyInteger* key2 = new KeyInteger(25);
	KeyInteger* key3 = new KeyInteger(35);

	mail->setKey(key);
	mail->setDate("27/8/2009");
	mail->setFrom("richy@lalala.com.ar");
	mail->setMessage(" a) El sistema operativo no sabe qué contiene el archivo, ni le interesa; lo único que ve son bytes. Cualquier significado que tenga el archivo deberán atribuírselo los programas en el nivel de usuario. Tanto UNIX como Windows utilizan este enfoque. Hacer que el sistema operativo vea los archivos únicamente como sucesiones de bytes ofrece el máximo de fexibilidad.");
	mail->setSubject("trabajo practico");
	mail->setTo("yogui");

	mail2->setKey(key2);
	mail2->setDate("27/8/2009");
	mail2->setFrom("richy@lalala.com.ar");
	mail2->setMessage("encabezado comienza con lo que se conoce como un número mágico, el cual identifica el archivo como ejecutable para evitar la ejecución accidental de un archivo que no tenga este formato. Luego vienen los tamaños de los diversos componentes del archivo, la dirección de la primera instrucción a ejecutar y algunos bits que actúan como indicadores. Después del encabezado vienen el texto y los datos del programa propiamente dicho. Éstos se cargan en la memoria y se reubican empleando los bits de reubicación. La tabla de símbolos sirve para depurar el programa ");
	mail2->setTo("yogui");

	mail3->setKey(key3);
	mail3->setDate("27/12/2009");
	mail3->setFrom("oscaR@lalala.com.ar");
	mail3->setMessage(" b) Un archivo es una sucesión de registros de longitud fija, cada uno de los cuales tiene cierta estructura interna. Un aspecto fundamental de la idea de que un archivo es una sucesión de registros es la idea de que la operación de lectura devuelve un registro y que la operación de escritura sobrescribe o añade un registro.");
	mail3->setSubject("trabajo practico");
	mail3->setTo("yogui");
	manager->loadMessageWords(mail,indexBSharp);
	manager->loadMessageWords(mail2,indexBSharp);
	manager->loadMessageWords(mail3,indexBSharp);

	indexBSharp->print(std::cout);
	delete indexBSharp;
		cout<<" esto es una manteca bambino!!!"<<endl;
	delete manager;
	delete mail;


}
void TestManagerInvertedIndex::testSearch(){
	IndexBSharp* indexBSharp = new IndexBSharp("files/storage/BTree.dat",BLOCK_SIZE,TYPE_REG_INVERTED_INDEX);
	RegInvertedIndex* regInvertedIndex= new RegInvertedIndex();
	regInvertedIndex->setKey(new KeyString("archivo"));
	regInvertedIndex=(RegInvertedIndex*)indexBSharp->searchRegistry(regInvertedIndex);
	regInvertedIndex->print(cout);
	delete indexBSharp;
	delete regInvertedIndex;
	cout<<" esto es una manteca bambino!!!"<<endl;
}
