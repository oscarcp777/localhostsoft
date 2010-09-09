/*
 * InternalNode.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "InternalNode.h"

using namespace std;
InternalNode::InternalNode(int type,unsigned int maxLong, unsigned int numBlock, unsigned int level) throw():Node(type,maxLong,numBlock,level){

}
InternalNode::InternalNode() {
}
InternalNode::~InternalNode() throw(){
	// TODO Auto-generated destructor stub
}

bool InternalNode::isLeaf() const throw(){
	return false;
}
void InternalNode::addComponent(Component* component) throw(){

}
void InternalNode::addComponent(Component* component,int pos/*, ComponenteCompuesto::iterador_componentes posicion*/) throw(){

}
void InternalNode::addBranch(int branch) throw(){
	this->branchList.push_back(branch);
}
void InternalNode::addBranch(std::vector<int>::iterator pos, int branch) throw(){
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

