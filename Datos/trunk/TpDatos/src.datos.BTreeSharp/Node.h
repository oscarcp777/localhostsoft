/*
 * Node.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef NODE_H_
#define NODE_H_
#include "../src.datos.models/Block.h"

class Node: public Block {
public:
	Node(int typeElement);
	virtual ~Node();
    int getTypeElement();
    void setTypeElement(int typeElement);

protected:
	int typeElement;
};

#endif /* NODE_H_ */
