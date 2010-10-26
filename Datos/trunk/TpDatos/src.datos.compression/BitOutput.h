/*
 * BitOutput.h
 *
 *  Created on: 22/10/2010
 *      Author: oscar
 */

#ifndef BITOUTPUT_H_
#define BITOUTPUT_H_
#include "../src.datos.storage/BitArrayBufferCompression.h"
#include <iostream>
using namespace std;

class BitOutput {
public:
	BitOutput(BitArrayBufferCompression* out);
	virtual ~BitOutput();
	void writeUnary(int n) throw();
	void writeGamma(long n) throw();
	void writeDelta(long n) throw();
	void writeBinary(long n, int numBits) throw();
	void writeTrue() throw();
	void writeFalse() throw();
	void writeBit(bool bit) throw();
	void writeLowOrderBits(int numBits, long n) throw();
	void reset();
	void flush() throw();
	void close() throw();
	long leastSignificantBits(long n, int numBits) throw();
	long leastSignificantBits2(long n, int numBits);
	long sliceBits(long n, int leastSignificantBit, int numBits) throw();
	long sliceBits2(long n, int leastSignificantBit, int numBits);
	int mostSignificantPowerOfTwo(long n);
	int getBytesCompressed();
    static BitOutput* getInstance();
    static int getOcupedBytes(int value);
private:
	int mNextByte;
    int mNextBitIndex;
    BitArrayBufferCompression* mOut;
	static BitOutput* instanceUnique;
	BitOutput();
};

#endif /* BITOUTPUT_H_ */
