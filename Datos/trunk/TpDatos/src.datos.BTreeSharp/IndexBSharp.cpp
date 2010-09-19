/*
 * IndexBSharp.cpp
 *
 *  Created on: 05/09/2010
 *      Author: oscar
 */

#include "IndexBSharp.h"
bool comparatorRegistry( Registry* reg1, Registry* reg2) {
	int compare= reg1->compareTo(reg2);
		return (compare< 0);
}
IndexBSharp::IndexBSharp(const std::string& nameFile,unsigned int sizeBlock,int typeElement){
	this->sizeBlock=sizeBlock;
	this->typeElement=typeElement;
	this->binaryFile= new BinaryFile();
	if(!this->binaryFile->isCreated(nameFile))
		this->binaryFile->create(nameFile);
	else
		this->binaryFile->open(nameFile);
	this->buffer= new Buffer(sizeBlock);
	this->freeBlockController = new FreeBlockController(nameFile+"free");
	this->readBlockRoot();
}

IndexBSharp::~IndexBSharp() {
	this->binaryFile->close();
	delete this->buffer;
	delete this->freeBlockController;
	delete this->binaryFile;
}

void IndexBSharp::addRegistry(Registry* registry) throw(){
//	if(this->searchRegistry(registry) == NULL){
		ContainerInsertion* containerInsertion=new ContainerInsertion();
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
		delete containerInsertion;
	}
//}

void IndexBSharp::deleteRegistry(Registry* registry) throw(){

}
Registry* IndexBSharp::searchRegistry(Registry* registry) throw(){
	if (this->rootNode->isLeaf()){
		LeafNode* leafNode = static_cast<LeafNode*>(this->rootNode);
		return this->searchLeafNode(leafNode, registry);
	} else {
		InternalNode* internalNode  = static_cast<InternalNode*>(this->rootNode);
		return this->searchInternalNode(internalNode, registry);
	}
}
void IndexBSharp::print(std::ostream& streamSalida) throw(){
	this->printRecursive(this->rootNode,streamSalida,0);
}
void IndexBSharp::createBlockRoot() throw(){
	// Instancia un nuevo bloque raiz
	this->rootNode = new LeafNode(this->typeElement,2*this->sizeBlock, 0,0);
	// Ecscribe bloque raiz
	this->writeBlockRoot();
}
void IndexBSharp::readBlockRoot() throw(){
	this->rootNode= this->readNode(0);
	if (this->rootNode== NULL) {
		this->createBlockRoot();
	}
}
void IndexBSharp::writeBlockRoot() throw(){
		Buffer* bufferRoot=new Buffer(this->sizeBlock*2);
		this->rootNode->pack(bufferRoot);
		this->binaryFile->write(bufferRoot->getData(),bufferRoot->getMaxBytes(),0);
}
void IndexBSharp::writeBlock(Node* node,int numBlock) throw(){
	this->buffer->clear();
	node->pack(this->buffer);
	this->binaryFile->write(this->buffer->getData(),this->buffer->getMaxBytes(),numBlock*this->sizeBlock);
}
Node* IndexBSharp::readNode(unsigned int numBlock) throw() {
	this->buffer->clear();
	if(this->binaryFile->read(buffer->getData(),this->sizeBlock,this->sizeBlock*numBlock)){
		Node* node = readNodeBytes(buffer);
//		cout<<"lee bloque "<< node->getNumBlock()<<endl;
//		buffer->init();
//		int var2=this->sizeBlock/4;
//		if(node->getNumBlock()==9){
//			for (int var = 0;var<= var2; ++var) {
//			       int num;
//			       buffer->unPackField(&num,sizeof(num));
//			       cout<<" | "<<num;
//				}
//				cout<<"fin del bloque "<<endl;
//			}
		return node;
	}else {
		return NULL;
	}
}
Node* IndexBSharp::readNodeBytes(Buffer* buffer) throw(){
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
Node* IndexBSharp::readInternalNodeBytes(Buffer* buffer) throw(){
	InternalNode* internalNode= new InternalNode(this->sizeBlock,this->typeElement);
	internalNode->unPack(buffer);
	return internalNode;
}
Node* IndexBSharp::readLeafNodeBytes(Buffer* buffer) throw(){
	LeafNode* leafNode= new LeafNode(this->typeElement,this->sizeBlock);
	leafNode->unPack(buffer);
	return leafNode;
}

void IndexBSharp::splitLeafRoot(ContainerInsertion* container, Registry* registry) throw(){

	// Busca espacio libre para la nueva raiz
	unsigned int positionFree = this->freeBlockController->searchSizeBusy();
	LeafNode* newLeftNode = new LeafNode(this->typeElement,this->sizeBlock,positionFree,0);

	positionFree = this->freeBlockController->searchSizeBusy();
	LeafNode* newCenterNode = new LeafNode(this->typeElement,this->sizeBlock,positionFree+1,0);


	positionFree = this->freeBlockController->searchSizeBusy();
	LeafNode* newRightNode = new LeafNode(this->typeElement,this->sizeBlock,positionFree+2,0);

	this->listRegistry.clear();
	this->rootNode->transferRegistry(this->listRegistry);

	this->listRegistry.push_back(registry);
	this->listRegistry.sort(comparatorRegistry);

	list<Registry*>::iterator current = this->listRegistry.begin();

	while(newLeftNode->posibleToAgregateComponent(*current)){
		newLeftNode->addComponent(*current);
		current++;
	}

	container->setLeftRegKey(this->extractKey(*current));


	while(newCenterNode->posibleToAgregateComponent(*current)){
			newCenterNode->addComponent(*current);
			current++;
		}

	container->setRightRegKey(this->extractKey(*current));

	while(current != this->listRegistry.end()){
		if(newRightNode->posibleToAgregateComponent(*current))
			newRightNode->addComponent(*current);
		else
			break;
		current++;
	}
	newLeftNode->setNextBlock(newCenterNode->getNumBlock());
	newCenterNode->setNextBlock(newRightNode->getNumBlock());

	InternalNode* newRoot = new InternalNode(this->typeElement,2*this->sizeBlock,0, this->rootNode->getLevel() + 1);
	newRoot->addBranch(newLeftNode->getNumBlock());
	newRoot->addBranch(newCenterNode->getNumBlock());
	newRoot->addBranch(newRightNode->getNextBlock());

	newRoot->addComponent(container->getLeftRegKey());
	newRoot->addComponent(container->getRightRegKey());
	// Escribe el bloque raiz
	this->rootNode = newRoot;
	this->writeBlockRoot();


	this->writeBlock(newLeftNode,newLeftNode->getNumBlock());
	this->writeBlock(newRightNode,newRightNode->getNumBlock() );
	this->writeBlock(newCenterNode, newCenterNode->getNumBlock());


}

void IndexBSharp::splitInternalRoot(ContainerInsertion* container) throw(){

	// Busca espacio libre para la nueva raiz
	unsigned int positionFree = this->freeBlockController->searchSizeBusy();
	InternalNode* newLeftNode = new InternalNode(this->typeElement,this->sizeBlock,positionFree,this->rootNode->getLevel());

	positionFree = this->freeBlockController->searchSizeBusy();
	InternalNode* newCenterNode = new InternalNode(this->typeElement,this->sizeBlock,positionFree+1,this->rootNode->getLevel());


	positionFree = this->freeBlockController->searchSizeBusy();
	InternalNode* newRightNode = new InternalNode(this->typeElement,this->sizeBlock,positionFree+2,this->rootNode->getLevel());

	this->listRegistry.clear();
	this->branchList.clear();
	this->rootNode->transferRegistry(this->listRegistry);
	((InternalNode*)this->rootNode)->transferBranchs(this->branchList);

	unsigned int positionInsert = searchPositionInsertInternalNode(container->getRightRegKey(),this->listRegistry.begin(),this->listRegistry.end());
	this->listRegistry.push_back(container->getRightRegKey());
	this->listRegistry.sort(comparatorRegistry);


	//adelanto el puntero
	std::vector<int>::iterator itListBranchs = this->branchList.begin();
	this->advanceVectorPointer(itListBranchs ,positionInsert + 1);
	// Inserta la rama
	branchList.insert(itListBranchs, container->getRightBlock());

	list<Registry*>::iterator itListRegistry = this->listRegistry.begin();
	itListBranchs = this->branchList.begin();
	newLeftNode->addBranch(*itListBranchs);
	itListBranchs++;


	while(newLeftNode->posibleToAgregateComponent(*itListRegistry)){
		newLeftNode->addBranch(*itListBranchs);
		newLeftNode->addComponent(*itListRegistry);
		itListRegistry++;
		itListBranchs++;
	}

	newCenterNode->addBranch(*itListBranchs);
	itListBranchs++;

	container->setLeftRegKey(this->extractKey(*itListRegistry));
	itListRegistry++;

	while(newCenterNode->posibleToAgregateComponent(*itListRegistry)){
		newCenterNode->addBranch(*itListBranchs);
		newCenterNode->addComponent(*itListRegistry);
		itListRegistry++;
		itListBranchs++;
		}


	newRightNode->addBranch(*itListBranchs);
	itListBranchs++;
	container->setRightRegKey(this->extractKey(*itListRegistry));
	itListRegistry++;

	while(itListRegistry != this->listRegistry.end()){
		if(newRightNode->posibleToAgregateComponent(*itListRegistry)){
			newRightNode->addBranch(*itListBranchs);
			newRightNode->addComponent(*itListRegistry);
		}
		else
			break;
		itListBranchs++;
		itListRegistry++;
	}


	InternalNode* newRoot = new InternalNode(this->typeElement,2*this->sizeBlock,0, this->rootNode->getLevel() + 1);
	newRoot->addBranch(newLeftNode->getNumBlock());
	newRoot->addBranch(newCenterNode->getNumBlock());
	newRoot->addBranch(newRightNode->getNextBlock());

	newRoot->addComponent(container->getLeftRegKey());
	newRoot->addComponent(container->getRightRegKey());
	// Escribe el bloque raiz
	this->rootNode = newRoot;
	this->writeBlockRoot();


	this->writeBlock(newLeftNode,newLeftNode->getNumBlock());
	this->writeBlock(newRightNode,newRightNode->getNumBlock() );
	this->writeBlock(newCenterNode, newCenterNode->getNumBlock());


}
int IndexBSharp::insertLeafNode(LeafNode* leafNode,Registry* registry,ContainerInsertion* container, unsigned int brotherNode) throw(){
	// Consideramos que no hay sobreflujo
	bool answer = INSERTION_OK;
	// Verifica que el bloque externo puede agregar el registro
	if (leafNode->posibleToAgregateComponent(registry)) {
		// Agrega el registro en el bloque externo no lleno
		this->insertLeafNodeNotFull(leafNode,registry);
	} else {
		LeafNode* sisterBranchNode;
		if(brotherNode != 0)
			sisterBranchNode = (LeafNode*)this->readNode(brotherNode);
		else
			sisterBranchNode = NULL;

		if(this->balanceLeafNode(registry,leafNode,sisterBranchNode,container)){
			answer = BALANCE;
		}else{
			answer = OVERFLOW;
			if(sisterBranchNode != NULL){
				this->insertLeafNodeFull(leafNode,sisterBranchNode,registry,container);
			}
		}
	}
	return answer;
}

void IndexBSharp::mergeComponentList(list<Registry*> &listRegistry, list<Registry*> &listLeftNode,list<Registry*> &listRightNode){
	list<Registry*>::iterator itListRegistry = listLeftNode.begin();
	while(itListRegistry != listLeftNode.end()){
		listRegistry.push_back(*itListRegistry);
		itListRegistry++;
	}
	itListRegistry = listRightNode.begin();
		while(itListRegistry != listRightNode.end()){
			listRegistry.push_back(*itListRegistry);
			itListRegistry++;
		}
}
void IndexBSharp::mergeBranchList(std::vector<int> &listBranch,std::vector<int> &listLeftNode,std::vector<int> &listRightNode){
	std::vector<int>::iterator itListBranchs = listLeftNode.begin();
	while(itListBranchs != listLeftNode.end()){
			listBranch.push_back(*itListBranchs);
			itListBranchs++;
		}
	itListBranchs = listRightNode.begin();
	while(itListBranchs != listRightNode.end()){
		listBranch.push_back(*itListBranchs);
		itListBranchs++;
	}

}
bool IndexBSharp::balanceLeafNode(Registry* reg, LeafNode* actualNode, LeafNode* brotherNode,ContainerInsertion* container) throw(){
	if(brotherNode == NULL)
		return false;

	Registry* actualReg = *(actualNode->iteratorBegin());
	Registry* brotherReg = *(brotherNode->iteratorBegin());

	LeafNode* leftNode;
	LeafNode* rightNode;
	list<Registry*> listRegLeftNode;
	list<Registry*> listRegRightNode;

	if(actualReg->compareTo(brotherReg) < 0){
		actualNode->transferRegistry(listRegLeftNode);
		brotherNode->transferRegistry(listRegRightNode);
		leftNode = actualNode;
		rightNode = brotherNode;
	}else{
		brotherNode->transferRegistry(listRegLeftNode);
		actualNode->transferRegistry(listRegRightNode);
		leftNode = brotherNode;
		rightNode = actualNode;
	}

	this->mergeComponentList(this->listRegistry,listRegLeftNode,listRegRightNode);

	this->listRegistry.push_back(reg);
	this->listRegistry.sort(comparatorRegistry);

	list<Registry*>::iterator itListRegistry = this->listRegistry.begin();
	while(leftNode->posibleToAgregateComponent(*itListRegistry)){
		leftNode->addComponent(*itListRegistry);
		itListRegistry++;
	}
	Registry* copy = container->getRegMidleKey();
	container->setRegMidleKey(this->extractKey(*itListRegistry));

	while(itListRegistry != this->listRegistry.end()){
		if(rightNode->posibleToAgregateComponent(*itListRegistry))
			rightNode->addComponent(*itListRegistry);
		else
			break;
		itListRegistry++;
	}

	if(itListRegistry != this->listRegistry.end()){
		leftNode->clearListRegistry();
		list<Registry*>::iterator itListReg = listRegLeftNode.begin();
		while(itListReg != listRegLeftNode.end()){
			leftNode->addComponent(*itListReg);
			itListReg++;
		}
		rightNode->clearListRegistry();
		itListReg = listRegRightNode.begin();
		while(itListReg != listRegRightNode.end()){
			rightNode->addComponent(*itListReg);
			itListReg++;
		}
		container->setRegMidleKey(copy);
		listRegLeftNode.clear();
		listRegRightNode.clear();
		return false;
	}
	else{
		this->writeBlock(leftNode,leftNode->getNumBlock());
		this->writeBlock(rightNode, rightNode->getNumBlock());
		return true;
	}

}
void IndexBSharp::insertLeafNodeNotFull(LeafNode* leafNode,Registry* registry) throw(){

	// Inserta el registro en el bloque externo
	leafNode->addReg(registry);
	leafNode->sortListRegistry();
//	leafNode->print(cout);
//	cout<<"termoni leaf "<<endl;
	// Actualiza espacio ocupado para el bloque
	this->freeBlockController->writeSizeBusy(leafNode->getNumBlock(), leafNode->getOcupedLong());

	if(leafNode->getNumBlock() == 0)
		this->writeBlockRoot();

	else// Escribe bloque en disco
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

void IndexBSharp::insertLeafNodeFull(LeafNode* leafNode,LeafNode* brotherNode,Registry* registry,ContainerInsertion* container) throw(){

	// Busco numero de bloque libre
	unsigned int numBlockFree = this->freeBlockController->searchSizeBusy();
	// Creo nuevo bloque externo para dividir bloque..
	LeafNode* newLeafNode = new LeafNode(this->typeElement,this->sizeBlock, numBlockFree,0);

	listRegistry.clear();

	LeafNode* leftNode;
	LeafNode* rightNode;
	list<Registry*> listRegLeftNode;
	list<Registry*> listRegRightNode;

	Registry* actualReg = *(leafNode->iteratorBegin());
	Registry* brotherReg = *(brotherNode->iteratorBegin());

	if(actualReg->compareTo(brotherReg) < 0){
		leafNode->transferRegistry(listRegLeftNode);
		brotherNode->transferRegistry(listRegRightNode);
		leftNode = leafNode;
		rightNode = brotherNode;
	}else{
		brotherNode->transferRegistry(listRegLeftNode);
		leafNode->transferRegistry(listRegRightNode);
		leftNode = brotherNode;
		rightNode = leafNode;
	}

	this->mergeComponentList(this->listRegistry,listRegLeftNode,listRegRightNode);

	this->listRegistry.push_back(registry);
	this->listRegistry.sort(comparatorRegistry);

	list<Registry*>::iterator itListRegistry = this->listRegistry.begin();
	while(leftNode->posibleToAgregateComponent(*itListRegistry)){
		leftNode->addComponent(*itListRegistry);
		itListRegistry++;
	}

	container->setLeftRegKey(this->extractKey(*itListRegistry));

	while(rightNode->posibleToAgregateComponent(*itListRegistry)){
			rightNode->addComponent(*itListRegistry);
			itListRegistry++;
		}
	container->setRightRegKey(this->extractKey(*itListRegistry));

	while(itListRegistry != this->listRegistry.end()){
		if(newLeafNode->posibleToAgregateComponent(*itListRegistry))
			newLeafNode->addComponent(*itListRegistry);
		else
			break;
		itListRegistry++;
	}

	newLeafNode->setNextBlock(rightNode->getNextBlock());
	rightNode->setNextBlock(newLeafNode->getNumBlock());

	this->writeBlock(leftNode,leftNode->getNumBlock());
	this->writeBlock(rightNode,rightNode->getNumBlock());
	this->writeBlock(newLeafNode,newLeafNode->getNumBlock());

	container->setLeftBlock(leftNode->getNumBlock());
	container->setRigthMedium(rightNode->getNumBlock());
	container->setRightBlock(newLeafNode->getNumBlock());

}

bool IndexBSharp::balanceInternalNode(InternalNode* internalNode, InternalNode* brotherNode, ContainerInsertion* container, Registry* fatherReg) throw(){
//SE BALANCEA POR TAMAÑO
//SE LLENA EL BLOQUE DE LA IZQUIERDA LO MAS POSIBLE, LUEGO SE INTENTA LLENAR EL DE LA DERECHA

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
	Registry*  brotherReg =(*(brotherNode->iteratorBegin()));


	InternalNode* leftNode;
	InternalNode* rightNode;
	list<Registry*> listRegLeftNode;
	list<Registry*> listRegRightNode;
	std::vector<int> listBranchLeftNode;
	std::vector<int> listBranchRightNode;

	//Diferencio cual es el bloque izquierdo del derecho
	if (currentReg->compareTo(brotherReg) < 0 ) {
		internalNode->transferRegistry(listRegLeftNode);
		brotherNode->transferRegistry(listRegRightNode);
		internalNode->transferBranchs(listBranchLeftNode);
		brotherNode->transferBranchs(listBranchRightNode);
		leftNode = internalNode;
		rightNode = brotherNode;
	}else{
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
	unsigned int positionInsert = searchPositionInsertInternalNode(regKey,this->listRegistry.begin(),this->listRegistry.end());
	this->listRegistry.push_back(regKey);
	this->listRegistry.sort(comparatorRegistry);


	//adelanto el puntero
	std::vector<int>::iterator itListBranchs = this->branchList.begin();
	this->advanceVectorPointer(itListBranchs ,positionInsert + 1);
	// Inserta la rama
	branchList.insert(itListBranchs,numRightNode);

	list<Registry*>::iterator itFinalListRegistry = this->listRegistry.begin();
	std::vector<int>::iterator itFinalListBranchs = this->branchList.begin();

	leftNode->addBranch(*itFinalListBranchs);
	itFinalListBranchs++;

	while (leftNode->posibleToAgregateComponent(*itFinalListRegistry)){
		leftNode->addBranch(*itFinalListBranchs);
		leftNode->addComponent(*itFinalListRegistry);
		itFinalListRegistry++;
		itFinalListBranchs++;
	}

	rightNode->addBranch(*itFinalListBranchs);
	itFinalListBranchs++;

	// Establece el elemento medio a subir en el resultado de insercion
	Registry* copy = container->getRegMidleKey();
	container->setRegMidleKey(this->extractKey(*itFinalListRegistry));
	itFinalListRegistry++;
	while (itFinalListRegistry != this->listRegistry.end()){
		if (rightNode->posibleToAgregateComponent(*itFinalListRegistry)){
			rightNode->addBranch(*itFinalListBranchs);
			rightNode->addComponent(*itFinalListRegistry);
		}
		else
			break;
		itFinalListRegistry++;
		itFinalListBranchs++;
	}

	if (itFinalListRegistry != this->listRegistry.end()){
		leftNode->clearListRegistry();
		list<Registry*>::iterator registryList = listRegLeftNode.begin();
		while (registryList != listRegLeftNode.end()){
			leftNode->addComponent(*registryList);
			registryList++;
		}
		rightNode->clearListRegistry();
		registryList = listRegRightNode.begin();
		while (registryList != listRegRightNode.end()){
			rightNode->addComponent(*registryList);
			registryList++;
		}
		listRegLeftNode.clear();
		listRegRightNode.clear();

		leftNode->clearBranch();

		std::vector<int>::iterator branchList = listBranchLeftNode.begin();
		while (branchList != listBranchLeftNode.end()){
			leftNode->addBranch(*branchList);
			branchList++;
		}
		rightNode->clearBranch();
		branchList = listBranchRightNode.begin();
		while (branchList != listBranchRightNode.end()){
			rightNode->addBranch(*branchList);
			branchList++;
		}
		listBranchLeftNode.clear();
		listBranchRightNode.clear();

		container->setRegMidleKey(copy);
		return false;
	}
	else{
		// Escribe bloque izquierdo
		this->writeBlock(leftNode,leftNode->getNumBlock());
		// Escribe bloque derecho
		this->writeBlock(rightNode,rightNode->getNumBlock());
		return true;
	}

	return false;
}

int IndexBSharp::insertInternalNode(InternalNode* internalNode,Registry* registryKey,ContainerInsertion* container,unsigned int brotherBlock, Registry* aux) throw(){
	// Considero que no hay sobreflujo al insertar en el bloque interno
	bool isOverflow = false;
	// Busco la rama por la cual insertar
	int branchInsert = this->searchBranch(internalNode, registryKey);
	// Leo el bloque por el cual insertar
	Node* nodeInsert= this->readNode(branchInsert);
	nodeInsert->print(cout);
	// Si el bloque existe
	if (nodeInsert != NULL) {
		// Considero que no hay sobreflujo al insertar en el bloque hijo
		bool isOverflowChild = false;
		if (nodeInsert->isLeaf()) {
			LeafNode* leafNodeInsert =static_cast<LeafNode*>(nodeInsert);
			// Inserto en el bloque externo hijo
			isOverflowChild = this->insertLeafNode(leafNodeInsert, registryKey, container);
		} else {
			InternalNode* internalNodeInsert =static_cast<InternalNode*>(nodeInsert);
			// Inserto en el bloque interno hijo
			isOverflowChild = this->insertInternalNode(internalNodeInsert, registryKey, container);
		}

		// Verifico si hubo sobrelujo al insertar en el bloque hijo
		if (isOverflowChild) {
			// Verifico si puedo agregar en el bloque interno
			if (internalNode->posibleToAgregateComponent(container->getRegMidleKey())) {
				// Inserto en el bloque interno no lleno
				this->insertInternalNodeNotFull(internalNode, container->getRegMidleKey(),container->getRightBlock());
			} else {
				// Inserto en el bloque interno lleno
				isOverflow = true;
				this->insertInternalNodeFull(internalNode, container->getRegMidleKey(),container->getRightBlock(),container);
			}
		}
	}
	return isOverflow;
}
void IndexBSharp::insertInternalNodeNotFull(InternalNode* internalNode,Registry* registryKey,unsigned int rightBlock) throw(){
	unsigned int insertPosition = this->searchPositionInsertInternalNode(registryKey, internalNode->iteratorBegin(), internalNode->iteratorEnd());

	   internalNode->addReg(registryKey);
		internalNode->sortListRegistry();
	// Agrego rama
	vector<int>::iterator iterator=internalNode->firstBranch();
	 for (unsigned int var = 0; var < insertPosition + 1; var++) {
	    	  iterator++;
		}
	internalNode->addBranch(iterator,rightBlock);
	// Actualizo espacio libre
	this->freeBlockController->writeSizeBusy(internalNode->getNumBlock(), internalNode->getOcupedLong());
	// Escribo bloque
	this->writeBlock(internalNode, internalNode->getNumBlock());
}
void IndexBSharp::insertInternalNodeFull(InternalNode* internalNode,Registry* registry,unsigned int rightBlock,ContainerInsertion* container) throw(){
	// Busco numero de bloque libre
	unsigned int numBlockFree = this->freeBlockController->searchSizeBusy();
	// Creo nuevo bloque interno para dividir
	InternalNode* newInternalNode = new InternalNode(this->typeElement,this->sizeBlock, numBlockFree, internalNode->getLevel());

	// Crea contenedor de registros para insertar ordenado el registro...
	listRegistry.clear();
	// Crea contenedor de ramas para insertar la rama nueva...
	branchList.clear();

	// Transfiere todos los regsitros del bloque interno a la lista de registros para insertar ordenado el regitro...
	internalNode->transferRegistry(listRegistry);
	// Transfiere todas las ramas del bloque interno a la lista de ramas para insertar la rama...
	internalNode->transferBranchs(branchList);
	// Busca posicion de insercion para el registro...
	unsigned int insertPos = searchPositionInsertInternalNode(registry, listRegistry.begin(), listRegistry.end());

	listRegistry.push_back(registry);
	listRegistry.sort(comparatorRegistry);
	//adelanto el puntero
	std::vector<int>::iterator itListBranchs = branchList.begin();
	this->advanceVectorPointer(itListBranchs ,insertPos + 1);
	// Inserta la rama
	branchList.insert(itListBranchs, rightBlock);

	// Obtiene elemento medio...
	list<Registry*>::iterator iteratorPosMedium=listRegistry.begin();
	this->advanceListPointer(iteratorPosMedium,(listRegistry.size() / 2));

	// Establece el elemento medio a subir en el resultado de insercion
	Registry* registryMedium=*iteratorPosMedium;
	container->setRegMidleKey(registryMedium->clone());

	// Inserta elementos a la izquierda del medio en bloque a dividir

	for (std::list<Registry*>::iterator actual = listRegistry.begin(); actual != iteratorPosMedium; ++actual) {
		Registry* reg=*actual;
		internalNode->addReg(reg);
	}

	// Inserta elementos a la derecha del medio en bloque nuevo
	iteratorPosMedium++;
	for (std::list<Registry*>::iterator actual = iteratorPosMedium; actual != listRegistry.end(); ++actual) {
		newInternalNode->addReg(*actual);
	}


	unsigned int counterLeftBranches = (internalNode->getNumElements() + 1);
	unsigned int counterRightBranches = branchList.size() - counterLeftBranches;

	std::vector<int>::iterator actual = branchList.begin();
	unsigned int counter = 0;
	while (counter < counterLeftBranches && actual != branchList.end()) {
		internalNode->addBranch(*actual);
		++actual;
	        ++counter;
	}

	counter = 0;
	while (counter < counterRightBranches && actual != branchList.end()) {
		newInternalNode->addBranch(*actual);
		++actual;
	        ++counter;
	}

	newInternalNode->setNextBlock(internalNode->getNextBlock());
	internalNode->setNextBlock(newInternalNode->getNumBlock());
	// Actualiza espacio ocupado para el bloque a dividir
	this->freeBlockController->writeSizeBusy(internalNode->getNumBlock(), internalNode->getOcupedLong());
	// Escribe bloque a dividir en disco
	this->writeBlock(internalNode, internalNode->getNumBlock());

	// Actualiza espacio ocupado para el bloque nuevo
	this->freeBlockController->writeSizeBusy(newInternalNode->getNumBlock(), newInternalNode->getOcupedLong());

	// Escribe bloque nuevo
	this->writeBlock(newInternalNode, newInternalNode->getNumBlock());


	// Establezco bloque derecho en resultado de insercion
	container->setRightBlock(newInternalNode->getNumBlock());

}
unsigned int IndexBSharp::searchPositionInsertLeafNode(Registry* registry, list<Registry*>::iterator iteratorBegin, list<Registry*>::iterator iteratorEnd) throw(){
	unsigned int insertPos = 0;
	for (list<Registry*>::iterator actual= iteratorBegin; actual != iteratorEnd ; ++actual, ++insertPos) {
		Registry* reg = *actual;
		if (!(reg->compareTo(registry) < 0)) {
			break;
		}
	}
	return insertPos;
}
unsigned int IndexBSharp::searchPositionInsertInternalNode(Registry* registry, list<Registry*>::iterator iteratorBegin, list<Registry*>::iterator iteratorEnd) throw(){
	unsigned int insertPos = 0;
	for (list<Registry*>::iterator actual= iteratorBegin; actual != iteratorEnd ; ++actual, ++insertPos) {
		Registry* reg = *actual;
		if ((reg->compareTo(registry) < 0)||(reg->compareTo(registry)==0)) {

		}else {
			break;
		}
	}
	return insertPos;
}
int IndexBSharp::searchBranch(InternalNode* internalNode,Registry* registry) throw(){

	std::list<Registry*>::const_iterator actualComponent = internalNode->iteratorBegin();
	std::list<Registry*>::const_iterator endComponent = internalNode->iteratorEnd();
	unsigned int branchPos = 0;
	while (actualComponent != endComponent) {
		Registry* actual=*actualComponent;
		if (registry->compareTo(actual) < 0) {
			break;
		}
		++actualComponent;
		++branchPos;
	}
	return internalNode->getBranch(branchPos);

}
Registry* IndexBSharp::extractKey(Registry* registry) throw(){
	return registry->cloneRegKey();
}
Registry* IndexBSharp::searchLeafNode(LeafNode* leafNode,Registry* registry) throw(){
	Registry* findRegistry = NULL;
	bool find = false;

	if (leafNode != NULL) {
		std::list<Registry*>::const_iterator actualComponent = leafNode->iteratorBegin();
		std::list<Registry*>::const_iterator endComponent = leafNode->iteratorEnd();

		while (actualComponent != endComponent && !find) {
			Registry* iterRegistry = *actualComponent;
			if (iterRegistry->compareTo(registry)==0) {
				findRegistry = iterRegistry;
				find = true;
			}
			++actualComponent;
		}
	}
	return findRegistry;
}
Registry*  IndexBSharp::searchInternalNode(InternalNode* internalNode,Registry* registry) throw(){

	Registry* findRegistry = NULL;
	if (internalNode != NULL) {
		int searchBranch = this->searchBranch(internalNode,registry);
		Node* readNode = this->readNode(searchBranch);
		if (readNode != NULL) {
			if (readNode->isLeaf()) {
				LeafNode* leafNodeRead = (LeafNode*)readNode;
				findRegistry = this->searchLeafNode(leafNodeRead, registry);
			} else {
				InternalNode* internalNodeRead = (InternalNode*)readNode;
				findRegistry = this->searchInternalNode(internalNodeRead, registry);
			}
		}
	}
	return findRegistry;

}
void IndexBSharp::printRecursive(Node* currentNode, std::ostream& outStream, unsigned int level) throw(){


	if (currentNode != NULL) {
		outStream << std::string(level * 4, '-');
		outStream << "NUMERO BLOQUE: " << currentNode->getNumBlock() << " ";
		outStream << "NIVEL: " << currentNode->getLevel() << " ";
		outStream << "COMPONENTES BLOQUE: "<<endl;
		list<Registry*>::iterator actualComp  = currentNode->iteratorBegin();
		list<Registry*>::iterator endComp = currentNode->iteratorEnd();
		while (actualComp != endComp) {
			Registry* reg =  *actualComp;
			this->printRegistry(reg, outStream);
			++actualComp;
		}
		if (currentNode->isLeaf()) {
			outStream << "--EN BLOQUE HOJA--";
			LeafNode* leafNode =  (LeafNode*)currentNode;
			outStream << "CON SIGUIENTE: " << leafNode->getNextBlock()<< " ";
			outStream << std::endl;
			outStream << std::endl;
			outStream << std::endl;
		} else {
			outStream << "--EN BLOQUE INTERNO--";
			InternalNode* internalNode = (InternalNode*)currentNode;
			std::vector<int>::const_iterator actualBranch = internalNode->firstBranch();
			std::vector<int>::const_iterator endBranch = internalNode->lastBranch();
			std::cout << "CON RAMAS(";
			while (actualBranch != endBranch) {
				outStream << " " << *actualBranch;
				++actualBranch;
			}
			outStream << " ) ";
			outStream << std::endl;
			outStream << std::endl;
			outStream << std::endl;

			actualBranch = internalNode->firstBranch();
			endBranch = internalNode->lastBranch();
			while (actualBranch != endBranch) {
				Node* childNode  = this->readNode(*actualBranch);
				if (childNode != NULL) {
					this->printRecursive(childNode, outStream, level + 1);
				}
				++actualBranch;
			}
		}
	}


}
void IndexBSharp::printRegistry(Registry* registry, std::ostream& outStream) throw(){
	registry->print(outStream);
}
