/*
 * LeafNode.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "LeafNode.h"

LeafNode::LeafNode(int type,unsigned int maxLong, unsigned int numBlock, unsigned int level) throw():Node(maxLong,numBlock,level){
	this->typeElement=type;
	this->setSizeFree(this->getFreeSize()- sizeof(int)*4);

}
LeafNode::LeafNode(int typeElement){
	this->typeElement=typeElement;
	this->setSizeFree(this->getFreeSize() - sizeof(int)*4);
}
LeafNode::~LeafNode()throw() {
	// TODO Auto-generated destructor stub
}

bool LeafNode::isLeaf() const throw(){
	return true;
}
int LeafNode::getNextBlock() const throw(){
	return this->nextNode;
}

void LeafNode::setNextBlock(int numBlock) throw(){
	this->nextNode = numBlock;
}
void LeafNode::pack(Buffer* buffer){
	this->packMetadata(buffer);
	this->packListRegistry(buffer);
}
void LeafNode::unPack(Buffer* buffer){
	int numElements = this->unPackMetadata(buffer);
	this->unPackListRegistry(buffer,numElements,this->typeElement);
}
void LeafNode::packMetadata(Buffer* buffer){
	int level = this->getLevel();
	buffer->packField(&level,sizeof(level));
	int numBlock = this->getNumBlock();
	buffer->packField(&numBlock,sizeof(numBlock));
	int nextNode = this->nextNode;
	buffer->packField(&nextNode,sizeof(nextNode));
	int numElements = this->getNumElements();
	buffer->packField(&numElements,sizeof(numElements));
}
int LeafNode::unPackMetadata(Buffer* buffer){
	int level;
	int numBlock;
	int nextNode;
	int numElements;
	buffer->unPackField(&level, sizeof(level));
	buffer->unPackField(&numBlock, sizeof(numBlock));
	buffer->unPackField(&nextNode, sizeof(nextNode));
	buffer->unPackField(&numElements, sizeof(numElements));
	this->setLevel(level);
	this->setNumBlock(numBlock);
	this->setNextBlock(nextNode);
	return numElements;
}


