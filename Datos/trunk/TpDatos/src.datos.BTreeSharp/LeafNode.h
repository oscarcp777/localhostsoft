/*
 * LeafNode.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef LEAFNODE_H_
#define LEAFNODE_H_

#include "Node.h"

class LeafNode: public Node {
public:
	LeafNode(int typeElement);
	virtual ~LeafNode();
};

#endif /* LEAFNODE_H_ */
