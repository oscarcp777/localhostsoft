/*
 * LeafNode.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "LeafNode.h"

LeafNode::LeafNode(int typeElement,unsigned int maxLong, unsigned int numBlock, unsigned int level) throw():Node(maxLong,numBlock,level){
    this->nextNode=-1;

}
LeafNode::LeafNode(int typeElement,unsigned int maxLong){
	this->typeElement=typeElement;
	this->setMaxLong(maxLong);
}
LeafNode::~LeafNode()throw() {
	// TODO Auto-generated destructor stub
}
unsigned int LeafNode::getOcupedLong() throw(){
	unsigned int sizeBusy=Block::getSizeRegistry();
	sizeBusy += sizeof(unsigned int)*4;
	return sizeBusy;
}
bool LeafNode::isLeaf() const throw(){
	return true;
}

bool LeafNode::posibleToAgregateComponent(Registry* registry) throw(){
   unsigned int ocupedLong=this->getOcupedLong();
   unsigned int longBytes=registry->getLongBytes();
	return (( ocupedLong+longBytes)  <= this->getMaxLong());

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


