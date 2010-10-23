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


void TestCompression::testCompression(){
	        BitOutputStream* bits = new BitOutputStream();
	        ByteArrayBuffer* buffer= new ByteArrayBuffer(512);
	        BitOutput* bo = new BitOutput(buffer);
	        bo->writeUnary(5);
	        bo->flush();
	        cout<<"00001000"<<endl;
	        cout<<bits->toString(buffer)<<endl;
	        buffer->init();
	        BitInput* bi=new BitInput(buffer);
	        long result=bi->readDelta();
	        cout<<result<<endl;
}
