/*
 * LeafNode.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "LeafNode.h"

LeafNode::LeafNode(int type,unsigned int maxLong, unsigned int numBlock, unsigned int level) throw():Node(maxLong,numBlock,level){
	this->typeElement=type;

}
LeafNode::LeafNode(){
}
LeafNode::~LeafNode()throw() {
	// TODO Auto-generated destructor stub
}

bool LeafNode::isLeaf() const throw(){
	return true;
}
void LeafNode::addComponent(Component* component) throw(){

}
void LeafNode::addComponent(Component* component,list<Registry*>::iterator ,int pos) throw(){

}
int LeafNode::getNextBlock() const throw(){
	return this->nextNode;
}

void LeafNode::setNextBlock(int numBlock) throw(){
	this->nextNode = numBlock;
}
void LeafNode::pack(Buffer* buffer){

}
void LeafNode::unPack(Buffer* buffer){

}
