/*
 * BitInput.cpp
 *
 *  Created on: 23/10/2010
 *      Author: oscar
 */

#include "BitInput.h"
#include "../src.datos.exception/eCompression.h"

static char ZERO_BYTE = (char) 0;

static unsigned int ALL_ONES_INT = ~0;

BitInput::BitInput(ByteArrayBuffer* in) {
	this->mEndOfStream = false;
	this->mIn = in;
	this->readAhead();
}

BitInput::~BitInput() {
	// TODO Auto-generated destructor stub
}


 void BitInput::close() throw() {
   this->mEndOfStream = true;

}

bool BitInput::endOfStream(){
   return mEndOfStream;
}



bool BitInput::readBit() throw(){
	bool result;
		switch (mNextBitIndex--) {
        case 0:
            result = ((mNextByte & 1) != 0);
            readAhead();
            return result;
        case 1:
            return ((mNextByte & 2) != 0);
        case 2:
            return ((mNextByte & 4) != 0);
        case 3:
            return ((mNextByte & 8) != 0);
        case 4:
            return ((mNextByte & 16) != 0);
        case 5:
            return ((mNextByte & 32) != 0);
        case 6:
            return ((mNextByte & 64) != 0);
        case 7:
            return ((mNextByte & 128) != 0);
        default:
        	throw eCompression("Index out of bounds");
        }
    }

int BitInput::readUnary() throw(){
        int result = 1;

        // look through remaining buffered bits
        for ( ; !endOfStream() && mNextBitIndex != 7; ++result)
            if (readBit())
                return result;

        // jump over whole 0 bytes
        while (!endOfStream() && mNextByte == ZERO_BYTE) {
            result += 8;
            mNextByte = mIn->read();//TODO PENSAR LO DEL BUFFER
            if (mNextByte == -1)
            	throw eCompression("Final sequence of 0 bits with no 1");

        }

        // read to last one bit (could do the search trick here!)
        while (!readBit()) // know we'll find it given last test
            ++result;
        return result;
    }





long BitInput::readGamma() throw(){
        int numBits = readUnary();
        if (numBits > 63)
        	throw eCompression("Gamma code binary part must be <= 63 bits");

        return readRest(numBits-1,1l);
 }




long BitInput::readDelta() throw() {
        long numBits = readGamma();
        checkDelta(numBits);
        if (numBits > 63l)
        	throw eCompression("Delta code must use <= 63 bits for fixed portion");

        return readRest((int)numBits-1,1l);
    }



long BitInput::readBinary(int numBits) throw(){
        if (numBits > 63)
        	throw eCompression("Cannot read more than 63 bits into positive long");

        if (numBits < 1)
        	throw eCompression("Number of bits to read must be > 0");

        long result = readBit() ? 1l : 0l;
        return readRest(numBits-1,result);
}





long BitInput::readRest(int numBits, long result) throw(){
        /* simple working version:
           while (--numBits >= 0) {
           notEndOfStream();
           result = result << 1;
           if (readBit()) result |= 1l;
           }
           return result;
        */

        if (numBits == 0) return result;

        notEndOfStream();

        // can read from currently buffered byte
        if (mNextBitIndex >= numBits) {
            mNextBitIndex -= numBits;
            return (result << numBits)
                | sliceBits2(mNextByte,mNextBitIndex+1,numBits+1);
        }

        // numBits > mNextBitIndex
        // read rest of current byte
        numBits -= (mNextBitIndex+1);
        result = (result << (mNextBitIndex+1))
            | sliceBits2(mNextByte,0,mNextBitIndex+1);

        for ( ; numBits >= 8; numBits -= 8) {
            int nextByte = mIn->read();//TODO PENSAR LO DEL BUFFER
            if (nextByte == -1) {
                mEndOfStream = true;
                throw eCompression("Premature end of stream reading binary - mid.");
            }
            result = (result << 8) | nextByte;
        }
        readAhead();

        if (numBits == 0) return result;
        notEndOfStream();
        mNextBitIndex = 7 - numBits;
        return (result << numBits)
            | sliceBits2(mNextByte,mNextBitIndex+1,numBits);
    }

void BitInput::readAhead() throw(){
        if (mEndOfStream) return;
        mNextByte = mIn->read();//TODO PENSAR LO DEL BUFFER
        if (mNextByte == -1) {
            mEndOfStream = true;
            return;
        }
        mNextBitIndex = 7;
    }


void BitInput::notEndOfStream() throw(){
	if (endOfStream())
		throw eCompression("End of stream reached prematurely");
}


long BitInput::leastSignificantBits2(int n, int numBits){
    return (ALL_ONES_INT >> (32-numBits)) & n;
}

long BitInput::sliceBits2(int n, int leastSignificantBit, int numBits){
        return leastSignificantBits2(((unsigned int) n) >>/*>TODO*/ leastSignificantBit,
                                     numBits);
}

void BitInput::checkGamma(int numBits) throw(){
        if (numBits <= 63) return;
        throw eCompression("Gamma code binary part must be <= 63 bits");

 }

void BitInput::checkDelta(long numBits) throw(){
        if (numBits <= 63l) return;
        throw eCompression("Delta code binary part must be <= 63 bits");
 }


