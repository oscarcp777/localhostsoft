/*
 * ContainerInsertion.cpp
 *
 *  Created on: 05/09/2010
 *      Author: oscar
 */

#include "ContainerInsertion.h"

ContainerInsertion::ContainerInsertion() {
	// TODO Auto-generated constructor stub

}

ContainerInsertion::~ContainerInsertion() {
	// TODO Auto-generated destructor stub
}
const Registry* ContainerInsertion::getRegMidleKey() const throw() {
	return this->midleRegKey;
}

void ContainerInsertion::setRegMidleKey(Registry* reg) throw() {
	this->midleRegKey = reg;
}

unsigned int ContainerInsertion::getLeftBlock() const throw(){
	return this->leftBlock;
}

void ContainerInsertion::setLeftBlock(unsigned int numBlock) throw() {
	this->leftBlock = numBlock;
}

unsigned int ContainerInsertion::getRightBlock() const throw(){
	return this->rigthBlock;
}

void ContainerInsertion::setRightBlock(unsigned int numBlock) throw(){
	this->rigthBlock = numBlock;
}
