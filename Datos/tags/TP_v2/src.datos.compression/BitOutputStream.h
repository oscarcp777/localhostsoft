/*
 * BitOutputStream.h
 *
 *  Created on: 22/10/2010
 *      Author: oscar
 */

#ifndef BITOUTPUTSTREAM_H_
#define BITOUTPUTSTREAM_H_
#include <string>
#include "../src.datos.storage/ByteArrayBuffer.h"
using namespace std;

class BitOutputStream {
public:
	BitOutputStream();
	virtual ~BitOutputStream();
	string toString(ByteArrayBuffer* buffer);
	void close() throw();

private:
    bool mClosed;
};

#endif /* BITOUTPUTSTREAM_H_ */
