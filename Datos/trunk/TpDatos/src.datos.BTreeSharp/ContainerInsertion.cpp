/*
 * ContainerInsertion.cpp
 *
 *  Created on: 05/09/2010
 *      Author: oscar
 */

#include "ContainerInsertion.h"

ContainerInsertion::ContainerInsertion() {
    this->leftRegKey=NULL;
    this->rightRegKey=NULL;
    this->midleRegKey=NULL;
}

ContainerInsertion::~ContainerInsertion() {
	this->leftRegKey=NULL;
	this->rightRegKey=NULL;
	this->midleRegKey=NULL;
}
Registry* ContainerInsertion::getRegMidleKey()throw() {
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

unsigned int ContainerInsertion::getMediumBlock() const
{
    return mediumBlock;
}

void ContainerInsertion::setMediumBlock(unsigned int mediumBlock)
{
    this->mediumBlock = mediumBlock;
}

Registry* ContainerInsertion::getLeftRegKey()
{
    return leftRegKey;
}

Registry* ContainerInsertion::getRightRegKey()
{
    return rightRegKey;
}

void ContainerInsertion::setLeftRegKey(Registry *leftRegKey)
{
    this->leftRegKey = leftRegKey;
}

void ContainerInsertion::setRightRegKey(Registry *rightRegKey)
{
    this->rightRegKey = rightRegKey;
}
void ContainerInsertion::setInternalKey(Registry* internalKey) throw(){
	this->internalKey = internalKey;
}
Registry* ContainerInsertion::getInternalKey() const throw(){
	   return this->internalKey;
}



