/*
 * Node.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Node.h"

Node::Node(unsigned int maxLong, unsigned int numBlock, unsigned int level) throw():Block(maxLong,numBlock,level){
	this->averageWeight = 0;
}
Node::Node(){
	this->averageWeight = 0;
}
Node::~Node() throw(){
	// TODO Auto-generated destructor stub
}

bool Node::isUnderflowRemove() throw() {

	unsigned int coteUnderflow = (2*this->getLongBytes()/3)-(0.5*this->getAverageWeight());
	return (this->getOcupedLong() < coteUnderflow);
}
void  Node::setAverageWeight(unsigned int weight){
	this->averageWeight = weight;
}
unsigned int Node::getAverageWeight(){
	if (averageWeight!=0)
		return averageWeight;
	else{
		list<Registry*>::iterator currentReg = this->iteratorBegin();
		list<Registry*>::iterator lastReg = this->iteratorEnd();
		int totalWeight = 0;
		int count = 0;
		while (currentReg != lastReg){
			totalWeight += (*currentReg)->getLongBytes();
			currentReg++;
			count++;
		}
		if (count == 0)
			return 0;
		unsigned int averageWeight = totalWeight/count;
		return averageWeight;
	}
}
