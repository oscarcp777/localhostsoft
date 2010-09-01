/*
 * Buffer.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef BUFFER_H_
#define BUFFER_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
class Buffer{

private:
	char* buffer; //character array to hold field values
	int bufferSize; //sum of the sizes of packed fields
	int maxBytes; //maximum number of characters in the buffer
	int nextByte; //index of next byte to be packed/unpacked
public:
	Buffer(int maxBytes);
	virtual ~Buffer();
	/**
	 * limpia los campos de buffer
	 */
	void clear();
    void init();

	/**
	 *setea el valor al siguiente campo del buffer
	 *si el size =-1 uso strlen(str) en la longitudes de la etiqueta
	 *@oscar
	 *@return retorna la cantidad de bytes del enpaquetado si -1 si hay error
	 */
	int packField(const void* field,int size=-1);
	/**
	 *extrae el valor al siguiente campo del buffer
	 *@oscar
	 *return reotrna el numero de bytes extraidos

	 */
	int unPackField(void* field,int size);
	int print();
    int getMaxBytes() const
    {
        return maxBytes;
    }

    void setMaxBytes(int maxBytes)
    {
        this->maxBytes = maxBytes;
    }

    char *getData()
    {
        return buffer;
    }

    int getBufferSize() const
    {
        return bufferSize;
    }
    void setBufferSize(int bufferSize )
       {
           this->bufferSize= bufferSize;
       }

};

#endif /* BUFFER_H_ */
