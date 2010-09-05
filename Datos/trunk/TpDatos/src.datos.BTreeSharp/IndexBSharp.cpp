/*
 * IndexBSharp.cpp
 *
 *  Created on: 05/09/2010
 *      Author: oscar
 */

#include "IndexBSharp.h"

IndexBSharp::IndexBSharp(const std::string& nameFile, int sizeBlock,int typeElement){
	// TODO Auto-generated constructor stub

}

IndexBSharp::~IndexBSharp() {
	// TODO Auto-generated destructor stub
}

void IndexBSharp::addRegistry(Registry* registry) throw(){

}

void IndexBSharp::deleteRegistry(Registry* registry) throw(){

}
void IndexBSharp::searchRegistry(Registry* registry) throw(){

}
void IndexBSharp::print(std::ostream& streamSalida) throw(){

}
void IndexBSharp::createBlockRoot() throw(){

}
void IndexBSharp::readBlockRoot() throw(){

}
void IndexBSharp::writeBlockRoot() throw(){

}
void IndexBSharp::splitRoot(ContainerInsertion* container) throw(){

}
bool IndexBSharp::insertLeafNode(LeafNode* leafNode,Registry* registry,ContainerInsertion* container) throw(){
 return true;
}
void IndexBSharp::insertLeafNodeNotFull(LeafNode* leafNode,Registry* registry) throw(){

}
void IndexBSharp::insertLeafNodeFull(LeafNode* leafNode,Registry* registry,ContainerInsertion* container) throw(){

}
bool IndexBSharp::insertInternalNode(InternalNode* internalNode,Registry* registry,ContainerInsertion* container) throw(){
	return true;
}
void IndexBSharp::insertInternalNodeNotFull(InternalNode* internalNode,Registry* registry,unsigned int rightBlock, unsigned int leftBlock) throw(){

}
void IndexBSharp::insertInternalNodeFull(InternalNode* internalNode,Registry* registry,unsigned int rightBlock, unsigned int leftBlock,ContainerInsertion* container) throw(){

}
unsigned int IndexBSharp::searchPositionInsertLeafNode(Registry* registry, list<Registry*>::iterator) throw(){
	return 1;
}
unsigned int IndexBSharp::searchPositionInsertInternalNode(Registry* registry, list<Registry*>::iterator) throw(){
	return 1;
}
int IndexBSharp::searchBranch(InternalNode* internalNode,Registry* registry) throw(){
	return 1;
}
Registry* IndexBSharp::extractKey(Registry* registry) throw(){
	return NULL;
}
Registry* IndexBSharp::searchLeafNode(LeafNode* leafNode,Registry* registry) throw(){
	return NULL;
}
Registry*  IndexBSharp::searchInternalNode(InternalNode* internalNode,Registry* registry) throw(){
	return NULL;
}
void IndexBSharp::printRecursive(Node* currentNode, std::ostream& streamSalida, unsigned int level) throw(){

}
void IndexBSharp::printRegistry(Registry* registry, std::ostream& streamSalida) throw(){

}
