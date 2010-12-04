/*
 * IndexBSharp.cpp
 *
 *  Created on: 05/09/2010
 *      Author: oscar
 */

#include "IndexBSharp.h"
#include "../src.datos.exception/eNotSpace.h"
#include "../src.datos.exception/eLostReg.h"
bool comparatorRegistry( Registry* reg1, Registry* reg2) {
	int compare= reg1->compareTo(reg2);
	return (compare< 0);
}
void IndexBSharp::initContainerDataBlock(const std::string& nameFile,unsigned int sizeBlock,int typeElement,int typeElementData,bool indexed){
	this->containerInsertDataBlock= new ContainerInsertDataBlock();
	this->containerInsertDataBlock->setIndexed(indexed);
	this->containerInsertDataBlock->setTypeElementData(typeElementData);
	string nameFileData=nameFile+".dt";
	BinaryFile* binaryFileData= new BinaryFile();
	FreeBlockController* freeBlockControllerData;
	if(!binaryFileData->isCreated(nameFileData)){
		binaryFileData->create(nameFileData);
		freeBlockControllerData = new FreeBlockController(nameFile+".fr2",-1);
	}else{
		binaryFileData->open(nameFileData);
		freeBlockControllerData = new FreeBlockController(nameFile+".fr2",binaryFileData->getCountBlockInFile(sizeBlock)-1);
	}
	this->containerInsertDataBlock->setBinaryFile(binaryFileData);
	this->containerInsertDataBlock->setFreeBlockController(freeBlockControllerData);
	this->containerInsertDataBlock->setTypeElement(typeElement);
	this->containerInsertDataBlock->setSizeBlockData(sizeBlock);
}
IndexBSharp::IndexBSharp(const std::string& nameFile, unsigned int sizeBlock,int typeElement) {
	this->containerInsertDataBlock = NULL;
	containerInsertion=new ContainerInsertion();
	this->sizeBlock = sizeBlock;
	this->typeElement = typeElement;
	this->binaryFile = new BinaryFile();
	if (!this->binaryFile->isCreated(nameFile)) {
		this->binaryFile->create(nameFile);
		this->freeBlockController = new FreeBlockController(nameFile+".fr",1);
	}else{
		this->binaryFile->open(nameFile);
		this->freeBlockController = new FreeBlockController(nameFile+".fr",this->binaryFile->getCountBlockInFile(sizeBlock)-1);
	}
	this->buffer= new Buffer(sizeBlock);
	this->bufferRoot= new Buffer(sizeBlock*2);
	if(typeElement==TYPE_REG_PRIMARY)
		this->initContainerDataBlock(nameFile,BLOCK_SIZE_MAILS,typeElement,TYPE_MAIL,false);
	if(typeElement==TYPE_REG_CLASSIFICATION)
		this->initContainerDataBlock(nameFile,sizeBlock,typeElement,TYPE_KEY_INTEGER,true);
	if(typeElement==TYPE_REG_INVERTED_INDEX)
			this->initContainerDataBlock(nameFile,sizeBlock,typeElement,TYPE_INFO_PER_DOC,true);
	this->readNode(0);
}
unsigned int IndexBSharp::averageEstimate(
		list<Registry*>::iterator iteratorBegin,
		list<Registry*>::iterator iteratorEnd) throw () {
	unsigned int totalWeight = 0;
	unsigned int cont = 0;
	while (iteratorBegin != iteratorEnd){
		Registry* registry = static_cast<Registry*>(*iteratorBegin);
		totalWeight += registry->getLongBytes();
		iteratorBegin++;
		cont++;
	}
	unsigned int averageEstimate = totalWeight / cont;
	return averageEstimate;
}
IndexBSharp::~IndexBSharp() {
	this->writeNode(this->rootNode,0);
	this->binaryFile->close();
	delete this->buffer;
	delete this->bufferRoot;
	if(this->containerInsertDataBlock != NULL)
		delete this->containerInsertDataBlock;
	delete this->freeBlockController;
	delete this->binaryFile;
	delete this->rootNode;
	delete containerInsertion;
}

void IndexBSharp::addRegistry(Registry* registry) throw(){
	int sizeMedium=0.5*this->sizeBlock;
	if (registry->getLongBytes() >= sizeMedium)
		throw eNotSpace("Registro demasiado grande!!");
	int answer = INSERTION_OK;
	if (this->rootNode->isLeaf()){
		LeafNode* leafNode = static_cast<LeafNode*>(this->rootNode);
		answer = this->insertLeafNode(leafNode, registry, containerInsertion,0);
	} else {
		InternalNode* internalNode  = static_cast<InternalNode*>(this->rootNode);
		Registry* aux = NULL;
		answer = this->insertInternalNode(internalNode, registry, containerInsertion, 0, aux);
	}

	if (answer == OVER_FLOW) {
		if(this->rootNode->isLeaf())
			this->splitLeafRoot(containerInsertion,registry);
		else
			this->splitInternalRoot(containerInsertion);
	}

}
//}

Registry* IndexBSharp::searchRegistry(Registry* registry) throw () {
	if (this->rootNode->isLeaf()) {
		LeafNode* leafNode = static_cast<LeafNode*> (this->rootNode);
		return this->searchLeafNode(leafNode, registry);
	} else {
		InternalNode* internalNode =
				static_cast<InternalNode*> (this->rootNode);
		return this->searchInternalNode(internalNode, registry);
	}
}
void IndexBSharp::print(std::ostream& streamSalida) throw () {
	this->printRecursive(this->rootNode, streamSalida, 0);
}
void IndexBSharp::createBlockRoot() throw () {
	// Instancia un nuevo bloque raiz
	this->rootNode = new LeafNode(this->typeElement, 2 * this->sizeBlock, 0, 0);
	// Ecscribe bloque raiz
	this->writeNode(this->rootNode, 0);
}


void IndexBSharp::writeNode(Node* node, int numBlock) throw () {
	if (numBlock == 0){
		this->bufferRoot->clear();
		node->pack(this->bufferRoot);
		this->binaryFile->write(this->bufferRoot->getData(),this->bufferRoot->getMaxBytes(),0);
	}else{
		this->buffer->clear();
		node->pack(this->buffer);
		this->binaryFile->write(this->buffer->getData(),this->buffer->getMaxBytes(),numBlock*this->buffer->getMaxBytes());
	}
}
Node* IndexBSharp::readNode(unsigned int numBlock) throw () {
	if (numBlock == 0){
		this->bufferRoot->clear();
		if(this->binaryFile->read(this->bufferRoot->getData(),this->bufferRoot->getMaxBytes(),0)){
			this->rootNode = readNodeBytes(this->bufferRoot);
		} else {
			this->createBlockRoot();
		}
		return this->rootNode;
	}else{
		this->buffer->clear();
		if (this->binaryFile->read(buffer->getData(),this->buffer->getMaxBytes(),this->buffer->getMaxBytes()* numBlock)) {
			Node* node = readNodeBytes(buffer);
			return node;
		} else {
			return NULL;
		}
	}
}

Node* IndexBSharp::readNodeBytes(Buffer* buffer) throw () {
	unsigned int levelNode;
	if (buffer->getData() != NULL) {
		buffer->unPackField(&levelNode, sizeof(levelNode));
		buffer->init();
		if (levelNode == 0) {
			return readLeafNodeBytes(buffer);
		} else {
			return readInternalNodeBytes(buffer);
		}
	}
	return NULL;
}
Node* IndexBSharp::readInternalNodeBytes(Buffer* buffer) throw () {
	InternalNode* internalNode = new InternalNode(buffer->getMaxBytes(),
			this->typeElement);
	internalNode->unPack(buffer);
	return internalNode;
}
Node* IndexBSharp::readLeafNodeBytes(Buffer* buffer) throw () {
	LeafNode* leafNode = new LeafNode(this->typeElement, buffer->getMaxBytes());
	leafNode->unPack(buffer);
	return leafNode;
}

void IndexBSharp::splitLeafRoot(ContainerInsertion* container,	Registry* registry) throw () {
  unsigned int cont=0;
	// Busca espacio libre para la nueva raiz
	unsigned int positionFree = this->freeBlockController->searchFreeBlock();
	LeafNode* newLeftNode = new LeafNode(this->typeElement, this->sizeBlock,
			positionFree, 0);

	positionFree = this->freeBlockController->searchFreeBlock();
	LeafNode* newCenterNode = new LeafNode(this->typeElement, this->sizeBlock,
			positionFree, 0);

	positionFree = this->freeBlockController->searchFreeBlock();
	LeafNode* newRightNode = new LeafNode(this->typeElement, this->sizeBlock,
			positionFree, 0);

	this->listRegistry.clear();
	this->rootNode->transferRegistry(this->listRegistry);

	this->listRegistry.push_back(registry);
	this->listRegistry.sort(comparatorRegistry);
	printListReg(cout,this->listRegistry.begin(),this->listRegistry.end());
	unsigned int averageEstimate = this->averageEstimate(listRegistry.begin(),listRegistry.end());
	newLeftNode->setAverageWeight(averageEstimate);
	newCenterNode->setAverageWeight(averageEstimate);
	newRightNode->setAverageWeight(averageEstimate);

	list<Registry*>::iterator current = this->listRegistry.begin();

	while (newLeftNode->isUnderflow(getSizeMinumumNode(averageEstimate,listRegistry.size()))) {
		Registry* reg=(Registry*)*current;
		if(DEBUG)reg->print(cout);
		newLeftNode->addComponent(reg);
		current++;
		cont++;
	}

	container->setLeftRegKey(this->extractKey(*current));

	while (newCenterNode->isUnderflow(getSizeMinumumNode(averageEstimate,listRegistry.size()))) {
		Registry* reg=(Registry*)*current;
		if(DEBUG)reg->print(cout);
		newCenterNode->addComponent(reg);
		current++;
		cont++;
	}

	container->setRightRegKey(this->extractKey(*current));

	while (current != this->listRegistry.end()) {
		if (newRightNode->posibleToAgregateComponent(*current)){
			Registry* reg=(Registry*)*current;
			if(DEBUG)reg->print(cout);
			newRightNode->addComponent(reg);
		}else
			break;
		current++;
		cont++;
	}
	if(DEBUG){
	  cout<<" CANTIDAD DE REGISTROS INSERTADoS "<<cont<<endl;
	  cout<<" CANTIDAD DE REGISTROS "<<listRegistry.size()<<endl;
	}

     if(cont!=listRegistry.size()){
	   cout<<"###########################################################"<<endl;
     cout<<"############# DANGER SE PERDIO UN REGISTRO    ##############"<<endl;
     cout<<"###########################################################"<<endl;
     throw eNotSpace("ERROR EN EL SPLIT SE PÉRDIERON REGISTROS !!!!!!");
    }
	newLeftNode->setNextBlock(newCenterNode->getNumBlock());
	newCenterNode->setNextBlock(newRightNode->getNumBlock());

	InternalNode* newRoot = new InternalNode(this->typeElement, 2*this->sizeBlock, 0, this->rootNode->getLevel() + 1);
	newRoot->addBranch(newLeftNode->getNumBlock());
	newRoot->addBranch(newCenterNode->getNumBlock());
	newRoot->addBranch(newRightNode->getNumBlock());

	newRoot->addComponent(container->getLeftRegKey());
	newRoot->addComponent(container->getRightRegKey());
	// Escribe el bloque raiz
	delete this->rootNode;
	this->rootNode = newRoot;
	this->writeNode(this->rootNode, 0);

	this->writeNode(newLeftNode, newLeftNode->getNumBlock());
	this->writeNode(newRightNode, newRightNode->getNumBlock());
	this->writeNode(newCenterNode, newCenterNode->getNumBlock());
	delete newCenterNode;
	delete newLeftNode;
	delete newRightNode;

}
unsigned int IndexBSharp::getSizeMinumumNode(unsigned int averageEstimate,unsigned int countReg){
        return (averageEstimate*countReg)/3;
}
void IndexBSharp::splitInternalRoot(ContainerInsertion* container) throw () {
    unsigned int cont=0;
	// Busca espacio libre para la nueva raiz
	unsigned int positionFree = this->freeBlockController->searchFreeBlock();
	InternalNode* newLeftNode = new InternalNode(this->typeElement,
			this->sizeBlock, positionFree, this->rootNode->getLevel());

	positionFree = this->freeBlockController->searchFreeBlock();
	InternalNode* newCenterNode = new InternalNode(this->typeElement,
			this->sizeBlock, positionFree, this->rootNode->getLevel());

	positionFree = this->freeBlockController->searchFreeBlock();
	InternalNode* newRightNode = new InternalNode(this->typeElement,
			this->sizeBlock, positionFree, this->rootNode->getLevel());

	this->listRegistry.clear();
	this->branchList.clear();
	this->rootNode->transferRegistry(this->listRegistry);
	((InternalNode*) this->rootNode)->transferBranchs(this->branchList);

	unsigned int positionInsert = searchPositionInsertInternalNode(container->getRightRegKey(), this->listRegistry.begin(),
			this->listRegistry.end());
	this->listRegistry.push_back(container->getRightRegKey());
	this->listRegistry.sort(comparatorRegistry);
	printListReg(cout,this->listRegistry.begin(),this->listRegistry.end());
	//adelanto el puntero
	std::vector<int>::iterator itListBranchs = this->branchList.begin();
	this->advanceVectorPointer(itListBranchs, positionInsert + 1);
	// Inserta la rama
	branchList.insert(itListBranchs, container->getRightBlock());
	this->printBranch(cout,this->branchList.begin(),this->branchList.end());
	list<Registry*>::iterator itListRegistry = this->listRegistry.begin();
	itListBranchs = this->branchList.begin();
	newLeftNode->addBranch(*itListBranchs);
	if(DEBUG)std::cout<<"  RAMA: B1 "<<*itListBranchs<<" - "<<std::endl;
	itListBranchs++;
	cont++;
	unsigned int averageEstimate = this->averageEstimate(listRegistry.begin(),listRegistry.end());

	newLeftNode->setAverageWeight(averageEstimate);
	newCenterNode->setAverageWeight(averageEstimate);
	newRightNode->setAverageWeight(averageEstimate);
	//le sumo el peso estimado de la rama asociada a la clave
	averageEstimate+=+sizeof(unsigned int);
	while (newLeftNode->isUnderflow(getSizeMinumumNode(averageEstimate,listRegistry.size()))) {

		newLeftNode->addBranch(*itListBranchs);
		Registry* reg=(Registry*)*itListRegistry;
		if(DEBUG)reg->print(cout);
		newLeftNode->addComponent(reg);
		if(DEBUG)std::cout<<"  RAMA:B1  "<<*itListBranchs<<" - "<<std::endl;
		itListRegistry++;
		itListBranchs++;
		cont++;
	}

	newCenterNode->addBranch(*itListBranchs);
	if(DEBUG)std::cout<<"  RAMA: B2 "<<*itListBranchs<<" - "<<std::endl;
	itListBranchs++;
	cont++;
	Registry* leftRegistryKey=(Registry*)*itListRegistry;
	container->setLeftRegKey(leftRegistryKey);
	itListRegistry++;
	while (newCenterNode->isUnderflow(getSizeMinumumNode(averageEstimate,listRegistry.size()))) {
		newCenterNode->addBranch(*itListBranchs);
		Registry* reg=(Registry*)*itListRegistry;
		if(DEBUG)reg->print(cout);
		newCenterNode->addComponent(reg);
		if(DEBUG)std::cout<<"  RAMA:B2 "<<*itListBranchs<<" - "<<std::endl;
		itListRegistry++;
		itListBranchs++;
		cont++;
	}


	newRightNode->addBranch(*itListBranchs);
	itListBranchs++;
	cont++;
	Registry* reg = (Registry*) *itListRegistry;
	container->setRightRegKey(reg);
	itListRegistry++;

	while (itListRegistry != this->listRegistry.end()) {
		if (newRightNode->posibleToAgregateComponent(*itListRegistry)) {
			Registry* reg=(Registry*)*itListRegistry;
			if(DEBUG)reg->print(cout);
			newRightNode->addComponent(reg);
			newRightNode->addBranch(*itListBranchs);
			if(DEBUG)std::cout<<"  RAMA:B3 "<<*itListBranchs<<" - "<<std::endl;
		} else
			break;
		itListBranchs++;
		itListRegistry++;
		cont++;
	}
	if(DEBUG){
	  cout<<" CANTIDAD DE RAMAS INSERTADAS "<<cont<<endl;
	  cout<<" CANTIDAD DE RAMAS "<<branchList.size()<<endl;
	}
   if(cont!=branchList.size()){
	   cout<<"###########################################################"<<endl;
       cout<<"############# DANGER SE PERDIO UN BLOQUE    ##############"<<endl;
       cout<<"###########################################################"<<endl;
       throw eNotSpace("ERROR EN EL SPLIT SE PÉRDIERON RAMAS !!!!!!");
   }
	InternalNode* newRoot = new InternalNode(this->typeElement,2*this->sizeBlock,0, this->rootNode->getLevel() + 1);
	newRoot->addBranch(newLeftNode->getNumBlock());
	newRoot->addBranch(newCenterNode->getNumBlock());
	newRoot->addBranch(newRightNode->getNumBlock());

	newRoot->addComponent(container->getLeftRegKey());
	newRoot->addComponent(container->getRightRegKey());
	// Escribe el bloque raiz
	delete this->rootNode;
	this->rootNode = newRoot;
	this->writeNode(this->rootNode, 0);

	this->writeNode(newLeftNode, newLeftNode->getNumBlock());
	this->writeNode(newRightNode, newRightNode->getNumBlock());
	this->writeNode(newCenterNode, newCenterNode->getNumBlock());

	delete newLeftNode;
	delete newRightNode;
	delete newCenterNode;

}
int IndexBSharp::insertLeafNode(LeafNode* leafNode, Registry* registry,
		ContainerInsertion* container, unsigned int brotherNode) throw () {

	if(DATA==1){
		if(this->typeElement==TYPE_REG_PRIMARY||this->typeElement==TYPE_REG_CLASSIFICATION||this->typeElement==TYPE_REG_INVERTED_INDEX){
			registry=  leafNode->insertBlockData(registry,this->containerInsertDataBlock);
		}
		if(registry==NULL)
			return INSERTION_OK;
	}

	// Consideramos que no hay sobreflujo
	int answer = INSERTION_OK;
	// Verifica que el bloque externo puede agregar el registro
	if (leafNode->posibleToAgregateComponent(registry)) {
		// Agrega el registro en el bloque externo no lleno
		this->insertLeafNodeNotFull(leafNode, registry);
	} else {
		LeafNode* sisterBranchNode;
		if (brotherNode != 0)
			sisterBranchNode = (LeafNode*) this->readNode(brotherNode);
		else
			sisterBranchNode = NULL;

		if (this->balanceLeafNode(registry, leafNode, sisterBranchNode,
				container)) {
			answer = BALANCE;
		} else {
			answer = OVER_FLOW;
			if (sisterBranchNode != NULL) {
				this->insertLeafNodeFull(leafNode, sisterBranchNode, registry,
						container);
			}
		}
		delete sisterBranchNode;
	}

	return answer;
}

void IndexBSharp::mergeComponentList(list<Registry*> &listRegistry, list<
		Registry*> &listLeftNode, list<Registry*> &listRightNode) {
	list<Registry*>::iterator itListRegistry = listLeftNode.begin();
	while (itListRegistry != listLeftNode.end()) {
		listRegistry.push_back(*itListRegistry);
		itListRegistry++;
	}
	itListRegistry = listRightNode.begin();
	while(itListRegistry != listRightNode.end()){
		listRegistry.push_back(*itListRegistry);
		itListRegistry++;
	}
}
void IndexBSharp::mergeBranchList(std::vector<int> &listBranch,
		std::vector<int> &listLeftNode, std::vector<int> &listRightNode) {
	std::vector<int>::iterator itListBranchs = listLeftNode.begin();
	while(itListBranchs != listLeftNode.end()){
		listBranch.push_back(*itListBranchs);
		itListBranchs++;
	}
	itListBranchs = listRightNode.begin();
	while (itListBranchs != listRightNode.end()) {
		listBranch.push_back(*itListBranchs);
		itListBranchs++;
	}

}

bool IndexBSharp::balanceLeafNode(Registry* reg, LeafNode* actualNode,LeafNode* brotherNode, ContainerInsertion* container) throw () {
	if (brotherNode == NULL)
		return false;
    unsigned int cont=0;
	Registry* actualReg = *(actualNode->iteratorBegin());
	Registry* brotherReg = *(brotherNode->iteratorBegin());

	LeafNode* leftNode;
	LeafNode* rightNode;
	list<Registry*> listRegLeftNode;
	list<Registry*> listRegRightNode;

	if (actualReg->compareTo(brotherReg) < 0) {
		actualNode->transferRegistry(listRegLeftNode);
		brotherNode->transferRegistry(listRegRightNode);
		leftNode = actualNode;
		rightNode = brotherNode;
	} else {
		brotherNode->transferRegistry(listRegLeftNode);
		actualNode->transferRegistry(listRegRightNode);
		leftNode = brotherNode;
		rightNode = actualNode;
	}

	//El primer elemento del bloque derecho es la clave padre de ambos bloques
	Registry* oldMiddleKey = *(listRegLeftNode.begin());
	this->listRegistry.clear();
	this->mergeComponentList(this->listRegistry, listRegLeftNode,
			listRegRightNode);

	this->listRegistry.push_back(reg);
	this->listRegistry.sort(comparatorRegistry);
	printListReg(cout,this->listRegistry.begin(),this->listRegistry.end());
	list<Registry*>::iterator itListRegistry = this->listRegistry.begin();
	while (leftNode->posibleToAgregateComponent(*itListRegistry)) {
		Registry* reg=(Registry*)*itListRegistry;
		if(DEBUG)reg->print(cout);
		leftNode->addComponent(reg);
		itListRegistry++;
		cont++;
	}
	container->setRegMidleKey(this->extractKey(*itListRegistry));

	while (itListRegistry != this->listRegistry.end()) {
		if (rightNode->posibleToAgregateComponent(*itListRegistry)){
			Registry* reg=(Registry*)*itListRegistry;
			if(DEBUG)reg->print(cout);
			rightNode->addComponent(reg);

		}else
			break;
		itListRegistry++;
		cont++;
	}


	int sizeOldMiddleKey = oldMiddleKey->getKey()->getLongBytes();
	int sizeNewMiddleKey = container->getRegMidleKey()->getLongBytes();
	if (itListRegistry != this->listRegistry.end()  || sizeOldMiddleKey < sizeNewMiddleKey) {
		leftNode->clearListRegistry();
		list<Registry*>::iterator itListReg = listRegLeftNode.begin();
		while (itListReg != listRegLeftNode.end()) {
			leftNode->addComponent(*itListReg);
			itListReg++;
		}
		rightNode->clearListRegistry();
		itListReg = listRegRightNode.begin();
		while (itListReg != listRegRightNode.end()) {
			rightNode->addComponent(*itListReg);
			itListReg++;
		}
		listRegLeftNode.clear();
		listRegRightNode.clear();
		delete container->getRegMidleKey();
		return false;
	} else {

	     if(cont!=listRegistry.size()){
		   cout<<"###########################################################"<<endl;
	     cout<<"############# DANGER SE PERDIO UN REGISTRO    ##############"<<endl;
	     cout<<"###########################################################"<<endl;
	     throw eNotSpace("ERROR EN EL BALANCELEAFNODE SE PÉRDIERON REGISTROS !!!!!!");
	    }
		this->writeNode(leftNode, leftNode->getNumBlock());
		this->writeNode(rightNode, rightNode->getNumBlock());
		return true;
	}

}
void IndexBSharp::insertLeafNodeNotFull(LeafNode* leafNode, Registry* registry) throw () {

	// Inserta el registro en el bloque externo
	leafNode->addReg(registry);
	leafNode->sortListRegistry();

	// Escribe bloque en disco
	this->writeNode(leafNode, leafNode->getNumBlock());

}
void IndexBSharp::advanceListPointer(list<Registry*>::iterator& iterator,unsigned int countAdvance){
	for (unsigned int var = 0; var < countAdvance; var++) {
		iterator++;
	}
}
void IndexBSharp::advanceVectorPointer(vector<int>::iterator& iterator,unsigned int countAdvance){
	for (unsigned int var = 0; var < countAdvance; var++) {
		iterator++;
	}
}

void IndexBSharp::insertLeafNodeFull(LeafNode* leafNode, LeafNode* brotherNode,	Registry* registry, ContainerInsertion* container) throw () {
    unsigned int cont=0;
	// Busco numero de bloque libre
	unsigned int numBlockFree = this->freeBlockController->searchFreeBlock();
	// Creo nuevo bloque externo para dividir bloque..
	LeafNode* newLeafNode = new LeafNode(this->typeElement, this->sizeBlock,
			numBlockFree, 0);

	listRegistry.clear();

	LeafNode* leftNode;
	LeafNode* rightNode;
	list<Registry*> listRegLeftNode;
	list<Registry*> listRegRightNode;

	Registry* actualReg = *(leafNode->iteratorBegin());
	Registry* brotherReg = *(brotherNode->iteratorBegin());

	if (actualReg->compareTo(brotherReg) < 0) {
		leafNode->transferRegistry(listRegLeftNode);
		brotherNode->transferRegistry(listRegRightNode);
		leftNode = leafNode;
		rightNode = brotherNode;
	} else {
		brotherNode->transferRegistry(listRegLeftNode);
		leafNode->transferRegistry(listRegRightNode);
		leftNode = brotherNode;
		rightNode = leafNode;
	}

	this->mergeComponentList(this->listRegistry, listRegLeftNode,listRegRightNode);

	this->listRegistry.push_back(registry);
	this->listRegistry.sort(comparatorRegistry);
	printListReg(cout,this->listRegistry.begin(),this->listRegistry.end());

	unsigned int averageEstimate = this->averageEstimate(listRegistry.begin(), listRegistry.end());
	leftNode->setAverageWeight(averageEstimate);
	rightNode->setAverageWeight(averageEstimate);
	newLeafNode->setAverageWeight(averageEstimate);
	list<Registry*>::iterator itListRegistry = this->listRegistry.begin();

	while (leftNode->isUnderflow(getSizeMinumumNode(averageEstimate,listRegistry.size()))) {
		Registry* reg=(Registry*)*itListRegistry;
		if(DEBUG)reg->print(cout);
		leftNode->addComponent(reg);
		itListRegistry++;
		cont++;
	}

	container->setLeftRegKey(this->extractKey(*itListRegistry));
	while(rightNode->isUnderflow(getSizeMinumumNode(averageEstimate,listRegistry.size()))){
		Registry* reg=(Registry*)*itListRegistry;
		if(DEBUG)reg->print(cout);
		rightNode->addComponent(reg);
		itListRegistry++;
		cont++;
	}
	container->setRightRegKey(this->extractKey(*itListRegistry));

	while (itListRegistry != this->listRegistry.end()) {
		if (newLeafNode->posibleToAgregateComponent(*itListRegistry)){
			Registry* reg=(Registry*)*itListRegistry;
			if(DEBUG)reg->print(cout);
			newLeafNode->addComponent(reg);

		}else
			break;
		itListRegistry++;
		cont++;
	}
	if(DEBUG){
	     cout<<" CANTIDAD DE registros INSERTADoS "<<cont<<endl;
		  cout<<" CANTIDAD DE registros "<<listRegistry.size()<<endl;
	}
	if(cont!=listRegistry.size()){
		cout<<"###########################################################"<<endl;
		cout<<"############# DANGER SE PERDIO UN registro    ##############"<<endl;
		cout<<"###########################################################"<<endl;
		throw eNotSpace("ERROR EN EL SPLIT SE PÉRDIERON registros !!!!!!");
	}
	newLeafNode->setNextBlock(rightNode->getNextBlock());
	rightNode->setNextBlock(newLeafNode->getNumBlock());

	this->writeNode(leftNode, leftNode->getNumBlock());
	this->writeNode(rightNode, rightNode->getNumBlock());
	this->writeNode(newLeafNode, newLeafNode->getNumBlock());

	container->setLeftBlock(leftNode->getNumBlock());
	container->setMediumBlock(rightNode->getNumBlock());
	container->setRightBlock(newLeafNode->getNumBlock());
	delete newLeafNode;

}

bool IndexBSharp::balanceInternalNode(InternalNode* internalNode, InternalNode* brotherNode, ContainerInsertion* container, Registry* fatherReg) throw(){
	//SE BALANCEA POR TAMAÑO
	//SE LLENA EL BLOQUE DE LA IZQUIERDA LO MAS POSIBLE, LUEGO SE INTENTA LLENAR EL DE LA DERECHA
	 unsigned int cont=0;
	 unsigned int contBranch=0;
	if (brotherNode == NULL)
		return false;

	Registry* regKey = container->getRightRegKey();
	//unsigned int numleftNode = container->getLeftBlock();
	unsigned int numRightNode = container->getRightBlock();

	this->listRegistry.clear();
	this->branchList.clear();

	//Registro menor del bloque actual
	Registry* currentReg = (*(internalNode->iteratorBegin()));

	//Registro menor bloque hermano
	Registry* brotherReg = (*(brotherNode->iteratorBegin()));
	InternalNode* leftNode;
	InternalNode* rightNode;
	list<Registry*> listRegLeftNode;
	list<Registry*> listRegRightNode;
	std::vector<int> listBranchLeftNode;
	std::vector<int> listBranchRightNode;

	//Diferencio cual es el bloque izquierdo del derecho
	if (currentReg->compareTo(brotherReg) < 0) {
		internalNode->transferRegistry(listRegLeftNode);
		brotherNode->transferRegistry(listRegRightNode);
		internalNode->transferBranchs(listBranchLeftNode);
		brotherNode->transferBranchs(listBranchRightNode);
		leftNode = internalNode;
		rightNode = brotherNode;
	} else {
		brotherNode->transferRegistry(listRegLeftNode);
		internalNode->transferRegistry(listRegRightNode);
		brotherNode->transferBranchs(listBranchLeftNode);
		internalNode->transferBranchs(listBranchRightNode);
		leftNode = brotherNode;
		rightNode = internalNode;
	}

	this->mergeComponentList(this->listRegistry,listRegLeftNode,listRegRightNode);
	this->mergeBranchList(this->branchList,listBranchLeftNode,listBranchRightNode);

	this->listRegistry.push_back(fatherReg);
	this->listRegistry.sort(comparatorRegistry);
	unsigned int positionInsert = searchPositionInsertInternalNode(regKey,this->listRegistry.begin(), this->listRegistry.end());
	this->listRegistry.push_back(regKey);
	this->listRegistry.sort(comparatorRegistry);
	printListReg(cout,this->listRegistry.begin(),this->listRegistry.end());
	//adelanto el puntero
	std::vector<int>::iterator itListBranchs = this->branchList.begin();
	this->advanceVectorPointer(itListBranchs, positionInsert + 1);
	// Inserta la rama
	branchList.insert(itListBranchs, numRightNode);
	this->printBranch(cout,this->branchList.begin(),this->branchList.end());
	list<Registry*>::iterator itFinalListRegistry = this->listRegistry.begin();
	std::vector<int>::iterator itFinalListBranchs = this->branchList.begin();

	leftNode->addBranch(*itFinalListBranchs);
	if(DEBUG)std::cout<<"  RAMA:B1 balanceInternalNode "<<*itFinalListBranchs<<" - "<<std::endl;
	itFinalListBranchs++;
	contBranch++;
	while (leftNode->posibleToAgregateComponent(*itFinalListRegistry)) {
		if(DEBUG)std::cout<<"  RAMA:B1 "<<*itFinalListBranchs<<" - "<<std::endl;
		Registry* reg=(Registry*)*itFinalListRegistry;
		if(DEBUG){reg->print(cout);cout<<endl;}
		leftNode->addComponent(reg);
		leftNode->addBranch(*itFinalListBranchs);
		itFinalListRegistry++;
		itFinalListBranchs++;
		cont++;
		contBranch++;
	}

	rightNode->addBranch(*itFinalListBranchs);
	if(DEBUG)std::cout<<"  RAMA:B2 "<<*itFinalListBranchs<<" - "<<std::endl;
	itFinalListBranchs++;
	contBranch++;
	// Establece el elemento medio a subir en el resultado de insercion
	Registry* regMidleKey = (Registry*) *itFinalListRegistry;
	container->setRegMidleKey(regMidleKey);
	itFinalListRegistry++;
	cont++;
	while (itFinalListRegistry != this->listRegistry.end()) {
		if (rightNode->posibleToAgregateComponent(*itFinalListRegistry)) {
			if(DEBUG)std::cout<<"  RAMA:B2 "<<*itFinalListBranchs<<" - "<<std::endl;
			Registry* reg=(Registry*)*itFinalListRegistry;
		    if(DEBUG){reg->print(cout);cout<<endl;}
			rightNode->addComponent(reg);
			rightNode->addBranch(*itFinalListBranchs);
		} else
			break;
		itFinalListRegistry++;
		itFinalListBranchs++;
		cont++;
		contBranch++;
	}

	int sizeOldMiddleKey = fatherReg->getLongBytes();
	int sizeNewMiddleKey = container->getRegMidleKey()->getLongBytes();
	if (itFinalListRegistry != this->listRegistry.end() || sizeOldMiddleKey < sizeNewMiddleKey) {
		leftNode->clearListRegistry();
		list<Registry*>::iterator registryList = listRegLeftNode.begin();
		while (registryList != listRegLeftNode.end()) {
			leftNode->addComponent(*registryList);
			registryList++;
		}
		rightNode->clearListRegistry();
		registryList = listRegRightNode.begin();
		while (registryList != listRegRightNode.end()) {
			rightNode->addComponent(*registryList);
			registryList++;
		}
		listRegLeftNode.clear();
		listRegRightNode.clear();

		leftNode->clearBranch();

		std::vector<int>::iterator branchList = listBranchLeftNode.begin();
		while (branchList != listBranchLeftNode.end()) {
			leftNode->addBranch(*branchList);
			branchList++;
		}
		rightNode->clearBranch();
		branchList = listBranchRightNode.begin();
		while (branchList != listBranchRightNode.end()) {
			rightNode->addBranch(*branchList);
			branchList++;
		}
		listBranchLeftNode.clear();
		listBranchRightNode.clear();

		return false;
	}else {
		if(cont!=listRegistry.size()&&contBranch!=branchList.size()){
				   cout<<"###########################################################"<<endl;
			     cout<<"############# DANGER SE PERDIO UN REGISTRO  O UNA RAMA  ##############"<<endl;
			     cout<<"###########################################################"<<endl;
			     throw eNotSpace("ERROR EN EL BALANCELEAFNODE SE PÉRDIERON REGISTROS O RAMAS !!!!!!");
		}
		// Escribe bloque izquierdo
		this->writeNode(leftNode, leftNode->getNumBlock());
		// Escribe bloque derecho
		this->writeNode(rightNode, rightNode->getNumBlock());
		fatherReg = NULL;
		return true;
	}

	return false;
}

int IndexBSharp::insertInternalNode(InternalNode* internalNode,
		Registry* registryKey, ContainerInsertion* container,
		unsigned int brotherBlock, Registry* fatherRegistry) throw () {

	// Considero que no hay sobreflujo al insertar en el bloque interno
	int answer = INSERTION_OK;
	// Busco la rama por la cual insertar
	int insertBranch = this->searchBranch(internalNode, registryKey);

	//OBTENER RAMA HERMANA PARA ENVIAR A LOS INSERTAR DE MAS ABAJO, ES LA RAMA DERECHA POR DEFECTO, SINO LA IZQ
	int sisterBranch = this->searchBranchSister(internalNode, registryKey);

	//Obtengo elemento actual del bloque por el cual bajo a la rama siguiente
	list<Registry*>::iterator actualRegistry = internalNode->iteratorBegin();
	list<Registry*>::iterator endRegistry = internalNode->iteratorEnd();
	--endRegistry;

	while (actualRegistry != endRegistry) {
		if (registryKey->compareTo(*actualRegistry) < 0){
			break;
		}
		actualRegistry++;
	}

	// Leo el bloque por el cual insertar
	Node* nodeInsertBranch = this->readNode(insertBranch);

	// Si el bloque existe
	if (nodeInsertBranch != NULL) {
		// Considero que no hay sobreflujo al insertar en el bloque hijo
		int childAnswer = INSERTION_OK;
		if (nodeInsertBranch->isLeaf()) {
			//MANDAR TAMBIEN POR PARAMETRO EL NUMERO DE BLOQUE QUE CONSEGUI
			LeafNode* leafInsertNode = (LeafNode*)nodeInsertBranch;
			// Inserto en el bloque externo hijo
			childAnswer = this->insertLeafNode(leafInsertNode, registryKey, container, sisterBranch);
		} else {
			InternalNode* internalInsertNode = (InternalNode*)nodeInsertBranch;
			Registry* regFatherSon = this->extractKey((Registry*)(*actualRegistry));
			// Inserto en el bloque interno hijo
			childAnswer = this->insertInternalNode(internalInsertNode, registryKey, container, sisterBranch, regFatherSon);
		}
		//Se actualiza la clave cuando hay balanceo en el hijo
		if (childAnswer == INSERTION_OK){
			if (fatherRegistry != NULL)
				delete fatherRegistry;
		}

		//Se actualiza la clave cuando hay balanceo en el hijo
		if (childAnswer == BALANCE){
			// Agrego componente
			Registry* replaceReg = (Registry*)(*actualRegistry);
			if(DEBUG)cout<<"reemplazo este:";
			if(DEBUG)replaceReg->print(cout);
			if(DEBUG)cout<<"|por este :";
			if(DEBUG)container->getRegMidleKey()->print(cout);
			if(DEBUG)cout<<"|"<<endl;;
			internalNode->replaceRegistry(replaceReg, container->getRegMidleKey());
			delete replaceReg;
			// Escribo bloque
			this->writeNode(internalNode,internalNode->getNumBlock());
			if (fatherRegistry != NULL)
				delete fatherRegistry;

		}

		// Verifico si hubo sobrelujo al insertar en el bloque hijo
		if (childAnswer == OVER_FLOW) {
			// Verifico si puedo agregar en el bloque interno
			Registry* replaceReg = (Registry*)(*actualRegistry);
			internalNode->replaceRegistry(replaceReg, container->getLeftRegKey());
			delete replaceReg;
			if (internalNode->posibleToAgregateComponent(container->getRightRegKey())){
				// Inserto en el bloque interno no lleno
				this->insertInternalNodeNotFull(internalNode, container->getRightRegKey(),container->getRightBlock());
				if (fatherRegistry != NULL)
					delete fatherRegistry;

			} else {

				// LEO BLOQUE DE LA DIR DEL HERMANO
				InternalNode* branchSisterNode=NULL;

				if (brotherBlock != 0){
					branchSisterNode = (InternalNode*)this->readNode(brotherBlock);
				}else
					branchSisterNode = NULL;

				// BALANCEO
				if (this->balanceInternalNode(internalNode, branchSisterNode,
						container, fatherRegistry)) {
					// Hubo balanceo
					answer = BALANCE;
				} else {
					// Inserto en el bloque interno lleno
					answer = OVER_FLOW;

					// Si la rama hermana es nula el sobreflujo se da en la raiz, no inserto, la raiz se encarga
					if (branchSisterNode != NULL) {
						this->insertInternalNodeFull(internalNode,
								branchSisterNode, container->getRightRegKey(),
								container, fatherRegistry);

					}
				}
				delete branchSisterNode;
			}
		}
	}
	delete nodeInsertBranch;
	return answer;
}
void IndexBSharp::insertInternalNodeNotFull(InternalNode* internalNode,
		Registry* registryKey, unsigned int rightBlock) throw () {
	unsigned int insertPosition = this->searchPositionInsertInternalNode(
			registryKey, internalNode->iteratorBegin(),
			internalNode->iteratorEnd());

	internalNode->addReg(registryKey);
	internalNode->sortListRegistry();
	// Agrego rama
	vector<int>::iterator iterator=internalNode->firstBranch();
	for (unsigned int var = 0; var < insertPosition + 1; var++) {
		iterator++;
	}
	internalNode->addBranch(iterator,rightBlock);
	// Escribo bloque
	this->writeNode(internalNode, internalNode->getNumBlock());
}

bool IndexBSharp::insertInternalNodeFull(InternalNode* internalNode,InternalNode* brothersNode, Registry* registryKey,
		ContainerInsertion* container, Registry* registryFather) throw () {
	 unsigned int cont=0;
	if (brothersNode== NULL)
		return false;
	// Busco numero de bloque libre
	unsigned int numBlockFree = this->freeBlockController->searchFreeBlock();
	// Creo nuevo bloque interno para dividir
	InternalNode* newInternalNode = new InternalNode(this->typeElement,this->sizeBlock, numBlockFree, internalNode->getLevel());
	unsigned int rightBlock = container->getRightBlock();
	// Crea contenedor de registros para insertar ordenado el registro...
	listRegistry.clear();
	// Crea contenedor de ramas para insertar la rama nueva...
	branchList.clear();

	//Registro menor del bloque actual
	Registry* registryCurrent= static_cast<Registry*>(*(internalNode->iteratorBegin()));

	//Registro menor bloque hermano
	Registry* registrybrothers= static_cast<Registry*>(*(brothersNode->iteratorBegin()));


	InternalNode* leftNode;
	InternalNode* rightNode;
	list<Registry*> listRegLeftNode;
	list<Registry*> listRegRightNode;
	vector<int> branchListLeftNode;
	vector<int> branchListRightNode;

	//Diferencio cual es el bloque izquierdo del derecho
	if (registryCurrent->compareTo(registrybrothers)<0) {
		internalNode->transferRegistry(listRegLeftNode);
		brothersNode->transferRegistry(listRegRightNode);
		internalNode->transferBranchs(branchListLeftNode);
		brothersNode->transferBranchs(branchListRightNode);
		leftNode = internalNode;
		rightNode = brothersNode;
	}else{
		brothersNode->transferRegistry(listRegLeftNode);
		internalNode->transferRegistry(listRegRightNode);
		brothersNode->transferBranchs(branchListLeftNode);
		internalNode->transferBranchs(branchListRightNode);
		leftNode = brothersNode;
		rightNode = internalNode;
	}
	this->listRegistry.clear();
	this->mergeComponentList(this->listRegistry,listRegLeftNode,listRegRightNode);
	this->mergeBranchList(this->branchList,branchListLeftNode,branchListRightNode);
	// Inserta ordenado el registro padre
	listRegistry.push_back(registryFather);
	listRegistry.sort(comparatorRegistry);
	// Busca posicion de insercion para el registroClave
	unsigned int insertPos = searchPositionInsertInternalNode(registryKey, listRegistry.begin(), listRegistry.end());
	// Inserta ordenado el registro clave
	listRegistry.push_back(registryKey);
	listRegistry.sort(comparatorRegistry);
	 this->printListReg(cout,listRegistry.begin(),listRegistry.end());
	// Inserta la rama
	//adelanto el puntero
	std::vector<int>::iterator itListBranchs = branchList.begin();
	this->advanceVectorPointer(itListBranchs ,insertPos + 1);
	// Inserta la rama
	branchList.insert(itListBranchs, rightBlock);
	 this->printBranch(cout,this->branchList.begin(),this->branchList.end());

	list<Registry*>::iterator iteratorListRegFinal = listRegistry.begin();
	vector<int>::iterator  iteratorBranchsFinal= branchList.begin();
	leftNode->addBranch(*iteratorBranchsFinal);
	if(DEBUG)std::cout<<"  RAMA:B1 "<<*iteratorBranchsFinal<<" - "<<std::endl;
	iteratorBranchsFinal++;
	cont++;

	unsigned int averageEstimate = this->averageEstimate(listRegistry.begin(), listRegistry.end());
	leftNode->setAverageWeight(averageEstimate);
	rightNode->setAverageWeight(averageEstimate);
	newInternalNode->setAverageWeight(averageEstimate);
	//le sumo el peso estimado de la rama asociada a la clave
	averageEstimate+=+sizeof(unsigned int);
	while (leftNode->isUnderflow(getSizeMinumumNode(averageEstimate,listRegistry.size()))){
		if(DEBUG)std::cout<<"  RAMA:B1 "<<*iteratorBranchsFinal<<" - "<<std::endl;
		leftNode->addBranch(*iteratorBranchsFinal);
		leftNode->addComponent(*iteratorListRegFinal);
		Registry* reg=(Registry*)*iteratorListRegFinal;
		if(DEBUG)reg->print(cout);
		iteratorListRegFinal++;
		iteratorBranchsFinal++;
		cont++;
	}
	rightNode->addBranch(*iteratorBranchsFinal);
	iteratorBranchsFinal++;
	cont++;
	if(DEBUG)std::cout<<"  RAMA:B2 "<<*iteratorBranchsFinal<<" - "<<std::endl;
	// Establece el elemento izquierdo a subir en el resultado de insercion
	Registry* leftRegKey =(Registry*)*iteratorListRegFinal;
	container->setLeftRegKey(leftRegKey);
	iteratorListRegFinal++;
	while (rightNode->isUnderflow(getSizeMinumumNode(averageEstimate,listRegistry.size()))){
		rightNode->addBranch(*iteratorBranchsFinal);
		rightNode->addComponent(*iteratorListRegFinal);
		Registry* reg=(Registry*)*iteratorListRegFinal;
		if(DEBUG)reg->print(cout);
		if(DEBUG)std::cout<<"  RAMA:B2 "<<*iteratorBranchsFinal<<" - "<<std::endl;
		iteratorListRegFinal++;
		iteratorBranchsFinal++;
		cont++;
	}

	newInternalNode->addBranch(*iteratorBranchsFinal);
	if(DEBUG)std::cout<<"  RAMA:B3 "<<*iteratorBranchsFinal<<" - "<<std::endl;
	iteratorBranchsFinal++;
	cont++;
	// Establece el elemento derecho a subir en el resultado de insercion
	Registry* rightRegKey =(Registry*)*iteratorListRegFinal;
	container->setRightRegKey(rightRegKey);
	iteratorListRegFinal++;
	while (iteratorListRegFinal != listRegistry.end()){
		if (newInternalNode->posibleToAgregateComponent(*iteratorListRegFinal)){
			if(DEBUG)	std::cout<<"  RAMA:B3 "<<*iteratorBranchsFinal<<" - "<<std::endl;
			Registry* reg=(Registry*)*iteratorListRegFinal;
			if(DEBUG)reg->print(cout);
			newInternalNode->addComponent(reg);
			newInternalNode->addBranch(*iteratorBranchsFinal);

		}
		else
			break;
		iteratorListRegFinal++;
		iteratorBranchsFinal++;
		cont++;
	}
	    if(DEBUG){
	     cout<<" CANTIDAD DE RAMAS INSERTADAS "<<cont<<endl;
		  cout<<" CANTIDAD DE RAMAS "<<branchList.size()<<endl;
	    }

	   if(cont!=branchList.size()){
		   cout<<"###########################################################"<<endl;
	       cout<<"############# DANGER SE PERDIO UN BLOQUE    ##############"<<endl;
	       cout<<"###########################################################"<<endl;
	       throw eNotSpace("ERROR EN EL SPLIT SE PÉRDIERON RAMAS !!!!!!");
	   }
	// Escribe bloque a dividir en disco
	this->writeNode(leftNode,leftNode->getNumBlock());
	// Escribe bloque a dividir en disco
	this->writeNode(rightNode,rightNode->getNumBlock());
	// Escribe bloque nuevo
	this->writeNode(newInternalNode,newInternalNode->getNumBlock());

	// Establezco bloque izquierdo en resultado de insercion
	container->setLeftBlock(leftNode->getNumBlock());
	// Establezco bloque derecho en resultado de insercion
	container->setRightBlock(rightNode->getNumBlock());
	// Establezco bloque medio en resultado de insercion
	container->setRightBlock(newInternalNode->getNumBlock());
	container->setMediumBlock(rightNode->getNumBlock());
	delete newInternalNode;
	registryFather=NULL;
	return true;
}

unsigned int IndexBSharp::searchPositionInsertLeafNode(Registry* registry,
		list<Registry*>::iterator iteratorBegin,
		list<Registry*>::iterator iteratorEnd) throw () {
	unsigned int insertPos = 0;
	for (list<Registry*>::iterator actual = iteratorBegin; actual
			!= iteratorEnd; ++actual, ++insertPos) {
		Registry* reg = *actual;
		if (!(reg->compareTo(registry) < 0)) {
			break;
		}
	}
	return insertPos;
}
unsigned int IndexBSharp::searchPositionInsertInternalNode(Registry* registry,
		list<Registry*>::iterator iteratorBegin,
		list<Registry*>::iterator iteratorEnd) throw () {
	unsigned int insertPos = 0;
	for (list<Registry*>::iterator actual = iteratorBegin; actual
			!= iteratorEnd; ++actual, ++insertPos) {
		Registry* reg = *actual;
		if ((reg->compareTo(registry) < 0) || (reg->compareTo(registry) == 0)) {

		} else {
			break;
		}
	}
	return insertPos;
}
int IndexBSharp::searchBranch(InternalNode* internalNode, Registry* registry) throw () {
	std::list<Registry*>::iterator actualComponent =internalNode->iteratorBegin();
	std::list<Registry*>::iterator endComponent =	internalNode->iteratorEnd();
	unsigned int branchPos = 0;
	if(DEBUG)std::cout<<"Buscar Rama"<<std::endl;
	while (actualComponent != endComponent) {
		Registry* actual = (Registry*)*actualComponent;
		if(DEBUG){
			std::cout << " Pos Rama: " << branchPos;
			std::cout << " Registro actual: "; this->printRegistry(actual,std::cout);
			std::cout << " Registro buscado: ";	this->printRegistry(registry,std::cout);
		}
		if (registry->compareTo(actual) < 0) {
			break;
		}
		++actualComponent;
		++branchPos;
	}
	return internalNode->getBranch(branchPos);

}

int IndexBSharp::searchBranchSister(InternalNode* internalNode,
		Registry* registry) throw () {
	std::list<Registry*>::const_iterator actualComponent =
			internalNode->iteratorBegin();
	std::list<Registry*>::const_iterator endComponent =
			internalNode->iteratorEnd();
	unsigned int branchSister = 0;
	unsigned int positionBranch = 0;

	while (actualComponent != endComponent) {
		Registry* actual=*actualComponent;
		if (registry->compareTo(actual) < 0) {
			break;
		}
		++actualComponent;
		++positionBranch;
	}

	if (actualComponent == endComponent) {
		branchSister = positionBranch - 1;
	} else {
		branchSister = positionBranch + 1;
	}

	return internalNode->getBranch(branchSister);
}
Registry* IndexBSharp::extractKey(Registry* registry) throw () {
	return registry->cloneRegKey();
}
Registry* IndexBSharp::searchLeafNode(LeafNode* leafNode, Registry* registry) throw () {
	Registry* findRegistry = NULL;
	bool find = false;
	if(DATA==1){
	if (this->typeElement == TYPE_REG_PRIMARY || this->typeElement== TYPE_REG_CLASSIFICATION ||this->typeElement==TYPE_REG_INVERTED_INDEX) {
		findRegistry = leafNode->searchRegistryBlockData(registry,this->containerInsertDataBlock);
		return findRegistry;
	}
	}
	if(this->typeElement== TYPE_REG_SELECTION||DATA==0){
		if (leafNode != NULL) {
			std::list<Registry*>::const_iterator actualComponent =
					leafNode->iteratorBegin();
			std::list<Registry*>::const_iterator endComponent =
					leafNode->iteratorEnd();

			while (actualComponent != endComponent && !find) {
				Registry* iterRegistry = *actualComponent;
				if (iterRegistry->equals(registry)) {
					findRegistry = iterRegistry;
					delete registry;
					return findRegistry->clone();
				}
				++actualComponent;
			}
		}
	}

	return findRegistry;
}
Registry* IndexBSharp::searchInternalNode(InternalNode* internalNode,Registry* registry) throw () {

	Registry* findRegistry = NULL;
	if (internalNode != NULL) {
		int numBranch = this->searchBranch(internalNode, registry);
		if(DEBUG)cout<<"Rama a buscar"<<numBranch<<endl;
		Node* readNode = this->readNode(numBranch);
		if (readNode != NULL) {
			if (readNode->isLeaf()) {
				LeafNode* leafNodeRead = (LeafNode*) readNode;
				findRegistry = this->searchLeafNode(leafNodeRead, registry);
			} else {
				InternalNode* internalNodeRead = (InternalNode*) readNode;
				findRegistry = this->searchInternalNode(internalNodeRead,registry);
			}
		}
		delete readNode;
	}
	return findRegistry;

}
void IndexBSharp::printRecursive(Node* currentNode, std::ostream& outStream,
		unsigned int level) throw () {

	if (currentNode != NULL) {
		outStream << std::string(level * 4, '-');
		outStream << "NUMERO BLOQUE: " << currentNode->getNumBlock() << " ";
		outStream << "NIVEL: " << currentNode->getLevel() << " ";
		outStream << "COMPONENTES BLOQUE: " << endl;

		list<Registry*>::iterator actualComp = currentNode->iteratorBegin();
		list<Registry*>::iterator endComp = currentNode->iteratorEnd();
		std::vector<int>::const_iterator actualBranch;
		if (!currentNode->isLeaf()) {
			InternalNode* internalNode = (InternalNode*) currentNode;
			actualBranch =	internalNode->firstBranch();
			outStream << " " << *actualBranch<< " ";
			actualBranch++;
		}
		while (actualComp != endComp) {
			Registry* reg = *actualComp;
			this->printRegistry(reg, outStream);
			if (!currentNode->isLeaf()) {
				outStream << " " << *actualBranch<< " ";
			}
			++actualComp;
			++actualBranch;
		}
		if (!currentNode->isLeaf())
			outStream << endl;
		outStream << "--ESPACIO OCUPADO: " << currentNode->getOcupedLong();
		if (currentNode->isLeaf()) {
			outStream << " --EN BLOQUE HOJA--";
			LeafNode* leafNode = (LeafNode*) currentNode;
			outStream << "CON SIGUIENTE: " << leafNode->getNextBlock() << " ";

			outStream << std::endl;
			outStream << std::endl;
			outStream << std::endl;
		} else {
			outStream << " --EN BLOQUE INTERNO--";
			InternalNode* internalNode = (InternalNode*) currentNode;
			std::vector<int>::const_iterator actualBranch;
			std::vector<int>::const_iterator endBranch = internalNode->lastBranch();

//			std::vector<int>::const_iterator actualBranch =	internalNode->firstBranch();
//			std::cout << "CON RAMAS(";
//			while (actualBranch != endBranch) {
//				outStream << " " << *actualBranch;
//				++actualBranch;
//			}
//			outStream << " ) ";
			outStream << std::endl;
			outStream << std::endl;
			outStream << std::endl;

			actualBranch = internalNode->firstBranch();
			endBranch = internalNode->lastBranch();
			while (actualBranch != endBranch) {
				Node* childNode = this->readNode(*actualBranch);
				if (childNode != NULL) {
					this->printRecursive(childNode, outStream, level + 1);
				}
				++actualBranch;
				delete childNode;
			}
		}
	}

}
void IndexBSharp::printRegistry(Registry* registry, std::ostream& outStream) throw () {
	registry->setContainer(this->containerInsertDataBlock);
	registry->print(outStream);

}
int IndexBSharp::getLongBytes(){
    return 10000;
}
IteratorBSharp* IndexBSharp::getIterator() throw(){
	int firstNode = getFirstNode();
	return new IteratorBSharp(firstNode, this->typeElement, this->binaryFile, this->sizeBlock, this->containerInsertDataBlock);
}

int IndexBSharp::getFirstNode() throw(){
	if (this->rootNode->isLeaf()) {
		return 0;
	}else{
		InternalNode* internalNode = static_cast<InternalNode*> (this->rootNode);
		int branch;
		int level;
		level = internalNode->getLevel();
		branch = internalNode->getBranch(0);
		while(level!=1){
			Node* node = this->readNode(branch);
			internalNode = static_cast<InternalNode*> (node);
			branch = internalNode->getBranch(0);
			level = internalNode->getLevel();
			delete internalNode;
		}
		return branch;
	}
}
void IndexBSharp::printBranch(std::ostream& outStream,vector<int>::iterator begin, vector<int>::iterator end) {
	if(DEBUG){
	int count=0;
	std::cout << " RAMAS(";
	while (begin != end) {
		outStream << " " << *begin;
		++begin;
		count++;
	}
	outStream << " ) ";
	outStream << "son :";
	outStream <<count;
	outStream << " ";
	outStream <<endl;
	}
}
void IndexBSharp::printListReg(std::ostream& outStream,list<Registry*>::iterator begin, list<Registry*>::iterator end) {
	if(DEBUG){
	int count=0;
	std::cout << " registros(";
	while (begin != end) {
		Registry* reg=(Registry*)*begin;
		reg->print(outStream);
		++begin;
		count++;
	}
	outStream << " ) ";
	outStream << "son :";
	outStream <<count;
	outStream << " ";
	outStream <<endl;
	}
}

bool IndexBSharp::removeLeafNodeEmpty(LeafNode* currentNode,LeafNode* firstBrotherNode, LeafNode* secondBrotherNode,ContainerInsertion* container,
		Registry* regFirstFather, Registry* regSecondFather){


	unsigned int count=0;

	if (firstBrotherNode == NULL || secondBrotherNode == NULL)
			return false;


	// Crea contenedor de componentes para almacenar los registros de los bloques
	list<Registry*> regList;

	Registry* currentReg = *(currentNode->iteratorBegin());

	//Registro menor bloque primer hermano
	Registry* firstBrotherReg = (*(firstBrotherNode->iteratorBegin()));

	//Registro menor bloque segundo hermano
	Registry* secondBrotherReg = (*(secondBrotherNode->iteratorBegin()));

	LeafNode*  leftNode;
	LeafNode* centerNode;
	LeafNode* rigthNode;
	list<Registry*> leftNodeReg;
	list<Registry*> centerNodeReg;
	list<Registry*> rigthNodeReg;

	//Diferencio orden bloques
	if (currentReg->compareTo(firstBrotherReg) <0)
		if (currentReg->compareTo(secondBrotherReg) < 0){
			leftNode = currentNode;
			if (firstBrotherReg->compareTo(secondBrotherReg) < 0){
				centerNode = firstBrotherNode;
				rigthNode = secondBrotherNode;
			}else{
				centerNode = secondBrotherNode;
				rigthNode = firstBrotherNode;
			}
		}else{
			leftNode = secondBrotherNode;
			centerNode = currentNode;
			rigthNode = firstBrotherNode;
		}
	else
		if (currentReg->compareTo(secondBrotherReg) < 0){
			leftNode = firstBrotherNode;
			centerNode = currentNode;
			rigthNode = secondBrotherNode;
		}else{
			rigthNode = currentNode;
			if (firstBrotherReg->compareTo(secondBrotherReg) < 0){
				leftNode = firstBrotherNode;
				centerNode = secondBrotherNode;
			}else{
				leftNode = secondBrotherNode;
				centerNode = firstBrotherNode;
			}
		}

	leftNode->transferRegistry(leftNodeReg);
	centerNode->transferRegistry(centerNodeReg);
	rigthNode->transferRegistry(rigthNodeReg);

	this->listRegistry.clear();// TODO OJO ESTA LA AGREGAMOS NOSOTROS
	this->mergeComponentList(this->listRegistry,leftNodeReg,centerNodeReg);
	this->mergeComponentList(regList,this->listRegistry,rigthNodeReg);
	leftNode->setAverageWeight(0);

	// Llena bloque izquierdo
	list<Registry*>::iterator iterListReg = regList.begin();
	while (leftNode->isUnderflowRemove()){
		Registry* reg=(Registry*)*iterListReg;
		leftNode->addComponent(reg);
		iterListReg++;
		count++;
	}

	// Llena bloque centro
	container->setRegMidleKey(this->extractKey(*iterListReg));
	while (iterListReg != regList.end()){
			Registry* reg=(Registry*)*iterListReg;
			if (centerNode->posibleToAgregateComponent(reg))
				centerNode->addComponent(reg);
			else
				break;
			iterListReg++;
			count++;
	}

	int sizeOldMiddleKey = regFirstFather->getLongBytes() + regSecondFather->getLongBytes() + sizeof(int);
	int sizeNewMiddleKey = container->getRegMidleKey()->getLongBytes();
	if (iterListReg != regList.end() || sizeOldMiddleKey < sizeNewMiddleKey){
		leftNode->clearListRegistry();
		list<Registry*>::iterator nodeRegList = leftNodeReg.begin();
		while (nodeRegList != leftNodeReg.end()){
			Registry* reg=(Registry*)*nodeRegList;
			leftNode->addComponent(reg);
			nodeRegList++;
		}
		centerNode->clearListRegistry();
		nodeRegList = centerNodeReg.begin();
		while (nodeRegList != centerNodeReg.end()){
			Registry* reg=(Registry*)*nodeRegList;
			centerNode->addComponent(reg);
			nodeRegList++;
		}
		rigthNode->clearListRegistry();
		nodeRegList = rigthNodeReg.begin();
		while (nodeRegList != rigthNodeReg.end()){
			Registry* reg=(Registry*)*nodeRegList;
			rigthNode->addComponent(reg);
			nodeRegList++;
		}
		leftNodeReg.clear();
		centerNodeReg.clear();
		rigthNodeReg.clear();
		delete container->getRegMidleKey();
		return false;
	}
	else{
		// Enlaza a los bloques
		centerNode->setNextBlock(rigthNode->getNextBlock());
		container->setRightBlock(rigthNode->getNumBlock());
		// Marco segundo bloque como borrado
		this->freeBlockController->writeFreeBlock(rigthNode->getNumBlock());
		// Escribo primer bloque
		this->writeNode(leftNode, leftNode->getNumBlock());
		// Escribo primer bloque
		this->writeNode(centerNode, centerNode->getNumBlock());

		return true;
	}
}

bool IndexBSharp::balanceLeafNodeRemove(LeafNode* currentNode,LeafNode* firstBrotherNode, LeafNode* secondBrotherNode,
		ContainerInsertion* container, Registry* regFirstFather, Registry* regSecondFather)throw(){

	unsigned int count=0;

	if (firstBrotherNode == NULL || secondBrotherNode == NULL)
			return false;


	// Crea contenedor de componentes para almacenar los registros de los bloques
	list<Registry*> regList;

	Registry* currentReg = *(currentNode->iteratorBegin());

	//Registro menor bloque primer hermano
	Registry* firstBrotherReg = (*(firstBrotherNode->iteratorBegin()));

	//Registro menor bloque segundo hermano
	Registry* secondBrotherReg = (*(secondBrotherNode->iteratorBegin()));

	LeafNode*  leftNode;
	LeafNode* centerNode;
	LeafNode* rigthNode;
	list<Registry*> leftNodeReg;
	list<Registry*> centerNodeReg;
	list<Registry*> rigthNodeReg;

	//Diferencio orden bloques
	if (currentReg->compareTo(firstBrotherReg) <0)
		if (currentReg->compareTo(secondBrotherReg) < 0){
			leftNode = currentNode;
			if (firstBrotherReg->compareTo(secondBrotherReg) < 0){
				centerNode = firstBrotherNode;
				rigthNode = secondBrotherNode;
			}else{
				centerNode = secondBrotherNode;
				rigthNode = firstBrotherNode;
			}
		}else{
			leftNode = secondBrotherNode;
			centerNode = currentNode;
			rigthNode = firstBrotherNode;
		}
	else
		if (currentReg->compareTo(secondBrotherReg) < 0){
			leftNode = firstBrotherNode;
			centerNode = currentNode;
			rigthNode = secondBrotherNode;
		}else{
			rigthNode = currentNode;
			if (firstBrotherReg->compareTo(secondBrotherReg) < 0){
				leftNode = firstBrotherNode;
				centerNode = secondBrotherNode;
			}else{
				leftNode = secondBrotherNode;
				centerNode = firstBrotherNode;
			}
		}

	leftNode->transferRegistry(leftNodeReg);
	centerNode->transferRegistry(centerNodeReg);
	rigthNode->transferRegistry(rigthNodeReg);

	this->listRegistry.clear();// TODO OJO ESTA LA AGREGAMOS NOSOTROS
	this->mergeComponentList(this->listRegistry,leftNodeReg,centerNodeReg);
	this->mergeComponentList(regList,this->listRegistry,rigthNodeReg);


	unsigned int averageWeight = this->averageEstimate(regList.begin(), regList.end());
	leftNode->setAverageWeight(averageWeight);
	centerNode->setAverageWeight(averageWeight);
	rigthNode->setAverageWeight(averageWeight);

	list<Registry*>::iterator iterRegFinalList = regList.begin();
	while (leftNode->isUnderflow((averageWeight*regList.size())/3)){
		Registry* reg=(Registry*)*iterRegFinalList;
		leftNode->addComponent(reg);
		iterRegFinalList++;
		count++;
	}

	// Establece el elemento izq a subir en el resultado
	container->setLeftRegKey(this->extractKey(*iterRegFinalList));
	while (centerNode->isUnderflow((averageWeight*regList.size())/3)){
			Registry* reg=(Registry*)*iterRegFinalList;
			centerNode->addComponent(reg);
			iterRegFinalList++;
			count++;
	}
	// Establece el elemento der a subir en el resultado
	container->setRightRegKey(this->extractKey(*iterRegFinalList));
	while (iterRegFinalList != regList.end()){
		if (rigthNode->posibleToAgregateComponent(*iterRegFinalList)){
			Registry* reg=(Registry*)*iterRegFinalList;
			rigthNode->addComponent(reg);
		}
		else
			break;
		iterRegFinalList++;
		count++;
	}

	int sizeOldLeftKey = regFirstFather->getLongBytes();
	int sizeNewLeftKey = container->getLeftRegKey()->getLongBytes();
	int sizeOldRightKey = regSecondFather->getLongBytes();
	int sizeNewRightKey = container->getRightRegKey()->getLongBytes();

	if (sizeOldLeftKey + sizeOldRightKey < sizeNewRightKey + sizeNewLeftKey) {

		if (DEBUG){
			std::cout<< "Bloques: "<<leftNode->getNumBlock()<<", "<<centerNode->getNumBlock()<<", "<<
					rigthNode->getNumBlock()<<" no se pudieron balancear, queda bloque "<<
					currentNode->getNumBlock()<<" en underflow"<<std::endl;
		}

		leftNode->clearListRegistry();
		list<Registry*>::iterator nodeRegList = leftNodeReg.begin();
		while (nodeRegList != leftNodeReg.end()){
			Registry* reg=(Registry*)*nodeRegList;
			leftNode->addComponent(reg);
			nodeRegList++;
		}
		centerNode->clearListRegistry();
		nodeRegList = centerNodeReg.begin();
		while (nodeRegList != centerNodeReg.end()){
			Registry* reg=(Registry*)*nodeRegList;
			centerNode->addComponent(reg);
			nodeRegList++;
		}
		rigthNode->clearListRegistry();
		nodeRegList = rigthNodeReg.begin();
		while (nodeRegList != rigthNodeReg.end()){
			Registry* reg=(Registry*)*nodeRegList;
			rigthNode->addComponent(reg);
			nodeRegList++;
		}
		delete container->getLeftRegKey();
		delete container->getRightRegKey();
		leftNodeReg.clear();
		centerNodeReg.clear();
		rigthNodeReg.clear();
		return false;
	}
	else{

		if(count!=regList.size()){
			throw eLostReg("Se perdio al menos un registro");
		}

		// Escribe bloque izquierdo
		this->writeNode(leftNode,leftNode->getNumBlock());
		// Escribe bloque centro
		this->writeNode(centerNode, centerNode->getNumBlock());
		// Escribe bloque derecho
		this->writeNode(rigthNode, rigthNode->getNumBlock());

		return true;

	}

}
bool IndexBSharp::balanceInternalNodeRemove(InternalNode* currentNode,InternalNode* firstBrotherNode, InternalNode* secondBrotherNode,ContainerInsertion* container,Registry* regFirstFather, Registry* regSecondFather) throw(){
	unsigned int count=0;

	if (firstBrotherNode == NULL || secondBrotherNode == NULL)
			return false;


	// Crea contenedor de componentes para almacenar los registros de los bloques
	list<Registry*> regList;

	Registry* currentReg = *(currentNode->iteratorBegin());

	//Registro menor bloque primer hermano
	Registry* firstBrotherReg = (*(firstBrotherNode->iteratorBegin()));

	//Registro menor bloque segundo hermano
	Registry* secondBrotherReg = (*(secondBrotherNode->iteratorBegin()));

	InternalNode*  leftNode;
	InternalNode* centerNode;
	InternalNode* rigthNode;
	list<Registry*> leftNodeReg;
	list<Registry*> centerNodeReg;
	list<Registry*> rigthNodeReg;
//	Registry* firstAuxToRemove;
//	Registry* secondAuxToRemove;

	// Crea contenedor de ramas para insertar la rama nueva...
	vector<int> branchList;
	vector<int> branchListLeftNode;
	vector<int> branchListCenterNode;
	vector<int> branchListRightNode;

	//Diferencio orden bloques
	if (currentReg->compareTo(firstBrotherReg) <0)
		if (currentReg->compareTo(secondBrotherReg) < 0){
			leftNode = currentNode;
			if (firstBrotherReg->compareTo(secondBrotherReg) < 0){
				centerNode = firstBrotherNode;
				rigthNode = secondBrotherNode;
			}else{
				centerNode = secondBrotherNode;
				rigthNode = firstBrotherNode;
			}
		}else{
			leftNode = secondBrotherNode;
			centerNode = currentNode;
			rigthNode = firstBrotherNode;
		}
	else
		if (currentReg->compareTo(secondBrotherReg) < 0){
			leftNode = firstBrotherNode;
			centerNode = currentNode;
			rigthNode = secondBrotherNode;
		}else{
			rigthNode = currentNode;
			if (firstBrotherReg->compareTo(secondBrotherReg) < 0){
				leftNode = firstBrotherNode;
				centerNode = secondBrotherNode;
			}else{
				leftNode = secondBrotherNode;
				centerNode = firstBrotherNode;
			}
		}

	leftNode->transferRegistry(leftNodeReg);
	centerNode->transferRegistry(centerNodeReg);
	rigthNode->transferRegistry(rigthNodeReg);

	this->listRegistry.clear();// TODO OJO ESTA LA AGREGAMOS NOSOTROS
	this->mergeComponentList(this->listRegistry,leftNodeReg,centerNodeReg);
	this->mergeComponentList(regList,this->listRegistry,rigthNodeReg);


	leftNode->transferBranchs(branchListLeftNode);
	centerNode->transferBranchs(branchListCenterNode);
	rigthNode->transferBranchs(branchListRightNode);

	this->branchList.clear();
	this->mergeBranchList(this->branchList,branchListLeftNode,branchListCenterNode);
	this->mergeBranchList(branchList,this->branchList,branchListRightNode);

	regList.push_back(regFirstFather);
	regList.push_back(regSecondFather);
	regList.sort(comparatorRegistry);

	// Llena bloque izquierdo
	list<Registry*>::iterator iterRegFinalList = regList.begin();
	vector<int>::iterator iterBranchFinalList = branchList.begin();

	unsigned int averageWeight = this->averageEstimate(regList.begin(), regList.end());
	leftNode->setAverageWeight(averageWeight);
	centerNode->setAverageWeight(averageWeight);
	rigthNode->setAverageWeight(averageWeight);
	//le sumo el peso estimado de la rama asociada a la clave
	averageWeight+=+sizeof(unsigned int);
	leftNode->addBranch(*iterBranchFinalList);
	iterBranchFinalList++;


	while (leftNode->isUnderflow((averageWeight*regList.size())/3)){
		Registry* reg=(Registry*)*iterRegFinalList;
		leftNode->addComponent(reg);
		iterRegFinalList++;
		leftNode->addBranch(*iterBranchFinalList);
		iterBranchFinalList++;
		count++;
	}

	centerNode->addBranch(*iterBranchFinalList);
	iterBranchFinalList++;

	// Establece el elemento izq a subir en el resultado
//	firstAuxToRemove = (Registry*)*iterRegFinalList;
//	container->setLeftRegKey(this->extractKey(*iterRegFinalList));
	container->setLeftRegKey(*iterRegFinalList);
	iterRegFinalList++;
	count++;
	while (centerNode->isUnderflow((averageWeight*regList.size())/3)){
			Registry* reg=(Registry*)*iterRegFinalList;
			centerNode->addComponent(reg);
			centerNode->addBranch(*iterBranchFinalList);
			iterBranchFinalList++;
			iterRegFinalList++;
			count++;
	}
	// Establece el elemento izq a subir en el resultado
//	secondAuxToRemove = (Registry*)*iterRegFinalList;
//	container->setRightRegKey(this->extractKey(*iterRegFinalList));
	container->setRightRegKey(*iterRegFinalList);
	iterRegFinalList++;
	rigthNode->addBranch(*iterBranchFinalList);
	iterBranchFinalList++;
	count++;
	while (iterRegFinalList != regList.end()){
		if (rigthNode->posibleToAgregateComponent(*iterRegFinalList)){
			Registry* reg=(Registry*)*iterRegFinalList;
			rigthNode->addComponent(reg);
			rigthNode->addBranch(*iterBranchFinalList);
		}
		else
			break;
		iterRegFinalList++;
		iterBranchFinalList++;
		count++;
	}

	int sizeOldLeftKey = regFirstFather->getLongBytes();
	int sizeNewLeftKey = container->getLeftRegKey()->getLongBytes();
	int sizeOldRightKey = regSecondFather->getLongBytes();
	int sizeNewRightKey = container->getRightRegKey()->getLongBytes();

	if (sizeOldLeftKey + sizeOldRightKey < sizeNewRightKey + sizeNewLeftKey){

		if (DEBUG){
			std::cout<< "Bloques: "<<leftNode->getNumBlock()<<", "<<centerNode->getNumBlock()<<", "<<
					rigthNode->getNumBlock()<<" no se pudieron balancear, queda bloque "<<
					currentNode->getNumBlock()<<" en underflow"<<std::endl;
		}

		leftNode->clearListRegistry();
		list<Registry*>::iterator iterRegNodeList = leftNodeReg.begin();

		while (iterRegNodeList != leftNodeReg.end()){
			Registry* reg=(Registry*)*iterRegNodeList;
			leftNode->addComponent(reg);
			iterRegNodeList++;
		}
		centerNode->clearListRegistry();
		iterRegNodeList = centerNodeReg.begin();
		while (iterRegNodeList != centerNodeReg.end()){
			Registry* reg=(Registry*)*iterRegNodeList;
			centerNode->addComponent(reg);
			iterRegNodeList++;
		}

		rigthNode->clearListRegistry();
		iterRegNodeList = rigthNodeReg.begin();
		while (iterRegNodeList != rigthNodeReg.end()){
			Registry* reg=(Registry*)*iterRegNodeList;
			rigthNode->addComponent(reg);
			iterRegNodeList++;
		}

		leftNodeReg.clear();
		centerNodeReg.clear();
		rigthNodeReg.clear();

		leftNode->clearBranch();
		vector<int>::iterator iterBranchNodeList = branchListLeftNode.begin();

		while (iterBranchNodeList != branchListLeftNode.end()){
			leftNode->addBranch(*iterBranchNodeList);
			iterBranchNodeList++;
		}
		centerNode->clearBranch();
		iterBranchNodeList = branchListCenterNode.begin();
		while (iterBranchNodeList != branchListCenterNode.end()){
			centerNode->addBranch(*iterBranchNodeList);
			iterBranchNodeList++;
		}

		rigthNode->clearBranch();
		iterBranchNodeList = branchListRightNode.begin();
		while (iterBranchNodeList != branchListRightNode.end()){
			rigthNode->addBranch(*iterBranchNodeList);
			iterBranchNodeList++;
		}

		branchListLeftNode.clear();
		branchListCenterNode.clear();
		branchListRightNode.clear();
		container->setLeftRegKey(NULL);
		container->setRightRegKey(NULL);
		return false;
	}
	else{

//		delete firstAuxToRemove;
//		delete secondAuxToRemove;

		if(count!=regList.size()){
			throw eLostReg("Se perdio al menos un registro");
		}

		// Escribe bloque izquierdo
		this->writeNode(leftNode, leftNode->getNumBlock());
		// Escribe bloque centro
		this->writeNode(centerNode, centerNode->getNumBlock());
		// Escribe bloque derecho
		this->writeNode(rigthNode, rigthNode->getNumBlock());

		return true;
	}

}
bool IndexBSharp::removeInternalNodeEmpty(InternalNode* currentNode,InternalNode* firstBrotherNode, InternalNode* secondBrotherNode,ContainerInsertion* container,Registry* regFirstFather, Registry* regSecondFather){

	unsigned int count=0;

		if (firstBrotherNode == NULL || secondBrotherNode == NULL)
				return false;
		// Crea contenedor de componentes para almacenar los registros de los bloques
		list<Registry*> regList;

		Registry* currentReg = *(currentNode->iteratorBegin());

		//Registro menor bloque primer hermano
		Registry* firstBrotherReg = (*(firstBrotherNode->iteratorBegin()));

		//Registro menor bloque segundo hermano
		Registry* secondBrotherReg = (*(secondBrotherNode->iteratorBegin()));

		InternalNode*  leftNode;
		InternalNode* centerNode;
		InternalNode* rigthNode;
		list<Registry*> leftNodeReg;
		list<Registry*> centerNodeReg;
		list<Registry*> rigthNodeReg;

	// Crea contenedor de ramas para insertar la rama nueva...
		vector<int> branchListFinal;
		vector<int> branchListLeftNode;
		vector<int> branchListCenterNode;
		vector<int> branchListRightNode;

		//Diferencio orden bloques
		if (currentReg->compareTo(firstBrotherReg) <0)
			if (currentReg->compareTo(secondBrotherReg) < 0){
				leftNode = currentNode;
				if (firstBrotherReg->compareTo(secondBrotherReg) < 0){
					centerNode = firstBrotherNode;
					rigthNode = secondBrotherNode;
				}else{
					centerNode = secondBrotherNode;
					rigthNode = firstBrotherNode;
				}
			}else{
				leftNode = secondBrotherNode;
				centerNode = currentNode;
				rigthNode = firstBrotherNode;
			}
		else
			if (currentReg->compareTo(secondBrotherReg) < 0){
				leftNode = firstBrotherNode;
				centerNode = currentNode;
				rigthNode = secondBrotherNode;
			}else{
				rigthNode = currentNode;
				if (firstBrotherReg->compareTo(secondBrotherReg) < 0){
					leftNode = firstBrotherNode;
					centerNode = secondBrotherNode;
				}else{
					leftNode = secondBrotherNode;
					centerNode = firstBrotherNode;
				}
			}

		leftNode->transferRegistry(leftNodeReg);
		centerNode->transferRegistry(centerNodeReg);
		rigthNode->transferRegistry(rigthNodeReg);

		this->listRegistry.clear();// TODO OJO ESTA LA AGREGAMOS NOSOTROS
		this->mergeComponentList(this->listRegistry,leftNodeReg,centerNodeReg);
		this->mergeComponentList(regList,this->listRegistry,rigthNodeReg);


	leftNode->transferBranchs(branchListLeftNode);
	centerNode->transferBranchs(branchListCenterNode);
	rigthNode->transferBranchs(branchListRightNode);

	this->branchList.clear();
	this->mergeBranchList(this->branchList,branchListLeftNode,branchListCenterNode);

	this->mergeBranchList(branchListFinal,this->branchList,branchListRightNode);

	regList.push_back(regFirstFather);
	regList.push_back(regSecondFather);
	regList.sort(comparatorRegistry);

	// Llena bloque izquierdo
	list<Registry*>::iterator iterRegFinalList = regList.begin();
	vector<int>::iterator iterBranchFinalList = branchListFinal.begin();
	leftNode->setAverageWeight(0);
	leftNode->addBranch(*iterBranchFinalList);
		iterBranchFinalList++;


	while (leftNode->isUnderflowRemove()){
			Registry* reg=(Registry*)*iterRegFinalList;
			leftNode->addComponent(reg);
			leftNode->addBranch(*iterBranchFinalList);
			iterRegFinalList++;
			iterBranchFinalList++;
			count++;
	}

	centerNode->addBranch(*iterBranchFinalList);
	iterBranchFinalList++;
	container->setRegMidleKey(*iterRegFinalList);
	iterRegFinalList++;
	count++;

	while (iterRegFinalList != regList.end()){
			if (centerNode->posibleToAgregateComponent(*iterRegFinalList)){
				Registry* reg=(Registry*)*iterRegFinalList;
				centerNode->addComponent(reg);
				centerNode->addBranch(*iterBranchFinalList);
			}
			else
				break;
			iterRegFinalList++;
			iterBranchFinalList++;
			count++;
	}
	//Valido que la nueva clave no sea mayor a las otras dos mas una rama que desapareceria
	int sizeOldMiddleKey = regFirstFather->getLongBytes() + regSecondFather->getLongBytes() + sizeof(int);
	int sizeNewMiddleKey = container->getRegMidleKey()->getLongBytes();
	if (iterRegFinalList != regList.end() || sizeOldMiddleKey < sizeNewMiddleKey){
		leftNode->clearListRegistry();
		list<Registry*>::iterator iterRegNodeList = leftNodeReg.begin();

		while (iterRegNodeList != leftNodeReg.end()){
			Registry* reg=(Registry*)*iterRegNodeList;
			leftNode->addComponent(reg);
			iterRegNodeList++;
		}
		centerNode->clearListRegistry();
		iterRegNodeList = centerNodeReg.begin();
		while (iterRegNodeList != centerNodeReg.end()){
			Registry* reg=(Registry*)*iterRegNodeList;
			centerNode->addComponent(reg);
			iterRegNodeList++;
		}

		rigthNode->clearListRegistry();
		iterRegNodeList = rigthNodeReg.begin();
		while (iterRegNodeList != rigthNodeReg.end()){
			Registry* reg=(Registry*)*iterRegNodeList;
			rigthNode->addComponent(reg);
			iterRegNodeList++;
		}

		leftNodeReg.clear();
		centerNodeReg.clear();
		rigthNodeReg.clear();

		leftNode->clearBranch();
		vector<int>::iterator iterBranchNodeList = branchListLeftNode.begin();

		while (iterBranchNodeList != branchListLeftNode.end()){
			leftNode->addBranch(*iterBranchNodeList);
			iterBranchNodeList++;
		}
		centerNode->clearBranch();
		iterBranchNodeList = branchListCenterNode.begin();
		while (iterBranchNodeList != branchListCenterNode.end()){
			centerNode->addBranch(*iterBranchNodeList);
			iterBranchNodeList++;
		}

		rigthNode->clearBranch();
		iterBranchNodeList = branchListRightNode.begin();
		while (iterBranchNodeList != branchListRightNode.end()){
			rigthNode->addBranch(*iterBranchNodeList);
			iterBranchNodeList++;
		}

		branchListLeftNode.clear();
		branchListCenterNode.clear();
		branchListRightNode.clear();

		container->setRegMidleKey(NULL);
		return false;
	}
	else{
		// Enlaza a los bloques
		centerNode->setNextBlock(rigthNode->getNextBlock());
		container->setRightBlock(rigthNode->getNumBlock());

		// Marco segundo bloque como borrado
		this->freeBlockController->writeFreeBlock(rigthNode->getNumBlock());
		// Escribo primer bloque
		this->writeNode(leftNode,leftNode->getNumBlock());
		// Escribo primer bloque
		this->writeNode(centerNode, centerNode->getNumBlock());
		regFirstFather = NULL;
		regSecondFather = NULL;
		return true;
	}
}
void IndexBSharp::searchBranchSisters(InternalNode* internalNode, Registry* reg, int *r1, int *r2) throw() {
	list<Registry*>::iterator currentReg= internalNode->iteratorBegin();
	list<Registry*>::iterator finalReg = internalNode->iteratorEnd();
	unsigned int sisterBranch = 0;
	unsigned int branchPos = 0;

	while (currentReg != finalReg) {
			if (reg->compareTo(*currentReg) < 0) {
				break;
			}
			++currentReg;
			++branchPos;
	}
	int sisterBranch2;
	// Si es el ultimo componente las ramas son las dos anteriores
	if (currentReg == finalReg) {
		sisterBranch = branchPos - 1;
		sisterBranch2 = branchPos - 2;
	}
	else{
		// Si es el primer componente las ramas son las dos posteriores
		if (branchPos ==  0){
			sisterBranch = branchPos + 1;
			sisterBranch2 = branchPos + 2;
		}else{
			// Si esta en el medio son las ramas anterior y posterior
			sisterBranch = branchPos - 1;
			sisterBranch2 = branchPos + 1;
		}
	}

	*r1 = internalNode->getBranch(sisterBranch);
	*r2 = internalNode->getBranch(sisterBranch2);
}
int IndexBSharp::removeInternalNode(InternalNode* internalNode, Registry* regKey,
		ContainerInsertion* insertionContainer, unsigned int firstBrother, unsigned int secondBrother, Registry* regFirstFather, Registry* regSecondFather) throw() {
	// Considero que no hay subflujo al remover en el bloque interno
	int answer = CORRECT_REMOVE;
	// Busco la rama por la cual borrar
	int branchToRemove = this->searchBranch(internalNode, regKey);
	int branchOne,branchTwo;
	this->searchBranchSisters(internalNode,regKey, &branchOne,&branchTwo);
	bool isLastReg= false;


	//Obtengo elemento actual del bloque por el cual bajo a la rama siguiente
	list<Registry*>::iterator currentReg = internalNode->iteratorBegin();
	list<Registry*>::iterator lastReg = internalNode->iteratorEnd();
	while (currentReg != lastReg) {
		if (regKey->compareTo(*currentReg) < 0) {
			break;
		}
		currentReg++;
	}


	if (currentReg ==  lastReg)
		isLastReg=true;

	if (currentReg !=  internalNode->iteratorBegin())
			currentReg--;


	// Leo el bloque por el cual borrar
	Node* nodeRemoveBranch= this->readNode(branchToRemove);

	if (nodeRemoveBranch != NULL) {
		// Considero que no hay subflujo al remover en el bloque hijo
		int childAnswer = CORRECT_REMOVE;

		Registry* regNextFirstFather;
		Registry* regNextSecondFather;
		list<Registry*>::iterator currentRegAux = currentReg;
		if (isLastReg){
			regNextSecondFather = *currentRegAux;
			regNextFirstFather =  *(--currentRegAux);
		}else{
			regNextFirstFather = *currentRegAux;
			regNextSecondFather = *(++currentRegAux);
		}

		if (nodeRemoveBranch->isLeaf()) {
			LeafNode* leafNodeRemove = (LeafNode*) nodeRemoveBranch;
			// Remuevo en el bloque externo hijo
			childAnswer = this->removeLeafNode(leafNodeRemove, regKey, insertionContainer, branchOne, branchTwo, regNextFirstFather, regNextSecondFather);
		} else {

			InternalNode* internalNodeRemove = (InternalNode*)nodeRemoveBranch;

			// Remuevo en el bloque interno hijo
			childAnswer = this->removeInternalNode(internalNodeRemove, regKey, insertionContainer, branchOne, branchTwo,regNextFirstFather, regNextSecondFather);
		}

		if (childAnswer == BALANCE) {
			if (regKey->compareTo(*currentReg) == 0){
				if (insertionContainer->getInternalKey()!=NULL)
					delete insertionContainer->getInternalKey();
				insertionContainer->setInternalKey(NULL);
			}

			Registry* biggerRegToReplace;
			Registry* smallerRegToReplace;

			vector<int>::iterator finalBranch = internalNode->lastBranch();
			list<Registry*>::iterator currentRegAux = currentReg;

			if (isLastReg){

				biggerRegToReplace =   *currentRegAux;
				smallerRegToReplace =  *(--currentRegAux);
			}else{
				smallerRegToReplace =   *currentRegAux;
				biggerRegToReplace =   *(++currentRegAux);

			}
			if(DEBUG){
				std::cout << "(remover bloq interno)Registro Menor a Reemplazar: ";
				this->printRegistry(smallerRegToReplace, std::cout);
				std::cout<< std::endl;
				std::cout << "Registro Menor a subir: ";
				this->printRegistry(insertionContainer->getLeftRegKey(), std::cout);
				std::cout<< std::endl;

				std::cout << "(remover bloq interno)Registro Mayor a Reemplazar: ";
				this->printRegistry(biggerRegToReplace, std::cout);
				std::cout<< std::endl;
				std::cout << "Registro Mayor a subir: ";
				this->printRegistry(insertionContainer->getRightRegKey(), std::cout);
				std::cout<< std::endl;
			}
			internalNode->replaceRegistry(smallerRegToReplace,insertionContainer->getLeftRegKey());
			internalNode->replaceRegistry(biggerRegToReplace, insertionContainer->getRightRegKey());

			if (nodeRemoveBranch->isLeaf()){
				delete smallerRegToReplace;
				delete biggerRegToReplace;
			}
			// Escribo bloque
			this->writeNode(internalNode, internalNode->getNumBlock());
		}
		// Verifico si hubo sobrelujo al insertar en el bloque hijo
		if (childAnswer == UNDERFLOW) {
			Registry* current = (Registry*)*currentReg;
			if (regKey->compareTo(current) == 0){
				if (insertionContainer->getInternalKey()!=NULL)
					delete insertionContainer->getInternalKey();
				insertionContainer->setInternalKey(NULL);
			}


			// Dejo actual componente en una posicion valida
//			if (isLastReg)
//				currentReg--;

			this->updateFusion(internalNode, insertionContainer);

			if (internalNode->isUnderflowRemove()){
				// Leo bloques hermanos
				InternalNode* firstBrotherNode;
				InternalNode* secondBrotherNode;
				if (firstBrother != 0 && secondBrother != 0){
					firstBrotherNode = (InternalNode*)this->readNode(firstBrother);
					secondBrotherNode = (InternalNode*)this->readNode(secondBrother);
				}else{
					firstBrotherNode = NULL;
					secondBrotherNode = NULL;
				}
				// Intento fusionar
				if (this->removeInternalNodeEmpty(internalNode,firstBrotherNode,secondBrotherNode, insertionContainer,regFirstFather,regSecondFather)){
					answer = UNDERFLOW;
				}
				else{
					// Si no se puede fusionar se balancea
					bool response = false;
					if (firstBrother != 0 && secondBrother != 0){
						response = this->balanceInternalNodeRemove(internalNode,firstBrotherNode,secondBrotherNode,insertionContainer,regFirstFather,regSecondFather);
					}
					if (response || firstBrotherNode == NULL)
						answer = BALANCE;

				}
//				if (firstBrother != 0 && secondBrother != 0){
//					delete firstBrotherNode;
//					delete secondBrotherNode;
//				}
			}
		}
	}
	if (answer == CORRECT_REMOVE && insertionContainer->getInternalKey() != NULL && !isLastReg){
		list<Registry*>::iterator currentRegAux = currentReg;
		Registry* regToRemove = (Registry*)*currentRegAux;
		if (insertionContainer->getInternalKey()->compareTo(regToRemove) == 0){
			if (regToRemove->getLongBytes() >= insertionContainer->getInternalKey()->getLongBytes()){
				if(DEBUG){
					std::cout << "Registro Interno Eliminado: ";
					this->printRegistry(regToRemove, std::cout);
					std::cout<< std::endl;
					std::cout << "Registro Interno Nuevo: ";
					this->printRegistry(insertionContainer->getInternalKey(), std::cout);
					std::cout<< std::endl;
				}
				internalNode->replaceRegistry(regToRemove, insertionContainer->getInternalKey());
				// Escribo bloque
				this->writeNode(internalNode,internalNode->getNumBlock());

				delete regToRemove;
			}
			insertionContainer->setInternalKey(NULL);

		}
	}
	delete nodeRemoveBranch;
	return answer;
}

int IndexBSharp::removeLeafNode(LeafNode* leafNode, Registry* regKey,
		ContainerInsertion* insertionContainer, unsigned int firstBrother, unsigned int secondBrother,
		Registry* regFirstFather, Registry* regSecondFather) throw() {

	// Consideramos que no hay subflujo
	int answer = CORRECT_REMOVE;
	    if(DATA==1){
			if(this->typeElement==TYPE_REG_PRIMARY||this->typeElement==TYPE_REG_CLASSIFICATION||this->typeElement==TYPE_REG_INVERTED_INDEX){
				answer= leafNode->deleteBlockData(regKey,this->containerInsertDataBlock);
			}
		    if(CORRECT_REMOVE==answer&&(this->typeElement==TYPE_REG_PRIMARY||this->typeElement==TYPE_REG_CLASSIFICATION)){
		    	delete regKey;
				return answer;
			}
		    if(BLOCK_EMPTY==answer&&this->typeElement==TYPE_REG_PRIMARY){
		    	Registry* regfind=leafNode->searchNumberBlockMail(regKey);
		    	regKey=regfind;
		    	answer = CORRECT_REMOVE;
		   	}
		    if(BLOCK_EMPTY==answer&&this->typeElement==TYPE_REG_CLASSIFICATION){
		    	answer = CORRECT_REMOVE;
		    }
		}




	list<Registry*>::iterator currentReg = leafNode->iteratorBegin();
	list<Registry*>::iterator lastReg = leafNode->iteratorEnd();
	bool isFirst = true;
	while (currentReg != lastReg) {
		Registry* iterReg  = *currentReg;
		if (iterReg->compareTo(regKey) == 0) {
			leafNode->removeReg(iterReg);
			break;
		}
		isFirst = false;
		++currentReg;
	}
	if (isFirst && (leafNode->getNumElements() > 0))
		insertionContainer->setInternalKey(this->extractKey((*leafNode->iteratorBegin())));

	if (leafNode->isUnderflowRemove()){
		// Leo bloques hermanos
		LeafNode* firstBrotherNode;
		LeafNode* secondBrotherNode;
		if (firstBrother != 0 && secondBrother != 0){
			firstBrotherNode = (LeafNode*) this->readNode(firstBrother);
			secondBrotherNode = (LeafNode*) this->readNode(secondBrother);
		}else{
			firstBrotherNode = NULL;
			secondBrotherNode = NULL;
		}
		// Intento fusionar
		if (this->removeLeafNodeEmpty(leafNode,firstBrotherNode,secondBrotherNode, insertionContainer, regFirstFather, regSecondFather))
			answer = UNDERFLOW;
		else{
			// Si no se puede fusionar se balancea
			bool response = false;
			if (firstBrother != 0 && secondBrother != 0)// TODO VER
				response = this->balanceLeafNodeRemove(leafNode,firstBrotherNode,secondBrotherNode,insertionContainer, regFirstFather, regSecondFather);
			if (response || firstBrotherNode == NULL)
				answer = BALANCE;
		}
		delete firstBrotherNode;
		delete secondBrotherNode;
	}

	if (answer == CORRECT_REMOVE){
		// Actualizo espacio en disco
		this->writeNode(leafNode, leafNode->getNumBlock());
	}

	return answer;

}

void IndexBSharp::updateFusion(InternalNode* fatherNode, ContainerInsertion* insertionContainer) throw() {
	vector<int>::iterator currentBranch = fatherNode->firstBranch();
	vector<int>::iterator lastBranch = fatherNode->lastBranch();
	int removeBranchPos = 0;

	while (currentBranch != lastBranch) {
		if (*currentBranch == (int)insertionContainer->getRightBlock()) {
			fatherNode->removeBranch(currentBranch);
			break;
		}
		++removeBranchPos;
		++currentBranch;
	}

	list<Registry*>::iterator currentKey = fatherNode->iteratorBegin();
	list<Registry*>::iterator previousKey = fatherNode->iteratorBegin();
	for (int countKeys = 0; countKeys < removeBranchPos - 1; ++countKeys) {
		previousKey = currentKey;
		++currentKey;
	}
	if(DEBUG){
		std::cout << "(fusion)Componente eliminado: ";
		this->printRegistry((Registry*)*currentKey, std::cout);
		std::cout<< std::endl;
	}
	Registry* iterReg  = *currentKey;
	fatherNode->removeReg(iterReg);

	Registry* regToReplace =   *previousKey;
	if(DEBUG){
		std::cout << "(fusion)Registro a Reemplazar: ";
		this->printRegistry(regToReplace, std::cout);
		std::cout<< std::endl;
		std::cout << "Registro a Poner: ";
		this->printRegistry(insertionContainer->getRegMidleKey(), std::cout);
		std::cout<< std::endl;
	}
	fatherNode->replaceRegistry(regToReplace, insertionContainer->getRegMidleKey());
	// Escribo bloque padre en disco...
	this->writeNode(fatherNode, fatherNode->getNumBlock());

	delete regToReplace;
}
void IndexBSharp::manageRootUnderflow() throw() {
	if (!this->rootNode->isLeaf()) {
		InternalNode* internalRootNode = (InternalNode*)this->rootNode;
		if (internalRootNode->getNumElements() == 1){
			if (internalRootNode->getLevel() == 1){
				unsigned int count=0;
				LeafNode* newRoot = new LeafNode(this->typeElement, 2*this->sizeBlock, 0, 0);

				vector<int>::iterator currentBranch = internalRootNode->firstBranch();
				LeafNode* firstChildNode = (LeafNode*)this->readNode(*currentBranch);
				LeafNode* secondChildNode = (LeafNode*)this->readNode(*(++currentBranch));

				list<Registry*> leftNodeRegs;
				list<Registry*> rightNodeRegs;

				firstChildNode->transferRegistry(leftNodeRegs);
				secondChildNode->transferRegistry(rightNodeRegs);

				// Crea contenedor de componentes para insertar ordenado el registro...
				list<Registry*> regList;


				this->mergeComponentList(regList,leftNodeRegs,rightNodeRegs);


				list<Registry*>::iterator finalListReg = regList.begin();
				while (finalListReg != regList.end()){
					if (newRoot->posibleToAgregateComponent(*finalListReg))
						newRoot->addComponent(*finalListReg);
					else
						break;
					finalListReg++;
					count++;
				}

				if(count!=regList.size()){
					throw eLostReg("Se perdio al menos un registro");
				}
				delete this->rootNode;
				this->rootNode = newRoot;

				this->freeBlockController->writeFreeBlock(firstChildNode->getNumBlock());
				this->freeBlockController->writeFreeBlock(secondChildNode->getNumBlock());

				delete firstChildNode;
				delete secondChildNode;

				this->writeNode(this->rootNode, 0);

				////////////////
			}
			else{
				unsigned int count=0;
				InternalNode* newRoot = new InternalNode(this->typeElement, 2*this->sizeBlock, 0, this->rootNode->getLevel() - 1);

				vector<int>::iterator currentBranch = internalRootNode->firstBranch();
				InternalNode* firstChildNode = (InternalNode*) this->readNode(*currentBranch);
				InternalNode* secondChildNode = (InternalNode*) this->readNode(*(++currentBranch));

				list<Registry*> leftNodeRegs;
				list<Registry*> rightNodeRegs;
				vector<int> leftNodeBranchs;
				vector<int> rightNodeBranchs;


				firstChildNode->transferRegistry(leftNodeRegs);
				secondChildNode->transferRegistry(rightNodeRegs);
				firstChildNode->transferBranchs(leftNodeBranchs);
				secondChildNode->transferBranchs(rightNodeBranchs);

				// Crea contenedor de componentes para insertar ordenado el registro...
				list<Registry*> regList;
				vector<int> branchList;

				Registry* fatherReg = (*(internalRootNode->iteratorBegin()));

				this->mergeComponentList(regList,leftNodeRegs,rightNodeRegs);

				regList.push_back(this->extractKey(fatherReg));
				regList.sort(comparatorRegistry);

				this->mergeBranchList(branchList,leftNodeBranchs,rightNodeBranchs);

				list<Registry*>::iterator finalListReg = regList.begin();
				vector<int>::iterator finalListBranch = branchList.begin();
				newRoot->addBranch(*finalListBranch);
				finalListBranch++;
				while (finalListReg != regList.end()){
					if (newRoot->posibleToAgregateComponent(*finalListReg)){
						newRoot->addComponent(*finalListReg);
						newRoot->addBranch(*finalListBranch);
					}
					else
						break;
					finalListReg++;
					finalListBranch++;
					count++;
				}

				if(count!=regList.size()){
					throw eLostReg("Se perdio al menos un registro");
				}
				delete this->rootNode;
				this->rootNode = newRoot;

				this->freeBlockController->writeFreeBlock(firstChildNode->getNumBlock());
				this->freeBlockController->writeFreeBlock(secondChildNode->getNumBlock());
				delete firstChildNode;
				delete secondChildNode;

				this->writeNode(this->rootNode, 0);
			}

			///////////////
		}
	}
}
void IndexBSharp::deleteRegistry(Registry* reg) throw() {
	ContainerInsertion insertionContainer;
	int answer = CORRECT_REMOVE;
	Registry* aux = NULL;
	if (this->rootNode->isLeaf()) {
		LeafNode* leafNode = (LeafNode*)this->rootNode;
		answer = this->removeLeafNode(leafNode, reg, &insertionContainer, 0, 0, aux, aux);
	} else {
		InternalNode* internalNode = (InternalNode*)this->rootNode;
		answer = this->removeInternalNode(internalNode, reg, &insertionContainer, 0, 0, aux, aux);
	}


	if (insertionContainer.getInternalKey()!=NULL)
		delete insertionContainer.getInternalKey();

	if (answer == BALANCE) {
		this->manageRootUnderflow();
	}

	delete reg;
}
