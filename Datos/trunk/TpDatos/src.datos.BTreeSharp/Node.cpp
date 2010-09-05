/*
 * Node.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Node.h"

Node::Node(int typeElement) {
	this->typeElement = typeElement;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}
int Node::getTypeElement(){
      return typeElement;
 }

void Node::setTypeElement(int typeElement){
      this->typeElement = typeElement;
  }
