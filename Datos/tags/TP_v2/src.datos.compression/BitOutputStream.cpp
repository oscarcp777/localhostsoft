/*
 * BitOutputStream.cpp
 *
 *  Created on: 22/10/2010
 *      Author: oscar
 */

#include "BitOutputStream.h"

BitOutputStream::BitOutputStream() {
	mClosed = false;

}

BitOutputStream::~BitOutputStream() {
	// TODO Auto-generated destructor stub
}

string BitOutputStream::toString(ByteArrayBuffer* buffer) {
	char* bytes = buffer->getData();
	string sb ="";
	for (int i = 0; i < buffer->getNextByte(); ++i) {
		char b = bytes[i];
		for (int j = 8; --j >= 0; ) {
			char apend=((b & (1 << j)) == 0) ? '0' : '1';
			sb.append(&apend);
		}
	}
	return sb;
}
void BitOutputStream::close() throw() {
	//if (mClosed) throw new IOException("closed twice.");
	mClosed = true;
}
