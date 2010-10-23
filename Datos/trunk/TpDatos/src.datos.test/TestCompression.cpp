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

TestCompression::TestCompression() {
	// TODO Auto-generated constructor stub

}

TestCompression::~TestCompression() {
	// TODO Auto-generated destructor stub
}
void TestCompression::testUnario(){
	        BitOutputStream* bits = new BitOutputStream();
	        ByteArrayBuffer* buffer= new ByteArrayBuffer(512);
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
	        delete buffer;
	        delete bo;
	        delete bi;
}
void TestCompression::testDelta(){
	        BitOutputStream* bits = new BitOutputStream();
	        ByteArrayBuffer* buffer= new ByteArrayBuffer(512);
	        BitOutput* bo = new BitOutput(buffer);
	        bo->writeDelta(5);
	        bo->flush();
	        cout<<"EL 5 EN delta :01101000"<<endl;
	        cout<<"BITS DEL BUFFER :"<<bits->toString(buffer)<<endl;
	        buffer->init();
	        BitInput* bi=new BitInput(buffer);
	        long result=bi->readDelta();
	        cout<<"NUMERO QUE LEYO DEL BUFFER :"<<result<<endl;
	        delete bits;
	        delete buffer;
	        delete bo;
	        delete bi;
}
void TestCompression::testGamma(){
	        BitOutputStream* bits = new BitOutputStream();
	        ByteArrayBuffer* buffer= new ByteArrayBuffer(512);
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
