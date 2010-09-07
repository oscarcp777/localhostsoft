/*
 * LeafNode.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "LeafNode.h"

LeafNode::LeafNode(int type,unsigned int maxLong, unsigned int numBlock, unsigned int level) throw():Node(type,maxLong,numBlock,level){
	// TODO Auto-generated constructor stub

}

LeafNode::~LeafNode()throw() {
	// TODO Auto-generated destructor stub
}

bool LeafNode::isLeaf() const throw(){
	return true;
}
void LeafNode::addComponent(Component* component) throw(){

}
void LeafNode::addComponent(Component* component,int pos/*, ComponenteCompuesto::iterador_componentes posicion*/) throw(){

}
