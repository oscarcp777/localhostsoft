/*
 * MailBlockManager.h
 *
 *  Created on: 09/09/2010
 *      Author: richy
 */

#ifndef MAILBLOCKMANAGER_H_
#define MAILBLOCKMANAGER_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "../src.datos.models/Mail.h"
#include "../src.datos.models/Block.h"
#include "BinaryFile.h"
#include "Buffer.h"

class MailBlockManager {
public:
	MailBlockManager(string fileName, unsigned int blockSize);
	virtual ~MailBlockManager();
	void readMetadata();
	void writeMetadata();
	void packMail(Mail* mail);
	void close();
	std::vector<Mail*> loadMailsInBlock(int block);
	void loadMailListToBuffer();


private:
	int blockSize;
	int numBlocks;
	BinaryFile* blocksFile;
	int currentBlock;
	Mail* currentMail;
	Buffer* buffer;
	//Buffer* metadataBuffer;
	int freeSizeCurrentBlock;
	std::vector<Mail*> mailList;
	std::vector<int> freeSizeOfBlocks;
};

#endif /* MAILBLOCKMANAGER_H_ */
