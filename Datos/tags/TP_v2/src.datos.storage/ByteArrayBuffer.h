/*
 * ByteArrayBuffer.h
 *
 *  Created on: 23/10/2010
 *      Author: oscar
 */

#ifndef BYTEARRAYBUFFER_H_
#define BYTEARRAYBUFFER_H_

#include "Buffer.h"

class ByteArrayBuffer: public Buffer {
public:
	ByteArrayBuffer(int maxBytes);
	virtual ~ByteArrayBuffer();
    void write(int b);
	int read();
	void reset();
	char* toByteArray();
	string toString();
};

#endif /* BYTEARRAYBUFFER_H_ */
