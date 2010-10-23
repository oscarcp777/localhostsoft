/*
 * ContainerInsertDataBlock.cpp
 *
 *  Created on: 21/09/2010
 *      Author: oscar
 */

#include "ContainerInsertDataBlock.h"

ContainerInsertDataBlock::ContainerInsertDataBlock() {
	// TODO Auto-generated constructor stub

}

ContainerInsertDataBlock::~ContainerInsertDataBlock() {
	this->binaryFile->close();
	delete this->binaryFile;
	delete this->freeBlockController;
}

BinaryFile *ContainerInsertDataBlock::getBinaryFile() const
{
    return binaryFile;
}

FreeBlockController *ContainerInsertDataBlock::getFreeBlockController() const
{
    return freeBlockController;
}

unsigned int ContainerInsertDataBlock::getSizeBlockData() const
{
    return sizeBlockData;
}

int ContainerInsertDataBlock::getTypeElement() const
{
    return typeElement;
}

void ContainerInsertDataBlock::setBinaryFile(BinaryFile *binaryFile)
{
    this->binaryFile = binaryFile;
}

void ContainerInsertDataBlock::setFreeBlockController(FreeBlockController *freeBlockController)
{
    this->freeBlockController = freeBlockController;
}

void ContainerInsertDataBlock::setSizeBlockData(unsigned int sizeBlockData)
{
    this->sizeBlockData = sizeBlockData;
}

void ContainerInsertDataBlock::setTypeElement(int typeElement)
{
    this->typeElement = typeElement;
}

bool ContainerInsertDataBlock::getIndexed() const
{
    return indexed;
}

void ContainerInsertDataBlock::setIndexed(bool indexed)
{
    this->indexed = indexed;
}

int ContainerInsertDataBlock::getTypeElementData() const
{
    return typeElementData;
}

void ContainerInsertDataBlock::setTypeElementData(int typeElementData)
{
    this->typeElementData = typeElementData;
}






