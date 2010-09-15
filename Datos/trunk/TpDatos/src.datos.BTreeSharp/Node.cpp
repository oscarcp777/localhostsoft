/*
 * Node.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Node.h"

Node::Node(unsigned int maxLong, unsigned int numBlock, unsigned int level) throw():Block(maxLong,numBlock,level){
}
Node::Node(){

}
Node::~Node() throw(){
	// TODO Auto-generated destructor stub
}
int Node::getTypeElement(){
      return typeElement;
 }

void Node::setTypeElement(int typeElement){
      this->typeElement = typeElement;
  }
void Node::setNextBlock(int numBlock) throw(){
	this->nextNode = numBlock;
}
int Node::getNextBlock() const throw(){
	return this->nextNode;
}
