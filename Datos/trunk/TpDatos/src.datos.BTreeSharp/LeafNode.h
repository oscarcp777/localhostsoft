/*
 * LeafNode.h
 *
 *  Created on: 04/09/2010
 *      Author: Facurndo
 */

#ifndef LEAFNODE_H_
#define LEAFNODE_H_

#include "Node.h"

class LeafNode: public Node {
public:
	LeafNode(int typeElement,unsigned int maxLong);
	LeafNode(int typeElement,unsigned int maxLong, unsigned int numBlock, unsigned int level)throw();
	virtual ~LeafNode()throw();
	virtual bool isLeaf() const throw();
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);
	void packMetadata(Buffer* buffer);
	int unPackMetadata(Buffer* buffer);

	/**
	 * Obtiene la longitud ocupada en bytes del bloque.
	 */
	 unsigned int getOcupedLong() throw();
	/**
	 * Devuelve si hay subflujo o no
	 */
	bool isUnderflow()throw();


	 bool posibleToAgregateComponent(Registry* registry)throw();

private:


};

#endif /* LEAFNODE_H_ */
