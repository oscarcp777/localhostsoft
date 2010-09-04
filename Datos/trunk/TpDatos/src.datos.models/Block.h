/*
 * Block.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include <list>
#include "Component.h"
#include "../src.datos.storage/Buffer.h"
#include "Registry.h"
#include "Key.h"

class Block: public Component {
public:
	Block();
	virtual ~Block();
	int getNumElements();
	int getFreeSize();
	void addReg(Registry* reg);
	Registry* getReg(Key* key);
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);

private:
	list<Registry*> regList;
	int freeSize;
	Buffer* buffer;
};

#endif /* BLOCK_H_ */
