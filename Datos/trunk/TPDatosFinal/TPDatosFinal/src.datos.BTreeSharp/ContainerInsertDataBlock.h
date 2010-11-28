/*
 * ContainerInsertDataBlock.h
 *
 *  Created on: 21/09/2010
 *      Author: oscar
 */

#ifndef CONTAINERINSERTDATABLOCK_H_
#define CONTAINERINSERTDATABLOCK_H_
#include "../src.datos.storage/FreeBlockController.h"
#include "../src.datos.storage/BinaryFile.h"
class ContainerInsertDataBlock {
public:
	ContainerInsertDataBlock();
	virtual ~ContainerInsertDataBlock();
    BinaryFile *getBinaryFile() const;
    FreeBlockController *getFreeBlockController() const;
    unsigned int getSizeBlockData() const;
    int getTypeElement() const;
    void setBinaryFile(BinaryFile *binaryFile);
    void setFreeBlockController(FreeBlockController* freeBlockController);
    void setSizeBlockData(unsigned int sizeBlockData);
    void setTypeElement(int typeElement);
    bool getIndexed() const;
    void setIndexed(bool indexed);
    int getTypeElementData() const;
    void setTypeElementData(int typeElementData);

private:
	BinaryFile* binaryFile;
	FreeBlockController* freeBlockController;
	unsigned int sizeBlockData;
	int typeElement;
	int typeElementData;
	bool indexed;
};

#endif /* CONTAINERINSERTDATABLOCK_H_ */
