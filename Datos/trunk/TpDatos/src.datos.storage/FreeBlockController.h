/*
 * FreeBlockList.h
 *
 *  Created on: 24/04/2010
 *      Author: Santiago
 */

#ifndef FREEBLOCKCONTROLLER_H_
#define FREEBLOCKCONTROLLER_H_

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "BinaryFile.h"

using namespace std;

class FreeBlockController {
public:
    FreeBlockController(string  fileName,int counterBlock) throw ();
    virtual ~FreeBlockController() throw ();
    void writeFreeBlock(unsigned int numBlock) throw ();
    unsigned int searchFreeBlock() throw ();
    unsigned int getCounterBlock() const; 
    void setCounterBlock(unsigned int counterBlock);
    void print(std::ostream& streamSalida);
    void writeFreeBlock();
private:
    void loadNumBlockFree();
    BinaryFile* binaryFile;
	vector<unsigned int> vectorFreeBlock;
	int counterBlock;


};

#endif /* FREEBLOCKCONTROLLER_H_ */
