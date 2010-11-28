/*
 * BitInput.h
 *
 *  Created on: 23/10/2010
 *      Author: oscar
 */

#ifndef BITINPUT_H_
#define BITINPUT_H_
#include "../src.datos.storage/BitArrayBufferCompression.h"


class BitInput {
public:
	BitInput(BitArrayBufferCompression* in);
	virtual ~BitInput();
	void close() throw();
	bool endOfStream();
	bool readBit() throw();
	int readUnary() throw();
	int readGamma() throw();
	int readDelta() throw();
	int readBinary(int numBits) throw();
	void skipRice(int numFixedBits) throw();
	int readRest(int numBits, int result) throw();
	void readAhead() throw();
	int leastSignificantBits2(int n, int numBits);
	int sliceBits2(int n, int leastSignificantBit, int numBits);
	void checkGamma(int numBits) throw();
	void checkDelta(int numBits) throw();
	void notEndOfStream() throw();
	void setBuffer(BitArrayBufferCompression* buffer);
	static BitInput* getInstance(BitArrayBufferCompression* buffer);
private:
	BitArrayBufferCompression* mIn;
    int mNextByte; // implied = 0;
    int mNextBitIndex;
    bool mEndOfStream;
    static BitInput* instanceUnique;
    BitInput();
};

#endif /* BITINPUT_H_ */
