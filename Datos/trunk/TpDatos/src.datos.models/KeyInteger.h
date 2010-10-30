/*
 * KeyInteger.h
 *
 *  Created on: 22/09/2010
 *      Author: oscar
 */

#ifndef KEYINTEGER_H_
#define KEYINTEGER_H_
#include "Key.h"

class KeyInteger :public Key{
public:
	KeyInteger(int value);
		KeyInteger();
		virtual ~KeyInteger();
		void pack(Buffer* buffer);
		void unPack(Buffer* buffer);
		unsigned int getSize();
		int getLongBytes();
		int print(std::ostream& outStream);
		bool equals(Registry* comp);
		int getValue();
		int compareTo(Registry* registry);
		Registry* clone();
		Registry* cloneRegKey();
		void packCompressed(BitOutput* compressor);
		void unPackCompressed(BitInput* compressor);
		unsigned int getlongBytesCompressed();
       void setValue(int value); 
	private:
		int value;
};

#endif /* KEYINTEGER_H_ */
