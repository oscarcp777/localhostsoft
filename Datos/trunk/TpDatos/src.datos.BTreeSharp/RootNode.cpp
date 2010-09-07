/*
 * RootNode.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "RootNode.h"

RootNode::RootNode(int type,unsigned int maxLong, unsigned int numBlock, unsigned int level) throw():Node(type,maxLong,numBlock,level){
	// TODO Auto-generated constructor stub

}

RootNode::~RootNode()throw() {
	// TODO Auto-generated destructor stub
}

bool RootNode::isLeaf() const throw(){
	return true;
}
void RootNode::addComponent(Component* component) throw(){

}
void RootNode::addComponent(Component* component,int pos/*, ComponenteCompuesto::iterador_componentes posicion*/) throw(){

}
