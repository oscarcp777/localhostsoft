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
	Node();
	Node(unsigned int maxLong, unsigned int numBlock, unsigned int level)throw();
	virtual ~Node()throw();
    int getTypeElement();
    void setTypeElement(int typeElement);
    virtual bool isLeaf() const throw() = 0;
    virtual void addComponent(Component* component) throw() = 0;
    virtual void addComponent(Component* component,list<Registry*>::iterator ,int pos) throw() = 0;

protected:
	int typeElement;
};

#endif /* NODE_H_ */
