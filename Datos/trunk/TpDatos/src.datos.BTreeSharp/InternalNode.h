/*
 * InternalNode.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef INTERNALNODE_H_
#define INTERNALNODE_H_

#include "Node.h"

class InternalNode: public Node {
public:
	InternalNode(int typeElement,unsigned int maxLong, unsigned int numBlock, unsigned int level)throw();
	virtual ~InternalNode()throw();
	virtual bool isLeaf() const throw();
	virtual void addComponent(Component* component) throw();
	virtual void addComponent(Component* component,int pos/*, ComponenteCompuesto::iterador_componentes posicion*/) throw();

};

#endif /* INTERNALNODE_H_ */
