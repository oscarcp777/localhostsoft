/*
 * Node.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef NODE_H_
#define NODE_H_
#include "../src.datos.models/Block.h"
#include "../src.datos.utils/Define.h"

class Node: public Block {
public:
	Node();
	Node(unsigned int maxLong, unsigned int numBlock, unsigned int level)throw();
	virtual ~Node()throw();
	virtual bool isLeaf() const throw() = 0;
	virtual void pack(Buffer* buffer) = 0;
	virtual void unPack(Buffer* buffer) = 0;
	virtual void packMetadata(Buffer* buffer)= 0;
	virtual int unPackMetadata(Buffer* buffer)= 0;
	virtual bool posibleToAgregateComponent(Registry* registry) throw()=0;
	/**
	 * Devuelve si hay subflujo o no
	 */
	virtual bool isUnderflow() throw() = 0;

};

#endif /* NODE_H_ */
