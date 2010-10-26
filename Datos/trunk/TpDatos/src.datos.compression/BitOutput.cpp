/*
 * BitOutput.cpp
 *
 *  Created on: 22/10/2010
 *      Author: oscar
 */

#include "BitOutput.h"
#include <math.h>
#include <cmath>
#include "../src.datos.exception/eCompression.h"

static unsigned long ALL_ONES_LONG = ~0l;

static char ZERO_BYTE = (char) 0;
BitOutput* BitOutput::instanceUnique=NULL;
BitOutput* BitOutput::getInstance(){

	if(!BitOutput::instanceUnique){
		BitOutput::instanceUnique= new BitOutput();
	}
	return BitOutput::instanceUnique;
}
BitOutput::BitOutput(BitArrayBufferCompression* out) {
	mOut = out;
	this->reset();
}
int BitOutput::getBytesCompressed(){
 return this->mOut->getNextByte();
}
BitOutput::BitOutput() {
	this->reset();
}

BitOutput::~BitOutput() {
	delete this->mOut;
}

void BitOutput::writeUnary(int n) throw(){
	// fit in buffer
	int numZeros = n - 1;
	if (numZeros <= this->mNextBitIndex) {
		this->mNextByte = this->mNextByte << numZeros;
		this->mNextBitIndex -= numZeros;
	    this->writeTrue();
	    return;
	}

	// fill buffer, write and flush
	// numZeros > mNextBitIndex
	this->mOut->write(this->mNextByte << this->mNextBitIndex); //TODO PENSAR LO DEL BUFFER
	numZeros -= (this->mNextBitIndex+1);
	this->reset();

	// fill in even multiples of eight
	for (; numZeros >= 8; numZeros -= 8)
	    this->mOut->write(ZERO_BYTE); //TODO PENSAR LO DEL BUFFER


	// fill in last zeros
	this->mNextBitIndex -= numZeros;
	this->writeTrue();
 }

void BitOutput::writeBinary(long n, int numBits) throw(){
	int k = this->mostSignificantPowerOfTwo(n);
	if (k >= numBits) {
	  throw eCompression("Number will not fit into number of bits");
	}
	this->writeLowOrderBits(numBits,n);
}

void BitOutput::writeGamma(long n) throw(){
	if (n == 1l) {
	    this->writeTrue();
	    return;
	}
	int k = this->mostSignificantPowerOfTwo(n);
	this->writeUnary(k+1);
	this->writeLowOrderBits(k,n);
    }

void BitOutput::writeDelta(long n) throw(){
	int numBits = this->mostSignificantPowerOfTwo(n); // 1 to 63
	if (numBits > 63) {
		throw eCompression("numBits too large");
	}
	this->writeGamma(numBits+1);
	if (numBits > 0)
	    this->writeLowOrderBits(numBits,n);
}

void BitOutput::close() throw(){
	this->flush();
}

void BitOutput::flush() throw(){
	if (mNextBitIndex < 7) {

	    int n= this->mNextByte << this->mNextBitIndex;
	    this->mOut->write(n); // shift to fill //TODO PENSAR LO DEL BUFFER


	    this->reset();
	}

    }


void BitOutput::writeBit(bool bit) throw(){
	if (bit) writeTrue();
	else writeFalse();
}


 void BitOutput::writeTrue() throw(){
	if (this->mNextBitIndex == 0) {
		this->mOut->write(this->mNextByte | 1);//TODO PENSAR LO DEL BUFFER
	    reset();
	} else {
		this->mNextByte = (this->mNextByte | 1) << 1;
	    --this->mNextBitIndex;
	}
 }

void BitOutput::writeFalse() throw(){
	if (this->mNextBitIndex == 0) {
	    this->mOut->write(this->mNextByte);//TODO PENSAR LO DEL BUFFER
	    this->reset();
	} else {
	    this->mNextByte <<= 1;
	    --this->mNextBitIndex;
	}
}

// writes out k lowest bits
void BitOutput::writeLowOrderBits(int numBits, long n) throw(){
	/* simple version that works:
	   while (--numBits >= 0)
	   writeBit(((ONE << numBits) & n) != 0);
	*/

	// if fits without output, pack and return
	if (this->mNextBitIndex >= numBits) {
		this->mNextByte
		= ( (this->mNextByte << (numBits-1))
		    | (int) leastSignificantBits2(n,numBits))
		<< 1;
		this->mNextBitIndex -= numBits;
	    return;
	}

	// pack rest of bit buffer and output
	numBits -= (this->mNextBitIndex + 1);
	this->mOut->write((this->mNextByte << this->mNextBitIndex)
		   | (int) sliceBits2(n,numBits,this->mNextBitIndex+1));//TODO PENSAR LO DEL BUFFER


	while (numBits >= 8) {
	    numBits -= 8;
	    this->mOut->write((int) sliceBits2(n,numBits,8));//TODO PENSAR LO DEL BUFFER
	}

	// write remainder
	if (numBits == 0) {
	    reset();
	    return;
	}
	this->mNextByte = ((int) this->leastSignificantBits2(n,numBits)) << 1;
	this->mNextBitIndex = 7 - numBits;
    }

void BitOutput::reset() {
	this->mNextByte = 0;
	this->mNextBitIndex = 7;
}

long BitOutput::leastSignificantBits(long n, int numBits) throw() {
	if (numBits < 1 || numBits > 64)
			throw eCompression("Number of bits must be between 1 and 64 inclusive");

	return this->leastSignificantBits2(n,numBits);
 }

long BitOutput::sliceBits(long n, int leastSignificantBit, int numBits) throw(){
	if (leastSignificantBit < 0 || leastSignificantBit > 63)
		throw eCompression("Least significant bit must be between 0 and 63");

	if (numBits < 1 || numBits > 64)
		throw eCompression("Number of bits must be between 1 and 64 inclusive");

	return this->sliceBits2(n,leastSignificantBit,numBits);
}

long BitOutput::leastSignificantBits2(long n, int numBits) {
	return (ALL_ONES_LONG >> (64-numBits)) & n;
}

long BitOutput::sliceBits2(long n, int leastSignificantBit, int numBits){
	return leastSignificantBits2(((unsigned int) n) >> leastSignificantBit,numBits);
}

int BitOutput::mostSignificantPowerOfTwo(long n) {
	int sum = (n >> 32 != 0) ? 32 : 0;
	if (n >> (sum | 16) != 0) sum = (sum | 16);
	if (n >> (sum | 8) != 0) sum = (sum | 8);
	if (n >> (sum | 4) != 0) sum = (sum | 4);
	if (n >> (sum | 2) != 0) sum = (sum | 2);
	return (n >> (sum | 1) != 0) ? (sum | 1) : sum;
}
int BitOutput::getOcupedBytes(int value){
	//	1 + 2|log 2 (2 x )| + |log( x)|
	 long cantBytes=0;
	double cantBit= 1+2*abs(log(2*value))+abs(log(value));
//   cout<<"bits :"<<cantBit<<" el numero : "<<value<<endl;
   if(cantBit>4&&cantBit<8)
	   cantBytes=1;
   else
    cantBytes=cantBit/8;
//    cout<<"bytes: "<<cantBytes<<" el numero : "<<value<<"--"<< BitOutput::getInstance()->contBytes<<endl;
    return cantBytes;
}
