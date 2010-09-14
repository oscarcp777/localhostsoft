/*
 * InternalNode.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "InternalNode.h"

using namespace std;
InternalNode::InternalNode(unsigned int maxLong, unsigned int numBlock, unsigned int level) throw():Node(maxLong,numBlock,level){
	this->typeElement= TYPE_KEY;
	unsigned int sizeBusy=sizeof(int)*4+this->branchList.size()*4;
	this->setSizeFree(maxLong- sizeBusy);
	//TODO y las ramas???
}
InternalNode::InternalNode(unsigned int maxLong) {
	this->typeElement= TYPE_KEY;
	unsigned int sizeBusy=sizeof(int)*4+this->branchList.size();
	this->setSizeFree(maxLong- sizeBusy);
	this->setMaxLong(maxLong);
}
InternalNode::~InternalNode() throw(){
	// TODO Auto-generated destructor stub
}
unsigned int InternalNode::getOcupedLong() throw(){
	unsigned int sizeBusy=Block::getSizeRegistry();
	sizeBusy += sizeof(unsigned int)*4;
	sizeBusy += this->branchList.size()*4;
	cout<<"InternalNode sizeBusy :"<<sizeBusy<<endl;
	return sizeBusy;
}
bool InternalNode::isLeaf() const throw(){
	return false;
}

bool InternalNode::posibleToAgregateComponent(Registry* registry) throw(){

	return (this->getOcupedLong() + registry->getLongBytes() <= this->getMaxLong());

}
void InternalNode::addBranch(int branch) throw(){
	this->branchList.push_back(branch);
}
void InternalNode::addBranch(std::vector<int>::iterator pos,unsigned int branch) throw(){
	this->branchList.insert(pos, branch);
}

void InternalNode::removeBranch(int branch) throw(){

	std::remove(this->firstBranch(), this->lastBranch(), branch);
}

void InternalNode::transferBranchs(std::vector<int>& branchList) throw(){
	branchList.clear();
	this->branchList.swap(branchList);
}

bool InternalNode::containsBranch(int branch) throw(){
	std::vector<int>::iterator pos;

	pos = std::find(this->firstBranch(), this->lastBranch(), branch);

	return pos != this->lastBranch();
}

int InternalNode::getBranch(unsigned int index) const throw(){
	return this->branchList[index];
}

unsigned int InternalNode::numberOfBranchs() const throw(){
	return this->branchList.size();
}

std::vector<int>::iterator InternalNode::firstBranch() throw(){
	return this->branchList.begin();
}

std::vector<int>::const_iterator   InternalNode::firstBranch() const throw(){
	return this->branchList.begin();
}

std::vector<int>::iterator InternalNode::lastBranch() throw(){
	return this->branchList.end();
}

std::vector<int>::const_iterator  InternalNode::lastBranch() const throw(){
	return this->branchList.end();
}
void InternalNode::unPackListBranch(Buffer* buffer, int numBranchs){
	vector<int>::iterator iterRegistry;
	int branch;
	for(int i=0; i<numBranchs; i++){
		buffer->unPackField(&branch,sizeof(branch));
		this->branchList.push_back(branch);
	}
}
void InternalNode::packListBranch(Buffer* buffer){
	vector<int>::iterator iterRegistry;
	int branch;
	for (iterRegistry=this->branchList.begin(); iterRegistry!=this->branchList.end(); iterRegistry++){
		branch=*iterRegistry;
		buffer->packField(&branch,sizeof(branch));
	}
}
void InternalNode::packMetadata(Buffer* buffer){
	int level = this->getLevel();
	buffer->packField(&level,sizeof(level));
	int numBlock = this->getNumBlock();
	buffer->packField(&numBlock,sizeof(numBlock));
	int numBranchs = this->branchList.size();
	buffer->packField(&numBranchs,sizeof(numBranchs));
	this->packListBranch(buffer);
	int numElements = this->getNumElements();
	buffer->packField(&numElements,sizeof(numElements));


}
int InternalNode::unPackMetadata(Buffer* buffer){
	int level;
	int numBlock;
	int numBranchs;
	int numElements;
	buffer->unPackField(&level, sizeof(level));
	buffer->unPackField(&numBlock, sizeof(numBlock));
	buffer->unPackField(&numBranchs, sizeof(numBranchs));
	this->unPackListBranch(buffer,numBranchs);
	buffer->unPackField(&numElements, sizeof(numElements));
	this->setLevel(level);
	this->setNumBlock(numBlock);
	return numElements;
}
void InternalNode::pack(Buffer* buffer){
	this->packMetadata(buffer);
	this->packListRegistry(buffer);
}
void InternalNode::unPack(Buffer* buffer){
	int numElements = this->unPackMetadata(buffer);
	this->unPackListRegistry(buffer,numElements,TYPE_KEY);
}
