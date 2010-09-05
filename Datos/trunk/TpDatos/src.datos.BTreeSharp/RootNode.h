/*
 * RootNode.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef ROOTNODE_H_
#define ROOTNODE_H_

#include "Node.h"

class RootNode: public Node {
public:
	RootNode(int typeElement);
	virtual ~RootNode();
};

#endif /* ROOTNODE_H_ */
