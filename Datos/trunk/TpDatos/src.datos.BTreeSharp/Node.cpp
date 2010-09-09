/*
 * Node.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Node.h"

Node::Node(int typeElement,unsigned int maxLong, unsigned int numBlock, unsigned int level) throw():Block(maxLong,numBlock,level){
	this->typeElement = typeElement;
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
