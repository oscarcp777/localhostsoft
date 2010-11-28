/*
 * CompressedBlock.h
 *
 *  Created on: 24/10/2010
 *      Author: oscar
 */

#ifndef COMPRESSEDBLOCK_H_
#define COMPRESSEDBLOCK_H_
#include "Block.h"
#include "InfoPerDoc.h"
#include "../src.datos.compression/BitInput.h"
#include "../src.datos.compression/BitOutput.h"
class CompressedBlock: public Block{
public:
	CompressedBlock(unsigned int sizeBlock,int typeElement,bool indexed);
	virtual ~CompressedBlock();
	void loadOutPutCompressor(BitArrayBufferCompression* buffer);
	void loadInPutCompressor(BitArrayBufferCompression* buffer);
	void packCompressed(BitArrayBufferCompression* buffer);
	void unPackCompressed(BitArrayBufferCompression* buffer);
	void packMetadataCompressed();
	int unPackMetadataCompressed();
	void packListRegistryCompressed();
	void unPackListRegistryCompressed(int numberElements,int typeElement);
	bool posibleToAgregateRegCompressed(InfoPerDoc* registry);
	unsigned int getOcupedLongCompressed();
	unsigned int getSizeRegCompressed();
	void chancePositionForDistancesAndReverse(bool reverse);
private:

	BitInput* compressorBitInput;
	BitOutput* compressorBitOutput;
};

#endif /* COMPRESSEDBLOCK_H_ */
