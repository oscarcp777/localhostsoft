/*
 * TestCompression.cpp
 *
 *  Created on: 18/10/2010
 *      Author: oscar
 */

#include "TestCompression.h"
#include "TestCompression.h"
#include "TestCompression.h"
#include "../src.datos.compression/BitOutput.h"
#include "../src.datos.compression/BitInput.h"
#include "../src.datos.compression/BitOutputStream.h"
#include "../src.datos.storage/BinaryFile.h"

TestCompression::TestCompression() {
	// TODO Auto-generated constructor stub

}

TestCompression::~TestCompression() {
	// TODO Auto-generated destructor stub
}
void TestCompression::testUnario(){
	BitOutputStream* bits = new BitOutputStream();
	BitArrayBufferCompression* buffer= new BitArrayBufferCompression(512);
	BitOutput* bo = new BitOutput(buffer);
	bo->writeUnary(5);
	bo->flush();
	cout<<"EL 5 EN UNARIO :00001000"<<endl;
	cout<<"BITS DEL BUFFER :"<<bits->toString(buffer)<<endl;
	buffer->init();
	BitInput* bi=new BitInput(buffer);
	long result=bi->readUnary();
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<result<<endl;
	delete bits;
	delete bo;
	delete bi;
}
void TestCompression::testDelta(){
	int cont=0;
    BinaryFile* file =new BinaryFile();
    file->create("testCompresion");
	BitOutputStream* bits = new BitOutputStream();
	BitArrayBufferCompression* buffer= new BitArrayBufferCompression(512);
	BitOutput* bo = new BitOutput(buffer);
	bo->writeDelta(10);
	cont+=BitOutput::getOcupedBytes(10);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(10)<<endl;
	bo->writeDelta(2); cont+=BitOutput::getOcupedBytes(2);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(2)<<endl;
	bo->writeDelta(1); cont+=BitOutput::getOcupedBytes(1);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(1)<<endl;
	bo->writeDelta(4); cont+=BitOutput::getOcupedBytes(4);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(4)<<endl;
	bo->writeDelta(48); cont+=BitOutput::getOcupedBytes(48);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(48)<<endl;
	bo->writeDelta(49); cont+=BitOutput::getOcupedBytes(49);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(49)<<endl;
	bo->writeDelta(53); cont+=BitOutput::getOcupedBytes(53);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(53)<<endl;
	bo->writeDelta(1); cont+=BitOutput::getOcupedBytes(1);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(1)<<endl;
	bo->writeDelta(13); cont+=BitOutput::getOcupedBytes(13);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(13)<<endl;
	bo->writeDelta(2); cont+=BitOutput::getOcupedBytes(2);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(2)<<endl;
	bo->writeDelta(22); cont+=BitOutput::getOcupedBytes(22);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(22)<<endl;
	bo->writeDelta(2); cont+=BitOutput::getOcupedBytes(2);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(2)<<endl;
	bo->writeDelta(10); cont+=BitOutput::getOcupedBytes(10);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(10)<<endl;
	bo->writeDelta(8); cont+=BitOutput::getOcupedBytes(8);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(8)<<endl;
	bo->writeDelta(1); cont+=BitOutput::getOcupedBytes(1);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(1)<<endl;
	bo->writeDelta(4); cont+=BitOutput::getOcupedBytes(4);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(4)<<endl;
	bo->writeDelta(48); cont+=BitOutput::getOcupedBytes(48);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(48)<<endl;
	bo->writeDelta(49); cont+=BitOutput::getOcupedBytes(49);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(49)<<endl;
	bo->writeDelta(5); cont+=BitOutput::getOcupedBytes(5);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(5)<<endl;
	bo->writeDelta(1); cont+=BitOutput::getOcupedBytes(1);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(1)<<endl;
	bo->writeDelta(1); cont+=BitOutput::getOcupedBytes(1);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(1)<<endl;
	bo->writeDelta(233); cont+=BitOutput::getOcupedBytes(233);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(233)<<endl;
	bo->writeDelta(2); cont+=BitOutput::getOcupedBytes(2);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(2)<<endl;
	bo->writeDelta(2); cont+=BitOutput::getOcupedBytes(2);
	cout<<"espacio ocupado por el numero comprimido :"<<buffer->getNextByte()<<" cantBytes :"<<cont<<" el que deberia ocupar :"<<BitOutput::getOcupedBytes(2)<<endl;


	bo->flush();
	file->write(buffer->getData(),buffer->getMaxBytes(),0);
	cout<<"BITS DEL BUFFER :"<<bits->toString(buffer)<<endl;
	 buffer->clear();
	file->read(buffer->getData(),buffer->getMaxBytes(),0);
	BitInput* bi=new BitInput(buffer);
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<bi->readDelta()<<endl;
	delete bits;
	delete buffer;
	delete bo;
	delete bi;
}
void TestCompression::testGamma(){
	BitOutputStream* bits = new BitOutputStream();
	BitArrayBufferCompression* buffer= new BitArrayBufferCompression(512);
	BitOutput* bo = new BitOutput(buffer);
	bo->writeGamma(5);
	bo->flush();
	cout<<"EL 5 EN Gamma :00101000"<<endl;
	cout<<"BITS DEL BUFFER :"<<bits->toString(buffer)<<endl;
	buffer->init();
	
	BitInput* bi=new BitInput(buffer);
	long result=bi->readGamma();
	cout<<"NUMERO QUE LEYO DEL BUFFER :"<<result<<endl;
	delete bits;
	delete buffer;
	delete bo;
	delete bi;
}
