/*
 * InternalNode.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "InternalNode.h"

InternalNode::InternalNode(int type,unsigned int maxLong, unsigned int numBlock, unsigned int level) throw():Node(type,maxLong,numBlock,level){

}

InternalNode::~InternalNode() throw(){
	// TODO Auto-generated destructor stub
}

bool InternalNode::isLeaf() const throw(){
	return false;
}
void InternalNode::addComponent(Component* component) throw(){

}
void InternalNode::addComponent(Component* component,int pos/*, ComponenteCompuesto::iterador_componentes posicion*/) throw(){

}
