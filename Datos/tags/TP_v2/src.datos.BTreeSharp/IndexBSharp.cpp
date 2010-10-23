/*
 * IndexBSharp.cpp
 *
 *  Created on: 05/09/2010
 *      Author: oscar
 */

#include "IndexBSharp.h"
#include "../src.datos.exception/eNotSpace.h"
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
	this->readBlockRoot();
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

	if (answer == OVERFLOW) {
		if(this->rootNode->isLeaf())
			this->splitLeafRoot(containerInsertion,registry);
		else
			this->splitInternalRoot(containerInsertion);
	}

}
//}

void IndexBSharp::deleteRegistry(Registry* registry) throw () {

}
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
	this->writeBlockRoot();
}
void IndexBSharp::readBlockRoot() throw(){
	this->bufferRoot->clear();
	if(this->binaryFile->read(this->bufferRoot->getData(),this->bufferRoot->getMaxBytes(),0)){
		this->rootNode = readNodeBytes(this->bufferRoot);
	} else {
		this->createBlockRoot();
	}
}
void IndexBSharp::writeBlockRoot() throw(){
	this->bufferRoot->clear();
	this->rootNode->pack(this->bufferRoot);
	this->binaryFile->write(this->bufferRoot->getData(),this->bufferRoot->getMaxBytes(),0);
}
void IndexBSharp::writeBlock(Node* node, int numBlock) throw () {
	this->buffer->clear();
	node->pack(this->buffer);
	this->binaryFile->write(this->buffer->getData(),this->buffer->getMaxBytes(),numBlock*this->buffer->getMaxBytes());
	//	cout<<"escribe bloque "<< node->getNumBlock()<<endl;
	//			buffer->init();
	//			int var2=this->sizeBlock/4;
	//				for (int var = 0;var<= var2; ++var) {
	//				       int num;
	//				       buffer->unPackField(&num,sizeof(num));
	//				       cout<<" | "<<num;
	//					}
	//					cout<<"fin del bloque "<<endl;
}
Node* IndexBSharp::readNode(unsigned int numBlock) throw () {
	this->buffer->clear();
	if (this->binaryFile->read(buffer->getData(),this->buffer->getMaxBytes(),this->buffer->getMaxBytes()* numBlock)) {
		Node* node = readNodeBytes(buffer);
		//		cout<<"lee bloque "<< node->getNumBlock()<<endl;
		//		buffer->init();
		//		int var2=this->sizeBlock/4;
		//			for (int var = 0;var<= var2; ++var) {
		//			       int num;
		//			       buffer->unPackField(&num,sizeof(num));
		//			       cout<<" | "<<num;
		//				}
		//				cout<<"fin del bloque "<<endl;

		return node;
	} else {
		return NULL;
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
	this->writeBlockRoot();

	this->writeBlock(newLeftNode, newLeftNode->getNumBlock());
	this->writeBlock(newRightNode, newRightNode->getNumBlock());
	this->writeBlock(newCenterNode, newCenterNode->getNumBlock());
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
	this->writeBlockRoot();

	this->writeBlock(newLeftNode, newLeftNode->getNumBlock());
	this->writeBlock(newRightNode, newRightNode->getNumBlock());
	this->writeBlock(newCenterNode, newCenterNode->getNumBlock());

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
			answer = OVERFLOW;
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
		this->writeBlock(leftNode, leftNode->getNumBlock());
		this->writeBlock(rightNode, rightNode->getNumBlock());
		return true;
	}

}
void IndexBSharp::insertLeafNodeNotFull(LeafNode* leafNode, Registry* registry) throw () {

	// Inserta el registro en el bloque externo
	leafNode->addReg(registry);
	leafNode->sortListRegistry();

	if (leafNode->getNumBlock() == 0)
		this->writeBlockRoot();

	else
		// Escribe bloque en disco
		this->writeBlock(leafNode, leafNode->getNumBlock());

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

	this->writeBlock(leftNode, leftNode->getNumBlock());
	this->writeBlock(rightNode, rightNode->getNumBlock());
	this->writeBlock(newLeafNode, newLeafNode->getNumBlock());

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
		this->writeBlock(leftNode, leftNode->getNumBlock());
		// Escribe bloque derecho
		this->writeBlock(rightNode, rightNode->getNumBlock());
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
			this->writeBlock(internalNode,internalNode->getNumBlock());
			if (fatherRegistry != NULL)
				delete fatherRegistry;

		}

		// Verifico si hubo sobrelujo al insertar en el bloque hijo
		if (childAnswer == OVERFLOW) {
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
					answer = OVERFLOW;

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
	if (internalNode->getNumBlock() == 0)
		this->writeBlockRoot();
	else
		this->writeBlock(internalNode, internalNode->getNumBlock());
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
	this->writeBlock(leftNode,leftNode->getNumBlock());
	// Escribe bloque a dividir en disco
	this->writeBlock(rightNode,rightNode->getNumBlock());
	// Escribe bloque nuevo
	this->writeBlock(newInternalNode,newInternalNode->getNumBlock());

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
	while (actualComponent != endComponent) {
		Registry* actual = *actualComponent;
		if(DEBUG)actual->print(cout);
		if(DEBUG)registry->print(cout);
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