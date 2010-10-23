/*
 * BitInput.h
 *
 *  Created on: 23/10/2010
 *      Author: oscar
 */

#ifndef BITINPUT_H_
#define BITINPUT_H_
#include "../src.datos.storage/ByteArrayBuffer.h"


class BitInput {
public:
	BitInput(ByteArrayBuffer* in);
	virtual ~BitInput();
	void close() throw();
	bool endOfStream();
	bool readBit() throw();
	int readUnary() throw();
	long readGamma() throw();
	long readDelta() throw();
	long readBinary(int numBits) throw();
	void skipRice(int numFixedBits) throw();
	long readRest(int numBits, long result) throw();
	void readAhead() throw();
	long leastSignificantBits2(int n, int numBits);
	long sliceBits2(int n, int leastSignificantBit, int numBits);
	void checkGamma(int numBits) throw();
	void checkDelta(long numBits) throw();
	void notEndOfStream() throw();
private:
	ByteArrayBuffer* mIn;
    int mNextByte; // implied = 0;
    int mNextBitIndex;
    bool mEndOfStream;
};

#endif /* BITINPUT_H_ */
