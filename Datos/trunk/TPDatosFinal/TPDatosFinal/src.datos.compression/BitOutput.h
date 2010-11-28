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
	void writeGamma(int n) throw();
	void writeDelta(int n) throw();
	void writeBinary(int n, int numBits) throw();
	void writeTrue() throw();
	void writeFalse() throw();
	void writeBit(bool bit) throw();
	void writeLowOrderBits(int numBits, int n) throw();
	void reset();
	void flush() throw();
	void close() throw();
	int leastSignificantBits(int n, int numBits) throw();
	int leastSignificantBits2(int n, int numBits);
	int sliceBits(int n, int leastSignificantBit, int numBits) throw();
	int sliceBits2(int n, int leastSignificantBit, int numBits);
	int mostSignificantPowerOfTwo(int n);
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
