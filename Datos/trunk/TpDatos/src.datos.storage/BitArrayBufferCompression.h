/*
 * BitArrayBufferCompression.h
 *
 *  Created on: 23/10/2010
 *      Author: oscar
 */

#ifndef BITARRAYBUFFERCOMPRESSION_H_
#define BITARRAYBUFFERCOMPRESSION_H_
#include "Buffer.h"
using namespace std;

class BitArrayBufferCompression: public Buffer {
public:
	BitArrayBufferCompression(int maxBytes);
	virtual ~BitArrayBufferCompression();
    void write(int b);
	int read();
	void reset();
	char* toByteArray();
	string toString();
};


#endif /* BITARRAYBUFFERCOMPRESSION_H_ */
